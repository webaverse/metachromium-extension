// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 ..
msbuild  ALL_BUILD.vcxproj

cd C:\Users\avaer\AppData\Local\Chromium\Application
set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality"

C:\Windows\System32\cmd.exe /c "set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\ && set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\ && set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\ &&  C:\Program Files (x86)\Minecraft Launcher\MinecraftLauncher.exe"
*/

#include <chrono>
#include <thread>
#include <algorithm>

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <wrl.h>
#include <memory>

// #include "device/vr/openvr/test/test_helper.h"
// #include "device/vr/test/test_hook.h"
#include "device/vr/windows/d3d11_device_helpers.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "third_party/openvr/src/src/ivrclientcore.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"

#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/sample/hellovr_opengl_main.h"
#include "device/vr/OpenOVR/Reimpl/static_bases.gen.h"
// #include "device/vr/openvr/test/serializer.h"
#include "device/vr/openvr/test/fnproxy.h"

std::string dllDir;
std::ofstream out;
std::ostream &getOut() {
  if (!out.is_open()) {
    std::string logPath = dllDir + "log.txt";
    out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return out;
}

void externalOpenVr(std::function<void()> &&fn) {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  SetEnvironmentVariable("VR_OVERRIDE", "");

  fn();

  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
}

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
class PVRCompositor : public IVRCompositor {
public:
  IVRSystem *vrsystem;
  IVRCompositor *vrcompositor;
  FnProxy &fnp;
  
  /* Microsoft::WRL::ComPtr<ID3D11Device> device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context; */
  ID3D11Device *device;
  ID3D11DeviceContext *context;
  ID3D11Texture2D *shTexLeft = nullptr;
  ID3D11Texture2D *shTexRight = nullptr;
  HANDLE shTexLeftHandle = 0;
  HANDLE shTexRightHandle = 0;
  
  PVRCompositor(IVRSystem *vrsystem, IVRCompositor *vrcompositor, FnProxy &fnp) : vrcompositor(vrcompositor), fnp(fnp) {
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
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) {
    fnp.call<kIVRCompositor_SetTrackingSpace, int, ETrackingUniverseOrigin>(eOrigin);
  }
	virtual ETrackingUniverseOrigin GetTrackingSpace() {
    return fnp.call<kIVRCompositor_GetTrackingSpace, ETrackingUniverseOrigin>();
  }
	virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
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
	virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
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
	virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) {
    auto result = fnp.call<
      kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
      std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
      TrackedDeviceIndex_t
    >(unDeviceIndex);
    *pOutputPose = *std::get<1>(result).data();
    *pOutputGamePose = *std::get<2>(result).data();
    return std::get<0>(result);
  }
	virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) {
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
	virtual void ClearLastSubmittedFrame() {
    fnp.call<
      kIVRCompositor_ClearLastSubmittedFrame,
      int
    >();
  }
	virtual void PostPresentHandoff() {
    fnp.call<
      kIVRCompositor_PostPresentHandoff,
      int
    >();
  }
	virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) {
    auto result = fnp.call<
      kIVRCompositor_GetFrameTiming,
      std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >(unFramesAgo);
    *pTiming = *std::get<1>(result).data();
    return std::get<0>(result);
  }
	virtual uint32_t GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
    auto result = fnp.call<
      kIVRCompositor_GetFrameTimings,
      std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >(nFrames);
    *pTiming = *std::get<1>(result).data();
    return std::get<0>(result);
  }
	virtual float GetFrameTimeRemaining() {
    return fnp.call<
      kIVRCompositor_GetFrameTimeRemaining,
      float
    >();
  }
	virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) {
    auto result = fnp.call<
      kIVRCompositor_GetCumulativeStats,
      zpp::serializer::managed_binary<Compositor_CumulativeStats>,
      uint32_t
    >(nStatsSizeInBytes);
    *pStats = *result.data();
  }
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) {
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
	virtual HmdColor_t GetCurrentFadeColor( bool bBackground = false ) {
    auto result = fnp.call<
      kIVRCompositor_GetCurrentFadeColor,
      zpp::serializer::managed_binary<HmdColor_t>,
      bool
    >(bBackground);
    return *result.data();
  }
	virtual void FadeGrid( float fSeconds, bool bFadeIn ) {
    fnp.call<
      kIVRCompositor_FadeGrid,
      int,
      float,
      bool
    >(fSeconds, bFadeIn);
  }
	virtual float GetCurrentGridAlpha() {
    return fnp.call<
      kIVRCompositor_GetCurrentGridAlpha,
      float
    >();
  }
	virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) {
    abort();
    return VRCompositorError_None;
  }
	virtual void ClearSkyboxOverride() {
    fnp.call<
      kIVRCompositor_ClearSkyboxOverride,
      int
    >();
  }
	virtual void CompositorBringToFront() {
    fnp.call<
      kIVRCompositor_CompositorBringToFront,
      int
    >();
  }
	virtual void CompositorGoToBack() {
    fnp.call<
      kIVRCompositor_CompositorGoToBack,
      int
    >();
  }
	virtual void CompositorQuit() {
    fnp.call<
      kIVRCompositor_CompositorQuit,
      int
    >();
  }
	virtual bool IsFullscreen() {
    return fnp.call<
      kIVRCompositor_IsFullscreen,
      bool
    >();
  }
	virtual uint32_t GetCurrentSceneFocusProcess() {
    return fnp.call<
      kIVRCompositor_GetCurrentSceneFocusProcess,
      uint32_t
    >();
  }
  virtual uint32_t GetLastFrameRenderer() {
    return fnp.call<
      kIVRCompositor_GetLastFrameRenderer,
      uint32_t
    >();
  }
	virtual bool CanRenderScene() {
    return fnp.call<
      kIVRCompositor_CanRenderScene,
      bool
    >();
  }
	virtual void ShowMirrorWindow() {
    fnp.call<
      kIVRCompositor_ShowMirrorWindow,
      int
    >();
  }
	virtual void HideMirrorWindow() {
    fnp.call<
      kIVRCompositor_HideMirrorWindow,
      int
    >();
  }
	virtual bool IsMirrorWindowVisible() {
    return fnp.call<
      kIVRCompositor_IsMirrorWindowVisible,
      int
    >();
  }
	virtual void CompositorDumpImages() {
    fnp.call<
      kIVRCompositor_CompositorDumpImages,
      int
    >();
  }
	virtual bool ShouldAppRenderWithLowResources() {
    return fnp.call<
      kIVRCompositor_ShouldAppRenderWithLowResources,
      bool
    >();
  }
	virtual void ForceInterleavedReprojectionOn( bool bOverride ) {
    fnp.call<
      kIVRCompositor_ShouldAppRenderWithLowResources,
      int,
      bool
    >(bOverride);
  }
	virtual void ForceReconnectProcess() {
    fnp.call<
      kIVRCompositor_ForceReconnectProcess,
      int
    >();
  }
	virtual void SuspendRendering( bool bSuspend ) {
    fnp.call<
      kIVRCompositor_SuspendRendering,
      int,
      bool
    >(bSuspend);
  }
	virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) {
    abort();
    return VRCompositorError_None;
  }
	virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) {
    abort();
  }
	virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) {
    abort();
    return VRCompositorError_None;
  }
	virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) {
    abort();
    return false;
  }
	virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
    abort();
  }
	virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
    abort();
  }
	virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
    abort();
    return 0;
  }
	virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
    abort();
    return 0;
  }
	virtual void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) {
    fnp.call<
      kIVRCompositor_SetExplicitTimingMode,
      int,
      EVRCompositorTimingMode
    >(eTimingMode);
  }
	virtual EVRCompositorError SubmitExplicitTimingData() {
    return fnp.call<
      kIVRCompositor_SubmitExplicitTimingData,
      EVRCompositorError
    >();
  }
	virtual bool IsMotionSmoothingEnabled() {
    return fnp.call<
      kIVRCompositor_IsMotionSmoothingEnabled,
      bool
    >();
  }
	virtual bool IsMotionSmoothingSupported() {
    return fnp.call<
      kIVRCompositor_IsMotionSmoothingSupported,
      bool
    >();
  }
	virtual bool IsCurrentSceneFocusAppLoading() {
    return fnp.call<
      kIVRCompositor_IsCurrentSceneFocusAppLoading,
      bool
    >();
  }
};

