#include "stdafx.h"
#define BASE_IMPL

// #include <chrono>
// #include "Misc/Config.h"

// #include "OVR_CAPI.h"
// #include "libovr_wrapper.h"
// #include "convert.h"

// #include "Extras/OVR_Math.h"
// using namespace OVR;

using namespace std;

#include "BaseCompositor.h"
#include "BaseOverlay.h"

// For the left and right hand constants - TODO move them to their own file
#include "BaseSystem.h"
#include "static_bases.gen.h"

// Need the LibOVR Vulkan headers for the GetVulkan[Device|Instance]ExtensionsRequired methods
/* #if defined(SUPPORT_VK)
#include "OVR_CAPI_Vk.h"
#endif
#if defined(SUPPORT_DX)
#include "OVR_CAPI_D3D.h"
#endif */

// #include "Misc/ScopeGuard.h"
// #include "Drivers/Backend.h"

using namespace vr;
using namespace IVRCompositor_022;

typedef int ovr_enum_t;

// #define SESS (*ovr::session

BaseCompositor::BaseCompositor() {
}

BaseCompositor::~BaseCompositor() {
}

void BaseCompositor::SetTrackingSpace(ETrackingUniverseOrigin eOrigin) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::SetTrackingSpace" << std::endl; });
  g_pvrcompositor->SetTrackingSpace(eOrigin);
}

ETrackingUniverseOrigin BaseCompositor::GetTrackingSpace() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetTrackingSpace" << std::endl; });
  return g_pvrcompositor->GetTrackingSpace();
}

ovr_enum_t BaseCompositor::WaitGetPoses(TrackedDevicePose_t * renderPoseArray, uint32_t renderPoseArrayCount,
	  TrackedDevicePose_t * gamePoseArray, uint32_t gamePoseArrayCount) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::WaitGetPoses" << std::endl; });
  // getOut() << "base wait get poses 1" << std::endl;
  bool doRealWait;
  g_pvrclientcore->PreWaitGetPoses(&doRealWait);
  auto result = doRealWait ?
    g_pvrcompositor->WaitGetPoses(renderPoseArray, renderPoseArrayCount, gamePoseArray, gamePoseArrayCount)
  :
    g_pvrcompositor->GetLastPoses(renderPoseArray, renderPoseArrayCount, gamePoseArray, gamePoseArrayCount);
  g_pvrclientcore->PostWaitGetPoses();
  return result;
  // getOut() << "wait get poses 2 " << result << std::endl;
}

/* void BaseCompositor::GetSinglePoseRendering(ETrackingUniverseOrigin origin, TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t * pOutputPose) {
	BackendManager::Instance().GetSinglePose(origin, unDeviceIndex, pOutputPose, ETrackingStateType::TrackingStateType_Rendering);
}

Matrix4f BaseCompositor::GetHandTransform() {
	float deg_to_rad = math_pi / 180;

	// The angle offset between the Touch and Vive controllers.
	// If this is incorrect, virtual hands will feel off.
	float controller_offset_angle = 39.5;

	// When testing to try and find the correct value above, uncomment
	//  this to lock the controller perfectly flat.
	// ovrPose.ThePose.Orientation = { 0,0,0,1 };

	Vector3f rotateAxis = Vector3f(1, 0, 0);
	Quatf rotation = Quatf(rotateAxis, controller_offset_angle * deg_to_rad); //count++ * 0.01f);

	Matrix4f transform(rotation);

	// Controller offset
	// Note this is about right, found by playing around in Unity until everything
	//  roughly lines up. If you want to contribute better numbers, please go ahead!
	transform.SetTranslation(Vector3f(0.0f, 0.0353f, -0.0451f));

	return transform;
} */

ovr_enum_t BaseCompositor::GetLastPoses(TrackedDevicePose_t * renderPoseArray, uint32_t renderPoseArrayCount,
	  TrackedDevicePose_t * gamePoseArray, uint32_t gamePoseArrayCount) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetLastPoses" << std::endl; });
  // getOut() << "get last poses 1 " << (void *)GetCurrentThreadId() << std::endl;
  // auto start = std::chrono::high_resolution_clock::now();
  auto result = g_pvrcompositor->GetLastPoses(renderPoseArray, renderPoseArrayCount, gamePoseArray, gamePoseArrayCount);
  /* auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  getOut() << "get last poses 2 " << elapsed.count() << std::endl; */
  return result;
}

ovr_enum_t BaseCompositor::GetLastPoseForTrackedDeviceIndex(TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t * pOutputPose,
	  TrackedDevicePose_t * pOutputGamePose) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetLastPoseForTrackedDeviceIndex" << std::endl; });
  // getOut() << "get last pose 1 " << std::endl;
  return g_pvrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
}

