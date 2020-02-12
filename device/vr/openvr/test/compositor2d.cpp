#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/overlayproxy.h"
#include "device/vr/openvr/test/matrix.h"

#include <psapi.h>

using namespace vr;

namespace compositor2d {

ID3D11Device5 *device;
ID3D11DeviceContext4 *context;
IDXGISwapChain *swapChain;

class WindowOverlay {
public:
  HWND hWnd;
  VROverlayHandle_t overlay;
  ID3D11Texture2D *tex;
  IDXGISurface1 *dxgiSurface1;
  IDXGIResource *dxgiResource;
  HANDLE surfaceShareHandle;
  int width;
  int height;
  bool seen;
  
  static size_t numOverlays;

public:
  WindowOverlay(HWND hWnd) :
    hWnd(hWnd)
  {
    RECT rect;          
    GetClientRect(hWnd, &rect);
    int newWidth = rect.right - rect.left;
    int newHeight = rect.bottom - rect.top;
    setBackingTexture(newWidth, newHeight);

    std::string overlayName("metachromium");
    overlayName += std::to_string(++numOverlays);
    EVROverlayError error = g_vroverlay->CreateOverlay(overlayName.c_str(), overlayName.c_str(), &overlay);
    if (error != VROverlayError_None) {
      getOut() << "error creating overlay: " << (void *)error << std::endl;
    }

    /* g_vroverlay->SetOverlayFlag(overlay, VROverlayFlags_NoDashboardTab, true);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay flag: " << (void *)error << std::endl;
    } */
    g_vroverlay->SetOverlayFlag(overlay, VROverlayFlags_VisibleInDashboard, true);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay flag: " << (void *)error << std::endl;
    }
    
    error = g_vroverlay->SetOverlayWidthInMeters(overlay, 1);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay width: " << (void *)error << std::endl;
    }
    
    /* g_vroverlay->SetOverlayColor(overlay, 0, 0, 0.5);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay color: " << (void *)error << std::endl;
    } */
    
    float position[16] = {0, numOverlays, -1};
    float quaternion[4] = {0, 0, 0, 1};
    float scale[3] = {1, 1, 1};
    float viewMatrix[16];
    composeMatrix(viewMatrix, position, quaternion, scale);
    
    HmdMatrix34_t mat;
    setPoseMatrix(mat, viewMatrix);
    error = g_vroverlay->SetOverlayTransformAbsolute(overlay, TrackingUniverseStanding, &mat);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay transform: " << (void *)error << std::endl;
    }

    error = g_vroverlay->ShowOverlay(overlay);
    if (error != VROverlayError_None) {
      getOut() << "error showing overlay: " << (void *)error << std::endl;
    }
    
    getOut() << "create overlay " << width << " " << height << " " << position[0] << " " << position[1] << " " << position[2] << std::endl;
  }
  void setBackingTexture(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.MiscFlags = D3D11_RESOURCE_MISC_GDI_COMPATIBLE | D3D11_RESOURCE_MISC_SHARED;

    HRESULT hr = device->CreateTexture2D(
      &desc,
      NULL,
      &tex
    );
    if (FAILED(hr) || !tex) {
      getOut() << "failed to create dc texture: " << (void *)hr << std::endl;
      abort();
    }

    hr = tex->QueryInterface(__uuidof(IDXGISurface1), (void **)&dxgiSurface1);
    if (FAILED(hr) || !dxgiSurface1) {
      getOut() << "failed to query dc texture surface: " << (void *)hr << std::endl;
      abort();
    }
    
    hr = tex->QueryInterface(__uuidof(IDXGIResource), (void **)&dxgiResource);
    if (FAILED(hr) || !dxgiResource) {
      getOut() << "failed to query dc texture surface: " << (void *)hr << std::endl;
      abort();
    }
    
    hr = dxgiResource->GetSharedHandle(&surfaceShareHandle);
    if (FAILED(hr) || !surfaceShareHandle) {
      getOut() << "failed to get dc surface shared handle: " << (void *)hr << std::endl;
      abort();
    }

    getOut() << "create surface " << width << " " << height << std::endl;
  }
};
size_t WindowOverlay::numOverlays = 0;

std::vector<HWND> hwnds;
std::map<HANDLE, WindowOverlay> windowOverlays;

BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
  hwnds.push_back(hwnd);
  return true;
}
void homeRenderLoop() {
  PVRCompositor::CreateDevice(&device, &context, &swapChain);
  ID3D11Texture2D *tex = nullptr;
  IDXGISurface1 *dxgiSurface1 = nullptr;
  int width = 0;
  int height = 0;
      
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  std::string cwd(cwdBuf);
  cwd += "\\chrome.exe";

  for (;;) {
    hwnds.clear();
    BOOL result = EnumWindows(
      EnumWindowsProc,
      NULL
    );
    for (auto hWnd : hwnds) {
      if (IsWindowVisible(hWnd)) {
        char buffer[MAX_PATH];
        DWORD dwProcId = 0; 

        GetWindowThreadProcessId(hWnd, &dwProcId);   

        HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);    
        DWORD result = GetModuleFileNameExA(hProc, NULL, buffer, sizeof(buffer));
        CloseHandle(hProc);

        char txt[MAX_PATH];
        GetWindowTextA(
          hWnd,
          txt,
          sizeof(txt)
        );

        if (result > 0 && cwd == buffer) {
          getOut() << "got chrome window " << hWnd << " " << windowOverlays.size() << " " << buffer << " " << txt << std::endl;

          auto iter = windowOverlays.find(hWnd);
          if (iter == windowOverlays.end()) {
            WindowOverlay windowOverlay(hWnd);

            windowOverlays.insert(std::pair<HANDLE, WindowOverlay>(hWnd, windowOverlay));
            iter = windowOverlays.find(hWnd);
          /* } else {
            WindowOverlay &windowOverlay = iter->second;
            
            RECT rect;          
            GetClientRect(windowOverlay.hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            
            if (width != windowOverlay.width || height != windowOverlay.height) {
              windowOverlay.setBackingTexture(width, height);
            } */
          }
          WindowOverlay &windowOverlay = iter->second;

          HDC hdcWindow = GetDC(hWnd);
          // getOut() << "dc " << (void *)hWnd << " " << (void *)windowOverlay.dxgiSurface1 << " " << windowOverlay.width << " " << windowOverlay.height << std::endl;
          HDC texDc;
          HRESULT hr = windowOverlay.dxgiSurface1->GetDC(false, &texDc);
          if (FAILED(hr)) {
            getOut() << "failed to get tex dc: " << (void *)hr << std::endl;
            abort();
          }

          BOOL blitResult = BitBlt(
            texDc,
            0,
            0,
            windowOverlay.width,
            windowOverlay.height,
            hdcWindow,
            0,
            0,
            SRCCOPY
          );
          if (!blitResult) {
            getOut() << "blit failed: " << (void *)GetLastError() << std::endl;
          }

          ReleaseDC(hWnd, hdcWindow);
          windowOverlay.dxgiSurface1->ReleaseDC(nullptr);

          {
            Texture_t vrTexDesc{};
            vrTexDesc.handle = windowOverlay.surfaceShareHandle;
            vrTexDesc.eType = TextureType_DXGISharedHandle;
            vrTexDesc.eColorSpace = ColorSpace_Auto;
            EVROverlayError error = g_vroverlay->SetOverlayTexture(windowOverlay.overlay, &vrTexDesc);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay texture: " << (void *)error << std::endl;
            }
          }
         
          windowOverlay.seen = true;
        }
      }
    }
    Sleep(100);
  }
}

}