#include <map>

#define CINTERFACE
#define D3D11_NO_HELPERS
// #include <windows.h>
#include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "device/vr/openvr/test/hijack.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/detours/detours.h"
#include "third_party/khronos/EGL/egl.h"

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

          /* getOut() << "add tex " <<
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
            std::endl; */

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
    std::endl;
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
  } */
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
void (STDMETHODCALLTYPE *RealResolveSubresource)(
  ID3D11DeviceContext1 *This,
  ID3D11Resource *pDstResource,
  UINT           DstSubresource,
  ID3D11Resource *pSrcResource,
  UINT           SrcSubresource,
  DXGI_FORMAT    Format
) = nullptr;
ID3D11Texture2D *tmpTexture = nullptr;
void STDMETHODCALLTYPE MineResolveSubresource(
  ID3D11DeviceContext1 *This,
  ID3D11Resource *pDstResource,
  UINT           DstSubresource,
  ID3D11Resource *pSrcResource,
  UINT           SrcSubresource,
  DXGI_FORMAT    Format
) {
  getOut() << "ResolveSubresource" << std::endl;
  
  if (tmpTexture) {
    tmpTexture->lpVtbl->Release(tmpTexture);
    tmpTexture = nullptr;
  }
  
  ID3D11Device *device;
  This->lpVtbl->GetDevice(This, &device);
  
  D3D11_TEXTURE2D_DESC desc;
  desc.Width = 256;
  desc.Height = 256;
  desc.MipLevels = desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.Usage = D3D11_USAGE_DYNAMIC;
  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  desc.MiscFlags = 0;

  device->lpVtbl->CreateTexture2D(device, &desc, NULL, &tmpTexture);
  
  RealResolveSubresource(This, pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

bool hijacked = false;
bool hijackedGl = false;

void checkDetourError(const char *label, LONG error) {
  if (error) {
    getOut() << "detour error " << label << " " << (void *)error << std::endl;
    abort();
  }
}

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
    checkDetourError("DetourTransactionBegin", error);

    error = DetourUpdateThread(GetCurrentThread());
    checkDetourError("DetourUpdateThread", error);
    
    RealOMSetRenderTargets = context->lpVtbl->OMSetRenderTargets;
    error = DetourAttach(&(PVOID&)RealOMSetRenderTargets, MineOMSetRenderTargets);
    checkDetourError("RealOMSetRenderTargets", error);

    RealOMSetDepthStencilState = context->lpVtbl->OMSetDepthStencilState;
    error = DetourAttach(&(PVOID&)RealOMSetDepthStencilState, MineOMSetDepthStencilState);
    checkDetourError("RealOMSetDepthStencilState", error);

    RealDraw = context->lpVtbl->Draw;
    error = DetourAttach(&(PVOID&)RealDraw, MineDraw);
    checkDetourError("RealDraw", error);
    
    RealDrawAuto = context->lpVtbl->DrawAuto;
    error = DetourAttach(&(PVOID&)RealDrawAuto, MineDrawAuto);
    checkDetourError("RealDrawAuto", error);
    
    RealDrawIndexed = context->lpVtbl->DrawIndexed;
    error = DetourAttach(&(PVOID&)RealDrawIndexed, MineDrawIndexed);
    checkDetourError("RealDrawIndexed", error);
    
    RealDrawIndexedInstanced = context->lpVtbl->DrawIndexedInstanced;
    error = DetourAttach(&(PVOID&)RealDrawIndexedInstanced, MineDrawIndexedInstanced);
    checkDetourError("RealDrawIndexedInstanced", error);
    
    RealDrawIndexedInstancedIndirect = context->lpVtbl->DrawIndexedInstancedIndirect;
    error = DetourAttach(&(PVOID&)RealDrawIndexedInstancedIndirect, MineDrawIndexedInstancedIndirect);
    checkDetourError("RealDrawIndexedInstancedIndirect", error);
    
    RealDrawInstanced = context->lpVtbl->DrawInstanced;
    error = DetourAttach(&(PVOID&)RealDrawInstanced, MineDrawInstanced);
    checkDetourError("RealDrawInstanced", error);
    
    RealDrawInstancedIndirect = context->lpVtbl->DrawInstancedIndirect;
    error = DetourAttach(&(PVOID&)RealDrawInstancedIndirect, MineDrawInstancedIndirect);
    checkDetourError("RealDrawInstancedIndirect", error);
    
    RealClearRenderTargetView = context->lpVtbl->ClearRenderTargetView;
    error = DetourAttach(&(PVOID&)RealClearRenderTargetView, MineClearRenderTargetView);
    checkDetourError("RealClearRenderTargetView", error);
    
    RealClearDepthStencilView = context->lpVtbl->ClearDepthStencilView;
    error = DetourAttach(&(PVOID&)RealClearDepthStencilView, MineClearDepthStencilView);
    checkDetourError("RealClearDepthStencilView", error);

    RealClearState = context->lpVtbl->ClearState;
    error = DetourAttach(&(PVOID&)RealClearState, MineClearState);
    checkDetourError("RealClearState", error);
    
    RealClearView = context1->lpVtbl->ClearView;
    error = DetourAttach(&(PVOID&)RealClearView, MineClearView);
    checkDetourError("RealClearView", error);
    
    RealResolveSubresource = context1->lpVtbl->ResolveSubresource;
    error = DetourAttach(&(PVOID&)RealResolveSubresource, MineResolveSubresource);
    checkDetourError("RealResolveSubresource", error);

    error = DetourTransactionCommit();
    checkDetourError("DetourTransactionCommit", error);

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

BOOL (STDMETHODCALLTYPE *RealGlGetFramebufferAttachmentParameteriv)(
  GLenum target,
 	GLenum attachment,
 	GLenum pname,
 	GLint *params
) = nullptr;

void (STDMETHODCALLTYPE *RealGlGenFramebuffers)(
  GLsizei n,
 	GLuint * framebuffers
) = nullptr;
void STDMETHODCALLTYPE MineGlGenFramebuffers(
  GLsizei n,
 	GLuint * framebuffers
) {
  RealGlGenFramebuffers(n, framebuffers);
  getOut() << "glGenFramebuffers " << n << " " << framebuffers[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
}
void (STDMETHODCALLTYPE *RealGlBindFramebuffer)(
  GLenum target,
 	GLuint framebuffer
) = nullptr;
void STDMETHODCALLTYPE MineGlBindFramebuffer(
  GLenum target,
 	GLuint framebuffer
) {
  getOut() << "glBindFramebuffer " << target << " " << framebuffer << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlBindFramebuffer(target, framebuffer);
}
void (STDMETHODCALLTYPE *RealGlGenRenderbuffers)(
  GLsizei n,
 	GLuint * renderbuffers
) = nullptr;
void STDMETHODCALLTYPE MineGlGenRenderbuffers(
  GLsizei n,
 	GLuint * renderbuffers
) {
  RealGlGenRenderbuffers(n, renderbuffers);
  getOut() << "glGenRenderbuffers " << n << " " << renderbuffers[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
}
void (STDMETHODCALLTYPE *RealGlBindRenderbuffer)(
  GLenum target,
 	GLuint renderbuffer
) = nullptr;
void STDMETHODCALLTYPE MineGlBindRenderbuffer(
  GLenum target,
 	GLuint renderbuffer
) {
  getOut() << "glBindRenderbuffer " << target << " " << renderbuffer << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlBindRenderbuffer(target, renderbuffer);
}
void (STDMETHODCALLTYPE *RealGlFramebufferTexture2D)(
  GLenum target,
 	GLenum attachment,
 	GLenum textarget,
 	GLuint texture,
 	GLint level
) = nullptr;
void STDMETHODCALLTYPE MineGlFramebufferTexture2D(
  GLenum target,
 	GLenum attachment,
 	GLenum textarget,
 	GLuint texture,
 	GLint level
) {
  getOut() << "glFramebufferTexture2D " << target << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlFramebufferTexture2D(target, attachment, textarget, texture, level);
}
void (STDMETHODCALLTYPE *RealGlFramebufferTexture2DMultisampleEXT)(
  GLenum target,
  GLenum attachment,
  GLenum textarget,
  GLuint texture, 
  GLint level,
  GLsizei samples
) = nullptr;
void STDMETHODCALLTYPE MineGlFramebufferTexture2DMultisampleEXT(
  GLenum target,
  GLenum attachment,
  GLenum textarget,
  GLuint texture, 
  GLint level,
  GLsizei samples
) {
  getOut() << "glFramebufferTexture2DMultisampleEXT " << target << " " << attachment << " " << textarget << " " << texture << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);
}
void (STDMETHODCALLTYPE *RealGlFramebufferRenderbuffer)(
  GLenum target,
 	GLenum attachment,
 	GLenum renderbuffertarget,
 	GLuint renderbuffer
) = nullptr;
void STDMETHODCALLTYPE MineGlFramebufferRenderbuffer(
  GLenum target,
 	GLenum attachment,
 	GLenum renderbuffertarget,
 	GLuint renderbuffer
) {
  getOut() << "glFramebufferRenderbuffer " << target << " " << attachment << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
void (STDMETHODCALLTYPE *RealGlDiscardFramebufferEXT)(
  GLenum target, 
  GLsizei numAttachments, 
  const GLenum *attachments
) = nullptr;
void STDMETHODCALLTYPE MineGlDiscardFramebufferEXT(
  GLenum target, 
  GLsizei numAttachments, 
  const GLenum *attachments
) {
  getOut() << "glDiscardFramebufferEXT" << std::endl;
  RealGlDiscardFramebufferEXT(target, numAttachments, attachments);
}
void (STDMETHODCALLTYPE *RealGlDiscardFramebufferEXTContextANGLE)(
  GLenum target, 
  GLsizei numAttachments, 
  const GLenum *attachments
) = nullptr;
void STDMETHODCALLTYPE MineGlDiscardFramebufferEXTContextANGLE(
  GLenum target, 
  GLsizei numAttachments, 
  const GLenum *attachments
) {
  getOut() << "glDiscardFramebufferEXTContextANGLE" << std::endl;
  RealGlDiscardFramebufferEXTContextANGLE(target, numAttachments, attachments);
}
void (STDMETHODCALLTYPE *RealGlInvalidateFramebuffer)(
  GLenum target,
 	GLsizei numAttachments,
 	const GLenum *attachments
) = nullptr;
void STDMETHODCALLTYPE MineGlInvalidateFramebuffer(
  GLenum target,
 	GLsizei numAttachments,
 	const GLenum *attachments
) {
  getOut() << "glInvalidateFramebuffer" << std::endl;
  RealGlInvalidateFramebuffer(target, numAttachments, attachments);
}
void (STDMETHODCALLTYPE *RealDiscardFramebufferEXT)(
  GLenum target,
  GLsizei count,
  const GLenum* attachments
) = nullptr;
void STDMETHODCALLTYPE MineDiscardFramebufferEXT(
  GLenum target,
  GLsizei count,
  const GLenum* attachments
) {
  getOut() << "DiscardFramebufferEXT" << std::endl;
  RealDiscardFramebufferEXT(target, count, attachments);
}
void (STDMETHODCALLTYPE *RealGlGenTextures)(
  GLsizei n,
 	GLuint * textures
) = nullptr;
void STDMETHODCALLTYPE MineGlGenTextures(
  GLsizei n,
 	GLuint * textures
) {
  RealGlGenTextures(n, textures);
  getOut() << "RealGlGenTextures" << n << " " << textures[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
}
/* void (STDMETHODCALLTYPE *RealGlBindTexture)(
  GLenum target,
 	GLuint texture
) = nullptr;
void STDMETHODCALLTYPE MineGlBindTexture(
  GLenum target,
 	GLuint texture
) {
  getOut() << "RealGlBindTexture " << target << " " << texture << std::endl;
  RealGlBindTexture(target, texture);
} */
void (STDMETHODCALLTYPE *RealGlRequestExtensionANGLE)(
  const GLchar *extension
) = nullptr;
void STDMETHODCALLTYPE MineGlRequestExtensionANGLE(
  const GLchar *extension
) {
  getOut() << "RealGlRequestExtensionANGLE " << extension << std::endl;
  RealGlRequestExtensionANGLE(extension);
}
void (STDMETHODCALLTYPE *RealGlDeleteTextures)(
  GLsizei n,
 	const GLuint * textures
) = nullptr;
void STDMETHODCALLTYPE MineGlDeleteTextures(
  GLsizei n,
 	const GLuint * textures
) {
  RealGlDeleteTextures(n, textures);
  if (n > 0 && textures != NULL) {
    getOut() << "RealGlDeleteTextures " << n << " " << textures[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  } else {
    getOut() << "RealGlDeleteTextures " << n << std::endl;
  }
}
void (STDMETHODCALLTYPE *RealGlFenceSync)(
  GLenum condition,
 	GLbitfield flags
) = nullptr;
void STDMETHODCALLTYPE MineGlFenceSync(
  GLenum condition,
 	GLbitfield flags
) {
  getOut() << "RealGlFenceSync" << std::endl;
  RealGlFenceSync(condition, flags);
}
void (STDMETHODCALLTYPE *RealGlDeleteSync)(
  GLsync sync
) = nullptr;
void STDMETHODCALLTYPE MineGlDeleteSync(
  GLsync sync
) {
  getOut() << "RealGlDeleteSync" << std::endl;
  RealGlDeleteSync(sync);
}
void (STDMETHODCALLTYPE *RealGlWaitSync)(
  GLsync sync,
 	GLbitfield flags,
 	GLuint64 timeout
) = nullptr;
void STDMETHODCALLTYPE MineGlWaitSync(
  GLsync sync,
 	GLbitfield flags,
 	GLuint64 timeout
) {
  getOut() << "RealGlWaitSync" << std::endl;
  RealGlWaitSync(sync, flags, timeout);
}
void (STDMETHODCALLTYPE *RealGlClientWaitSync)(
  GLsync sync,
 	GLbitfield flags,
 	GLuint64 timeout
) = nullptr;
void STDMETHODCALLTYPE MineGlClientWaitSync(
  GLsync sync,
 	GLbitfield flags,
 	GLuint64 timeout
) {
  getOut() << "RealGlClientWaitSync" << std::endl;
  RealGlClientWaitSync(sync, flags, timeout);
}
void (STDMETHODCALLTYPE *RealGlClear)(
  GLbitfield mask
) = nullptr;
void STDMETHODCALLTYPE MineGlClear(
  GLbitfield mask
) {
  getOut() << "RealGlClear " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  GLint type;
  RealGlGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
  GLint rbo;
  RealGlGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &rbo);
  getOut() << "bound rbo " << type << " " << rbo << std::endl;
  RealGlClear(mask);
}
void (STDMETHODCALLTYPE *RealGlClearColor)(
  GLclampf red,
 	GLclampf green,
 	GLclampf blue,
 	GLclampf alpha
) = nullptr;
void STDMETHODCALLTYPE MineGlClearColor(
  GLclampf red,
 	GLclampf green,
 	GLclampf blue,
 	GLclampf alpha
) {
  getOut() << "RealGlClearColor " << red << " " << green << " " << blue << " " << alpha << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlClearColor(red, green, blue, alpha);
}
void (STDMETHODCALLTYPE *RealGlColorMask)(
  GLboolean red,
 	GLboolean green,
 	GLboolean blue,
 	GLboolean alpha
) = nullptr;
void STDMETHODCALLTYPE MineGlColorMask(
  GLboolean red,
 	GLboolean green,
 	GLboolean blue,
 	GLboolean alpha
) {
  getOut() << "RealGlColorMask " << (int)red << " " << (int)green << " " << (int)blue << " " << (int)alpha << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlColorMask(red, green, blue, alpha);
}
EGLBoolean (STDMETHODCALLTYPE *RealEGL_MakeCurrent)(
  EGLDisplay display,
 	EGLSurface draw,
 	EGLSurface read,
 	EGLContext context
) = nullptr;
EGLBoolean STDMETHODCALLTYPE MineEGL_MakeCurrent(
  EGLDisplay display,
 	EGLSurface draw,
 	EGLSurface read,
 	EGLContext context
) {
  getOut() << "RealEGL_MakeCurrent " << (void *)display << " " << (void *)draw << " " << (void *)read << " " << (void *)context << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  return RealEGL_MakeCurrent(display, draw, read, context);
}
BOOL (STDMETHODCALLTYPE *RealWglMakeCurrent)(
  HDC arg1,
  HGLRC arg2
) = nullptr;
BOOL STDMETHODCALLTYPE MineWglMakeCurrent(
  HDC arg1,
  HGLRC arg2
) {
  getOut() << "RealWglMakeCurrent" << (void *)arg1 << " " << (void *)arg2 << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  return RealWglMakeCurrent(arg1, arg2);
}

void hijackGl() {
  if (!hijackedGl) {
    HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
    HMODULE libOpenGl32 = LoadLibraryA("opengl32.dll");

    if (libGlesV2 != NULL && libOpenGl32 != NULL) {
      decltype(RealGlGetFramebufferAttachmentParameteriv) glGetFramebufferAttachmentParameteriv = (decltype(RealGlGetFramebufferAttachmentParameteriv))GetProcAddress(libGlesV2, "glGetFramebufferAttachmentParameteriv");
      RealGlGetFramebufferAttachmentParameteriv = glGetFramebufferAttachmentParameteriv;
      
      decltype(RealGlGenFramebuffers) glGenFramebuffers = (decltype(RealGlGenFramebuffers))GetProcAddress(libGlesV2, "glGenFramebuffers");
      decltype(RealGlBindFramebuffer) glBindFramebuffer = (decltype(RealGlBindFramebuffer))GetProcAddress(libGlesV2, "glBindFramebuffer");
      decltype(RealGlGenRenderbuffers) glGenRenderbuffers = (decltype(RealGlGenRenderbuffers))GetProcAddress(libGlesV2, "glGenRenderbuffers");
      decltype(RealGlBindRenderbuffer) glBindRenderbuffer = (decltype(RealGlBindRenderbuffer))GetProcAddress(libGlesV2, "glBindRenderbuffer");
      decltype(RealGlFramebufferTexture2D) glFramebufferTexture2D = (decltype(RealGlFramebufferTexture2D))GetProcAddress(libGlesV2, "glFramebufferTexture2D");
      decltype(RealGlFramebufferTexture2DMultisampleEXT) glFramebufferTexture2DMultisampleEXT = (decltype(RealGlFramebufferTexture2DMultisampleEXT))GetProcAddress(libGlesV2, "glFramebufferTexture2DMultisampleEXT");
      decltype(RealGlFramebufferRenderbuffer) glFramebufferRenderbuffer = (decltype(RealGlFramebufferRenderbuffer))GetProcAddress(libGlesV2, "glFramebufferRenderbuffer");
      decltype(RealGlDiscardFramebufferEXT) glDiscardFramebufferEXT = (decltype(RealGlDiscardFramebufferEXT))GetProcAddress(libGlesV2, "glDiscardFramebufferEXT");
      decltype(RealGlDiscardFramebufferEXTContextANGLE) glDiscardFramebufferEXTContextANGLE = (decltype(RealGlDiscardFramebufferEXTContextANGLE))GetProcAddress(libGlesV2, "glDiscardFramebufferEXTContextANGLE");
      decltype(RealGlInvalidateFramebuffer) glInvalidateFramebuffer = (decltype(RealGlInvalidateFramebuffer))GetProcAddress(libGlesV2, "glInvalidateFramebuffer");
      decltype(RealDiscardFramebufferEXT) DiscardFramebufferEXT = (decltype(RealDiscardFramebufferEXT))GetProcAddress(libGlesV2, "?DiscardFramebufferEXT@gl@@YAXIHPEBI@Z");
      decltype(RealGlGenTextures) glGenTextures = (decltype(RealGlGenTextures))GetProcAddress(libGlesV2, "glGenTextures");
      // decltype(RealGlBindTexture) glBindTexture = (decltype(RealGlBindTexture))GetProcAddress(libGlesV2, "glBindTexture");
      decltype(RealGlRequestExtensionANGLE) glRequestExtensionANGLE = (decltype(RealGlRequestExtensionANGLE))GetProcAddress(libGlesV2, "glRequestExtensionANGLE");
      decltype(RealGlDeleteTextures) glDeleteTextures = (decltype(RealGlDeleteTextures))GetProcAddress(libGlesV2, "glDeleteTextures");
      decltype(RealGlFenceSync) glFenceSync = (decltype(RealGlFenceSync))GetProcAddress(libGlesV2, "glFenceSync");
      decltype(RealGlDeleteSync) glDeleteSync = (decltype(RealGlDeleteSync))GetProcAddress(libGlesV2, "glDeleteSync");
      decltype(RealGlWaitSync) glWaitSync = (decltype(RealGlWaitSync))GetProcAddress(libGlesV2, "glWaitSync");
      decltype(RealGlClientWaitSync) glClientWaitSync = (decltype(RealGlClientWaitSync))GetProcAddress(libGlesV2, "glClientWaitSync");
      decltype(RealGlClear) glClear = (decltype(RealGlClear))GetProcAddress(libGlesV2, "glClear");
      decltype(RealGlClearColor) glClearColor = (decltype(RealGlClearColor))GetProcAddress(libGlesV2, "glClearColor");
      decltype(RealGlColorMask) glColorMask = (decltype(RealGlColorMask))GetProcAddress(libGlesV2, "glColorMask");
      decltype(RealEGL_MakeCurrent) EGL_MakeCurrent = (decltype(RealEGL_MakeCurrent))GetProcAddress(libGlesV2, "EGL_MakeCurrent");
      decltype(RealWglMakeCurrent) wglMakeCurrent = (decltype(RealWglMakeCurrent))GetProcAddress(libOpenGl32, "wglMakeCurrent");
  
      LONG error = DetourTransactionBegin();
      checkDetourError("DetourTransactionBegin", error);

      error = DetourUpdateThread(GetCurrentThread());
      checkDetourError("DetourUpdateThread", error);
      
      RealGlGenFramebuffers = glGenFramebuffers;
      error = DetourAttach(&(PVOID&)RealGlGenFramebuffers, MineGlGenFramebuffers);
      checkDetourError("RealGlGenFramebuffers", error);
      
      RealGlBindFramebuffer = glBindFramebuffer;
      error = DetourAttach(&(PVOID&)RealGlBindFramebuffer, MineGlBindFramebuffer);
      checkDetourError("RealGlBindFramebuffer", error);

      RealGlGenRenderbuffers = glGenRenderbuffers;
      error = DetourAttach(&(PVOID&)RealGlGenRenderbuffers, MineGlGenRenderbuffers);
      checkDetourError("RealGlGenRenderbuffers", error);
      
      RealGlBindRenderbuffer = glBindRenderbuffer;
      error = DetourAttach(&(PVOID&)RealGlBindRenderbuffer, MineGlBindRenderbuffer);
      checkDetourError("RealGlBindRenderbuffer", error);

      RealGlFramebufferTexture2D = glFramebufferTexture2D;
      error = DetourAttach(&(PVOID&)RealGlFramebufferTexture2D, MineGlFramebufferTexture2D);
      checkDetourError("RealGlFramebufferTexture2D", error);
      
      RealGlFramebufferTexture2DMultisampleEXT = glFramebufferTexture2DMultisampleEXT;
      error = DetourAttach(&(PVOID&)RealGlFramebufferTexture2DMultisampleEXT, MineGlFramebufferTexture2DMultisampleEXT);
      checkDetourError("RealGlFramebufferTexture2DMultisampleEXT", error);
      
      RealGlFramebufferRenderbuffer = glFramebufferRenderbuffer;
      error = DetourAttach(&(PVOID&)RealGlFramebufferRenderbuffer, MineGlFramebufferRenderbuffer);
      checkDetourError("RealGlFramebufferRenderbuffer", error);
      
      RealGlDiscardFramebufferEXT = glDiscardFramebufferEXT;
      error = DetourAttach(&(PVOID&)RealGlDiscardFramebufferEXT, MineGlDiscardFramebufferEXT);
      checkDetourError("RealGlDiscardFramebufferEXT", error);
      
      RealGlDiscardFramebufferEXTContextANGLE = glDiscardFramebufferEXTContextANGLE;
      error = DetourAttach(&(PVOID&)RealGlDiscardFramebufferEXTContextANGLE, MineGlDiscardFramebufferEXTContextANGLE);
      checkDetourError("RealGlDiscardFramebufferEXTContextANGLE", error);

      RealGlInvalidateFramebuffer = glInvalidateFramebuffer;
      error = DetourAttach(&(PVOID&)RealGlInvalidateFramebuffer, MineGlInvalidateFramebuffer);
      checkDetourError("RealGlInvalidateFramebuffer", error);
      
      RealDiscardFramebufferEXT = DiscardFramebufferEXT;
      error = DetourAttach(&(PVOID&)RealDiscardFramebufferEXT, MineDiscardFramebufferEXT);
      checkDetourError("RealDiscardFramebufferEXT", error);
      
      RealGlGenTextures = glGenTextures;
      error = DetourAttach(&(PVOID&)RealGlGenTextures, MineGlGenTextures);
      checkDetourError("RealGlGenTextures", error);
      
      /* RealGlBindTexture = glBindTexture;
      error = DetourAttach(&(PVOID&)RealGlBindTexture, MineGlBindTexture);
      checkDetourError("RealGlBindTexture", error); */

      RealGlDeleteTextures = glDeleteTextures;
      error = DetourAttach(&(PVOID&)RealGlDeleteTextures, MineGlDeleteTextures);
      checkDetourError("RealGlDeleteTextures", error);
      
      RealGlFenceSync = glFenceSync;
      error = DetourAttach(&(PVOID&)RealGlFenceSync, MineGlFenceSync);
      checkDetourError("RealGlFenceSync", error);
      
      RealGlDeleteSync = glDeleteSync;
      error = DetourAttach(&(PVOID&)RealGlDeleteSync, MineGlDeleteSync);
      checkDetourError("RealGlDeleteSync", error);
      
      RealGlWaitSync = glWaitSync;
      error = DetourAttach(&(PVOID&)RealGlWaitSync, MineGlWaitSync);
      checkDetourError("RealGlWaitSync", error);
      
      RealGlClientWaitSync = glClientWaitSync;
      error = DetourAttach(&(PVOID&)RealGlClientWaitSync, MineGlClientWaitSync);
      checkDetourError("RealGlClientWaitSync", error);
      
      RealGlClear = glClear;
      error = DetourAttach(&(PVOID&)RealGlClear, MineGlClear);
      checkDetourError("RealGlClear", error);
      
      RealGlClearColor = glClearColor;
      error = DetourAttach(&(PVOID&)RealGlClearColor, MineGlClearColor);
      checkDetourError("RealGlClearColor", error);
      
      RealGlColorMask = glColorMask;
      error = DetourAttach(&(PVOID&)RealGlColorMask, MineGlColorMask);
      checkDetourError("RealGlColorMask", error);
      
      RealEGL_MakeCurrent = EGL_MakeCurrent;
      error = DetourAttach(&(PVOID&)RealEGL_MakeCurrent, MineEGL_MakeCurrent);
      checkDetourError("RealEGL_MakeCurrent", error);
      
      RealWglMakeCurrent = wglMakeCurrent;
      error = DetourAttach(&(PVOID&)RealWglMakeCurrent, MineWglMakeCurrent);
      checkDetourError("RealWglMakeCurrent", error);

      error = DetourTransactionCommit();
      checkDetourError("DetourTransactionCommit", error);
    } else {
      getOut() << "failed to load gl hijack libs: " << (void *)libGlesV2 << " " << (void *)libOpenGl32 << " " << GetLastError() << std::endl;
    }

    hijackedGl = true;
  }
}