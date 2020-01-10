#define CINTERFACE
#define D3D11_NO_HELPERS

// #include <windows.h>
#include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "device/vr/openvr/test/out.h"
#include "device/vr/detours/detours.h"

/* class DID3D11DeviceContext : public ID3D11DeviceContext4 {
public:
  void fakeFn(
    ID3D11Resource  *pDstResource,
    UINT            DstSubresource,
    UINT            DstX,
    UINT            DstY,
    UINT            DstZ,
    ID3D11Resource  *pSrcResource,
    UINT            SrcSubresource,
    const D3D11_BOX *pSrcBox
  );
  static void (ID3D11DeviceContext4::* copySubresourceRegion)(
    ID3D11Resource *,
    UINT,
    UINT,
    UINT,
    UINT,
    ID3D11Resource *,
    UINT,
    const D3D11_BOX *
  );
};
void (ID3D11DeviceContext4::* DID3D11DeviceContext::copySubresourceRegion)(
  ID3D11Resource *,
  UINT,
  UINT,
  UINT,
  UINT,
  ID3D11Resource *,
  UINT,
  const D3D11_BOX *
) = &ID3D11DeviceContext4::CopySubresourceRegion;
void DID3D11DeviceContext::fakeFn(
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
  (this->*copySubresourceRegion)(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}
void (DID3D11DeviceContext::* fakeFn)(
  ID3D11Resource *,
  UINT,
  UINT,
  UINT,
  UINT,
  ID3D11Resource *,
  UINT,
  const D3D11_BOX *
) = &DID3D11DeviceContext::fakeFn; */

void (STDMETHODCALLTYPE *RealCopySubresourceRegion)(
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
  // (this->*copySubresourceRegion)(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

bool hijacked = false;

void hijack(ID3D11DeviceContext4 *context) {
  if (!hijacked) {
    getOut() << "detour 1" << std::endl;
    LONG error = DetourTransactionBegin();
    getOut() << "detour 2 " << error << std::endl;
    error = DetourUpdateThread(GetCurrentThread());
    getOut() << "detour 3 " << error << std::endl;
    // error = DetourAttach(&(PVOID&)DID3D11DeviceContext::copySubresourceRegion, *(PBYTE*)&fakeFn);
    RealCopySubresourceRegion = context->lpVtbl->CopySubresourceRegion;
    error = DetourAttach(&(PVOID&)RealCopySubresourceRegion, MineCopySubresourceRegion);
    getOut() << "detour 4 " << error << std::endl;
    error = DetourTransactionCommit();
    getOut() << "detour 5 " << error << std::endl;
    hijacked = true;
  }
}