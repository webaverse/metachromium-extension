#include <deque>
#include <map>
#include <string>
#include <algorithm>

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

#define EGL_EGLEXT_PROTOTYPES

#include "third_party/khronos/EGL/egl.h"
#include "third_party/khronos/EGL/eglext.h"
#include "third_party/khronos/EGL/eglext_angle.h"

#include "device/vr/openvr/test/glcontext.h"

// externs
extern Hijacker *g_hijacker;
extern uint64_t *pFrameCount;
uint64_t localFrameCount = 0;

// constants
char kHijacker_QueueDepthTex[] = "Hijacker_QueueDepthTex";
char kHijacker_ShiftDepthTex[] = "Hijacker_ShiftDepthTex";
char kHijacker_ClearDepthTex[] = "Hijacker_ClearDepthTex";

const char *depthVsh = R"END(#version 100
precision highp float;

attribute vec2 position;
attribute vec2 uv;
varying vec2 vUv;

void main() {
  vUv = uv;
  gl_Position = vec4(position.xy, 0., 1.);
}
)END";
const char *depthFsh = R"END(#version 100
precision highp float;

varying vec2 vUv;
uniform sampler2D tex;

void main() {
  gl_FragColor = texture2D(tex, vUv);
  // gl_FragColor = vec4(vec3(texture2D(tex, vUv).r), 0.0);
  // gl_FragColor.r += 1.0;
  // gl_FragColor = vec4(0.0);
}
)END";

// dx
// front
ID3D11Texture2D *lastDepthTex = nullptr;
ID3D11Resource *lastDepthTexResource = nullptr;
D3D11_TEXTURE2D_DESC lastDescDepth{};
// ID3D11Texture2D *sbsTex = nullptr;
ID3D11Texture2D *sbsDepthTex = nullptr;
HANDLE sbsDepthTexShHandle = NULL;
bool sbsDepthTexLatched = false;
bool sbsDepthTexDrawn = false;
std::vector<ID3D11Texture2D *> texCache;
uint32_t texCacheSamples = 0;
std::vector<HANDLE> texSharedHandleCache;
std::deque<ProxyTexture> texOrder;
std::deque<HANDLE> eventOrder;
// client
ID3D11Device5 *hijackerDevice = nullptr;
ID3D11DeviceContext4 *hijackerContext = nullptr;
HANDLE hijackerInteropDevice = NULL;

// gl
// front
int glPhase = 0;
GLuint depthResolveTexId = 0;
GLuint depthTexId = 0;
GLuint depthResolveFbo = 0;
GLuint depthShFbo = 0;
ID3D11Texture2D *depthTex = nullptr;
GLuint depthVao = 0;
GLsizei depthSamples = 0;
GLenum depthInternalformat = 0;
GLuint depthProgram = 0;
// client
ID3D11Texture2D *clientDepthTex = nullptr;
HANDLE clientDepthEvent = NULL;
HANDLE clientDepthHandleLatched = NULL;

// dx + gl
// front
uint32_t depthWidth = 0;
uint32_t depthHeight = 0;
size_t fenceValue = 0;
HANDLE frontSharedDepthHandle = NULL;
std::vector<ID3D11Fence *> fenceCache;
std::vector<HANDLE> eventCache;

// void LocalGetDXGIOutputInfo(int32_t *pAdaterIndex);
void ProxyGetDXGIOutputInfo(int32_t *pAdaterIndex);
void ProxyGetRecommendedRenderTargetSize(uint32_t *pWidth, uint32_t *pHeight);

void checkDetourError(const char *label, LONG error) {
  if (error) {
    getOut() << "detour error " << label << " " << (void *)error << std::endl;
    abort();
  }
}

decltype(eglGetCurrentDisplay) *EGL_GetCurrentDisplay = nullptr;
decltype(eglChooseConfig) *EGL_ChooseConfig = nullptr;
decltype(eglCreatePbufferFromClientBuffer) *EGL_CreatePbufferFromClientBuffer = nullptr;
decltype(eglBindTexImage) *EGL_BindTexImage = nullptr;
decltype(eglQueryString) *EGL_QueryString = nullptr;
decltype(eglQueryDisplayAttribEXT) *EGL_QueryDisplayAttribEXT = nullptr;
decltype(eglQueryDeviceAttribEXT) *EGL_QueryDeviceAttribEXT = nullptr;
decltype(eglGetError) *EGL_GetError = nullptr;

