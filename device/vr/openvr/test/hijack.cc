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
std::vector<ID3D11Texture2D *> texOrder;

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
  // getOut() << "intercept 1" << std::endl;

  if (NumViews > 0 && ppRenderTargetViews && pDepthStencilView) {
    // getOut() << "intercept 2 " << NumViews << std::endl;
    
    ID3D11RenderTargetView * const pRenderTargetViews = *ppRenderTargetViews;

    if (pRenderTargetViews) {
      // getOut() << "intercept 2.1 " << (void *)pRenderTargetViews << std::endl;

      for (uint32_t i = 0; i < NumViews; i++) {
        ID3D11Texture2D *tex = nullptr;
        ID3D11Texture2D *depthTex = nullptr;

        // getOut() << "intercept 3 " << i << " " << NumViews << std::endl;

        {
          ID3D11RenderTargetView * const pRenderTargetView = pRenderTargetViews + i;
          
          // getOut() << "intercept 4.1 " << (void *)pRenderTargetView << std::endl;
          
          ID3D11Resource *texResource = nullptr;
          pRenderTargetView->lpVtbl->GetResource(pRenderTargetView, &texResource);
          // getOut() << "intercept 4.1 " << (void *)texResource << std::endl;
          HRESULT hr = texResource->lpVtbl->QueryInterface(texResource, IID_ID3D11Texture2D, (void **)&tex);
          // getOut() << "intercept 4.2 " << (void *)tex << std::endl;
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to get hijack texture resource: " << (void *)hr << std::endl;
            abort();
          }
          texResource->lpVtbl->Release(texResource);
        }
        // getOut() << "intercept 5" << std::endl;
        {
          ID3D11Resource *depthTexResource = nullptr;
          pDepthStencilView->lpVtbl->GetResource(pDepthStencilView, &depthTexResource);
          HRESULT hr = depthTexResource->lpVtbl->QueryInterface(depthTexResource, IID_ID3D11Texture2D, (void **)&depthTex);
          // getOut() << "intercept 6" << std::endl;
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
            abort();
          }
          depthTexResource->lpVtbl->Release(depthTexResource);
        }
        
        /// getOut() << "intercept 7" << std::endl;
        
        auto iter = texMap.find(tex);
        if (iter == texMap.end()) {
          D3D11_TEXTURE2D_DESC desc;
          tex->lpVtbl->GetDesc(tex, &desc);
          D3D11_TEXTURE2D_DESC descDepth;
          depthTex->lpVtbl->GetDesc(depthTex, &descDepth);
          /* 2124 2348
          1 1
          2 0
          19 // DXGI_FORMAT_R32G8X24_TYPELESS
          0 64 0 0 */ // D3D11_BIND_DEPTH_STENCIL
          getOut() << "add tex " << (void *)tex << " " << (void *)depthTex << " | " <<
            desc.Width << " " << desc.Height << " " <<
            desc.MipLevels << " " << desc.ArraySize << " " <<
            desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
            desc.Format << " " <<
            desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags << " | " <<
            descDepth.Width << " " << descDepth.Height << " " <<
            descDepth.MipLevels << " " << descDepth.ArraySize << " " <<
            descDepth.SampleDesc.Count << " " << descDepth.SampleDesc.Quality << " " <<
            descDepth.Format << " " <<
            descDepth.Usage << " " << descDepth.BindFlags << " " << descDepth.CPUAccessFlags << " " << descDepth.MiscFlags <<
            std::endl;

          texMap.emplace(tex, depthTex);
          texOrder.push_back(tex);
        } else {
          tex->lpVtbl->Release(tex);
          depthTex->lpVtbl->Release(depthTex);
        }
        
        // getOut() << "intercept 8" << std::endl;
      }
    }
  }
  
  // getOut() << "intercept 9" << std::endl;
  
  RealOMSetRenderTargets(This, NumViews, ppRenderTargetViews, pDepthStencilView);

  // getOut() << "intercept 10" << std::endl;
}

bool hijacked = false;

void hijack(ID3D11DeviceContext *context) {
  if (!hijacked) {
    LONG error = DetourTransactionBegin();
    if (error) {
      getOut() << "detour error 1: " << (void *)error << std::endl;
      abort();
    }
    error = DetourUpdateThread(GetCurrentThread());
    if (error) {
      getOut() << "detour error 2: " << (void *)error << std::endl;
      abort();
    }
    getOut() << "detour 3 " << error << std::endl;
    if (error) {
      getOut() << "detour error 3: " << (void *)error << std::endl;
      abort();
    }
    RealOMSetRenderTargets = context->lpVtbl->OMSetRenderTargets;
    error = DetourAttach(&(PVOID&)RealOMSetRenderTargets, MineOMSetRenderTargets);
    if (error) {
      getOut() << "detour error 4: " << (void *)error << std::endl;
      abort();
    }
    error = DetourTransactionCommit();
    if (error) {
      getOut() << "detour error 5: " << (void *)error << std::endl;
      abort();
    }
    hijacked = true;
  }
}
ID3D11Texture2D *getDepthTextureMatching(ID3D11Texture2D *tex) {
  auto iter = texMap.find(tex);
  // getOut() << "get depth texture matching " << (void *)tex << " " << (iter != texMap.end()) << std::endl;
  if (iter != texMap.end()) {
    auto iter2 = std::find(texOrder.begin(), texOrder.end(), tex);
    iter2--;
    ID3D11Texture2D *tex2 = *iter2;
    iter = texMap.find(tex2);
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
    texOrder.clear();
  }
}