ovr_enum_t BaseCompositor::Submit(EVREye eye, const Texture_t * texture, const VRTextureBounds_t * bounds, EVRSubmitFlags submitFlags) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::Submit" << std::endl; });
  // getOut() << "submit 1" << std::endl;
  bool doRealSubmit;
  g_pvrclientcore->PreSubmit(&doRealSubmit);
  // getOut() << "submit 2" << std::endl;
  g_pvrcompositor->PrepareSubmit(texture);
  VRCompositorError result = g_pvrcompositor->Submit(eye, texture, bounds, submitFlags);
  //  getOut() << "do real submit " << doRealSubmit << std::endl;
  if (doRealSubmit) {
    g_pvrcompositor->FlushSubmit(eye);
    // g_pvrcompositor->PostPresentHandoff();
  }
  // getOut() << "submit 3" << std::endl;
  g_pvrclientcore->PostSubmit();
	return result;
  // getOut() << "submit 2 " << texture->eType << " " << texture->eColorSpace << std::endl;
}

void BaseCompositor::ClearLastSubmittedFrame() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ClearLastSubmittedFrame" << std::endl; });
	// At this point we should show the loading screen and show Guardian, and undo this when the
	// next frame comes along. TODO implement since it would improve loading screens, but it's certainly not critical
  g_pvrcompositor->ClearLastSubmittedFrame();
}

void BaseCompositor::PostPresentHandoff() {
	// It appears (from the documentation) that SteamVR will, even after all frames are submitted, not begin
	//  compositing the submitted textures until WaitGetPoses is called. Thus is you want to do some rendering
	//  or game logic or whatever, it will delay the compositor. Calling this tells SteamVR that no further changes
	//  are to be made to the frame, and it can begin the compositor - in the aforementioned cases, this would be
	//  called directly after the last Submit call.
	//
	// On the other hand, LibOVR starts compositing as soon as ovr_EndFrame is called. So we don't have to do
	//  anything here.
	//
	// TODO: use ovr_EndFrame and co instead of ovr_SubmitFrame for better performance, not just here but in all cases
	//  that way we can call ovr_WaitToBeginFrame in WaitGetPoses to mimick SteamVR.
  // TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::PostPresentHandoff" << std::endl; });
  // g_pvrcompositor->PostPresentHandoff();
}

bool BaseCompositor::GetFrameTiming(vr::Compositor_FrameTiming * pTiming, uint32_t unFramesAgo) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetFrameTiming" << std::endl; });
  return g_pvrcompositor->GetFrameTiming(pTiming, unFramesAgo);

	// TODO fill in the m_nNumVSyncsReadyForUse and uint32_t m_nNumVSyncsToFirstView fields, but only
	// when called from the correct version of the interface.
}

uint32_t BaseCompositor::GetFrameTimings(vr::Compositor_FrameTiming * pTiming, uint32_t nFrames) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetFrameTimings" << std::endl; });
	return g_pvrcompositor->GetFrameTimings(pTiming, nFrames);
}

/* bool BaseCompositor::GetFrameTiming(vr::Compositor_FrameTiming * pTiming, uint32_t unFramesAgo) {
  return g_vrcompositor->GetFrameTiming(pTiming, unFramesAgo);
}

uint32_t BaseCompositor::GetFrameTimings(vr::Compositor_FrameTiming * pTiming, uint32_t nFrames) {
	return g_vrcompositor->GetFrameTimings(pTiming, nFrames);
} */

float BaseCompositor::GetFrameTimeRemaining() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetFrameTimeRemaining" << std::endl; });
	return g_pvrcompositor->GetFrameTimeRemaining();
}

void BaseCompositor::GetCumulativeStats(vr::Compositor_CumulativeStats * pStats, uint32_t nStatsSizeInBytes) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetCumulativeStats" << std::endl; });
	return g_pvrcompositor->GetCumulativeStats(pStats, nStatsSizeInBytes);
}

void BaseCompositor::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::FadeToColor" << std::endl; });
	return g_pvrcompositor->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}

HmdColor_t BaseCompositor::GetCurrentFadeColor(bool bBackground) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetCurrentFadeColor" << std::endl; });
	return g_pvrcompositor->GetCurrentFadeColor(bBackground);
}

void BaseCompositor::FadeGrid(float fSeconds, bool bFadeIn) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::FadeGrid" << std::endl; });
	return g_pvrcompositor->FadeGrid(fSeconds, bFadeIn);
}

float BaseCompositor::GetCurrentGridAlpha() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetCurrentGridAlpha" << std::endl; });
	return g_pvrcompositor->GetCurrentGridAlpha();
}

ovr_enum_t BaseCompositor::SetSkyboxOverride(const Texture_t * pTextures, uint32_t unTextureCount) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::SetSkyboxOverride" << std::endl; });
	return g_pvrcompositor->SetSkyboxOverride(pTextures, unTextureCount);
}

void BaseCompositor::ClearSkyboxOverride() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ClearSkyboxOverride" << std::endl; });
	return g_pvrcompositor->ClearSkyboxOverride();
}

void BaseCompositor::CompositorBringToFront() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::CompositorBringToFront" << std::endl; });
	return g_pvrcompositor->CompositorBringToFront();
}

void BaseCompositor::CompositorGoToBack() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::CompositorGoToBack" << std::endl; });
	return g_pvrcompositor->CompositorGoToBack();
}

void BaseCompositor::CompositorQuit() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::CompositorQuit" << std::endl; });
	return g_pvrcompositor->CompositorQuit();
}

