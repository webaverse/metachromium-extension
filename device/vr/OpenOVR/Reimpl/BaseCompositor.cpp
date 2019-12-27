#include "stdafx.h"
#define BASE_IMPL

#include "Misc/Config.h"

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

#include "Misc/ScopeGuard.h"
// #include "Drivers/Backend.h"

using namespace vr;
using namespace IVRCompositor_022;

typedef int ovr_enum_t;

#define SESS (*ovr::session)

BaseCompositor::BaseCompositor() {
}

BaseCompositor::~BaseCompositor() {
}

void BaseCompositor::SetTrackingSpace(ETrackingUniverseOrigin eOrigin) {
  g_vrcompositor->SetTrackingSpace(eOrigin);
	/* ovrTrackingOrigin origin = ovrTrackingOrigin_FloorLevel;
	if (eOrigin == TrackingUniverseSeated) {
		origin = ovrTrackingOrigin_EyeLevel;
	}

	vr::FAILED_OVR_ABORT(ovr_SetTrackingOriginType(SESS, origin)); */
}

ETrackingUniverseOrigin BaseCompositor::GetTrackingSpace() {
  return g_vrcompositor->GetTrackingSpace();
}

ovr_enum_t BaseCompositor::WaitGetPoses(TrackedDevicePose_t * renderPoseArray, uint32_t renderPoseArrayCount,
	TrackedDevicePose_t * gamePoseArray, uint32_t gamePoseArrayCount) {
  return g_vrcompositor->WaitGetPoses(renderPoseArray, renderPoseArrayCount, gamePoseArray, gamePoseArrayCount);
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
  return g_vrcompositor->GetLastPoses(renderPoseArray, renderPoseArrayCount, gamePoseArray, gamePoseArrayCount);
}

ovr_enum_t BaseCompositor::GetLastPoseForTrackedDeviceIndex(TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t * pOutputPose,
	  TrackedDevicePose_t * pOutputGamePose) {
  return g_vrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
}

ovr_enum_t BaseCompositor::Submit(EVREye eye, const Texture_t * texture, const VRTextureBounds_t * bounds, EVRSubmitFlags submitFlags) {
  // getOut() << "submit " << texture->eType << " " << texture->eColorSpace << std::endl;
	return g_vrcompositor->Submit(eye, texture, bounds, submitFlags);
}

void BaseCompositor::ClearLastSubmittedFrame() {
	// At this point we should show the loading screen and show Guardian, and undo this when the
	// next frame comes along. TODO implement since it would improve loading screens, but it's certainly not critical
  return g_vrcompositor->ClearLastSubmittedFrame();
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
  return g_vrcompositor->PostPresentHandoff();
}

bool BaseCompositor::GetFrameTiming(vr::Compositor_FrameTiming * pTiming, uint32_t unFramesAgo) {
  return g_vrcompositor->GetFrameTiming(pTiming, unFramesAgo);

	// TODO fill in the m_nNumVSyncsReadyForUse and uint32_t m_nNumVSyncsToFirstView fields, but only
	// when called from the correct version of the interface.
}

uint32_t BaseCompositor::GetFrameTimings(vr::Compositor_FrameTiming * pTiming, uint32_t nFrames) {
	return g_vrcompositor->GetFrameTimings(pTiming, nFrames);
}

/* bool BaseCompositor::GetFrameTiming(vr::Compositor_FrameTiming * pTiming, uint32_t unFramesAgo) {
  return g_vrcompositor->GetFrameTiming(pTiming, unFramesAgo);
}

uint32_t BaseCompositor::GetFrameTimings(vr::Compositor_FrameTiming * pTiming, uint32_t nFrames) {
	return g_vrcompositor->GetFrameTimings(pTiming, nFrames);
} */

float BaseCompositor::GetFrameTimeRemaining() {
	return g_vrcompositor->GetFrameTimeRemaining();
}

void BaseCompositor::GetCumulativeStats(vr::Compositor_CumulativeStats * pStats, uint32_t nStatsSizeInBytes) {
	return g_vrcompositor->GetCumulativeStats(pStats, nStatsSizeInBytes);
}

void BaseCompositor::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) {
	return g_vrcompositor->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}

HmdColor_t BaseCompositor::GetCurrentFadeColor(bool bBackground) {
	return g_vrcompositor->GetCurrentFadeColor(bBackground);
}

void BaseCompositor::FadeGrid(float fSeconds, bool bFadeIn) {
	return g_vrcompositor->FadeGrid(fSeconds, bFadeIn);
}

float BaseCompositor::GetCurrentGridAlpha() {
	return g_vrcompositor->GetCurrentGridAlpha();
}

