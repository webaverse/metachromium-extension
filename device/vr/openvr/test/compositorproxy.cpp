// #include <chrono>
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/hijack.h"

// extern uint64_t *pFrameCount;
// extern bool isChrome;
// extern bool haveZBufferParams;
// extern float zBufferParams[4];

namespace vr {
char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";
char kIVRCompositor_GetTrackingSpace[] = "IVRCompositor::GetTrackingSpace";
char kIVRCompositor_WaitGetPoses[] = "IVRCompositor::WaitGetPoses";
char kIVRCompositor_GetLastPoses[] = "IVRCompositor::GetLastPoses";
char kIVRCompositor_GetLastPoseForTrackedDeviceIndex[] = "IVRCompositor::GetLastPoseForTrackedDeviceIndex";
char kIVRCompositor_PrepareSubmit[] = "IVRCompositor::PrepareSubmit";
char kIVRCompositor_Submit[] = "IVRCompositor::Submit";
char kIVRCompositor_FlushSubmit[] = "IVRCompositor::FlushSubmit";
char kIVRCompositor_ClearLastSubmittedFrame[] = "IVRCompositor::ClearLastSubmittedFrame";
char kIVRCompositor_PostPresentHandoff[] = "IVRCompositor::PostPresentHandoff";
char kIVRCompositor_GetFrameTiming[] = "IVRCompositor::GetFrameTiming";
char kIVRCompositor_GetFrameTimings[] = "IVRCompositor::GetFrameTimings";
char kIVRCompositor_GetFrameTimeRemaining[] = "IVRCompositor::GetFrameTimeRemaining";
char kIVRCompositor_GetCumulativeStats[] = "IVRCompositor::GetCumulativeStats";
char kIVRCompositor_FadeToColor[] = "IVRCompositor::FadeToColor";
char kIVRCompositor_GetCurrentFadeColor[] = "IVRCompositor::GetCurrentFadeColor";
char kIVRCompositor_FadeGrid[] = "IVRCompositor::FadeGrid";
char kIVRCompositor_GetCurrentGridAlpha[] = "IVRCompositor::GetCurrentGridAlpha";
char kIVRCompositor_ClearSkyboxOverride[] = "IVRCompositor::ClearSkyboxOverride";
char kIVRCompositor_CompositorBringToFront[] = "IVRCompositor::CompositorBringToFront";
char kIVRCompositor_CompositorGoToBack[] = "IVRCompositor::CompositorGoToBack";
char kIVRCompositor_CompositorQuit[] = "IVRCompositor::CompositorQuit";
char kIVRCompositor_IsFullscreen[] = "IVRCompositor::IsFullscreen";
char kIVRCompositor_GetCurrentSceneFocusProcess[] = "IVRCompositor::GetCurrentSceneFocusProcess";
char kIVRCompositor_GetLastFrameRenderer[] = "IVRCompositor::GetLastFrameRenderer";
char kIVRCompositor_CanRenderScene[] = "IVRCompositor::CanRenderScene";
char kIVRCompositor_ShowMirrorWindow[] = "IVRCompositor::ShowMirrorWindow";
char kIVRCompositor_HideMirrorWindow[] = "IVRCompositor::HideMirrorWindow";
char kIVRCompositor_IsMirrorWindowVisible[] = "IVRCompositor::IsMirrorWindowVisible";
char kIVRCompositor_CompositorDumpImages[] = "IVRCompositor::CompositorDumpImages";
char kIVRCompositor_ShouldAppRenderWithLowResources[] = "IVRCompositor::ShouldAppRenderWithLowResources";
char kIVRCompositor_ForceInterleavedReprojectionOn[] = "IVRCompositor::ForceInterleavedReprojectionOn";
char kIVRCompositor_ForceReconnectProcess[] = "IVRCompositor::ForceReconnectProcess";
char kIVRCompositor_SuspendRendering[] = "IVRCompositor::SuspendRendering";
char kIVRCompositor_GetMirrorTextureD3D11[] = "IVRCompositor::GetMirrorTextureD3D11";
char kIVRCompositor_ReleaseMirrorTextureD3D11[] = "IVRCompositor::ReleaseMirrorTextureD3D11";
char kIVRCompositor_GetMirrorTextureGL[] = "IVRCompositor::GetMirrorTextureGL";
char kIVRCompositor_ReleaseSharedGLTexture[] = "IVRCompositor::ReleaseSharedGLTexture";
char kIVRCompositor_LockGLSharedTextureForAccess[] = "IVRCompositor::LockGLSharedTextureForAccess";
char kIVRCompositor_UnlockGLSharedTextureForAccess[] = "IVRCompositor::UnlockGLSharedTextureForAccess";
char kIVRCompositor_GetVulkanInstanceExtensionsRequired[] = "IVRCompositor::GetVulkanInstanceExtensionsRequired";
char kIVRCompositor_GetVulkanDeviceExtensionsRequired[] = "IVRCompositor::GetVulkanDeviceExtensionsRequired";
char kIVRCompositor_SetExplicitTimingMode[] = "IVRCompositor::SetExplicitTimingMode";
char kIVRCompositor_SubmitExplicitTimingData[] = "IVRCompositor::SubmitExplicitTimingData";
char kIVRCompositor_IsMotionSmoothingEnabled[] = "IVRCompositor::IsMotionSmoothingEnabled";
char kIVRCompositor_IsMotionSmoothingSupported[] = "IVRCompositor::IsMotionSmoothingSupported";
char kIVRCompositor_IsCurrentSceneFocusAppLoading[] = "IVRCompositor::IsCurrentSceneFocusAppLoading";

const char *composeVsh = R"END(
#version 330

in vec2 position;
in vec2 uv;
out vec2 vUv;

void main() {
  vUv = uv;
  gl_Position = vec4(position.xy, 0., 1.);
}
)END";
const char *blitFsh = R"END(
#version 330

in vec2 vUv;
out vec4 fragColor;
uniform sampler2D tex;

void main() {
  fragColor = vec4(texture(tex, vUv).rgb, 1.0);
  // fragColor += vec4(0.5, 0.0, 0.0, 0.1);
}
)END";
const char *hlsl = R"END(
//------------------------------------------------------------//
// Description
//------------------------------------------------------------//
// A simple fullscreen quad
//------------------------------------------------------------//

//------------------------------------------------------------//
// Global shader data
//------------------------------------------------------------//
//------------------------------------------------------------//

//------------------------------------------------------------//
// Constants
//------------------------------------------------------------//
// float Width;
// float Height;
// float depthScale = 1000;
//------------------------------------------------------------//

cbuffer VS_CONSTANT_BUFFER : register(b0)
{
  float flip;
  float eye1;
  float tmpvs11;
  float tmpvs12;
  float tmpvs13;
  float tmpvs14;
  float tmpvs15;
  float tmpvs16;
}

cbuffer PS_CONSTANT_BUFFER : register(b0)
{
  float width;
  float height;
  float tmpps11;
  float tmpps12;
  float tmpps13;
  float tmpps14;
  float tmpps15;
  float tmpps16;
}

cbuffer PS_CONSTANT_BUFFER : register(b1)
{
  float2 _ZBufferParams;
  float4 depthColor;
  float tmpps21;
  float tmpps22;
}

//------------------------------------------------------------//
// Structs
//------------------------------------------------------------//
// Vertex shader OUT struct
struct VS_OUTPUT
{
   float4 Position: SV_POSITION;
   float2 Uv: TEXCOORD0;
   float2 Tex1: TEXCOORD1;
};
//------------------------------------------------------------//
// Pixel Shader OUT struct
struct PS_OUTPUT
{
	float4 Color : SV_Target0;
	float Depth : SV_Target1;
};
//------------------------------------------------------------//

//------------------------------------------------------------//
// Textures / samplers
//------------------------------------------------------------//
//Texture
Texture2D QuadTexture : register(ps, t0);
Texture2DMS<float4> QuadDepthTexture : register(ps, t1);
Texture2D DepthTexture : register(ps, t2);
SamplerState QuadTextureSampler {
  MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
//------------------------------------------------------------//

VS_OUTPUT vs_main(float2 inPos : POSITION, float2 inTex : TEXCOORD0)
{
  VS_OUTPUT Output;
  Output.Position = float4(inPos, 0, 1);
  Output.Uv = float2(inTex.x, (flip > 0) ? inTex.y : (1-inTex.y));
  Output.Tex1 = float2(inTex.x + eye1, inTex.y);
  return Output;
}

/* // Unity
static const float4x4 projectionMatrix = {0.917286, -0, 0, 0, 0, -0.833537, 0, 0, -0.174072, 0.106141, 9.53674e-07, -1, 0, -0, 0.02, 0};
static const float m32 = projectionMatrix[3][2];
static const float m22 = projectionMatrix[2][2];
static const float near = m32 / (m22 + 1);
static const float far = m32 / (m22);
static const float4 _ZBufferParams = float4(-1+far/near, 1, (-1+far/near)/far, 1/far);

// Chrome
static const float4x4 projectionMatrixRaw = {0.917286, 0, -0.174072, 0, 0, 0.833537, -0.106141, 0, 0, 0, -1.0002, -0.20002, 0, 0, -1, 0};
static const float4x4 projectionMatrix = transpose(projectionMatrixRaw); // {0.917286, 0, 0, 0, 0, 0.833537, 0, 0, -0.174072, -0.106141, -1.0002, -1, 0, 0, -0.20002, 0};
static const float m32 = projectionMatrix[3][2];
static const float m22 = projectionMatrix[2][2];
static const float near = m32 / (m22 - 1);
static const float far = m32 / (m22 + 1);
static const float4 _ZBufferParams = float4(1-far/near, far/near, (1-far/near)/far, (far/near)/far); */

inline float LinearEyeDepth( float z ) {
  return 1.0 / (_ZBufferParams.x * z + _ZBufferParams.y);
}

PS_OUTPUT ps_main(VS_OUTPUT IN)
{
  PS_OUTPUT result;

  // float near = _ZBufferParams.x;
  // float reversed = _ZBufferParams.y;

  float depthScale = 1000;

  float d = QuadDepthTexture[uint2(IN.Tex1.x * width, IN.Tex1.y * height)].r;
  d = LinearEyeDepth(d);
  // d /= depthScale;
  // d = LinearEyeDepth(reversed > 0 ? (1-d) : d);
  /* if (reversed > 0) {
    d *= 1.464304;
  } */
  // d = LinearEyeDepth(d*2.0 - 1.0);
  float e = DepthTexture.Sample(QuadTextureSampler, IN.Uv).r;

  /* if (d < 0.5) {
    result.Color = float4(d, 0, 0, 1);
    result.Depth = d;
  } else if (d < 1) {
    result.Color = float4(0, d, 0, 1);
    result.Depth = d;
  } else {
    result.Color = float4(0, 0, d, 1);
    result.Depth = e;
    // discard;
  } */

  if (e == 1.0 || d < (e*depthScale)) {
    result.Color = float4(QuadTexture.Sample(QuadTextureSampler, IN.Uv).rgb, 1);
    result.Depth = d/depthScale;
  } else {
    // result.Color = float4(0, 0, e, 1);
    // result.Depth = e;
    discard;
  }

  return result;
}

//------------------------------------------------------------//
)END";

const EVREye EYES[] = {
  Eye_Left,
  Eye_Right,
};

/* void checkError(const char *label) {
  auto error = glGetError();
  if (error) {
    getOut() << "gl error: " << error << " " << label << std::endl;
  }
} */