IVRSystem *g_vrsystem = nullptr;
IVRCompositor *g_vrcompositor = nullptr;
IVRChaperone *g_vrchaperone = nullptr;
IVRChaperoneSetup *g_vrchaperonesetup = nullptr;
IVROverlay *g_vroverlay = nullptr;
IVRRenderModels *vr::g_vrrendermodels = nullptr;
IVRScreenshots *vr::g_vrscreenshots = nullptr;
IVRSettings *vr::g_vrsettings = nullptr;
IVRExtendedDisplay *vr::g_vrextendeddisplay = nullptr;
IVRApplications *vr::g_vrapplications = nullptr;
IVRInput *g_vrinput = nullptr;

PVRCompositor *g_pvrcompositor = nullptr;

}  // namespace vr

extern "C" {
  void *__imp_VR_GetGenericInterface = nullptr;
  void *__imp_VR_IsInterfaceVersionVersion = nullptr;
  void *__imp_VR_GetInitToken = nullptr;
  void *__imp_VR_IsInterfaceVersion = nullptr;
  void *__imp_VR_InitInternal2 = nullptr;
  void *__imp_VR_IsInterfaceVersionValid = nullptr;
  void *__imp_VR_ShutdownInternal = nullptr;
  void *__imp_VR_IsHmdPresent = nullptr;
  void *__imp_VR_GetVRInitErrorAsSymbol = nullptr;
  void *__imp_VR_GetVRInitErrorAsEnglishDescription = nullptr;
  
  __declspec(dllexport) void* VRClientCoreFactory(const char* interface_name, int* return_code) {
    getOut() << "core 0 " << std::endl;
    getOut() << "core 1 " << interface_name << std::endl;
    externalOpenVr([&]() -> void {
      vr::EVRInitError result = vr::VRInitError_None;

      getOut() << "core 2 " << interface_name << std::endl;

      // only look in the override
      std::string openvrApiDllPath = dllDir + "openvr_api.dll";
      void *pMod = SharedLib_Load(openvrApiDllPath.c_str());
      // dumpbin /exports "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\vrclient_x64.dll"
      // nothing more to do if we can't load the DLL
      getOut() << "core 3 " << pMod << std::endl;
      if( !pMod )
      {
        getOut() << "core abort" << std::endl; abort();
        // return vr::VRInitError_Init_VRClientDLLNotFound;
      }
      
      getOut() << "core 4 " << pMod << std::endl;

      __imp_VR_GetGenericInterface = SharedLib_GetFunction( pMod, "VR_GetGenericInterface" );
      __imp_VR_IsInterfaceVersionVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionVersion" );
      __imp_VR_GetInitToken = SharedLib_GetFunction( pMod, "VR_GetInitToken" );
      __imp_VR_IsInterfaceVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersion" );
      __imp_VR_InitInternal2 = SharedLib_GetFunction( pMod, "VR_InitInternal2" );
      __imp_VR_IsInterfaceVersionValid = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionValid" );
      __imp_VR_ShutdownInternal = SharedLib_GetFunction( pMod, "VR_ShutdownInternal" );
      __imp_VR_IsHmdPresent = SharedLib_GetFunction( pMod, "VR_IsHmdPresent" );
      __imp_VR_GetVRInitErrorAsSymbol = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsSymbol" );
      __imp_VR_GetVRInitErrorAsEnglishDescription = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsEnglishDescription" );
      getOut() << "core 5 " << pMod << " " << __imp_VR_GetGenericInterface << std::endl;
      if( !__imp_VR_GetGenericInterface )
      {
        SharedLib_Unload( pMod );
        getOut() << "unload abort" << std::endl; abort();
        // return vr::VRInitError_Init_FactoryNotFound;
      }
      
      getOut() << "core 6 " << pMod << " " << __imp_VR_GetGenericInterface << std::endl;

      /* int nReturnCode = 0;
      g_pHmdSystem = static_cast< IVRClientCore * > ( fnFactory( vr::IVRClientCore_Version, &nReturnCode ) );
      if( !g_pHmdSystem )
      {
        SharedLib_Unload( pMod );
        return vr::VRInitError_Init_InterfaceNotFound;
      } */
      
      vr::VR_Init(&result, vr::VRApplication_Scene);
      if (result == vr::VRInitError_None) {
        getOut() << "init 2" << std::endl;

        vr::g_vrsystem = vr::VRSystem();
        vr::g_vrcompositor = vr::VRCompositor();
        vr::g_vrchaperone = vr::VRChaperone();
        vr::g_vrchaperonesetup = vr::VRChaperoneSetup();
        vr::g_vroverlay = vr::VROverlay();
        vr::g_vrrendermodels = vr::VRRenderModels();
        vr::g_vrscreenshots = vr::VRScreenshots();
        vr::g_vrsettings = vr::VRSettings();
        vr::g_vrextendeddisplay = vr::VRExtendedDisplay();
        vr::g_vrapplications = vr::VRApplications();
        vr::g_vrinput = vr::VRInput();

        /* FnProxy fnp;
        vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrsystem, vr::g_vrcompositor, fnp); */

        result = vr::VRInitError_None;
        getOut() << "init 3" << std::endl;
      } else {
        getOut() << "init 4" << std::endl;
        // vr::VR_Shutdown();
        // getOut() << "init 4" << std::endl;
        result = vr::VRInitError_Unknown;
      }
      getOut() << "init 5" << std::endl;
    });
    getOut() << "init 6 " << interface_name << std::endl;
    void *iface = CreateInterfaceByName(interface_name);
    getOut() << "init 7 " << interface_name << " " << iface << std::endl;
    return iface;
  }
}