bool BaseCompositor::IsFullscreen() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::IsFullscreen" << std::endl; });
	return g_pvrcompositor->IsFullscreen();
}

uint32_t BaseCompositor::GetCurrentSceneFocusProcess() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetCurrentSceneFocusProcess" << std::endl; });
	return g_pvrcompositor->GetCurrentSceneFocusProcess();
}

uint32_t BaseCompositor::GetLastFrameRenderer() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetCurrentSceneFocusProcess" << std::endl; });
	return g_pvrcompositor->GetLastFrameRenderer();
}

bool BaseCompositor::CanRenderScene() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::CanRenderScene" << std::endl; });
	return g_pvrcompositor->CanRenderScene();
}

void BaseCompositor::ShowMirrorWindow() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ShowMirrorWindow" << std::endl; });
	return g_vrcompositor->ShowMirrorWindow();
}

void BaseCompositor::HideMirrorWindow() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::HideMirrorWindow" << std::endl; });
	return g_pvrcompositor->HideMirrorWindow();
}

bool BaseCompositor::IsMirrorWindowVisible() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::IsMirrorWindowVisible" << std::endl; });
	return g_pvrcompositor->IsMirrorWindowVisible();
}

void BaseCompositor::CompositorDumpImages() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::CompositorDumpImages" << std::endl; });
	return g_pvrcompositor->CompositorDumpImages();
}

bool BaseCompositor::ShouldAppRenderWithLowResources() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ShouldAppRenderWithLowResources" << std::endl; });
	return g_pvrcompositor->ShouldAppRenderWithLowResources();
}

void BaseCompositor::ForceInterleavedReprojectionOn(bool bOverride) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ForceInterleavedReprojectionOn" << std::endl; });
	return g_pvrcompositor->ForceInterleavedReprojectionOn(bOverride);
}

void BaseCompositor::ForceReconnectProcess() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ForceReconnectProcess" << std::endl; });
	return g_pvrcompositor->ForceReconnectProcess();
}

void BaseCompositor::SuspendRendering(bool bSuspend) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::SuspendRendering" << std::endl; });
	return g_pvrcompositor->SuspendRendering(bSuspend);
}

ovr_enum_t BaseCompositor::GetMirrorTextureD3D11(EVREye eEye, void * pD3D11DeviceOrResource, void ** ppD3D11ShaderResourceView) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetMirrorTextureD3D11" << std::endl; });
	return g_pvrcompositor->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView);
}

void BaseCompositor::ReleaseMirrorTextureD3D11(void * pD3D11ShaderResourceView) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ReleaseMirrorTextureD3D11" << std::endl; });
	return g_pvrcompositor->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView);
}

ovr_enum_t BaseCompositor::GetMirrorTextureGL(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetMirrorTextureGL" << std::endl; });
  return g_pvrcompositor->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
}

bool BaseCompositor::ReleaseSharedGLTexture(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::ReleaseSharedGLTexture" << std::endl; });
	return g_pvrcompositor->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
}

void BaseCompositor::LockGLSharedTextureForAccess(glSharedTextureHandle_t glSharedTextureHandle) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::LockGLSharedTextureForAccess" << std::endl; });
	return g_pvrcompositor->LockGLSharedTextureForAccess(glSharedTextureHandle);
}

void BaseCompositor::UnlockGLSharedTextureForAccess(glSharedTextureHandle_t glSharedTextureHandle) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::UnlockGLSharedTextureForAccess" << std::endl; });
	return g_pvrcompositor->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
}

uint32_t BaseCompositor::GetVulkanInstanceExtensionsRequired(VR_OUT_STRING() char * pchValue, uint32_t unBufferSize) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetVulkanInstanceExtensionsRequired" << std::endl; });
	return g_pvrcompositor->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
}

uint32_t BaseCompositor::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T * pPhysicalDevice, char * pchValue, uint32_t unBufferSize) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::GetVulkanDeviceExtensionsRequired" << std::endl; });
	return g_pvrcompositor->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize);
}

void BaseCompositor::SetExplicitTimingMode(ovr_enum_t eTimingMode) {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::SetExplicitTimingMode" << std::endl; });
	return g_pvrcompositor->SetExplicitTimingMode((vr::EVRCompositorTimingMode)eTimingMode);
}

ovr_enum_t BaseCompositor::SubmitExplicitTimingData() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::SubmitExplicitTimingData" << std::endl; });
	return g_pvrcompositor->SubmitExplicitTimingData();
}

bool BaseCompositor::IsMotionSmoothingSupported() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::IsMotionSmoothingSupported" << std::endl; });
	return g_pvrcompositor->IsMotionSmoothingSupported();
}

bool BaseCompositor::IsMotionSmoothingEnabled() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::IsMotionSmoothingEnabled" << std::endl; });
	return g_pvrcompositor->IsMotionSmoothingEnabled();
}

bool BaseCompositor::IsCurrentSceneFocusAppLoading() {
  TRACE("BaseCompositor", []() { getOut() << "BaseCompositor::IsCurrentSceneFocusAppLoading" << std::endl; });
	return g_pvrcompositor->IsCurrentSceneFocusAppLoading();
}