PVRCompositor::PVRCompositor(IVRCompositor *vrcompositor, Hijacker &hijacker, FnProxy &fnp) :
  vrcompositor(vrcompositor),
  hijacker(hijacker),
  fnp(fnp)
{
  fnp.reg<
    kIVRCompositor_SetTrackingSpace,
    int,
    ETrackingUniverseOrigin
  >([=](ETrackingUniverseOrigin eOrigin) {
    vrcompositor->SetTrackingSpace(eOrigin);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetTrackingSpace,
    ETrackingUniverseOrigin
  >([=]() {
    return vrcompositor->GetTrackingSpace();
  });
  fnp.reg<
    kIVRCompositor_WaitGetPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    InfoQueueLog();
    
    // getOut() << "waitgetposes 1" << std::endl;
    managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);
    // getOut() << "handle poses 2" << std::endl;

    memcpy(renderPoseArray.data(), cachedRenderPoses, unRenderPoseArrayCount * sizeof(TrackedDevicePose_t));
    memcpy(gamePoseArray.data(), cachedGamePoses, unGamePoseArrayCount * sizeof(TrackedDevicePose_t));

    // EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

    // getOut() << "handle poses 3" << std::endl;

    EVRCompositorError error = VRCompositorError_None;
    auto result = std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
    // getOut() << "handle poses 4" << std::endl;
    return std::move(result);
  });
  fnp.reg<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

    memcpy(renderPoseArray.data(), cachedRenderPoses, unRenderPoseArrayCount * sizeof(TrackedDevicePose_t));
    memcpy(gamePoseArray.data(), cachedGamePoses, unGamePoseArrayCount * sizeof(TrackedDevicePose_t));

    // auto start = std::chrono::high_resolution_clock::now();
    // EVRCompositorError error = vrcompositor->GetLastPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);
    /* auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    getOut() << "get last poses real " << elapsed.count() << std::endl; */

    EVRCompositorError error = VRCompositorError_None;
    return std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
  });
  fnp.reg<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >([=](TrackedDeviceIndex_t unDeviceIndex) {
    managed_binary<TrackedDevicePose_t> outputPose(1);
    managed_binary<TrackedDevicePose_t> gamePose(1);

    EVRCompositorError error = vrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, outputPose.data(), gamePose.data());

    return std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(outputPose),
      std::move(gamePose)
    );
  });
  fnp.reg<
    kIVRCompositor_PrepareSubmit,
    int,
    ETextureType
  >([=](ETextureType textureType) {
    // getOut() << "prepare submit server 1" << std::endl;

    HRESULT hr;
    if (!device) {
      // device = (ID3D11Device *)pDevice;

      int32_t adapterIndex;
      g_vrsystem->GetDXGIOutputInfo(&adapterIndex);
      if (adapterIndex == -1) {
        adapterIndex = 0;
      }

      Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_factory;
      IDXGIAdapter1 *adapter;
      hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &dxgi_factory);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "create dxgi factory failed " << (void *)hr << std::endl;
      }
      dxgi_factory->EnumAdapters1(adapterIndex, &adapter);

      getOut() << "create device " << adapterIndex << " " << (void *)adapter << std::endl;

      for (unsigned int i = 0;; i++) {
        hr = dxgi_factory->EnumAdapters1(i, &adapter);
        if (SUCCEEDED(hr)) {
          DXGI_ADAPTER_DESC desc;
          adapter->GetDesc(&desc);
          getOut() << "got adapter desc " << i << (char *)desc.Description << " " << desc.AdapterLuid.HighPart << " " << desc.AdapterLuid.LowPart << std::endl;
        } else {
          break;
        }
      }
      
      // getOut() << "creating device 1" << std::endl;

      // Microsoft::WRL::ComPtr<ID3D11Device> device;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;

      D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1
      };
      // getOut() << "create swap chain " << (void *)g_hWnd << std::endl;
      DXGI_SWAP_CHAIN_DESC swapChainDesc{};
      swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
      swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; 
      swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; 
      swapChainDesc.SampleDesc.Count = 1;                               
      swapChainDesc.SampleDesc.Quality = 0;                               
      swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      swapChainDesc.BufferCount = 1;                               
      swapChainDesc.OutputWindow = g_hWnd;                
      swapChainDesc.Windowed = true;

      hr = D3D11CreateDeviceAndSwapChain(
        adapter, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        0, // D3D11_CREATE_DEVICE_DEBUG, // Flags
        featureLevels, // pFeatureLevels
        ARRAYSIZE(featureLevels), // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        &swapChainDesc, // pSwapChainDesc,
        &swapChain, // ppSwapChain
        &deviceBasic, // ppDevice
        NULL, // pFeatureLevel
        &contextBasic // ppImmediateContext
      );
      // getOut() << "creating device 2" << std::endl;
      if (SUCCEEDED(hr)) {
        hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "device query failed" << std::endl;
          abort();
        }
        
        Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
        device->GetImmediateContext3(&context3);
        hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "context query failed" << std::endl;
          abort();
        }

        hr = deviceBasic->QueryInterface(__uuidof(ID3D11InfoQueue), (void **)&infoQueue);
        if (SUCCEEDED(hr)) {
          infoQueue->PushEmptyStorageFilter();
        } else {
          getOut() << "info queue query failed" << std::endl;
          // abort();
        }

        /* hr = contextBasic->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&context);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "context query failed" << std::endl;
        } */
        
        IDXGIDevice * pDXGIDevice = nullptr;
        hr = device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
        
        IDXGIAdapter * pDXGIAdapter = nullptr;
        hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
        
        DXGI_ADAPTER_DESC desc;
        hr = pDXGIAdapter->GetDesc(&desc);
        getOut() << "got desc " << (char *)desc.Description << " " << desc.AdapterLuid.HighPart << " " << desc.AdapterLuid.LowPart << std::endl;
        
        // nothing
      } else {
        getOut() << "create dx device failed " << (void *)hr << std::endl;
        abort();
      }
      
      InitShader();
    }
    
    if (!fence) {
      hr = device->CreateFence(
        0, // value
        // D3D11_FENCE_FLAG_SHARED|D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER, // flags
        // D3D11_FENCE_FLAG_SHARED, // flags
        D3D11_FENCE_FLAG_SHARED, // flags
        __uuidof(ID3D11Fence), // interface
        (void **)&fence // out
      );
      if (SUCCEEDED(hr)) {
        // getOut() << "created fence " << (void *)fence << std::endl;
        // nothing
      } else {
        getOut() << "failed to create fence" << std::endl;
        abort();
      }

      hr = fence->CreateSharedHandle(
        NULL, // security attributes
        GENERIC_ALL, // access
        nullptr, // name
        &fenceHandle // share handle
      );
      if (SUCCEEDED(hr)) {
        getOut() << "create shared fence handle " << (void *)fenceHandle << std::endl;
        // nothing
      } else {
        getOut() << "failed to create fence share handle" << std::endl;
        abort();
      }
      
      // context->Flush();
    }
    
    // getOut() << "prepare submit server 20" << std::endl;

    // return fenceHandle;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_Submit,
    std::tuple<uintptr_t, uintptr_t, uint64_t>,
    EVREye,
    managed_binary<Texture_t>,
    bool,
    EVRSubmitFlags,
    std::tuple<uintptr_t, float, float>,
    std::tuple<uintptr_t, uintptr_t, uint64_t>
  >([=, &fnp](
    EVREye eEye,
    managed_binary<Texture_t> sharedTexture,
    bool flip,
    EVRSubmitFlags submitFlags,
    std::tuple<uintptr_t, float, float> depthSpec,
    std::tuple<uintptr_t, uintptr_t, uint64_t> fenceSpec
  ) {
    Texture_t *pTexture = sharedTexture.data();
    uintptr_t sharedDepthHandlePtr = std::get<0>(depthSpec);
    HANDLE sharedDepthHandle = (HANDLE)sharedDepthHandlePtr;
    float zbx = std::get<1>(depthSpec);
    float zby = std::get<2>(depthSpec);
    DWORD clientProcessId = (DWORD)std::get<0>(fenceSpec);
    HANDLE clientFenceHandle = (HANDLE)std::get<1>(fenceSpec);
    uint64_t clientFenceValue = std::get<2>(fenceSpec);

    // getOut() << "submit server 1 " << zbx << " " << zby << " " << zbz << " " << zbw << std::endl;

    auto key = std::pair<size_t, EVREye>(fnp.remoteProcessId, eEye);
    auto iter = inBackIndices.find(key);
    size_t index;
    if (iter != inBackIndices.end()) {
      index = iter->second;
    } else {
      index = inBackTexs.size();
      inBackIndices[key] = index;
      iter = inBackIndices.find(key);

      inBackTexs.resize(index+1, NULL);
      // inBackInteropHandles.resize(index+1, NULL);
      inBackDepthTexs.resize(index+1, NULL);
      // inBackDepthReadEvents.resize(index+1, NULL);
      // inBackDepthInteropHandles.resize(index+1, NULL);
      shaderResourceViews.resize(index+1, std::pair<ID3D11ShaderResourceView *, ID3D11ShaderResourceView *>(nullptr, nullptr));
      // inBackReadEvents.resize(index+1, NULL);
      inBackTextureFulls.resize(index+1, 0);
      inBackHandleLatches.resize(index+1, NULL);
      inBackDepthHandleLatches.resize(index+1, NULL);
      inBackFences.resize(index+1, NULL);
    }
    
    // getOut() << "submit server 2" << std::endl;

    HANDLE sharedHandle = (HANDLE)pTexture->handle;
    ID3D11Texture2D *&shTexIn = inBackTexs[index]; // color texture
    // HANDLE &shTexInInteropHandle = inBackInteropHandles[index]; // interop texture handle
    ID3D11Texture2D *&shDepthTexIn = inBackDepthTexs[index]; // depth texture
    // HANDLE &depthReadEvent = inBackDepthReadEvents[index]; // depth texture fence read event
    // HANDLE &shDepthTexInInteropHandle = inBackDepthInteropHandles[index]; // interop depth texture handle
    ID3D11ShaderResourceView *&shaderResourceView = shaderResourceViews[index].first;
    ID3D11ShaderResourceView *&shaderDepthResourceView = shaderResourceViews[index].second;
    // HANDLE &readEvent = inBackReadEvents[index]; // interop texture handle
    float &textureFull = inBackTextureFulls[index]; // depth texture is side-by-side
    HANDLE &handleLatched = inBackHandleLatches[index]; // remembered attachemnt
    HANDLE &depthHandleLatched = inBackDepthHandleLatches[index]; // remembered depth attachemnt
    ID3D11Fence *&clientFence = inBackFences[index]; // remembered client fence

    // getOut() << "submit server 3" << std::endl;

    if (handleLatched != sharedHandle) {
      // getOut() << "got shTex in " << (void *)sharedHandle << std::endl;
      if (handleLatched) {
        // XXX delete old resources
        // hr = device->OpenSharedResou rce(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      }
      handleLatched = sharedHandle;

      // getOut() << "submit server 4" << std::endl;

      // IDXGIResource1 *pD3DResource;
      // HRESULT hr = device->OpenSharedResource1(sharedHandle, __uuidof(IDXGIResource1), (void**)(&pD3DResource));
      

      // getOut() << "submit server 5" << std::endl;

      /* GLuint textures[2];
      glGenTextures(ARRAYSIZE(textures), textures);
      shTexInId = textures[0];
      shDepthTexInId = textures[1]; */

      {
        ID3D11Resource *shTexResource;
        HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&shTexResource));

        if (SUCCEEDED(hr)) {
          hr = shTexResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shTexIn));
          
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to unpack shared texture: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
            abort();
          }
        } else {
          getOut() << "failed to unpack shared texture handle: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
          abort();
        }

        /* shTexInInteropHandle = wglDXRegisterObjectNV(hInteropDevice, shTexIn, shTexInId, GL_TEXTURE_2D, WGL_ACCESS_READ_ONLY_NV);
        if (shTexInInteropHandle) {
          // nothing
        } else {
          // C007006E
          getOut() << "failed to get shared interop handle " << (void *)hInteropDevice << " " << shTexIn << " " << shTexInId << " " << glGetError() << " " << GetLastError() << std::endl;
          abort();
        } */
        shTexResource->Release();
      }

      {
        D3D11_TEXTURE2D_DESC desc;
        shTexIn->GetDesc(&desc);
        getOut() << "shader resource view tex " <<
          desc.Width << " " << desc.Height << " " <<
          desc.MipLevels << " " << desc.ArraySize << " " <<
          desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
          desc.Format << " " <<
          desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags <<
          std::endl;
        
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
        shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        HRESULT hr = device->CreateShaderResourceView(
          shTexIn,
          // texResource,
          &shaderResourceViewDesc,
          &shaderResourceView
        );
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to create shader resource view: " << (void *)hr << std::endl;
          abort();
        }
      }
    }

    if (depthHandleLatched != sharedDepthHandle) {
      if (depthHandleLatched) {
        // XXX delete old resources
      }
      depthHandleLatched = sharedDepthHandle;

      if (sharedDepthHandle) {
        {
          ID3D11Resource *shDepthTexResource;
          HRESULT hr = device->OpenSharedResource(sharedDepthHandle, __uuidof(ID3D11Resource), (void**)(&shDepthTexResource));

          if (SUCCEEDED(hr)) {
            hr = shDepthTexResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shDepthTexIn));

            if (SUCCEEDED(hr)) {
              // nothing
            } else {
              getOut() << "failed to unpack shared depth texture: " << (void *)hr << " " << (void *)sharedDepthHandle << std::endl;
              abort();
            }
          } else {
            getOut() << "failed to unpack shared depth texture handle: " << (void *)hr << " " << (void *)sharedDepthHandle << std::endl;
            abort();
          }
          shDepthTexResource->Release();
        }
        {
          D3D11_TEXTURE2D_DESC desc;
          shDepthTexIn->GetDesc(&desc);
          getOut() << "shader resource view depth " <<
            desc.Width << " " << desc.Height << " " <<
            desc.MipLevels << " " << desc.ArraySize << " " <<
            desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
            desc.Format << " " <<
            desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags <<
            std::endl;

          D3D11_SHADER_RESOURCE_VIEW_DESC shaderDepthResourceViewDesc{};
          if (desc.Format == DXGI_FORMAT_R32G8X24_TYPELESS) {
            shaderDepthResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
          } else if (desc.Format == DXGI_FORMAT_R24G8_TYPELESS) {
            shaderDepthResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
          } else {
            shaderDepthResourceViewDesc.Format = desc.Format;
          }
          shaderDepthResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
          // shaderDepthResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
          // shaderDepthResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
          shaderDepthResourceViewDesc.Texture2D.MostDetailedMip = 0;
          shaderDepthResourceViewDesc.Texture2D.MipLevels = 1;
          HRESULT hr = device->CreateShaderResourceView(
            shDepthTexIn,
            // texResource,
            &shaderDepthResourceViewDesc,
            &shaderDepthResourceView
          );
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            getOut() << "failed to create depth shader resource view: " << (void *)hr << std::endl;
            InfoQueueLog();
            abort();
          }
          
          // getOut() << "set texture full " << desc.Width << " " << width << std::endl;
          textureFull = desc.Width > width ? 1 : 0;
        }
      } else {
        getOut() << "shader resource view depth clear" << std::endl;

        shaderDepthResourceView = nullptr;
        textureFull = 0;
      }
    }
    
    if (!clientFence) {
      /* ID3D11Resource *fenceResource;
      HRESULT hr = device->OpenSharedResource(fenceHandle, __uuidof(ID3D11Resource), (void**)(&fenceResource));

      if (SUCCEEDED(hr)) {
        hr = fenceResource->QueryInterface(__uuidof(ID3D11Fence), (void**)(&fence));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared fence: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to unpack shared fence handle: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
        abort();
      }
      
      (std::string("Local\\OpenVrProxyFence") + std::to_string(eEye == Eye_Left ? 0 : 1)).c_str() */
      
      HANDLE srcProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, clientProcessId);
      HANDLE dstProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, GetCurrentProcessId());
      
      HANDLE fenceHandle2;
      BOOL ok = DuplicateHandle(
        srcProcess,
        clientFenceHandle,
        dstProcess,
        &fenceHandle2,
        0,
        false,
        DUPLICATE_SAME_ACCESS
      );
      if (ok) {
        HRESULT hr = device->OpenSharedFence(fenceHandle2, __uuidof(ID3D11Fence), (void **)&clientFence);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          InfoQueueLog();
          getOut() << "server fence resource unpack failed " << (void *)hr << " " << (void *)fenceHandle << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to duplicate fence handle " << GetLastError() << std::endl;
      }
      
      CloseHandle(srcProcess);
      CloseHandle(dstProcess);
    }

    // render
    {
      int iEye = eEye == Eye_Left ? 0 : 1;

      context->Wait(clientFence, clientFenceValue);

      ID3D11ShaderResourceView *localShaderResourceViews[3] = {
        shaderResourceViews[index].first,
        shaderResourceViews[index].second,
        depthShaderFrontResourceViews[iEye]
      };
      float localTextureFulls[8] = {
        flip ? 1.0f : 0.0f,
        textureFull * iEye,
        0,
        0,
        0,
        0,
        0,
        0
      };
      context->UpdateSubresource(vsConstantBuffers[0], 0, 0, localTextureFulls, 0, 0);

      float localDepthColors[8] = {
        zbx,
        zby,
        (index <= 1) ? 1 : 0,
        0,
        (index <= 1) ? 0 : 1,
        1,
        0,
        0
      };
      context->UpdateSubresource(psConstantBuffers[1], 0, 0, localDepthColors, 0, 0);

      context->PSSetShaderResources(0, ARRAYSIZE(localShaderResourceViews), localShaderResourceViews);
      D3D11_VIEWPORT viewport{
        0, // TopLeftX,
        0, // TopLeftY,
        width, // Width,
        height, // Height,
        0, // MinDepth,
        1 // MaxDepth
      };
      context->RSSetViewports(1, &viewport);
      ID3D11RenderTargetView *localRenderTargetViews[2] = {
        renderTargetViews[iEye],
        renderTargetDepthBackViews[iEye]
      };
      context->OMSetRenderTargets(
        ARRAYSIZE(localRenderTargetViews),
        localRenderTargetViews,
        nullptr
      );
      context->DrawIndexed(6, 0, 0);
      // context->Draw(4, 0);
      
      {
        float depthColor[4] = {1, 0, 0, 0};
        context->ClearRenderTargetView(
          renderTargetDepthFrontViews[iEye],
          depthColor
        );

        auto temp1 = depthShaderFrontResourceViews[iEye];
        depthShaderFrontResourceViews[iEye] = depthShaderBackResourceViews[iEye];
        depthShaderBackResourceViews[iEye] = temp1;
        
        auto temp2 = renderTargetDepthFrontViews[iEye];
        renderTargetDepthFrontViews[iEye] = renderTargetDepthBackViews[iEye];
        renderTargetDepthBackViews[iEye] = temp2;
      }
    }

    ++fenceValue;
    context->Signal(fence.Get(), fenceValue);

    /* if (!fence) {
      ID3D11Resource *fenceResource;
      HRESULT hr = device->OpenSharedResource(fenceHandle, __uuidof(ID3D11Resource), (void**)(&fenceResource));

      getOut() << "submit server 8" << std::endl;

      if (SUCCEEDED(hr)) {
        hr = fenceResource->QueryInterface(__uuidof(ID3D11Fence), (void**)(&fence));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared fence: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to unpack shared fence handle: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
        abort();
      }
    } */

    // getOut() << "submit server 9 " << (void *)readEvent << std::endl;

    // auto r = WaitForSingleObject(readEvent, INFINITE);
    // ++fenceValue;
    // context->Wait(fence.Get(), fenceValue);
    
    // getOut() << "submit server 9" << std::endl;

    return std::tuple<uintptr_t, uintptr_t, uint64_t>((uintptr_t)GetCurrentProcessId(), (uintptr_t)fenceHandle, fenceValue);
  });
  fnp.reg<
    kIVRCompositor_FlushSubmit,
    int
  >([=]() {
    // getOut() << "flush submit server 1" << std::endl;

    for (int iEye = 0; iEye < ARRAYSIZE(EYES); iEye++) {
      EVREye eEye = EYES[iEye];

      Texture_t texture{
        (void *)shTexOuts[iEye],
        TextureType_DirectX,
        ColorSpace_Auto
      };
      VRTextureBounds_t bounds{
        0.0f, 0.0f,
        1.0f, 1.0f
      };
      // getOut() << "flush submit server 7 " << (int)eye << std::endl;
      // getOut() << "gl submit 2 " << glGetError() << std::endl;
      auto result = vrcompositor->Submit(eEye, &texture, &bounds, EVRSubmitFlags::Submit_Default);
      // getOut() << "compositor submit result " << (void *)result << std::endl;
    }
    
    vrcompositor->PostPresentHandoff();
    
    swapChain->Present(0, 0);

    // getOut() << "flush submit server 11" << std::endl;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >([=]() {
    vrcompositor->ClearLastSubmittedFrame();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_PostPresentHandoff,
    int
  >([=]() {
    // getOut() << "post present handoff server 1" << std::endl;
    vrcompositor->PostPresentHandoff();
    // getOut() << "post present handoff server 2" << std::endl;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, Compositor_FrameTiming>,
    uint32_t
  >([=](uint32_t unFramesAgo) {
    Compositor_FrameTiming timing;
    timing.m_nSize = sizeof(Compositor_FrameTiming);
    // getOut() << "server get frame timing 1" << std::endl;
    // managed_binary<Compositor_FrameTiming> timing(1);
    bool result = vrcompositor->GetFrameTiming(&timing, unFramesAgo);
    // getOut() << "server get frame timing 2" << std::endl;
    return std::tuple<bool, Compositor_FrameTiming>(
      result,
      timing
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >([=](int32_t nFrames) {
    managed_binary<Compositor_FrameTiming> timings(nFrames);
    for (uint32_t i = 0; i < nFrames; i++) {
      timings.data()[i].m_nSize = sizeof(Compositor_FrameTiming);
    }
    uint32_t result = vrcompositor->GetFrameTimings(timings.data(), nFrames);
    return std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>(
      result,
      std::move(timings)
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimeRemaining,
    float
  >([=]() {
    return vrcompositor->GetFrameTimeRemaining();
  });
  fnp.reg<
    kIVRCompositor_GetCumulativeStats,
    managed_binary<Compositor_CumulativeStats>,
    uint32_t
  >([=](uint32_t nStatsSizeInBytes) {
    managed_binary<Compositor_CumulativeStats> stats(1);

    vrcompositor->GetCumulativeStats(stats.data(), nStatsSizeInBytes);

    return std::move(stats);
  });
  fnp.reg<
    kIVRCompositor_FadeToColor,
    int,
    float,
    float,
    float,
    float,
    float,
    bool
  >([=](float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) {
    vrcompositor->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetCurrentFadeColor,
    managed_binary<HmdColor_t>,
    bool
  >([=](bool bBackground) {
    managed_binary<HmdColor_t> result(1);

    *result.data() = vrcompositor->GetCurrentFadeColor(bBackground);
    
    return std::move(result);
  });
  fnp.reg<
    kIVRCompositor_FadeGrid,
    int,
    float,
    bool
  >([=](float fSeconds, bool bFadeIn) {
    vrcompositor->FadeGrid(fSeconds, bFadeIn);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetCurrentGridAlpha,
    float
  >([=]() {
    return vrcompositor->GetCurrentGridAlpha();
  });
  fnp.reg<
    kIVRCompositor_ClearSkyboxOverride,
    int
  >([=]() {
    vrcompositor->ClearSkyboxOverride();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorBringToFront,
    int
  >([=]() {
    vrcompositor->CompositorBringToFront();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorGoToBack,
    int
  >([=]() {
    vrcompositor->CompositorGoToBack();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorQuit,
    int
  >([=]() {
    vrcompositor->CompositorQuit();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_IsFullscreen,
    bool
  >([=]() {
    return vrcompositor->IsFullscreen();
  });
  fnp.reg<
    kIVRCompositor_GetCurrentSceneFocusProcess,
    uint32_t
  >([=]() {
    return vrcompositor->GetCurrentSceneFocusProcess();
  });
  fnp.reg<
    kIVRCompositor_GetLastFrameRenderer,
    uint32_t
  >([=]() {
    return vrcompositor->GetLastFrameRenderer();
  });
  fnp.reg<
    kIVRCompositor_CanRenderScene,
    bool
  >([=]() {
    return vrcompositor->CanRenderScene();
  });
  fnp.reg<
    kIVRCompositor_ShowMirrorWindow,
    int
  >([=]() {
    vrcompositor->ShowMirrorWindow();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_HideMirrorWindow,
    int
  >([=]() {
    vrcompositor->HideMirrorWindow();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_IsMirrorWindowVisible,
    bool
  >([=]() {
    return vrcompositor->IsMirrorWindowVisible();
  });
  fnp.reg<
    kIVRCompositor_CompositorDumpImages,
    int
  >([=]() {
    vrcompositor->CompositorDumpImages();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    bool
  >([=]() {
    return vrcompositor->ShouldAppRenderWithLowResources();
  });
  fnp.reg<
    kIVRCompositor_ForceInterleavedReprojectionOn,
    int,
    bool
  >([=](bool bOverride) {
    vrcompositor->ForceInterleavedReprojectionOn(bOverride);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ForceReconnectProcess,
    int
  >([=]() {
    getOut() << "ForceReconnectProcess" << std::endl;
    abort();
    // vrcompositor->ForceReconnectProcess();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_SuspendRendering,
    int,
    bool
  >([=](bool bSuspend) {
    // vrcompositor->SuspendRendering(bSuspend);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "GetMirrorTextureD3D11" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "ReleaseMirrorTextureD3D11" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureGL,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "GetMirrorTextureGL" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseSharedGLTexture,
    bool
  >([=]() {
    getOut() << "ReleaseSharedGLTexture" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_LockGLSharedTextureForAccess,
    bool
  >([=]() {
    getOut() << "LockGLSharedTextureForAccess" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_UnlockGLSharedTextureForAccess,
    bool
  >([=]() {
    getOut() << "UnlockGLSharedTextureForAccess" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanInstanceExtensionsRequired,
    uint32_t
  >([=]() {
    getOut() << "GetVulkanInstanceExtensionsRequired" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanDeviceExtensionsRequired,
    uint32_t
  >([=]() {
    getOut() << "GetVulkanDeviceExtensionsRequired" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_SetExplicitTimingMode,
    int,
    EVRCompositorTimingMode
  >([=](EVRCompositorTimingMode eTimingMode) {
    vrcompositor->SetExplicitTimingMode(eTimingMode);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_SubmitExplicitTimingData,
    EVRCompositorError
  >([=]() {
    return vrcompositor->SubmitExplicitTimingData();
  });
  fnp.reg<
    kIVRCompositor_IsMotionSmoothingEnabled,
    bool
  >([=]() {
    return vrcompositor->IsMotionSmoothingEnabled();
  });
  fnp.reg<
    kIVRCompositor_IsMotionSmoothingSupported,
    bool
  >([=]() {
    return vrcompositor->IsMotionSmoothingSupported();
  });
  fnp.reg<
    kIVRCompositor_IsCurrentSceneFocusAppLoading,
    bool
  >([=]() {
    return vrcompositor->IsCurrentSceneFocusAppLoading();
  });
}
void PVRCompositor::SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) {
  fnp.call<kIVRCompositor_SetTrackingSpace, int, ETrackingUniverseOrigin>(eOrigin);
}
ETrackingUniverseOrigin PVRCompositor::GetTrackingSpace() {
  return fnp.call<kIVRCompositor_GetTrackingSpace, ETrackingUniverseOrigin>();
}
EVRCompositorError PVRCompositor::WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  getOut() << "wait get poses" << std::endl;
  
  InfoQueueLog();
  
  // hijacker.flushTextureLatches();
  
  // (*pFrameCount)++;
  
  auto result = fnp.call<
    kIVRCompositor_WaitGetPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  // getOut() << "proxy wait get poses 1 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(TrackedDevicePose_t));
  // getOut() << "proxy wait get poses 2 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(TrackedDevicePose_t));
  // getOut() << "proxy wait get poses 3 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  // auto start = std::chrono::high_resolution_clock::now();
  auto result = fnp.call<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  /* auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  getOut() << "get last poses call " << elapsed.count() << std::endl;  */
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(TrackedDevicePose_t));
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(TrackedDevicePose_t));
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) {
  auto result = fnp.call<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >(unDeviceIndex);
  *pOutputPose = *std::get<1>(result).data();
  *pOutputGamePose = *std::get<2>(result).data();
  return std::get<0>(result);
}
void PVRCompositor::PrepareSubmit(const Texture_t *pTexture) {
  // getOut() << "prepare submit client 1" << std::endl;

  HRESULT hr;
  if (!device) {
    if (pTexture->eType == ETextureType::TextureType_DirectX) {
      // getOut() << "prepare submit client 2.1" << std::endl;
      ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
      
      // getOut() << "initial tex 1" << std::endl;
      
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      tex->GetDevice(&deviceBasic);

      // getOut() << "initial tex 2" << std::endl;
      
      hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
      // getOut() << "initial tex 3 " << (void *)device.Get() << std::endl;
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "device query failed" << std::endl;
        abort();
      }

      hr = deviceBasic->QueryInterface(__uuidof(ID3D11InfoQueue), (void **)&infoQueue);
      if (SUCCEEDED(hr)) {
        infoQueue->PushEmptyStorageFilter();
      } else {
        getOut() << "info queue query failed" << std::endl;
        // abort();
      }
      
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;
      device->GetImmediateContext(&contextBasic);
      hijacker.hijackDx(contextBasic.Get());

      Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
      device->GetImmediateContext3(&context3);
      hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      }
      
      // getOut() << "initial tex 7 " << (void *)context.Get() << std::endl;
    } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      {
        glewExperimental = true;
        auto result2 = glewInit();
        // getOut() << "get p " << (void *)wglDXOpenDeviceNV << std::endl;
        if (result2 == GLEW_OK) {
          // nothing
        } else {
          const GLubyte *errorString = glewGetErrorString(result2);
          getOut() << "failed to initialize glew: " << (void *)result2 << " " << errorString << std::endl;
          // abort();
        }
      }
      {
        // getOut() << "init program 1" << std::endl;
        
        GLint oldProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
        GLint oldVao;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVao);
        GLint oldArrayBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldArrayBuffer);
        
        // getOut() << "init program 2.0 " << glGetString(GL_VERSION) << std::endl;

        glGenVertexArrays(1, &blitVao);
        // getOut() << "init program 2.1 " << blitVao << std::endl;
        glBindVertexArray(blitVao);
        
        // getOut() << "init program 3" << std::endl;

        // vertex shader
        GLuint composeVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(composeVertex, 1, &composeVsh, NULL);
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

        // getOut() << "init program 4" << std::endl;

        // fragment shader
        GLuint composeFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(composeFragment, 1, &blitFsh, NULL);
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
        
        // getOut() << "init program 5" << std::endl;

        // shader program
        blitProgram = glCreateProgram();
        glAttachShader(blitProgram, composeVertex);
        glAttachShader(blitProgram, composeFragment);
        glLinkProgram(blitProgram);
        glGetProgramiv(blitProgram, GL_LINK_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(blitProgram, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "blit program linking failed\n" << infoLog << std::endl;
          abort();
        }
        
        // getOut() << "init program 6" << std::endl;

        GLuint positionLocation = glGetAttribLocation(blitProgram, "position");
        if (positionLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'position'" << std::endl;
          abort();
        }
        // getOut() << "prepare submit server 13" << std::endl;
        GLuint uvLocation = glGetAttribLocation(blitProgram, "uv");
        if (uvLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'uv'" << std::endl;
          abort();
        }

        // getOut() << "init program 6" << std::endl;

        std::string texString = std::string("tex");
        GLuint texLocation = glGetUniformLocation(blitProgram, texString.c_str());
        // getOut() << "get location 1  " << texString << " " << texLocation << std::endl;
        if (texLocation != -1) {
          // 
        } else {
          getOut() << "blit program failed to get uniform location for '" << texString << "'" << std::endl;
          abort();
        }
        
        // getOut() << "init program 7" << std::endl;

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(composeVertex);
        glDeleteShader(composeFragment);

        glUseProgram(blitProgram);

        GLuint positionBuffer;
        glGenBuffers(1, &positionBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
        static const float positions[] = {
          -1.0f, 1.0f,
          1.0f, 1.0f,
          -1.0f, -1.0f,
          1.0f, -1.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(positionLocation);
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

        // getOut() << "init program 9" << std::endl;

        GLuint indexBuffer;
        glGenBuffers(1, &indexBuffer);
        static const uint16_t indices[] = {0, 2, 1, 2, 3, 1};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glUniform1i(texLocation, 0);

        glBindVertexArray(oldVao);
        glUseProgram(oldProgram);
        glBindBuffer(GL_ARRAY_BUFFER, oldArrayBuffer);
      }

      // getOut() << "init program 10" << std::endl;

      int32_t adapterIndex;
      g_pvrsystem->GetDXGIOutputInfo(&adapterIndex);
      if (adapterIndex == -1) {
        adapterIndex = 0;
      }
      
      // getOut() << "init program 11" << std::endl;

      Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_factory;
      IDXGIAdapter *adapter;
      hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &dxgi_factory);
      dxgi_factory->EnumAdapters(adapterIndex, &adapter);

      // getOut() << "init program 12" << std::endl;

      // Microsoft::WRL::ComPtr<ID3D11Device> device;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;
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
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "opengl texture dx device creation failed " << (void *)hr << std::endl;
        abort();
      }
      
      hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "device query failed" << std::endl;
        abort();
      }

      Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
      device->GetImmediateContext3(&context3);
      hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      }
      
      hijacker.hijackDx(contextBasic.Get());

      /* {
        HMODULE module = LoadLibraryA("glew32.dll");
        wglDXOpenDeviceNV = reinterpret_cast<decltype(wglDXOpenDeviceNV)>(GetProcAddress(module, "__wglewDXOpenDeviceNV"));
        getOut() << "get p " << (void *)wglDXOpenDeviceNV << std::endl;
      } */

      // getOut() << "prepare submit client 2.7 " << (void *)wglDXOpenDeviceNV << " " << (void *)device.Get() << std::endl;

      hInteropDevice = wglDXOpenDeviceNV(device.Get());

      // getOut() << "prepare submit client 2.8" << std::endl;

      /* hr = contextBasic->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      } */

      /* scd.BufferCount = 1;                                    // one back buffer
      scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
      scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
      scd.OutputWindow = hWnd;                                // the window to be used
      scd.SampleDesc.Count = 4;                               // how many multisamples
      scd.Windowed = TRUE;                                    // windowed/full-screen mode

      HRESULT D3D11CreateDeviceAndSwapChain(
        &adapter, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        0, // Flags
        NULL, // pFeatureLevels
        0, // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        0, // pSwapChainDesc
        IDXGISwapChain             **ppSwapChain,
        ID3D11Device               **ppDevice,
        D3D_FEATURE_LEVEL          *pFeatureLevel,
        ID3D11DeviceContext        **ppImmediateContext
      ); */
    } else {
      getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
      abort();
    }
  }

  // getOut() << "prepare submit client 3" << std::endl;

  if (!fence) {
    hr = device->CreateFence(
      0, // value
      // D3D11_FENCE_FLAG_SHARED|D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER, // flags
      // D3D11_FENCE_FLAG_SHARED, // flags
      D3D11_FENCE_FLAG_SHARED, // flags
      __uuidof(ID3D11Fence), // interface
      (void **)&fence // out
    );
    if (SUCCEEDED(hr)) {
      // getOut() << "created fence " << (void *)fence << std::endl;
      // nothing
    } else {
      getOut() << "failed to create fence" << std::endl;
      abort();
    }

    /* hr = fence->CreateSharedHandle(
      NULL, // security attributes
      GENERIC_ALL, // access
      (std::string("Local\\OpenVrProxyFence") + std::to_string(eEye == Eye_Left ? 0 : 1)).c_str(), // name
      &clientFence // share handle
    ); */
    hr = fence->CreateSharedHandle(
      NULL, // security attributes
      GENERIC_ALL, // access
      NULL, // (std::string("Local\\OpenVrProxyFence") + std::to_string(eEye == Eye_Left ? 0 : 1)).c_str(), // name
      &fenceHandle // share handle
    );
    if (SUCCEEDED(hr)) {
      getOut() << "create shared fence handle " << (void *)fenceHandle << std::endl;
      // nothing
    } else {
      getOut() << "failed to create fence share handle" << std::endl;
      abort();
    }
    
    // context->Flush();
  }

  /*HANDLE newFenceHandle = */fnp.call<
    kIVRCompositor_PrepareSubmit,
    int,
    ETextureType
  >(pTexture->eType);
  /* if (newFenceHandle != fenceHandle) {
    getOut() << "new fence check 1 " << (void *)newFenceHandle << std::endl;

    // IDisplayDeviceInterop *interop;
    // device.As(&interop);

    hr = device->OpenSharedFence(newFenceHandle, __uuidof(ID3D11Fence), (void **)&fence);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "fence resource unpack failed 2 " << (void *)hr << std::endl;
      abort();
    }

    getOut() << "new fence check 2 " << (void *)newFenceHandle << std::endl;
    
    fenceHandle = newFenceHandle;
  } */
  // getOut() << "prepare submit client 4" << std::endl;
}
EVRCompositorError PVRCompositor::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags ) {
  // getOut() << "submit client 1 " << std::endl;

  /* if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    GLuint tex = (GLuint)pTexture->handle;

    // glBindTexture(GL_TEXTURE_2D, tex);
    GLint width, height;
    glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_HEIGHT, &height);
    // glBindTexture(GL_TEXTURE_2D, 0);

    getOut() << "got width height top " << width << " " << height << std::endl;
  } */

  auto key = std::pair<size_t, EVREye>(fnp.processId, eEye);
  auto iter = inFrontIndices.find(key);
  size_t index;
  if (iter != inFrontIndices.end()) {
    index = iter->second;
  } else {
    index = inDxTexs.size();
    inFrontIndices[key] = index;
    // iter = inFrontIndices.find(key);

    inDxTexs.resize(index+1, NULL);
    inDxDepthTexs.resize(index+1, NULL);
    // inDxDepthTexs2.resize(index+1, NULL);
    // inDxDepthTexs3.resize(index+1, NULL);
    inShDxShareHandles.resize(index+1, NULL);
    inShDepthDxShareHandles.resize(index+1, NULL);
    inClientZBufferParams.resize(index+1, std::tuple<float, float>{});
    // inShDepthDxEventIndexes.resize(index+1, 0);
    inTexLatches.resize(index+1, NULL);
    inDepthTexLatches.resize(index+1, NULL);
    interopTexs.resize(index+1, NULL);
    inReadInteropHandles.resize(index+1, NULL);
    // inReadEvents.resize(index+1, NULL);
  }
  
  // getOut() << "submit client 2" << std::endl;

  VRTextureBounds_t bounds;
  // getOut() << "submit client 23 " << bounds.size() << " " << (void *)pBounds << std::endl;
  if (pBounds) {
    bounds = *pBounds;
  } else {
    bounds = VRTextureBounds_t{
      0.0f, 0.0f,
      1.0f, 1.0f
    };
  }
  
  float uMin = std::min(bounds.uMin, bounds.uMax);
  float uMax = std::max(bounds.uMin, bounds.uMax);
  float vMin = std::min(bounds.vMin, bounds.vMax);
  float vMax = std::max(bounds.vMin, bounds.vMax);
  if (uMax - uMin == 0) {
    uMax = 1;
  }
  if (vMax - vMin == 0) {
    vMax = 1;
  }

  HRESULT hr;
  ID3D11Texture2D *&shTex = inDxTexs[index]; // shared dx texture
  ID3D11Texture2D *&shDepthTex = inDxDepthTexs[index]; // shared dx depth texture
  /// ID3D11Texture2D *&shDepthTex2 = inDxDepthTexs2[index]; // shared dx depth texture 2
  // ID3D11Texture2D *&shDepthTex3 = inDxDepthTexs3[index]; // shared dx depth texture 3
  HANDLE &sharedHandle = inShDxShareHandles[index]; // dx interop handle
  HANDLE &sharedDepthHandle = inShDepthDxShareHandles[index]; // dx depth interop handle
  std::tuple<float, float> &clientZBufferParams = inClientZBufferParams[index]; // dx depth interop handle
  // size_t &sharedDepthEventIndex = inShDepthDxEventIndexes[index]; // dx depth event index
  // HANDLE &readEvent = inReadEvents[index]; // fence event
  uintptr_t &textureLatched = inTexLatches[index]; // remembered attachemnt
  uintptr_t &depthTextureLatched = inDepthTexLatches[index]; // remembered depth attachemnt

  if (textureLatched != (uintptr_t)pTexture->handle) {
    if (textureLatched) {
      // XXX delete old resources
    }
    textureLatched = (uintptr_t)pTexture->handle;

    // compute rexture params
    D3D11_TEXTURE2D_DESC desc{};
    if (pTexture->eType == ETextureType::TextureType_DirectX) {
      ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);

      getOut() << "submit client dx " << uMin << " " << vMin << " " << uMax << " " << vMax << std::endl;

      tex->GetDesc(&desc);
      // getOut() << "old tex width " << desc.Width << " " << desc.Height << " " << (bounds.data()->uMax - bounds.data()->uMin) << " " << (bounds.data()->vMax - bounds.data()->vMin) << std::endl;
      width = desc.Width;
      height = desc.Height;
      desc.Width *= uMax - uMin;
      desc.Height *= vMax - vMin;
    } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint tex = (GLuint)pTexture->handle;

      getOut() << "submit client gl" << std::endl;

      // glBindTexture(GL_TEXTURE_2D, tex);
      // GLint width, height;
      glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_WIDTH, (GLint *)&width);
      glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_HEIGHT, (GLint *)&height);
      // glBindTexture(GL_TEXTURE_2D, 0);
      // getOut() << "got width frontend " << width << " " << height << std::endl;

      desc.Width = width * (uMax - uMin);
      desc.Height = height * (vMax - vMin);
      desc.ArraySize = 1;
      // desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      // desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
      desc.SampleDesc.Count = 1;
      desc.Usage = D3D11_USAGE_DEFAULT;
      // desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
      // desc.BindFlags = 40; // D3D11_BIND_DEPTH_STENCIL
      desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // D3D11_BIND_DEPTH_STENCIL
      // desc.MiscFlags = 0; //D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

      // XXX need to add the interop handle
    } else {
      getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
      abort();
    }

    // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;
    
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    getOut() << "shared tex flags " <<
      desc.Width << " " << desc.Height << " " <<
      desc.MipLevels << " " << desc.ArraySize << " " <<
      desc.SampleDesc.Count << " " << desc.SampleDesc.Quality << " " <<
      desc.Format << " " <<
      desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags <<
      std::endl;

    // getOut() << "submit client 5" << std::endl;

    hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTex
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
      InfoQueueLog();
      abort();
    }
    /* {
      std::string s("SharedTex");
      s += std::to_string((int)eEye);
      shTex->SetPrivateData(WKPDID_D3DDebugObjectName, s.size(), s.c_str());
    } */

    /* {
      D3D11_TEXTURE2D_DESC descDepth{};
      descDepth.Width = width;
      descDepth.Height = height;
      descDepth.MipLevels = 1;
      descDepth.ArraySize = 1;
      descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;// DXGI_FORMAT_R8G8B8A8_UNORM; // GL_DEPTH32F_STENCIL8
      descDepth.SampleDesc.Count = 1;
      descDepth.SampleDesc.Quality = 0;
      descDepth.Usage = D3D11_USAGE_DEFAULT;
      descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      descDepth.CPUAccessFlags = 0;
      descDepth.MiscFlags = 0;
      
      getOut() << "got shared depth desc " << descDepth.Width << " " << descDepth.Height << " " << descDepth.Format << " " << descDepth.Usage << " " << descDepth.BindFlags << " " << descDepth.CPUAccessFlags << " " << descDepth.MiscFlags << std::endl;

      hr = device->CreateTexture2D(
        &descDepth,
        NULL,
        &shDepthTex2
      );
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "failed to create shared depth texture: " << (void *)hr << std::endl;
        abort();
      }
    }
    {
      D3D11_TEXTURE2D_DESC descDepth{};
      descDepth.Width = width;
      descDepth.Height = height;
      descDepth.MipLevels = 1;
      descDepth.ArraySize = 1;
      descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
      descDepth.SampleDesc.Count = 1;
      descDepth.SampleDesc.Quality = 0;
      descDepth.Usage = D3D11_USAGE_STAGING;
      descDepth.BindFlags = 0;
      descDepth.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
      descDepth.MiscFlags = 0;

      hr = device->CreateTexture2D(
        &descDepth,
        NULL,
        &shDepthTex3
      );
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "failed to create shared depth texture: " << (void *)hr << std::endl;
        abort();
      }
    } */

    // getOut() << "get submit 6" << std::endl;

    // get gl interop for copying
    if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint &interopTex = interopTexs[index];
      HANDLE &readInteropHandle = inReadInteropHandles[index];
      
      // getOut() << "get submit 7.1" << std::endl;
      // checkError("get submit 7.1");

      glGenTextures(1, &interopTex);
      // getOut() << "get submit 7.2 " << (void *)hInteropDevice << std::endl;
      // checkError("get submit 7.2");
      readInteropHandle = wglDXRegisterObjectNV(hInteropDevice, shTex, interopTex, GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
      // getOut() << "get submit 7.3 " << (void *)readInteropHandle << std::endl;
      // checkError("get submit 7.3");
    }

    // getOut() << "get submit 8" << std::endl;

    // get share handles
    {
      IDXGIResource1 *shTexResource;
      hr = shTex->QueryInterface(__uuidof(IDXGIResource1), (void **)&shTexResource);
      // getOut() << "submit client 7" << std::endl;
      // IDXGIResource1 *pDXGIResource;
      // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

      if (SUCCEEDED(hr)) {
        // getOut() << "submit client 8" << std::endl;
        // getOut() << "submit client 7" << std::endl;
        hr = shTexResource->GetSharedHandle(&sharedHandle);
        // hr = shTexResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, NULL, &sharedHandle);

        // getOut() << "submit client 9" << std::endl;

        // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        if (SUCCEEDED(hr)) {
          // getOut() << "submit client 10" << std::endl;
          // shTexResource->Release();
          // getOut() << "submit client 11" << std::endl;
          // nothing
        } else {
          getOut() << "failed to get shared texture handle: " << (void *)hr << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to get shared texture: " << (void *)hr << std::endl;
        abort();
      }
    }
    
    // getOut() << "submit client 14" << std::endl;
  }
  
  // getOut() << "submit client 10" << std::endl;

  // getOut() << "submit client 11" << std::endl;

  /* uint32_t width = 1552;
  uint32_t height = 1552;
  D3D11_BOX srcBox;
  srcBox.left = pBounds->uMin * width;
  srcBox.right = pBounds->uMax * height;
  srcBox.top = pBounds->vMax * width;
  srcBox.bottom = pBounds->vMin * height;
  srcBox.front = 0;
  srcBox.back = 1;
  context->CopySubresourceRegion(shTex, 0, pBounds->uMin, pBounds->vMax, 0, tex, 0, &srcBox); */
  if (pTexture->eType == ETextureType::TextureType_DirectX) {
    // getOut() << "submit client 12" << std::endl;
    ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
    ProxyTexture &depthProxyTexture = hijacker.getDepthTextureMatching(tex);
    HANDLE &depthTexHandle = depthProxyTexture.texHandle;
    std::tuple<float, float> &localZBufferParams = depthProxyTexture.zBufferParams;
    // getOut() << "get matching depth tex " << (void *)depthTexHandle << " " << depthTexEventIndex << std::endl;
    /* {
      // getOut() << "get tex view" << std::endl;

      ID3D11Device *device2;
      ID3D11DeviceContext *context2;
      tex->GetDevice(&device2);
      device2->GetImmediateContext(&context2);
      
      ID3D11RenderTargetView *renderTargetViews[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
      ID3D11DepthStencilView *depthStencilViews[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
      context2->OMGetRenderTargets(ARRAYSIZE(renderTargetViews), renderTargetViews, depthStencilViews);

      ID3D11Resource *depthResource;
      depthStencilViews[0]->GetResource(&depthResource);
      hr = depthResource->QueryInterface(__uuidof(ID3D11Texture2D), (void **)&depthTex);
      if (SUCCEEDED(hr)) {
        // getOut() << "got resource ok" << std::endl;
      } else {
        getOut() << "got resource fail" << std::endl;
        abort();
        // D3D11_RESOURCE_DIMENSION dimension;
      }

      // D3D11_TEXTURE2D_DESC desc;
      // depthTex->GetDesc(&desc);
      // getOut() << "got source depth desc " << desc.Width << " " << desc.Height << " " << desc.Format << " " << desc.Usage << " " << desc.BindFlags << " " << desc.CPUAccessFlags << " " << desc.MiscFlags << std::endl;
      
      // for (uint32_t i = 0; i < ARRAYSIZE(depthStencilViews); i++) {
        // getOut() << "check depth " << i << " " << (void *)depthStencilViews[i] << std::endl;
      // }

      // D3D11_DEPTH_STENCIL_VIEW_DESC desc;
      // depthStencilViews[0]->GetDesc(&desc);
      // getOut() << "got desc " << desc.Format << " " << desc.ViewDimension << " " << desc.Flags << std::endl;
    }
    // getOut() << "got desc 2" << std::endl; */

    D3D11_BOX srcBox{
      width * uMin,
      height * vMin,
      0,
      width * uMax,
      height * vMax,
      1
    };
    context->CopySubresourceRegion(
      shTex,
      0,
      0,
      0,
      0,
      tex,
      0,
      &srcBox
    );
    if (depthTextureLatched != (uintptr_t)depthTexHandle) {
      if (depthTextureLatched) {
        // XXX delete old resources
      }
      depthTextureLatched = (uintptr_t)depthTexHandle;

      sharedDepthHandle = depthTexHandle;
      // sharedDepthEventIndex = depthTexEventIndex;
    }
    clientZBufferParams = localZBufferParams;

    /* context->CopyResource(
      shDepthTex,
      depthTex
    ); */

    /* context->CopySubresourceRegion(
      shDepthTex,
      0,
      0,
      0,
      0,
      depthTex,
      0,
      &srcBox
    );
    context->ResolveSubresource(
      shDepthTex2,
      0,
      depthTex,
      0,
      DXGI_FORMAT_D32_FLOAT_S8X24_UINT
    );
    context->CopyResource(
      shDepthTex3,
      shDepthTex2
    );
    // context->Flush();

    D3D11_TEXTURE2D_DESC descDepth;
    shDepthTex3->GetDesc(&descDepth);
    
    // getOut() << "copy resource " << uMin << " " << vMin << " " << uMax << " " << vMax << std::endl;

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    UINT subresource = 0;//D3D11CalcSubresource(0, 0, 0);
    hr = context->Map(shDepthTex3, subresource, D3D11_MAP_READ, 0, &mappedResource);
    if (SUCCEEDED(hr)) {
      // getOut() << "get tex data pointer " << (void *)mappedResource.pData << " " << mappedResource.RowPitch << std::endl;
      float value = 0;
      // uint32_t ticks = 0;
      const uint32_t pixelSize = 4*2;
      char *pData = (char *)mappedResource.pData;
      for (uint32_t j = 0; j < descDepth.Height; j++) {
        for (uint32_t i = 0; i < descDepth.Width; i++) {
          value += *((float *)(pData + j*mappedResource.RowPitch + i*pixelSize));
          // ticks++;
        }
      }
      getOut() << "got value " << value << std::endl;
    } else {
      getOut() << "depth tex map failed " << (void *)hr << std::endl;
    }
    context->Unmap(shDepthTex3, subresource); */
  } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    GLuint readTex = (GLuint)pTexture->handle;
    GLuint &interopTex = interopTexs[index];
    HANDLE &readInteropHandle = inReadInteropHandles[index];

    /* if (!shDepthTex) {
      // XXX create the depth texture here

      IDXGIResource1 *shDepthTexResource;
      hr = shDepthTex->QueryInterface(__uuidof(IDXGIResource1), (void **)&shDepthTexResource);
      // getOut() << "submit client 7" << std::endl;
      // IDXGIResource1 *pDXGIResource;
      // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

      if (SUCCEEDED(hr)) {
        // getOut() << "submit client 8" << std::endl;
        // getOut() << "submit client 7" << std::endl;
        hr = shDepthTexResource->GetSharedHandle(&sharedDepthHandle);
        // hr = shTexResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, NULL, &sharedHandle);

        // getOut() << "submit client 9" << std::endl;

        // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        if (SUCCEEDED(hr)) {
          // getOut() << "submit client 10" << std::endl;
          // shTexResource->Release();
          // getOut() << "submit client 11" << std::endl;
          // nothing
        } else {
          getOut() << "failed to get shared depth texture handle: " << (void *)hr << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to get shared depth texture: " << (void *)hr << std::endl;
        abort();
      }
      shDepthTexResource->Release();
    } */

    HANDLE objects[] = {
      readInteropHandle
    };
    bool lockOk = wglDXLockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
    // getOut() << "submit client 13" << std::endl;
    // checkError("submit client 13");
    if (lockOk) {
      GLint oldActiveTexture;
      glGetIntegerv(GL_ACTIVE_TEXTURE, &oldActiveTexture);
      glActiveTexture(GL_TEXTURE0);
      GLint oldTexture2d;
      glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture2d);
      glBindTexture(GL_TEXTURE_2D, readTex);

      GLint oldProgram;
      glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
      GLint oldVao;
      glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVao);
      GLint oldViewport[4];
      glGetIntegerv(GL_VIEWPORT, oldViewport);

      GLint oldReadFbo;
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &oldReadFbo);
      GLint oldDrawFbo;
      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &oldDrawFbo);

      // GLint width, height, internalFormat;
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_WIDTH, &width);
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_HEIGHT, &height);
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

      // getOut() << "got width height 3 " << (int)eEye << " " << readTex << " " << (void *)pBounds << " " << interopTex << " " << width << " " << height << " " << internalFormat << std::endl;

      // checkError("submit client 14");

      GLuint rwFbos[2];
      glGenFramebuffers(2, rwFbos);
      // GLuint &readFbo = rwFbos[0];
      // glBindFramebuffer(GL_READ_FRAMEBUFFER, readFbo);
      // glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, readTex, 0);
      GLuint &drawFbo = rwFbos[1];
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFbo);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, interopTex, 0);

      // checkError("submit client 16");

      // glBindTexture(GL_TEXTURE_2D, interopTex);

      // checkError("submit client 17");

      /* std::vector<unsigned char> data(4);
      glReadPixels(
        width/2,
        height/2,
        1,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data.data());

      checkError("submit client 17.1");

      getOut() << "got data " <<
        (int)data[0] << " " <<
        (int)data[1] << " " <<
        (int)data[2] << " " <<
        (int)data[3] << " " <<
        std::endl; */

      /* glCopyTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        0,
        0,
        width,
        height,
        0
      ); */
      // glClearColor(0.0, 0.0, 0.5, 1.0);
      // glClear(GL_COLOR_BUFFER_BIT);
      glBindVertexArray(blitVao);
      glUseProgram(blitProgram);
      
      // checkError("check error 1");
      
      glViewport(0, 0, width, height);
      glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_SHORT,
        (void *)0
      );

      // checkError("check error 2");

      /* glBlitFramebuffer(
        0,
        0,
        width/2,
        height/2,
        0,
        0,
        width/2,
        height/2,
        GL_COLOR_BUFFER_BIT,
        GL_LINEAR
      );
      // glFinish(); */

      // checkError("submit client 18");

      glBindVertexArray(oldVao);
      glUseProgram(oldProgram);
      glBindTexture(GL_TEXTURE_2D, oldTexture2d);
      glActiveTexture(oldActiveTexture);
      // glBindFramebuffer(GL_READ_FRAMEBUFFER, oldReadFbo);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, oldDrawFbo);
      glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
      // glReadBuffer(oldReadBuffer);
      glDeleteFramebuffers(ARRAYSIZE(rwFbos), rwFbos);

      // getOut() << "submit client 15" << std::endl;
      // checkError("submit client 19");
      bool unlockOk = wglDXUnlockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
      if (unlockOk) {
        // getOut() << "submit client 16" << std::endl;
        // checkError("submit client 20");
        // nothing
      } else {
        getOut() << "texture unlocking failed" << std::endl;
        abort();
      }
    } else {
      getOut() << "texture locking failed" << std::endl;
      abort();
    }
    // getOut() << "submit client 17" << std::endl;
  } else {
    getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
    abort();
  }

  ++fenceValue;
  context->Signal(fence.Get(), fenceValue);
  // context->Flush();

  // getOut() << "submit client 19 " << (void *)sharedHandle << " " << (void *)pTexture << std::endl;

  // checkError("submit client 21");

  managed_binary<Texture_t> sharedTexture(1);
  *sharedTexture.data() = Texture_t{
    (void *)sharedHandle,
    // pTexture->eType,
    ETextureType::TextureType_DirectX,
    EColorSpace::ColorSpace_Auto,
    // pTexture->eColorSpace
  };
  const bool flip = bounds.vMax < bounds.vMin;
  /* *bounds.data() = VRTextureBounds_t{
    0.0f, flip ? 1.0f : 0.0f,
    1.0f, flip ? 0.0f : 1.0f
  }; */

  getOut() << "client submit 1 " << flip << " " << std::get<0>(clientZBufferParams) << " " << std::get<1>(clientZBufferParams) << std::endl;

  auto result = fnp.call<
    kIVRCompositor_Submit,
    std::tuple<uintptr_t, uintptr_t, uint64_t>,
    EVREye,
    managed_binary<Texture_t>,
    bool,
    EVRSubmitFlags,
    std::tuple<uintptr_t, float, float>,
    std::tuple<uintptr_t, uintptr_t, uint64_t>
  >(
    eEye,
    std::move(sharedTexture),
    flip,
    EVRSubmitFlags::Submit_Default,
    std::tuple<uintptr_t, float, float>(
      (uintptr_t)sharedDepthHandle,
      std::get<0>(clientZBufferParams),
      std::get<1>(clientZBufferParams)
    ),
    std::tuple<uintptr_t, uintptr_t, uint64_t>(
      (uintptr_t)GetCurrentProcessId(),
      (uintptr_t)fenceHandle,
      fenceValue
    )
  );
  // getOut() << "client submit 2" << std::endl;
  DWORD serverProcessId = std::get<0>(result);
  HANDLE serverFenceHandle = (HANDLE)std::get<1>(result);
  uint64_t serverFenceValue = std::get<2>(result);
  
  if (!remoteServerFence) {
    // getOut() << "open remote server fence " << (void *)serverProcessId << " " << (void *)serverFenceHandle << " " << (void *)serverFenceValue << std::endl;

    HANDLE srcProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, serverProcessId);
    HANDLE dstProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, GetCurrentProcessId());
    
    HANDLE fenceHandle2;
    BOOL ok = DuplicateHandle(
      srcProcess,
      serverFenceHandle,
      dstProcess,
      &fenceHandle2,
      0,
      false,
      DUPLICATE_SAME_ACCESS
    );
    if (ok) {
      HRESULT hr = device->OpenSharedFence(fenceHandle2, __uuidof(ID3D11Fence), (void **)&remoteServerFence);
      if (SUCCEEDED(hr)) {
        // nothing
        getOut() << "got server fence handle ok " << std::endl;
      } else {
        InfoQueueLog();
        getOut() << "remote server fence resource unpack failed " << (void *)hr << " " << (void *)fenceHandle2 << std::endl;
        abort();
      }
    } else {
      getOut() << "failed to duplicate fence handle " << GetLastError() << std::endl;
    }
    
    CloseHandle(srcProcess);
    CloseHandle(dstProcess);
  }
  
  context->Wait(remoteServerFence, serverFenceValue);

  // getOut() << "submit client 23" << std::endl;

  return VRCompositorError_None;
}
void PVRCompositor::FlushSubmit() {
  // getOut() << "flush submit client 1" << std::endl;
  fnp.call<
    kIVRCompositor_FlushSubmit,
    int
  >();
  // getOut() << "flush submit client 2" << std::endl;
}
void PVRCompositor::ClearLastSubmittedFrame() {
  fnp.call<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >();
}
void PVRCompositor::PostPresentHandoff() {
  // getOut() << "post present handoff client 1" << std::endl;
  fnp.call<
    kIVRCompositor_PostPresentHandoff,
    int
  >();
  // getOut() << "post present handoff client 2" << std::endl;
}
bool PVRCompositor::GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo ) {
  auto result = fnp.call<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, Compositor_FrameTiming>,
    uint32_t
  >(unFramesAgo);
  memcpy(pTiming, &std::get<1>(result), pTiming->m_nSize);

  /* getOut() << "get frame timing " <<
    std::get<1>(result).m_nSize << " " <<
    std::get<1>(result).m_nFrameIndex << " " <<
    std::get<1>(result).m_nNumFramePresents << " " <<
    std::get<1>(result).m_nNumMisPresented << " " <<
    std::get<1>(result).m_nNumDroppedFrames << " " <<
    std::get<1>(result).m_nReprojectionFlags << " " <<
    std::get<1>(result).m_flSystemTimeInSeconds << " " <<

    std::get<1>(result).m_flPreSubmitGpuMs << " " <<
    std::get<1>(result).m_flPostSubmitGpuMs << " " <<
    std::get<1>(result).m_flTotalRenderGpuMs << " " <<
    std::get<1>(result).m_flCompositorRenderGpuMs << " " <<
    std::get<1>(result).m_flCompositorRenderCpuMs << " " <<
    std::get<1>(result).m_flCompositorIdleCpuMs << " " <<

    std::get<1>(result).m_flClientFrameIntervalMs << " " <<
    std::get<1>(result).m_flPresentCallCpuMs << " " <<
    std::get<1>(result).m_flWaitForPresentCpuMs << " " <<
    std::get<1>(result).m_flSubmitFrameMs << " " <<

    std::get<1>(result).m_flWaitGetPosesCalledMs << " " <<
    std::get<1>(result).m_flNewPosesReadyMs << " " <<
    std::get<1>(result).m_flNewFrameReadyMs << " " <<
    std::get<1>(result).m_flCompositorUpdateStartMs << " " <<
    std::get<1>(result).m_flCompositorUpdateEndMs << " " <<
    std::get<1>(result).m_flCompositorRenderStartMs << " " <<

    // m_HmdPose << " " <<

    std::get<1>(result).m_nNumVSyncsReadyForUse << " " <<
    std::get<1>(result).m_nNumVSyncsToFirstView << " " <<
    std::endl; */

  return std::get<0>(result);
}
uint32_t PVRCompositor::GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
  auto result = fnp.call<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >(nFrames);
  uint32_t numResults = std::get<0>(result);
  for (uint32_t i = 0; i < numResults; i++) {
    memcpy(pTiming, std::get<1>(result).data(), pTiming->m_nSize);
    pTiming = (Compositor_FrameTiming *)(((char *)pTiming) + pTiming->m_nSize);
  }
  return numResults;
}
float PVRCompositor::GetFrameTimeRemaining() {
  return fnp.call<
    kIVRCompositor_GetFrameTimeRemaining,
    float
  >();
}
void PVRCompositor::GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) {
  auto result = fnp.call<
    kIVRCompositor_GetCumulativeStats,
    managed_binary<Compositor_CumulativeStats>,
    uint32_t
  >(nStatsSizeInBytes);
  *pStats = *result.data();
}
void PVRCompositor::FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground ) {
  fnp.call<
    kIVRCompositor_FadeToColor,
    int,
    float,
    float,
    float,
    float,
    float,
    bool
  >(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}
HmdColor_t PVRCompositor::GetCurrentFadeColor( bool bBackground ) {
  auto result = fnp.call<
    kIVRCompositor_GetCurrentFadeColor,
    managed_binary<HmdColor_t>,
    bool
  >(bBackground);
  return *result.data();
}
void PVRCompositor::FadeGrid( float fSeconds, bool bFadeIn ) {
  fnp.call<
    kIVRCompositor_FadeGrid,
    int,
    float,
    bool
  >(fSeconds, bFadeIn);
}
float PVRCompositor::GetCurrentGridAlpha() {
  return fnp.call<
    kIVRCompositor_GetCurrentGridAlpha,
    float
  >();
}
EVRCompositorError PVRCompositor::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) {
  getOut() << "SetSkyboxOverride not implemented" << std::endl;
  return VRCompositorError_None;
}
void PVRCompositor::ClearSkyboxOverride() {
  fnp.call<
    kIVRCompositor_ClearSkyboxOverride,
    int
  >();
}
void PVRCompositor::CompositorBringToFront() {
  fnp.call<
    kIVRCompositor_CompositorBringToFront,
    int
  >();
}
void PVRCompositor::CompositorGoToBack() {
  fnp.call<
    kIVRCompositor_CompositorGoToBack,
    int
  >();
}
void PVRCompositor::CompositorQuit() {
  fnp.call<
    kIVRCompositor_CompositorQuit,
    int
  >();
}
bool PVRCompositor::IsFullscreen() {
  return fnp.call<
    kIVRCompositor_IsFullscreen,
    bool
  >();
}
uint32_t PVRCompositor::GetCurrentSceneFocusProcess() {
  return fnp.call<
    kIVRCompositor_GetCurrentSceneFocusProcess,
    uint32_t
  >();
}
uint32_t PVRCompositor::GetLastFrameRenderer() {
  return fnp.call<
    kIVRCompositor_GetLastFrameRenderer,
    uint32_t
  >();
}
bool PVRCompositor::CanRenderScene() {
  return fnp.call<
    kIVRCompositor_CanRenderScene,
    bool
  >();
}
void PVRCompositor::ShowMirrorWindow() {
  fnp.call<
    kIVRCompositor_ShowMirrorWindow,
    int
  >();
}
void PVRCompositor::HideMirrorWindow() {
  fnp.call<
    kIVRCompositor_HideMirrorWindow,
    int
  >();
}
bool PVRCompositor::IsMirrorWindowVisible() {
  return fnp.call<
    kIVRCompositor_IsMirrorWindowVisible,
    int
  >();
}
void PVRCompositor::CompositorDumpImages() {
  fnp.call<
    kIVRCompositor_CompositorDumpImages,
    int
  >();
}
bool PVRCompositor::ShouldAppRenderWithLowResources() {
  return fnp.call<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    bool
  >();
}
void PVRCompositor::ForceInterleavedReprojectionOn( bool bOverride ) {
  fnp.call<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    int,
    bool
  >(bOverride);
}
void PVRCompositor::ForceReconnectProcess() {
  fnp.call<
    kIVRCompositor_ForceReconnectProcess,
    int
  >();
}
void PVRCompositor::SuspendRendering( bool bSuspend ) {
  fnp.call<
    kIVRCompositor_SuspendRendering,
    int,
    bool
  >(bSuspend);
}
vr::EVRCompositorError PVRCompositor::GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) {
  abort();
  return VRCompositorError_None;
}
void PVRCompositor::ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) {
  abort();
}
vr::EVRCompositorError PVRCompositor::GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) {
  abort();
  return VRCompositorError_None;
}
bool PVRCompositor::ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
  return false;
}
void PVRCompositor::LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
}
void PVRCompositor::UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
}
uint32_t PVRCompositor::GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
  abort();
  return 0;
}
uint32_t PVRCompositor::GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
  abort();
  return 0;
}
void PVRCompositor::SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) {
  fnp.call<
    kIVRCompositor_SetExplicitTimingMode,
    int,
    EVRCompositorTimingMode
  >(eTimingMode);
}
EVRCompositorError PVRCompositor::SubmitExplicitTimingData() {
  return fnp.call<
    kIVRCompositor_SubmitExplicitTimingData,
    EVRCompositorError
  >();
}
bool PVRCompositor::IsMotionSmoothingEnabled() {
  return fnp.call<
    kIVRCompositor_IsMotionSmoothingEnabled,
    bool
  >();
}
bool PVRCompositor::IsMotionSmoothingSupported() {
  return fnp.call<
    kIVRCompositor_IsMotionSmoothingSupported,
    bool
  >();
}
bool PVRCompositor::IsCurrentSceneFocusAppLoading() {
  return fnp.call<
    kIVRCompositor_IsCurrentSceneFocusAppLoading,
    bool
  >();
}
void PVRCompositor::CacheWaitGetPoses() {
  // getOut() << "CacheWaitGetPoses 1" << std::endl;
  EVRCompositorError error = vrcompositor->WaitGetPoses(cachedRenderPoses, ARRAYSIZE(cachedRenderPoses), cachedGamePoses, ARRAYSIZE(cachedGamePoses));
  // getOut() << "CacheWaitGetPoses 2" << std::endl;
  if (error != VRCompositorError_None) {
    getOut() << "compositor WaitGetPoses error: " << (void *)error << std::endl;
  }

  if (renderTargetViews.size() >= 2) {
    float color[4] = {0, 0, 0, 0};
    float depthColor[4] = {1, 0, 0, 0};
    for (int i = 0; i < 2; i++) {
      context->ClearRenderTargetView(
        renderTargetViews[i],
        color
      );
      context->ClearRenderTargetView(
        renderTargetDepthFrontViews[i],
        depthColor
      );
    }
  }
}
void PVRCompositor::InitShader() {
  float vertices[] = { // xyuv
    -1, -1, 0, 0,
    -1, 1, 0, 1,
    1, -1, 1, 0,
    1, 1, 1, 1
  };
  int indices[] = {
    0, 1, 2,
    3, 2, 1
  };

  getOut() << "init render 1" << std::endl;
  
  HRESULT hr;

  {
    D3D11_BUFFER_DESC bd{};
    D3D11_SUBRESOURCE_DATA InitData{};

    // ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(float) * (2+2) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    // ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    
    // ID3D11Buffer* vertexBuffer = nullptr;
    hr = device->CreateBuffer(&bd, &InitData, &vertexBuffer);
    if(FAILED(hr)) {
      getOut() << "Unable to create vertex buffer: " << (void *)hr << std::endl;
      abort();   
    }
    // m_VB.Set(vertexBuffer);
  }
  getOut() << "init render 2" << std::endl;
  {
    D3D11_BUFFER_DESC bd{};
    D3D11_SUBRESOURCE_DATA InitData{};

    // ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(int) * 6;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    // ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = indices;

    // ID3D11Buffer* indexBuffer = nullptr;
    hr = device->CreateBuffer(&bd, &InitData, &indexBuffer);
    if(FAILED(hr)) {
      getOut() << "Unable to create index buffer: " << (void *)hr << std::endl;
      abort();
    }
    // m_IB.Set(indexBuffer);
  }
  g_vrsystem->GetRecommendedRenderTargetSize(&width, &height);
  getOut() << "init render 3 " << width << " " << height << std::endl;
  vsConstantBuffers.resize(1);
  psConstantBuffers.resize(2);
  {
    D3D11_BUFFER_DESC cbDesc{};
    cbDesc.ByteWidth = 8 * sizeof(float);
    // cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // cbDesc.MiscFlags = 0;
    // cbDesc.StructureByteStride = 0;

    // x = -1+far/near
    // y = 1
    // z = x/far
    // w = 1/far

    // Create the buffer.
    hr = device->CreateBuffer(
      &cbDesc,
      NULL, 
      &vsConstantBuffers[0]
    );
    if (FAILED(hr)) {
      getOut() << "vs cbuf 1 create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  {
    float hw[] = {
      (float)width,
      (float)height,
      0,
      0,
      0,
      0,
      0,
      0
    };
    
    D3D11_BUFFER_DESC cbDesc{};
    cbDesc.ByteWidth = sizeof(hw);
    cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    // cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    // Fill in the subresource data.
    D3D11_SUBRESOURCE_DATA InitData{};
    InitData.pSysMem = hw;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    // Create the buffer.
    hr = device->CreateBuffer(
      &cbDesc,
      &InitData,
      &psConstantBuffers[0]
    );
    if (FAILED(hr)) {
      getOut() << "main cbuf create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  {
    D3D11_BUFFER_DESC cbDesc{};
    cbDesc.ByteWidth = 8 * sizeof(float);
    // cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // cbDesc.MiscFlags = 0;
    // cbDesc.StructureByteStride = 0;

    // Create the buffer.
    hr = device->CreateBuffer(
      &cbDesc,
      NULL, 
      &psConstantBuffers[1]
    );
    if (FAILED(hr)) {
      getOut() << "vs cbuf 1 create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  getOut() << "init render 4" << std::endl;
  {
    ID3DBlob *errorBlob = nullptr;
    hr = D3DCompile(
      hlsl,
      strlen(hlsl),
      "vs.hlsl",
      nullptr,
      D3D_COMPILE_STANDARD_FILE_INCLUDE,
      "vs_main",
      "vs_5_0",
      D3DCOMPILE_ENABLE_STRICTNESS,
      0,
      &vsBlob,
      &errorBlob
    );
    if (FAILED(hr)) {
      if (errorBlob != nullptr) {
        getOut() << "vs compilation failed: " << (char*)errorBlob->GetBufferPointer() << std::endl;
        abort();
      }
    }
    ID3D11ClassLinkage *linkage = nullptr;
    hr = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), linkage, &vsShader);
    if (FAILED(hr)) {
      getOut() << "vs create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  getOut() << "init render 5" << std::endl;
  {
    ID3DBlob *errorBlob = nullptr;
    hr = D3DCompile(
      hlsl,
      strlen(hlsl),
      "ps.hlsl",
      nullptr,
      D3D_COMPILE_STANDARD_FILE_INCLUDE,
      "ps_main",
      "ps_5_0",
      D3DCOMPILE_ENABLE_STRICTNESS,
      0,
      &psBlob,
      &errorBlob
    );
    getOut() << "init render 6" << std::endl;
    if (FAILED(hr)) {
      if (errorBlob != nullptr) {
        getOut() << "ps compilation failed: " << (char*)errorBlob->GetBufferPointer() << std::endl;
        abort();
      }
    }
    
    getOut() << "init render 7" << std::endl;

    ID3D11ClassLinkage *linkage = nullptr;
    hr = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), linkage, &psShader);
    if (FAILED(hr)) {
      getOut() << "ps create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  getOut() << "init render 8" << std::endl;
  {
    D3D11_INPUT_ELEMENT_DESC PositionTextureVertexLayout[] = {
      { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(PositionTextureVertexLayout);
    hr = device->CreateInputLayout(PositionTextureVertexLayout, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &vertexLayout);
  }
  getOut() << "init render 9" << std::endl;
  {
    context->VSSetShader(vsShader, nullptr, 0);
    context->PSSetShader(psShader, nullptr, 0);
    // context->PSSetSamplers(0, 1, &linearSampler);

    UINT stride = sizeof(float) * 4; // xyuv
    UINT offset = 0;
    // context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(vertexLayout);
    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->VSSetConstantBuffers(0, vsConstantBuffers.size(), vsConstantBuffers.data());
    context->PSSetConstantBuffers(0, psConstantBuffers.size(), psConstantBuffers.data());
  }
  getOut() << "init render 10" << std::endl;

  D3D11_TEXTURE2D_DESC desc{};
  desc.Width = width;
  desc.Height = height;
  desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_RENDER_TARGET;
  
  D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
  renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
  renderTargetViewDesc.Texture2D.MipSlice = 0;
  
  D3D11_TEXTURE2D_DESC depthDesc{};
  depthDesc.Width = width;
  depthDesc.Height = height;
  depthDesc.ArraySize = 1;
  depthDesc.Format = DXGI_FORMAT_R32_TYPELESS;
  depthDesc.SampleDesc.Count = 1;
  depthDesc.Usage = D3D11_USAGE_DEFAULT;
  depthDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

  D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDepthDesc{};
  renderTargetViewDepthDesc.Format = DXGI_FORMAT_R32_FLOAT;
  renderTargetViewDepthDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
  renderTargetViewDepthDesc.Texture2D.MipSlice = 0;

  D3D11_SHADER_RESOURCE_VIEW_DESC depthSrv{};
  depthSrv.Format = DXGI_FORMAT_R32_FLOAT;
  depthSrv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  depthSrv.Texture2D.MostDetailedMip = 0;
  depthSrv.Texture2D.MipLevels = 1;

  shTexOuts.resize(2);
  shDepthTexFrontOuts.resize(2);
  shDepthTexBackOuts.resize(2);
  renderTargetViews.resize(2);
  renderTargetDepthFrontViews.resize(2);
  renderTargetDepthBackViews.resize(2);
  depthShaderFrontResourceViews.resize(2);
  depthShaderBackResourceViews.resize(2);
  for (int i = 0; i < 2; i++) {
    hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTexOuts[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye texture: " << (void *)hr << std::endl;
      abort();
    }

    hr = device->CreateRenderTargetView(
      shTexOuts[i],
      &renderTargetViewDesc,
      &renderTargetViews[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye render target view: " << (void *)hr << std::endl;
      abort();
    }
    
    hr = device->CreateTexture2D(
      &depthDesc,
      NULL,
      &shDepthTexFrontOuts[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth texture: " << (void *)hr << std::endl;
      abort();
    }
    hr = device->CreateRenderTargetView(
      shDepthTexFrontOuts[i],
      &renderTargetViewDepthDesc,
      &renderTargetDepthFrontViews[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth render target front view: " << (void *)hr << std::endl;
      abort();
    }
    hr = device->CreateShaderResourceView(
      shDepthTexFrontOuts[i],
      &depthSrv,
      &depthShaderFrontResourceViews[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth shader resource front view: " << (void *)hr << std::endl;
      abort();
    }

    hr = device->CreateTexture2D(
      &depthDesc,
      NULL,
      &shDepthTexBackOuts[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth texture: " << (void *)hr << std::endl;
      abort();
    }
    hr = device->CreateRenderTargetView(
      shDepthTexBackOuts[i],
      &renderTargetViewDepthDesc,
      &renderTargetDepthBackViews[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth render target back view: " << (void *)hr << std::endl;
      abort();
    }
    hr = device->CreateShaderResourceView(
      shDepthTexBackOuts[i],
      &depthSrv,
      &depthShaderBackResourceViews[i]
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      InfoQueueLog();
      getOut() << "failed to create eye depth shader resource back view: " << (void *)hr << std::endl;
      abort();
    }
  }
  /* {
    D3D11_DEPTH_STENCIL_DESC dsDesc{};

    // Depth test parameters
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    // Stencil test parameters
    dsDesc.StencilEnable = false;

    // Create depth stencil state
    ID3D11DepthStencilState *pDSState;
    device->CreateDepthStencilState(&dsDesc, &pDSState);
    
    context->OMSetDepthStencilState(pDSState, 1);
  } */
}
void PVRCompositor::InfoQueueLog() {
  if (infoQueue) {
    UINT64 numStoredMessages = infoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
    for (UINT64 i = 0; i < numStoredMessages; i++) {
      size_t messageSize = 0;
      HRESULT hr = infoQueue->GetMessage(
        i,
        nullptr,
        &messageSize
      );
      if (SUCCEEDED(hr)) {
        D3D11_MESSAGE *message = (D3D11_MESSAGE *)malloc(messageSize);
        
        hr = infoQueue->GetMessage(
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
    infoQueue->ClearStoredMessages();
  }
}
}