/* TCHAR processExe[4096] = TEXT("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\process.exe");
char lol[] = "lol";
char lol2[] = "lol2"; */
BOOL WINAPI DllMain(
  _In_ HINSTANCE hinstDLL,
  _In_ DWORD     fdwReason,
  _In_ LPVOID    lpvReserved
) {
  { 
    // getOut() << "loading paths" << std::endl;
    char dllPath[MAX_PATH];
    HMODULE hm = NULL;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR) &VRClientCoreFactory, &hm) == 0)
    {
        int ret = GetLastError();
        // getOut() << "GetModuleHandle failed, error = " << ret << std::endl;
        // Return or however you want to handle an error.
        getOut() << "dll abort 1" << std::endl; abort();
    }
    if (GetModuleFileName(hm, dllPath, sizeof(dllPath)) == 0)
    {
        int ret = GetLastError();
        // getOut() << "GetModuleFileName failed, error = " << ret << std::endl;
        getOut() << "dll abort 2" << std::endl; abort();
    }
    
    char drive[MAX_PATH];
    char dir[MAX_PATH];
    // char fname[MAX_PATH];
    // char ext[MAX_PATH];
    _splitpath(dllPath, drive, dir, nullptr, nullptr);
    dllDir = drive;
    dllDir += dir;
  }
  
  getOut() << "init dll 0" << std::endl;
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  getOut() << "init dll 1 " << buf.data() << std::endl;
  getOut() << "init dll 2 " << buf.data() << std::endl;
  
  return true;
}