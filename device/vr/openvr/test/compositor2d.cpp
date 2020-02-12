#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/matrix.h"

#include <psapi.h>

namespace compositor2d {

std::vector<HWND> hwnds;
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
  vr::PVRCompositor::CreateDevice(&device, &context, &swapChain);
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
  
  getOut() << "try cwd " << cwd << std::endl;

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
          
          if (!tex) {
            RECT rect;          
            GetClientRect(hWnd, &rect);
            
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;
            
            D3D11_TEXTURE2D_DESC desc{};
            desc.Width = width;
            desc.Height = height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.BindFlags = 0;
            desc.MiscFlags = 0;

            ID3D11Texture2D *tex = nullptr;
            HRESULT hr = device->CreateTexture2D(
              &desc,
              NULL,
              &tex
            );
            if (FAILED(hr)) {
              getOut() << "failed to create dc texture: " << (void *)hr << std::endl;
              abort();
            }
            
            hr = tex->QueryInterface(__uuidof(IDXGISurface1), (void **)&dxgiSurface1);
            if (FAILED(hr)) {
              getOut() << "failed to query dc texture surface: " << (void *)hr << std::endl;
              abort();
            }
          }
          
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
          dxgiSurface1->Release();
        }
      }
    }
    Sleep(1000);
  }
}

}