ovr_enum_t BaseCompositor::SetSkyboxOverride(const Texture_t * pTextures, uint32_t unTextureCount) {
	return g_vrcompositor->SetSkyboxOverride(pTextures, unTextureCount);
}

void BaseCompositor::ClearSkyboxOverride() {
	return g_vrcompositor->ClearSkyboxOverride();
}

void BaseCompositor::CompositorBringToFront() {
	return g_vrcompositor->CompositorBringToFront();
}

void BaseCompositor::CompositorGoToBack() {
	return g_vrcompositor->CompositorGoToBack();
}

void BaseCompositor::CompositorQuit() {
	return g_vrcompositor->CompositorQuit();
}

bool BaseCompositor::IsFullscreen() {
	return g_vrcompositor->IsFullscreen();
}

uint32_t BaseCompositor::GetCurrentSceneFocusProcess() {
	return g_vrcompositor->GetCurrentSceneFocusProcess();
}

uint32_t BaseCompositor::GetLastFrameRenderer() {
	return g_vrcompositor->GetLastFrameRenderer();
}

bool BaseCompositor::CanRenderScene() {
	return g_vrcompositor->CanRenderScene();
}

void BaseCompositor::ShowMirrorWindow() {
	return g_vrcompositor->ShowMirrorWindow();
}

void BaseCompositor::HideMirrorWindow() {
	return g_vrcompositor->HideMirrorWindow();
}

bool BaseCompositor::IsMirrorWindowVisible() {
	return g_vrcompositor->IsMirrorWindowVisible();
}

void BaseCompositor::CompositorDumpImages() {
	return g_vrcompositor->CompositorDumpImages();
}

bool BaseCompositor::ShouldAppRenderWithLowResources() {
	return g_vrcompositor->ShouldAppRenderWithLowResources();
}

void BaseCompositor::ForceInterleavedReprojectionOn(bool bOverride) {
	return g_vrcompositor->ForceInterleavedReprojectionOn(bOverride);
}

void BaseCompositor::ForceReconnectProcess() {
	return g_vrcompositor->ForceReconnectProcess();
}

void BaseCompositor::SuspendRendering(bool bSuspend) {
	return g_vrcompositor->SuspendRendering(bSuspend);
}

ovr_enum_t BaseCompositor::GetMirrorTextureD3D11(EVREye eEye, void * pD3D11DeviceOrResource, void ** ppD3D11ShaderResourceView) {
	return g_vrcompositor->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView);
}

void BaseCompositor::ReleaseMirrorTextureD3D11(void * pD3D11ShaderResourceView) {
	return g_vrcompositor->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView);
}

ovr_enum_t BaseCompositor::GetMirrorTextureGL(EVREye eEye, glUInt_t * pglTextureId, glSharedTextureHandle_t * pglSharedTextureHandle) {
  return g_vrcompositor->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle);
}

bool BaseCompositor::ReleaseSharedGLTexture(glUInt_t glTextureId, glSharedTextureHandle_t glSharedTextureHandle) {
	return g_vrcompositor->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle);
}

void BaseCompositor::LockGLSharedTextureForAccess(glSharedTextureHandle_t glSharedTextureHandle) {
	return g_vrcompositor->LockGLSharedTextureForAccess(glSharedTextureHandle);
}

void BaseCompositor::UnlockGLSharedTextureForAccess(glSharedTextureHandle_t glSharedTextureHandle) {
	return g_vrcompositor->UnlockGLSharedTextureForAccess(glSharedTextureHandle);
}

uint32_t BaseCompositor::GetVulkanInstanceExtensionsRequired(VR_OUT_STRING() char * pchValue, uint32_t unBufferSize) {
	return g_vrcompositor->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize);
}

uint32_t BaseCompositor::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T * pPhysicalDevice, char * pchValue, uint32_t unBufferSize) {
	return g_vrcompositor->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize);
}

void BaseCompositor::SetExplicitTimingMode(ovr_enum_t eTimingMode) {
	return g_vrcompositor->SetExplicitTimingMode((vr::EVRCompositorTimingMode)eTimingMode);
}

ovr_enum_t BaseCompositor::SubmitExplicitTimingData() {
	return g_vrcompositor->SubmitExplicitTimingData();
}

bool BaseCompositor::IsMotionSmoothingSupported() {
	return g_vrcompositor->IsMotionSmoothingSupported();
}

bool BaseCompositor::IsMotionSmoothingEnabled() {
	return g_vrcompositor->IsMotionSmoothingEnabled();
}

bool BaseCompositor::IsCurrentSceneFocusAppLoading() {
	return g_vrcompositor->IsCurrentSceneFocusAppLoading();
}