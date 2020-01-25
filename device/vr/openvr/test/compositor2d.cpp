#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/compositorproxy.h"

/* extern HRESULT (STDMETHODCALLTYPE *RealCreateTexture2D)(
  ID3D11Device *This,
  const D3D11_TEXTURE2D_DESC   *pDesc,
  const D3D11_SUBRESOURCE_DATA *pInitialData,
  ID3D11Texture2D              **ppTexture2D
); */

namespace compositor2d {

HWND twoDWindow = NULL;
ID3D11Texture2D *windowTex = nullptr;
RECT windowRect{};
uint32_t windowWidth = 0;
uint32_t windowHeight = 0;
IDXGISurface1 *windowGdiSurface = nullptr;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  char buffer[256];
  int written = GetWindowTextA(hwnd, buffer, sizeof(buffer));
  if (written && strstr(buffer, "Discord") != NULL) {
    *(HWND*)lParam = hwnd;
    return FALSE;
  }
  return TRUE;
}

HWND GetDiscordHwnd() {
  HWND hWnd = NULL;
  EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);
  return hWnd;
}

void blendWindow(vr::PVRCompositor *pvrcompositor, ID3D11Device5 *device, ID3D11DeviceContext4 *context, int iEye, ID3D11RenderTargetView *colorRenderTarget, ID3D11RenderTargetView *depthRenderTarget, ID3D11ShaderResourceView *depthIn) {
  HRESULT hr;
  
  if (!twoDWindow) {
    twoDWindow = GetDiscordHwnd();
    if (!twoDWindow) {
      getOut() << "failed to get 2d window: " << (void *)GetLastError() << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    if (!GetWindowRect(twoDWindow, &windowRect)) {
      getOut() << "failed to get 2d window rect: " << (void *)GetLastError() << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    windowWidth = windowRect.right - windowRect.left;
    windowHeight = windowRect.bottom - windowRect.top;
    
    getOut() << "got window rect: " << windowRect.left << " " << windowRect.right << " " << windowRect.top << " " << windowRect.bottom << " " << windowWidth << " " << windowHeight << std::endl;

    // getOut() << "succ 0.1 " << (void *)RealCreateTexture2D << std::endl;

    D3D11_TEXTURE2D_DESC desc{};
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    /* desc.Width = windowWidth;
    desc.Height = windowHeight; */
    desc.Width = desc.Height = 512;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    // desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    // desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
    // desc.BindFlags = 40; // D3D11_BIND_DEPTH_STENCIL
    desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // D3D11_BIND_DEPTH_STENCIL
    // desc.MiscFlags = 0; //D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_GDI_COMPATIBLE;

    hr = device->CreateTexture2D(
      &desc,
      NULL,
      &windowTex
    );
    if (FAILED(hr)) {
      getOut() << "failed to create 2d window tex: " << (void *)hr << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    getOut() << "created 2d window tex" << std::endl;
    
    hr = windowTex->QueryInterface(__uuidof(IDXGIResource1), (void **)&windowGdiSurface);
    if (FAILED(hr)) {
      getOut() << "failed to get 2d window gdi surface: " << (void *)hr << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    getOut() << "created 2d window gdi surface" << std::endl;
  }
  
  getOut() << "get gdi surface dc " << (void *)windowTex << " " << (void *)windowGdiSurface << std::endl;
  pvrcompositor->InfoQueueLog();

  HDC dstDc = nullptr;
  hr = windowGdiSurface->GetDC(
    true, // discard contents
    &dstDc
  );
  if (FAILED(hr)) {
    getOut() << "failed to get 2d window dst hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  getOut() << "get 2d window dc" << std::endl;
  
  HDC srcDc = GetWindowDC(twoDWindow);
  if (!srcDc) {
    getOut() << "failed to get 2d window src hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  getOut() << "blitting 2d window tex" << std::endl;
  
  if (!BitBlt(
    dstDc,
    0,
    0,
    windowWidth,
    windowHeight,
    srcDc,
    0,
    0,
    SRCCOPY
  )) {
    getOut() << "failed to blit 2d window: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  getOut() << "blitted 2d window tex" << std::endl;
  
  hr = windowGdiSurface->ReleaseDC(&windowRect);
  if (FAILED(hr)) {
    getOut() << "failed to release 2d window dst hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  if (!ReleaseDC(twoDWindow, srcDc)) {
    getOut() << "failed to release 2d window src hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
}

}