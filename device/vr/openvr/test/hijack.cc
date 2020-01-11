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
          getOut() << "add tex " <<
            (void *)This << " | " <<
            (void *)tex << " " << (void *)depthTex << " | " <<
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
            
            2124 2348 1 1 8 0 19 0 64 0 0

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
void (STDMETHODCALLTYPE *RealOMSetDepthStencilState)(
  ID3D11DeviceContext *This,
  ID3D11DepthStencilState *pDepthStencilState,
  UINT                    StencilRef
) = nullptr;
void STDMETHODCALLTYPE MineOMSetDepthStencilState(
  ID3D11DeviceContext *This,
  ID3D11DepthStencilState *pDepthStencilState,
  UINT                    StencilRef
) {
  /* getOut() << "set depth stencil state " <<
    D3D11_COMPARISON_NEVER << " " <<
    D3D11_COMPARISON_LESS << " " <<
    D3D11_COMPARISON_EQUAL << " " <<
    D3D11_COMPARISON_LESS_EQUAL << " " <<
    D3D11_COMPARISON_GREATER << " " <<
    D3D11_COMPARISON_NOT_EQUAL << " " <<
    D3D11_COMPARISON_GREATER_EQUAL << " " <<
    D3D11_COMPARISON_ALWAYS << " " <<
    std::endl; */
  if (pDepthStencilState) {
    D3D11_DEPTH_STENCIL_DESC desc;
    pDepthStencilState->lpVtbl->GetDesc(pDepthStencilState, &desc);

    getOut() << "depth state " <<
      (void *)This << " " <<
      desc.DepthEnable << " " <<
      desc.DepthWriteMask << " " <<
      desc.DepthFunc << " " <<
      desc.StencilEnable << " " <<
      (void *)desc.StencilReadMask << " " <<
      (void *)desc.StencilWriteMask << " " <<
      desc.FrontFace.StencilFailOp << " " << desc.FrontFace.StencilDepthFailOp << " " << desc.FrontFace.StencilPassOp << " " << desc.FrontFace.StencilFunc << " " <<
      desc.BackFace.StencilFailOp << " " << desc.BackFace.StencilDepthFailOp << " " << desc.BackFace.StencilPassOp << " " << desc.BackFace.StencilFunc << " " <<
      std::endl;
  }
  RealOMSetDepthStencilState(This, pDepthStencilState, StencilRef);
}
void (STDMETHODCALLTYPE *RealDraw)(
  ID3D11DeviceContext *This,
  UINT VertexCount,
  UINT StartVertexLocation
) = nullptr;
void STDMETHODCALLTYPE MineDraw(
  ID3D11DeviceContext *This,
  UINT VertexCount,
  UINT StartVertexLocation
) {
  getOut() << "Draw" << std::endl;
  RealDraw(This, VertexCount, StartVertexLocation);
}
void (STDMETHODCALLTYPE *RealDrawAuto)(
  ID3D11DeviceContext *This
) = nullptr;
void STDMETHODCALLTYPE MineDrawAuto(
  ID3D11DeviceContext *This
) {
  getOut() << "DrawAuto" << std::endl;
  RealDrawAuto(This);
}
void (STDMETHODCALLTYPE *RealDrawIndexed)(
  ID3D11DeviceContext *This,
  UINT IndexCount,
  UINT StartIndexLocation,
  INT  BaseVertexLocation
) = nullptr;
void STDMETHODCALLTYPE MineDrawIndexed(
  ID3D11DeviceContext *This,
  UINT IndexCount,
  UINT StartIndexLocation,
  INT  BaseVertexLocation
) {
  getOut() << "DrawIndexed" << std::endl;
  RealDrawIndexed(This, IndexCount, StartIndexLocation, BaseVertexLocation);
}
void (STDMETHODCALLTYPE *RealDrawIndexedInstanced)(
  ID3D11DeviceContext *This,
  UINT IndexCountPerInstance,
  UINT InstanceCount,
  UINT StartIndexLocation,
  INT  BaseVertexLocation,
  UINT StartInstanceLocation
) = nullptr;
void STDMETHODCALLTYPE MineDrawIndexedInstanced(
  ID3D11DeviceContext *This,
  UINT IndexCountPerInstance,
  UINT InstanceCount,
  UINT StartIndexLocation,
  INT  BaseVertexLocation,
  UINT StartInstanceLocation
) {
  getOut() << "DrawIndexedInstanced" << std::endl;
  RealDrawIndexedInstanced(This, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}
void (STDMETHODCALLTYPE *RealDrawIndexedInstancedIndirect)(
  ID3D11DeviceContext *This,
  ID3D11Buffer *pBufferForArgs,
  UINT         AlignedByteOffsetForArgs
) = nullptr;
void STDMETHODCALLTYPE MineDrawIndexedInstancedIndirect(
  ID3D11DeviceContext *This,
  ID3D11Buffer *pBufferForArgs,
  UINT         AlignedByteOffsetForArgs
) {
  getOut() << "DrawIndexedInstancedIndirect" << std::endl;
  RealDrawIndexedInstancedIndirect(This, pBufferForArgs, AlignedByteOffsetForArgs);
}
void (STDMETHODCALLTYPE *RealDrawInstanced)(
  ID3D11DeviceContext *This,
  UINT VertexCountPerInstance,
  UINT InstanceCount,
  UINT StartVertexLocation,
  UINT StartInstanceLocation
) = nullptr;
void STDMETHODCALLTYPE MineDrawInstanced(
  ID3D11DeviceContext *This,
  UINT VertexCountPerInstance,
  UINT InstanceCount,
  UINT StartVertexLocation,
  UINT StartInstanceLocation
) {
  getOut() << "DrawInstanced" << std::endl;
  RealDrawInstanced(This, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}
void (STDMETHODCALLTYPE *RealDrawInstancedIndirect)(
  ID3D11DeviceContext *This,
  ID3D11Buffer *pBufferForArgs,
  UINT         AlignedByteOffsetForArgs
) = nullptr;
void STDMETHODCALLTYPE MineDrawInstancedIndirect(
  ID3D11DeviceContext *This,
  ID3D11Buffer *pBufferForArgs,
  UINT         AlignedByteOffsetForArgs
) {
  getOut() << "DrawInstancedIndirect" << std::endl;
  RealDrawInstancedIndirect(This, pBufferForArgs, AlignedByteOffsetForArgs);
}
void (STDMETHODCALLTYPE *RealClearRenderTargetView)(
  ID3D11DeviceContext *This,
  ID3D11RenderTargetView *pRenderTargetView,
  const FLOAT         ColorRGBA[4]
) = nullptr;
void STDMETHODCALLTYPE MineClearRenderTargetView(
  ID3D11DeviceContext *This,
  ID3D11RenderTargetView *pRenderTargetView,
  const FLOAT         ColorRGBA[4]
) {
  getOut() << "ClearRenderTargetView" << std::endl;
  RealClearRenderTargetView(This, pRenderTargetView, ColorRGBA);
}
void (STDMETHODCALLTYPE *RealClearDepthStencilView)(
  ID3D11DeviceContext *This,
  ID3D11DepthStencilView *pDepthStencilView,
  UINT                   ClearFlags,
  FLOAT                  Depth,
  UINT8                  Stencil
) = nullptr;
void STDMETHODCALLTYPE MineClearDepthStencilView(
  ID3D11DeviceContext *This,
  ID3D11DepthStencilView *pDepthStencilView,
  UINT                   ClearFlags,
  FLOAT                  Depth,
  UINT8                  Stencil
) {
  getOut() << "ClearDepthStencilView" << std::endl;
  RealClearDepthStencilView(This, pDepthStencilView, ClearFlags, Depth, Stencil);
}
void (STDMETHODCALLTYPE *RealClearState)(
  ID3D11DeviceContext *This
) = nullptr;
void STDMETHODCALLTYPE MineClearState(
  ID3D11DeviceContext *This
) {
  getOut() << "ClearState" << std::endl;
  RealClearState(This);
}
void (STDMETHODCALLTYPE *RealClearView)(
  ID3D11DeviceContext1 *This,
  ID3D11View       *pView,
  const FLOAT   Color[4],
  const D3D11_RECT *pRect,
  UINT             NumRects
) = nullptr;
void STDMETHODCALLTYPE MineClearView(
  ID3D11DeviceContext1 *This,
  ID3D11View       *pView,
  const FLOAT   Color[4],
  const D3D11_RECT *pRect,
  UINT             NumRects
) {
  getOut() << "ClearView" << std::endl;
  RealClearView(This, pView, Color, pRect, NumRects);
}

bool hijacked = false;

void hijack(ID3D11DeviceContext *context) {
  if (!hijacked) {
    ID3D11DeviceContext1 *context1;
    HRESULT hr = context->lpVtbl->QueryInterface(context, IID_ID3D11DeviceContext1, (void **)&context1);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "hijack failed to get context 1: " << (void *)hr << std::endl;
    }
    
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
    
    RealOMSetDepthStencilState = context->lpVtbl->OMSetDepthStencilState;
    error = DetourAttach(&(PVOID&)RealOMSetDepthStencilState, MineOMSetDepthStencilState);

    RealDraw = context->lpVtbl->Draw;
    error = DetourAttach(&(PVOID&)RealDraw, MineDraw);
    
    RealDrawAuto = context->lpVtbl->DrawAuto;
    error = DetourAttach(&(PVOID&)RealDrawAuto, MineDrawAuto);
    
    RealDrawIndexed = context->lpVtbl->DrawIndexed;
    error = DetourAttach(&(PVOID&)RealDrawIndexed, MineDrawIndexed);
    
    RealDrawIndexedInstanced = context->lpVtbl->DrawIndexedInstanced;
    error = DetourAttach(&(PVOID&)RealDrawIndexedInstanced, MineDrawIndexedInstanced);
    
    RealDrawIndexedInstancedIndirect = context->lpVtbl->DrawIndexedInstancedIndirect;
    error = DetourAttach(&(PVOID&)RealDrawIndexedInstancedIndirect, MineDrawIndexedInstancedIndirect);
    
    RealDrawInstanced = context->lpVtbl->DrawInstanced;
    error = DetourAttach(&(PVOID&)RealDrawInstanced, MineDrawInstanced);
    
    RealDrawInstancedIndirect = context->lpVtbl->DrawInstancedIndirect;
    error = DetourAttach(&(PVOID&)RealDrawInstancedIndirect, MineDrawInstancedIndirect);
    
    RealClearRenderTargetView = context->lpVtbl->ClearRenderTargetView;
    error = DetourAttach(&(PVOID&)RealClearRenderTargetView, MineClearRenderTargetView);
    
    RealClearDepthStencilView = context->lpVtbl->ClearDepthStencilView;
    error = DetourAttach(&(PVOID&)RealClearDepthStencilView, MineClearDepthStencilView);

    RealClearState = context->lpVtbl->ClearState;
    error = DetourAttach(&(PVOID&)RealClearState, MineClearState);
    
    RealClearView = context1->lpVtbl->ClearView;
    error = DetourAttach(&(PVOID&)RealClearView, MineClearView);
    
    if (error) {
      getOut() << "detour error 4: " << (void *)error << std::endl;
      abort();
    }
    error = DetourTransactionCommit();
    if (error) {
      getOut() << "detour error 5: " << (void *)error << std::endl;
      abort();
    }
    
    context1->lpVtbl->Release(context1);
    
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