bool isEyeDepthTex(const D3D11_TEXTURE2D_DESC &desc) {
  if (!depthWidth) {
    ProxyGetRecommendedRenderTargetSize(&depthWidth, &depthHeight);
  }
  return desc.Width == depthWidth*2 &&
    desc.Height == depthHeight &&
    // desc.Format == DXGI_FORMAT_R24G8_TYPELESS &&
    desc.SampleDesc.Count > 1 &&
    (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE) && (desc.BindFlags & D3D11_BIND_DEPTH_STENCIL);
}
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
  // getOut() << "RealOMSetRenderTargets 1" << std::endl;

  /* if (NumViews > 0 && ppRenderTargetViews && *ppRenderTargetViews && pDepthStencilView) {
    if (!depthWidth || !depthHeight) {
      ProxyGetRecommendedRenderTargetSize(&depthWidth, &depthHeight);
    }
    
    // getOut() << "RealOMSetRenderTargets 2" << std::endl;

    ID3D11Texture2D *depthTex = nullptr;
    ID3D11Resource *depthTexResource = nullptr;
    pDepthStencilView->lpVtbl->GetResource(pDepthStencilView, &depthTexResource);
    HRESULT hr = depthTexResource->lpVtbl->QueryInterface(depthTexResource, IID_ID3D11Texture2D, (void **)&depthTex);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
      abort();
    }

    D3D11_TEXTURE2D_DESC descDepth;
    depthTex->lpVtbl->GetDesc(depthTex, &descDepth);

    if (
      (lastDescDepth.Width == depthWidth && lastDescDepth.Height == depthHeight && lastDescDepth.SampleDesc.Count > 1) &&
      (descDepth.Width != depthWidth || descDepth.Height != depthHeight || descDepth.SampleDesc.Count == 1)
    ) {
      // getOut() << "RealOMSetRenderTargets 8" << std::endl;

      if (texCacheSamples != lastDescDepth.SampleDesc.Count) {
        for (auto iter : texCache) {
          iter->lpVtbl->Release(iter);
        }
        texCache.clear();
        for (auto iter : texSharedHandleCache) {
          CloseHandle(iter);
        }
        texSharedHandleCache.clear();
        for (auto iter : fenceCache) {
          iter->lpVtbl->Release(iter);
        }
        fenceCache.clear();
        for (auto iter : eventCache) {
          CloseHandle(iter);
        }
        eventCache.clear();

        texCacheSamples = lastDescDepth.SampleDesc.Count;
      }

      ID3D11DeviceContext4 *context4;
      hr = This->lpVtbl->QueryInterface(This, IID_ID3D11DeviceContext4, (void **)&context4);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "failed to get hijack context4: " << (void *)hr << std::endl;
        abort();
      }

      if (texCache.size() < texOrder.size() + 1) {
        ID3D11Device *device;
        This->lpVtbl->GetDevice(This, &device);
        
        // getOut() << "RealOMSetRenderTargets 9" << std::endl;
        
        ID3D11Device5 *device5;
        hr = device->lpVtbl->QueryInterface(device, IID_ID3D11Device5, (void **)&device5);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to get hijack device5: " << (void *)hr << std::endl;
          abort();
        }
        
        // getOut() << "RealOMSetRenderTargets 10" << std::endl;

        {
          ID3D11Texture2D *shDepthTex;
          
          // descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
          lastDescDepth.Usage = D3D11_USAGE_DEFAULT;
          lastDescDepth.BindFlags = D3D11_BIND_SHADER_RESOURCE;
          // descDepth.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
          lastDescDepth.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
          // descDepth.SampleDesc.Count = 1;

          // getOut() << "RealOMSetRenderTargets 11" << std::endl;

          hr = device->lpVtbl->CreateTexture2D(
            device,
            &lastDescDepth,
            NULL,
            &shDepthTex
          );
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to create proxy depth texture: " << (void *)hr << std::endl;
            abort();
          }
          
          // getOut() << "RealOMSetRenderTargets 12" << std::endl;

          IDXGIResource1 *shDepthTexResource;
          hr = shDepthTex->lpVtbl->QueryInterface(shDepthTex, IID_IDXGIResource1, (void **)&shDepthTexResource);
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to get hijack shared depth resource: " << (void *)hr << std::endl;
            abort();
          }
          
          // getOut() << "RealOMSetRenderTargets 13" << std::endl;

          HANDLE shDepthTexHandle;
          hr = shDepthTexResource->lpVtbl->GetSharedHandle(shDepthTexResource, &shDepthTexHandle);
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to get hijack shared depth handle: " << (void *)hr << std::endl;
            abort();
          }
          
          // getOut() << "RealOMSetRenderTargets 14 " << (void *)shDepthTexHandle << std::endl;
          
          texCache.push_back(shDepthTex);
          texSharedHandleCache.push_back(shDepthTexHandle);

          // getOut() << "RealOMSetRenderTargets 15" << std::endl;

          // shDepthTexResource->lpVtbl->Release(shDepthTexResource);
          
          // getOut() << "RealOMSetRenderTargets 16" << std::endl;
        }
        // getOut() << "RealOMSetRenderTargets 17" << std::endl;
        {
          ID3D11Fence *depthFence;
          hr = device5->lpVtbl->CreateFence(
            device5,
            0, // value
            // D3D11_FENCE_FLAG_SHARED|D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER, // flags
            // D3D11_FENCE_FLAG_SHARED, // flags
            D3D11_FENCE_FLAG_NONE, // flags
            IID_ID3D11Fence, // interface
            (void **)&depthFence // out
          );
          if (SUCCEEDED(hr)) {
            // getOut() << "created fence " << (void *)fence << std::endl;
            // nothing
          } else {
            getOut() << "failed to create depth fence" << std::endl;
            abort();
          }

          fenceCache.push_back(depthFence);
        }
        // getOut() << "RealOMSetRenderTargets 18" << std::endl;
        {
          HANDLE depthEvent = CreateEventA(
            NULL,
            false,
            false,
            (std::string("Local\\OpenVrDepthFenceEvent") + std::to_string(eventCache.size())).c_str()
          );
          if (!depthEvent) {
            getOut() << "failed to create front depth dx event " << (void *)GetLastError() << std::endl;
            abort();
          }
          eventCache.push_back(depthEvent);
        }
        
        // getOut() << "RealOMSetRenderTargets 19" << std::endl;

        device->lpVtbl->Release(device);
        device5->lpVtbl->Release(device5);
      }

      // getOut() << "RealOMSetRenderTargets 20" << std::endl;

      size_t index = texOrder.size();
      ID3D11Texture2D *&shDepthTex = texCache[index];
      HANDLE &shDepthTexHandle = texSharedHandleCache[index];
      ID3D11Fence *&depthFence = fenceCache[index];
      HANDLE &depthEvent = eventCache[index];

      ID3D11Resource *shDepthTexResource = nullptr;
      hr = shDepthTex->lpVtbl->QueryInterface(shDepthTex, IID_ID3D11Resource, (void **)&shDepthTexResource);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "failed to get hijack shared depth texture resource: " << (void *)hr << std::endl;
        abort();
      }

      // getOut() << "RealOMSetRenderTargets 21 " << (void *)shDepthTexHandle << std::endl;

      This->lpVtbl->CopyResource(
        This,
        shDepthTexResource,
        lastDepthTexResource
      );

      // getOut() << "RealOMSetRenderTargets 22" << std::endl;

      ++fenceValue;
      context4->lpVtbl->Signal(context4, depthFence, fenceValue);
      depthFence->lpVtbl->SetEventOnCompletion(depthFence, fenceValue, depthEvent);

      // getOut() << "RealOMSetRenderTargets 23" << std::endl;

      texOrder.push_back(ProxyTexture{
        shDepthTexHandle,
        index
      });

      // getOut() << "push tex order " << texOrder.size() << " " << (void *)shDepthTexHandle << " " << (void *)depthTex << std::endl;

      shDepthTexResource->lpVtbl->Release(shDepthTexResource);
    }

    if (lastDepthTex) {
      lastDepthTex->lpVtbl->Release(lastDepthTex);
    }
    lastDepthTex = depthTex;
    if (lastDepthTexResource) {
      lastDepthTexResource->lpVtbl->Release(lastDepthTexResource);
    }
    lastDepthTexResource = depthTexResource;
    lastDescDepth = descDepth;
  } */

  if (pDepthStencilView) {
    /* auto pRenderTargetView = ppRenderTargetViews[0];

    ID3D11Texture2D *tex = nullptr;
    ID3D11Resource *texResource = nullptr;
    pRenderTargetView->lpVtbl->GetResource(pRenderTargetView, &texResource);
    HRESULT hr = texResource->lpVtbl->QueryInterface(texResource, IID_ID3D11Texture2D, (void **)&tex);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
      abort();
    }

    D3D11_TEXTURE2D_DESC desc{};
    tex->lpVtbl->GetDesc(tex, &desc); */

    ID3D11Texture2D *depthTex = nullptr;
    ID3D11Resource *depthTexResource = nullptr;
    pDepthStencilView->lpVtbl->GetResource(pDepthStencilView, &depthTexResource);
    HRESULT hr = depthTexResource->lpVtbl->QueryInterface(depthTexResource, IID_ID3D11Texture2D, (void **)&depthTex);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
      abort();
    }

    // D3D11_TEXTURE2D_DESC descDepth;
    // depthTex->lpVtbl->GetDesc(depthTex, &descDepth);

    D3D11_TEXTURE2D_DESC desc;
    depthTex->lpVtbl->GetDesc(depthTex, &desc);

    if (isEyeDepthTex(desc)) {
      if (sbsDepthTex != depthTex) {
        sbsDepthTex = depthTex;
        
        IDXGIResource1 *dxgiResource;
        hr = sbsDepthTex->lpVtbl->QueryInterface(sbsDepthTex, IID_IDXGIResource1, (void **)&dxgiResource);
        if (FAILED(hr)) {
          getOut() << "failed to get sbs depth tex shared resource " << (void *)hr << std::endl;
          abort();
        }

        hr = dxgiResource->lpVtbl->GetSharedHandle(dxgiResource, &sbsDepthTexShHandle);
        if (FAILED(hr)) {
          getOut() << "failed to get sbs depth tex shared handle " << (void *)hr << std::endl;
          abort();
        }
        
        getOut() << "latch depth share handle " << (void *)sbsDepthTexShHandle << std::endl;
        
        dxgiResource->lpVtbl->Release(dxgiResource);
      }
      
      sbsDepthTexLatched = true;
    } else {
      sbsDepthTexLatched = false;
    }
    getOut() << "set depth render target solid " <<
      GetCurrentProcessId() << " " <<
      (void *)depthTex << " " << sbsDepthTexLatched << " " <<
      desc.Width << " " << depthWidth << " " << desc.Height << " " <<
      desc.MipLevels << " " << desc.ArraySize << " " <<
      desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
      desc.Format << " " <<
      desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags << " " <<
      // DXGI_FORMAT_D32_FLOAT << " " <<
      // (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE) << " " << (desc.BindFlags & D3D11_BIND_DEPTH_STENCIL) << 
      std::endl;
    
    depthTex->lpVtbl->Release(depthTex);
    depthTexResource->lpVtbl->Release(depthTexResource);

    /* getOut() << "RealOMSetRenderTargets tex " <<
      (void *)pRenderTargetView << " " <<
      desc.Width << " " << depthWidth*2 << " " << desc.Height << " " <<
      desc.MipLevels << " " << desc.ArraySize << " " <<
      desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
      desc.Format << " " <<
      desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags <<
      std::endl;
    if (
      desc.Width == depthWidth*2 && desc.Height == depthHeight &&
      desc.SampleDesc.Count == 4 &&
      descDepth.Width == depthWidth*2 && descDepth.Height == depthHeight &&
      descDepth.SampleDesc.Count == 4
    ) {
      getOut() << "RealOMSetRenderTargets tex " <<
        (void *)tex << " " <<
        desc.Width << " " << desc.Height << " " <<
        desc.MipLevels << " " << desc.ArraySize << " " <<
        desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
        desc.Format << " " <<
        desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags <<
        std::endl;
      getOut() << "RealOMSetRenderTargets depth " <<
        (void *)depthTex << " " <<
        descDepth.Width << " " << descDepth.Height << " " <<
        descDepth.MipLevels << " " << descDepth.ArraySize << " " <<
        descDepth.SampleDesc.Count << " " << descDepth.SampleDesc.Quality << " " <<
        descDepth.Format << " " <<
        descDepth.Usage << " " << descDepth.BindFlags << " " << descDepth.CPUAccessFlags << " " << descDepth.MiscFlags <<
        std::endl;
    } */
  } else {
    sbsDepthTexLatched = false;
    getOut() << "set depth render target blank" << std::endl;
  }
  
  RealOMSetRenderTargets(This, NumViews, ppRenderTargetViews, pDepthStencilView);
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
void ensureDepthTexDrawn() {
  getOut() << "draw" << std::endl;
  if (sbsDepthTexLatched) {
    // getOut() << "remote queue depth handle " << (void *)sbsDepthTexShHandle << std::endl;
    g_hijacker->fnp.call<
      kHijacker_QueueDepthTex,
      int,
      HANDLE,
      size_t
    >(sbsDepthTexShHandle, 0);
    g_hijacker->fnp.call<
      kHijacker_QueueDepthTex,
      int,
      HANDLE,
      size_t
    >(sbsDepthTexShHandle, 1);
  }
}
template <typename T>
bool shouldDepthTexClear(T *view) {
  uint64_t remoteFrameCount = *pFrameCount;
  if (localFrameCount != remoteFrameCount) {
    localFrameCount = remoteFrameCount;
    return true;
  } else {
    ID3D11Resource *resource;
    view->lpVtbl->GetResource(view, &resource);
    
    ID3D11Texture2D *depthTex;
    resource->lpVtbl->QueryInterface(resource, IID_ID3D11Texture2D, (void **)&depthTex);
    bool result = (sbsDepthTex != depthTex);
    getOut() << "should clear depth tex " << GetCurrentProcessId() << " " << (void *)depthTex << " " << result << std::endl;

    depthTex->lpVtbl->Release(depthTex);
    resource->lpVtbl->Release(resource);
    
    return result;
  }
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
  getOut() << "Draw " << VertexCount << std::endl;
  RealDraw(This, VertexCount, StartVertexLocation);
  ensureDepthTexDrawn();
}
void (STDMETHODCALLTYPE *RealDrawAuto)(
  ID3D11DeviceContext *This
) = nullptr;
void STDMETHODCALLTYPE MineDrawAuto(
  ID3D11DeviceContext *This
) {
  getOut() << "DrawAuto" << std::endl;
  RealDrawAuto(This);
  ensureDepthTexDrawn();
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
  getOut() << "DrawIndexed " << IndexCount << std::endl;
  RealDrawIndexed(This, IndexCount, StartIndexLocation, BaseVertexLocation);
  ensureDepthTexDrawn();
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
  getOut() << "DrawIndexedInstanced " << IndexCountPerInstance << " " << InstanceCount << std::endl;
  RealDrawIndexedInstanced(This, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
  ensureDepthTexDrawn();
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
  ensureDepthTexDrawn();
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
  getOut() << "DrawInstanced " << VertexCountPerInstance << " " << InstanceCount << std::endl;
  RealDrawInstanced(This, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
  ensureDepthTexDrawn();
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
  ensureDepthTexDrawn();
}
HRESULT (STDMETHODCALLTYPE *RealCreateShaderResourceView)(
  ID3D11Device *This,
  ID3D11Resource                        *pResource,
  const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
  ID3D11ShaderResourceView              **ppSRView
) = nullptr;
HRESULT STDMETHODCALLTYPE MineCreateShaderResourceView(
  ID3D11Device *This,
  ID3D11Resource                        *pResource,
  const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
  ID3D11ShaderResourceView              **ppSRView
) {
  TRACE("Hijack", [&]() { getOut() << "CreateShaderResourceView" << std::endl; });
  return RealCreateShaderResourceView(This, pResource, pDesc, ppSRView);
}
HRESULT (STDMETHODCALLTYPE *RealCreateDepthStencilView)(
  ID3D11Device *This,
  ID3D11Resource                      *pResource,
  const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc,
  ID3D11DepthStencilView              **ppDepthStencilView
) = nullptr;
HRESULT STDMETHODCALLTYPE MineCreateDepthStencilView(
  ID3D11Device *This,
  ID3D11Resource                      *pResource,
  const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc,
  ID3D11DepthStencilView              **ppDepthStencilView
) {
  TRACE("Hijack", [&]() { getOut() << "CreateDepthStencilView" << std::endl; });
  
  ID3D11Texture2D *depthTex = nullptr;
  HRESULT hr = pResource->lpVtbl->QueryInterface(pResource, IID_ID3D11Texture2D, (void **)&depthTex);
  if (SUCCEEDED(hr)) {
    // nothing
  } else {
    getOut() << "failed to get hijack depth texture resource: " << (void *)hr << std::endl;
    abort();
  }

  D3D11_TEXTURE2D_DESC descDepth;
  depthTex->lpVtbl->GetDesc(depthTex, &descDepth);
  
  getOut() << "CreateDepthStencilView " << pDesc->Format << " " << descDepth.Format << std::endl;
  
  depthTex->lpVtbl->Release(depthTex);
  
  hr = RealCreateDepthStencilView(This, pResource, pDesc, ppDepthStencilView);
  if (FAILED(hr)) {
    getOut() << "CreateDepthStencilView failed " << pDesc->Format << " " << descDepth.Format << std::endl;
  }
  return hr;
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
  TRACE("Hijack", [&]() { getOut() << "ClearRenderTargetView" << std::endl; });
  RealClearRenderTargetView(This, pRenderTargetView, ColorRGBA);
  ensureDepthTexDrawn();
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
  TRACE("Hijack", [&]() { getOut() << "ClearDepthStencilView" << std::endl; });
  if (shouldDepthTexClear(pDepthStencilView)) {
    RealClearDepthStencilView(This, pDepthStencilView, ClearFlags, Depth, Stencil);
  }
}
void (STDMETHODCALLTYPE *RealClearState)(
  ID3D11DeviceContext *This
) = nullptr;
void STDMETHODCALLTYPE MineClearState(
  ID3D11DeviceContext *This
) {
  TRACE("Hijack", [&]() { getOut() << "ClearState" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "ClearView" << std::endl; });
  if (shouldDepthTexClear(pView)) {
    RealClearView(This, pView, Color, pRect, NumRects);
  }
}
void (STDMETHODCALLTYPE *RealResolveSubresource)(
  ID3D11DeviceContext1 *This,
  ID3D11Resource *pDstResource,
  UINT           DstSubresource,
  ID3D11Resource *pSrcResource,
  UINT           SrcSubresource,
  DXGI_FORMAT    Format
) = nullptr;
void STDMETHODCALLTYPE MineResolveSubresource(
  ID3D11DeviceContext1 *This,
  ID3D11Resource *pDstResource,
  UINT           DstSubresource,
  ID3D11Resource *pSrcResource,
  UINT           SrcSubresource,
  DXGI_FORMAT    Format
) {
  TRACE("Hijack", [&]() { getOut() << "ResolveSubresource" << std::endl; });  
  RealResolveSubresource(This, pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}
HRESULT (STDMETHODCALLTYPE *RealCreateTexture2D)(
  ID3D11Device *This,
  const D3D11_TEXTURE2D_DESC   *pDesc,
  const D3D11_SUBRESOURCE_DATA *pInitialData,
  ID3D11Texture2D              **ppTexture2D
) = nullptr;
HRESULT STDMETHODCALLTYPE MineCreateTexture2D(
  ID3D11Device *This,
  const D3D11_TEXTURE2D_DESC   *pDesc,
  const D3D11_SUBRESOURCE_DATA *pInitialData,
  ID3D11Texture2D              **ppTexture2D
) {
  /* D3D11_TEXTURE2D_DESC desc = *pDesc;
  
  if (!depthWidth || !depthHeight) {
    ProxyGetRecommendedRenderTargetSize(&depthWidth, &depthHeight);
  }
  bool isSbsDepthTex = false;
  if (
    desc.Width == depthWidth*2 && desc.Height == depthHeight &&
    desc.SampleDesc.Count == 4
  ) {
    if (desc.Format == DXGI_FORMAT_R24G8_TYPELESS && (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE) && (desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)) {
      if (!sbsDepthTex) {
        desc.Format = DXGI_FORMAT_R32G8X24_TYPELESS;
        desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
        isSbsDepthTex = true;
        getOut() << "pre create depth tex " << std::endl;
      } else {
        sbsDepthTex->lpVtbl->AddRef(sbsDepthTex);
        *ppTexture2D = sbsDepthTex;
        getOut() << "reuse depth tex " << (void *)sbsDepthTex << std::endl;
      }
    }
  }
  HRESULT hr = RealCreateTexture2D(This, &desc, pInitialData, ppTexture2D);
  
  if (SUCCEEDED(hr)) {
    if (isSbsDepthTex) {
      sbsDepthTex = *ppTexture2D;
      sbsDepthTex->lpVtbl->AddRef(sbsDepthTex);
      getOut() << "create depth tex " << (void *)sbsDepthTex << std::endl;

      IDXGIResource1 *dxgiResource;
      hr = sbsDepthTex->lpVtbl->QueryInterface(sbsDepthTex, IID_IDXGIResource1, (void **)&dxgiResource);
      if (FAILED(hr)) {
        getOut() << "failed to get sbs depth tex shared resource " << (void *)hr << std::endl;
        abort();
      }

      hr = dxgiResource->lpVtbl->GetSharedHandle(dxgiResource, &sbsDepthTexShHandle);
      if (FAILED(hr)) {
        getOut() << "failed to get sbs depth tex shared handle " << (void *)hr << std::endl;
        abort();
      }
      
      dxgiResource->lpVtbl->Release(dxgiResource);
    }
  }
  getOut() << "CreateTexture2D " <<
    (void *)(*ppTexture2D) << " " <<
    desc.Width << " " << desc.Height << " " <<
    desc.MipLevels << " " << pDesc->ArraySize << " " <<
    desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
    desc.Format << " " <<
    desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags << " " <<
    std::endl;
  return hr; */
  if (isEyeDepthTex(*pDesc)) {
    D3D11_TEXTURE2D_DESC desc = *pDesc;
    /* auto oldFormat = desc.Format;
    if (desc.Format == DXGI_FORMAT_R24G8_TYPELESS) {
      desc.Format = DXGI_FORMAT_R32G8X24_TYPELESS;
    } */
    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
    // getOut() << "create eye depth tex " << oldFormat << " " << desc.Format << std::endl;
    auto hr = RealCreateTexture2D(This, &desc, pInitialData, ppTexture2D);
    if (FAILED(hr)) {
      getOut() << "failed to create texture 2d: " << (void *)hr << std::endl;
      
      /* ID3D11InfoQueue *infoQueue;
      HRESULT hr = This->lpVtbl->QueryInterface(This, IID_ID3D11InfoQueue, (void **)&infoQueue);
      if (SUCCEEDED(hr)) {
        infoQueue->lpVtbl->PushEmptyStorageFilter(infoQueue);
      } else {
        getOut() << "info queue query failed" << std::endl;
        // abort();
      }

      UINT64 numStoredMessages = infoQueue->lpVtbl->GetNumStoredMessagesAllowedByRetrievalFilter(infoQueue);
      for (UINT64 i = 0; i < numStoredMessages; i++) {
        size_t messageSize = 0;
        HRESULT hr = infoQueue->lpVtbl->GetMessage(
          infoQueue,
          i,
          nullptr,
          &messageSize
        );
        if (SUCCEEDED(hr)) {
          D3D11_MESSAGE *message = (D3D11_MESSAGE *)malloc(messageSize);
          
          hr = infoQueue->lpVtbl->GetMessage(
            infoQueue,
            i,
            message,
            &messageSize
          );
          if (SUCCEEDED(hr)) {
            // if (message->Severity <= D3D11_MESSAGE_SEVERITY_WARNING) {
              getOut() << "info: " << message->Severity << " " << std::string(message->pDescription, message->DescriptionByteLength) << std::endl;
            // }
          } else {
            getOut() << "failed to get info queue message size: " << (void *)hr << std::endl;
          }
          
          free(message);
        } else {
          getOut() << "failed to get info queue message size: " << (void *)hr << std::endl;
        }
      }
      infoQueue->lpVtbl->ClearStoredMessages(infoQueue); */
      
      abort();
    }
    return hr;
  } else {
    return RealCreateTexture2D(This, pDesc, pInitialData, ppTexture2D);
  }
}

BOOL (STDMETHODCALLTYPE *RealGlGetIntegerv)(
  GLenum pname,
 	GLint * data
) = nullptr;
BOOL (STDMETHODCALLTYPE *RealGlGetFramebufferAttachmentParameteriv)(
  GLenum target,
 	GLenum attachment,
 	GLenum pname,
 	GLint *params
) = nullptr;

void (STDMETHODCALLTYPE *RealGlViewport)(
  GLint x,
 	GLint y,
 	GLsizei width,
 	GLsizei height
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
  TRACE("Hijack", [&]() { getOut() << "glGenFramebuffers " << n << " " << framebuffers[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
}
void (STDMETHODCALLTYPE *RealGlBindFramebuffer)(
  GLenum target,
 	GLuint framebuffer
) = nullptr;
void STDMETHODCALLTYPE MineGlBindFramebuffer(
  GLenum target,
 	GLuint framebuffer
) {
  TRACE("Hijack", [&]() { getOut() << "glBindFramebuffer " << target << " " << framebuffer << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
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
  EGLDisplay display = EGL_GetCurrentDisplay();
  if (display == EGL_NO_DISPLAY) {
    getOut() << "failed to get EGL display" << std::endl;
    abort();
  }
  
  intptr_t egl_device_ptr = 0;
  intptr_t device_ptr = 0;
  getOut() << "hijack dx from gl " << (void *)EGL_QueryDisplayAttribEXT << " " << EGL_QueryDeviceAttribEXT << std::endl;
  EGLBoolean ok = (*((decltype(eglQueryDisplayAttribEXT) *)EGL_QueryDisplayAttribEXT))(display, EGL_DEVICE_EXT, &egl_device_ptr);
  // getOut() << "get device renderbuffers 2 " << (void *)egl_device_ptr << " " << (void *)ok << std::endl;
  ok = EGL_QueryDeviceAttribEXT(reinterpret_cast<EGLDeviceEXT>(egl_device_ptr), EGL_D3D11_DEVICE_ANGLE, &device_ptr);
  // getOut() << "get device renderbuffers 3 " << (void *)device_ptr << " " << (void *)ok << " " << GetLastError() << std::endl;
  ID3D11Device *d3d11_device = reinterpret_cast<ID3D11Device *>(device_ptr);
  ID3D11DeviceContext *context;
  d3d11_device->lpVtbl->GetImmediateContext(d3d11_device, &context);
  // getOut() << "get device renderbuffers 4 " << (void *)context << " " << GetLastError() << std::endl;
  g_hijacker->hijackDx(context);
  // getOut() << "get device renderbuffers 5" << std::endl;
  
  RealGlGenRenderbuffers(n, renderbuffers);
  TRACE("Hijack", [&]() { getOut() << "glGenRenderbuffers " << n << " " << renderbuffers[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
}
void (STDMETHODCALLTYPE *RealGlBindRenderbuffer)(
  GLenum target,
 	GLuint renderbuffer
) = nullptr;
void STDMETHODCALLTYPE MineGlBindRenderbuffer(
  GLenum target,
 	GLuint renderbuffer
) {
  TRACE("Hijack", [&]() { getOut() << "glBindRenderbuffer " << target << " " << renderbuffer << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "glFramebufferTexture2D " << target << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
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
  glPhase = 1;
  TRACE("Hijack", [&]() { getOut() << "glFramebufferTexture2DMultisampleEXT " << target << " " << attachment << " " << textarget << " " << texture << " " << level << " " << samples << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "glFramebufferRenderbuffer " << target << " " << attachment << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
  RealGlFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
void (STDMETHODCALLTYPE *RealGlRenderbufferStorage)(
  GLenum target,
 	GLenum internalformat,
 	GLsizei width,
 	GLsizei height
) = nullptr;
void (STDMETHODCALLTYPE *RealGlRenderbufferStorageMultisampleEXT)(
  GLenum target,
  GLsizei samples,
  GLenum internalformat,
  GLsizei width,
  GLsizei height
) = nullptr;
void STDMETHODCALLTYPE MineGlRenderbufferStorageMultisampleEXT(
  GLenum target,
  GLsizei samples,
  GLenum internalformat,
  GLsizei width,
  GLsizei height
) {
  /* depthSamples = samples;
  depthInternalformat = internalformat;
  depthWidth = width;
  depthHeight = height; */
  TRACE("Hijack", [&]() { getOut() << "glRenderbufferStorageMultisampleEXT " << target << " " << samples << " " << internalformat << " " << width << " " << height << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
  // RealGlRenderbufferStorage(target, internalformat, width, height);
  RealGlRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
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
  TRACE("Hijack", [&]() { getOut() << "glDiscardFramebufferEXT" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "glDiscardFramebufferEXTContextANGLE" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "glInvalidateFramebuffer" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "DiscardFramebufferEXT" << std::endl; });
  RealDiscardFramebufferEXT(target, count, attachments);
}
void (STDMETHODCALLTYPE *RealGlGenTextures)(
  GLsizei n,
 	GLuint * textures
) = nullptr;
/* void STDMETHODCALLTYPE MineGlGenTextures(
  GLsizei n,
 	GLuint * textures
) {
  RealGlGenTextures(n, textures);
  getOut() << "RealGlGenTextures" << n << " " << textures[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
} */
void (STDMETHODCALLTYPE *RealGlTexImage2D)(
  GLenum target,
 	GLint level,
 	GLint internalformat,
 	GLsizei width,
 	GLsizei height,
 	GLint border,
 	GLenum format,
 	GLenum type,
 	const void * data
) = nullptr;
void (STDMETHODCALLTYPE *RealGlTexParameteri)(
  GLenum target,
 	GLenum pname,
 	GLint param
) = nullptr;
void (STDMETHODCALLTYPE *RealGlBindTexture)(
  GLenum target,
 	GLuint texture
) = nullptr;
/* void STDMETHODCALLTYPE MineGlBindTexture(
  GLenum target,
 	GLuint texture
) {
  getOut() << "RealGlBindTexture " << target << " " << texture << std::endl;
  RealGlBindTexture(target, texture);
} */
void (STDMETHODCALLTYPE *RealGlReadPixels)(
  GLint x,
 	GLint y,
 	GLsizei width,
 	GLsizei height,
 	GLenum format,
 	GLenum type,
 	void * data
) = nullptr;
void (STDMETHODCALLTYPE *RealGlTexStorage2DMultisample)(
  GLenum target,
 	GLsizei samples,
 	GLenum internalformat,
 	GLsizei width,
 	GLsizei height,
 	GLboolean fixedsamplelocations
) = nullptr;
GLenum (STDMETHODCALLTYPE *RealGlGetError)(
) = nullptr;
void (STDMETHODCALLTYPE *RealGlRequestExtensionANGLE)(
  const GLchar *extension
) = nullptr;
void STDMETHODCALLTYPE MineGlRequestExtensionANGLE(
  const GLchar *extension
) {
  TRACE("Hijack", [&]() { getOut() << "RealGlRequestExtensionANGLE " << extension << std::endl; });
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
    TRACE("Hijack", [&]() { getOut() << "RealGlDeleteTextures " << n << " " << textures[0] << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
  } else {
    TRACE("Hijack", [&]() { getOut() << "RealGlDeleteTextures " << n << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "RealGlFenceSync" << std::endl; });
  RealGlFenceSync(condition, flags);
}
void (STDMETHODCALLTYPE *RealGlDeleteSync)(
  GLsync sync
) = nullptr;
void STDMETHODCALLTYPE MineGlDeleteSync(
  GLsync sync
) {
  TRACE("Hijack", [&]() { getOut() << "RealGlDeleteSync" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "RealGlWaitSync" << std::endl; });
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
  TRACE("Hijack", [&]() { getOut() << "RealGlClientWaitSync" << std::endl; });
  RealGlClientWaitSync(sync, flags, timeout);
}
GLenum (STDMETHODCALLTYPE *RealGlDrawElements)(
  GLenum mode,
 	GLsizei count,
 	GLenum type,
 	const void * indices
) = nullptr;
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
  if (glPhase == 2 && red == 0 && blue == 0 && green == 0 && alpha == 0) {
    glPhase = 3;
  } else {
    glPhase = 0;
  }
  TRACE("Hijack", [&]() { getOut() << "RealGlClearColor " << red << " " << green << " " << blue << " " << alpha << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
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
  if (glPhase == 1 && red == 1 && blue == 1 && green == 1 && alpha == 1) {
    glPhase = 2;
  } else {
    glPhase = 0;
  }
  TRACE("Hijack", [&]() { getOut() << "RealGlColorMask " << (int)red << " " << (int)green << " " << (int)blue << " " << (int)alpha << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl; });
  RealGlColorMask(red, green, blue, alpha);
}
void (STDMETHODCALLTYPE *RealGlFlush)(
) = nullptr;
void handleGlClearHack() {
  if (glPhase == 3) {
    if (!glActiveTexture) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glActiveTexture = (decltype(glActiveTexture))GetProcAddress(libGlesV2, "glActiveTexture");
    }
    if (!glTexStorage2DMultisample) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glTexStorage2DMultisample = (decltype(glTexStorage2DMultisample))GetProcAddress(libGlesV2, "glTexStorage2DMultisample");
    }
    if (!glFramebufferTexture2DMultisampleEXT) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glFramebufferTexture2DMultisampleEXT = (decltype(glFramebufferTexture2DMultisampleEXT))GetProcAddress(libGlesV2, "glFramebufferTexture2DMultisampleEXT");
    }
    if (!glGenFramebuffers) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGenFramebuffers = (decltype(glGenFramebuffers))GetProcAddress(libGlesV2, "glGenFramebuffers");
    }
    if (!glBindFramebuffer) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBindFramebuffer = (decltype(glBindFramebuffer))GetProcAddress(libGlesV2, "glBindFramebuffer");
    }
    if (!glBlitFramebuffer) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBlitFramebuffer = (decltype(glBlitFramebuffer))GetProcAddress(libGlesV2, "glBlitFramebuffer");
    }
    if (!glBlitFramebufferANGLE) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBlitFramebufferANGLE = (decltype(glBlitFramebuffer))GetProcAddress(libGlesV2, "glBlitFramebufferANGLE");
    }
    if (!glGenVertexArrays) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGenVertexArrays = (decltype(glGenVertexArrays))GetProcAddress(libGlesV2, "glGenVertexArraysOES");
    }
    if (!glBindVertexArray) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBindVertexArray = (decltype(glBindVertexArray))GetProcAddress(libGlesV2, "glBindVertexArrayOES");
    }
    if (!glCreateShader) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glCreateShader = (decltype(glCreateShader))GetProcAddress(libGlesV2, "glCreateShader");
    }
    if (!glShaderSource) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glShaderSource = (decltype(glShaderSource))GetProcAddress(libGlesV2, "glShaderSource");
    }
    if (!glCompileShader) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glCompileShader = (decltype(glCompileShader))GetProcAddress(libGlesV2, "glCompileShader");
    }
    if (!glGetShaderiv) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGetShaderiv = (decltype(glGetShaderiv))GetProcAddress(libGlesV2, "glGetShaderiv");
    }
    if (!glGetShaderInfoLog) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGetShaderInfoLog = (decltype(glGetShaderInfoLog))GetProcAddress(libGlesV2, "glGetShaderInfoLog");
    }
    if (!glCreateProgram) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glCreateProgram = (decltype(glCreateProgram))GetProcAddress(libGlesV2, "glCreateProgram");
    }
    if (!glAttachShader) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glAttachShader = (decltype(glAttachShader))GetProcAddress(libGlesV2, "glAttachShader");
    }
    if (!glLinkProgram) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glLinkProgram = (decltype(glLinkProgram))GetProcAddress(libGlesV2, "glLinkProgram");
    }
    if (!glGetProgramiv) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGetProgramiv = (decltype(glGetProgramiv))GetProcAddress(libGlesV2, "glGetProgramiv");
    }
    if (!glGetAttribLocation) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGetAttribLocation = (decltype(glGetAttribLocation))GetProcAddress(libGlesV2, "glGetAttribLocation");
    }
    if (!glGetUniformLocation) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGetUniformLocation = (decltype(glGetUniformLocation))GetProcAddress(libGlesV2, "glGetUniformLocation");
    }
    if (!glDeleteShader) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glDeleteShader = (decltype(glDeleteShader))GetProcAddress(libGlesV2, "glDeleteShader");
    }
    if (!glUseProgram) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glUseProgram = (decltype(glUseProgram))GetProcAddress(libGlesV2, "glUseProgram");
    }
    if (!glGenBuffers) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glGenBuffers = (decltype(glGenBuffers))GetProcAddress(libGlesV2, "glGenBuffers");
    }
    if (!glBindBuffer) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBindBuffer = (decltype(glBindBuffer))GetProcAddress(libGlesV2, "glBindBuffer");
    }
    if (!glBufferData) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glBufferData = (decltype(glBufferData))GetProcAddress(libGlesV2, "glBufferData");
    }
    if (!glEnableVertexAttribArray) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glEnableVertexAttribArray = (decltype(glEnableVertexAttribArray))GetProcAddress(libGlesV2, "glEnableVertexAttribArray");
    }
    if (!glVertexAttribPointer) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glVertexAttribPointer = (decltype(glVertexAttribPointer))GetProcAddress(libGlesV2, "glVertexAttribPointer");
    }
    if (!glUniform1i) {
      HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
      glUniform1i = (decltype(glUniform1i))GetProcAddress(libGlesV2, "glUniform1i");
    }
    
    GLint oldActiveTexture;
    RealGlGetIntegerv(GL_ACTIVE_TEXTURE, &oldActiveTexture);
    glActiveTexture(GL_TEXTURE0);
    GLint oldTexture2d;
    RealGlGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture2d);
    GLint oldFbo;
    RealGlGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFbo);
    GLint oldReadFbo;
    RealGlGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &oldReadFbo);
    GLint oldDrawFbo;
    RealGlGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &oldDrawFbo);
    GLint oldProgram;
    RealGlGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
    GLint oldVao;
    RealGlGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVao);
    GLint oldArrayBuffer;
    RealGlGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldArrayBuffer);
    GLint oldViewport[4];
    RealGlGetIntegerv(GL_VIEWPORT, oldViewport);

    // getOut() << "get old X " << oldTex << " " << oldReadFbo << " " << oldDrawFbo << " " << oldProgram << " " << oldVao << " " << oldArrayBuffer << std::endl;

    if (!depthTexId) {
      // Hijacker::ensureClientDevice();

      EGLDisplay display = EGL_GetCurrentDisplay();
      if (display == EGL_NO_DISPLAY) {
        getOut() << "failed to get EGL display" << std::endl;
        abort();
      }

      HRESULT hr;
      {
        intptr_t egl_device_ptr = 0;
        intptr_t device_ptr = 0;
        getOut() << "get device 1 " << (void *)EGL_QueryDisplayAttribEXT << " " << EGL_QueryDeviceAttribEXT << std::endl;
        EGLBoolean ok = (*((decltype(eglQueryDisplayAttribEXT) *)EGL_QueryDisplayAttribEXT))(display, EGL_DEVICE_EXT, &egl_device_ptr);
        getOut() << "get device 2 " << (void *)egl_device_ptr << " " << (void *)ok << std::endl;
        ok = EGL_QueryDeviceAttribEXT(reinterpret_cast<EGLDeviceEXT>(egl_device_ptr), EGL_D3D11_DEVICE_ANGLE, &device_ptr);
        getOut() << "get device 3 " << (void *)device_ptr << " " << (void *)ok << " " << GetLastError() << std::endl;
        ID3D11Device *d3d11_device = reinterpret_cast<ID3D11Device *>(device_ptr);

        hr = d3d11_device->lpVtbl->QueryInterface(d3d11_device, IID_ID3D11Device5, (void **)&hijackerDevice);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "device query failed" << std::endl;
          abort();
        }
        
        /* wglDXOpenDeviceNV = (decltype(wglDXOpenDeviceNV))wglGetProcAddress("wglDXOpenDeviceNV");
        getOut() << "ensure client device 4 " << (void *)wglDXOpenDeviceNV << std::endl;

        HANDLE hInteropDevice = wglDXOpenDeviceNV(hijackerDevice);

        getOut() << "ensure client device 5 " << (void *)hInteropDevice << " " << GetLastError() << std::endl; */

        ID3D11DeviceContext3 *context3;
        hijackerDevice->lpVtbl->GetImmediateContext3(hijackerDevice, &context3);
        hr = context3->lpVtbl->QueryInterface(context3, IID_ID3D11DeviceContext4, (void **)&hijackerContext);
        getOut() << "ensure client device 6" << std::endl;
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "context query failed" << std::endl;
          abort();
        }
        context3->lpVtbl->Release(context3);
      }

      GLuint textures[2];
      RealGlGenTextures(2, textures);
      depthResolveTexId = textures[0];
      depthTexId = textures[1];
      GLuint fbos[2];
      RealGlGenFramebuffers(2, fbos);
      depthResolveFbo = fbos[0];
      depthShFbo = fbos[1];

      {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = depthWidth;
        desc.Height = depthHeight;
        desc.MipLevels = desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        // desc.CPUAccessFlags = 0;
        desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        hr = hijackerDevice->lpVtbl->CreateTexture2D(hijackerDevice, &desc, NULL, &depthTex);
        if (FAILED(hr)) {
          getOut() << "failed to create gl depth tex shared " << (void *)hr << std::endl;
          abort();
        }

        IDXGIResource1 *dxgiResource;
        hr = depthTex->lpVtbl->QueryInterface(depthTex, IID_IDXGIResource1, (void **)&dxgiResource);
        if (FAILED(hr)) {
          getOut() << "failed to get gl depth tex shared resource " << (void *)hr << std::endl;
          abort();
        }

        hr = dxgiResource->lpVtbl->GetSharedHandle(dxgiResource, &frontSharedDepthHandle);
        if (FAILED(hr)) {
          getOut() << "failed to get gl depth tex shared handle " << (void *)hr << std::endl;
          abort();
        }

        EGLConfig config;
        EGLint numConfigs = 0;
        EGLint attribList[] = {
          EGL_RED_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_BLUE_SIZE, 8,
          EGL_ALPHA_SIZE, 8,
          // EGL_BUFFER_SIZE, 8,
          EGL_DEPTH_SIZE, 0,
          EGL_STENCIL_SIZE, 0,
          // EGL_SAMPLES, 1,
          EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
          EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
          EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
          EGL_NONE
        };
        EGLBoolean ok = EGL_ChooseConfig(
          display,
          attribList,
          &config,
          1,
          &numConfigs
        );
        if (numConfigs == 0) {
          getOut() << "failed to get EGL config" << std::endl;
          abort();
        }

        EGLint pBufferAttributes[] = {
          EGL_WIDTH, desc.Width,
          EGL_HEIGHT, desc.Height,
          // EGL_FLEXIBLE_SURFACE_COMPATIBILITY_SUPPORTED_ANGLE, EGL_TRUE,
          EGL_TEXTURE_TARGET, EGL_TEXTURE_2D,
          EGL_TEXTURE_FORMAT, EGL_TEXTURE_RGBA,
          EGL_NONE
        };
        {
          auto error = EGL_GetError();
          if (error != EGL_SUCCESS) getOut() << "egl pre error " << (void *)error << std::endl;
        }
        EGLSurface surface = EGL_CreatePbufferFromClientBuffer(display, EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE, (EGLClientBuffer)frontSharedDepthHandle, config, pBufferAttributes);
        if (surface == EGL_NO_SURFACE) {
          getOut() << "failed to get egl surface " << (void *)surface << " " << (void *)EGL_GetError() << std::endl;
          abort();
        }

        RealGlBindTexture(GL_TEXTURE_2D, depthTexId);
        EGL_BindTexImage(display, surface, EGL_BACK_BUFFER);
        {
          auto error = EGL_GetError();
          if (error != EGL_SUCCESS) getOut() << "egl bind tex error " << (void *)error << std::endl;
        }
        
        getOut() << "got texture" << std::endl;
      }
      {
        RealGlBindFramebuffer(GL_FRAMEBUFFER, depthResolveFbo);
        RealGlBindTexture(GL_TEXTURE_2D, depthResolveTexId);
        /* std::vector<uint32_t> data(depthWidth * depthHeight);
        std::fill(data.begin(), data.end(), 0xFFFFFFFF); */
        RealGlTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, depthWidth, depthHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
        // RealGlTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, depthWidth, depthHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        RealGlFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthResolveTexId, 0);

        RealGlBindFramebuffer(GL_FRAMEBUFFER, depthShFbo);
        RealGlBindTexture(GL_TEXTURE_2D, depthTexId);
        // RealGlTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, depthWidth, depthHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        RealGlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        RealGlFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthTexId, 0);
      }
      {
        glGenVertexArrays(1, &depthVao);
        glBindVertexArray(depthVao);
        
        // getOut() << "generating depth 5 3 " << (void *)glCreateShader << " " << (void *)glShaderSource << " " << (void *)glCompileShader << " " << (void *)glGetShaderiv << " " << (void *)RealGlGetError() << std::endl;

        // vertex shader
        GLuint composeVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(composeVertex, 1, &depthVsh, NULL);
        glCompileShader(composeVertex);
        GLint success;
        glGetShaderiv(composeVertex, GL_COMPILE_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(composeVertex, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "compose vertex shader compilation failed:\n" << infoLog << std::endl;
          abort();
        };
        
        // getOut() << "generating depth 5 4 " << (void *)RealGlGetError() << std::endl;

        // fragment shader
        GLuint composeFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(composeFragment, 1, &depthFsh, NULL);
        glCompileShader(composeFragment);
        glGetShaderiv(composeFragment, GL_COMPILE_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(composeFragment, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "compose fragment shader compilation failed:\n" << infoLog << std::endl;
          abort();
        };
        
        // getOut() << "generating depth 5 5 " << (void *)glCreateProgram << " " << (void *)glAttachShader << " " << (void *)glLinkProgram << " " << (void *)glGetProgramiv << " " << (void *)RealGlGetError() << std::endl;

        // shader program
        depthProgram = glCreateProgram();
        glAttachShader(depthProgram, composeVertex);
        glAttachShader(depthProgram, composeFragment);
        glLinkProgram(depthProgram);
        glGetProgramiv(depthProgram, GL_LINK_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(depthProgram, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "blit program linking failed\n" << infoLog << std::endl;
          abort();
        }

        // getOut() << "generating depth 5 6 " << (void *)RealGlGetError() << std::endl;

        GLuint positionLocation = glGetAttribLocation(depthProgram, "position");
        if (positionLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'position'" << std::endl;
          abort();
        }
        getOut() << "generating depth 5 7 " << (void *)RealGlGetError() << std::endl;
        GLuint uvLocation = glGetAttribLocation(depthProgram, "uv");
        if (uvLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'uv'" << std::endl;
          abort();
        }

        // getOut() << "generating depth 5 8 " << (void *)RealGlGetError() << std::endl;

        GLuint texLocation = glGetUniformLocation(depthProgram, "tex");
        // getOut() << "get location 1  " << texString << " " << texLocation << std::endl;
        if (texLocation != -1) {
          // 
        } else {
          getOut() << "blit program failed to get uniform location for 'tex'" << std::endl;
          // abort();
        }
        
        // getOut() << "generating depth 5 9 " << (void *)RealGlGetError() << std::endl;

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(composeVertex);
        glDeleteShader(composeFragment);

        // getOut() << "generating depth 5 10 " << (void *)RealGlGetError() << std::endl;

        glUseProgram(depthProgram);
        
        // getOut() << "generating depth 11 " << (void *)RealGlGetError() << std::endl;

        GLuint positionBuffer;
        glGenBuffers(1, &positionBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
        getOut() << "generating depth 5 12 " << (void *)RealGlGetError() << std::endl;
        static const float positions[] = {
          -1.0f, 1.0f,
          1.0f, 1.0f,
          -1.0f, -1.0f,
          1.0f, -1.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        // getOut() << "generating depth 5 13 " << (void *)RealGlGetError() << std::endl;
        glEnableVertexAttribArray(positionLocation);
        // getOut() << "generating depth 5 14 " << (void *)RealGlGetError() << std::endl;
        glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, 0);

        // getOut() << "init program 8" << std::endl;

        GLuint uvBuffer;
        glGenBuffers(1, &uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        static const float uvs[] = {
          0.0f, 0.0f,
          1.0f, 0.0f,
          0.0f, 1.0f,
          1.0f, 1.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
        glEnableVertexAttribArray(uvLocation);
        glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, 0, 0);

        // getOut() << "generating depth 5 15 " << (void *)RealGlGetError() << std::endl;

        GLuint indexBuffer;
        glGenBuffers(1, &indexBuffer);
        static const uint16_t indices[] = {0, 2, 1, 2, 3, 1};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        if (texLocation != -1) {
          glUniform1i(texLocation, 0);
        }
        
        // getOut() << "generating depth 5 16 " << (void *)RealGlGetError() << std::endl;
      }
      {
        for (size_t i = 0; i < 2; i++) {
          ID3D11Fence *fence;
          HRESULT hr = hijackerDevice->lpVtbl->CreateFence(
            hijackerDevice,
            0, // value
            // D3D11_FENCE_FLAG_SHARED|D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER, // flags
            // D3D11_FENCE_FLAG_SHARED, // flags
            D3D11_FENCE_FLAG_NONE, // flags
            IID_ID3D11Fence, // interface
            (void **)&fence // out
          );
          if (SUCCEEDED(hr)) {
            // getOut() << "created fence " << (void *)fence << std::endl;
            // nothing
          } else {
            getOut() << "failed to create depth fence" << std::endl;
            abort();
          }
          fenceCache.push_back(fence);
 
          HANDLE depthEvent = CreateEventA(
            NULL,
            false,
            false,
            (std::string("Local\\OpenVrDepthFenceEvent") + std::to_string(i)).c_str()
          );
          if (!depthEvent) {
            getOut() << "failed to create front depth gl event " << (void *)GetLastError() << std::endl;
            abort();
          }
          eventCache.push_back(depthEvent);
        }
      }
      
      RealGlBindFramebuffer(GL_FRAMEBUFFER, oldFbo);
    }
    
    // getOut() << "generating depth 6 1 " << (void *)RealGlGetError() << std::endl;

    RealGlBindFramebuffer(GL_DRAW_FRAMEBUFFER, depthResolveFbo);
    // getOut() << "generating depth 6 2 " << (void *)RealGlGetError() << std::endl;
    glBlitFramebufferANGLE(
      0, 0,
      depthWidth, depthHeight,
      0, 0,
      depthWidth, depthHeight,
      GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
      GL_NEAREST
    );
    
    // getOut() << "generating depth 7 " << (void *)RealGlGetError() << std::endl;

    RealGlBindFramebuffer(GL_DRAW_FRAMEBUFFER, depthShFbo);
    glBindVertexArray(depthVao);
    glUseProgram(depthProgram);
    glActiveTexture(GL_TEXTURE0);
    RealGlBindTexture(GL_TEXTURE_2D, depthResolveTexId);
    RealGlViewport(0, 0, depthWidth, depthHeight);
    /* RealGlClearColor(0, 0, 0, 0);
    RealGlColorMask(true, true, true, true);
    RealGlClear(GL_COLOR_BUFFER_BIT); */
    RealGlDrawElements(
      GL_TRIANGLES,
      6,
      GL_UNSIGNED_SHORT,
      (void *)0
    );

    // getOut() << "generating depth 8 " << (void *)RealGlGetError() << std::endl;
    
    /* RealGlBindFramebuffer(GL_READ_FRAMEBUFFER, depthShFbo);
    std::vector<unsigned char> data(depthWidth * depthHeight * 4);
    // std::fill(data.begin(), data.end(), 2);
    RealGlReadPixels(0, 0, depthWidth, depthHeight, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    size_t count = 0;
    for (size_t i = 0; i < data.size(); i += 4) {
      if (data[i] == 234) {
        count += data[i];
      }
    }
    getOut() << "get real read pixels " << count << std::endl; */
    
    // RealGlFlush();

    RealGlBindTexture(GL_TEXTURE_2D, oldTexture2d);
    glActiveTexture(oldActiveTexture);
    RealGlBindFramebuffer(GL_FRAMEBUFFER, oldFbo);
    RealGlBindFramebuffer(GL_READ_FRAMEBUFFER, oldReadFbo);
    RealGlBindFramebuffer(GL_DRAW_FRAMEBUFFER, oldDrawFbo);
    glUseProgram(oldProgram);
    glBindVertexArray(oldVao);
    glBindBuffer(GL_ARRAY_BUFFER, oldArrayBuffer);
    RealGlViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
    
    // getOut() << "generating depth 10 " << (void *)RealGlGetError() << std::endl;

    /* GLint type;
    RealGlGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
    GLint rbo;
    RealGlGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &rbo);
    getOut() << "blit rbo " << type << " " << rbo << " " << oldDrawFbo << std::endl; */

    for (size_t i = 0; i < 2; i++) {
      ID3D11Fence *&fence = fenceCache[i];
      HANDLE &depthEvent = eventCache[i];
      
      ++fenceValue;
      hijackerContext->lpVtbl->Signal(hijackerContext, fence, fenceValue);
      fence->lpVtbl->SetEventOnCompletion(fence, fenceValue, depthEvent);
      
      g_hijacker->fnp.call<
        kHijacker_QueueDepthTex,
        int,
        HANDLE,
        size_t
      >(frontSharedDepthHandle, i);
    }

    glPhase = 0;
  } else {
    glPhase = 0;
  }
}
void (STDMETHODCALLTYPE *RealGlClear)(
  GLbitfield mask
) = nullptr;
void STDMETHODCALLTYPE MineGlClear(
  GLbitfield mask
) {
  // handleGlClearHack();

  // getOut() << "RealGlClear " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  RealGlClear(mask);
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
  glPhase = 0;
  // getOut() << "RealEGL_MakeCurrent " << (void *)display << " " << (void *)draw << " " << (void *)read << " " << (void *)context << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  return RealEGL_MakeCurrent(display, draw, read, context);
}
/* BOOL (STDMETHODCALLTYPE *RealWglMakeCurrent)(
  HDC arg1,
  HGLRC arg2
) = nullptr;
BOOL STDMETHODCALLTYPE MineWglMakeCurrent(
  HDC arg1,
  HGLRC arg2
) {
  getOut() << "RealWglMakeCurrent" << (void *)arg1 << " " << (void *)arg2 << " " << GetCurrentProcessId() << ":" << GetCurrentThreadId() << std::endl;
  return RealWglMakeCurrent(arg1, arg2);
} */

Hijacker::Hijacker(FnProxy &fnp) : fnp(fnp) {
  fnp.reg<
    kHijacker_QueueDepthTex,
    int,
    HANDLE,
    size_t
  >([=](HANDLE shDepthTexHandle, size_t eventIndex) {
    size_t count = std::count_if(texOrder.begin(), texOrder.end(), [&](const ProxyTexture &pt) -> bool {
      return pt.texHandle == shDepthTexHandle;
    });
    if (count < 2) {
      texOrder.push_back(ProxyTexture{
        shDepthTexHandle,
        eventIndex
      });
      getOut() << "push tex order " << texOrder.size() << std::endl;
    }
    return 0;
  });
  fnp.reg<
    kHijacker_ShiftDepthTex,
    std::tuple<HANDLE, size_t>
  >([=]() {
    getOut() << "shift tex order " << texOrder.size() << std::endl;
    if (texOrder.size() > 0) {
      ProxyTexture result = texOrder.front();
      texOrder.pop_front();
      getOut() << "shift tex order result " << (void *)result.texHandle << std::endl;
      return std::tuple<HANDLE, size_t>(result.texHandle, result.eventIndex);
    } else {
      return std::tuple<HANDLE, size_t>(nullptr, 0);
    }
  });
  fnp.reg<
    kHijacker_ClearDepthTex,
    int
  >([=]() {
    texOrder.clear();
    return 0;
  });
}
/* void Hijacker::ensureClientDevice() {
  if (!hijackerDevice) {
    getOut() << "ensure client device 1" << std::endl;
    int32_t adapterIndex;
    ProxyGetDXGIOutputInfo(&adapterIndex);
    if (adapterIndex == -1) {
      adapterIndex = 0;
    }
    
    getOut() << "ensure client device 2" << std::endl;

    IDXGIFactory1 *dxgi_factory;
    IDXGIAdapter *adapter;
    HRESULT hr = CreateDXGIFactory1(IID_IDXGIFactory1, (void **)&dxgi_factory);
    dxgi_factory->lpVtbl->EnumAdapters(dxgi_factory, adapterIndex, &adapter);

    getOut() << "ensure client device 3" << std::endl;

    ID3D11Device *deviceBasic;
    ID3D11DeviceContext *contextBasic;
    D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_11_1
    };
    hr = D3D11CreateDevice(
      // adapter, // pAdapter
      NULL, // pAdapter
      D3D_DRIVER_TYPE_HARDWARE, // DriverType
      NULL, // Software
      0, // Flags
      featureLevels, // pFeatureLevels
      ARRAYSIZE(featureLevels), // FeatureLevels
      D3D11_SDK_VERSION, // SDKVersion
      &deviceBasic, // ppDevice
      NULL, // pFeatureLevel
      &contextBasic // ppImmediateContext
    );
    getOut() << "ensure client device 4" << std::endl;
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "hijacker client device creation failed " << (void *)hr << std::endl;
      abort();
    }

    hr = deviceBasic->lpVtbl->QueryInterface(deviceBasic, IID_ID3D11Device5, (void **)&hijackerDevice);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "device query failed" << std::endl;
      abort();
    }

    getOut() << "ensure client device 5" << std::endl;

    ID3D11DeviceContext3 *context3;
    hijackerDevice->lpVtbl->GetImmediateContext3(hijackerDevice, &context3);
    hr = context3->lpVtbl->QueryInterface(context3, IID_ID3D11DeviceContext4, (void **)&hijackerContext);
    getOut() << "ensure client device 6" << std::endl;
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "context query failed" << std::endl;
      abort();
    }
    
    getOut() << "ensure client device 7" << std::endl;
    
    dxgi_factory->lpVtbl->Release(dxgi_factory);
    deviceBasic->lpVtbl->Release(deviceBasic);
    contextBasic->lpVtbl->Release(contextBasic);
    context3->lpVtbl->Release(context3);
    
    getOut() << "ensure client device 8" << std::endl;
  }
} */
void Hijacker::hijackDx(ID3D11DeviceContext *context) {
  if (!hijacked) {
    ID3D11DeviceContext1 *context1;
    HRESULT hr = context->lpVtbl->QueryInterface(context, IID_ID3D11DeviceContext1, (void **)&context1);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "hijack failed to get context1: " << (void *)hr << std::endl;
    }
    
    ID3D11Device *device;
    context->lpVtbl->GetDevice(context, &device);

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
    
    RealCreateShaderResourceView  = device->lpVtbl->CreateShaderResourceView;
    error = DetourAttach(&(PVOID&)RealCreateShaderResourceView, MineCreateShaderResourceView);
    checkDetourError("RealCreateShaderResourceView", error);
    
    RealCreateDepthStencilView  = device->lpVtbl->CreateDepthStencilView;
    error = DetourAttach(&(PVOID&)RealCreateDepthStencilView, MineCreateDepthStencilView);
    checkDetourError("RealCreateDepthStencilView", error);
    
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
    
    RealCreateTexture2D = device->lpVtbl->CreateTexture2D;
    error = DetourAttach(&(PVOID&)RealCreateTexture2D, MineCreateTexture2D);
    checkDetourError("RealCreateTexture2D", error);

    error = DetourTransactionCommit();
    checkDetourError("DetourTransactionCommit", error);

    context1->lpVtbl->Release(context1);
    device->lpVtbl->Release(device);

    hijacked = true;
  }
}
void Hijacker::hijackGl() {
  if (!hijackedGl) {
    HMODULE libGlesV2 = LoadLibraryA("libglesv2.dll");
    HMODULE libOpenGl32 = LoadLibraryA("opengl32.dll");
    HMODULE libEgl = LoadLibraryA("libegl.dll");

    if (libGlesV2 != NULL && libOpenGl32 != NULL && libEgl != NULL) {
      decltype(RealEGL_MakeCurrent) EGL_MakeCurrent = (decltype(RealEGL_MakeCurrent))GetProcAddress(libEgl, "eglMakeCurrent");
      EGL_GetCurrentDisplay = (decltype(EGL_GetCurrentDisplay))GetProcAddress(libEgl, "eglGetCurrentDisplay");
      EGL_ChooseConfig = (decltype(EGL_ChooseConfig))GetProcAddress(libEgl, "eglChooseConfig");
      EGL_CreatePbufferFromClientBuffer = (decltype(EGL_CreatePbufferFromClientBuffer))GetProcAddress(libEgl, "eglCreatePbufferFromClientBuffer");
      EGL_BindTexImage = (decltype(EGL_BindTexImage))GetProcAddress(libEgl, "eglBindTexImage");
      EGL_QueryString = (decltype(EGL_QueryString))GetProcAddress(libEgl, "eglQueryString");
      EGL_QueryDisplayAttribEXT = (decltype(EGL_QueryDisplayAttribEXT))GetProcAddress(libEgl, "eglQueryDisplayAttribEXT");
      EGL_QueryDeviceAttribEXT = (decltype(EGL_QueryDeviceAttribEXT))GetProcAddress(libEgl, "eglQueryDeviceAttribEXT");
      EGL_GetError = (decltype(EGL_GetError))GetProcAddress(libEgl, "eglGetError");
      
      decltype(RealGlGetIntegerv) glGetIntegerv = (decltype(RealGlGetIntegerv))GetProcAddress(libGlesV2, "glGetIntegerv");
      RealGlGetIntegerv = glGetIntegerv;
      decltype(RealGlGetFramebufferAttachmentParameteriv) glGetFramebufferAttachmentParameteriv = (decltype(RealGlGetFramebufferAttachmentParameteriv))GetProcAddress(libGlesV2, "glGetFramebufferAttachmentParameteriv");
      RealGlGetFramebufferAttachmentParameteriv = glGetFramebufferAttachmentParameteriv;

      decltype(RealGlViewport) glViewport = (decltype(RealGlViewport))GetProcAddress(libGlesV2, "glViewport");
      decltype(RealGlGenFramebuffers) glGenFramebuffers = (decltype(RealGlGenFramebuffers))GetProcAddress(libGlesV2, "glGenFramebuffers");
      decltype(RealGlBindFramebuffer) glBindFramebuffer = (decltype(RealGlBindFramebuffer))GetProcAddress(libGlesV2, "glBindFramebuffer");
      decltype(RealGlGenRenderbuffers) glGenRenderbuffers = (decltype(RealGlGenRenderbuffers))GetProcAddress(libGlesV2, "glGenRenderbuffers");
      decltype(RealGlBindRenderbuffer) glBindRenderbuffer = (decltype(RealGlBindRenderbuffer))GetProcAddress(libGlesV2, "glBindRenderbuffer");
      decltype(RealGlFramebufferTexture2D) glFramebufferTexture2D = (decltype(RealGlFramebufferTexture2D))GetProcAddress(libGlesV2, "glFramebufferTexture2D");
      decltype(RealGlFramebufferTexture2DMultisampleEXT) glFramebufferTexture2DMultisampleEXT = (decltype(RealGlFramebufferTexture2DMultisampleEXT))GetProcAddress(libGlesV2, "glFramebufferTexture2DMultisampleEXT");
      decltype(RealGlFramebufferRenderbuffer) glFramebufferRenderbuffer = (decltype(RealGlFramebufferRenderbuffer))GetProcAddress(libGlesV2, "glFramebufferRenderbuffer");
      decltype(RealGlRenderbufferStorageMultisampleEXT) glRenderbufferStorageMultisampleEXT = (decltype(RealGlRenderbufferStorageMultisampleEXT))GetProcAddress(libGlesV2, "glRenderbufferStorageMultisampleEXT");
      decltype(RealGlRenderbufferStorage) glRenderbufferStorage = (decltype(RealGlRenderbufferStorage))GetProcAddress(libGlesV2, "glRenderbufferStorage");
      decltype(RealGlDiscardFramebufferEXT) glDiscardFramebufferEXT = (decltype(RealGlDiscardFramebufferEXT))GetProcAddress(libGlesV2, "glDiscardFramebufferEXT");
      decltype(RealGlDiscardFramebufferEXTContextANGLE) glDiscardFramebufferEXTContextANGLE = (decltype(RealGlDiscardFramebufferEXTContextANGLE))GetProcAddress(libGlesV2, "glDiscardFramebufferEXTContextANGLE");
      decltype(RealGlInvalidateFramebuffer) glInvalidateFramebuffer = (decltype(RealGlInvalidateFramebuffer))GetProcAddress(libGlesV2, "glInvalidateFramebuffer");
      decltype(RealDiscardFramebufferEXT) DiscardFramebufferEXT = (decltype(RealDiscardFramebufferEXT))GetProcAddress(libGlesV2, "?DiscardFramebufferEXT@gl@@YAXIHPEBI@Z");
      decltype(RealGlGenTextures) glGenTextures = (decltype(RealGlGenTextures))GetProcAddress(libGlesV2, "glGenTextures");
      decltype(RealGlBindTexture) glBindTexture = (decltype(RealGlBindTexture))GetProcAddress(libGlesV2, "glBindTexture");
      decltype(RealGlTexImage2D) glTexImage2D = (decltype(RealGlTexImage2D))GetProcAddress(libGlesV2, "glTexImage2D");
      decltype(RealGlTexParameteri) glTexParameteri = (decltype(RealGlTexParameteri))GetProcAddress(libGlesV2, "glTexParameteri");
      decltype(RealGlReadPixels) glReadPixels = (decltype(RealGlReadPixels))GetProcAddress(libGlesV2, "glReadPixels");
      decltype(RealGlTexStorage2DMultisample) glTexStorage2DMultisample = (decltype(RealGlTexStorage2DMultisample))GetProcAddress(libGlesV2, "glTexStorage2DMultisample");
      decltype(RealGlRequestExtensionANGLE) glRequestExtensionANGLE = (decltype(RealGlRequestExtensionANGLE))GetProcAddress(libGlesV2, "glRequestExtensionANGLE");
      decltype(RealGlDeleteTextures) glDeleteTextures = (decltype(RealGlDeleteTextures))GetProcAddress(libGlesV2, "glDeleteTextures");
      decltype(RealGlFenceSync) glFenceSync = (decltype(RealGlFenceSync))GetProcAddress(libGlesV2, "glFenceSync");
      decltype(RealGlDeleteSync) glDeleteSync = (decltype(RealGlDeleteSync))GetProcAddress(libGlesV2, "glDeleteSync");
      decltype(RealGlWaitSync) glWaitSync = (decltype(RealGlWaitSync))GetProcAddress(libGlesV2, "glWaitSync");
      decltype(RealGlClientWaitSync) glClientWaitSync = (decltype(RealGlClientWaitSync))GetProcAddress(libGlesV2, "glClientWaitSync");
      decltype(RealGlDrawElements) glDrawElements = (decltype(RealGlDrawElements))GetProcAddress(libGlesV2, "glDrawElements");
      decltype(RealGlClear) glClear = (decltype(RealGlClear))GetProcAddress(libGlesV2, "glClear");
      decltype(RealGlClearColor) glClearColor = (decltype(RealGlClearColor))GetProcAddress(libGlesV2, "glClearColor");
      decltype(RealGlColorMask) glColorMask = (decltype(RealGlColorMask))GetProcAddress(libGlesV2, "glColorMask");
      decltype(RealGlFlush) glFlush = (decltype(RealGlFlush))GetProcAddress(libGlesV2, "glFlush");
      // decltype(RealWglMakeCurrent) wglMakeCurrent = (decltype(RealWglMakeCurrent))GetProcAddress(libOpenGl32, "wglMakeCurrent");
      decltype(RealGlGetError) glGetError = (decltype(RealGlGetError))GetProcAddress(libGlesV2, "glGetError");
  
      LONG error = DetourTransactionBegin();
      checkDetourError("DetourTransactionBegin", error);

      error = DetourUpdateThread(GetCurrentThread());
      checkDetourError("DetourUpdateThread", error);
      
      RealGlViewport = glViewport;
      
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
      
      RealGlRenderbufferStorage = glRenderbufferStorage;
      /* error = DetourAttach(&(PVOID&)RealGlRenderbufferStorageMultisampleEXT, MineGlRenderbufferStorageMultisampleEXT);
      checkDetourError("RealGlRenderbufferStorageMultisampleEXT", error); */
      
      RealGlRenderbufferStorageMultisampleEXT = glRenderbufferStorageMultisampleEXT;
      error = DetourAttach(&(PVOID&)RealGlRenderbufferStorageMultisampleEXT, MineGlRenderbufferStorageMultisampleEXT);
      checkDetourError("RealGlRenderbufferStorageMultisampleEXT", error);
      
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
      /* error = DetourAttach(&(PVOID&)RealGlGenTextures, MineGlGenTextures);
      checkDetourError("RealGlGenTextures", error); */

      RealGlBindTexture = glBindTexture;
      /* error = DetourAttach(&(PVOID&)RealGlBindTexture, MineGlBindTexture);
      checkDetourError("RealGlBindTexture", error); */
      
      RealGlTexImage2D = glTexImage2D;
      /* error = DetourAttach(&(PVOID&)RealGlBindTexture, MineGlBindTexture);
      checkDetourError("RealGlBindTexture", error); */
      
      RealGlTexParameteri = glTexParameteri;
      
      RealGlReadPixels = glReadPixels;
      /* error = DetourAttach(&(PVOID&)RealGlBindTexture, MineGlBindTexture);
      checkDetourError("RealGlBindTexture", error); */
      
      RealGlTexStorage2DMultisample = glTexStorage2DMultisample;

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
      
      RealGlDrawElements = glDrawElements;
      
      RealGlClear = glClear;
      error = DetourAttach(&(PVOID&)RealGlClear, MineGlClear);
      checkDetourError("RealGlClear", error);
      
      RealGlClearColor = glClearColor;
      error = DetourAttach(&(PVOID&)RealGlClearColor, MineGlClearColor);
      checkDetourError("RealGlClearColor", error);
      
      RealGlColorMask = glColorMask;
      error = DetourAttach(&(PVOID&)RealGlColorMask, MineGlColorMask);
      checkDetourError("RealGlColorMask", error);
      
      RealGlFlush = glFlush;
      
      RealEGL_MakeCurrent = EGL_MakeCurrent;
      error = DetourAttach(&(PVOID&)RealEGL_MakeCurrent, MineEGL_MakeCurrent);
      checkDetourError("RealEGL_MakeCurrent", error);
      
      /* RealWglMakeCurrent = wglMakeCurrent;
      error = DetourAttach(&(PVOID&)RealWglMakeCurrent, MineWglMakeCurrent);
      checkDetourError("RealWglMakeCurrent", error); */

      RealGlGetError = glGetError;
      /* error = DetourAttach(&(PVOID&)RealGlGetError, MineGlGetError);
      checkDetourError("RealGlGetError", error); */

      error = DetourTransactionCommit();
      checkDetourError("DetourTransactionCommit", error);
    } else {
      getOut() << "failed to load gl hijack libs: " << (void *)libGlesV2 << " " << (void *)libOpenGl32 << " " << GetLastError() << std::endl;
    }

    hijackedGl = true;
  }
}
ProxyTexture Hijacker::getDepthTextureMatching(ID3D11Texture2D *tex) { // called from client during submit
  // local
  if (texOrder.size() > 0) {
    ProxyTexture result = texOrder.front();
    texOrder.pop_front();
    return result;
  }
  // remote
  std::tuple<HANDLE, size_t> shiftResult = fnp.call<
    kHijacker_ShiftDepthTex,
    std::tuple<HANDLE, size_t>
  >();
  HANDLE &sharedDepthHandle = std::get<0>(shiftResult);
  size_t &eventIndex = std::get<1>(shiftResult);
  if (sharedDepthHandle) {
    if (clientDepthHandleLatched != sharedDepthHandle) {
      if (clientDepthHandleLatched) {
        // XXX delete old resources
      }
      clientDepthHandleLatched = sharedDepthHandle;
      
      getOut() << "latch client depth " << (void *)sharedDepthHandle << std::endl;
    }
    
    // getOut() << "would have depthed " << (void *)clientDepthTex << " " << clientDepthEvent << std::endl;

    return ProxyTexture{
      sharedDepthHandle,
      eventIndex
    };
  }
  // not found
  return ProxyTexture{
    nullptr,
    0
  };
}
void Hijacker::flushTextureLatches() {
  texOrder.clear();
  fnp.call<
    kHijacker_ClearDepthTex,
    int
  >();
  /* if (texMap.size() > 0) {
    for (auto iter : texMap) {
      iter.first->lpVtbl->Release(iter.first);
      iter.second->lpVtbl->Release(iter.second);
    }
    texMap.clear();
    texOrder.clear();
  } */
}