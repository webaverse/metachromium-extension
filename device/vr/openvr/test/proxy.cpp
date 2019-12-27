#include "device/vr/openvr/test/proxy.h"

namespace vr {
char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";
char kIVRCompositor_GetTrackingSpace[] = "IVRCompositor::GetTrackingSpace";
char kIVRCompositor_WaitGetPoses[] = "IVRCompositor::WaitGetPoses";
char kIVRCompositor_GetLastPoses[] = "IVRCompositor::GetLastPoses";
char kIVRCompositor_GetLastPoseForTrackedDeviceIndex[] = "IVRCompositor::GetLastPoseForTrackedDeviceIndex";
char kIVRCompositor_Submit[] = "IVRCompositor::Submit";
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

PVRCompositor::PVRCompositor(IVRSystem *vrsystem, IVRCompositor *vrcompositor, FnProxy &fnp) : vrcompositor(vrcompositor), fnp(fnp) {
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
    std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    zpp::serializer::managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    zpp::serializer::managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

    EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

    return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
  });
  fnp.reg<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    zpp::serializer::managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    zpp::serializer::managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

    EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

    return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
  });
  fnp.reg<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >([=](TrackedDeviceIndex_t unDeviceIndex) {
    zpp::serializer::managed_binary<TrackedDevicePose_t> outputPose(1);
    zpp::serializer::managed_binary<TrackedDevicePose_t> gamePose(1);

    EVRCompositorError error = vrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, outputPose.data(), gamePose.data());

    return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(outputPose),
      std::move(gamePose)
    );
  });
  fnp.reg<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    zpp::serializer::binary<Texture_t>,
    zpp::serializer::binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >([=](EVREye eEye, zpp::serializer::binary<Texture_t> sharedTexture, zpp::serializer::binary<VRTextureBounds_t> bounds, EVRSubmitFlags submitFlags) {
    Texture_t *pTexture = sharedTexture.data();
    VRTextureBounds_t *pBounds = bounds.data();
    
    if (!device) {          
      IDXGIFactory *factory;
      HRESULT hr = CreateDXGIFactory(
        __uuidof(IDXGIFactory),
        (void **)(&factory)
      );
      
      if (SUCCEEDED(hr)) {
        int32_t adapterIndex;
        vrsystem->GetDXGIOutputInfo(&adapterIndex);
        
        if (adapterIndex != -1) {
          IDXGIAdapter *pAdapter;
          hr = factory->EnumAdapters(
            adapterIndex,
            &pAdapter
          );
          if (SUCCEEDED(hr)) {
            hr = D3D11CreateDevice(
              pAdapter,
              D3D_DRIVER_TYPE_REFERENCE,
              NULL,
              0,
              NULL,
              0,
              D3D11_SDK_VERSION,
              &device,
              NULL,
              &context
            );
            if (SUCCEEDED(hr)) {
              // nothing
            } else {
              getOut() << "failed to create device: " << (void *)hr << std::endl;
              abort();
            }
          } else {
            getOut() << "failed to get adapter: " << (void *)hr << std::endl;
            abort();
          }
        } else {
          getOut() << "failed to get adapter index" << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to create dxgi handle: " << (void *)hr << std::endl;
        abort();
      }
    }

    ID3D11Texture2D *&shTex = eEye == Eye_Left ? shTexLeft : shTexRight;
    if (!shTex) {
      HANDLE sharedHandle = (HANDLE)pTexture->handle;

      ID3D11Resource *pD3DResource;
      HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      
      if (SUCCEEDED(hr)) {
        hr = pD3DResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shTex));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared texture: " << (void *)hr << std::endl;
          abort();
        }

        pD3DResource->Release();
      } else {
        getOut() << "failed to unpack shared texture handle: " << (void *)hr << std::endl;
        abort();
      }
    }

    pTexture->handle = (void *)shTex;
    return vrcompositor->Submit(eEye, pTexture, pBounds, submitFlags);
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
    vrcompositor->PostPresentHandoff();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >([=](uint32_t unFramesAgo) {
    zpp::serializer::managed_binary<Compositor_FrameTiming> timing(1);

    bool result = vrcompositor->GetFrameTiming(timing.data(), unFramesAgo);

    return std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>(
      result,
      std::move(timing)
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >([=](uint32_t nFrames) {
    zpp::serializer::managed_binary<Compositor_FrameTiming> timings(nFrames);

    uint32_t result = vrcompositor->GetFrameTimings(timings.data(), nFrames);

    return std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>(
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
    zpp::serializer::managed_binary<Compositor_CumulativeStats>,
    uint32_t
  >([=](uint32_t nStatsSizeInBytes) {
    zpp::serializer::managed_binary<Compositor_CumulativeStats> stats(1);

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
    zpp::serializer::managed_binary<HmdColor_t>,
    bool
  >([=](bool bBackground) {
    zpp::serializer::managed_binary<HmdColor_t> result(1);

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
    vrcompositor->ForceReconnectProcess();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_SuspendRendering,
    int,
    bool
  >([=](bool bSuspend) {
    vrcompositor->SuspendRendering(bSuspend);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureGL,
    vr::EVRCompositorError
  >([=]() {
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseSharedGLTexture,
    bool
  >([=]() {
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_LockGLSharedTextureForAccess,
    bool
  >([=]() {
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_UnlockGLSharedTextureForAccess,
    bool
  >([=]() {
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanInstanceExtensionsRequired,
    uint32_t
  >([=]() {
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanInstanceExtensionsRequired,
    uint32_t
  >([=]() {
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanDeviceExtensionsRequired,
    uint32_t
  >([=]() {
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
  auto result = fnp.call<
    kIVRCompositor_WaitGetPoses,
    std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size_in_bytes());
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size_in_bytes());
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  auto result = fnp.call<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size_in_bytes());
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size_in_bytes());
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) {
  auto result = fnp.call<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >(unDeviceIndex);
  *pOutputPose = *std::get<1>(result).data();
  *pOutputGamePose = *std::get<2>(result).data();
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags ) {
  ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);

  if (!device) {
    tex->GetDevice(&device);
  }
  if (!context) {
    device->GetImmediateContext(&context);
  }

  ID3D11Texture2D *&shTex = eEye == Eye_Left ? shTexLeft : shTexRight;
  if (!shTex) {
    D3D11_TEXTURE2D_DESC desc;
    tex->GetDesc(&desc);

    // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;

    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    HRESULT hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTex
    );

    if (SUCCEEDED(hr)) {
      IDXGIResource *pDXGIResource;
      hr = shTex->QueryInterface(__uuidof(IDXGIResource), (void **)&pDXGIResource);
      // IDXGIResource1 *pDXGIResource;
      // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

      if (SUCCEEDED(hr)) {
        // getOut() << "succ 1 " << (void *)pDXGIResource << std::endl;
        HANDLE &sharedHandle = eEye == Eye_Left ? shTexLeftHandle : shTexRightHandle;
        hr = pDXGIResource->GetSharedHandle(&sharedHandle);
        // hr = pDXGIResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ, L"Local\\lol", &sharedHandle);

        // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to get shared texture handle: " << (void *)hr << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to get shared texture: " << (void *)hr << std::endl;
        abort();
      }
    } else {
      getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
      abort();
    }
  }

  context->CopyResource(shTex, tex);
  
  zpp::serializer::managed_binary<Texture_t> sharedTexture(1);
  *sharedTexture.data() = Texture_t{
    (void *)shTex,
    pTexture->eType,
    pTexture->eColorSpace
  };
  zpp::serializer::managed_binary<VRTextureBounds_t> bounds(1);
  *bounds.data() = *pBounds;
  return fnp.call<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    zpp::serializer::managed_binary<Texture_t>,
    zpp::serializer::managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >(eEye, std::move(sharedTexture), std::move(bounds), nSubmitFlags);
}
void PVRCompositor::ClearLastSubmittedFrame() {
  fnp.call<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >();
}
void PVRCompositor::PostPresentHandoff() {
  fnp.call<
    kIVRCompositor_PostPresentHandoff,
    int
  >();
}
bool PVRCompositor::GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo ) {
  auto result = fnp.call<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >(unFramesAgo);
  *pTiming = *std::get<1>(result).data();
  return std::get<0>(result);
}
uint32_t PVRCompositor::GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
  auto result = fnp.call<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >(nFrames);
  *pTiming = *std::get<1>(result).data();
  return std::get<0>(result);
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
    zpp::serializer::managed_binary<Compositor_CumulativeStats>,
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
    zpp::serializer::managed_binary<HmdColor_t>,
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
  abort();
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
}