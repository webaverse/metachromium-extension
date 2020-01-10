#define CINTERFACE
#define D3D11_NO_HELPERS

// #include <windows.h>
#include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "device/vr/openvr/test/out.h"
#include "device/vr/detours/detours.h"

/* void (STDMETHODCALLTYPE *RealCopySubresourceRegion)(
  ID3D11DeviceContext4 *This,
  ID3D11Resource  *pDstResource,
  UINT            DstSubresource,
  UINT            DstX,
  UINT            DstY,
  UINT            DstZ,
  ID3D11Resource  *pSrcResource,
  UINT            SrcSubresource,
  const D3D11_BOX *pSrcBox
) = nullptr;
void STDMETHODCALLTYPE MineCopySubresourceRegion(
  ID3D11DeviceContext4 *This,
  ID3D11Resource  *pDstResource,
  UINT            DstSubresource,
  UINT            DstX,
  UINT            DstY,
  UINT            DstZ,
  ID3D11Resource  *pSrcResource,
  UINT            SrcSubresource,
  const D3D11_BOX *pSrcBox
) {
  getOut() << "copy subresource intercept" << std::endl;
  RealCopySubresourceRegion(This, pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
} */
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
  getOut() << "intercept " << NumViews << std::endl;

  if (ppRenderTargetViews) {
    ID3D11RenderTargetView * const pRenderTargetView = *ppRenderTargetViews;
    ID3D11Resource *depthResource;
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
    }
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