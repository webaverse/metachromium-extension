#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/overlayproxy.h"
#include "device/vr/openvr/test/matrix.h"

#include <psapi.h>

using namespace vr;

namespace compositor2d {

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
};

std::vector<HWND> hwnds;
std::map<HANDLE, WindowOverlay> windowOverlays;
size_t numOverlays = 0;

BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
  hwnds.push_back(hwnd);
  return true;
}
void homeRenderLoop() {
  ID3D11Device5 *device;
  ID3D11DeviceContext4 *context;
  IDXGISwapChain *swapChain;
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
          getOut() << "got chrome window " << result << " " << buffer << " " << txt << std::endl;

          auto iter = windowOverlays.find(hWnd);
          if (iter == windowOverlays.end()) {
            WindowOverlay windowOverlay{};

            RECT rect;          
            GetClientRect(hWnd, &rect);

            windowOverlay.width = rect.right - rect.left;
            windowOverlay.height = rect.bottom - rect.top;

            D3D11_TEXTURE2D_DESC desc{};
            desc.Width = windowOverlay.width;
            desc.Height = windowOverlay.height;
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
              &windowOverlay.tex
            );
            if (FAILED(hr) || !windowOverlay.tex) {
              getOut() << "failed to create dc texture: " << (void *)hr << std::endl;
              abort();
            }

            hr = windowOverlay.tex->QueryInterface(__uuidof(IDXGISurface1), (void **)&windowOverlay.dxgiSurface1);
            if (FAILED(hr) || !windowOverlay.dxgiSurface1) {
              getOut() << "failed to query dc texture surface: " << (void *)hr << std::endl;
              abort();
            }
            
            hr = windowOverlay.tex->QueryInterface(__uuidof(IDXGIResource), (void **)&windowOverlay.dxgiResource);
            if (FAILED(hr) || !windowOverlay.dxgiResource) {
              getOut() << "failed to query dc texture surface: " << (void *)hr << std::endl;
              abort();
            }
            
            hr = windowOverlay.dxgiResource->GetSharedHandle(&windowOverlay.surfaceShareHandle);
            if (FAILED(hr) || !windowOverlay.surfaceShareHandle) {
              getOut() << "failed to get dc surface shared handle: " << (void *)hr << std::endl;
              abort();
            }

            getOut() << "create surface " << (void *)windowOverlay.dxgiSurface1 << std::endl;

            std::string overlayName("metachromium");
            overlayName += std::to_string(++numOverlays);
            EVROverlayError error = g_vroverlay->CreateOverlay(overlayName.c_str(), overlayName.c_str(), &windowOverlay.overlay);
            if (error != VROverlayError_None) {
              getOut() << "error creating overlay: " << (void *)error << std::endl;
            }

            Texture_t vrTexDesc{};
            vrTexDesc.handle = windowOverlay.surfaceShareHandle;
            vrTexDesc.eType = TextureType_DXGISharedHandle;
            vrTexDesc.eColorSpace = ColorSpace_Auto;
            error = g_vroverlay->SetOverlayTexture(windowOverlay.overlay, &vrTexDesc);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay texture: " << (void *)error << std::endl;
            }

            g_vroverlay->SetOverlayFlag(windowOverlay.overlay, VROverlayFlags_NoDashboardTab, true);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay flag: " << (void *)error << std::endl;
            }
            g_vroverlay->SetOverlayFlag(windowOverlay.overlay, VROverlayFlags_VisibleInDashboard, true);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay flag: " << (void *)error << std::endl;
            }
            
            error = g_vroverlay->SetOverlayWidthInMeters(windowOverlay.overlay, 1);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay width: " << (void *)error << std::endl;
            }
            
            g_vroverlay->SetOverlayColor(windowOverlay.overlay, 0, 0, 0.5);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay color: " << (void *)error << std::endl;
            }
            
            HmdMatrix34_t mat{};
            mat.m[0][0] = 1;
            mat.m[1][1] = 1;
            mat.m[2][2] = 1;
            error = g_vroverlay->SetOverlayTransformAbsolute(windowOverlay.overlay, TrackingUniverseStanding, &mat);
            if (error != VROverlayError_None) {
              getOut() << "error setting overlay transform: " << (void *)error << std::endl;
            }
            
            error = g_vroverlay->ShowOverlay(windowOverlay.overlay);
            if (error != VROverlayError_None) {
              getOut() << "error showing overlay: " << (void *)error << std::endl;
            }

            windowOverlays.insert(std::pair<HANDLE, WindowOverlay>(hWnd, windowOverlay));
            iter = windowOverlays.find(hWnd);
          }
          WindowOverlay &windowOverlay = iter->second;

          getOut() << "dc 1" << std::endl;

          HDC hdcWindow = GetDC(hWnd);
          getOut() << "dc 2 " << (void *)hWnd << " " << (void *)windowOverlay.dxgiSurface1 << std::endl;
          HDC texDc;
          HRESULT hr = windowOverlay.dxgiSurface1->GetDC(false, &texDc);
          getOut() << "dc 3" << std::endl;
          if (FAILED(hr)) {
            getOut() << "failed to get tex dc: " << (void *)hr << std::endl;
            abort();
          }

          getOut() << "dc 4" << std::endl;

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
          
          getOut() << "dc 5" << std::endl;

          ReleaseDC(hWnd, hdcWindow);
          windowOverlay.dxgiSurface1->ReleaseDC(nullptr);
          
          windowOverlay.seen = true;
          
          getOut() << "dc 6" << std::endl;
        }
      }
    }
    Sleep(1000);
  }
}

}