#include <map>

#define CINTERFACE
#define D3D11_NO_HELPERS
// #include <windows.h>
#include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "device/vr/openvr/test/out.h"
#include "device/vr/detours/detours.h"

std::map<ID3D11Texture2D *, ID3D11Texture2D *> texMap;
void (STDMETHODCALLTYPE *RealOMSetRenderTargets)(
  ID3D11DeviceContext *This,
  UINT                   NumViews,
  ID3D11RenderTargetView * const *ppRenderTargetViews,
  ID3D11DepthStencilView *pDepthStencilView
) = nullptr;
void STDMETHODCALLTYPE MineOMSetRenderTargets(
  ID3D11DeviceContext *This,
  UINT                   NumViews,
  ID3D11RenderTargetView * const *ppRenderTargetViews,
  ID3D11DepthStencilView *pDepthStencilView
) {
  // getOut() << "intercept " << NumViews << std::endl;

  if (NumViews > 0 && ppRenderTargetViews && pDepthStencilView) {
    ID3D11RenderTargetView * const pRenderTargetViews = *ppRenderTargetViews;
    for (uint32_t i = 0; i < NumViews; i++) {
      ID3D11Texture2D *tex;
      ID3D11Texture2D *depthTex;

      {
        ID3D11RenderTargetView * const pRenderTargetView = pRenderTargetViews + i;
        ID3D11Resource *texResource;
        pRenderTargetView->lpVtbl->GetResource(pRenderTargetView, &texResource);
        HRESULT hr = texResource->lpVtbl->QueryInterface(texResource, IID_ID3D11Texture2D, (void **)&tex);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to get hijack texture resource: " << (void *)hr << std::endl;
          abort();
        }
        texResource->lpVtbl->Release(texResource);
      }
      {
        ID3D11Resource *depthTexResource;
        pDepthStencilView->lpVtbl->GetResource(pDepthStencilView, &depthTexResource);
        HRESULT hr = depthTexResource->lpVtbl->QueryInterface(depthTexResource, IID_ID3D11Texture2D, (void **)&depthTex);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
          abort();
        }
        depthTexResource->lpVtbl->Release(depthTexResource);
      }
      
      auto iter = texMap.find(tex);
      if (iter == texMap.end()) {
        // getOut() << "add tex " << (void *)tex << " " << (void *)depthTex << std::endl;
        texMap.emplace(tex, depthTex);
      } else {
        tex->lpVtbl->Release(tex);
        depthTex->lpVtbl->Release(depthTex);
      }
    }
    
    /* ID3D11Resource *depthResource;
    pRenderTargetView->lpVtbl->GetResource(pRenderTargetView, &depthResource);
    ID3D11Texture2D *depthTex;
    HRESULT hr = depthResource->lpVtbl->QueryInterface(depthResource, IID_ID3D11Texture2D, (void **)&depthTex);
    if (SUCCEEDED(hr)) {
      // getOut() << "got resource ok" << std::endl;
      D3D11_TEXTURE2D_DESC desc;
      depthTex->lpVtbl->GetDesc(depthTex, &desc);
      getOut() << "got source depth desc " << (void *)depthTex << " " << desc.Width << " " << desc.Height << " " << desc.Format << " " << desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags << std::endl;
    } else {
      getOut() << "got resource fail" << std::endl;
      abort();
      // D3D11_RESOURCE_DIMENSION dimension;
    } */
  }
  
  RealOMSetRenderTargets(This, NumViews, ppRenderTargetViews, pDepthStencilView);
}

bool hijacked = false;

void hijack(ID3D11DeviceContext *context) {
  if (!hijacked) {
    getOut() << "detour 1" << std::endl;
    LONG error = DetourTransactionBegin();
    getOut() << "detour 2 " << error << std::endl;
    error = DetourUpdateThread(GetCurrentThread());
    getOut() << "detour 3 " << error << std::endl;
    // error = DetourAttach(&(PVOID&)DID3D11DeviceContext::copySubresourceRegion, *(PBYTE*)&fakeFn);
    RealOMSetRenderTargets = context->lpVtbl->OMSetRenderTargets;
    error = DetourAttach(&(PVOID&)RealOMSetRenderTargets, MineOMSetRenderTargets);
    getOut() << "detour 4 " << error << std::endl;
    error = DetourTransactionCommit();
    getOut() << "detour 5 " << error << std::endl;
    hijacked = true;
  }
}
ID3D11Texture2D *getDepthTextureMatching(ID3D11Texture2D *tex) {
  auto iter = texMap.find(tex);
  // getOut() << "get depth texture matching " << (void *)tex << " " << (iter != texMap.end()) << std::endl;
  if (iter != texMap.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}
void flushTextureLatches() {
  if (texMap.size() > 0) {
    for (auto iter : texMap) {
      iter.first->lpVtbl->Release(iter.first);
      iter.second->lpVtbl->Release(iter.second);
    }
    texMap.clear();
  }
}