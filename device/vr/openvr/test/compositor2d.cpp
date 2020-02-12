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
  
  static const uint32_t cursorSize = 11;
  static size_t numOverlays;
  static ID3D11Texture2D *blackTex;
  static ID3D11Resource *blackResource;

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

    g_vroverlay->SetOverlayFlag(overlay, VROverlayFlags_NoDashboardTab, true);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay flag: " << (void *)error << std::endl;
    }
    /* g_vroverlay->SetOverlayFlag(overlay, VROverlayFlags_VisibleInDashboard, true);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay flag: " << (void *)error << std::endl;
    } */
    
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
    
    error = g_vroverlay->SetOverlayInputMethod(overlay, VROverlayInputMethod_Mouse);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay input method: " << (void *)error << std::endl;
    }
    
    /* error = g_vroverlay->TriggerLaserMouseHapticVibration(overlay, 0.1, 50.0, 0.5);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay haptics: " << (void *)error << std::endl;
    } */
    
    getOut() << "create overlay " << width << " " << height << " " << position[0] << " " << position[1] << " " << position[2] << std::endl;
    
    if (!blackTex) {
      D3D11_TEXTURE2D_DESC blackDesc{};
      blackDesc.Width = cursorSize;
      blackDesc.Height = cursorSize;
      blackDesc.MipLevels = 1;
      blackDesc.ArraySize = 1;
      blackDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
      blackDesc.Usage = D3D11_USAGE_DEFAULT;
      blackDesc.SampleDesc.Count = 1;
      blackDesc.SampleDesc.Quality = 0;
      blackDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
      // desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
      
      HRESULT hr = device->CreateTexture2D(
        &blackDesc,
        NULL,
        &blackTex
      );
      if (FAILED(hr) || !tex) {
        getOut() << "failed to create black texture: " << (void *)hr << std::endl;
        abort();
      }
      
      hr = blackTex->QueryInterface(__uuidof(ID3D11Resource), (void **)&blackResource);
      if (FAILED(hr) || !dxgiSurface1) {
        getOut() << "failed to query black texture resource: " << (void *)hr << std::endl;
        abort();
      }
    }
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
    
    /* HmdVector2_t vecWindowSize = {
      width,
      height
    };
    EVROverlayError error = g_vroverlay->SetOverlayMouseScale(overlay, &vecWindowSize);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay mouse scale: " << (void *)error << std::endl;
    } */

    getOut() << "create surface " << width << " " << height << std::endl;
  }
  void tick() {    
    HDC hdcWindow = GetDC(hWnd);
    HDC texDc;
    HRESULT hr = dxgiSurface1->GetDC(false, &texDc);
    if (FAILED(hr)) {
      getOut() << "failed to get tex dc: " << (void *)hr << std::endl;
      abort();
    }

    BOOL blitResult = BitBlt(
      texDc,
      0,
      0,
      width,
      height,
      hdcWindow,
      0,
      0,
      SRCCOPY
    );
    if (!blitResult) {
      getOut() << "blit failed: " << (void *)GetLastError() << std::endl;
    }

    ReleaseDC(hWnd, hdcWindow);
    dxgiSurface1->ReleaseDC(nullptr);
    // GdiFlush();
    
    /* VREvent_t event;
    while (g_vroverlay->PollNextOverlayEvent(overlay, &event, sizeof(event))) {
      switch (event.eventType) {
        case VREvent_MouseMove: {
          getOut() << "mouse move" << std::endl;
          break;
        }
        case VREvent_MouseButtonDown: {
          getOut() << "mouse down" << std::endl;
          break;
        }
        case VREvent_MouseButtonUp: {
          getOut() << "mouse up" << std::endl;
          break;
        }
        case VREvent_FocusEnter: {
          getOut() << "focus enter" << std::endl;
          break;
        }
        case VREvent_FocusLeave: {
          getOut() << "focus leave" << std::endl;
          break;
        }
        case VREvent_TouchPadMove: {
          getOut() << "touchpad move" << std::endl;
          break;
        }
        // case VREvent_PropertyChanged:
        // case VREvent_TrackedDeviceUserInteractionStarted:
        // case VREvent_SceneApplicationStateChanged:
        // {
          // break;
        // }
        default: {
          getOut() << "unknown overlay event type: " << event.eventType << std::endl;
          break;
        }
      }
    } */
    
    // context->Flush();
    
    TrackedDevicePose_t cachedRenderPoses[k_unMaxTrackedDeviceCount];
    EVRCompositorError error2 = g_vrcompositor->GetLastPoses(cachedRenderPoses, ARRAYSIZE(cachedRenderPoses), nullptr, 0);
    if (error2 == VRCompositorError_None) {
      for (size_t i = 0; i < ARRAYSIZE(cachedRenderPoses); i++) {
        TrackedDevicePose_t &cachedRenderPose = cachedRenderPoses[i];

        if (cachedRenderPose.bPoseIsValid) {
          ETrackedDeviceClass deviceClass = g_vrsystem->GetTrackedDeviceClass(i);

          if (deviceClass == TrackedDeviceClass_Controller) {
            ETrackedControllerRole controllerRole = g_vrsystem->GetControllerRoleForTrackedDeviceIndex(i);
            if (controllerRole == TrackedControllerRole_LeftHand) {
              // XXX
            } else if (controllerRole == TrackedControllerRole_RightHand) {
              float viewMatrix[16];
              setPoseMatrix(viewMatrix, cachedRenderPose.mDeviceToAbsoluteTracking);
              float position[3];
              float quaternion[4];
              float scale[3];
              decomposeMatrix(viewMatrix, position, quaternion, scale);

              VROverlayIntersectionParams_t params{};
              memcpy(params.vSource.v, position, sizeof(position));
              float direction[3] = {0, 0, -1};
              applyVector3Quaternion(direction, quaternion);
              memcpy(params.vDirection.v, direction, sizeof(direction));
              params.eOrigin = TrackingUniverseStanding;
              VROverlayIntersectionResults_t results;
              if (g_vroverlay->ComputeOverlayIntersection(overlay, &params, &results) && results.fDistance < 3.0f) {
                float heightFactor = (float)height/(float)width;
                
                results.vUVs.v[1] = 1.0f - results.vUVs.v[1];
                results.vUVs.v[1] -= 0.5f;
                if (std::abs(results.vUVs.v[1]) < heightFactor/2) {
                  results.vUVs.v[1] /= heightFactor;
                  results.vUVs.v[1] += 0.5f;

                  D3D11_BOX srcBox{};
                  srcBox.left = 0;
                  srcBox.right = cursorSize;
                  srcBox.top = 0;
                  srcBox.bottom = cursorSize;
                  srcBox.front = 0;
                  srcBox.back = 1;
                  uint32_t x = std::min<uint32_t>(std::max<uint32_t>(((float)width * results.vUVs.v[0]) - ((float)cursorSize-1)/2, 0), width);
                  uint32_t y = std::min<uint32_t>(std::max<uint32_t>(((float)height * results.vUVs.v[1]) - ((float)cursorSize-1)/2, 0), height);
                  context->CopySubresourceRegion(tex, 0, x, y, 0, blackTex, 0, &srcBox);
                }
              }
            }
          }
        }
      }
    }
    
    context->Flush();
    
    Texture_t vrTexDesc{};
    vrTexDesc.handle = surfaceShareHandle;
    vrTexDesc.eType = TextureType_DXGISharedHandle;
    vrTexDesc.eColorSpace = ColorSpace_Auto;
    EVROverlayError error = g_vroverlay->SetOverlayTexture(overlay, &vrTexDesc);
    if (error != VROverlayError_None) {
      getOut() << "error setting overlay texture: " << (void *)error << std::endl;
    }

    seen = true;
  }
};
size_t WindowOverlay::numOverlays = 0;
ID3D11Texture2D *WindowOverlay::blackTex = nullptr;
ID3D11Resource *WindowOverlay::blackResource = nullptr;

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
          windowOverlay.tick();
        }
      }
    }
    Sleep(100);
  }
}

}