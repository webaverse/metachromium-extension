#include "stdafx.h"
#include "Interfaces.h"
#include "static_bases.gen.h"
#include "GVRCompositor.gen.h"
// Single inst of BaseCompositor
static std::weak_ptr<BaseCompositor> _single_inst_Compositor;
static BaseCompositor *_single_inst_Compositor_unsafe = NULL;
std::shared_ptr<BaseCompositor> GetBaseCompositor() { return _single_inst_Compositor.lock(); };
BaseCompositor* GetUnsafeBaseCompositor() { return _single_inst_Compositor_unsafe; };
std::shared_ptr<BaseCompositor> GetCreateBaseCompositor() {
	std::shared_ptr<BaseCompositor> ret = _single_inst_Compositor.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseCompositor>(new BaseCompositor(), [](BaseCompositor *obj){ _single_inst_Compositor_unsafe = NULL; delete obj; });
		_single_inst_Compositor = ret;
		_single_inst_Compositor_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRCompositor_012:
CVRCompositor_012::CVRCompositor_012() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_012:
void CVRCompositor_012::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_012::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_012::EVRCompositorError CVRCompositor_012::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_012::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_012::EVRCompositorError CVRCompositor_012::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_012::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_012::EVRCompositorError CVRCompositor_012::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_012::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_012::EVRCompositorError CVRCompositor_012::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_012::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_012::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_012::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_012::GetFrameTiming(vr::IVRCompositor_012::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
float CVRCompositor_012::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_012::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_012::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_012::EVRCompositorError CVRCompositor_012::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_012::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_012::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_012::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_012::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_012::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_012::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_012::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_012::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_012::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_012::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_012::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_012::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_012::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_012::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
// FnTable for CVRCompositor_012:
static CVRCompositor_012 *fntable_Compositor_012_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_012_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetTrackingSpace() { return fntable_Compositor_012_instance->GetTrackingSpace(); }
static vr::IVRCompositor_012::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_012_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_012::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_012_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_012::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_012_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_012::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_012_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_ClearLastSubmittedFrame() { return fntable_Compositor_012_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_PostPresentHandoff() { return fntable_Compositor_012_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetFrameTiming(vr::IVRCompositor_012::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_012_instance->GetFrameTiming(pTiming, unFramesAgo); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetFrameTimeRemaining() { return fntable_Compositor_012_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_012_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_012_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_012::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_012_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_ClearSkyboxOverride() { return fntable_Compositor_012_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_CompositorBringToFront() { return fntable_Compositor_012_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_CompositorGoToBack() { return fntable_Compositor_012_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_CompositorQuit() { return fntable_Compositor_012_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_IsFullscreen() { return fntable_Compositor_012_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_012_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_GetLastFrameRenderer() { return fntable_Compositor_012_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_CanRenderScene() { return fntable_Compositor_012_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_ShowMirrorWindow() { return fntable_Compositor_012_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_HideMirrorWindow() { return fntable_Compositor_012_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_IsMirrorWindowVisible() { return fntable_Compositor_012_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_CompositorDumpImages() { return fntable_Compositor_012_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_012_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_012_instance->ShouldAppRenderWithLowResources(); }
static void *fntable_Compositor_012_funcs[] = {
	fntable_Compositor_012_impl_SetTrackingSpace,
	fntable_Compositor_012_impl_GetTrackingSpace,
	fntable_Compositor_012_impl_WaitGetPoses,
	fntable_Compositor_012_impl_GetLastPoses,
	fntable_Compositor_012_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_012_impl_Submit,
	fntable_Compositor_012_impl_ClearLastSubmittedFrame,
	fntable_Compositor_012_impl_PostPresentHandoff,
	fntable_Compositor_012_impl_GetFrameTiming,
	fntable_Compositor_012_impl_GetFrameTimeRemaining,
	fntable_Compositor_012_impl_FadeToColor,
	fntable_Compositor_012_impl_FadeGrid,
	fntable_Compositor_012_impl_SetSkyboxOverride,
	fntable_Compositor_012_impl_ClearSkyboxOverride,
	fntable_Compositor_012_impl_CompositorBringToFront,
	fntable_Compositor_012_impl_CompositorGoToBack,
	fntable_Compositor_012_impl_CompositorQuit,
	fntable_Compositor_012_impl_IsFullscreen,
	fntable_Compositor_012_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_012_impl_GetLastFrameRenderer,
	fntable_Compositor_012_impl_CanRenderScene,
	fntable_Compositor_012_impl_ShowMirrorWindow,
	fntable_Compositor_012_impl_HideMirrorWindow,
	fntable_Compositor_012_impl_IsMirrorWindowVisible,
	fntable_Compositor_012_impl_CompositorDumpImages,
	fntable_Compositor_012_impl_ShouldAppRenderWithLowResources,
};
void** CVRCompositor_012::_GetStatFuncList() { fntable_Compositor_012_instance = this; return fntable_Compositor_012_funcs; }
// Misc for CVRCompositor_013:
CVRCompositor_013::CVRCompositor_013() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_013:
void CVRCompositor_013::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_013::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_013::EVRCompositorError CVRCompositor_013::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_013::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_013::EVRCompositorError CVRCompositor_013::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_013::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_013::EVRCompositorError CVRCompositor_013::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_013::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_013::EVRCompositorError CVRCompositor_013::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_013::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_013::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_013::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_013::GetFrameTiming(vr::IVRCompositor_013::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
float CVRCompositor_013::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_013::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_013::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_013::EVRCompositorError CVRCompositor_013::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_013::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_013::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_013::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_013::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_013::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_013::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_013::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_013::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_013::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_013::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_013::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_013::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_013::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_013::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_013::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
// FnTable for CVRCompositor_013:
static CVRCompositor_013 *fntable_Compositor_013_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_013_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetTrackingSpace() { return fntable_Compositor_013_instance->GetTrackingSpace(); }
static vr::IVRCompositor_013::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_013_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_013::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_013_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_013::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_013_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_013::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_013_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_ClearLastSubmittedFrame() { return fntable_Compositor_013_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_PostPresentHandoff() { return fntable_Compositor_013_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetFrameTiming(vr::IVRCompositor_013::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_013_instance->GetFrameTiming(pTiming, unFramesAgo); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetFrameTimeRemaining() { return fntable_Compositor_013_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_013_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_013_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_013::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_013_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_ClearSkyboxOverride() { return fntable_Compositor_013_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_CompositorBringToFront() { return fntable_Compositor_013_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_CompositorGoToBack() { return fntable_Compositor_013_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_CompositorQuit() { return fntable_Compositor_013_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_IsFullscreen() { return fntable_Compositor_013_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_013_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_GetLastFrameRenderer() { return fntable_Compositor_013_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_CanRenderScene() { return fntable_Compositor_013_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_ShowMirrorWindow() { return fntable_Compositor_013_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_HideMirrorWindow() { return fntable_Compositor_013_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_IsMirrorWindowVisible() { return fntable_Compositor_013_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_CompositorDumpImages() { return fntable_Compositor_013_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_013_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_013_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_013_instance->ForceInterleavedReprojectionOn(bOverride); }
static void *fntable_Compositor_013_funcs[] = {
	fntable_Compositor_013_impl_SetTrackingSpace,
	fntable_Compositor_013_impl_GetTrackingSpace,
	fntable_Compositor_013_impl_WaitGetPoses,
	fntable_Compositor_013_impl_GetLastPoses,
	fntable_Compositor_013_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_013_impl_Submit,
	fntable_Compositor_013_impl_ClearLastSubmittedFrame,
	fntable_Compositor_013_impl_PostPresentHandoff,
	fntable_Compositor_013_impl_GetFrameTiming,
	fntable_Compositor_013_impl_GetFrameTimeRemaining,
	fntable_Compositor_013_impl_FadeToColor,
	fntable_Compositor_013_impl_FadeGrid,
	fntable_Compositor_013_impl_SetSkyboxOverride,
	fntable_Compositor_013_impl_ClearSkyboxOverride,
	fntable_Compositor_013_impl_CompositorBringToFront,
	fntable_Compositor_013_impl_CompositorGoToBack,
	fntable_Compositor_013_impl_CompositorQuit,
	fntable_Compositor_013_impl_IsFullscreen,
	fntable_Compositor_013_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_013_impl_GetLastFrameRenderer,
	fntable_Compositor_013_impl_CanRenderScene,
	fntable_Compositor_013_impl_ShowMirrorWindow,
	fntable_Compositor_013_impl_HideMirrorWindow,
	fntable_Compositor_013_impl_IsMirrorWindowVisible,
	fntable_Compositor_013_impl_CompositorDumpImages,
	fntable_Compositor_013_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_013_impl_ForceInterleavedReprojectionOn,
};
void** CVRCompositor_013::_GetStatFuncList() { fntable_Compositor_013_instance = this; return fntable_Compositor_013_funcs; }
// Misc for CVRCompositor_014:
CVRCompositor_014::CVRCompositor_014() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_014:
void CVRCompositor_014::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_014::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_014::EVRCompositorError CVRCompositor_014::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_014::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_014::EVRCompositorError CVRCompositor_014::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_014::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_014::EVRCompositorError CVRCompositor_014::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_014::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_014::EVRCompositorError CVRCompositor_014::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_014::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_014::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_014::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_014::GetFrameTiming(vr::IVRCompositor_014::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
float CVRCompositor_014::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_014::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_014::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_014::EVRCompositorError CVRCompositor_014::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_014::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_014::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_014::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_014::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_014::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_014::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_014::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_014::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_014::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_014::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_014::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_014::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_014::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_014::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_014::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_014::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_014::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
// FnTable for CVRCompositor_014:
static CVRCompositor_014 *fntable_Compositor_014_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_014_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetTrackingSpace() { return fntable_Compositor_014_instance->GetTrackingSpace(); }
static vr::IVRCompositor_014::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_014_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_014::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_014_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_014::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_014_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_014::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_014_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ClearLastSubmittedFrame() { return fntable_Compositor_014_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_PostPresentHandoff() { return fntable_Compositor_014_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetFrameTiming(vr::IVRCompositor_014::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_014_instance->GetFrameTiming(pTiming, unFramesAgo); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetFrameTimeRemaining() { return fntable_Compositor_014_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_014_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_014_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_014::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_014_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ClearSkyboxOverride() { return fntable_Compositor_014_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_CompositorBringToFront() { return fntable_Compositor_014_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_CompositorGoToBack() { return fntable_Compositor_014_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_CompositorQuit() { return fntable_Compositor_014_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_IsFullscreen() { return fntable_Compositor_014_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_014_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_GetLastFrameRenderer() { return fntable_Compositor_014_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_CanRenderScene() { return fntable_Compositor_014_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ShowMirrorWindow() { return fntable_Compositor_014_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_HideMirrorWindow() { return fntable_Compositor_014_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_IsMirrorWindowVisible() { return fntable_Compositor_014_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_CompositorDumpImages() { return fntable_Compositor_014_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_014_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_014_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_ForceReconnectProcess() { return fntable_Compositor_014_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_014_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_014_instance->SuspendRendering(bSuspend); }
static void *fntable_Compositor_014_funcs[] = {
	fntable_Compositor_014_impl_SetTrackingSpace,
	fntable_Compositor_014_impl_GetTrackingSpace,
	fntable_Compositor_014_impl_WaitGetPoses,
	fntable_Compositor_014_impl_GetLastPoses,
	fntable_Compositor_014_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_014_impl_Submit,
	fntable_Compositor_014_impl_ClearLastSubmittedFrame,
	fntable_Compositor_014_impl_PostPresentHandoff,
	fntable_Compositor_014_impl_GetFrameTiming,
	fntable_Compositor_014_impl_GetFrameTimeRemaining,
	fntable_Compositor_014_impl_FadeToColor,
	fntable_Compositor_014_impl_FadeGrid,
	fntable_Compositor_014_impl_SetSkyboxOverride,
	fntable_Compositor_014_impl_ClearSkyboxOverride,
	fntable_Compositor_014_impl_CompositorBringToFront,
	fntable_Compositor_014_impl_CompositorGoToBack,
	fntable_Compositor_014_impl_CompositorQuit,
	fntable_Compositor_014_impl_IsFullscreen,
	fntable_Compositor_014_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_014_impl_GetLastFrameRenderer,
	fntable_Compositor_014_impl_CanRenderScene,
	fntable_Compositor_014_impl_ShowMirrorWindow,
	fntable_Compositor_014_impl_HideMirrorWindow,
	fntable_Compositor_014_impl_IsMirrorWindowVisible,
	fntable_Compositor_014_impl_CompositorDumpImages,
	fntable_Compositor_014_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_014_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_014_impl_ForceReconnectProcess,
	fntable_Compositor_014_impl_SuspendRendering,
};
void** CVRCompositor_014::_GetStatFuncList() { fntable_Compositor_014_instance = this; return fntable_Compositor_014_funcs; }
// Misc for CVRCompositor_015:
CVRCompositor_015::CVRCompositor_015() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_015:
void CVRCompositor_015::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_015::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_015::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_015::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_015::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_015::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_015::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_015::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_015::GetFrameTiming(vr::IVRCompositor_015::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
float CVRCompositor_015::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_015::GetCumulativeStats(vr::IVRCompositor_015::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_015::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_015::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_015::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_015::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_015::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_015::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_015::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_015::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_015::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_015::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_015::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_015::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_015::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_015::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_015::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_015::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_015::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_015::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_015::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_015::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
vr::IVRCompositor_015::EVRCompositorError CVRCompositor_015::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_015::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_015::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_015::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_015::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
// FnTable for CVRCompositor_015:
static CVRCompositor_015 *fntable_Compositor_015_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_015_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetTrackingSpace() { return fntable_Compositor_015_instance->GetTrackingSpace(); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_015_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_015_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_015_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_015_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ClearLastSubmittedFrame() { return fntable_Compositor_015_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_PostPresentHandoff() { return fntable_Compositor_015_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetFrameTiming(vr::IVRCompositor_015::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_015_instance->GetFrameTiming(pTiming, unFramesAgo); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetFrameTimeRemaining() { return fntable_Compositor_015_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetCumulativeStats(vr::IVRCompositor_015::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_015_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_015_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_015_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_015_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ClearSkyboxOverride() { return fntable_Compositor_015_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_CompositorBringToFront() { return fntable_Compositor_015_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_CompositorGoToBack() { return fntable_Compositor_015_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_CompositorQuit() { return fntable_Compositor_015_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_IsFullscreen() { return fntable_Compositor_015_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_015_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetLastFrameRenderer() { return fntable_Compositor_015_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_CanRenderScene() { return fntable_Compositor_015_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ShowMirrorWindow() { return fntable_Compositor_015_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_HideMirrorWindow() { return fntable_Compositor_015_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_IsMirrorWindowVisible() { return fntable_Compositor_015_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_CompositorDumpImages() { return fntable_Compositor_015_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_015_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_015_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ForceReconnectProcess() { return fntable_Compositor_015_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_015_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_RequestScreenshot(vr::EVRScreenshotType type, const char* pchDestinationFileName, const char* pchVRDestinationFileName) { return fntable_Compositor_015_instance->RequestScreenshot(type, pchDestinationFileName, pchVRDestinationFileName); }
static vr::EVRScreenshotType OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetCurrentScreenshotType() { return fntable_Compositor_015_instance->GetCurrentScreenshotType(); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_015_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static vr::IVRCompositor_015::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_015_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_015_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_015_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_015_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_015_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static void *fntable_Compositor_015_funcs[] = {
	fntable_Compositor_015_impl_SetTrackingSpace,
	fntable_Compositor_015_impl_GetTrackingSpace,
	fntable_Compositor_015_impl_WaitGetPoses,
	fntable_Compositor_015_impl_GetLastPoses,
	fntable_Compositor_015_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_015_impl_Submit,
	fntable_Compositor_015_impl_ClearLastSubmittedFrame,
	fntable_Compositor_015_impl_PostPresentHandoff,
	fntable_Compositor_015_impl_GetFrameTiming,
	fntable_Compositor_015_impl_GetFrameTimeRemaining,
	fntable_Compositor_015_impl_GetCumulativeStats,
	fntable_Compositor_015_impl_FadeToColor,
	fntable_Compositor_015_impl_FadeGrid,
	fntable_Compositor_015_impl_SetSkyboxOverride,
	fntable_Compositor_015_impl_ClearSkyboxOverride,
	fntable_Compositor_015_impl_CompositorBringToFront,
	fntable_Compositor_015_impl_CompositorGoToBack,
	fntable_Compositor_015_impl_CompositorQuit,
	fntable_Compositor_015_impl_IsFullscreen,
	fntable_Compositor_015_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_015_impl_GetLastFrameRenderer,
	fntable_Compositor_015_impl_CanRenderScene,
	fntable_Compositor_015_impl_ShowMirrorWindow,
	fntable_Compositor_015_impl_HideMirrorWindow,
	fntable_Compositor_015_impl_IsMirrorWindowVisible,
	fntable_Compositor_015_impl_CompositorDumpImages,
	fntable_Compositor_015_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_015_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_015_impl_ForceReconnectProcess,
	fntable_Compositor_015_impl_SuspendRendering,
	fntable_Compositor_015_impl_RequestScreenshot,
	fntable_Compositor_015_impl_GetCurrentScreenshotType,
	fntable_Compositor_015_impl_GetMirrorTextureD3D11,
	fntable_Compositor_015_impl_GetMirrorTextureGL,
	fntable_Compositor_015_impl_ReleaseSharedGLTexture,
	fntable_Compositor_015_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_015_impl_UnlockGLSharedTextureForAccess,
};
void** CVRCompositor_015::_GetStatFuncList() { fntable_Compositor_015_instance = this; return fntable_Compositor_015_funcs; }
// Misc for CVRCompositor_016:
CVRCompositor_016::CVRCompositor_016() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_016:
void CVRCompositor_016::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_016::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_016::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_016::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_016::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_016::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_016::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_016::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_016::GetFrameTiming(vr::IVRCompositor_016::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
float CVRCompositor_016::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_016::GetCumulativeStats(vr::IVRCompositor_016::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_016::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_016::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_016::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_016::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_016::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_016::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_016::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_016::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_016::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_016::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_016::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_016::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_016::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_016::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_016::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_016::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_016::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_016::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_016::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_016::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
vr::IVRCompositor_016::EVRCompositorError CVRCompositor_016::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_016::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_016::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_016::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_016::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
// FnTable for CVRCompositor_016:
static CVRCompositor_016 *fntable_Compositor_016_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_016_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetTrackingSpace() { return fntable_Compositor_016_instance->GetTrackingSpace(); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_016_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_016_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_016_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_016_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ClearLastSubmittedFrame() { return fntable_Compositor_016_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_PostPresentHandoff() { return fntable_Compositor_016_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetFrameTiming(vr::IVRCompositor_016::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_016_instance->GetFrameTiming(pTiming, unFramesAgo); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetFrameTimeRemaining() { return fntable_Compositor_016_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetCumulativeStats(vr::IVRCompositor_016::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_016_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_016_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_016_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_016_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ClearSkyboxOverride() { return fntable_Compositor_016_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_CompositorBringToFront() { return fntable_Compositor_016_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_CompositorGoToBack() { return fntable_Compositor_016_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_CompositorQuit() { return fntable_Compositor_016_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_IsFullscreen() { return fntable_Compositor_016_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_016_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetLastFrameRenderer() { return fntable_Compositor_016_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_CanRenderScene() { return fntable_Compositor_016_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ShowMirrorWindow() { return fntable_Compositor_016_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_HideMirrorWindow() { return fntable_Compositor_016_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_IsMirrorWindowVisible() { return fntable_Compositor_016_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_CompositorDumpImages() { return fntable_Compositor_016_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_016_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_016_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ForceReconnectProcess() { return fntable_Compositor_016_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_016_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_016_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static vr::IVRCompositor_016::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_016_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_016_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_016_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_016_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_016_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static void *fntable_Compositor_016_funcs[] = {
	fntable_Compositor_016_impl_SetTrackingSpace,
	fntable_Compositor_016_impl_GetTrackingSpace,
	fntable_Compositor_016_impl_WaitGetPoses,
	fntable_Compositor_016_impl_GetLastPoses,
	fntable_Compositor_016_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_016_impl_Submit,
	fntable_Compositor_016_impl_ClearLastSubmittedFrame,
	fntable_Compositor_016_impl_PostPresentHandoff,
	fntable_Compositor_016_impl_GetFrameTiming,
	fntable_Compositor_016_impl_GetFrameTimeRemaining,
	fntable_Compositor_016_impl_GetCumulativeStats,
	fntable_Compositor_016_impl_FadeToColor,
	fntable_Compositor_016_impl_FadeGrid,
	fntable_Compositor_016_impl_SetSkyboxOverride,
	fntable_Compositor_016_impl_ClearSkyboxOverride,
	fntable_Compositor_016_impl_CompositorBringToFront,
	fntable_Compositor_016_impl_CompositorGoToBack,
	fntable_Compositor_016_impl_CompositorQuit,
	fntable_Compositor_016_impl_IsFullscreen,
	fntable_Compositor_016_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_016_impl_GetLastFrameRenderer,
	fntable_Compositor_016_impl_CanRenderScene,
	fntable_Compositor_016_impl_ShowMirrorWindow,
	fntable_Compositor_016_impl_HideMirrorWindow,
	fntable_Compositor_016_impl_IsMirrorWindowVisible,
	fntable_Compositor_016_impl_CompositorDumpImages,
	fntable_Compositor_016_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_016_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_016_impl_ForceReconnectProcess,
	fntable_Compositor_016_impl_SuspendRendering,
	fntable_Compositor_016_impl_GetMirrorTextureD3D11,
	fntable_Compositor_016_impl_GetMirrorTextureGL,
	fntable_Compositor_016_impl_ReleaseSharedGLTexture,
	fntable_Compositor_016_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_016_impl_UnlockGLSharedTextureForAccess,
};
void** CVRCompositor_016::_GetStatFuncList() { fntable_Compositor_016_instance = this; return fntable_Compositor_016_funcs; }
// Misc for CVRCompositor_017:
CVRCompositor_017::CVRCompositor_017() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_017:
void CVRCompositor_017::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_017::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_017::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_017::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_017::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_017::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_017::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_017::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_017::GetFrameTiming(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
uint32_t CVRCompositor_017::GetFrameTimings(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings((vr::Compositor_FrameTiming*) pTiming, nFrames); }
float CVRCompositor_017::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_017::GetCumulativeStats(vr::IVRCompositor_017::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_017::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
void CVRCompositor_017::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_017::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_017::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_017::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_017::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_017::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_017::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_017::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_017::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_017::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_017::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_017::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_017::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_017::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_017::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_017::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_017::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_017::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_017::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
vr::IVRCompositor_017::EVRCompositorError CVRCompositor_017::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_017::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_017::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_017::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_017::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
// FnTable for CVRCompositor_017:
static CVRCompositor_017 *fntable_Compositor_017_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_017_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetTrackingSpace() { return fntable_Compositor_017_instance->GetTrackingSpace(); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_017_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_017_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_017_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_017_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ClearLastSubmittedFrame() { return fntable_Compositor_017_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_PostPresentHandoff() { return fntable_Compositor_017_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetFrameTiming(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_017_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetFrameTimings(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_017_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetFrameTimeRemaining() { return fntable_Compositor_017_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetCumulativeStats(vr::IVRCompositor_017::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_017_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_017_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_017_instance->FadeGrid(fSeconds, bFadeIn); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_017_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ClearSkyboxOverride() { return fntable_Compositor_017_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_CompositorBringToFront() { return fntable_Compositor_017_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_CompositorGoToBack() { return fntable_Compositor_017_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_CompositorQuit() { return fntable_Compositor_017_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_IsFullscreen() { return fntable_Compositor_017_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_017_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetLastFrameRenderer() { return fntable_Compositor_017_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_CanRenderScene() { return fntable_Compositor_017_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ShowMirrorWindow() { return fntable_Compositor_017_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_HideMirrorWindow() { return fntable_Compositor_017_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_IsMirrorWindowVisible() { return fntable_Compositor_017_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_CompositorDumpImages() { return fntable_Compositor_017_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_017_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_017_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ForceReconnectProcess() { return fntable_Compositor_017_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_017_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_017_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static vr::IVRCompositor_017::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_017_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_017_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_017_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_017_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_017_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static void *fntable_Compositor_017_funcs[] = {
	fntable_Compositor_017_impl_SetTrackingSpace,
	fntable_Compositor_017_impl_GetTrackingSpace,
	fntable_Compositor_017_impl_WaitGetPoses,
	fntable_Compositor_017_impl_GetLastPoses,
	fntable_Compositor_017_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_017_impl_Submit,
	fntable_Compositor_017_impl_ClearLastSubmittedFrame,
	fntable_Compositor_017_impl_PostPresentHandoff,
	fntable_Compositor_017_impl_GetFrameTiming,
	fntable_Compositor_017_impl_GetFrameTimings,
	fntable_Compositor_017_impl_GetFrameTimeRemaining,
	fntable_Compositor_017_impl_GetCumulativeStats,
	fntable_Compositor_017_impl_FadeToColor,
	fntable_Compositor_017_impl_FadeGrid,
	fntable_Compositor_017_impl_SetSkyboxOverride,
	fntable_Compositor_017_impl_ClearSkyboxOverride,
	fntable_Compositor_017_impl_CompositorBringToFront,
	fntable_Compositor_017_impl_CompositorGoToBack,
	fntable_Compositor_017_impl_CompositorQuit,
	fntable_Compositor_017_impl_IsFullscreen,
	fntable_Compositor_017_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_017_impl_GetLastFrameRenderer,
	fntable_Compositor_017_impl_CanRenderScene,
	fntable_Compositor_017_impl_ShowMirrorWindow,
	fntable_Compositor_017_impl_HideMirrorWindow,
	fntable_Compositor_017_impl_IsMirrorWindowVisible,
	fntable_Compositor_017_impl_CompositorDumpImages,
	fntable_Compositor_017_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_017_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_017_impl_ForceReconnectProcess,
	fntable_Compositor_017_impl_SuspendRendering,
	fntable_Compositor_017_impl_GetMirrorTextureD3D11,
	fntable_Compositor_017_impl_GetMirrorTextureGL,
	fntable_Compositor_017_impl_ReleaseSharedGLTexture,
	fntable_Compositor_017_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_017_impl_UnlockGLSharedTextureForAccess,
};
void** CVRCompositor_017::_GetStatFuncList() { fntable_Compositor_017_instance = this; return fntable_Compositor_017_funcs; }
// Misc for CVRCompositor_018:
CVRCompositor_018::CVRCompositor_018() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_018:
void CVRCompositor_018::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_018::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_018::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_018::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_018::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_018::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_018::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_018::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_018::GetFrameTiming(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
uint32_t CVRCompositor_018::GetFrameTimings(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings((vr::Compositor_FrameTiming*) pTiming, nFrames); }
float CVRCompositor_018::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_018::GetCumulativeStats(vr::IVRCompositor_018::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_018::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
vr::HmdColor_t CVRCompositor_018::GetCurrentFadeColor(bool bBackground) { return base->GetCurrentFadeColor(bBackground); }
void CVRCompositor_018::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
float CVRCompositor_018::GetCurrentGridAlpha() { return base->GetCurrentGridAlpha(); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_018::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_018::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_018::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_018::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_018::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_018::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_018::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_018::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_018::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_018::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_018::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_018::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_018::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_018::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_018::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_018::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_018::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_018::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
vr::IVRCompositor_018::EVRCompositorError CVRCompositor_018::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_018::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_018::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_018::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_018::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
// FnTable for CVRCompositor_018:
static CVRCompositor_018 *fntable_Compositor_018_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_018_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetTrackingSpace() { return fntable_Compositor_018_instance->GetTrackingSpace(); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_018_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_018_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_018_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_018_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ClearLastSubmittedFrame() { return fntable_Compositor_018_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_PostPresentHandoff() { return fntable_Compositor_018_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetFrameTiming(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_018_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetFrameTimings(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_018_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetFrameTimeRemaining() { return fntable_Compositor_018_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetCumulativeStats(vr::IVRCompositor_018::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_018_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_018_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static vr::HmdColor_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetCurrentFadeColor(bool bBackground) { return fntable_Compositor_018_instance->GetCurrentFadeColor(bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_018_instance->FadeGrid(fSeconds, bFadeIn); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetCurrentGridAlpha() { return fntable_Compositor_018_instance->GetCurrentGridAlpha(); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_018_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ClearSkyboxOverride() { return fntable_Compositor_018_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_CompositorBringToFront() { return fntable_Compositor_018_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_CompositorGoToBack() { return fntable_Compositor_018_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_CompositorQuit() { return fntable_Compositor_018_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_IsFullscreen() { return fntable_Compositor_018_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_018_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetLastFrameRenderer() { return fntable_Compositor_018_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_CanRenderScene() { return fntable_Compositor_018_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ShowMirrorWindow() { return fntable_Compositor_018_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_HideMirrorWindow() { return fntable_Compositor_018_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_IsMirrorWindowVisible() { return fntable_Compositor_018_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_CompositorDumpImages() { return fntable_Compositor_018_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_018_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_018_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ForceReconnectProcess() { return fntable_Compositor_018_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_018_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_018_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static vr::IVRCompositor_018::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_018_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_018_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_018_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_018_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_018_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static void *fntable_Compositor_018_funcs[] = {
	fntable_Compositor_018_impl_SetTrackingSpace,
	fntable_Compositor_018_impl_GetTrackingSpace,
	fntable_Compositor_018_impl_WaitGetPoses,
	fntable_Compositor_018_impl_GetLastPoses,
	fntable_Compositor_018_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_018_impl_Submit,
	fntable_Compositor_018_impl_ClearLastSubmittedFrame,
	fntable_Compositor_018_impl_PostPresentHandoff,
	fntable_Compositor_018_impl_GetFrameTiming,
	fntable_Compositor_018_impl_GetFrameTimings,
	fntable_Compositor_018_impl_GetFrameTimeRemaining,
	fntable_Compositor_018_impl_GetCumulativeStats,
	fntable_Compositor_018_impl_FadeToColor,
	fntable_Compositor_018_impl_GetCurrentFadeColor,
	fntable_Compositor_018_impl_FadeGrid,
	fntable_Compositor_018_impl_GetCurrentGridAlpha,
	fntable_Compositor_018_impl_SetSkyboxOverride,
	fntable_Compositor_018_impl_ClearSkyboxOverride,
	fntable_Compositor_018_impl_CompositorBringToFront,
	fntable_Compositor_018_impl_CompositorGoToBack,
	fntable_Compositor_018_impl_CompositorQuit,
	fntable_Compositor_018_impl_IsFullscreen,
	fntable_Compositor_018_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_018_impl_GetLastFrameRenderer,
	fntable_Compositor_018_impl_CanRenderScene,
	fntable_Compositor_018_impl_ShowMirrorWindow,
	fntable_Compositor_018_impl_HideMirrorWindow,
	fntable_Compositor_018_impl_IsMirrorWindowVisible,
	fntable_Compositor_018_impl_CompositorDumpImages,
	fntable_Compositor_018_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_018_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_018_impl_ForceReconnectProcess,
	fntable_Compositor_018_impl_SuspendRendering,
	fntable_Compositor_018_impl_GetMirrorTextureD3D11,
	fntable_Compositor_018_impl_GetMirrorTextureGL,
	fntable_Compositor_018_impl_ReleaseSharedGLTexture,
	fntable_Compositor_018_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_018_impl_UnlockGLSharedTextureForAccess,
};
void** CVRCompositor_018::_GetStatFuncList() { fntable_Compositor_018_instance = this; return fntable_Compositor_018_funcs; }
// Misc for CVRCompositor_019:
CVRCompositor_019::CVRCompositor_019() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_019:
void CVRCompositor_019::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_019::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_019::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_019::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_019::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_019::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_019::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_019::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_019::GetFrameTiming(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
uint32_t CVRCompositor_019::GetFrameTimings(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings((vr::Compositor_FrameTiming*) pTiming, nFrames); }
float CVRCompositor_019::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_019::GetCumulativeStats(vr::IVRCompositor_019::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_019::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
vr::HmdColor_t CVRCompositor_019::GetCurrentFadeColor(bool bBackground) { return base->GetCurrentFadeColor(bBackground); }
void CVRCompositor_019::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
float CVRCompositor_019::GetCurrentGridAlpha() { return base->GetCurrentGridAlpha(); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_019::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_019::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_019::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_019::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_019::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_019::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_019::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_019::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_019::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_019::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_019::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_019::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_019::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_019::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_019::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_019::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_019::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_019::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
vr::IVRCompositor_019::EVRCompositorError CVRCompositor_019::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_019::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_019::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_019::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_019::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
uint32_t CVRCompositor_019::GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return base->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
uint32_t CVRCompositor_019::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return base->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
// FnTable for CVRCompositor_019:
static CVRCompositor_019 *fntable_Compositor_019_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_019_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetTrackingSpace() { return fntable_Compositor_019_instance->GetTrackingSpace(); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_019_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_019_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_019_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_019_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ClearLastSubmittedFrame() { return fntable_Compositor_019_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_PostPresentHandoff() { return fntable_Compositor_019_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetFrameTiming(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_019_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetFrameTimings(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_019_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetFrameTimeRemaining() { return fntable_Compositor_019_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetCumulativeStats(vr::IVRCompositor_019::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_019_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_019_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static vr::HmdColor_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetCurrentFadeColor(bool bBackground) { return fntable_Compositor_019_instance->GetCurrentFadeColor(bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_019_instance->FadeGrid(fSeconds, bFadeIn); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetCurrentGridAlpha() { return fntable_Compositor_019_instance->GetCurrentGridAlpha(); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_019_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ClearSkyboxOverride() { return fntable_Compositor_019_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_CompositorBringToFront() { return fntable_Compositor_019_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_CompositorGoToBack() { return fntable_Compositor_019_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_CompositorQuit() { return fntable_Compositor_019_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_IsFullscreen() { return fntable_Compositor_019_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_019_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetLastFrameRenderer() { return fntable_Compositor_019_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_CanRenderScene() { return fntable_Compositor_019_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ShowMirrorWindow() { return fntable_Compositor_019_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_HideMirrorWindow() { return fntable_Compositor_019_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_IsMirrorWindowVisible() { return fntable_Compositor_019_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_CompositorDumpImages() { return fntable_Compositor_019_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_019_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_019_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ForceReconnectProcess() { return fntable_Compositor_019_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_019_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_019_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static vr::IVRCompositor_019::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_019_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_019_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_019_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_019_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_019_instance->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_019_impl_GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_019_instance->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
static void *fntable_Compositor_019_funcs[] = {
	fntable_Compositor_019_impl_SetTrackingSpace,
	fntable_Compositor_019_impl_GetTrackingSpace,
	fntable_Compositor_019_impl_WaitGetPoses,
	fntable_Compositor_019_impl_GetLastPoses,
	fntable_Compositor_019_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_019_impl_Submit,
	fntable_Compositor_019_impl_ClearLastSubmittedFrame,
	fntable_Compositor_019_impl_PostPresentHandoff,
	fntable_Compositor_019_impl_GetFrameTiming,
	fntable_Compositor_019_impl_GetFrameTimings,
	fntable_Compositor_019_impl_GetFrameTimeRemaining,
	fntable_Compositor_019_impl_GetCumulativeStats,
	fntable_Compositor_019_impl_FadeToColor,
	fntable_Compositor_019_impl_GetCurrentFadeColor,
	fntable_Compositor_019_impl_FadeGrid,
	fntable_Compositor_019_impl_GetCurrentGridAlpha,
	fntable_Compositor_019_impl_SetSkyboxOverride,
	fntable_Compositor_019_impl_ClearSkyboxOverride,
	fntable_Compositor_019_impl_CompositorBringToFront,
	fntable_Compositor_019_impl_CompositorGoToBack,
	fntable_Compositor_019_impl_CompositorQuit,
	fntable_Compositor_019_impl_IsFullscreen,
	fntable_Compositor_019_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_019_impl_GetLastFrameRenderer,
	fntable_Compositor_019_impl_CanRenderScene,
	fntable_Compositor_019_impl_ShowMirrorWindow,
	fntable_Compositor_019_impl_HideMirrorWindow,
	fntable_Compositor_019_impl_IsMirrorWindowVisible,
	fntable_Compositor_019_impl_CompositorDumpImages,
	fntable_Compositor_019_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_019_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_019_impl_ForceReconnectProcess,
	fntable_Compositor_019_impl_SuspendRendering,
	fntable_Compositor_019_impl_GetMirrorTextureD3D11,
	fntable_Compositor_019_impl_GetMirrorTextureGL,
	fntable_Compositor_019_impl_ReleaseSharedGLTexture,
	fntable_Compositor_019_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_019_impl_UnlockGLSharedTextureForAccess,
	fntable_Compositor_019_impl_GetVulkanInstanceExtensionsRequired,
	fntable_Compositor_019_impl_GetVulkanDeviceExtensionsRequired,
};
void** CVRCompositor_019::_GetStatFuncList() { fntable_Compositor_019_instance = this; return fntable_Compositor_019_funcs; }
// Misc for CVRCompositor_020:
CVRCompositor_020::CVRCompositor_020() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_020:
void CVRCompositor_020::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_020::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_020::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_020::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_020::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_020::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_020::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_020::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_020::GetFrameTiming(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
uint32_t CVRCompositor_020::GetFrameTimings(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings((vr::Compositor_FrameTiming*) pTiming, nFrames); }
float CVRCompositor_020::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_020::GetCumulativeStats(vr::IVRCompositor_020::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_020::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
vr::HmdColor_t CVRCompositor_020::GetCurrentFadeColor(bool bBackground) { return base->GetCurrentFadeColor(bBackground); }
void CVRCompositor_020::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
float CVRCompositor_020::GetCurrentGridAlpha() { return base->GetCurrentGridAlpha(); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_020::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_020::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_020::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_020::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_020::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_020::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_020::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_020::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_020::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_020::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_020::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_020::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_020::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_020::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_020::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_020::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_020::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_020::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
void CVRCompositor_020::ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return base->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
vr::IVRCompositor_020::EVRCompositorError CVRCompositor_020::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_020::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_020::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_020::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_020::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
uint32_t CVRCompositor_020::GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return base->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
uint32_t CVRCompositor_020::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return base->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
// FnTable for CVRCompositor_020:
static CVRCompositor_020 *fntable_Compositor_020_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_020_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetTrackingSpace() { return fntable_Compositor_020_instance->GetTrackingSpace(); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_020_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_020_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_020_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_020_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ClearLastSubmittedFrame() { return fntable_Compositor_020_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_PostPresentHandoff() { return fntable_Compositor_020_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetFrameTiming(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_020_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetFrameTimings(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_020_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetFrameTimeRemaining() { return fntable_Compositor_020_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetCumulativeStats(vr::IVRCompositor_020::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_020_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_020_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static vr::HmdColor_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetCurrentFadeColor(bool bBackground) { return fntable_Compositor_020_instance->GetCurrentFadeColor(bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_020_instance->FadeGrid(fSeconds, bFadeIn); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetCurrentGridAlpha() { return fntable_Compositor_020_instance->GetCurrentGridAlpha(); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_020_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ClearSkyboxOverride() { return fntable_Compositor_020_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_CompositorBringToFront() { return fntable_Compositor_020_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_CompositorGoToBack() { return fntable_Compositor_020_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_CompositorQuit() { return fntable_Compositor_020_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_IsFullscreen() { return fntable_Compositor_020_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_020_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetLastFrameRenderer() { return fntable_Compositor_020_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_CanRenderScene() { return fntable_Compositor_020_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ShowMirrorWindow() { return fntable_Compositor_020_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_HideMirrorWindow() { return fntable_Compositor_020_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_IsMirrorWindowVisible() { return fntable_Compositor_020_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_CompositorDumpImages() { return fntable_Compositor_020_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_020_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_020_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ForceReconnectProcess() { return fntable_Compositor_020_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_020_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_020_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return fntable_Compositor_020_instance->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
static vr::IVRCompositor_020::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_020_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_020_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_020_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_020_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_020_instance->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_020_impl_GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_020_instance->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
static void *fntable_Compositor_020_funcs[] = {
	fntable_Compositor_020_impl_SetTrackingSpace,
	fntable_Compositor_020_impl_GetTrackingSpace,
	fntable_Compositor_020_impl_WaitGetPoses,
	fntable_Compositor_020_impl_GetLastPoses,
	fntable_Compositor_020_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_020_impl_Submit,
	fntable_Compositor_020_impl_ClearLastSubmittedFrame,
	fntable_Compositor_020_impl_PostPresentHandoff,
	fntable_Compositor_020_impl_GetFrameTiming,
	fntable_Compositor_020_impl_GetFrameTimings,
	fntable_Compositor_020_impl_GetFrameTimeRemaining,
	fntable_Compositor_020_impl_GetCumulativeStats,
	fntable_Compositor_020_impl_FadeToColor,
	fntable_Compositor_020_impl_GetCurrentFadeColor,
	fntable_Compositor_020_impl_FadeGrid,
	fntable_Compositor_020_impl_GetCurrentGridAlpha,
	fntable_Compositor_020_impl_SetSkyboxOverride,
	fntable_Compositor_020_impl_ClearSkyboxOverride,
	fntable_Compositor_020_impl_CompositorBringToFront,
	fntable_Compositor_020_impl_CompositorGoToBack,
	fntable_Compositor_020_impl_CompositorQuit,
	fntable_Compositor_020_impl_IsFullscreen,
	fntable_Compositor_020_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_020_impl_GetLastFrameRenderer,
	fntable_Compositor_020_impl_CanRenderScene,
	fntable_Compositor_020_impl_ShowMirrorWindow,
	fntable_Compositor_020_impl_HideMirrorWindow,
	fntable_Compositor_020_impl_IsMirrorWindowVisible,
	fntable_Compositor_020_impl_CompositorDumpImages,
	fntable_Compositor_020_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_020_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_020_impl_ForceReconnectProcess,
	fntable_Compositor_020_impl_SuspendRendering,
	fntable_Compositor_020_impl_GetMirrorTextureD3D11,
	fntable_Compositor_020_impl_ReleaseMirrorTextureD3D11,
	fntable_Compositor_020_impl_GetMirrorTextureGL,
	fntable_Compositor_020_impl_ReleaseSharedGLTexture,
	fntable_Compositor_020_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_020_impl_UnlockGLSharedTextureForAccess,
	fntable_Compositor_020_impl_GetVulkanInstanceExtensionsRequired,
	fntable_Compositor_020_impl_GetVulkanDeviceExtensionsRequired,
};
void** CVRCompositor_020::_GetStatFuncList() { fntable_Compositor_020_instance = this; return fntable_Compositor_020_funcs; }
// Misc for CVRCompositor_021:
CVRCompositor_021::CVRCompositor_021() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_021:
void CVRCompositor_021::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_021::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_021::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_021::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_021::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_021::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_021::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_021::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_021::GetFrameTiming(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming((vr::Compositor_FrameTiming*) pTiming, unFramesAgo); }
uint32_t CVRCompositor_021::GetFrameTimings(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings((vr::Compositor_FrameTiming*) pTiming, nFrames); }
float CVRCompositor_021::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_021::GetCumulativeStats(vr::IVRCompositor_021::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_021::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
vr::HmdColor_t CVRCompositor_021::GetCurrentFadeColor(bool bBackground) { return base->GetCurrentFadeColor(bBackground); }
void CVRCompositor_021::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
float CVRCompositor_021::GetCurrentGridAlpha() { return base->GetCurrentGridAlpha(); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_021::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_021::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_021::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_021::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_021::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_021::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_021::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_021::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_021::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_021::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_021::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_021::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_021::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_021::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_021::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_021::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_021::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_021::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
void CVRCompositor_021::ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return base->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_021::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_021::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_021::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_021::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
uint32_t CVRCompositor_021::GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return base->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
uint32_t CVRCompositor_021::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return base->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
void CVRCompositor_021::SetExplicitTimingMode(bool bExplicitTimingMode) { return base->SetExplicitTimingMode(bExplicitTimingMode); }
vr::IVRCompositor_021::EVRCompositorError CVRCompositor_021::SubmitExplicitTimingData() { return (vr::IVRCompositor_021::EVRCompositorError) base->SubmitExplicitTimingData(); }
// FnTable for CVRCompositor_021:
static CVRCompositor_021 *fntable_Compositor_021_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_021_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetTrackingSpace() { return fntable_Compositor_021_instance->GetTrackingSpace(); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_021_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_021_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_021_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_021_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ClearLastSubmittedFrame() { return fntable_Compositor_021_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_PostPresentHandoff() { return fntable_Compositor_021_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetFrameTiming(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_021_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetFrameTimings(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_021_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetFrameTimeRemaining() { return fntable_Compositor_021_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetCumulativeStats(vr::IVRCompositor_021::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_021_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_021_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static vr::HmdColor_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetCurrentFadeColor(bool bBackground) { return fntable_Compositor_021_instance->GetCurrentFadeColor(bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_021_instance->FadeGrid(fSeconds, bFadeIn); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetCurrentGridAlpha() { return fntable_Compositor_021_instance->GetCurrentGridAlpha(); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_021_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ClearSkyboxOverride() { return fntable_Compositor_021_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_CompositorBringToFront() { return fntable_Compositor_021_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_CompositorGoToBack() { return fntable_Compositor_021_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_CompositorQuit() { return fntable_Compositor_021_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_IsFullscreen() { return fntable_Compositor_021_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_021_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetLastFrameRenderer() { return fntable_Compositor_021_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_CanRenderScene() { return fntable_Compositor_021_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ShowMirrorWindow() { return fntable_Compositor_021_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_HideMirrorWindow() { return fntable_Compositor_021_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_IsMirrorWindowVisible() { return fntable_Compositor_021_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_CompositorDumpImages() { return fntable_Compositor_021_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_021_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_021_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ForceReconnectProcess() { return fntable_Compositor_021_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_021_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_021_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return fntable_Compositor_021_instance->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_021_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_021_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_021_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_021_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_021_instance->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_021_instance->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_SetExplicitTimingMode(bool bExplicitTimingMode) { return fntable_Compositor_021_instance->SetExplicitTimingMode(bExplicitTimingMode); }
static vr::IVRCompositor_021::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_021_impl_SubmitExplicitTimingData() { return fntable_Compositor_021_instance->SubmitExplicitTimingData(); }
static void *fntable_Compositor_021_funcs[] = {
	fntable_Compositor_021_impl_SetTrackingSpace,
	fntable_Compositor_021_impl_GetTrackingSpace,
	fntable_Compositor_021_impl_WaitGetPoses,
	fntable_Compositor_021_impl_GetLastPoses,
	fntable_Compositor_021_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_021_impl_Submit,
	fntable_Compositor_021_impl_ClearLastSubmittedFrame,
	fntable_Compositor_021_impl_PostPresentHandoff,
	fntable_Compositor_021_impl_GetFrameTiming,
	fntable_Compositor_021_impl_GetFrameTimings,
	fntable_Compositor_021_impl_GetFrameTimeRemaining,
	fntable_Compositor_021_impl_GetCumulativeStats,
	fntable_Compositor_021_impl_FadeToColor,
	fntable_Compositor_021_impl_GetCurrentFadeColor,
	fntable_Compositor_021_impl_FadeGrid,
	fntable_Compositor_021_impl_GetCurrentGridAlpha,
	fntable_Compositor_021_impl_SetSkyboxOverride,
	fntable_Compositor_021_impl_ClearSkyboxOverride,
	fntable_Compositor_021_impl_CompositorBringToFront,
	fntable_Compositor_021_impl_CompositorGoToBack,
	fntable_Compositor_021_impl_CompositorQuit,
	fntable_Compositor_021_impl_IsFullscreen,
	fntable_Compositor_021_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_021_impl_GetLastFrameRenderer,
	fntable_Compositor_021_impl_CanRenderScene,
	fntable_Compositor_021_impl_ShowMirrorWindow,
	fntable_Compositor_021_impl_HideMirrorWindow,
	fntable_Compositor_021_impl_IsMirrorWindowVisible,
	fntable_Compositor_021_impl_CompositorDumpImages,
	fntable_Compositor_021_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_021_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_021_impl_ForceReconnectProcess,
	fntable_Compositor_021_impl_SuspendRendering,
	fntable_Compositor_021_impl_GetMirrorTextureD3D11,
	fntable_Compositor_021_impl_ReleaseMirrorTextureD3D11,
	fntable_Compositor_021_impl_GetMirrorTextureGL,
	fntable_Compositor_021_impl_ReleaseSharedGLTexture,
	fntable_Compositor_021_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_021_impl_UnlockGLSharedTextureForAccess,
	fntable_Compositor_021_impl_GetVulkanInstanceExtensionsRequired,
	fntable_Compositor_021_impl_GetVulkanDeviceExtensionsRequired,
	fntable_Compositor_021_impl_SetExplicitTimingMode,
	fntable_Compositor_021_impl_SubmitExplicitTimingData,
};
void** CVRCompositor_021::_GetStatFuncList() { fntable_Compositor_021_instance = this; return fntable_Compositor_021_funcs; }
// Misc for CVRCompositor_022:
CVRCompositor_022::CVRCompositor_022() : base(GetCreateBaseCompositor()) {}
// Interface methods for CVRCompositor_022:
void CVRCompositor_022::SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return base->SetTrackingSpace(eOrigin); }
vr::ETrackingUniverseOrigin CVRCompositor_022::GetTrackingSpace() { return base->GetTrackingSpace(); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_022::EVRCompositorError) base->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return (vr::IVRCompositor_022::EVRCompositorError) base->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return (vr::IVRCompositor_022::EVRCompositorError) base->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return (vr::IVRCompositor_022::EVRCompositorError) base->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
void CVRCompositor_022::ClearLastSubmittedFrame() { return base->ClearLastSubmittedFrame(); }
void CVRCompositor_022::PostPresentHandoff() { return base->PostPresentHandoff(); }
bool CVRCompositor_022::GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return base->GetFrameTiming(pTiming, unFramesAgo); }
uint32_t CVRCompositor_022::GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return base->GetFrameTimings(pTiming, nFrames); }
float CVRCompositor_022::GetFrameTimeRemaining() { return base->GetFrameTimeRemaining(); }
void CVRCompositor_022::GetCumulativeStats(vr::IVRCompositor_022::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return base->GetCumulativeStats((vr::Compositor_CumulativeStats*) pStats, nStatsSizeInBytes); }
void CVRCompositor_022::FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return base->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
vr::HmdColor_t CVRCompositor_022::GetCurrentFadeColor(bool bBackground) { return base->GetCurrentFadeColor(bBackground); }
void CVRCompositor_022::FadeGrid(float fSeconds, bool bFadeIn) { return base->FadeGrid(fSeconds, bFadeIn); }
float CVRCompositor_022::GetCurrentGridAlpha() { return base->GetCurrentGridAlpha(); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return (vr::IVRCompositor_022::EVRCompositorError) base->SetSkyboxOverride(pTextures, unTextureCount); }
void CVRCompositor_022::ClearSkyboxOverride() { return base->ClearSkyboxOverride(); }
void CVRCompositor_022::CompositorBringToFront() { return base->CompositorBringToFront(); }
void CVRCompositor_022::CompositorGoToBack() { return base->CompositorGoToBack(); }
void CVRCompositor_022::CompositorQuit() { return base->CompositorQuit(); }
bool CVRCompositor_022::IsFullscreen() { return base->IsFullscreen(); }
uint32_t CVRCompositor_022::GetCurrentSceneFocusProcess() { return base->GetCurrentSceneFocusProcess(); }
uint32_t CVRCompositor_022::GetLastFrameRenderer() { return base->GetLastFrameRenderer(); }
bool CVRCompositor_022::CanRenderScene() { return base->CanRenderScene(); }
void CVRCompositor_022::ShowMirrorWindow() { return base->ShowMirrorWindow(); }
void CVRCompositor_022::HideMirrorWindow() { return base->HideMirrorWindow(); }
bool CVRCompositor_022::IsMirrorWindowVisible() { return base->IsMirrorWindowVisible(); }
void CVRCompositor_022::CompositorDumpImages() { return base->CompositorDumpImages(); }
bool CVRCompositor_022::ShouldAppRenderWithLowResources() { return base->ShouldAppRenderWithLowResources(); }
void CVRCompositor_022::ForceInterleavedReprojectionOn(bool bOverride) { return base->ForceInterleavedReprojectionOn(bOverride); }
void CVRCompositor_022::ForceReconnectProcess() { return base->ForceReconnectProcess(); }
void CVRCompositor_022::SuspendRendering(bool bSuspend) { return base->SuspendRendering(bSuspend); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return (vr::IVRCompositor_022::EVRCompositorError) base->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
void CVRCompositor_022::ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return base->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return (vr::IVRCompositor_022::EVRCompositorError) base->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
bool CVRCompositor_022::ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
void CVRCompositor_022::LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->LockGLSharedTextureForAccess(glSharedTextureHandle); }
void CVRCompositor_022::UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return base->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
uint32_t CVRCompositor_022::GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return base->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
uint32_t CVRCompositor_022::GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return base->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
void CVRCompositor_022::SetExplicitTimingMode(vr::IVRCompositor_022::EVRCompositorTimingMode eTimingMode) { return base->SetExplicitTimingMode((vr::EVRCompositorTimingMode) eTimingMode); }
vr::IVRCompositor_022::EVRCompositorError CVRCompositor_022::SubmitExplicitTimingData() { return (vr::IVRCompositor_022::EVRCompositorError) base->SubmitExplicitTimingData(); }
bool CVRCompositor_022::IsMotionSmoothingEnabled() { return base->IsMotionSmoothingEnabled(); }
bool CVRCompositor_022::IsMotionSmoothingSupported() { return base->IsMotionSmoothingSupported(); }
bool CVRCompositor_022::IsCurrentSceneFocusAppLoading() { return base->IsCurrentSceneFocusAppLoading(); }
// FnTable for CVRCompositor_022:
static CVRCompositor_022 *fntable_Compositor_022_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin) { return fntable_Compositor_022_instance->SetTrackingSpace(eOrigin); }
static vr::ETrackingUniverseOrigin OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetTrackingSpace() { return fntable_Compositor_022_instance->GetTrackingSpace(); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_022_instance->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount) { return fntable_Compositor_022_instance->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose) { return fntable_Compositor_022_instance->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags) { return fntable_Compositor_022_instance->Submit(eEye, pTexture, pBounds, nSubmitFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ClearLastSubmittedFrame() { return fntable_Compositor_022_instance->ClearLastSubmittedFrame(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_PostPresentHandoff() { return fntable_Compositor_022_instance->PostPresentHandoff(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo) { return fntable_Compositor_022_instance->GetFrameTiming(pTiming, unFramesAgo); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames) { return fntable_Compositor_022_instance->GetFrameTimings(pTiming, nFrames); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetFrameTimeRemaining() { return fntable_Compositor_022_instance->GetFrameTimeRemaining(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetCumulativeStats(vr::IVRCompositor_022::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes) { return fntable_Compositor_022_instance->GetCumulativeStats(pStats, nStatsSizeInBytes); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) { return fntable_Compositor_022_instance->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }
static vr::HmdColor_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetCurrentFadeColor(bool bBackground) { return fntable_Compositor_022_instance->GetCurrentFadeColor(bBackground); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_FadeGrid(float fSeconds, bool bFadeIn) { return fntable_Compositor_022_instance->FadeGrid(fSeconds, bFadeIn); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetCurrentGridAlpha() { return fntable_Compositor_022_instance->GetCurrentGridAlpha(); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount) { return fntable_Compositor_022_instance->SetSkyboxOverride(pTextures, unTextureCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ClearSkyboxOverride() { return fntable_Compositor_022_instance->ClearSkyboxOverride(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_CompositorBringToFront() { return fntable_Compositor_022_instance->CompositorBringToFront(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_CompositorGoToBack() { return fntable_Compositor_022_instance->CompositorGoToBack(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_CompositorQuit() { return fntable_Compositor_022_instance->CompositorQuit(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_IsFullscreen() { return fntable_Compositor_022_instance->IsFullscreen(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetCurrentSceneFocusProcess() { return fntable_Compositor_022_instance->GetCurrentSceneFocusProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetLastFrameRenderer() { return fntable_Compositor_022_instance->GetLastFrameRenderer(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_CanRenderScene() { return fntable_Compositor_022_instance->CanRenderScene(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ShowMirrorWindow() { return fntable_Compositor_022_instance->ShowMirrorWindow(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_HideMirrorWindow() { return fntable_Compositor_022_instance->HideMirrorWindow(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_IsMirrorWindowVisible() { return fntable_Compositor_022_instance->IsMirrorWindowVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_CompositorDumpImages() { return fntable_Compositor_022_instance->CompositorDumpImages(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ShouldAppRenderWithLowResources() { return fntable_Compositor_022_instance->ShouldAppRenderWithLowResources(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ForceInterleavedReprojectionOn(bool bOverride) { return fntable_Compositor_022_instance->ForceInterleavedReprojectionOn(bOverride); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ForceReconnectProcess() { return fntable_Compositor_022_instance->ForceReconnectProcess(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_SuspendRendering(bool bSuspend) { return fntable_Compositor_022_instance->SuspendRendering(bSuspend); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView) { return fntable_Compositor_022_instance->GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView) { return fntable_Compositor_022_instance->ReleaseMirrorTextureD3D11(pD3D11ShaderResourceView); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle) { return fntable_Compositor_022_instance->GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_022_instance->ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_022_instance->LockGLSharedTextureForAccess(glSharedTextureHandle); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle) { return fntable_Compositor_022_instance->UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_022_instance->GetVulkanInstanceExtensionsRequired(pchValue, unBufferSize); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize) { return fntable_Compositor_022_instance->GetVulkanDeviceExtensionsRequired(pPhysicalDevice, pchValue, unBufferSize); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_SetExplicitTimingMode(vr::IVRCompositor_022::EVRCompositorTimingMode eTimingMode) { return fntable_Compositor_022_instance->SetExplicitTimingMode(eTimingMode); }
static vr::IVRCompositor_022::EVRCompositorError OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_SubmitExplicitTimingData() { return fntable_Compositor_022_instance->SubmitExplicitTimingData(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_IsMotionSmoothingEnabled() { return fntable_Compositor_022_instance->IsMotionSmoothingEnabled(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_IsMotionSmoothingSupported() { return fntable_Compositor_022_instance->IsMotionSmoothingSupported(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Compositor_022_impl_IsCurrentSceneFocusAppLoading() { return fntable_Compositor_022_instance->IsCurrentSceneFocusAppLoading(); }
static void *fntable_Compositor_022_funcs[] = {
	fntable_Compositor_022_impl_SetTrackingSpace,
	fntable_Compositor_022_impl_GetTrackingSpace,
	fntable_Compositor_022_impl_WaitGetPoses,
	fntable_Compositor_022_impl_GetLastPoses,
	fntable_Compositor_022_impl_GetLastPoseForTrackedDeviceIndex,
	fntable_Compositor_022_impl_Submit,
	fntable_Compositor_022_impl_ClearLastSubmittedFrame,
	fntable_Compositor_022_impl_PostPresentHandoff,
	fntable_Compositor_022_impl_GetFrameTiming,
	fntable_Compositor_022_impl_GetFrameTimings,
	fntable_Compositor_022_impl_GetFrameTimeRemaining,
	fntable_Compositor_022_impl_GetCumulativeStats,
	fntable_Compositor_022_impl_FadeToColor,
	fntable_Compositor_022_impl_GetCurrentFadeColor,
	fntable_Compositor_022_impl_FadeGrid,
	fntable_Compositor_022_impl_GetCurrentGridAlpha,
	fntable_Compositor_022_impl_SetSkyboxOverride,
	fntable_Compositor_022_impl_ClearSkyboxOverride,
	fntable_Compositor_022_impl_CompositorBringToFront,
	fntable_Compositor_022_impl_CompositorGoToBack,
	fntable_Compositor_022_impl_CompositorQuit,
	fntable_Compositor_022_impl_IsFullscreen,
	fntable_Compositor_022_impl_GetCurrentSceneFocusProcess,
	fntable_Compositor_022_impl_GetLastFrameRenderer,
	fntable_Compositor_022_impl_CanRenderScene,
	fntable_Compositor_022_impl_ShowMirrorWindow,
	fntable_Compositor_022_impl_HideMirrorWindow,
	fntable_Compositor_022_impl_IsMirrorWindowVisible,
	fntable_Compositor_022_impl_CompositorDumpImages,
	fntable_Compositor_022_impl_ShouldAppRenderWithLowResources,
	fntable_Compositor_022_impl_ForceInterleavedReprojectionOn,
	fntable_Compositor_022_impl_ForceReconnectProcess,
	fntable_Compositor_022_impl_SuspendRendering,
	fntable_Compositor_022_impl_GetMirrorTextureD3D11,
	fntable_Compositor_022_impl_ReleaseMirrorTextureD3D11,
	fntable_Compositor_022_impl_GetMirrorTextureGL,
	fntable_Compositor_022_impl_ReleaseSharedGLTexture,
	fntable_Compositor_022_impl_LockGLSharedTextureForAccess,
	fntable_Compositor_022_impl_UnlockGLSharedTextureForAccess,
	fntable_Compositor_022_impl_GetVulkanInstanceExtensionsRequired,
	fntable_Compositor_022_impl_GetVulkanDeviceExtensionsRequired,
	fntable_Compositor_022_impl_SetExplicitTimingMode,
	fntable_Compositor_022_impl_SubmitExplicitTimingData,
	fntable_Compositor_022_impl_IsMotionSmoothingEnabled,
	fntable_Compositor_022_impl_IsMotionSmoothingSupported,
	fntable_Compositor_022_impl_IsCurrentSceneFocusAppLoading,
};
void** CVRCompositor_022::_GetStatFuncList() { fntable_Compositor_022_instance = this; return fntable_Compositor_022_funcs; }
#include "GVRSystem.gen.h"
// Single inst of BaseSystem
static std::weak_ptr<BaseSystem> _single_inst_System;
static BaseSystem *_single_inst_System_unsafe = NULL;
std::shared_ptr<BaseSystem> GetBaseSystem() { return _single_inst_System.lock(); };
BaseSystem* GetUnsafeBaseSystem() { return _single_inst_System_unsafe; };
std::shared_ptr<BaseSystem> GetCreateBaseSystem() {
	std::shared_ptr<BaseSystem> ret = _single_inst_System.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseSystem>(new BaseSystem(), [](BaseSystem *obj){ _single_inst_System_unsafe = NULL; delete obj; });
		_single_inst_System = ret;
		_single_inst_System_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRSystem_011:
CVRSystem_011::CVRSystem_011() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_011:
void CVRSystem_011::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_011::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
void CVRSystem_011::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
vr::DistortionCoordinates_t CVRSystem_011::ComputeDistortion(vr::EVREye eEye, float fU, float fV) { return base->ComputeDistortion(eEye, fU, fV); }
vr::HmdMatrix34_t CVRSystem_011::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_011::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_011::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_011::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
bool CVRSystem_011::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_011::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_011::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_011::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_011::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_011::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_011::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_011::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_011::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_011::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_011::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_011::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_011::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_011::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_011::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_011::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_011::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_011::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_011::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_011::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_011::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_011::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_011::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_011::GetHiddenAreaMesh(vr::EVREye eEye) { return base->GetHiddenAreaMesh(eEye); }
void CVRSystem_011::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_011::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_011::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_011::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_011::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_011::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_011::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_011::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_011::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_011::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
void CVRSystem_011::PerformanceTestEnableCapture(bool bEnable) { return base->PerformanceTestEnableCapture(bEnable); }
void CVRSystem_011::PerformanceTestReportFidelityLevelChange(int nFidelityLevel) { return base->PerformanceTestReportFidelityLevelChange(nFidelityLevel); }
// FnTable for CVRSystem_011:
static CVRSystem_011 *fntable_System_011_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_011_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return fntable_System_011_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_011_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static vr::DistortionCoordinates_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV) { return fntable_System_011_instance->ComputeDistortion(eEye, fU, fV); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_011_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_011_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetD3D9AdapterIndex() { return fntable_System_011_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_011_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_IsDisplayOnDesktop() { return fntable_System_011_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_011_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_011_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_ResetSeatedZeroPose() { return fntable_System_011_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_011_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_011_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_011_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_011_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_011_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_011_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_011_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_011_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_011_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_011_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_011_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_011_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_011_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_011_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetHiddenAreaMesh(vr::EVREye eEye) { return fntable_System_011_instance->GetHiddenAreaMesh(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState) { return fntable_System_011_instance->GetControllerState(unControllerDeviceIndex, pControllerState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_011_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_011_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_011_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_011_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_CaptureInputFocus() { return fntable_System_011_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_ReleaseInputFocus() { return fntable_System_011_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_011_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_011_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_011_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_AcknowledgeQuit_Exiting() { return fntable_System_011_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_011_instance->AcknowledgeQuit_UserPrompt(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_PerformanceTestEnableCapture(bool bEnable) { return fntable_System_011_instance->PerformanceTestEnableCapture(bEnable); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_011_impl_PerformanceTestReportFidelityLevelChange(int nFidelityLevel) { return fntable_System_011_instance->PerformanceTestReportFidelityLevelChange(nFidelityLevel); }
static void *fntable_System_011_funcs[] = {
	fntable_System_011_impl_GetRecommendedRenderTargetSize,
	fntable_System_011_impl_GetProjectionMatrix,
	fntable_System_011_impl_GetProjectionRaw,
	fntable_System_011_impl_ComputeDistortion,
	fntable_System_011_impl_GetEyeToHeadTransform,
	fntable_System_011_impl_GetTimeSinceLastVsync,
	fntable_System_011_impl_GetD3D9AdapterIndex,
	fntable_System_011_impl_GetDXGIOutputInfo,
	fntable_System_011_impl_IsDisplayOnDesktop,
	fntable_System_011_impl_SetDisplayVisibility,
	fntable_System_011_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_011_impl_ResetSeatedZeroPose,
	fntable_System_011_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_011_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_011_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_011_impl_GetTrackedDeviceActivityLevel,
	fntable_System_011_impl_ApplyTransform,
	fntable_System_011_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_011_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_011_impl_GetTrackedDeviceClass,
	fntable_System_011_impl_IsTrackedDeviceConnected,
	fntable_System_011_impl_GetBoolTrackedDeviceProperty,
	fntable_System_011_impl_GetFloatTrackedDeviceProperty,
	fntable_System_011_impl_GetInt32TrackedDeviceProperty,
	fntable_System_011_impl_GetUint64TrackedDeviceProperty,
	fntable_System_011_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_011_impl_GetStringTrackedDeviceProperty,
	fntable_System_011_impl_GetPropErrorNameFromEnum,
	fntable_System_011_impl_PollNextEvent,
	fntable_System_011_impl_PollNextEventWithPose,
	fntable_System_011_impl_GetEventTypeNameFromEnum,
	fntable_System_011_impl_GetHiddenAreaMesh,
	fntable_System_011_impl_GetControllerState,
	fntable_System_011_impl_GetControllerStateWithPose,
	fntable_System_011_impl_TriggerHapticPulse,
	fntable_System_011_impl_GetButtonIdNameFromEnum,
	fntable_System_011_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_011_impl_CaptureInputFocus,
	fntable_System_011_impl_ReleaseInputFocus,
	fntable_System_011_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_011_impl_DriverDebugRequest,
	fntable_System_011_impl_PerformFirmwareUpdate,
	fntable_System_011_impl_AcknowledgeQuit_Exiting,
	fntable_System_011_impl_AcknowledgeQuit_UserPrompt,
	fntable_System_011_impl_PerformanceTestEnableCapture,
	fntable_System_011_impl_PerformanceTestReportFidelityLevelChange,
};
void** CVRSystem_011::_GetStatFuncList() { fntable_System_011_instance = this; return fntable_System_011_funcs; }
// Misc for CVRSystem_012:
CVRSystem_012::CVRSystem_012() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_012:
void CVRSystem_012::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_012::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
void CVRSystem_012::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
vr::DistortionCoordinates_t CVRSystem_012::ComputeDistortion(vr::EVREye eEye, float fU, float fV) { return base->ComputeDistortion(eEye, fU, fV); }
vr::HmdMatrix34_t CVRSystem_012::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_012::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_012::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_012::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
bool CVRSystem_012::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_012::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_012::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_012::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_012::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_012::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_012::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_012::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_012::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_012::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_012::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_012::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_012::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_012::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_012::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_012::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_012::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_012::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_012::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_012::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_012::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_012::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_012::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_012::GetHiddenAreaMesh(vr::EVREye eEye) { return base->GetHiddenAreaMesh(eEye); }
void CVRSystem_012::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_012::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_012::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_012::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_012::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_012::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_012::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_012::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_012::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_012::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_012:
static CVRSystem_012 *fntable_System_012_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_012_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return fntable_System_012_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_012_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static vr::DistortionCoordinates_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV) { return fntable_System_012_instance->ComputeDistortion(eEye, fU, fV); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_012_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_012_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetD3D9AdapterIndex() { return fntable_System_012_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_012_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_IsDisplayOnDesktop() { return fntable_System_012_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_012_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_012_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_ResetSeatedZeroPose() { return fntable_System_012_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_012_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_012_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_012_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_012_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_012_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_012_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_012_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_012_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_012_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_012_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_012_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_012_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_012_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_012_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetHiddenAreaMesh(vr::EVREye eEye) { return fntable_System_012_instance->GetHiddenAreaMesh(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState) { return fntable_System_012_instance->GetControllerState(unControllerDeviceIndex, pControllerState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_012_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_012_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_012_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_012_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_CaptureInputFocus() { return fntable_System_012_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_ReleaseInputFocus() { return fntable_System_012_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_012_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_012_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_012_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_AcknowledgeQuit_Exiting() { return fntable_System_012_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_012_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_012_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_012_funcs[] = {
	fntable_System_012_impl_GetRecommendedRenderTargetSize,
	fntable_System_012_impl_GetProjectionMatrix,
	fntable_System_012_impl_GetProjectionRaw,
	fntable_System_012_impl_ComputeDistortion,
	fntable_System_012_impl_GetEyeToHeadTransform,
	fntable_System_012_impl_GetTimeSinceLastVsync,
	fntable_System_012_impl_GetD3D9AdapterIndex,
	fntable_System_012_impl_GetDXGIOutputInfo,
	fntable_System_012_impl_IsDisplayOnDesktop,
	fntable_System_012_impl_SetDisplayVisibility,
	fntable_System_012_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_012_impl_ResetSeatedZeroPose,
	fntable_System_012_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_012_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_012_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_012_impl_GetTrackedDeviceActivityLevel,
	fntable_System_012_impl_ApplyTransform,
	fntable_System_012_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_012_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_012_impl_GetTrackedDeviceClass,
	fntable_System_012_impl_IsTrackedDeviceConnected,
	fntable_System_012_impl_GetBoolTrackedDeviceProperty,
	fntable_System_012_impl_GetFloatTrackedDeviceProperty,
	fntable_System_012_impl_GetInt32TrackedDeviceProperty,
	fntable_System_012_impl_GetUint64TrackedDeviceProperty,
	fntable_System_012_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_012_impl_GetStringTrackedDeviceProperty,
	fntable_System_012_impl_GetPropErrorNameFromEnum,
	fntable_System_012_impl_PollNextEvent,
	fntable_System_012_impl_PollNextEventWithPose,
	fntable_System_012_impl_GetEventTypeNameFromEnum,
	fntable_System_012_impl_GetHiddenAreaMesh,
	fntable_System_012_impl_GetControllerState,
	fntable_System_012_impl_GetControllerStateWithPose,
	fntable_System_012_impl_TriggerHapticPulse,
	fntable_System_012_impl_GetButtonIdNameFromEnum,
	fntable_System_012_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_012_impl_CaptureInputFocus,
	fntable_System_012_impl_ReleaseInputFocus,
	fntable_System_012_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_012_impl_DriverDebugRequest,
	fntable_System_012_impl_PerformFirmwareUpdate,
	fntable_System_012_impl_AcknowledgeQuit_Exiting,
	fntable_System_012_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_012::_GetStatFuncList() { fntable_System_012_instance = this; return fntable_System_012_funcs; }
// Misc for CVRSystem_014:
CVRSystem_014::CVRSystem_014() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_014:
void CVRSystem_014::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_014::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
void CVRSystem_014::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_014::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_014::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_014::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_014::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_014::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
bool CVRSystem_014::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_014::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_014::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_014::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_014::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_014::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_014::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_014::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_014::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_014::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_014::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_014::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_014::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_014::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_014::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_014::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_014::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_014::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_014::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_014::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_014::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_014::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_014::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_014::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_014::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_014::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_014::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_014::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_014::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_014::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_014::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_014::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_014::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_014::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_014::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_014::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_014:
static CVRSystem_014 *fntable_System_014_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_014_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType) { return fntable_System_014_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_014_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_014_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_014_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_014_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetD3D9AdapterIndex() { return fntable_System_014_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_014_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_IsDisplayOnDesktop() { return fntable_System_014_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_014_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_014_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_ResetSeatedZeroPose() { return fntable_System_014_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_014_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_014_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_014_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_014_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_014_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_014_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_014_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_014_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_014_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_014_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_014_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_014_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_014_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_014_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_014_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_014_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_014_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_014_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_014_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_014_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_CaptureInputFocus() { return fntable_System_014_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_ReleaseInputFocus() { return fntable_System_014_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_014_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_014_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_014_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_AcknowledgeQuit_Exiting() { return fntable_System_014_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_014_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_014_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_014_funcs[] = {
	fntable_System_014_impl_GetRecommendedRenderTargetSize,
	fntable_System_014_impl_GetProjectionMatrix,
	fntable_System_014_impl_GetProjectionRaw,
	fntable_System_014_impl_ComputeDistortion,
	fntable_System_014_impl_GetEyeToHeadTransform,
	fntable_System_014_impl_GetTimeSinceLastVsync,
	fntable_System_014_impl_GetD3D9AdapterIndex,
	fntable_System_014_impl_GetDXGIOutputInfo,
	fntable_System_014_impl_IsDisplayOnDesktop,
	fntable_System_014_impl_SetDisplayVisibility,
	fntable_System_014_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_014_impl_ResetSeatedZeroPose,
	fntable_System_014_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_014_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_014_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_014_impl_GetTrackedDeviceActivityLevel,
	fntable_System_014_impl_ApplyTransform,
	fntable_System_014_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_014_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_014_impl_GetTrackedDeviceClass,
	fntable_System_014_impl_IsTrackedDeviceConnected,
	fntable_System_014_impl_GetBoolTrackedDeviceProperty,
	fntable_System_014_impl_GetFloatTrackedDeviceProperty,
	fntable_System_014_impl_GetInt32TrackedDeviceProperty,
	fntable_System_014_impl_GetUint64TrackedDeviceProperty,
	fntable_System_014_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_014_impl_GetStringTrackedDeviceProperty,
	fntable_System_014_impl_GetPropErrorNameFromEnum,
	fntable_System_014_impl_PollNextEvent,
	fntable_System_014_impl_PollNextEventWithPose,
	fntable_System_014_impl_GetEventTypeNameFromEnum,
	fntable_System_014_impl_GetHiddenAreaMesh,
	fntable_System_014_impl_GetControllerState,
	fntable_System_014_impl_GetControllerStateWithPose,
	fntable_System_014_impl_TriggerHapticPulse,
	fntable_System_014_impl_GetButtonIdNameFromEnum,
	fntable_System_014_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_014_impl_CaptureInputFocus,
	fntable_System_014_impl_ReleaseInputFocus,
	fntable_System_014_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_014_impl_DriverDebugRequest,
	fntable_System_014_impl_PerformFirmwareUpdate,
	fntable_System_014_impl_AcknowledgeQuit_Exiting,
	fntable_System_014_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_014::_GetStatFuncList() { fntable_System_014_instance = this; return fntable_System_014_funcs; }
// Misc for CVRSystem_015:
CVRSystem_015::CVRSystem_015() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_015:
void CVRSystem_015::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_015::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
void CVRSystem_015::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_015::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_015::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_015::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_015::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_015::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
bool CVRSystem_015::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_015::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_015::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_015::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_015::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_015::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_015::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_015::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_015::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_015::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_015::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_015::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_015::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_015::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_015::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_015::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_015::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_015::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_015::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_015::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_015::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_015::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_015::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_015::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_015::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_015::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_015::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_015::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_015::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_015::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_015::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_015::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_015::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_015::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_015::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_015::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_015:
static CVRSystem_015 *fntable_System_015_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_015_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return fntable_System_015_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_015_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_015_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_015_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_015_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetD3D9AdapterIndex() { return fntable_System_015_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_015_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_IsDisplayOnDesktop() { return fntable_System_015_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_015_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_015_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_ResetSeatedZeroPose() { return fntable_System_015_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_015_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_015_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_015_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_015_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_015_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_015_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_015_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_015_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_015_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_015_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_015_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_015_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_015_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_015_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_015_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_015_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_015_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_015_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_015_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_015_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_CaptureInputFocus() { return fntable_System_015_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_ReleaseInputFocus() { return fntable_System_015_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_015_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_015_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_015_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_AcknowledgeQuit_Exiting() { return fntable_System_015_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_015_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_015_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_015_funcs[] = {
	fntable_System_015_impl_GetRecommendedRenderTargetSize,
	fntable_System_015_impl_GetProjectionMatrix,
	fntable_System_015_impl_GetProjectionRaw,
	fntable_System_015_impl_ComputeDistortion,
	fntable_System_015_impl_GetEyeToHeadTransform,
	fntable_System_015_impl_GetTimeSinceLastVsync,
	fntable_System_015_impl_GetD3D9AdapterIndex,
	fntable_System_015_impl_GetDXGIOutputInfo,
	fntable_System_015_impl_IsDisplayOnDesktop,
	fntable_System_015_impl_SetDisplayVisibility,
	fntable_System_015_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_015_impl_ResetSeatedZeroPose,
	fntable_System_015_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_015_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_015_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_015_impl_GetTrackedDeviceActivityLevel,
	fntable_System_015_impl_ApplyTransform,
	fntable_System_015_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_015_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_015_impl_GetTrackedDeviceClass,
	fntable_System_015_impl_IsTrackedDeviceConnected,
	fntable_System_015_impl_GetBoolTrackedDeviceProperty,
	fntable_System_015_impl_GetFloatTrackedDeviceProperty,
	fntable_System_015_impl_GetInt32TrackedDeviceProperty,
	fntable_System_015_impl_GetUint64TrackedDeviceProperty,
	fntable_System_015_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_015_impl_GetStringTrackedDeviceProperty,
	fntable_System_015_impl_GetPropErrorNameFromEnum,
	fntable_System_015_impl_PollNextEvent,
	fntable_System_015_impl_PollNextEventWithPose,
	fntable_System_015_impl_GetEventTypeNameFromEnum,
	fntable_System_015_impl_GetHiddenAreaMesh,
	fntable_System_015_impl_GetControllerState,
	fntable_System_015_impl_GetControllerStateWithPose,
	fntable_System_015_impl_TriggerHapticPulse,
	fntable_System_015_impl_GetButtonIdNameFromEnum,
	fntable_System_015_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_015_impl_CaptureInputFocus,
	fntable_System_015_impl_ReleaseInputFocus,
	fntable_System_015_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_015_impl_DriverDebugRequest,
	fntable_System_015_impl_PerformFirmwareUpdate,
	fntable_System_015_impl_AcknowledgeQuit_Exiting,
	fntable_System_015_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_015::_GetStatFuncList() { fntable_System_015_instance = this; return fntable_System_015_funcs; }
// Misc for CVRSystem_016:
CVRSystem_016::CVRSystem_016() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_016:
void CVRSystem_016::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_016::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
void CVRSystem_016::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_016::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_016::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_016::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_016::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_016::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
void CVRSystem_016::GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType) { return base->GetOutputDevice(pnDevice, textureType); }
bool CVRSystem_016::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_016::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_016::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_016::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_016::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_016::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_016::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_016::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_016::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_016::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_016::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_016::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_016::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_016::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_016::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_016::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_016::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_016::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_016::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_016::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_016::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_016::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_016::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_016::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_016::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_016::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_016::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_016::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_016::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_016::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_016::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_016::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_016::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_016::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_016::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_016::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_016:
static CVRSystem_016 *fntable_System_016_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_016_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return fntable_System_016_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_016_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_016_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_016_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_016_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetD3D9AdapterIndex() { return fntable_System_016_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_016_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType) { return fntable_System_016_instance->GetOutputDevice(pnDevice, textureType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_IsDisplayOnDesktop() { return fntable_System_016_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_016_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_016_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_ResetSeatedZeroPose() { return fntable_System_016_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_016_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_016_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_016_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_016_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_016_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_016_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_016_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_016_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_016_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_016_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_016_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_016_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_016_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_016_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_016_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_016_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_016_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_016_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_016_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_016_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_CaptureInputFocus() { return fntable_System_016_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_ReleaseInputFocus() { return fntable_System_016_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_016_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_016_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_016_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_AcknowledgeQuit_Exiting() { return fntable_System_016_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_016_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_016_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_016_funcs[] = {
	fntable_System_016_impl_GetRecommendedRenderTargetSize,
	fntable_System_016_impl_GetProjectionMatrix,
	fntable_System_016_impl_GetProjectionRaw,
	fntable_System_016_impl_ComputeDistortion,
	fntable_System_016_impl_GetEyeToHeadTransform,
	fntable_System_016_impl_GetTimeSinceLastVsync,
	fntable_System_016_impl_GetD3D9AdapterIndex,
	fntable_System_016_impl_GetDXGIOutputInfo,
	fntable_System_016_impl_GetOutputDevice,
	fntable_System_016_impl_IsDisplayOnDesktop,
	fntable_System_016_impl_SetDisplayVisibility,
	fntable_System_016_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_016_impl_ResetSeatedZeroPose,
	fntable_System_016_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_016_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_016_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_016_impl_GetTrackedDeviceActivityLevel,
	fntable_System_016_impl_ApplyTransform,
	fntable_System_016_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_016_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_016_impl_GetTrackedDeviceClass,
	fntable_System_016_impl_IsTrackedDeviceConnected,
	fntable_System_016_impl_GetBoolTrackedDeviceProperty,
	fntable_System_016_impl_GetFloatTrackedDeviceProperty,
	fntable_System_016_impl_GetInt32TrackedDeviceProperty,
	fntable_System_016_impl_GetUint64TrackedDeviceProperty,
	fntable_System_016_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_016_impl_GetStringTrackedDeviceProperty,
	fntable_System_016_impl_GetPropErrorNameFromEnum,
	fntable_System_016_impl_PollNextEvent,
	fntable_System_016_impl_PollNextEventWithPose,
	fntable_System_016_impl_GetEventTypeNameFromEnum,
	fntable_System_016_impl_GetHiddenAreaMesh,
	fntable_System_016_impl_GetControllerState,
	fntable_System_016_impl_GetControllerStateWithPose,
	fntable_System_016_impl_TriggerHapticPulse,
	fntable_System_016_impl_GetButtonIdNameFromEnum,
	fntable_System_016_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_016_impl_CaptureInputFocus,
	fntable_System_016_impl_ReleaseInputFocus,
	fntable_System_016_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_016_impl_DriverDebugRequest,
	fntable_System_016_impl_PerformFirmwareUpdate,
	fntable_System_016_impl_AcknowledgeQuit_Exiting,
	fntable_System_016_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_016::_GetStatFuncList() { fntable_System_016_instance = this; return fntable_System_016_funcs; }
// Misc for CVRSystem_017:
CVRSystem_017::CVRSystem_017() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_017:
void CVRSystem_017::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_017::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
void CVRSystem_017::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_017::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_017::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_017::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_017::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_017::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
void CVRSystem_017::GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return base->GetOutputDevice(pnDevice, textureType, pInstance); }
bool CVRSystem_017::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_017::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_017::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_017::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_017::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_017::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_017::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_017::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_017::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_017::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_017::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_017::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_017::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_017::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_017::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_017::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_017::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_017::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_017::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_017::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_017::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_017::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_017::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_017::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_017::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_017::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_017::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_017::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_017::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_017::CaptureInputFocus() { return base->CaptureInputFocus(); }
void CVRSystem_017::ReleaseInputFocus() { return base->ReleaseInputFocus(); }
bool CVRSystem_017::IsInputFocusCapturedByAnotherProcess() { return base->IsInputFocusCapturedByAnotherProcess(); }
uint32_t CVRSystem_017::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_017::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_017::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_017::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_017:
static CVRSystem_017 *fntable_System_017_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_017_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return fntable_System_017_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_017_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_017_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_017_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_017_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetD3D9AdapterIndex() { return fntable_System_017_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_017_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return fntable_System_017_instance->GetOutputDevice(pnDevice, textureType, pInstance); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_IsDisplayOnDesktop() { return fntable_System_017_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_017_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_017_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_ResetSeatedZeroPose() { return fntable_System_017_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_017_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_017_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_017_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_017_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_017_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_017_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_017_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_017_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_017_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_017_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_017_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_017_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_017_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_017_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_017_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_017_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_017_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_017_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_017_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_017_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_CaptureInputFocus() { return fntable_System_017_instance->CaptureInputFocus(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_ReleaseInputFocus() { return fntable_System_017_instance->ReleaseInputFocus(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_IsInputFocusCapturedByAnotherProcess() { return fntable_System_017_instance->IsInputFocusCapturedByAnotherProcess(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_017_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_017_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_AcknowledgeQuit_Exiting() { return fntable_System_017_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_017_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_017_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_017_funcs[] = {
	fntable_System_017_impl_GetRecommendedRenderTargetSize,
	fntable_System_017_impl_GetProjectionMatrix,
	fntable_System_017_impl_GetProjectionRaw,
	fntable_System_017_impl_ComputeDistortion,
	fntable_System_017_impl_GetEyeToHeadTransform,
	fntable_System_017_impl_GetTimeSinceLastVsync,
	fntable_System_017_impl_GetD3D9AdapterIndex,
	fntable_System_017_impl_GetDXGIOutputInfo,
	fntable_System_017_impl_GetOutputDevice,
	fntable_System_017_impl_IsDisplayOnDesktop,
	fntable_System_017_impl_SetDisplayVisibility,
	fntable_System_017_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_017_impl_ResetSeatedZeroPose,
	fntable_System_017_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_017_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_017_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_017_impl_GetTrackedDeviceActivityLevel,
	fntable_System_017_impl_ApplyTransform,
	fntable_System_017_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_017_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_017_impl_GetTrackedDeviceClass,
	fntable_System_017_impl_IsTrackedDeviceConnected,
	fntable_System_017_impl_GetBoolTrackedDeviceProperty,
	fntable_System_017_impl_GetFloatTrackedDeviceProperty,
	fntable_System_017_impl_GetInt32TrackedDeviceProperty,
	fntable_System_017_impl_GetUint64TrackedDeviceProperty,
	fntable_System_017_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_017_impl_GetStringTrackedDeviceProperty,
	fntable_System_017_impl_GetPropErrorNameFromEnum,
	fntable_System_017_impl_PollNextEvent,
	fntable_System_017_impl_PollNextEventWithPose,
	fntable_System_017_impl_GetEventTypeNameFromEnum,
	fntable_System_017_impl_GetHiddenAreaMesh,
	fntable_System_017_impl_GetControllerState,
	fntable_System_017_impl_GetControllerStateWithPose,
	fntable_System_017_impl_TriggerHapticPulse,
	fntable_System_017_impl_GetButtonIdNameFromEnum,
	fntable_System_017_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_017_impl_CaptureInputFocus,
	fntable_System_017_impl_ReleaseInputFocus,
	fntable_System_017_impl_IsInputFocusCapturedByAnotherProcess,
	fntable_System_017_impl_DriverDebugRequest,
	fntable_System_017_impl_PerformFirmwareUpdate,
	fntable_System_017_impl_AcknowledgeQuit_Exiting,
	fntable_System_017_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_017::_GetStatFuncList() { fntable_System_017_instance = this; return fntable_System_017_funcs; }
// Misc for CVRSystem_019:
CVRSystem_019::CVRSystem_019() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_019:
void CVRSystem_019::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_019::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
void CVRSystem_019::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_019::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_019::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_019::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_019::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_019::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
void CVRSystem_019::GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return base->GetOutputDevice(pnDevice, textureType, pInstance); }
bool CVRSystem_019::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_019::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_019::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_019::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_019::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_019::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_019::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_019::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_019::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_019::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_019::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_019::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_019::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_019::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_019::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_019::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_019::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_019::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_019::GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError); }
uint32_t CVRSystem_019::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_019::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_019::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_019::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_019::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_019::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_019::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_019::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_019::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_019::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_019::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_019::IsInputAvailable() { return base->IsInputAvailable(); }
bool CVRSystem_019::IsSteamVRDrawingControllers() { return base->IsSteamVRDrawingControllers(); }
bool CVRSystem_019::ShouldApplicationPause() { return base->ShouldApplicationPause(); }
bool CVRSystem_019::ShouldApplicationReduceRenderingWork() { return base->ShouldApplicationReduceRenderingWork(); }
uint32_t CVRSystem_019::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return base->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
vr::EVRFirmwareError CVRSystem_019::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_019::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_019::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
// FnTable for CVRSystem_019:
static CVRSystem_019 *fntable_System_019_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_019_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return fntable_System_019_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_019_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_019_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_019_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_019_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetD3D9AdapterIndex() { return fntable_System_019_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_019_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return fntable_System_019_instance->GetOutputDevice(pnDevice, textureType, pInstance); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_IsDisplayOnDesktop() { return fntable_System_019_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_019_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_019_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_ResetSeatedZeroPose() { return fntable_System_019_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_019_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_019_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_019_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_019_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_019_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_019_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_019_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_019_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_019_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_019_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_019_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_019_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_019_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_019_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_019_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_019_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_019_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_019_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_019_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_019_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_IsInputAvailable() { return fntable_System_019_instance->IsInputAvailable(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_IsSteamVRDrawingControllers() { return fntable_System_019_instance->IsSteamVRDrawingControllers(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_ShouldApplicationPause() { return fntable_System_019_instance->ShouldApplicationPause(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_ShouldApplicationReduceRenderingWork() { return fntable_System_019_instance->ShouldApplicationReduceRenderingWork(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) { return fntable_System_019_instance->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_019_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_AcknowledgeQuit_Exiting() { return fntable_System_019_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_019_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_019_instance->AcknowledgeQuit_UserPrompt(); }
static void *fntable_System_019_funcs[] = {
	fntable_System_019_impl_GetRecommendedRenderTargetSize,
	fntable_System_019_impl_GetProjectionMatrix,
	fntable_System_019_impl_GetProjectionRaw,
	fntable_System_019_impl_ComputeDistortion,
	fntable_System_019_impl_GetEyeToHeadTransform,
	fntable_System_019_impl_GetTimeSinceLastVsync,
	fntable_System_019_impl_GetD3D9AdapterIndex,
	fntable_System_019_impl_GetDXGIOutputInfo,
	fntable_System_019_impl_GetOutputDevice,
	fntable_System_019_impl_IsDisplayOnDesktop,
	fntable_System_019_impl_SetDisplayVisibility,
	fntable_System_019_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_019_impl_ResetSeatedZeroPose,
	fntable_System_019_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_019_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_019_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_019_impl_GetTrackedDeviceActivityLevel,
	fntable_System_019_impl_ApplyTransform,
	fntable_System_019_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_019_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_019_impl_GetTrackedDeviceClass,
	fntable_System_019_impl_IsTrackedDeviceConnected,
	fntable_System_019_impl_GetBoolTrackedDeviceProperty,
	fntable_System_019_impl_GetFloatTrackedDeviceProperty,
	fntable_System_019_impl_GetInt32TrackedDeviceProperty,
	fntable_System_019_impl_GetUint64TrackedDeviceProperty,
	fntable_System_019_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_019_impl_GetArrayTrackedDeviceProperty,
	fntable_System_019_impl_GetStringTrackedDeviceProperty,
	fntable_System_019_impl_GetPropErrorNameFromEnum,
	fntable_System_019_impl_PollNextEvent,
	fntable_System_019_impl_PollNextEventWithPose,
	fntable_System_019_impl_GetEventTypeNameFromEnum,
	fntable_System_019_impl_GetHiddenAreaMesh,
	fntable_System_019_impl_GetControllerState,
	fntable_System_019_impl_GetControllerStateWithPose,
	fntable_System_019_impl_TriggerHapticPulse,
	fntable_System_019_impl_GetButtonIdNameFromEnum,
	fntable_System_019_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_019_impl_IsInputAvailable,
	fntable_System_019_impl_IsSteamVRDrawingControllers,
	fntable_System_019_impl_ShouldApplicationPause,
	fntable_System_019_impl_ShouldApplicationReduceRenderingWork,
	fntable_System_019_impl_DriverDebugRequest,
	fntable_System_019_impl_PerformFirmwareUpdate,
	fntable_System_019_impl_AcknowledgeQuit_Exiting,
	fntable_System_019_impl_AcknowledgeQuit_UserPrompt,
};
void** CVRSystem_019::_GetStatFuncList() { fntable_System_019_instance = this; return fntable_System_019_funcs; }
// Misc for CVRSystem_020:
CVRSystem_020::CVRSystem_020() : base(GetCreateBaseSystem()) {}
// Interface methods for CVRSystem_020:
void CVRSystem_020::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
vr::HmdMatrix44_t CVRSystem_020::GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return base->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
void CVRSystem_020::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return base->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
bool CVRSystem_020::ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return base->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
vr::HmdMatrix34_t CVRSystem_020::GetEyeToHeadTransform(vr::EVREye eEye) { return base->GetEyeToHeadTransform(eEye); }
bool CVRSystem_020::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return base->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
int32_t CVRSystem_020::GetD3D9AdapterIndex() { return base->GetD3D9AdapterIndex(); }
void CVRSystem_020::GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex); }
void CVRSystem_020::GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return base->GetOutputDevice(pnDevice, textureType, pInstance); }
bool CVRSystem_020::IsDisplayOnDesktop() { return base->IsDisplayOnDesktop(); }
bool CVRSystem_020::SetDisplayVisibility(bool bIsVisibleOnDesktop) { return base->SetDisplayVisibility(bIsVisibleOnDesktop); }
void CVRSystem_020::GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRSystem_020::ResetSeatedZeroPose() { return base->ResetSeatedZeroPose(); }
vr::HmdMatrix34_t CVRSystem_020::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return base->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
vr::HmdMatrix34_t CVRSystem_020::GetRawZeroPoseToStandingAbsoluteTrackingPose() { return base->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
uint32_t CVRSystem_020::GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return base->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
vr::EDeviceActivityLevel CVRSystem_020::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return base->GetTrackedDeviceActivityLevel(unDeviceId); }
void CVRSystem_020::ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return base->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
vr::TrackedDeviceIndex_t CVRSystem_020::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return base->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
vr::ETrackedControllerRole CVRSystem_020::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
vr::ETrackedDeviceClass CVRSystem_020::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->GetTrackedDeviceClass(unDeviceIndex); }
bool CVRSystem_020::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->IsTrackedDeviceConnected(unDeviceIndex); }
bool CVRSystem_020::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
float CVRSystem_020::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
int32_t CVRSystem_020::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint64_t CVRSystem_020::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
vr::HmdMatrix34_t CVRSystem_020::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return base->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
uint32_t CVRSystem_020::GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError); }
uint32_t CVRSystem_020::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return base->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
const char* CVRSystem_020::GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return base->GetPropErrorNameFromEnum(error); }
bool CVRSystem_020::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
bool CVRSystem_020::PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
const char* CVRSystem_020::GetEventTypeNameFromEnum(vr::EVREventType eType) { return base->GetEventTypeNameFromEnum(eType); }
vr::HiddenAreaMesh_t CVRSystem_020::GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return base->GetHiddenAreaMesh(eEye, type); }
bool CVRSystem_020::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return base->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
bool CVRSystem_020::GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return base->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
void CVRSystem_020::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return base->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
const char* CVRSystem_020::GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return base->GetButtonIdNameFromEnum(eButtonId); }
const char* CVRSystem_020::GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return base->GetControllerAxisTypeNameFromEnum(eAxisType); }
bool CVRSystem_020::IsInputAvailable() { return base->IsInputAvailable(); }
bool CVRSystem_020::IsSteamVRDrawingControllers() { return base->IsSteamVRDrawingControllers(); }
bool CVRSystem_020::ShouldApplicationPause() { return base->ShouldApplicationPause(); }
bool CVRSystem_020::ShouldApplicationReduceRenderingWork() { return base->ShouldApplicationReduceRenderingWork(); }
vr::EVRFirmwareError CVRSystem_020::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return base->PerformFirmwareUpdate(unDeviceIndex); }
void CVRSystem_020::AcknowledgeQuit_Exiting() { return base->AcknowledgeQuit_Exiting(); }
void CVRSystem_020::AcknowledgeQuit_UserPrompt() { return base->AcknowledgeQuit_UserPrompt(); }
uint32_t CVRSystem_020::GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize) { return base->GetAppContainerFilePaths(pchBuffer, unBufferSize); }
const char* CVRSystem_020::GetRuntimeVersion() { return base->GetRuntimeVersion(); }
// FnTable for CVRSystem_020:
static CVRSystem_020 *fntable_System_020_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_System_020_instance->GetRecommendedRenderTargetSize(pnWidth, pnHeight); }
static vr::HmdMatrix44_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ) { return fntable_System_020_instance->GetProjectionMatrix(eEye, fNearZ, fFarZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) { return fntable_System_020_instance->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates) { return fntable_System_020_instance->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetEyeToHeadTransform(vr::EVREye eEye) { return fntable_System_020_instance->GetEyeToHeadTransform(eEye); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) { return fntable_System_020_instance->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetD3D9AdapterIndex() { return fntable_System_020_instance->GetD3D9AdapterIndex(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex) { return fntable_System_020_instance->GetDXGIOutputInfo(pnAdapterIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance) { return fntable_System_020_instance->GetOutputDevice(pnDevice, textureType, pInstance); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_IsDisplayOnDesktop() { return fntable_System_020_instance->IsDisplayOnDesktop(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_SetDisplayVisibility(bool bIsVisibleOnDesktop) { return fntable_System_020_instance->SetDisplayVisibility(bIsVisibleOnDesktop); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_System_020_instance->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_ResetSeatedZeroPose() { return fntable_System_020_instance->ResetSeatedZeroPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_020_instance->GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose() { return fntable_System_020_instance->GetRawZeroPoseToStandingAbsoluteTrackingPose(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) { return fntable_System_020_instance->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }
static vr::EDeviceActivityLevel OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) { return fntable_System_020_instance->GetTrackedDeviceActivityLevel(unDeviceId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform) { return fntable_System_020_instance->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) { return fntable_System_020_instance->GetTrackedDeviceIndexForControllerRole(unDeviceType); }
static vr::ETrackedControllerRole OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_020_instance->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }
static vr::ETrackedDeviceClass OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_020_instance->GetTrackedDeviceClass(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_020_instance->IsTrackedDeviceConnected(unDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static vr::HmdMatrix34_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError) { return fntable_System_020_instance->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetPropErrorNameFromEnum(vr::ETrackedPropertyError error) { return fntable_System_020_instance->GetPropErrorNameFromEnum(error); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_System_020_instance->PollNextEvent(pEvent, uncbVREvent); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_020_instance->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetEventTypeNameFromEnum(vr::EVREventType eType) { return fntable_System_020_instance->GetEventTypeNameFromEnum(eType); }
static vr::HiddenAreaMesh_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type) { return fntable_System_020_instance->GetHiddenAreaMesh(eEye, type); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize) { return fntable_System_020_instance->GetControllerState(unControllerDeviceIndex, pControllerState, unControllerStateSize); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose) { return fntable_System_020_instance->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) { return fntable_System_020_instance->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId) { return fntable_System_020_instance->GetButtonIdNameFromEnum(eButtonId); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType) { return fntable_System_020_instance->GetControllerAxisTypeNameFromEnum(eAxisType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_IsInputAvailable() { return fntable_System_020_instance->IsInputAvailable(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_IsSteamVRDrawingControllers() { return fntable_System_020_instance->IsSteamVRDrawingControllers(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_ShouldApplicationPause() { return fntable_System_020_instance->ShouldApplicationPause(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_ShouldApplicationReduceRenderingWork() { return fntable_System_020_instance->ShouldApplicationReduceRenderingWork(); }
static vr::EVRFirmwareError OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) { return fntable_System_020_instance->PerformFirmwareUpdate(unDeviceIndex); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_AcknowledgeQuit_Exiting() { return fntable_System_020_instance->AcknowledgeQuit_Exiting(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_AcknowledgeQuit_UserPrompt() { return fntable_System_020_instance->AcknowledgeQuit_UserPrompt(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize) { return fntable_System_020_instance->GetAppContainerFilePaths(pchBuffer, unBufferSize); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_System_020_impl_GetRuntimeVersion() { return fntable_System_020_instance->GetRuntimeVersion(); }
static void *fntable_System_020_funcs[] = {
	fntable_System_020_impl_GetRecommendedRenderTargetSize,
	fntable_System_020_impl_GetProjectionMatrix,
	fntable_System_020_impl_GetProjectionRaw,
	fntable_System_020_impl_ComputeDistortion,
	fntable_System_020_impl_GetEyeToHeadTransform,
	fntable_System_020_impl_GetTimeSinceLastVsync,
	fntable_System_020_impl_GetD3D9AdapterIndex,
	fntable_System_020_impl_GetDXGIOutputInfo,
	fntable_System_020_impl_GetOutputDevice,
	fntable_System_020_impl_IsDisplayOnDesktop,
	fntable_System_020_impl_SetDisplayVisibility,
	fntable_System_020_impl_GetDeviceToAbsoluteTrackingPose,
	fntable_System_020_impl_ResetSeatedZeroPose,
	fntable_System_020_impl_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_020_impl_GetRawZeroPoseToStandingAbsoluteTrackingPose,
	fntable_System_020_impl_GetSortedTrackedDeviceIndicesOfClass,
	fntable_System_020_impl_GetTrackedDeviceActivityLevel,
	fntable_System_020_impl_ApplyTransform,
	fntable_System_020_impl_GetTrackedDeviceIndexForControllerRole,
	fntable_System_020_impl_GetControllerRoleForTrackedDeviceIndex,
	fntable_System_020_impl_GetTrackedDeviceClass,
	fntable_System_020_impl_IsTrackedDeviceConnected,
	fntable_System_020_impl_GetBoolTrackedDeviceProperty,
	fntable_System_020_impl_GetFloatTrackedDeviceProperty,
	fntable_System_020_impl_GetInt32TrackedDeviceProperty,
	fntable_System_020_impl_GetUint64TrackedDeviceProperty,
	fntable_System_020_impl_GetMatrix34TrackedDeviceProperty,
	fntable_System_020_impl_GetArrayTrackedDeviceProperty,
	fntable_System_020_impl_GetStringTrackedDeviceProperty,
	fntable_System_020_impl_GetPropErrorNameFromEnum,
	fntable_System_020_impl_PollNextEvent,
	fntable_System_020_impl_PollNextEventWithPose,
	fntable_System_020_impl_GetEventTypeNameFromEnum,
	fntable_System_020_impl_GetHiddenAreaMesh,
	fntable_System_020_impl_GetControllerState,
	fntable_System_020_impl_GetControllerStateWithPose,
	fntable_System_020_impl_TriggerHapticPulse,
	fntable_System_020_impl_GetButtonIdNameFromEnum,
	fntable_System_020_impl_GetControllerAxisTypeNameFromEnum,
	fntable_System_020_impl_IsInputAvailable,
	fntable_System_020_impl_IsSteamVRDrawingControllers,
	fntable_System_020_impl_ShouldApplicationPause,
	fntable_System_020_impl_ShouldApplicationReduceRenderingWork,
	fntable_System_020_impl_PerformFirmwareUpdate,
	fntable_System_020_impl_AcknowledgeQuit_Exiting,
	fntable_System_020_impl_AcknowledgeQuit_UserPrompt,
	fntable_System_020_impl_GetAppContainerFilePaths,
	fntable_System_020_impl_GetRuntimeVersion,
};
void** CVRSystem_020::_GetStatFuncList() { fntable_System_020_instance = this; return fntable_System_020_funcs; }
#include "GVRChaperone.gen.h"
// Single inst of BaseChaperone
static std::weak_ptr<BaseChaperone> _single_inst_Chaperone;
static BaseChaperone *_single_inst_Chaperone_unsafe = NULL;
std::shared_ptr<BaseChaperone> GetBaseChaperone() { return _single_inst_Chaperone.lock(); };
BaseChaperone* GetUnsafeBaseChaperone() { return _single_inst_Chaperone_unsafe; };
std::shared_ptr<BaseChaperone> GetCreateBaseChaperone() {
	std::shared_ptr<BaseChaperone> ret = _single_inst_Chaperone.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseChaperone>(new BaseChaperone(), [](BaseChaperone *obj){ _single_inst_Chaperone_unsafe = NULL; delete obj; });
		_single_inst_Chaperone = ret;
		_single_inst_Chaperone_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRChaperone_003:
CVRChaperone_003::CVRChaperone_003() : base(GetCreateBaseChaperone()) {}
// Interface methods for CVRChaperone_003:
vr::IVRChaperone_003::ChaperoneCalibrationState CVRChaperone_003::GetCalibrationState() { return (vr::IVRChaperone_003::ChaperoneCalibrationState) base->GetCalibrationState(); }
bool CVRChaperone_003::GetPlayAreaSize(float* pSizeX, float* pSizeZ) { return base->GetPlayAreaSize(pSizeX, pSizeZ); }
bool CVRChaperone_003::GetPlayAreaRect(vr::HmdQuad_t* rect) { return base->GetPlayAreaRect(rect); }
void CVRChaperone_003::ReloadInfo() { return base->ReloadInfo(); }
void CVRChaperone_003::SetSceneColor(vr::HmdColor_t color) { return base->SetSceneColor(color); }
void CVRChaperone_003::GetBoundsColor(vr::HmdColor_t* pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t* pOutputCameraColor) { return base->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor); }
bool CVRChaperone_003::AreBoundsVisible() { return base->AreBoundsVisible(); }
void CVRChaperone_003::ForceBoundsVisible(bool bForce) { return base->ForceBoundsVisible(bForce); }
// FnTable for CVRChaperone_003:
static CVRChaperone_003 *fntable_Chaperone_003_instance = NULL;
static vr::IVRChaperone_003::ChaperoneCalibrationState OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_GetCalibrationState() { return fntable_Chaperone_003_instance->GetCalibrationState(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_GetPlayAreaSize(float* pSizeX, float* pSizeZ) { return fntable_Chaperone_003_instance->GetPlayAreaSize(pSizeX, pSizeZ); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_GetPlayAreaRect(vr::HmdQuad_t* rect) { return fntable_Chaperone_003_instance->GetPlayAreaRect(rect); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_ReloadInfo() { return fntable_Chaperone_003_instance->ReloadInfo(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_SetSceneColor(vr::HmdColor_t color) { return fntable_Chaperone_003_instance->SetSceneColor(color); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_GetBoundsColor(vr::HmdColor_t* pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t* pOutputCameraColor) { return fntable_Chaperone_003_instance->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_AreBoundsVisible() { return fntable_Chaperone_003_instance->AreBoundsVisible(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Chaperone_003_impl_ForceBoundsVisible(bool bForce) { return fntable_Chaperone_003_instance->ForceBoundsVisible(bForce); }
static void *fntable_Chaperone_003_funcs[] = {
	fntable_Chaperone_003_impl_GetCalibrationState,
	fntable_Chaperone_003_impl_GetPlayAreaSize,
	fntable_Chaperone_003_impl_GetPlayAreaRect,
	fntable_Chaperone_003_impl_ReloadInfo,
	fntable_Chaperone_003_impl_SetSceneColor,
	fntable_Chaperone_003_impl_GetBoundsColor,
	fntable_Chaperone_003_impl_AreBoundsVisible,
	fntable_Chaperone_003_impl_ForceBoundsVisible,
};
void** CVRChaperone_003::_GetStatFuncList() { fntable_Chaperone_003_instance = this; return fntable_Chaperone_003_funcs; }
#include "GVROverlay.gen.h"
// Single inst of BaseOverlay
static std::weak_ptr<BaseOverlay> _single_inst_Overlay;
static BaseOverlay *_single_inst_Overlay_unsafe = NULL;
std::shared_ptr<BaseOverlay> GetBaseOverlay() { return _single_inst_Overlay.lock(); };
BaseOverlay* GetUnsafeBaseOverlay() { return _single_inst_Overlay_unsafe; };
std::shared_ptr<BaseOverlay> GetCreateBaseOverlay() {
	std::shared_ptr<BaseOverlay> ret = _single_inst_Overlay.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseOverlay>(new BaseOverlay(), [](BaseOverlay *obj){ _single_inst_Overlay_unsafe = NULL; delete obj; });
		_single_inst_Overlay = ret;
		_single_inst_Overlay_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVROverlay_010:
CVROverlay_010::CVROverlay_010() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_010:
vr::EVROverlayError CVROverlay_010::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_010::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_010::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_010::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_010::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_010::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_010::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_010::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_010::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_010::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_010::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_010::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_010::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_010::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_010::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_010::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_010::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_010::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_010::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_010::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_010::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_010::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_010::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_010::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_010::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_010::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_010::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_010::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_010::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_010::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_010::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_010::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_010::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_010::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_010::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_010::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_010::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_010::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_010::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_010::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_010::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_010::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_010::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_010::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_010::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_010::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_010::SetOverlayNeighbor(vr::IVROverlay_010::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_010::MoveGamepadFocusToNeighbor(vr::IVROverlay_010::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_010::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_010::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_010::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_010::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_010::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_010::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_010::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_010::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_010::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_010::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_010::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_010::ShowKeyboard(vr::IVROverlay_010::EGamepadTextInputMode eInputMode, vr::IVROverlay_010::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_010::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::EGamepadTextInputMode eInputMode, vr::IVROverlay_010::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_010::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_010::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_010::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_010::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
// FnTable for CVROverlay_010:
static CVROverlay_010 *fntable_Overlay_010_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_010_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_010_instance->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetHighQualityOverlay() { return fntable_Overlay_010_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_010_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_010_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_010_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_010_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_010_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_010_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_010_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_010_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_010_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_010_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_010_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_010_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_010_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_010_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_010_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_010_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_010_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_010_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayTransformType* peTransformType) { return fntable_Overlay_010_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_010_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_010_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_010_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_010_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_010_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_010_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_010_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_010_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_010_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::VROverlayInputMethod eInputMethod) { return fntable_Overlay_010_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_010_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_010_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_010::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_010::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_010_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_010_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetGamepadFocusOverlay() { return fntable_Overlay_010_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_010_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayNeighbor(vr::IVROverlay_010::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_010_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_010::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_010_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_010_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_010_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_010_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_010_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_IsDashboardVisible() { return fntable_Overlay_010_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_010_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_010_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_010_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_010_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_010_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ShowKeyboard(vr::IVROverlay_010::EGamepadTextInputMode eInputMode, vr::IVROverlay_010::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_010_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_010::EGamepadTextInputMode eInputMode, vr::IVROverlay_010::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_010_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_010_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_HideKeyboard() { return fntable_Overlay_010_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_010_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_010_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_010_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static void *fntable_Overlay_010_funcs[] = {
	fntable_Overlay_010_impl_FindOverlay,
	fntable_Overlay_010_impl_CreateOverlay,
	fntable_Overlay_010_impl_DestroyOverlay,
	fntable_Overlay_010_impl_SetHighQualityOverlay,
	fntable_Overlay_010_impl_GetHighQualityOverlay,
	fntable_Overlay_010_impl_GetOverlayKey,
	fntable_Overlay_010_impl_GetOverlayName,
	fntable_Overlay_010_impl_GetOverlayImageData,
	fntable_Overlay_010_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_010_impl_SetOverlayFlag,
	fntable_Overlay_010_impl_GetOverlayFlag,
	fntable_Overlay_010_impl_SetOverlayColor,
	fntable_Overlay_010_impl_GetOverlayColor,
	fntable_Overlay_010_impl_SetOverlayAlpha,
	fntable_Overlay_010_impl_GetOverlayAlpha,
	fntable_Overlay_010_impl_SetOverlayWidthInMeters,
	fntable_Overlay_010_impl_GetOverlayWidthInMeters,
	fntable_Overlay_010_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_010_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_010_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_010_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_010_impl_SetOverlayTextureBounds,
	fntable_Overlay_010_impl_GetOverlayTextureBounds,
	fntable_Overlay_010_impl_GetOverlayTransformType,
	fntable_Overlay_010_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_010_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_010_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_010_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_010_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_010_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_010_impl_ShowOverlay,
	fntable_Overlay_010_impl_HideOverlay,
	fntable_Overlay_010_impl_IsOverlayVisible,
	fntable_Overlay_010_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_010_impl_PollNextOverlayEvent,
	fntable_Overlay_010_impl_GetOverlayInputMethod,
	fntable_Overlay_010_impl_SetOverlayInputMethod,
	fntable_Overlay_010_impl_GetOverlayMouseScale,
	fntable_Overlay_010_impl_SetOverlayMouseScale,
	fntable_Overlay_010_impl_ComputeOverlayIntersection,
	fntable_Overlay_010_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_010_impl_IsHoverTargetOverlay,
	fntable_Overlay_010_impl_GetGamepadFocusOverlay,
	fntable_Overlay_010_impl_SetGamepadFocusOverlay,
	fntable_Overlay_010_impl_SetOverlayNeighbor,
	fntable_Overlay_010_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_010_impl_SetOverlayTexture,
	fntable_Overlay_010_impl_ClearOverlayTexture,
	fntable_Overlay_010_impl_SetOverlayRaw,
	fntable_Overlay_010_impl_SetOverlayFromFile,
	fntable_Overlay_010_impl_CreateDashboardOverlay,
	fntable_Overlay_010_impl_IsDashboardVisible,
	fntable_Overlay_010_impl_IsActiveDashboardOverlay,
	fntable_Overlay_010_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_010_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_010_impl_ShowDashboard,
	fntable_Overlay_010_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_010_impl_ShowKeyboard,
	fntable_Overlay_010_impl_ShowKeyboardForOverlay,
	fntable_Overlay_010_impl_GetKeyboardText,
	fntable_Overlay_010_impl_HideKeyboard,
	fntable_Overlay_010_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_010_impl_SetKeyboardPositionForOverlay,
};
void** CVROverlay_010::_GetStatFuncList() { fntable_Overlay_010_instance = this; return fntable_Overlay_010_funcs; }
// Misc for CVROverlay_011:
CVROverlay_011::CVROverlay_011() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_011:
vr::EVROverlayError CVROverlay_011::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_011::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_011::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_011::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_011::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_011::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_011::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_011::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_011::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_011::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_011::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_011::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_011::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_011::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_011::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_011::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_011::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_011::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_011::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_011::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_011::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_011::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_011::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_011::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_011::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_011::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_011::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_011::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_011::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_011::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_011::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_011::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_011::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_011::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_011::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_011::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_011::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_011::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_011::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_011::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_011::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_011::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_011::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_011::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_011::SetOverlayNeighbor(vr::IVROverlay_011::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_011::MoveGamepadFocusToNeighbor(vr::IVROverlay_011::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_011::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_011::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_011::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_011::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_011::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_011::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_011::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_011::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_011::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_011::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_011::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_011::ShowKeyboard(vr::IVROverlay_011::EGamepadTextInputMode eInputMode, vr::IVROverlay_011::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_011::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::EGamepadTextInputMode eInputMode, vr::IVROverlay_011::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_011::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_011::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_011::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_011::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
// FnTable for CVROverlay_011:
static CVROverlay_011 *fntable_Overlay_011_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_011_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_011_instance->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetHighQualityOverlay() { return fntable_Overlay_011_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_011_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_011_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_011_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_011_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_011_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_011_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_011_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_011_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_011_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_011_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_011_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_011_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_011_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_011_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_011_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_011_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_011_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_011_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_011_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayTransformType* peTransformType) { return fntable_Overlay_011_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_011_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_011_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_011_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_011_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_011_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_011_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_011_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_011_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_011_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::VROverlayInputMethod eInputMethod) { return fntable_Overlay_011_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_011_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_011_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_011::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_011::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_011_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_011_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetGamepadFocusOverlay() { return fntable_Overlay_011_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_011_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayNeighbor(vr::IVROverlay_011::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_011_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_011::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_011_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_011_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_011_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_011_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, EGraphicsAPIConvention* pAPI, vr::EColorSpace* pColorSpace) { return fntable_Overlay_011_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPI, pColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_011_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_011_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_IsDashboardVisible() { return fntable_Overlay_011_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_011_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_011_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_011_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_011_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_011_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ShowKeyboard(vr::IVROverlay_011::EGamepadTextInputMode eInputMode, vr::IVROverlay_011::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_011_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_011::EGamepadTextInputMode eInputMode, vr::IVROverlay_011::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_011_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_011_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_HideKeyboard() { return fntable_Overlay_011_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_011_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_011_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_011_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static void *fntable_Overlay_011_funcs[] = {
	fntable_Overlay_011_impl_FindOverlay,
	fntable_Overlay_011_impl_CreateOverlay,
	fntable_Overlay_011_impl_DestroyOverlay,
	fntable_Overlay_011_impl_SetHighQualityOverlay,
	fntable_Overlay_011_impl_GetHighQualityOverlay,
	fntable_Overlay_011_impl_GetOverlayKey,
	fntable_Overlay_011_impl_GetOverlayName,
	fntable_Overlay_011_impl_GetOverlayImageData,
	fntable_Overlay_011_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_011_impl_SetOverlayRenderingPid,
	fntable_Overlay_011_impl_GetOverlayRenderingPid,
	fntable_Overlay_011_impl_SetOverlayFlag,
	fntable_Overlay_011_impl_GetOverlayFlag,
	fntable_Overlay_011_impl_SetOverlayColor,
	fntable_Overlay_011_impl_GetOverlayColor,
	fntable_Overlay_011_impl_SetOverlayAlpha,
	fntable_Overlay_011_impl_GetOverlayAlpha,
	fntable_Overlay_011_impl_SetOverlayWidthInMeters,
	fntable_Overlay_011_impl_GetOverlayWidthInMeters,
	fntable_Overlay_011_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_011_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_011_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_011_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_011_impl_SetOverlayTextureBounds,
	fntable_Overlay_011_impl_GetOverlayTextureBounds,
	fntable_Overlay_011_impl_GetOverlayTransformType,
	fntable_Overlay_011_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_011_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_011_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_011_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_011_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_011_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_011_impl_ShowOverlay,
	fntable_Overlay_011_impl_HideOverlay,
	fntable_Overlay_011_impl_IsOverlayVisible,
	fntable_Overlay_011_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_011_impl_PollNextOverlayEvent,
	fntable_Overlay_011_impl_GetOverlayInputMethod,
	fntable_Overlay_011_impl_SetOverlayInputMethod,
	fntable_Overlay_011_impl_GetOverlayMouseScale,
	fntable_Overlay_011_impl_SetOverlayMouseScale,
	fntable_Overlay_011_impl_ComputeOverlayIntersection,
	fntable_Overlay_011_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_011_impl_IsHoverTargetOverlay,
	fntable_Overlay_011_impl_GetGamepadFocusOverlay,
	fntable_Overlay_011_impl_SetGamepadFocusOverlay,
	fntable_Overlay_011_impl_SetOverlayNeighbor,
	fntable_Overlay_011_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_011_impl_SetOverlayTexture,
	fntable_Overlay_011_impl_ClearOverlayTexture,
	fntable_Overlay_011_impl_SetOverlayRaw,
	fntable_Overlay_011_impl_SetOverlayFromFile,
	fntable_Overlay_011_impl_GetOverlayTexture,
	fntable_Overlay_011_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_011_impl_CreateDashboardOverlay,
	fntable_Overlay_011_impl_IsDashboardVisible,
	fntable_Overlay_011_impl_IsActiveDashboardOverlay,
	fntable_Overlay_011_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_011_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_011_impl_ShowDashboard,
	fntable_Overlay_011_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_011_impl_ShowKeyboard,
	fntable_Overlay_011_impl_ShowKeyboardForOverlay,
	fntable_Overlay_011_impl_GetKeyboardText,
	fntable_Overlay_011_impl_HideKeyboard,
	fntable_Overlay_011_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_011_impl_SetKeyboardPositionForOverlay,
};
void** CVROverlay_011::_GetStatFuncList() { fntable_Overlay_011_instance = this; return fntable_Overlay_011_funcs; }
// Misc for CVROverlay_013:
CVROverlay_013::CVROverlay_013() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_013:
vr::EVROverlayError CVROverlay_013::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_013::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_013::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_013::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_013::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_013::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_013::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_013::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_013::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_013::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_013::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_013::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_013::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_013::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_013::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_013::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_013::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_013::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_013::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_013::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_013::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_013::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_013::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_013::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_013::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_013::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_013::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_013::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_013::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_013::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_013::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_013::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_013::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_013::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_013::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_013::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_013::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_013::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_013::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_013::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_013::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_013::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_013::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_013::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_013::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_013::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_013::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_013::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_013::SetOverlayNeighbor(vr::IVROverlay_013::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_013::MoveGamepadFocusToNeighbor(vr::IVROverlay_013::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_013::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_013::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_013::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_013::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_013::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_013::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_013::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_013::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_013::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_013::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_013::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_013::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_013::ShowKeyboard(vr::IVROverlay_013::EGamepadTextInputMode eInputMode, vr::IVROverlay_013::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_013::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::EGamepadTextInputMode eInputMode, vr::IVROverlay_013::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_013::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_013::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_013::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_013::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_013::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
// FnTable for CVROverlay_013:
static CVROverlay_013 *fntable_Overlay_013_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_013_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_013_instance->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetHighQualityOverlay() { return fntable_Overlay_013_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_013_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_013_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_013_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_013_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_013_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_013_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_013_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_013_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_013_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_013_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_013_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_013_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_013_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_013_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_013_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_013_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_013_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_013_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_013_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_013_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_013_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_013_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_013_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayTransformType* peTransformType) { return fntable_Overlay_013_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_013_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_013_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_013_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_013_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_013_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_013_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_013_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_013_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_013_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayInputMethod eInputMethod) { return fntable_Overlay_013_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_013_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_013_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_013::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_013::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_013_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_013_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetGamepadFocusOverlay() { return fntable_Overlay_013_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_013_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayNeighbor(vr::IVROverlay_013::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_013_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_013::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_013_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_013_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_013_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_013_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, EGraphicsAPIConvention* pAPI, vr::EColorSpace* pColorSpace) { return fntable_Overlay_013_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPI, pColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_013_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_013_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_013_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_IsDashboardVisible() { return fntable_Overlay_013_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_013_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_013_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_013_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_013_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_013_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ShowKeyboard(vr::IVROverlay_013::EGamepadTextInputMode eInputMode, vr::IVROverlay_013::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_013_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::EGamepadTextInputMode eInputMode, vr::IVROverlay_013::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_013_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_013_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_HideKeyboard() { return fntable_Overlay_013_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_013_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_013_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_013_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_013::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_013_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static void *fntable_Overlay_013_funcs[] = {
	fntable_Overlay_013_impl_FindOverlay,
	fntable_Overlay_013_impl_CreateOverlay,
	fntable_Overlay_013_impl_DestroyOverlay,
	fntable_Overlay_013_impl_SetHighQualityOverlay,
	fntable_Overlay_013_impl_GetHighQualityOverlay,
	fntable_Overlay_013_impl_GetOverlayKey,
	fntable_Overlay_013_impl_GetOverlayName,
	fntable_Overlay_013_impl_GetOverlayImageData,
	fntable_Overlay_013_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_013_impl_SetOverlayRenderingPid,
	fntable_Overlay_013_impl_GetOverlayRenderingPid,
	fntable_Overlay_013_impl_SetOverlayFlag,
	fntable_Overlay_013_impl_GetOverlayFlag,
	fntable_Overlay_013_impl_SetOverlayColor,
	fntable_Overlay_013_impl_GetOverlayColor,
	fntable_Overlay_013_impl_SetOverlayAlpha,
	fntable_Overlay_013_impl_GetOverlayAlpha,
	fntable_Overlay_013_impl_SetOverlayTexelAspect,
	fntable_Overlay_013_impl_GetOverlayTexelAspect,
	fntable_Overlay_013_impl_SetOverlaySortOrder,
	fntable_Overlay_013_impl_GetOverlaySortOrder,
	fntable_Overlay_013_impl_SetOverlayWidthInMeters,
	fntable_Overlay_013_impl_GetOverlayWidthInMeters,
	fntable_Overlay_013_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_013_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_013_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_013_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_013_impl_SetOverlayTextureBounds,
	fntable_Overlay_013_impl_GetOverlayTextureBounds,
	fntable_Overlay_013_impl_GetOverlayTransformType,
	fntable_Overlay_013_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_013_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_013_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_013_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_013_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_013_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_013_impl_ShowOverlay,
	fntable_Overlay_013_impl_HideOverlay,
	fntable_Overlay_013_impl_IsOverlayVisible,
	fntable_Overlay_013_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_013_impl_PollNextOverlayEvent,
	fntable_Overlay_013_impl_GetOverlayInputMethod,
	fntable_Overlay_013_impl_SetOverlayInputMethod,
	fntable_Overlay_013_impl_GetOverlayMouseScale,
	fntable_Overlay_013_impl_SetOverlayMouseScale,
	fntable_Overlay_013_impl_ComputeOverlayIntersection,
	fntable_Overlay_013_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_013_impl_IsHoverTargetOverlay,
	fntable_Overlay_013_impl_GetGamepadFocusOverlay,
	fntable_Overlay_013_impl_SetGamepadFocusOverlay,
	fntable_Overlay_013_impl_SetOverlayNeighbor,
	fntable_Overlay_013_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_013_impl_SetOverlayTexture,
	fntable_Overlay_013_impl_ClearOverlayTexture,
	fntable_Overlay_013_impl_SetOverlayRaw,
	fntable_Overlay_013_impl_SetOverlayFromFile,
	fntable_Overlay_013_impl_GetOverlayTexture,
	fntable_Overlay_013_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_013_impl_GetOverlayTextureSize,
	fntable_Overlay_013_impl_CreateDashboardOverlay,
	fntable_Overlay_013_impl_IsDashboardVisible,
	fntable_Overlay_013_impl_IsActiveDashboardOverlay,
	fntable_Overlay_013_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_013_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_013_impl_ShowDashboard,
	fntable_Overlay_013_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_013_impl_ShowKeyboard,
	fntable_Overlay_013_impl_ShowKeyboardForOverlay,
	fntable_Overlay_013_impl_GetKeyboardText,
	fntable_Overlay_013_impl_HideKeyboard,
	fntable_Overlay_013_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_013_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_013_impl_SetOverlayIntersectionMask,
};
void** CVROverlay_013::_GetStatFuncList() { fntable_Overlay_013_instance = this; return fntable_Overlay_013_funcs; }
// Misc for CVROverlay_014:
CVROverlay_014::CVROverlay_014() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_014:
vr::EVROverlayError CVROverlay_014::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_014::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_014::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_014::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_014::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_014::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_014::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_014::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_014::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_014::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_014::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_014::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_014::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_014::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_014::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_014::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_014::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_014::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_014::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_014::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_014::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_014::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_014::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_014::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_014::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_014::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_014::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_014::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_014::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_014::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_014::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_014::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_014::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_014::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_014::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_014::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_014::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_014::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_014::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_014::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_014::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_014::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_014::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_014::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_014::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_014::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_014::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_014::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_014::SetOverlayNeighbor(vr::IVROverlay_014::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_014::MoveGamepadFocusToNeighbor(vr::IVROverlay_014::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_014::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_014::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_014::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_014::GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return base->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
vr::EVROverlayError CVROverlay_014::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_014::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_014::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_014::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_014::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_014::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_014::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_014::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_014::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_014::ShowKeyboard(vr::IVROverlay_014::EGamepadTextInputMode eInputMode, vr::IVROverlay_014::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_014::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::EGamepadTextInputMode eInputMode, vr::IVROverlay_014::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_014::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_014::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_014::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_014::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_014::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
vr::EVROverlayError CVROverlay_014::GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return base->GetOverlayFlags(ulOverlayHandle, pFlags); }
vr::IVROverlay_014::VRMessageOverlayResponse CVROverlay_014::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return (vr::IVROverlay_014::VRMessageOverlayResponse) base->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
// FnTable for CVROverlay_014:
static CVROverlay_014 *fntable_Overlay_014_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_014_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_014_instance->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetHighQualityOverlay() { return fntable_Overlay_014_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_014_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_014_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_014_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_014_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_014_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_014_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_014_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_014_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_014_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_014_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_014_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_014_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_014_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_014_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_014_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_014_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_014_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_014_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_014_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_014_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_014_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_014_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_014_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayTransformType* peTransformType) { return fntable_Overlay_014_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_014_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_014_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_014_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_014_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_014_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_014_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_014_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_014_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_014_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayInputMethod eInputMethod) { return fntable_Overlay_014_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_014_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_014_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_014::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_014::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_014_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_014_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetGamepadFocusOverlay() { return fntable_Overlay_014_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_014_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayNeighbor(vr::IVROverlay_014::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_014_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_014::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_014_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_014_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_014_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_014_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return fntable_Overlay_014_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_014_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_014_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_014_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_IsDashboardVisible() { return fntable_Overlay_014_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_014_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_014_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_014_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_014_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_014_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ShowKeyboard(vr::IVROverlay_014::EGamepadTextInputMode eInputMode, vr::IVROverlay_014::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_014_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::EGamepadTextInputMode eInputMode, vr::IVROverlay_014::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_014_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_014_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_HideKeyboard() { return fntable_Overlay_014_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_014_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_014_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_014::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_014_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return fntable_Overlay_014_instance->GetOverlayFlags(ulOverlayHandle, pFlags); }
static vr::IVROverlay_014::VRMessageOverlayResponse OPENVR_FNTABLE_CALLTYPE fntable_Overlay_014_impl_ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return fntable_Overlay_014_instance->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
static void *fntable_Overlay_014_funcs[] = {
	fntable_Overlay_014_impl_FindOverlay,
	fntable_Overlay_014_impl_CreateOverlay,
	fntable_Overlay_014_impl_DestroyOverlay,
	fntable_Overlay_014_impl_SetHighQualityOverlay,
	fntable_Overlay_014_impl_GetHighQualityOverlay,
	fntable_Overlay_014_impl_GetOverlayKey,
	fntable_Overlay_014_impl_GetOverlayName,
	fntable_Overlay_014_impl_GetOverlayImageData,
	fntable_Overlay_014_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_014_impl_SetOverlayRenderingPid,
	fntable_Overlay_014_impl_GetOverlayRenderingPid,
	fntable_Overlay_014_impl_SetOverlayFlag,
	fntable_Overlay_014_impl_GetOverlayFlag,
	fntable_Overlay_014_impl_SetOverlayColor,
	fntable_Overlay_014_impl_GetOverlayColor,
	fntable_Overlay_014_impl_SetOverlayAlpha,
	fntable_Overlay_014_impl_GetOverlayAlpha,
	fntable_Overlay_014_impl_SetOverlayTexelAspect,
	fntable_Overlay_014_impl_GetOverlayTexelAspect,
	fntable_Overlay_014_impl_SetOverlaySortOrder,
	fntable_Overlay_014_impl_GetOverlaySortOrder,
	fntable_Overlay_014_impl_SetOverlayWidthInMeters,
	fntable_Overlay_014_impl_GetOverlayWidthInMeters,
	fntable_Overlay_014_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_014_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_014_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_014_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_014_impl_SetOverlayTextureBounds,
	fntable_Overlay_014_impl_GetOverlayTextureBounds,
	fntable_Overlay_014_impl_GetOverlayTransformType,
	fntable_Overlay_014_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_014_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_014_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_014_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_014_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_014_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_014_impl_ShowOverlay,
	fntable_Overlay_014_impl_HideOverlay,
	fntable_Overlay_014_impl_IsOverlayVisible,
	fntable_Overlay_014_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_014_impl_PollNextOverlayEvent,
	fntable_Overlay_014_impl_GetOverlayInputMethod,
	fntable_Overlay_014_impl_SetOverlayInputMethod,
	fntable_Overlay_014_impl_GetOverlayMouseScale,
	fntable_Overlay_014_impl_SetOverlayMouseScale,
	fntable_Overlay_014_impl_ComputeOverlayIntersection,
	fntable_Overlay_014_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_014_impl_IsHoverTargetOverlay,
	fntable_Overlay_014_impl_GetGamepadFocusOverlay,
	fntable_Overlay_014_impl_SetGamepadFocusOverlay,
	fntable_Overlay_014_impl_SetOverlayNeighbor,
	fntable_Overlay_014_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_014_impl_SetOverlayTexture,
	fntable_Overlay_014_impl_ClearOverlayTexture,
	fntable_Overlay_014_impl_SetOverlayRaw,
	fntable_Overlay_014_impl_SetOverlayFromFile,
	fntable_Overlay_014_impl_GetOverlayTexture,
	fntable_Overlay_014_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_014_impl_GetOverlayTextureSize,
	fntable_Overlay_014_impl_CreateDashboardOverlay,
	fntable_Overlay_014_impl_IsDashboardVisible,
	fntable_Overlay_014_impl_IsActiveDashboardOverlay,
	fntable_Overlay_014_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_014_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_014_impl_ShowDashboard,
	fntable_Overlay_014_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_014_impl_ShowKeyboard,
	fntable_Overlay_014_impl_ShowKeyboardForOverlay,
	fntable_Overlay_014_impl_GetKeyboardText,
	fntable_Overlay_014_impl_HideKeyboard,
	fntable_Overlay_014_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_014_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_014_impl_SetOverlayIntersectionMask,
	fntable_Overlay_014_impl_GetOverlayFlags,
	fntable_Overlay_014_impl_ShowMessageOverlay,
};
void** CVROverlay_014::_GetStatFuncList() { fntable_Overlay_014_instance = this; return fntable_Overlay_014_funcs; }
// Misc for CVROverlay_016:
CVROverlay_016::CVROverlay_016() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_016:
vr::EVROverlayError CVROverlay_016::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_016::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_016::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_016::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_016::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_016::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_016::SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return base->SetOverlayName(ulOverlayHandle, pchName); }
vr::EVROverlayError CVROverlay_016::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_016::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_016::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_016::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_016::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_016::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_016::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_016::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_016::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_016::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_016::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_016::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_016::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_016::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_016::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_016::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_016::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_016::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_016::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_016::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_016::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
uint32_t CVROverlay_016::GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return base->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
vr::EVROverlayError CVROverlay_016::SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return base->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
vr::EVROverlayError CVROverlay_016::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_016::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_016::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_016::GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_016::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_016::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_016::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_016::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_016::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_016::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_016::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_016::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_016::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_016::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_016::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_016::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_016::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_016::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_016::SetOverlayNeighbor(vr::IVROverlay_016::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_016::MoveGamepadFocusToNeighbor(vr::IVROverlay_016::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_016::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_016::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_016::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_016::GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return base->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
vr::EVROverlayError CVROverlay_016::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_016::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_016::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_016::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_016::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_016::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_016::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_016::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_016::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_016::ShowKeyboard(vr::IVROverlay_016::EGamepadTextInputMode eInputMode, vr::IVROverlay_016::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_016::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::EGamepadTextInputMode eInputMode, vr::IVROverlay_016::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_016::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_016::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_016::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_016::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_016::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
vr::EVROverlayError CVROverlay_016::GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return base->GetOverlayFlags(ulOverlayHandle, pFlags); }
vr::IVROverlay_016::VRMessageOverlayResponse CVROverlay_016::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return (vr::IVROverlay_016::VRMessageOverlayResponse) base->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
void CVROverlay_016::CloseMessageOverlay() { return base->CloseMessageOverlay(); }
// FnTable for CVROverlay_016:
static CVROverlay_016 *fntable_Overlay_016_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_016_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_016_instance->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetHighQualityOverlay() { return fntable_Overlay_016_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_016_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_016_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return fntable_Overlay_016_instance->SetOverlayName(ulOverlayHandle, pchName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_016_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_016_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_016_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_016_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_016_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_016_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_016_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_016_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_016_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_016_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_016_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_016_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_016_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_016_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_016_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_016_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_016_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_016_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_016_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_016_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_016_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return fntable_Overlay_016_instance->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return fntable_Overlay_016_instance->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayTransformType* peTransformType) { return fntable_Overlay_016_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_016_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_016_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_016_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_016_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_016_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_016_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_016_instance->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_016_instance->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_016_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_016_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_016_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayInputMethod eInputMethod) { return fntable_Overlay_016_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_016_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_016_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_016::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_016::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_016_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_016_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetGamepadFocusOverlay() { return fntable_Overlay_016_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_016_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayNeighbor(vr::IVROverlay_016::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_016_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_016::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_016_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_016_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_016_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_016_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return fntable_Overlay_016_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_016_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_016_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_016_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_IsDashboardVisible() { return fntable_Overlay_016_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_016_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_016_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_016_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_016_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_016_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ShowKeyboard(vr::IVROverlay_016::EGamepadTextInputMode eInputMode, vr::IVROverlay_016::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_016_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::EGamepadTextInputMode eInputMode, vr::IVROverlay_016::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_016_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_016_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_HideKeyboard() { return fntable_Overlay_016_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_016_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_016_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_016::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_016_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return fntable_Overlay_016_instance->GetOverlayFlags(ulOverlayHandle, pFlags); }
static vr::IVROverlay_016::VRMessageOverlayResponse OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return fntable_Overlay_016_instance->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_016_impl_CloseMessageOverlay() { return fntable_Overlay_016_instance->CloseMessageOverlay(); }
static void *fntable_Overlay_016_funcs[] = {
	fntable_Overlay_016_impl_FindOverlay,
	fntable_Overlay_016_impl_CreateOverlay,
	fntable_Overlay_016_impl_DestroyOverlay,
	fntable_Overlay_016_impl_SetHighQualityOverlay,
	fntable_Overlay_016_impl_GetHighQualityOverlay,
	fntable_Overlay_016_impl_GetOverlayKey,
	fntable_Overlay_016_impl_GetOverlayName,
	fntable_Overlay_016_impl_SetOverlayName,
	fntable_Overlay_016_impl_GetOverlayImageData,
	fntable_Overlay_016_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_016_impl_SetOverlayRenderingPid,
	fntable_Overlay_016_impl_GetOverlayRenderingPid,
	fntable_Overlay_016_impl_SetOverlayFlag,
	fntable_Overlay_016_impl_GetOverlayFlag,
	fntable_Overlay_016_impl_SetOverlayColor,
	fntable_Overlay_016_impl_GetOverlayColor,
	fntable_Overlay_016_impl_SetOverlayAlpha,
	fntable_Overlay_016_impl_GetOverlayAlpha,
	fntable_Overlay_016_impl_SetOverlayTexelAspect,
	fntable_Overlay_016_impl_GetOverlayTexelAspect,
	fntable_Overlay_016_impl_SetOverlaySortOrder,
	fntable_Overlay_016_impl_GetOverlaySortOrder,
	fntable_Overlay_016_impl_SetOverlayWidthInMeters,
	fntable_Overlay_016_impl_GetOverlayWidthInMeters,
	fntable_Overlay_016_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_016_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_016_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_016_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_016_impl_SetOverlayTextureBounds,
	fntable_Overlay_016_impl_GetOverlayTextureBounds,
	fntable_Overlay_016_impl_GetOverlayRenderModel,
	fntable_Overlay_016_impl_SetOverlayRenderModel,
	fntable_Overlay_016_impl_GetOverlayTransformType,
	fntable_Overlay_016_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_016_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_016_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_016_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_016_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_016_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_016_impl_GetOverlayTransformOverlayRelative,
	fntable_Overlay_016_impl_SetOverlayTransformOverlayRelative,
	fntable_Overlay_016_impl_ShowOverlay,
	fntable_Overlay_016_impl_HideOverlay,
	fntable_Overlay_016_impl_IsOverlayVisible,
	fntable_Overlay_016_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_016_impl_PollNextOverlayEvent,
	fntable_Overlay_016_impl_GetOverlayInputMethod,
	fntable_Overlay_016_impl_SetOverlayInputMethod,
	fntable_Overlay_016_impl_GetOverlayMouseScale,
	fntable_Overlay_016_impl_SetOverlayMouseScale,
	fntable_Overlay_016_impl_ComputeOverlayIntersection,
	fntable_Overlay_016_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_016_impl_IsHoverTargetOverlay,
	fntable_Overlay_016_impl_GetGamepadFocusOverlay,
	fntable_Overlay_016_impl_SetGamepadFocusOverlay,
	fntable_Overlay_016_impl_SetOverlayNeighbor,
	fntable_Overlay_016_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_016_impl_SetOverlayTexture,
	fntable_Overlay_016_impl_ClearOverlayTexture,
	fntable_Overlay_016_impl_SetOverlayRaw,
	fntable_Overlay_016_impl_SetOverlayFromFile,
	fntable_Overlay_016_impl_GetOverlayTexture,
	fntable_Overlay_016_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_016_impl_GetOverlayTextureSize,
	fntable_Overlay_016_impl_CreateDashboardOverlay,
	fntable_Overlay_016_impl_IsDashboardVisible,
	fntable_Overlay_016_impl_IsActiveDashboardOverlay,
	fntable_Overlay_016_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_016_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_016_impl_ShowDashboard,
	fntable_Overlay_016_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_016_impl_ShowKeyboard,
	fntable_Overlay_016_impl_ShowKeyboardForOverlay,
	fntable_Overlay_016_impl_GetKeyboardText,
	fntable_Overlay_016_impl_HideKeyboard,
	fntable_Overlay_016_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_016_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_016_impl_SetOverlayIntersectionMask,
	fntable_Overlay_016_impl_GetOverlayFlags,
	fntable_Overlay_016_impl_ShowMessageOverlay,
	fntable_Overlay_016_impl_CloseMessageOverlay,
};
void** CVROverlay_016::_GetStatFuncList() { fntable_Overlay_016_instance = this; return fntable_Overlay_016_funcs; }
// Misc for CVROverlay_017:
CVROverlay_017::CVROverlay_017() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_017:
vr::EVROverlayError CVROverlay_017::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_017::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_017::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_017::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_017::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_017::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_017::SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return base->SetOverlayName(ulOverlayHandle, pchName); }
vr::EVROverlayError CVROverlay_017::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_017::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_017::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_017::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_017::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_017::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_017::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_017::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_017::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_017::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_017::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_017::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_017::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_017::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_017::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_017::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_017::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_017::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_017::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_017::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_017::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
uint32_t CVROverlay_017::GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return base->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
vr::EVROverlayError CVROverlay_017::SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return base->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
vr::EVROverlayError CVROverlay_017::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_017::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_017::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_017::GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_017::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_017::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_017::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_017::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_017::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_017::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_017::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_017::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_017::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_017::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_017::HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return base->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
bool CVROverlay_017::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_017::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_017::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_017::SetOverlayNeighbor(vr::IVROverlay_017::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_017::MoveGamepadFocusToNeighbor(vr::IVROverlay_017::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_017::SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t& vCenter, float fRadius) { return base->SetOverlayDualAnalogTransform(ulOverlay, eWhich, vCenter, fRadius); }
vr::EVROverlayError CVROverlay_017::GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return base->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
vr::EVROverlayError CVROverlay_017::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_017::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_017::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_017::GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return base->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
vr::EVROverlayError CVROverlay_017::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_017::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_017::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_017::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_017::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_017::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_017::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_017::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_017::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_017::ShowKeyboard(vr::IVROverlay_017::EGamepadTextInputMode eInputMode, vr::IVROverlay_017::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_017::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::EGamepadTextInputMode eInputMode, vr::IVROverlay_017::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_017::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_017::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_017::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_017::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_017::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
vr::EVROverlayError CVROverlay_017::GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return base->GetOverlayFlags(ulOverlayHandle, pFlags); }
vr::IVROverlay_017::VRMessageOverlayResponse CVROverlay_017::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return (vr::IVROverlay_017::VRMessageOverlayResponse) base->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
void CVROverlay_017::CloseMessageOverlay() { return base->CloseMessageOverlay(); }
// FnTable for CVROverlay_017:
static CVROverlay_017 *fntable_Overlay_017_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_017_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_017_instance->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetHighQualityOverlay() { return fntable_Overlay_017_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_017_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_017_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return fntable_Overlay_017_instance->SetOverlayName(ulOverlayHandle, pchName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_017_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_017_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_017_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_017_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_017_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_017_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_017_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_017_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_017_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_017_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_017_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_017_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_017_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_017_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_017_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_017_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_017_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_017_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_017_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_017_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_017_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return fntable_Overlay_017_instance->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return fntable_Overlay_017_instance->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayTransformType* peTransformType) { return fntable_Overlay_017_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_017_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_017_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_017_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_017_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_017_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_017_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_017_instance->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_017_instance->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_017_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_017_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_017_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayInputMethod eInputMethod) { return fntable_Overlay_017_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_017_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_017_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_017::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_017::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_017_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_HandleControllerOverlayInteractionAsMouse(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unControllerDeviceIndex) { return fntable_Overlay_017_instance->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetGamepadFocusOverlay() { return fntable_Overlay_017_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_017_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayNeighbor(vr::IVROverlay_017::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_017_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_017::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_017_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t& vCenter, float fRadius) { return fntable_Overlay_017_instance->SetOverlayDualAnalogTransform(ulOverlay, eWhich, vCenter, fRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return fntable_Overlay_017_instance->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_017_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_017_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_017_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return fntable_Overlay_017_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_017_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_017_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_017_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_IsDashboardVisible() { return fntable_Overlay_017_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_017_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_017_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_017_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_017_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_017_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ShowKeyboard(vr::IVROverlay_017::EGamepadTextInputMode eInputMode, vr::IVROverlay_017::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_017_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::EGamepadTextInputMode eInputMode, vr::IVROverlay_017::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_017_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_017_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_HideKeyboard() { return fntable_Overlay_017_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_017_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_017_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_017::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_017_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return fntable_Overlay_017_instance->GetOverlayFlags(ulOverlayHandle, pFlags); }
static vr::IVROverlay_017::VRMessageOverlayResponse OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return fntable_Overlay_017_instance->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_017_impl_CloseMessageOverlay() { return fntable_Overlay_017_instance->CloseMessageOverlay(); }
static void *fntable_Overlay_017_funcs[] = {
	fntable_Overlay_017_impl_FindOverlay,
	fntable_Overlay_017_impl_CreateOverlay,
	fntable_Overlay_017_impl_DestroyOverlay,
	fntable_Overlay_017_impl_SetHighQualityOverlay,
	fntable_Overlay_017_impl_GetHighQualityOverlay,
	fntable_Overlay_017_impl_GetOverlayKey,
	fntable_Overlay_017_impl_GetOverlayName,
	fntable_Overlay_017_impl_SetOverlayName,
	fntable_Overlay_017_impl_GetOverlayImageData,
	fntable_Overlay_017_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_017_impl_SetOverlayRenderingPid,
	fntable_Overlay_017_impl_GetOverlayRenderingPid,
	fntable_Overlay_017_impl_SetOverlayFlag,
	fntable_Overlay_017_impl_GetOverlayFlag,
	fntable_Overlay_017_impl_SetOverlayColor,
	fntable_Overlay_017_impl_GetOverlayColor,
	fntable_Overlay_017_impl_SetOverlayAlpha,
	fntable_Overlay_017_impl_GetOverlayAlpha,
	fntable_Overlay_017_impl_SetOverlayTexelAspect,
	fntable_Overlay_017_impl_GetOverlayTexelAspect,
	fntable_Overlay_017_impl_SetOverlaySortOrder,
	fntable_Overlay_017_impl_GetOverlaySortOrder,
	fntable_Overlay_017_impl_SetOverlayWidthInMeters,
	fntable_Overlay_017_impl_GetOverlayWidthInMeters,
	fntable_Overlay_017_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_017_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_017_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_017_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_017_impl_SetOverlayTextureBounds,
	fntable_Overlay_017_impl_GetOverlayTextureBounds,
	fntable_Overlay_017_impl_GetOverlayRenderModel,
	fntable_Overlay_017_impl_SetOverlayRenderModel,
	fntable_Overlay_017_impl_GetOverlayTransformType,
	fntable_Overlay_017_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_017_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_017_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_017_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_017_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_017_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_017_impl_GetOverlayTransformOverlayRelative,
	fntable_Overlay_017_impl_SetOverlayTransformOverlayRelative,
	fntable_Overlay_017_impl_ShowOverlay,
	fntable_Overlay_017_impl_HideOverlay,
	fntable_Overlay_017_impl_IsOverlayVisible,
	fntable_Overlay_017_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_017_impl_PollNextOverlayEvent,
	fntable_Overlay_017_impl_GetOverlayInputMethod,
	fntable_Overlay_017_impl_SetOverlayInputMethod,
	fntable_Overlay_017_impl_GetOverlayMouseScale,
	fntable_Overlay_017_impl_SetOverlayMouseScale,
	fntable_Overlay_017_impl_ComputeOverlayIntersection,
	fntable_Overlay_017_impl_HandleControllerOverlayInteractionAsMouse,
	fntable_Overlay_017_impl_IsHoverTargetOverlay,
	fntable_Overlay_017_impl_GetGamepadFocusOverlay,
	fntable_Overlay_017_impl_SetGamepadFocusOverlay,
	fntable_Overlay_017_impl_SetOverlayNeighbor,
	fntable_Overlay_017_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_017_impl_SetOverlayDualAnalogTransform,
	fntable_Overlay_017_impl_GetOverlayDualAnalogTransform,
	fntable_Overlay_017_impl_SetOverlayTexture,
	fntable_Overlay_017_impl_ClearOverlayTexture,
	fntable_Overlay_017_impl_SetOverlayRaw,
	fntable_Overlay_017_impl_SetOverlayFromFile,
	fntable_Overlay_017_impl_GetOverlayTexture,
	fntable_Overlay_017_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_017_impl_GetOverlayTextureSize,
	fntable_Overlay_017_impl_CreateDashboardOverlay,
	fntable_Overlay_017_impl_IsDashboardVisible,
	fntable_Overlay_017_impl_IsActiveDashboardOverlay,
	fntable_Overlay_017_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_017_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_017_impl_ShowDashboard,
	fntable_Overlay_017_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_017_impl_ShowKeyboard,
	fntable_Overlay_017_impl_ShowKeyboardForOverlay,
	fntable_Overlay_017_impl_GetKeyboardText,
	fntable_Overlay_017_impl_HideKeyboard,
	fntable_Overlay_017_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_017_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_017_impl_SetOverlayIntersectionMask,
	fntable_Overlay_017_impl_GetOverlayFlags,
	fntable_Overlay_017_impl_ShowMessageOverlay,
	fntable_Overlay_017_impl_CloseMessageOverlay,
};
void** CVROverlay_017::_GetStatFuncList() { fntable_Overlay_017_instance = this; return fntable_Overlay_017_funcs; }
// Misc for CVROverlay_018:
CVROverlay_018::CVROverlay_018() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_018:
vr::EVROverlayError CVROverlay_018::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_018::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_018::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_018::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_018::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_018::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_018::SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return base->SetOverlayName(ulOverlayHandle, pchName); }
vr::EVROverlayError CVROverlay_018::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_018::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_018::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_018::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_018::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_018::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_018::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_018::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_018::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_018::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_018::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_018::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_018::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_018::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_018::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_018::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_018::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_018::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_018::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_018::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_018::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
uint32_t CVROverlay_018::GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return base->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
vr::EVROverlayError CVROverlay_018::SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return base->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
vr::EVROverlayError CVROverlay_018::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_018::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_018::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_018::GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_018::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_018::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_018::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_018::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_018::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_018::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_018::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_018::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_018::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_018::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_018::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_018::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_018::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_018::SetOverlayNeighbor(vr::IVROverlay_018::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_018::MoveGamepadFocusToNeighbor(vr::IVROverlay_018::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_018::SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t& vCenter, float fRadius) { return base->SetOverlayDualAnalogTransform(ulOverlay, eWhich, vCenter, fRadius); }
vr::EVROverlayError CVROverlay_018::GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return base->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
vr::EVROverlayError CVROverlay_018::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_018::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_018::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_018::GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return base->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
vr::EVROverlayError CVROverlay_018::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_018::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_018::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_018::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_018::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_018::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_018::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_018::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_018::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_018::ShowKeyboard(vr::IVROverlay_018::EGamepadTextInputMode eInputMode, vr::IVROverlay_018::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_018::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::EGamepadTextInputMode eInputMode, vr::IVROverlay_018::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_018::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_018::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_018::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_018::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_018::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
vr::EVROverlayError CVROverlay_018::GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return base->GetOverlayFlags(ulOverlayHandle, pFlags); }
vr::IVROverlay_018::VRMessageOverlayResponse CVROverlay_018::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return (vr::IVROverlay_018::VRMessageOverlayResponse) base->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
void CVROverlay_018::CloseMessageOverlay() { return base->CloseMessageOverlay(); }
// FnTable for CVROverlay_018:
static CVROverlay_018 *fntable_Overlay_018_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_018_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_018_instance->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetHighQualityOverlay() { return fntable_Overlay_018_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_018_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_018_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return fntable_Overlay_018_instance->SetOverlayName(ulOverlayHandle, pchName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_018_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_018_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_018_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_018_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_018_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_018_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_018_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_018_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_018_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_018_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_018_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_018_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_018_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_018_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_018_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_018_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_018_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_018_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_018_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_018_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_018_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return fntable_Overlay_018_instance->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return fntable_Overlay_018_instance->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayTransformType* peTransformType) { return fntable_Overlay_018_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_018_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_018_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_018_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_018_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_018_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_018_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_018_instance->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_018_instance->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_018_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_018_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_018_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayInputMethod eInputMethod) { return fntable_Overlay_018_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_018_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_018_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_018::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_018::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_018_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetGamepadFocusOverlay() { return fntable_Overlay_018_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_018_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayNeighbor(vr::IVROverlay_018::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_018_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_018::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_018_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t& vCenter, float fRadius) { return fntable_Overlay_018_instance->SetOverlayDualAnalogTransform(ulOverlay, eWhich, vCenter, fRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return fntable_Overlay_018_instance->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_018_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_018_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_018_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return fntable_Overlay_018_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_018_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_018_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_018_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_IsDashboardVisible() { return fntable_Overlay_018_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_018_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_018_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_018_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_018_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_018_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ShowKeyboard(vr::IVROverlay_018::EGamepadTextInputMode eInputMode, vr::IVROverlay_018::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_018_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::EGamepadTextInputMode eInputMode, vr::IVROverlay_018::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_018_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_018_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_HideKeyboard() { return fntable_Overlay_018_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_018_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_018_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_018::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_018_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return fntable_Overlay_018_instance->GetOverlayFlags(ulOverlayHandle, pFlags); }
static vr::IVROverlay_018::VRMessageOverlayResponse OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return fntable_Overlay_018_instance->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_018_impl_CloseMessageOverlay() { return fntable_Overlay_018_instance->CloseMessageOverlay(); }
static void *fntable_Overlay_018_funcs[] = {
	fntable_Overlay_018_impl_FindOverlay,
	fntable_Overlay_018_impl_CreateOverlay,
	fntable_Overlay_018_impl_DestroyOverlay,
	fntable_Overlay_018_impl_SetHighQualityOverlay,
	fntable_Overlay_018_impl_GetHighQualityOverlay,
	fntable_Overlay_018_impl_GetOverlayKey,
	fntable_Overlay_018_impl_GetOverlayName,
	fntable_Overlay_018_impl_SetOverlayName,
	fntable_Overlay_018_impl_GetOverlayImageData,
	fntable_Overlay_018_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_018_impl_SetOverlayRenderingPid,
	fntable_Overlay_018_impl_GetOverlayRenderingPid,
	fntable_Overlay_018_impl_SetOverlayFlag,
	fntable_Overlay_018_impl_GetOverlayFlag,
	fntable_Overlay_018_impl_SetOverlayColor,
	fntable_Overlay_018_impl_GetOverlayColor,
	fntable_Overlay_018_impl_SetOverlayAlpha,
	fntable_Overlay_018_impl_GetOverlayAlpha,
	fntable_Overlay_018_impl_SetOverlayTexelAspect,
	fntable_Overlay_018_impl_GetOverlayTexelAspect,
	fntable_Overlay_018_impl_SetOverlaySortOrder,
	fntable_Overlay_018_impl_GetOverlaySortOrder,
	fntable_Overlay_018_impl_SetOverlayWidthInMeters,
	fntable_Overlay_018_impl_GetOverlayWidthInMeters,
	fntable_Overlay_018_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_018_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_018_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_018_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_018_impl_SetOverlayTextureBounds,
	fntable_Overlay_018_impl_GetOverlayTextureBounds,
	fntable_Overlay_018_impl_GetOverlayRenderModel,
	fntable_Overlay_018_impl_SetOverlayRenderModel,
	fntable_Overlay_018_impl_GetOverlayTransformType,
	fntable_Overlay_018_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_018_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_018_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_018_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_018_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_018_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_018_impl_GetOverlayTransformOverlayRelative,
	fntable_Overlay_018_impl_SetOverlayTransformOverlayRelative,
	fntable_Overlay_018_impl_ShowOverlay,
	fntable_Overlay_018_impl_HideOverlay,
	fntable_Overlay_018_impl_IsOverlayVisible,
	fntable_Overlay_018_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_018_impl_PollNextOverlayEvent,
	fntable_Overlay_018_impl_GetOverlayInputMethod,
	fntable_Overlay_018_impl_SetOverlayInputMethod,
	fntable_Overlay_018_impl_GetOverlayMouseScale,
	fntable_Overlay_018_impl_SetOverlayMouseScale,
	fntable_Overlay_018_impl_ComputeOverlayIntersection,
	fntable_Overlay_018_impl_IsHoverTargetOverlay,
	fntable_Overlay_018_impl_GetGamepadFocusOverlay,
	fntable_Overlay_018_impl_SetGamepadFocusOverlay,
	fntable_Overlay_018_impl_SetOverlayNeighbor,
	fntable_Overlay_018_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_018_impl_SetOverlayDualAnalogTransform,
	fntable_Overlay_018_impl_GetOverlayDualAnalogTransform,
	fntable_Overlay_018_impl_SetOverlayTexture,
	fntable_Overlay_018_impl_ClearOverlayTexture,
	fntable_Overlay_018_impl_SetOverlayRaw,
	fntable_Overlay_018_impl_SetOverlayFromFile,
	fntable_Overlay_018_impl_GetOverlayTexture,
	fntable_Overlay_018_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_018_impl_GetOverlayTextureSize,
	fntable_Overlay_018_impl_CreateDashboardOverlay,
	fntable_Overlay_018_impl_IsDashboardVisible,
	fntable_Overlay_018_impl_IsActiveDashboardOverlay,
	fntable_Overlay_018_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_018_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_018_impl_ShowDashboard,
	fntable_Overlay_018_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_018_impl_ShowKeyboard,
	fntable_Overlay_018_impl_ShowKeyboardForOverlay,
	fntable_Overlay_018_impl_GetKeyboardText,
	fntable_Overlay_018_impl_HideKeyboard,
	fntable_Overlay_018_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_018_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_018_impl_SetOverlayIntersectionMask,
	fntable_Overlay_018_impl_GetOverlayFlags,
	fntable_Overlay_018_impl_ShowMessageOverlay,
	fntable_Overlay_018_impl_CloseMessageOverlay,
};
void** CVROverlay_018::_GetStatFuncList() { fntable_Overlay_018_instance = this; return fntable_Overlay_018_funcs; }
// Misc for CVROverlay_019:
CVROverlay_019::CVROverlay_019() : base(GetCreateBaseOverlay()) {}
// Interface methods for CVROverlay_019:
vr::EVROverlayError CVROverlay_019::FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return base->FindOverlay(pchOverlayKey, pOverlayHandle); }
vr::EVROverlayError CVROverlay_019::CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return base->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
vr::EVROverlayError CVROverlay_019::DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->DestroyOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->SetHighQualityOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_019::GetHighQualityOverlay() { return base->GetHighQualityOverlay(); }
uint32_t CVROverlay_019::GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
uint32_t CVROverlay_019::GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return base->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
vr::EVROverlayError CVROverlay_019::SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return base->SetOverlayName(ulOverlayHandle, pchName); }
vr::EVROverlayError CVROverlay_019::GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return base->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
const char* CVROverlay_019::GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return base->GetOverlayErrorNameFromEnum(error); }
vr::EVROverlayError CVROverlay_019::SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return base->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
uint32_t CVROverlay_019::GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return base->GetOverlayRenderingPid(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayFlags eOverlayFlag, bool bEnabled) { return base->SetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, bEnabled); }
vr::EVROverlayError CVROverlay_019::GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return base->GetOverlayFlag(ulOverlayHandle, (vr::VROverlayFlags) eOverlayFlag, pbEnabled); }
vr::EVROverlayError CVROverlay_019::SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return base->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
vr::EVROverlayError CVROverlay_019::GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return base->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
vr::EVROverlayError CVROverlay_019::SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return base->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
vr::EVROverlayError CVROverlay_019::GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return base->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
vr::EVROverlayError CVROverlay_019::SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return base->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
vr::EVROverlayError CVROverlay_019::GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return base->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
vr::EVROverlayError CVROverlay_019::SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return base->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
vr::EVROverlayError CVROverlay_019::GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return base->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
vr::EVROverlayError CVROverlay_019::SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return base->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
vr::EVROverlayError CVROverlay_019::GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return base->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
vr::EVROverlayError CVROverlay_019::SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return base->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_019::GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return base->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
vr::EVROverlayError CVROverlay_019::SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return base->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
vr::EVROverlayError CVROverlay_019::GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return base->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
vr::EVROverlayError CVROverlay_019::SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
vr::EVROverlayError CVROverlay_019::GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return base->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
uint32_t CVROverlay_019::GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return base->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
vr::EVROverlayError CVROverlay_019::SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return base->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
vr::EVROverlayError CVROverlay_019::GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayTransformType* peTransformType) { return base->GetOverlayTransformType(ulOverlayHandle, (vr::VROverlayTransformType*) peTransformType); }
vr::EVROverlayError CVROverlay_019::SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return base->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return base->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return base->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
vr::EVROverlayError CVROverlay_019::GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return base->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
vr::EVROverlayError CVROverlay_019::GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return base->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
vr::EVROverlayError CVROverlay_019::ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->ShowOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->HideOverlay(ulOverlayHandle); }
bool CVROverlay_019::IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsOverlayVisible(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return base->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
bool CVROverlay_019::PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
vr::EVROverlayError CVROverlay_019::GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayInputMethod* peInputMethod) { return base->GetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod*) peInputMethod); }
vr::EVROverlayError CVROverlay_019::SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayInputMethod eInputMethod) { return base->SetOverlayInputMethod(ulOverlayHandle, (vr::VROverlayInputMethod) eInputMethod); }
vr::EVROverlayError CVROverlay_019::GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return base->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
vr::EVROverlayError CVROverlay_019::SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return base->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
bool CVROverlay_019::ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_019::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_019::VROverlayIntersectionResults_t* pResults) { return base->ComputeOverlayIntersection(ulOverlayHandle, (const vr::VROverlayIntersectionParams_t*) pParams, (vr::VROverlayIntersectionResults_t*) pResults); }
bool CVROverlay_019::IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsHoverTargetOverlay(ulOverlayHandle); }
vr::VROverlayHandle_t CVROverlay_019::GetGamepadFocusOverlay() { return base->GetGamepadFocusOverlay(); }
vr::EVROverlayError CVROverlay_019::SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return base->SetGamepadFocusOverlay(ulNewFocusOverlay); }
vr::EVROverlayError CVROverlay_019::SetOverlayNeighbor(vr::IVROverlay_019::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return base->SetOverlayNeighbor((vr::EOverlayDirection) eDirection, ulFrom, ulTo); }
vr::EVROverlayError CVROverlay_019::MoveGamepadFocusToNeighbor(vr::IVROverlay_019::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return base->MoveGamepadFocusToNeighbor((vr::EOverlayDirection) eDirection, ulFrom); }
vr::EVROverlayError CVROverlay_019::SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t* pvCenter, float fRadius) { return base->SetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, fRadius); }
vr::EVROverlayError CVROverlay_019::GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return base->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
vr::EVROverlayError CVROverlay_019::SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return base->SetOverlayTexture(ulOverlayHandle, pTexture); }
vr::EVROverlayError CVROverlay_019::ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return base->ClearOverlayTexture(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return base->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
vr::EVROverlayError CVROverlay_019::SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return base->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
vr::EVROverlayError CVROverlay_019::GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return base->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
vr::EVROverlayError CVROverlay_019::ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return base->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
vr::EVROverlayError CVROverlay_019::GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return base->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
vr::EVROverlayError CVROverlay_019::CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return base->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
bool CVROverlay_019::IsDashboardVisible() { return base->IsDashboardVisible(); }
bool CVROverlay_019::IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return base->IsActiveDashboardOverlay(ulOverlayHandle); }
vr::EVROverlayError CVROverlay_019::SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return base->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
vr::EVROverlayError CVROverlay_019::GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return base->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
void CVROverlay_019::ShowDashboard(const char* pchOverlayToShow) { return base->ShowDashboard(pchOverlayToShow); }
vr::TrackedDeviceIndex_t CVROverlay_019::GetPrimaryDashboardDevice() { return base->GetPrimaryDashboardDevice(); }
vr::EVROverlayError CVROverlay_019::ShowKeyboard(vr::IVROverlay_019::EGamepadTextInputMode eInputMode, vr::IVROverlay_019::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboard((vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
vr::EVROverlayError CVROverlay_019::ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::EGamepadTextInputMode eInputMode, vr::IVROverlay_019::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return base->ShowKeyboardForOverlay(ulOverlayHandle, (vr::EGamepadTextInputMode) eInputMode, (vr::EGamepadTextInputLineMode) eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
uint32_t CVROverlay_019::GetKeyboardText(char* pchText, uint32_t cchText) { return base->GetKeyboardText(pchText, cchText); }
void CVROverlay_019::HideKeyboard() { return base->HideKeyboard(); }
void CVROverlay_019::SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return base->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
void CVROverlay_019::SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return base->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
vr::EVROverlayError CVROverlay_019::SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return base->SetOverlayIntersectionMask(ulOverlayHandle, (vr::VROverlayIntersectionMaskPrimitive_t*) pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
vr::EVROverlayError CVROverlay_019::GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return base->GetOverlayFlags(ulOverlayHandle, pFlags); }
vr::IVROverlay_019::VRMessageOverlayResponse CVROverlay_019::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return (vr::IVROverlay_019::VRMessageOverlayResponse) base->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
void CVROverlay_019::CloseMessageOverlay() { return base->CloseMessageOverlay(); }
// FnTable for CVROverlay_019:
static CVROverlay_019 *fntable_Overlay_019_instance = NULL;
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_FindOverlay(const char* pchOverlayKey, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_019_instance->FindOverlay(pchOverlayKey, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_CreateOverlay(const char* pchOverlayKey, const char* pchOverlayName, vr::VROverlayHandle_t* pOverlayHandle) { return fntable_Overlay_019_instance->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_DestroyOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->DestroyOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetHighQualityOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->SetHighQualityOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetHighQualityOverlay() { return fntable_Overlay_019_instance->GetHighQualityOverlay(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayKey(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_019_instance->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::EVROverlayError* pError) { return fntable_Overlay_019_instance->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayName(vr::VROverlayHandle_t ulOverlayHandle, const char* pchName) { return fntable_Overlay_019_instance->SetOverlayName(ulOverlayHandle, pchName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayImageData(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unBufferSize, uint32_t* punWidth, uint32_t* punHeight) { return fntable_Overlay_019_instance->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayErrorNameFromEnum(vr::EVROverlayError error) { return fntable_Overlay_019_instance->GetOverlayErrorNameFromEnum(error); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unPID) { return fntable_Overlay_019_instance->SetOverlayRenderingPid(ulOverlayHandle, unPID); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayRenderingPid(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->GetOverlayRenderingPid(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayFlags eOverlayFlag, bool bEnabled) { return fntable_Overlay_019_instance->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayFlag(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayFlags eOverlayFlag, bool* pbEnabled) { return fntable_Overlay_019_instance->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) { return fntable_Overlay_019_instance->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayColor(vr::VROverlayHandle_t ulOverlayHandle, float* pfRed, float* pfGreen, float* pfBlue) { return fntable_Overlay_019_instance->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float fAlpha) { return fntable_Overlay_019_instance->SetOverlayAlpha(ulOverlayHandle, fAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayAlpha(vr::VROverlayHandle_t ulOverlayHandle, float* pfAlpha) { return fntable_Overlay_019_instance->GetOverlayAlpha(ulOverlayHandle, pfAlpha); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float fTexelAspect) { return fntable_Overlay_019_instance->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTexelAspect(vr::VROverlayHandle_t ulOverlayHandle, float* pfTexelAspect) { return fntable_Overlay_019_instance->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) { return fntable_Overlay_019_instance->SetOverlaySortOrder(ulOverlayHandle, unSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlaySortOrder(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punSortOrder) { return fntable_Overlay_019_instance->GetOverlaySortOrder(ulOverlayHandle, punSortOrder); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) { return fntable_Overlay_019_instance->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayWidthInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfWidthInMeters) { return fntable_Overlay_019_instance->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) { return fntable_Overlay_019_instance->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayAutoCurveDistanceRangeInMeters(vr::VROverlayHandle_t ulOverlayHandle, float* pfMinDistanceInMeters, float* pfMaxDistanceInMeters) { return fntable_Overlay_019_instance->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace eTextureColorSpace) { return fntable_Overlay_019_instance->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTextureColorSpace(vr::VROverlayHandle_t ulOverlayHandle, vr::EColorSpace* peTextureColorSpace) { return fntable_Overlay_019_instance->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, const vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_019_instance->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTextureBounds(vr::VROverlayHandle_t ulOverlayHandle, vr::VRTextureBounds_t* pOverlayTextureBounds) { return fntable_Overlay_019_instance->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, char* pchValue, uint32_t unBufferSize, vr::HmdColor_t* pColor, vr::EVROverlayError* pError) { return fntable_Overlay_019_instance->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayRenderModel(vr::VROverlayHandle_t ulOverlayHandle, const char* pchRenderModel, const vr::HmdColor_t* pColor) { return fntable_Overlay_019_instance->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTransformType(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayTransformType* peTransformType) { return fntable_Overlay_019_instance->GetOverlayTransformType(ulOverlayHandle, peTransformType); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_019_instance->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTransformAbsolute(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin* peTrackingOrigin, vr::HmdMatrix34_t* pmatTrackingOriginToOverlayTransform) { return fntable_Overlay_019_instance->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unTrackedDevice, const vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_019_instance->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTransformTrackedDeviceRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punTrackedDevice, vr::HmdMatrix34_t* pmatTrackedDeviceToOverlayTransform) { return fntable_Overlay_019_instance->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchComponentName) { return fntable_Overlay_019_instance->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTransformTrackedDeviceComponent(vr::VROverlayHandle_t ulOverlayHandle, vr::TrackedDeviceIndex_t* punDeviceIndex, char* pchComponentName, uint32_t unComponentNameSize) { return fntable_Overlay_019_instance->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t* ulOverlayHandleParent, vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_019_instance->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTransformOverlayRelative(vr::VROverlayHandle_t ulOverlayHandle, vr::VROverlayHandle_t ulOverlayHandleParent, const vr::HmdMatrix34_t* pmatParentOverlayToOverlayTransform) { return fntable_Overlay_019_instance->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ShowOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->ShowOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_HideOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->HideOverlay(ulOverlayHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_IsOverlayVisible(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->IsOverlayVisible(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetTransformForOverlayCoordinates(vr::VROverlayHandle_t ulOverlayHandle, vr::ETrackingUniverseOrigin eTrackingOrigin, vr::HmdVector2_t coordinatesInOverlay, vr::HmdMatrix34_t* pmatTransform) { return fntable_Overlay_019_instance->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_PollNextOverlayEvent(vr::VROverlayHandle_t ulOverlayHandle, vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_Overlay_019_instance->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayInputMethod* peInputMethod) { return fntable_Overlay_019_instance->GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayInputMethod(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayInputMethod eInputMethod) { return fntable_Overlay_019_instance->SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_019_instance->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayMouseScale(vr::VROverlayHandle_t ulOverlayHandle, const vr::HmdVector2_t* pvecMouseScale) { return fntable_Overlay_019_instance->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ComputeOverlayIntersection(vr::VROverlayHandle_t ulOverlayHandle, const vr::IVROverlay_019::VROverlayIntersectionParams_t* pParams, vr::IVROverlay_019::VROverlayIntersectionResults_t* pResults) { return fntable_Overlay_019_instance->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_IsHoverTargetOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->IsHoverTargetOverlay(ulOverlayHandle); }
static vr::VROverlayHandle_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetGamepadFocusOverlay() { return fntable_Overlay_019_instance->GetGamepadFocusOverlay(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetGamepadFocusOverlay(vr::VROverlayHandle_t ulNewFocusOverlay) { return fntable_Overlay_019_instance->SetGamepadFocusOverlay(ulNewFocusOverlay); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayNeighbor(vr::IVROverlay_019::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom, vr::VROverlayHandle_t ulTo) { return fntable_Overlay_019_instance->SetOverlayNeighbor(eDirection, ulFrom, ulTo); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_MoveGamepadFocusToNeighbor(vr::IVROverlay_019::EOverlayDirection eDirection, vr::VROverlayHandle_t ulFrom) { return fntable_Overlay_019_instance->MoveGamepadFocusToNeighbor(eDirection, ulFrom); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, const vr::HmdVector2_t* pvCenter, float fRadius) { return fntable_Overlay_019_instance->SetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, fRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayDualAnalogTransform(vr::VROverlayHandle_t ulOverlay, vr::EDualAnalogWhich eWhich, vr::HmdVector2_t* pvCenter, float* pfRadius) { return fntable_Overlay_019_instance->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, const vr::Texture_t* pTexture) { return fntable_Overlay_019_instance->SetOverlayTexture(ulOverlayHandle, pTexture); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ClearOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->ClearOverlayTexture(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayRaw(vr::VROverlayHandle_t ulOverlayHandle, void* pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) { return fntable_Overlay_019_instance->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayFromFile(vr::VROverlayHandle_t ulOverlayHandle, const char* pchFilePath) { return fntable_Overlay_019_instance->SetOverlayFromFile(ulOverlayHandle, pchFilePath); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTexture(vr::VROverlayHandle_t ulOverlayHandle, void** pNativeTextureHandle, void* pNativeTextureRef, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pNativeFormat, vr::ETextureType* pAPIType, vr::EColorSpace* pColorSpace, vr::VRTextureBounds_t* pTextureBounds) { return fntable_Overlay_019_instance->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ReleaseNativeOverlayHandle(vr::VROverlayHandle_t ulOverlayHandle, void* pNativeTextureHandle) { return fntable_Overlay_019_instance->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayTextureSize(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pWidth, uint32_t* pHeight) { return fntable_Overlay_019_instance->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_CreateDashboardOverlay(const char* pchOverlayKey, const char* pchOverlayFriendlyName, vr::VROverlayHandle_t* pMainHandle, vr::VROverlayHandle_t* pThumbnailHandle) { return fntable_Overlay_019_instance->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_IsDashboardVisible() { return fntable_Overlay_019_instance->IsDashboardVisible(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_IsActiveDashboardOverlay(vr::VROverlayHandle_t ulOverlayHandle) { return fntable_Overlay_019_instance->IsActiveDashboardOverlay(ulOverlayHandle); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) { return fntable_Overlay_019_instance->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetDashboardOverlaySceneProcess(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* punProcessId) { return fntable_Overlay_019_instance->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ShowDashboard(const char* pchOverlayToShow) { return fntable_Overlay_019_instance->ShowDashboard(pchOverlayToShow); }
static vr::TrackedDeviceIndex_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetPrimaryDashboardDevice() { return fntable_Overlay_019_instance->GetPrimaryDashboardDevice(); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ShowKeyboard(vr::IVROverlay_019::EGamepadTextInputMode eInputMode, vr::IVROverlay_019::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_019_instance->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ShowKeyboardForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::EGamepadTextInputMode eInputMode, vr::IVROverlay_019::EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32_t unCharMax, const char* pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) { return fntable_Overlay_019_instance->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetKeyboardText(char* pchText, uint32_t cchText) { return fntable_Overlay_019_instance->GetKeyboardText(pchText, cchText); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_HideKeyboard() { return fntable_Overlay_019_instance->HideKeyboard(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetKeyboardTransformAbsolute(vr::ETrackingUniverseOrigin eTrackingOrigin, const vr::HmdMatrix34_t* pmatTrackingOriginToKeyboardTransform) { return fntable_Overlay_019_instance->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetKeyboardPositionForOverlay(vr::VROverlayHandle_t ulOverlayHandle, vr::HmdRect2_t avoidRect) { return fntable_Overlay_019_instance->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_SetOverlayIntersectionMask(vr::VROverlayHandle_t ulOverlayHandle, vr::IVROverlay_019::VROverlayIntersectionMaskPrimitive_t* pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) { return fntable_Overlay_019_instance->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize); }
static vr::EVROverlayError OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_GetOverlayFlags(vr::VROverlayHandle_t ulOverlayHandle, uint32_t* pFlags) { return fntable_Overlay_019_instance->GetOverlayFlags(ulOverlayHandle, pFlags); }
static vr::IVROverlay_019::VRMessageOverlayResponse OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) { return fntable_Overlay_019_instance->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Overlay_019_impl_CloseMessageOverlay() { return fntable_Overlay_019_instance->CloseMessageOverlay(); }
static void *fntable_Overlay_019_funcs[] = {
	fntable_Overlay_019_impl_FindOverlay,
	fntable_Overlay_019_impl_CreateOverlay,
	fntable_Overlay_019_impl_DestroyOverlay,
	fntable_Overlay_019_impl_SetHighQualityOverlay,
	fntable_Overlay_019_impl_GetHighQualityOverlay,
	fntable_Overlay_019_impl_GetOverlayKey,
	fntable_Overlay_019_impl_GetOverlayName,
	fntable_Overlay_019_impl_SetOverlayName,
	fntable_Overlay_019_impl_GetOverlayImageData,
	fntable_Overlay_019_impl_GetOverlayErrorNameFromEnum,
	fntable_Overlay_019_impl_SetOverlayRenderingPid,
	fntable_Overlay_019_impl_GetOverlayRenderingPid,
	fntable_Overlay_019_impl_SetOverlayFlag,
	fntable_Overlay_019_impl_GetOverlayFlag,
	fntable_Overlay_019_impl_SetOverlayColor,
	fntable_Overlay_019_impl_GetOverlayColor,
	fntable_Overlay_019_impl_SetOverlayAlpha,
	fntable_Overlay_019_impl_GetOverlayAlpha,
	fntable_Overlay_019_impl_SetOverlayTexelAspect,
	fntable_Overlay_019_impl_GetOverlayTexelAspect,
	fntable_Overlay_019_impl_SetOverlaySortOrder,
	fntable_Overlay_019_impl_GetOverlaySortOrder,
	fntable_Overlay_019_impl_SetOverlayWidthInMeters,
	fntable_Overlay_019_impl_GetOverlayWidthInMeters,
	fntable_Overlay_019_impl_SetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_019_impl_GetOverlayAutoCurveDistanceRangeInMeters,
	fntable_Overlay_019_impl_SetOverlayTextureColorSpace,
	fntable_Overlay_019_impl_GetOverlayTextureColorSpace,
	fntable_Overlay_019_impl_SetOverlayTextureBounds,
	fntable_Overlay_019_impl_GetOverlayTextureBounds,
	fntable_Overlay_019_impl_GetOverlayRenderModel,
	fntable_Overlay_019_impl_SetOverlayRenderModel,
	fntable_Overlay_019_impl_GetOverlayTransformType,
	fntable_Overlay_019_impl_SetOverlayTransformAbsolute,
	fntable_Overlay_019_impl_GetOverlayTransformAbsolute,
	fntable_Overlay_019_impl_SetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_019_impl_GetOverlayTransformTrackedDeviceRelative,
	fntable_Overlay_019_impl_SetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_019_impl_GetOverlayTransformTrackedDeviceComponent,
	fntable_Overlay_019_impl_GetOverlayTransformOverlayRelative,
	fntable_Overlay_019_impl_SetOverlayTransformOverlayRelative,
	fntable_Overlay_019_impl_ShowOverlay,
	fntable_Overlay_019_impl_HideOverlay,
	fntable_Overlay_019_impl_IsOverlayVisible,
	fntable_Overlay_019_impl_GetTransformForOverlayCoordinates,
	fntable_Overlay_019_impl_PollNextOverlayEvent,
	fntable_Overlay_019_impl_GetOverlayInputMethod,
	fntable_Overlay_019_impl_SetOverlayInputMethod,
	fntable_Overlay_019_impl_GetOverlayMouseScale,
	fntable_Overlay_019_impl_SetOverlayMouseScale,
	fntable_Overlay_019_impl_ComputeOverlayIntersection,
	fntable_Overlay_019_impl_IsHoverTargetOverlay,
	fntable_Overlay_019_impl_GetGamepadFocusOverlay,
	fntable_Overlay_019_impl_SetGamepadFocusOverlay,
	fntable_Overlay_019_impl_SetOverlayNeighbor,
	fntable_Overlay_019_impl_MoveGamepadFocusToNeighbor,
	fntable_Overlay_019_impl_SetOverlayDualAnalogTransform,
	fntable_Overlay_019_impl_GetOverlayDualAnalogTransform,
	fntable_Overlay_019_impl_SetOverlayTexture,
	fntable_Overlay_019_impl_ClearOverlayTexture,
	fntable_Overlay_019_impl_SetOverlayRaw,
	fntable_Overlay_019_impl_SetOverlayFromFile,
	fntable_Overlay_019_impl_GetOverlayTexture,
	fntable_Overlay_019_impl_ReleaseNativeOverlayHandle,
	fntable_Overlay_019_impl_GetOverlayTextureSize,
	fntable_Overlay_019_impl_CreateDashboardOverlay,
	fntable_Overlay_019_impl_IsDashboardVisible,
	fntable_Overlay_019_impl_IsActiveDashboardOverlay,
	fntable_Overlay_019_impl_SetDashboardOverlaySceneProcess,
	fntable_Overlay_019_impl_GetDashboardOverlaySceneProcess,
	fntable_Overlay_019_impl_ShowDashboard,
	fntable_Overlay_019_impl_GetPrimaryDashboardDevice,
	fntable_Overlay_019_impl_ShowKeyboard,
	fntable_Overlay_019_impl_ShowKeyboardForOverlay,
	fntable_Overlay_019_impl_GetKeyboardText,
	fntable_Overlay_019_impl_HideKeyboard,
	fntable_Overlay_019_impl_SetKeyboardTransformAbsolute,
	fntable_Overlay_019_impl_SetKeyboardPositionForOverlay,
	fntable_Overlay_019_impl_SetOverlayIntersectionMask,
	fntable_Overlay_019_impl_GetOverlayFlags,
	fntable_Overlay_019_impl_ShowMessageOverlay,
	fntable_Overlay_019_impl_CloseMessageOverlay,
};
void** CVROverlay_019::_GetStatFuncList() { fntable_Overlay_019_instance = this; return fntable_Overlay_019_funcs; }
#include "GVRChaperoneSetup.gen.h"
// Single inst of BaseChaperoneSetup
static std::weak_ptr<BaseChaperoneSetup> _single_inst_ChaperoneSetup;
static BaseChaperoneSetup *_single_inst_ChaperoneSetup_unsafe = NULL;
std::shared_ptr<BaseChaperoneSetup> GetBaseChaperoneSetup() { return _single_inst_ChaperoneSetup.lock(); };
BaseChaperoneSetup* GetUnsafeBaseChaperoneSetup() { return _single_inst_ChaperoneSetup_unsafe; };
std::shared_ptr<BaseChaperoneSetup> GetCreateBaseChaperoneSetup() {
	std::shared_ptr<BaseChaperoneSetup> ret = _single_inst_ChaperoneSetup.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseChaperoneSetup>(new BaseChaperoneSetup(), [](BaseChaperoneSetup *obj){ _single_inst_ChaperoneSetup_unsafe = NULL; delete obj; });
		_single_inst_ChaperoneSetup = ret;
		_single_inst_ChaperoneSetup_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRChaperoneSetup_005:
CVRChaperoneSetup_005::CVRChaperoneSetup_005() : base(GetCreateBaseChaperoneSetup()) {}
// Interface methods for CVRChaperoneSetup_005:
bool CVRChaperoneSetup_005::CommitWorkingCopy(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) { return base->CommitWorkingCopy((vr::EChaperoneConfigFile) configFile); }
void CVRChaperoneSetup_005::RevertWorkingCopy() { return base->RevertWorkingCopy(); }
bool CVRChaperoneSetup_005::GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) { return base->GetWorkingPlayAreaSize(pSizeX, pSizeZ); }
bool CVRChaperoneSetup_005::GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) { return base->GetWorkingPlayAreaRect(rect); }
bool CVRChaperoneSetup_005::GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return base->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
bool CVRChaperoneSetup_005::GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return base->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
bool CVRChaperoneSetup_005::GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return base->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
bool CVRChaperoneSetup_005::GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) { return base->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_005::SetWorkingPlayAreaSize(float sizeX, float sizeZ) { return base->SetWorkingPlayAreaSize(sizeX, sizeZ); }
void CVRChaperoneSetup_005::SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return base->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount); }
void CVRChaperoneSetup_005::SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) { return base->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_005::SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) { return base->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_005::ReloadFromDisk(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) { return base->ReloadFromDisk((vr::EChaperoneConfigFile) configFile); }
bool CVRChaperoneSetup_005::GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return base->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_005::SetWorkingCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t unTagCount) { return base->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount); }
bool CVRChaperoneSetup_005::GetLiveCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t* punTagCount) { return base->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount); }
bool CVRChaperoneSetup_005::SetWorkingPhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return base->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount); }
bool CVRChaperoneSetup_005::GetLivePhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return base->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount); }
bool CVRChaperoneSetup_005::ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) { return base->ExportLiveToBuffer(pBuffer, pnBufferLength); }
bool CVRChaperoneSetup_005::ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) { return base->ImportFromBufferToWorking(pBuffer, nImportFlags); }
// FnTable for CVRChaperoneSetup_005:
static CVRChaperoneSetup_005 *fntable_ChaperoneSetup_005_instance = NULL;
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_CommitWorkingCopy(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) { return fntable_ChaperoneSetup_005_instance->CommitWorkingCopy(configFile); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_RevertWorkingCopy() { return fntable_ChaperoneSetup_005_instance->RevertWorkingCopy(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) { return fntable_ChaperoneSetup_005_instance->GetWorkingPlayAreaSize(pSizeX, pSizeZ); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) { return fntable_ChaperoneSetup_005_instance->GetWorkingPlayAreaRect(rect); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return fntable_ChaperoneSetup_005_instance->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return fntable_ChaperoneSetup_005_instance->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_005_instance->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_005_instance->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingPlayAreaSize(float sizeX, float sizeZ) { return fntable_ChaperoneSetup_005_instance->SetWorkingPlayAreaSize(sizeX, sizeZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return fntable_ChaperoneSetup_005_instance->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_005_instance->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_005_instance->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_ReloadFromDisk(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile) { return fntable_ChaperoneSetup_005_instance->ReloadFromDisk(configFile); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_005_instance->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t unTagCount) { return fntable_ChaperoneSetup_005_instance->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetLiveCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t* punTagCount) { return fntable_ChaperoneSetup_005_instance->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_SetWorkingPhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return fntable_ChaperoneSetup_005_instance->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_GetLivePhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return fntable_ChaperoneSetup_005_instance->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) { return fntable_ChaperoneSetup_005_instance->ExportLiveToBuffer(pBuffer, pnBufferLength); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_005_impl_ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) { return fntable_ChaperoneSetup_005_instance->ImportFromBufferToWorking(pBuffer, nImportFlags); }
static void *fntable_ChaperoneSetup_005_funcs[] = {
	fntable_ChaperoneSetup_005_impl_CommitWorkingCopy,
	fntable_ChaperoneSetup_005_impl_RevertWorkingCopy,
	fntable_ChaperoneSetup_005_impl_GetWorkingPlayAreaSize,
	fntable_ChaperoneSetup_005_impl_GetWorkingPlayAreaRect,
	fntable_ChaperoneSetup_005_impl_GetWorkingCollisionBoundsInfo,
	fntable_ChaperoneSetup_005_impl_GetLiveCollisionBoundsInfo,
	fntable_ChaperoneSetup_005_impl_GetWorkingSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_005_impl_GetWorkingStandingZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_005_impl_SetWorkingPlayAreaSize,
	fntable_ChaperoneSetup_005_impl_SetWorkingCollisionBoundsInfo,
	fntable_ChaperoneSetup_005_impl_SetWorkingSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_005_impl_SetWorkingStandingZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_005_impl_ReloadFromDisk,
	fntable_ChaperoneSetup_005_impl_GetLiveSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_005_impl_SetWorkingCollisionBoundsTagsInfo,
	fntable_ChaperoneSetup_005_impl_GetLiveCollisionBoundsTagsInfo,
	fntable_ChaperoneSetup_005_impl_SetWorkingPhysicalBoundsInfo,
	fntable_ChaperoneSetup_005_impl_GetLivePhysicalBoundsInfo,
	fntable_ChaperoneSetup_005_impl_ExportLiveToBuffer,
	fntable_ChaperoneSetup_005_impl_ImportFromBufferToWorking,
};
void** CVRChaperoneSetup_005::_GetStatFuncList() { fntable_ChaperoneSetup_005_instance = this; return fntable_ChaperoneSetup_005_funcs; }
// Misc for CVRChaperoneSetup_006:
CVRChaperoneSetup_006::CVRChaperoneSetup_006() : base(GetCreateBaseChaperoneSetup()) {}
// Interface methods for CVRChaperoneSetup_006:
bool CVRChaperoneSetup_006::CommitWorkingCopy(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) { return base->CommitWorkingCopy((vr::EChaperoneConfigFile) configFile); }
void CVRChaperoneSetup_006::RevertWorkingCopy() { return base->RevertWorkingCopy(); }
bool CVRChaperoneSetup_006::GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) { return base->GetWorkingPlayAreaSize(pSizeX, pSizeZ); }
bool CVRChaperoneSetup_006::GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) { return base->GetWorkingPlayAreaRect(rect); }
bool CVRChaperoneSetup_006::GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return base->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
bool CVRChaperoneSetup_006::GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return base->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
bool CVRChaperoneSetup_006::GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return base->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
bool CVRChaperoneSetup_006::GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) { return base->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_006::SetWorkingPlayAreaSize(float sizeX, float sizeZ) { return base->SetWorkingPlayAreaSize(sizeX, sizeZ); }
void CVRChaperoneSetup_006::SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return base->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount); }
void CVRChaperoneSetup_006::SetWorkingPerimeter(vr::HmdVector2_t* pPointBuffer, uint32_t unPointCount) { return base->SetWorkingPerimeter(pPointBuffer, unPointCount); }
void CVRChaperoneSetup_006::SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) { return base->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_006::SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) { return base->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose); }
void CVRChaperoneSetup_006::ReloadFromDisk(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) { return base->ReloadFromDisk((vr::EChaperoneConfigFile) configFile); }
bool CVRChaperoneSetup_006::GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return base->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
bool CVRChaperoneSetup_006::ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) { return base->ExportLiveToBuffer(pBuffer, pnBufferLength); }
bool CVRChaperoneSetup_006::ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) { return base->ImportFromBufferToWorking(pBuffer, nImportFlags); }
void CVRChaperoneSetup_006::ShowWorkingSetPreview() { return base->ShowWorkingSetPreview(); }
void CVRChaperoneSetup_006::HideWorkingSetPreview() { return base->HideWorkingSetPreview(); }
void CVRChaperoneSetup_006::RoomSetupStarting() { return base->RoomSetupStarting(); }
// FnTable for CVRChaperoneSetup_006:
static CVRChaperoneSetup_006 *fntable_ChaperoneSetup_006_instance = NULL;
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_CommitWorkingCopy(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) { return fntable_ChaperoneSetup_006_instance->CommitWorkingCopy(configFile); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_RevertWorkingCopy() { return fntable_ChaperoneSetup_006_instance->RevertWorkingCopy(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ) { return fntable_ChaperoneSetup_006_instance->GetWorkingPlayAreaSize(pSizeX, pSizeZ); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetWorkingPlayAreaRect(vr::HmdQuad_t* rect) { return fntable_ChaperoneSetup_006_instance->GetWorkingPlayAreaRect(rect); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return fntable_ChaperoneSetup_006_instance->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount) { return fntable_ChaperoneSetup_006_instance->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_006_instance->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_006_instance->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_SetWorkingPlayAreaSize(float sizeX, float sizeZ) { return fntable_ChaperoneSetup_006_instance->SetWorkingPlayAreaSize(sizeX, sizeZ); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount) { return fntable_ChaperoneSetup_006_instance->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_SetWorkingPerimeter(vr::HmdVector2_t* pPointBuffer, uint32_t unPointCount) { return fntable_ChaperoneSetup_006_instance->SetWorkingPerimeter(pPointBuffer, unPointCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_006_instance->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_006_instance->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_ReloadFromDisk(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile) { return fntable_ChaperoneSetup_006_instance->ReloadFromDisk(configFile); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose) { return fntable_ChaperoneSetup_006_instance->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength) { return fntable_ChaperoneSetup_006_instance->ExportLiveToBuffer(pBuffer, pnBufferLength); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags) { return fntable_ChaperoneSetup_006_instance->ImportFromBufferToWorking(pBuffer, nImportFlags); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_ShowWorkingSetPreview() { return fntable_ChaperoneSetup_006_instance->ShowWorkingSetPreview(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_HideWorkingSetPreview() { return fntable_ChaperoneSetup_006_instance->HideWorkingSetPreview(); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ChaperoneSetup_006_impl_RoomSetupStarting() { return fntable_ChaperoneSetup_006_instance->RoomSetupStarting(); }
static void *fntable_ChaperoneSetup_006_funcs[] = {
	fntable_ChaperoneSetup_006_impl_CommitWorkingCopy,
	fntable_ChaperoneSetup_006_impl_RevertWorkingCopy,
	fntable_ChaperoneSetup_006_impl_GetWorkingPlayAreaSize,
	fntable_ChaperoneSetup_006_impl_GetWorkingPlayAreaRect,
	fntable_ChaperoneSetup_006_impl_GetWorkingCollisionBoundsInfo,
	fntable_ChaperoneSetup_006_impl_GetLiveCollisionBoundsInfo,
	fntable_ChaperoneSetup_006_impl_GetWorkingSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_006_impl_GetWorkingStandingZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_006_impl_SetWorkingPlayAreaSize,
	fntable_ChaperoneSetup_006_impl_SetWorkingCollisionBoundsInfo,
	fntable_ChaperoneSetup_006_impl_SetWorkingPerimeter,
	fntable_ChaperoneSetup_006_impl_SetWorkingSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_006_impl_SetWorkingStandingZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_006_impl_ReloadFromDisk,
	fntable_ChaperoneSetup_006_impl_GetLiveSeatedZeroPoseToRawTrackingPose,
	fntable_ChaperoneSetup_006_impl_ExportLiveToBuffer,
	fntable_ChaperoneSetup_006_impl_ImportFromBufferToWorking,
	fntable_ChaperoneSetup_006_impl_ShowWorkingSetPreview,
	fntable_ChaperoneSetup_006_impl_HideWorkingSetPreview,
	fntable_ChaperoneSetup_006_impl_RoomSetupStarting,
};
void** CVRChaperoneSetup_006::_GetStatFuncList() { fntable_ChaperoneSetup_006_instance = this; return fntable_ChaperoneSetup_006_funcs; }
#include "GVRRenderModels.gen.h"
// Single inst of BaseRenderModels
static std::weak_ptr<BaseRenderModels> _single_inst_RenderModels;
static BaseRenderModels *_single_inst_RenderModels_unsafe = NULL;
std::shared_ptr<BaseRenderModels> GetBaseRenderModels() { return _single_inst_RenderModels.lock(); };
BaseRenderModels* GetUnsafeBaseRenderModels() { return _single_inst_RenderModels_unsafe; };
std::shared_ptr<BaseRenderModels> GetCreateBaseRenderModels() {
	std::shared_ptr<BaseRenderModels> ret = _single_inst_RenderModels.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseRenderModels>(new BaseRenderModels(), [](BaseRenderModels *obj){ _single_inst_RenderModels_unsafe = NULL; delete obj; });
		_single_inst_RenderModels = ret;
		_single_inst_RenderModels_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRRenderModels_004:
CVRRenderModels_004::CVRRenderModels_004() : base(GetCreateBaseRenderModels()) {}
// Interface methods for CVRRenderModels_004:
vr::IVRRenderModels_004::EVRRenderModelError CVRRenderModels_004::LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_004::RenderModel_t** ppRenderModel) { return (vr::IVRRenderModels_004::EVRRenderModelError) base->LoadRenderModel_Async(pchRenderModelName, (vr::RenderModel_t**) ppRenderModel); }
void CVRRenderModels_004::FreeRenderModel(vr::IVRRenderModels_004::RenderModel_t* pRenderModel) { return base->FreeRenderModel((vr::RenderModel_t*) pRenderModel); }
vr::IVRRenderModels_004::EVRRenderModelError CVRRenderModels_004::LoadTexture_Async(vr::IVRRenderModels_004::TextureID_t textureId, vr::IVRRenderModels_004::RenderModel_TextureMap_t** ppTexture) { return (vr::IVRRenderModels_004::EVRRenderModelError) base->LoadTexture_Async((vr::TextureID_t) textureId, (vr::RenderModel_TextureMap_t**) ppTexture); }
void CVRRenderModels_004::FreeTexture(vr::IVRRenderModels_004::RenderModel_TextureMap_t* pTexture) { return base->FreeTexture((vr::RenderModel_TextureMap_t*) pTexture); }
vr::IVRRenderModels_004::EVRRenderModelError CVRRenderModels_004::LoadTextureD3D11_Async(vr::IVRRenderModels_004::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return (vr::IVRRenderModels_004::EVRRenderModelError) base->LoadTextureD3D11_Async((vr::TextureID_t) textureId, pD3D11Device, ppD3D11Texture2D); }
void CVRRenderModels_004::FreeTextureD3D11(void* pD3D11Texture2D) { return base->FreeTextureD3D11(pD3D11Texture2D); }
uint32_t CVRRenderModels_004::GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return base->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
uint32_t CVRRenderModels_004::GetRenderModelCount() { return base->GetRenderModelCount(); }
uint32_t CVRRenderModels_004::GetComponentCount(const char* pchRenderModelName) { return base->GetComponentCount(pchRenderModelName); }
uint32_t CVRRenderModels_004::GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return base->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
uint64_t CVRRenderModels_004::GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return base->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
uint32_t CVRRenderModels_004::GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return base->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
bool CVRRenderModels_004::GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_004::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_004::RenderModel_ComponentState_t* pComponentState) { return base->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, (const vr::RenderModel_ControllerMode_State_t*) pState, (vr::RenderModel_ComponentState_t*) pComponentState); }
bool CVRRenderModels_004::RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return base->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
// FnTable for CVRRenderModels_004:
static CVRRenderModels_004 *fntable_RenderModels_004_instance = NULL;
static vr::IVRRenderModels_004::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_004::RenderModel_t** ppRenderModel) { return fntable_RenderModels_004_instance->LoadRenderModel_Async(pchRenderModelName, ppRenderModel); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_FreeRenderModel(vr::IVRRenderModels_004::RenderModel_t* pRenderModel) { return fntable_RenderModels_004_instance->FreeRenderModel(pRenderModel); }
static vr::IVRRenderModels_004::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_LoadTexture_Async(vr::IVRRenderModels_004::TextureID_t textureId, vr::IVRRenderModels_004::RenderModel_TextureMap_t** ppTexture) { return fntable_RenderModels_004_instance->LoadTexture_Async(textureId, ppTexture); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_FreeTexture(vr::IVRRenderModels_004::RenderModel_TextureMap_t* pTexture) { return fntable_RenderModels_004_instance->FreeTexture(pTexture); }
static vr::IVRRenderModels_004::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_LoadTextureD3D11_Async(vr::IVRRenderModels_004::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return fntable_RenderModels_004_instance->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_FreeTextureD3D11(void* pD3D11Texture2D) { return fntable_RenderModels_004_instance->FreeTextureD3D11(pD3D11Texture2D); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return fntable_RenderModels_004_instance->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetRenderModelCount() { return fntable_RenderModels_004_instance->GetRenderModelCount(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetComponentCount(const char* pchRenderModelName) { return fntable_RenderModels_004_instance->GetComponentCount(pchRenderModelName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return fntable_RenderModels_004_instance->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_004_instance->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return fntable_RenderModels_004_instance->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_004::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_004::RenderModel_ComponentState_t* pComponentState) { return fntable_RenderModels_004_instance->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_004_impl_RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_004_instance->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
static void *fntable_RenderModels_004_funcs[] = {
	fntable_RenderModels_004_impl_LoadRenderModel_Async,
	fntable_RenderModels_004_impl_FreeRenderModel,
	fntable_RenderModels_004_impl_LoadTexture_Async,
	fntable_RenderModels_004_impl_FreeTexture,
	fntable_RenderModels_004_impl_LoadTextureD3D11_Async,
	fntable_RenderModels_004_impl_FreeTextureD3D11,
	fntable_RenderModels_004_impl_GetRenderModelName,
	fntable_RenderModels_004_impl_GetRenderModelCount,
	fntable_RenderModels_004_impl_GetComponentCount,
	fntable_RenderModels_004_impl_GetComponentName,
	fntable_RenderModels_004_impl_GetComponentButtonMask,
	fntable_RenderModels_004_impl_GetComponentRenderModelName,
	fntable_RenderModels_004_impl_GetComponentState,
	fntable_RenderModels_004_impl_RenderModelHasComponent,
};
void** CVRRenderModels_004::_GetStatFuncList() { fntable_RenderModels_004_instance = this; return fntable_RenderModels_004_funcs; }
// Misc for CVRRenderModels_005:
CVRRenderModels_005::CVRRenderModels_005() : base(GetCreateBaseRenderModels()) {}
// Interface methods for CVRRenderModels_005:
vr::IVRRenderModels_005::EVRRenderModelError CVRRenderModels_005::LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_005::RenderModel_t** ppRenderModel) { return (vr::IVRRenderModels_005::EVRRenderModelError) base->LoadRenderModel_Async(pchRenderModelName, (vr::RenderModel_t**) ppRenderModel); }
void CVRRenderModels_005::FreeRenderModel(vr::IVRRenderModels_005::RenderModel_t* pRenderModel) { return base->FreeRenderModel((vr::RenderModel_t*) pRenderModel); }
vr::IVRRenderModels_005::EVRRenderModelError CVRRenderModels_005::LoadTexture_Async(vr::IVRRenderModels_005::TextureID_t textureId, vr::IVRRenderModels_005::RenderModel_TextureMap_t** ppTexture) { return (vr::IVRRenderModels_005::EVRRenderModelError) base->LoadTexture_Async((vr::TextureID_t) textureId, (vr::RenderModel_TextureMap_t**) ppTexture); }
void CVRRenderModels_005::FreeTexture(vr::IVRRenderModels_005::RenderModel_TextureMap_t* pTexture) { return base->FreeTexture((vr::RenderModel_TextureMap_t*) pTexture); }
vr::IVRRenderModels_005::EVRRenderModelError CVRRenderModels_005::LoadTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return (vr::IVRRenderModels_005::EVRRenderModelError) base->LoadTextureD3D11_Async((vr::TextureID_t) textureId, pD3D11Device, ppD3D11Texture2D); }
vr::IVRRenderModels_005::EVRRenderModelError CVRRenderModels_005::LoadIntoTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pDstTexture) { return (vr::IVRRenderModels_005::EVRRenderModelError) base->LoadIntoTextureD3D11_Async((vr::TextureID_t) textureId, pDstTexture); }
void CVRRenderModels_005::FreeTextureD3D11(void* pD3D11Texture2D) { return base->FreeTextureD3D11(pD3D11Texture2D); }
uint32_t CVRRenderModels_005::GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return base->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
uint32_t CVRRenderModels_005::GetRenderModelCount() { return base->GetRenderModelCount(); }
uint32_t CVRRenderModels_005::GetComponentCount(const char* pchRenderModelName) { return base->GetComponentCount(pchRenderModelName); }
uint32_t CVRRenderModels_005::GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return base->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
uint64_t CVRRenderModels_005::GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return base->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
uint32_t CVRRenderModels_005::GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return base->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
bool CVRRenderModels_005::GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_005::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_005::RenderModel_ComponentState_t* pComponentState) { return base->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, (const vr::RenderModel_ControllerMode_State_t*) pState, (vr::RenderModel_ComponentState_t*) pComponentState); }
bool CVRRenderModels_005::RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return base->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
uint32_t CVRRenderModels_005::GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) { return base->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, (vr::EVRRenderModelError*) peError); }
uint32_t CVRRenderModels_005::GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) { return base->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, (vr::EVRRenderModelError*) peError); }
const char* CVRRenderModels_005::GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_005::EVRRenderModelError error) { return base->GetRenderModelErrorNameFromEnum((vr::EVRRenderModelError) error); }
// FnTable for CVRRenderModels_005:
static CVRRenderModels_005 *fntable_RenderModels_005_instance = NULL;
static vr::IVRRenderModels_005::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_005::RenderModel_t** ppRenderModel) { return fntable_RenderModels_005_instance->LoadRenderModel_Async(pchRenderModelName, ppRenderModel); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_FreeRenderModel(vr::IVRRenderModels_005::RenderModel_t* pRenderModel) { return fntable_RenderModels_005_instance->FreeRenderModel(pRenderModel); }
static vr::IVRRenderModels_005::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_LoadTexture_Async(vr::IVRRenderModels_005::TextureID_t textureId, vr::IVRRenderModels_005::RenderModel_TextureMap_t** ppTexture) { return fntable_RenderModels_005_instance->LoadTexture_Async(textureId, ppTexture); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_FreeTexture(vr::IVRRenderModels_005::RenderModel_TextureMap_t* pTexture) { return fntable_RenderModels_005_instance->FreeTexture(pTexture); }
static vr::IVRRenderModels_005::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_LoadTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return fntable_RenderModels_005_instance->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D); }
static vr::IVRRenderModels_005::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_LoadIntoTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pDstTexture) { return fntable_RenderModels_005_instance->LoadIntoTextureD3D11_Async(textureId, pDstTexture); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_FreeTextureD3D11(void* pD3D11Texture2D) { return fntable_RenderModels_005_instance->FreeTextureD3D11(pD3D11Texture2D); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return fntable_RenderModels_005_instance->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetRenderModelCount() { return fntable_RenderModels_005_instance->GetRenderModelCount(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetComponentCount(const char* pchRenderModelName) { return fntable_RenderModels_005_instance->GetComponentCount(pchRenderModelName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return fntable_RenderModels_005_instance->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_005_instance->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return fntable_RenderModels_005_instance->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_005::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_005::RenderModel_ComponentState_t* pComponentState) { return fntable_RenderModels_005_instance->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_005_instance->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) { return fntable_RenderModels_005_instance->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_005::EVRRenderModelError* peError) { return fntable_RenderModels_005_instance->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_005_impl_GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_005::EVRRenderModelError error) { return fntable_RenderModels_005_instance->GetRenderModelErrorNameFromEnum(error); }
static void *fntable_RenderModels_005_funcs[] = {
	fntable_RenderModels_005_impl_LoadRenderModel_Async,
	fntable_RenderModels_005_impl_FreeRenderModel,
	fntable_RenderModels_005_impl_LoadTexture_Async,
	fntable_RenderModels_005_impl_FreeTexture,
	fntable_RenderModels_005_impl_LoadTextureD3D11_Async,
	fntable_RenderModels_005_impl_LoadIntoTextureD3D11_Async,
	fntable_RenderModels_005_impl_FreeTextureD3D11,
	fntable_RenderModels_005_impl_GetRenderModelName,
	fntable_RenderModels_005_impl_GetRenderModelCount,
	fntable_RenderModels_005_impl_GetComponentCount,
	fntable_RenderModels_005_impl_GetComponentName,
	fntable_RenderModels_005_impl_GetComponentButtonMask,
	fntable_RenderModels_005_impl_GetComponentRenderModelName,
	fntable_RenderModels_005_impl_GetComponentState,
	fntable_RenderModels_005_impl_RenderModelHasComponent,
	fntable_RenderModels_005_impl_GetRenderModelThumbnailURL,
	fntable_RenderModels_005_impl_GetRenderModelOriginalPath,
	fntable_RenderModels_005_impl_GetRenderModelErrorNameFromEnum,
};
void** CVRRenderModels_005::_GetStatFuncList() { fntable_RenderModels_005_instance = this; return fntable_RenderModels_005_funcs; }
// Misc for CVRRenderModels_006:
CVRRenderModels_006::CVRRenderModels_006() : base(GetCreateBaseRenderModels()) {}
// Interface methods for CVRRenderModels_006:
vr::IVRRenderModels_006::EVRRenderModelError CVRRenderModels_006::LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_006::RenderModel_t** ppRenderModel) { return (vr::IVRRenderModels_006::EVRRenderModelError) base->LoadRenderModel_Async(pchRenderModelName, (vr::RenderModel_t**) ppRenderModel); }
void CVRRenderModels_006::FreeRenderModel(vr::IVRRenderModels_006::RenderModel_t* pRenderModel) { return base->FreeRenderModel((vr::RenderModel_t*) pRenderModel); }
vr::IVRRenderModels_006::EVRRenderModelError CVRRenderModels_006::LoadTexture_Async(vr::IVRRenderModels_006::TextureID_t textureId, vr::IVRRenderModels_006::RenderModel_TextureMap_t** ppTexture) { return (vr::IVRRenderModels_006::EVRRenderModelError) base->LoadTexture_Async((vr::TextureID_t) textureId, (vr::RenderModel_TextureMap_t**) ppTexture); }
void CVRRenderModels_006::FreeTexture(vr::IVRRenderModels_006::RenderModel_TextureMap_t* pTexture) { return base->FreeTexture((vr::RenderModel_TextureMap_t*) pTexture); }
vr::IVRRenderModels_006::EVRRenderModelError CVRRenderModels_006::LoadTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return (vr::IVRRenderModels_006::EVRRenderModelError) base->LoadTextureD3D11_Async((vr::TextureID_t) textureId, pD3D11Device, ppD3D11Texture2D); }
vr::IVRRenderModels_006::EVRRenderModelError CVRRenderModels_006::LoadIntoTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pDstTexture) { return (vr::IVRRenderModels_006::EVRRenderModelError) base->LoadIntoTextureD3D11_Async((vr::TextureID_t) textureId, pDstTexture); }
void CVRRenderModels_006::FreeTextureD3D11(void* pD3D11Texture2D) { return base->FreeTextureD3D11(pD3D11Texture2D); }
uint32_t CVRRenderModels_006::GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return base->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
uint32_t CVRRenderModels_006::GetRenderModelCount() { return base->GetRenderModelCount(); }
uint32_t CVRRenderModels_006::GetComponentCount(const char* pchRenderModelName) { return base->GetComponentCount(pchRenderModelName); }
uint32_t CVRRenderModels_006::GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return base->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
uint64_t CVRRenderModels_006::GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return base->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
uint32_t CVRRenderModels_006::GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return base->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
bool CVRRenderModels_006::GetComponentStateForDevicePath(const char* pchRenderModelName, const char* pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState) { return base->GetComponentStateForDevicePath(pchRenderModelName, pchComponentName, devicePath, (const vr::RenderModel_ControllerMode_State_t*) pState, (vr::RenderModel_ComponentState_t*) pComponentState); }
bool CVRRenderModels_006::GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState) { return base->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, (const vr::RenderModel_ControllerMode_State_t*) pState, (vr::RenderModel_ComponentState_t*) pComponentState); }
bool CVRRenderModels_006::RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return base->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
uint32_t CVRRenderModels_006::GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) { return base->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, (vr::EVRRenderModelError*) peError); }
uint32_t CVRRenderModels_006::GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) { return base->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, (vr::EVRRenderModelError*) peError); }
const char* CVRRenderModels_006::GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_006::EVRRenderModelError error) { return base->GetRenderModelErrorNameFromEnum((vr::EVRRenderModelError) error); }
// FnTable for CVRRenderModels_006:
static CVRRenderModels_006 *fntable_RenderModels_006_instance = NULL;
static vr::IVRRenderModels_006::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_006::RenderModel_t** ppRenderModel) { return fntable_RenderModels_006_instance->LoadRenderModel_Async(pchRenderModelName, ppRenderModel); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_FreeRenderModel(vr::IVRRenderModels_006::RenderModel_t* pRenderModel) { return fntable_RenderModels_006_instance->FreeRenderModel(pRenderModel); }
static vr::IVRRenderModels_006::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_LoadTexture_Async(vr::IVRRenderModels_006::TextureID_t textureId, vr::IVRRenderModels_006::RenderModel_TextureMap_t** ppTexture) { return fntable_RenderModels_006_instance->LoadTexture_Async(textureId, ppTexture); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_FreeTexture(vr::IVRRenderModels_006::RenderModel_TextureMap_t* pTexture) { return fntable_RenderModels_006_instance->FreeTexture(pTexture); }
static vr::IVRRenderModels_006::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_LoadTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D) { return fntable_RenderModels_006_instance->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D); }
static vr::IVRRenderModels_006::EVRRenderModelError OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_LoadIntoTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pDstTexture) { return fntable_RenderModels_006_instance->LoadIntoTextureD3D11_Async(textureId, pDstTexture); }
static void OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_FreeTextureD3D11(void* pD3D11Texture2D) { return fntable_RenderModels_006_instance->FreeTextureD3D11(pD3D11Texture2D); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen) { return fntable_RenderModels_006_instance->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetRenderModelCount() { return fntable_RenderModels_006_instance->GetRenderModelCount(); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentCount(const char* pchRenderModelName) { return fntable_RenderModels_006_instance->GetComponentCount(pchRenderModelName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen) { return fntable_RenderModels_006_instance->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_006_instance->GetComponentButtonMask(pchRenderModelName, pchComponentName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) { return fntable_RenderModels_006_instance->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentStateForDevicePath(const char* pchRenderModelName, const char* pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState) { return fntable_RenderModels_006_instance->GetComponentStateForDevicePath(pchRenderModelName, pchComponentName, devicePath, pState, pComponentState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState) { return fntable_RenderModels_006_instance->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName) { return fntable_RenderModels_006_instance->RenderModelHasComponent(pchRenderModelName, pchComponentName); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) { return fntable_RenderModels_006_instance->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_006::EVRRenderModelError* peError) { return fntable_RenderModels_006_instance->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_RenderModels_006_impl_GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_006::EVRRenderModelError error) { return fntable_RenderModels_006_instance->GetRenderModelErrorNameFromEnum(error); }
static void *fntable_RenderModels_006_funcs[] = {
	fntable_RenderModels_006_impl_LoadRenderModel_Async,
	fntable_RenderModels_006_impl_FreeRenderModel,
	fntable_RenderModels_006_impl_LoadTexture_Async,
	fntable_RenderModels_006_impl_FreeTexture,
	fntable_RenderModels_006_impl_LoadTextureD3D11_Async,
	fntable_RenderModels_006_impl_LoadIntoTextureD3D11_Async,
	fntable_RenderModels_006_impl_FreeTextureD3D11,
	fntable_RenderModels_006_impl_GetRenderModelName,
	fntable_RenderModels_006_impl_GetRenderModelCount,
	fntable_RenderModels_006_impl_GetComponentCount,
	fntable_RenderModels_006_impl_GetComponentName,
	fntable_RenderModels_006_impl_GetComponentButtonMask,
	fntable_RenderModels_006_impl_GetComponentRenderModelName,
	fntable_RenderModels_006_impl_GetComponentStateForDevicePath,
	fntable_RenderModels_006_impl_GetComponentState,
	fntable_RenderModels_006_impl_RenderModelHasComponent,
	fntable_RenderModels_006_impl_GetRenderModelThumbnailURL,
	fntable_RenderModels_006_impl_GetRenderModelOriginalPath,
	fntable_RenderModels_006_impl_GetRenderModelErrorNameFromEnum,
};
void** CVRRenderModels_006::_GetStatFuncList() { fntable_RenderModels_006_instance = this; return fntable_RenderModels_006_funcs; }
#include "GVRScreenshots.gen.h"
// Single inst of BaseScreenshots
static std::weak_ptr<BaseScreenshots> _single_inst_Screenshots;
static BaseScreenshots *_single_inst_Screenshots_unsafe = NULL;
std::shared_ptr<BaseScreenshots> GetBaseScreenshots() { return _single_inst_Screenshots.lock(); };
BaseScreenshots* GetUnsafeBaseScreenshots() { return _single_inst_Screenshots_unsafe; };
std::shared_ptr<BaseScreenshots> GetCreateBaseScreenshots() {
	std::shared_ptr<BaseScreenshots> ret = _single_inst_Screenshots.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseScreenshots>(new BaseScreenshots(), [](BaseScreenshots *obj){ _single_inst_Screenshots_unsafe = NULL; delete obj; });
		_single_inst_Screenshots = ret;
		_single_inst_Screenshots_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRScreenshots_001:
CVRScreenshots_001::CVRScreenshots_001() : base(GetCreateBaseScreenshots()) {}
// Interface methods for CVRScreenshots_001:
vr::IVRScreenshots_001::EVRScreenshotError CVRScreenshots_001::RequestScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, vr::EVRScreenshotType type, const char* pchPreviewFilename, const char* pchVRFilename) { return (vr::IVRScreenshots_001::EVRScreenshotError) base->RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename); }
vr::IVRScreenshots_001::EVRScreenshotError CVRScreenshots_001::HookScreenshot(const vr::EVRScreenshotType* pSupportedTypes, int numTypes) { return (vr::IVRScreenshots_001::EVRScreenshotError) base->HookScreenshot(pSupportedTypes, numTypes); }
vr::EVRScreenshotType CVRScreenshots_001::GetScreenshotPropertyType(vr::ScreenshotHandle_t screenshotHandle, vr::IVRScreenshots_001::EVRScreenshotError* pError) { return base->GetScreenshotPropertyType(screenshotHandle, (vr::EVRScreenshotError*) pError); }
uint32_t CVRScreenshots_001::GetScreenshotPropertyFilename(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, char* pchFilename, uint32_t cchFilename, vr::IVRScreenshots_001::EVRScreenshotError* pError) { return base->GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, (vr::EVRScreenshotError*) pError); }
vr::IVRScreenshots_001::EVRScreenshotError CVRScreenshots_001::UpdateScreenshotProgress(vr::ScreenshotHandle_t screenshotHandle, float flProgress) { return (vr::IVRScreenshots_001::EVRScreenshotError) base->UpdateScreenshotProgress(screenshotHandle, flProgress); }
vr::IVRScreenshots_001::EVRScreenshotError CVRScreenshots_001::TakeStereoScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, const char* pchPreviewFilename, const char* pchVRFilename) { return (vr::IVRScreenshots_001::EVRScreenshotError) base->TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename); }
vr::IVRScreenshots_001::EVRScreenshotError CVRScreenshots_001::SubmitScreenshot(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char* pchSourcePreviewFilename, const char* pchSourceVRFilename) { return (vr::IVRScreenshots_001::EVRScreenshotError) base->SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename); }
// FnTable for CVRScreenshots_001:
static CVRScreenshots_001 *fntable_Screenshots_001_instance = NULL;
static vr::IVRScreenshots_001::EVRScreenshotError OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_RequestScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, vr::EVRScreenshotType type, const char* pchPreviewFilename, const char* pchVRFilename) { return fntable_Screenshots_001_instance->RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename); }
static vr::IVRScreenshots_001::EVRScreenshotError OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_HookScreenshot(const vr::EVRScreenshotType* pSupportedTypes, int numTypes) { return fntable_Screenshots_001_instance->HookScreenshot(pSupportedTypes, numTypes); }
static vr::EVRScreenshotType OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_GetScreenshotPropertyType(vr::ScreenshotHandle_t screenshotHandle, vr::IVRScreenshots_001::EVRScreenshotError* pError) { return fntable_Screenshots_001_instance->GetScreenshotPropertyType(screenshotHandle, pError); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_GetScreenshotPropertyFilename(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, char* pchFilename, uint32_t cchFilename, vr::IVRScreenshots_001::EVRScreenshotError* pError) { return fntable_Screenshots_001_instance->GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, pError); }
static vr::IVRScreenshots_001::EVRScreenshotError OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_UpdateScreenshotProgress(vr::ScreenshotHandle_t screenshotHandle, float flProgress) { return fntable_Screenshots_001_instance->UpdateScreenshotProgress(screenshotHandle, flProgress); }
static vr::IVRScreenshots_001::EVRScreenshotError OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_TakeStereoScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, const char* pchPreviewFilename, const char* pchVRFilename) { return fntable_Screenshots_001_instance->TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename); }
static vr::IVRScreenshots_001::EVRScreenshotError OPENVR_FNTABLE_CALLTYPE fntable_Screenshots_001_impl_SubmitScreenshot(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char* pchSourcePreviewFilename, const char* pchSourceVRFilename) { return fntable_Screenshots_001_instance->SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename); }
static void *fntable_Screenshots_001_funcs[] = {
	fntable_Screenshots_001_impl_RequestScreenshot,
	fntable_Screenshots_001_impl_HookScreenshot,
	fntable_Screenshots_001_impl_GetScreenshotPropertyType,
	fntable_Screenshots_001_impl_GetScreenshotPropertyFilename,
	fntable_Screenshots_001_impl_UpdateScreenshotProgress,
	fntable_Screenshots_001_impl_TakeStereoScreenshot,
	fntable_Screenshots_001_impl_SubmitScreenshot,
};
void** CVRScreenshots_001::_GetStatFuncList() { fntable_Screenshots_001_instance = this; return fntable_Screenshots_001_funcs; }
#include "GVRSettings.gen.h"
// Single inst of BaseSettings
static std::weak_ptr<BaseSettings> _single_inst_Settings;
static BaseSettings *_single_inst_Settings_unsafe = NULL;
std::shared_ptr<BaseSettings> GetBaseSettings() { return _single_inst_Settings.lock(); };
BaseSettings* GetUnsafeBaseSettings() { return _single_inst_Settings_unsafe; };
std::shared_ptr<BaseSettings> GetCreateBaseSettings() {
	std::shared_ptr<BaseSettings> ret = _single_inst_Settings.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseSettings>(new BaseSettings(), [](BaseSettings *obj){ _single_inst_Settings_unsafe = NULL; delete obj; });
		_single_inst_Settings = ret;
		_single_inst_Settings_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRSettings_001:
CVRSettings_001::CVRSettings_001() : base(GetCreateBaseSettings()) {}
// Interface methods for CVRSettings_001:
const char* CVRSettings_001::GetSettingsErrorNameFromEnum(vr::IVRSettings_001::EVRSettingsError eError) { return base->GetSettingsErrorNameFromEnum((vr::EVRSettingsError) eError); }
bool CVRSettings_001::Sync(bool bForce, vr::IVRSettings_001::EVRSettingsError* peError) { return base->Sync(bForce, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_001::EVRSettingsError* peError) { return base->SetBool(pchSection, pchSettingsKey, bValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_001::EVRSettingsError* peError) { return base->SetInt32(pchSection, pchSettingsKey, nValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_001::EVRSettingsError* peError) { return base->SetFloat(pchSection, pchSettingsKey, flValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_001::EVRSettingsError* peError) { return base->SetString(pchSection, pchSettingsKey, pchValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::RemoveSection(const char* pchSection, vr::IVRSettings_001::EVRSettingsError* peError) { return base->RemoveSection(pchSection, (vr::EVRSettingsError*) peError); }
void CVRSettings_001::RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_001::EVRSettingsError* peError) { return base->RemoveKeyInSection(pchSection, pchSettingsKey, (vr::EVRSettingsError*) peError); }
// FnTable for CVRSettings_001:
static CVRSettings_001 *fntable_Settings_001_instance = NULL;
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_GetSettingsErrorNameFromEnum(vr::IVRSettings_001::EVRSettingsError eError) { return fntable_Settings_001_instance->GetSettingsErrorNameFromEnum(eError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_Sync(bool bForce, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->Sync(bForce, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_GetBool(const char* pchSection, const char* pchSettingsKey, bool bDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->GetBool(pchSection, pchSettingsKey, bDefaultValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->SetBool(pchSection, pchSettingsKey, bValue, peError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_GetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->GetInt32(pchSection, pchSettingsKey, nDefaultValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->SetInt32(pchSection, pchSettingsKey, nValue, peError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_GetFloat(const char* pchSection, const char* pchSettingsKey, float flDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->GetFloat(pchSection, pchSettingsKey, flDefaultValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->SetFloat(pchSection, pchSettingsKey, flValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, const char* pchDefaultValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, pchDefaultValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->SetString(pchSection, pchSettingsKey, pchValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_RemoveSection(const char* pchSection, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->RemoveSection(pchSection, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_001_impl_RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_001::EVRSettingsError* peError) { return fntable_Settings_001_instance->RemoveKeyInSection(pchSection, pchSettingsKey, peError); }
static void *fntable_Settings_001_funcs[] = {
	fntable_Settings_001_impl_GetSettingsErrorNameFromEnum,
	fntable_Settings_001_impl_Sync,
	fntable_Settings_001_impl_GetBool,
	fntable_Settings_001_impl_SetBool,
	fntable_Settings_001_impl_GetInt32,
	fntable_Settings_001_impl_SetInt32,
	fntable_Settings_001_impl_GetFloat,
	fntable_Settings_001_impl_SetFloat,
	fntable_Settings_001_impl_GetString,
	fntable_Settings_001_impl_SetString,
	fntable_Settings_001_impl_RemoveSection,
	fntable_Settings_001_impl_RemoveKeyInSection,
};
void** CVRSettings_001::_GetStatFuncList() { fntable_Settings_001_instance = this; return fntable_Settings_001_funcs; }
// Misc for CVRSettings_002:
CVRSettings_002::CVRSettings_002() : base(GetCreateBaseSettings()) {}
// Interface methods for CVRSettings_002:
const char* CVRSettings_002::GetSettingsErrorNameFromEnum(vr::IVRSettings_002::EVRSettingsError eError) { return base->GetSettingsErrorNameFromEnum((vr::EVRSettingsError) eError); }
bool CVRSettings_002::Sync(bool bForce, vr::IVRSettings_002::EVRSettingsError* peError) { return base->Sync(bForce, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_002::EVRSettingsError* peError) { return base->SetBool(pchSection, pchSettingsKey, bValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_002::EVRSettingsError* peError) { return base->SetInt32(pchSection, pchSettingsKey, nValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_002::EVRSettingsError* peError) { return base->SetFloat(pchSection, pchSettingsKey, flValue, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_002::EVRSettingsError* peError) { return base->SetString(pchSection, pchSettingsKey, pchValue, (vr::EVRSettingsError*) peError); }
bool CVRSettings_002::GetBool(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return base->GetBool(pchSection, pchSettingsKey, (vr::EVRSettingsError*) peError); }
int32_t CVRSettings_002::GetInt32(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return base->GetInt32(pchSection, pchSettingsKey, (vr::EVRSettingsError*) peError); }
float CVRSettings_002::GetFloat(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return base->GetFloat(pchSection, pchSettingsKey, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, vr::IVRSettings_002::EVRSettingsError* peError) { return base->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::RemoveSection(const char* pchSection, vr::IVRSettings_002::EVRSettingsError* peError) { return base->RemoveSection(pchSection, (vr::EVRSettingsError*) peError); }
void CVRSettings_002::RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return base->RemoveKeyInSection(pchSection, pchSettingsKey, (vr::EVRSettingsError*) peError); }
// FnTable for CVRSettings_002:
static CVRSettings_002 *fntable_Settings_002_instance = NULL;
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_GetSettingsErrorNameFromEnum(vr::IVRSettings_002::EVRSettingsError eError) { return fntable_Settings_002_instance->GetSettingsErrorNameFromEnum(eError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_Sync(bool bForce, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->Sync(bForce, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_SetBool(const char* pchSection, const char* pchSettingsKey, bool bValue, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->SetBool(pchSection, pchSettingsKey, bValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_SetInt32(const char* pchSection, const char* pchSettingsKey, int32_t nValue, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->SetInt32(pchSection, pchSettingsKey, nValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_SetFloat(const char* pchSection, const char* pchSettingsKey, float flValue, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->SetFloat(pchSection, pchSettingsKey, flValue, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_SetString(const char* pchSection, const char* pchSettingsKey, const char* pchValue, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->SetString(pchSection, pchSettingsKey, pchValue, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_GetBool(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->GetBool(pchSection, pchSettingsKey, peError); }
static int32_t OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_GetInt32(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->GetInt32(pchSection, pchSettingsKey, peError); }
static float OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_GetFloat(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->GetFloat(pchSection, pchSettingsKey, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_GetString(const char* pchSection, const char* pchSettingsKey, char* pchValue, uint32_t unValueLen, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_RemoveSection(const char* pchSection, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->RemoveSection(pchSection, peError); }
static void OPENVR_FNTABLE_CALLTYPE fntable_Settings_002_impl_RemoveKeyInSection(const char* pchSection, const char* pchSettingsKey, vr::IVRSettings_002::EVRSettingsError* peError) { return fntable_Settings_002_instance->RemoveKeyInSection(pchSection, pchSettingsKey, peError); }
static void *fntable_Settings_002_funcs[] = {
	fntable_Settings_002_impl_GetSettingsErrorNameFromEnum,
	fntable_Settings_002_impl_Sync,
	fntable_Settings_002_impl_SetBool,
	fntable_Settings_002_impl_SetInt32,
	fntable_Settings_002_impl_SetFloat,
	fntable_Settings_002_impl_SetString,
	fntable_Settings_002_impl_GetBool,
	fntable_Settings_002_impl_GetInt32,
	fntable_Settings_002_impl_GetFloat,
	fntable_Settings_002_impl_GetString,
	fntable_Settings_002_impl_RemoveSection,
	fntable_Settings_002_impl_RemoveKeyInSection,
};
void** CVRSettings_002::_GetStatFuncList() { fntable_Settings_002_instance = this; return fntable_Settings_002_funcs; }
#include "GVRExtendedDisplay.gen.h"
// Single inst of BaseExtendedDisplay
static std::weak_ptr<BaseExtendedDisplay> _single_inst_ExtendedDisplay;
static BaseExtendedDisplay *_single_inst_ExtendedDisplay_unsafe = NULL;
std::shared_ptr<BaseExtendedDisplay> GetBaseExtendedDisplay() { return _single_inst_ExtendedDisplay.lock(); };
BaseExtendedDisplay* GetUnsafeBaseExtendedDisplay() { return _single_inst_ExtendedDisplay_unsafe; };
std::shared_ptr<BaseExtendedDisplay> GetCreateBaseExtendedDisplay() {
	std::shared_ptr<BaseExtendedDisplay> ret = _single_inst_ExtendedDisplay.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseExtendedDisplay>(new BaseExtendedDisplay(), [](BaseExtendedDisplay *obj){ _single_inst_ExtendedDisplay_unsafe = NULL; delete obj; });
		_single_inst_ExtendedDisplay = ret;
		_single_inst_ExtendedDisplay_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRExtendedDisplay_001:
CVRExtendedDisplay_001::CVRExtendedDisplay_001() : base(GetCreateBaseExtendedDisplay()) {}
// Interface methods for CVRExtendedDisplay_001:
void CVRExtendedDisplay_001::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetWindowBounds(pnX, pnY, pnWidth, pnHeight); }
void CVRExtendedDisplay_001::GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) { return base->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight); }
void CVRExtendedDisplay_001::GetDXGIOutputInfo(int32_t* pnAdapterIndex, int32_t* pnAdapterOutputIndex) { return base->GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex); }
// FnTable for CVRExtendedDisplay_001:
static CVRExtendedDisplay_001 *fntable_ExtendedDisplay_001_instance = NULL;
static void OPENVR_FNTABLE_CALLTYPE fntable_ExtendedDisplay_001_impl_GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_ExtendedDisplay_001_instance->GetWindowBounds(pnX, pnY, pnWidth, pnHeight); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ExtendedDisplay_001_impl_GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) { return fntable_ExtendedDisplay_001_instance->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ExtendedDisplay_001_impl_GetDXGIOutputInfo(int32_t* pnAdapterIndex, int32_t* pnAdapterOutputIndex) { return fntable_ExtendedDisplay_001_instance->GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex); }
static void *fntable_ExtendedDisplay_001_funcs[] = {
	fntable_ExtendedDisplay_001_impl_GetWindowBounds,
	fntable_ExtendedDisplay_001_impl_GetEyeOutputViewport,
	fntable_ExtendedDisplay_001_impl_GetDXGIOutputInfo,
};
void** CVRExtendedDisplay_001::_GetStatFuncList() { fntable_ExtendedDisplay_001_instance = this; return fntable_ExtendedDisplay_001_funcs; }
#include "GVRApplications.gen.h"
// Single inst of BaseApplications
static std::weak_ptr<BaseApplications> _single_inst_Applications;
static BaseApplications *_single_inst_Applications_unsafe = NULL;
std::shared_ptr<BaseApplications> GetBaseApplications() { return _single_inst_Applications.lock(); };
BaseApplications* GetUnsafeBaseApplications() { return _single_inst_Applications_unsafe; };
std::shared_ptr<BaseApplications> GetCreateBaseApplications() {
	std::shared_ptr<BaseApplications> ret = _single_inst_Applications.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseApplications>(new BaseApplications(), [](BaseApplications *obj){ _single_inst_Applications_unsafe = NULL; delete obj; });
		_single_inst_Applications = ret;
		_single_inst_Applications_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRApplications_004:
CVRApplications_004::CVRApplications_004() : base(GetCreateBaseApplications()) {}
// Interface methods for CVRApplications_004:
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return (vr::IVRApplications_004::EVRApplicationError) base->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return (vr::IVRApplications_004::EVRApplicationError) base->RemoveApplicationManifest(pchApplicationManifestFullPath); }
bool CVRApplications_004::IsApplicationInstalled(const char* pchAppKey) { return base->IsApplicationInstalled(pchAppKey); }
uint32_t CVRApplications_004::GetApplicationCount() { return base->GetApplicationCount(); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_004::EVRApplicationError) base->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_004::EVRApplicationError) base->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::LaunchApplication(const char* pchAppKey) { return (vr::IVRApplications_004::EVRApplicationError) base->LaunchApplication(pchAppKey); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::LaunchDashboardOverlay(const char* pchAppKey) { return (vr::IVRApplications_004::EVRApplicationError) base->LaunchDashboardOverlay(pchAppKey); }
bool CVRApplications_004::CancelApplicationLaunch(const char* pchAppKey) { return base->CancelApplicationLaunch(pchAppKey); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return (vr::IVRApplications_004::EVRApplicationError) base->IdentifyApplication(unProcessId, pchAppKey); }
uint32_t CVRApplications_004::GetApplicationProcessId(const char* pchAppKey) { return base->GetApplicationProcessId(pchAppKey); }
const char* CVRApplications_004::GetApplicationsErrorNameFromEnum(vr::IVRApplications_004::EVRApplicationError error) { return base->GetApplicationsErrorNameFromEnum((vr::EVRApplicationError) error); }
uint32_t CVRApplications_004::GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_004::EVRApplicationError* peError) { return base->GetApplicationPropertyString(pchAppKey, (vr::EVRApplicationProperty) eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, (vr::EVRApplicationError*) peError); }
bool CVRApplications_004::GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) { return base->GetApplicationPropertyBool(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
uint64_t CVRApplications_004::GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) { return base->GetApplicationPropertyUint64(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return (vr::IVRApplications_004::EVRApplicationError) base->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
bool CVRApplications_004::GetApplicationAutoLaunch(const char* pchAppKey) { return base->GetApplicationAutoLaunch(pchAppKey); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_004::EVRApplicationError) base->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_004::EVRApplicationTransitionState CVRApplications_004::GetTransitionState() { return (vr::IVRApplications_004::EVRApplicationTransitionState) base->GetTransitionState(); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::PerformApplicationPrelaunchCheck(const char* pchAppKey) { return (vr::IVRApplications_004::EVRApplicationError) base->PerformApplicationPrelaunchCheck(pchAppKey); }
const char* CVRApplications_004::GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_004::EVRApplicationTransitionState state) { return base->GetApplicationsTransitionStateNameFromEnum((vr::EVRApplicationTransitionState) state); }
bool CVRApplications_004::IsQuitUserPromptRequested() { return base->IsQuitUserPromptRequested(); }
vr::IVRApplications_004::EVRApplicationError CVRApplications_004::LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return (vr::IVRApplications_004::EVRApplicationError) base->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
// FnTable for CVRApplications_004:
static CVRApplications_004 *fntable_Applications_004_instance = NULL;
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return fntable_Applications_004_instance->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return fntable_Applications_004_instance->RemoveApplicationManifest(pchApplicationManifestFullPath); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_IsApplicationInstalled(const char* pchAppKey) { return fntable_Applications_004_instance->IsApplicationInstalled(pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationCount() { return fntable_Applications_004_instance->GetApplicationCount(); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_004_instance->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_004_instance->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_LaunchApplication(const char* pchAppKey) { return fntable_Applications_004_instance->LaunchApplication(pchAppKey); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_LaunchDashboardOverlay(const char* pchAppKey) { return fntable_Applications_004_instance->LaunchDashboardOverlay(pchAppKey); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_CancelApplicationLaunch(const char* pchAppKey) { return fntable_Applications_004_instance->CancelApplicationLaunch(pchAppKey); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return fntable_Applications_004_instance->IdentifyApplication(unProcessId, pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationProcessId(const char* pchAppKey) { return fntable_Applications_004_instance->GetApplicationProcessId(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationsErrorNameFromEnum(vr::IVRApplications_004::EVRApplicationError error) { return fntable_Applications_004_instance->GetApplicationsErrorNameFromEnum(error); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_004::EVRApplicationError* peError) { return fntable_Applications_004_instance->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) { return fntable_Applications_004_instance->GetApplicationPropertyBool(pchAppKey, eProperty, peError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError) { return fntable_Applications_004_instance->GetApplicationPropertyUint64(pchAppKey, eProperty, peError); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return fntable_Applications_004_instance->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationAutoLaunch(const char* pchAppKey) { return fntable_Applications_004_instance->GetApplicationAutoLaunch(pchAppKey); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_004_instance->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_004::EVRApplicationTransitionState OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetTransitionState() { return fntable_Applications_004_instance->GetTransitionState(); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_PerformApplicationPrelaunchCheck(const char* pchAppKey) { return fntable_Applications_004_instance->PerformApplicationPrelaunchCheck(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_004::EVRApplicationTransitionState state) { return fntable_Applications_004_instance->GetApplicationsTransitionStateNameFromEnum(state); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_IsQuitUserPromptRequested() { return fntable_Applications_004_instance->IsQuitUserPromptRequested(); }
static vr::IVRApplications_004::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_004_impl_LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return fntable_Applications_004_instance->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
static void *fntable_Applications_004_funcs[] = {
	fntable_Applications_004_impl_AddApplicationManifest,
	fntable_Applications_004_impl_RemoveApplicationManifest,
	fntable_Applications_004_impl_IsApplicationInstalled,
	fntable_Applications_004_impl_GetApplicationCount,
	fntable_Applications_004_impl_GetApplicationKeyByIndex,
	fntable_Applications_004_impl_GetApplicationKeyByProcessId,
	fntable_Applications_004_impl_LaunchApplication,
	fntable_Applications_004_impl_LaunchDashboardOverlay,
	fntable_Applications_004_impl_CancelApplicationLaunch,
	fntable_Applications_004_impl_IdentifyApplication,
	fntable_Applications_004_impl_GetApplicationProcessId,
	fntable_Applications_004_impl_GetApplicationsErrorNameFromEnum,
	fntable_Applications_004_impl_GetApplicationPropertyString,
	fntable_Applications_004_impl_GetApplicationPropertyBool,
	fntable_Applications_004_impl_GetApplicationPropertyUint64,
	fntable_Applications_004_impl_SetApplicationAutoLaunch,
	fntable_Applications_004_impl_GetApplicationAutoLaunch,
	fntable_Applications_004_impl_GetStartingApplication,
	fntable_Applications_004_impl_GetTransitionState,
	fntable_Applications_004_impl_PerformApplicationPrelaunchCheck,
	fntable_Applications_004_impl_GetApplicationsTransitionStateNameFromEnum,
	fntable_Applications_004_impl_IsQuitUserPromptRequested,
	fntable_Applications_004_impl_LaunchInternalProcess,
};
void** CVRApplications_004::_GetStatFuncList() { fntable_Applications_004_instance = this; return fntable_Applications_004_funcs; }
// Misc for CVRApplications_005:
CVRApplications_005::CVRApplications_005() : base(GetCreateBaseApplications()) {}
// Interface methods for CVRApplications_005:
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return (vr::IVRApplications_005::EVRApplicationError) base->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return (vr::IVRApplications_005::EVRApplicationError) base->RemoveApplicationManifest(pchApplicationManifestFullPath); }
bool CVRApplications_005::IsApplicationInstalled(const char* pchAppKey) { return base->IsApplicationInstalled(pchAppKey); }
uint32_t CVRApplications_005::GetApplicationCount() { return base->GetApplicationCount(); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_005::EVRApplicationError) base->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_005::EVRApplicationError) base->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::LaunchApplication(const char* pchAppKey) { return (vr::IVRApplications_005::EVRApplicationError) base->LaunchApplication(pchAppKey); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_005::AppOverrideKeys_t* pKeys, uint32_t unKeys) { return (vr::IVRApplications_005::EVRApplicationError) base->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, (const vr::AppOverrideKeys_t*) pKeys, unKeys); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::LaunchDashboardOverlay(const char* pchAppKey) { return (vr::IVRApplications_005::EVRApplicationError) base->LaunchDashboardOverlay(pchAppKey); }
bool CVRApplications_005::CancelApplicationLaunch(const char* pchAppKey) { return base->CancelApplicationLaunch(pchAppKey); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return (vr::IVRApplications_005::EVRApplicationError) base->IdentifyApplication(unProcessId, pchAppKey); }
uint32_t CVRApplications_005::GetApplicationProcessId(const char* pchAppKey) { return base->GetApplicationProcessId(pchAppKey); }
const char* CVRApplications_005::GetApplicationsErrorNameFromEnum(vr::IVRApplications_005::EVRApplicationError error) { return base->GetApplicationsErrorNameFromEnum((vr::EVRApplicationError) error); }
uint32_t CVRApplications_005::GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_005::EVRApplicationError* peError) { return base->GetApplicationPropertyString(pchAppKey, (vr::EVRApplicationProperty) eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, (vr::EVRApplicationError*) peError); }
bool CVRApplications_005::GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) { return base->GetApplicationPropertyBool(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
uint64_t CVRApplications_005::GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) { return base->GetApplicationPropertyUint64(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return (vr::IVRApplications_005::EVRApplicationError) base->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
bool CVRApplications_005::GetApplicationAutoLaunch(const char* pchAppKey) { return base->GetApplicationAutoLaunch(pchAppKey); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_005::EVRApplicationError) base->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_005::EVRApplicationTransitionState CVRApplications_005::GetTransitionState() { return (vr::IVRApplications_005::EVRApplicationTransitionState) base->GetTransitionState(); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::PerformApplicationPrelaunchCheck(const char* pchAppKey) { return (vr::IVRApplications_005::EVRApplicationError) base->PerformApplicationPrelaunchCheck(pchAppKey); }
const char* CVRApplications_005::GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_005::EVRApplicationTransitionState state) { return base->GetApplicationsTransitionStateNameFromEnum((vr::EVRApplicationTransitionState) state); }
bool CVRApplications_005::IsQuitUserPromptRequested() { return base->IsQuitUserPromptRequested(); }
vr::IVRApplications_005::EVRApplicationError CVRApplications_005::LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return (vr::IVRApplications_005::EVRApplicationError) base->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
// FnTable for CVRApplications_005:
static CVRApplications_005 *fntable_Applications_005_instance = NULL;
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return fntable_Applications_005_instance->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return fntable_Applications_005_instance->RemoveApplicationManifest(pchApplicationManifestFullPath); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_IsApplicationInstalled(const char* pchAppKey) { return fntable_Applications_005_instance->IsApplicationInstalled(pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationCount() { return fntable_Applications_005_instance->GetApplicationCount(); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_005_instance->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_005_instance->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_LaunchApplication(const char* pchAppKey) { return fntable_Applications_005_instance->LaunchApplication(pchAppKey); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_005::AppOverrideKeys_t* pKeys, uint32_t unKeys) { return fntable_Applications_005_instance->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_LaunchDashboardOverlay(const char* pchAppKey) { return fntable_Applications_005_instance->LaunchDashboardOverlay(pchAppKey); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_CancelApplicationLaunch(const char* pchAppKey) { return fntable_Applications_005_instance->CancelApplicationLaunch(pchAppKey); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return fntable_Applications_005_instance->IdentifyApplication(unProcessId, pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationProcessId(const char* pchAppKey) { return fntable_Applications_005_instance->GetApplicationProcessId(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationsErrorNameFromEnum(vr::IVRApplications_005::EVRApplicationError error) { return fntable_Applications_005_instance->GetApplicationsErrorNameFromEnum(error); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_005::EVRApplicationError* peError) { return fntable_Applications_005_instance->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) { return fntable_Applications_005_instance->GetApplicationPropertyBool(pchAppKey, eProperty, peError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError) { return fntable_Applications_005_instance->GetApplicationPropertyUint64(pchAppKey, eProperty, peError); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return fntable_Applications_005_instance->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationAutoLaunch(const char* pchAppKey) { return fntable_Applications_005_instance->GetApplicationAutoLaunch(pchAppKey); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_005_instance->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_005::EVRApplicationTransitionState OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetTransitionState() { return fntable_Applications_005_instance->GetTransitionState(); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_PerformApplicationPrelaunchCheck(const char* pchAppKey) { return fntable_Applications_005_instance->PerformApplicationPrelaunchCheck(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_005::EVRApplicationTransitionState state) { return fntable_Applications_005_instance->GetApplicationsTransitionStateNameFromEnum(state); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_IsQuitUserPromptRequested() { return fntable_Applications_005_instance->IsQuitUserPromptRequested(); }
static vr::IVRApplications_005::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_005_impl_LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return fntable_Applications_005_instance->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
static void *fntable_Applications_005_funcs[] = {
	fntable_Applications_005_impl_AddApplicationManifest,
	fntable_Applications_005_impl_RemoveApplicationManifest,
	fntable_Applications_005_impl_IsApplicationInstalled,
	fntable_Applications_005_impl_GetApplicationCount,
	fntable_Applications_005_impl_GetApplicationKeyByIndex,
	fntable_Applications_005_impl_GetApplicationKeyByProcessId,
	fntable_Applications_005_impl_LaunchApplication,
	fntable_Applications_005_impl_LaunchTemplateApplication,
	fntable_Applications_005_impl_LaunchDashboardOverlay,
	fntable_Applications_005_impl_CancelApplicationLaunch,
	fntable_Applications_005_impl_IdentifyApplication,
	fntable_Applications_005_impl_GetApplicationProcessId,
	fntable_Applications_005_impl_GetApplicationsErrorNameFromEnum,
	fntable_Applications_005_impl_GetApplicationPropertyString,
	fntable_Applications_005_impl_GetApplicationPropertyBool,
	fntable_Applications_005_impl_GetApplicationPropertyUint64,
	fntable_Applications_005_impl_SetApplicationAutoLaunch,
	fntable_Applications_005_impl_GetApplicationAutoLaunch,
	fntable_Applications_005_impl_GetStartingApplication,
	fntable_Applications_005_impl_GetTransitionState,
	fntable_Applications_005_impl_PerformApplicationPrelaunchCheck,
	fntable_Applications_005_impl_GetApplicationsTransitionStateNameFromEnum,
	fntable_Applications_005_impl_IsQuitUserPromptRequested,
	fntable_Applications_005_impl_LaunchInternalProcess,
};
void** CVRApplications_005::_GetStatFuncList() { fntable_Applications_005_instance = this; return fntable_Applications_005_funcs; }
// Misc for CVRApplications_006:
CVRApplications_006::CVRApplications_006() : base(GetCreateBaseApplications()) {}
// Interface methods for CVRApplications_006:
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return (vr::IVRApplications_006::EVRApplicationError) base->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return (vr::IVRApplications_006::EVRApplicationError) base->RemoveApplicationManifest(pchApplicationManifestFullPath); }
bool CVRApplications_006::IsApplicationInstalled(const char* pchAppKey) { return base->IsApplicationInstalled(pchAppKey); }
uint32_t CVRApplications_006::GetApplicationCount() { return base->GetApplicationCount(); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_006::EVRApplicationError) base->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_006::EVRApplicationError) base->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::LaunchApplication(const char* pchAppKey) { return (vr::IVRApplications_006::EVRApplicationError) base->LaunchApplication(pchAppKey); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_006::AppOverrideKeys_t* pKeys, uint32_t unKeys) { return (vr::IVRApplications_006::EVRApplicationError) base->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, (const vr::AppOverrideKeys_t*) pKeys, unKeys); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::LaunchApplicationFromMimeType(const char* pchMimeType, const char* pchArgs) { return (vr::IVRApplications_006::EVRApplicationError) base->LaunchApplicationFromMimeType(pchMimeType, pchArgs); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::LaunchDashboardOverlay(const char* pchAppKey) { return (vr::IVRApplications_006::EVRApplicationError) base->LaunchDashboardOverlay(pchAppKey); }
bool CVRApplications_006::CancelApplicationLaunch(const char* pchAppKey) { return base->CancelApplicationLaunch(pchAppKey); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return (vr::IVRApplications_006::EVRApplicationError) base->IdentifyApplication(unProcessId, pchAppKey); }
uint32_t CVRApplications_006::GetApplicationProcessId(const char* pchAppKey) { return base->GetApplicationProcessId(pchAppKey); }
const char* CVRApplications_006::GetApplicationsErrorNameFromEnum(vr::IVRApplications_006::EVRApplicationError error) { return base->GetApplicationsErrorNameFromEnum((vr::EVRApplicationError) error); }
uint32_t CVRApplications_006::GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_006::EVRApplicationError* peError) { return base->GetApplicationPropertyString(pchAppKey, (vr::EVRApplicationProperty) eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, (vr::EVRApplicationError*) peError); }
bool CVRApplications_006::GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) { return base->GetApplicationPropertyBool(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
uint64_t CVRApplications_006::GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) { return base->GetApplicationPropertyUint64(pchAppKey, (vr::EVRApplicationProperty) eProperty, (vr::EVRApplicationError*) peError); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return (vr::IVRApplications_006::EVRApplicationError) base->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
bool CVRApplications_006::GetApplicationAutoLaunch(const char* pchAppKey) { return base->GetApplicationAutoLaunch(pchAppKey); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::SetDefaultApplicationForMimeType(const char* pchAppKey, const char* pchMimeType) { return (vr::IVRApplications_006::EVRApplicationError) base->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType); }
bool CVRApplications_006::GetDefaultApplicationForMimeType(const char* pchMimeType, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return base->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen); }
bool CVRApplications_006::GetApplicationSupportedMimeTypes(const char* pchAppKey, char* pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) { return base->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer); }
uint32_t CVRApplications_006::GetApplicationsThatSupportMimeType(const char* pchMimeType, char* pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) { return base->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer); }
uint32_t CVRApplications_006::GetApplicationLaunchArguments(uint32_t unHandle, char* pchArgs, uint32_t unArgs) { return base->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return (vr::IVRApplications_006::EVRApplicationError) base->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
vr::IVRApplications_006::EVRApplicationTransitionState CVRApplications_006::GetTransitionState() { return (vr::IVRApplications_006::EVRApplicationTransitionState) base->GetTransitionState(); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::PerformApplicationPrelaunchCheck(const char* pchAppKey) { return (vr::IVRApplications_006::EVRApplicationError) base->PerformApplicationPrelaunchCheck(pchAppKey); }
const char* CVRApplications_006::GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_006::EVRApplicationTransitionState state) { return base->GetApplicationsTransitionStateNameFromEnum((vr::EVRApplicationTransitionState) state); }
bool CVRApplications_006::IsQuitUserPromptRequested() { return base->IsQuitUserPromptRequested(); }
vr::IVRApplications_006::EVRApplicationError CVRApplications_006::LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return (vr::IVRApplications_006::EVRApplicationError) base->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
uint32_t CVRApplications_006::GetCurrentSceneProcessId() { return base->GetCurrentSceneProcessId(); }
// FnTable for CVRApplications_006:
static CVRApplications_006 *fntable_Applications_006_instance = NULL;
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary) { return fntable_Applications_006_instance->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_RemoveApplicationManifest(const char* pchApplicationManifestFullPath) { return fntable_Applications_006_instance->RemoveApplicationManifest(pchApplicationManifestFullPath); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_IsApplicationInstalled(const char* pchAppKey) { return fntable_Applications_006_instance->IsApplicationInstalled(pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationCount() { return fntable_Applications_006_instance->GetApplicationCount(); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_006_instance->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_006_instance->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_LaunchApplication(const char* pchAppKey) { return fntable_Applications_006_instance->LaunchApplication(pchAppKey); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_006::AppOverrideKeys_t* pKeys, uint32_t unKeys) { return fntable_Applications_006_instance->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_LaunchApplicationFromMimeType(const char* pchMimeType, const char* pchArgs) { return fntable_Applications_006_instance->LaunchApplicationFromMimeType(pchMimeType, pchArgs); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_LaunchDashboardOverlay(const char* pchAppKey) { return fntable_Applications_006_instance->LaunchDashboardOverlay(pchAppKey); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_CancelApplicationLaunch(const char* pchAppKey) { return fntable_Applications_006_instance->CancelApplicationLaunch(pchAppKey); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_IdentifyApplication(uint32_t unProcessId, const char* pchAppKey) { return fntable_Applications_006_instance->IdentifyApplication(unProcessId, pchAppKey); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationProcessId(const char* pchAppKey) { return fntable_Applications_006_instance->GetApplicationProcessId(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationsErrorNameFromEnum(vr::IVRApplications_006::EVRApplicationError error) { return fntable_Applications_006_instance->GetApplicationsErrorNameFromEnum(error); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_006::EVRApplicationError* peError) { return fntable_Applications_006_instance->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) { return fntable_Applications_006_instance->GetApplicationPropertyBool(pchAppKey, eProperty, peError); }
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError) { return fntable_Applications_006_instance->GetApplicationPropertyUint64(pchAppKey, eProperty, peError); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch) { return fntable_Applications_006_instance->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationAutoLaunch(const char* pchAppKey) { return fntable_Applications_006_instance->GetApplicationAutoLaunch(pchAppKey); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_SetDefaultApplicationForMimeType(const char* pchAppKey, const char* pchMimeType) { return fntable_Applications_006_instance->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetDefaultApplicationForMimeType(const char* pchMimeType, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_006_instance->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationSupportedMimeTypes(const char* pchAppKey, char* pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) { return fntable_Applications_006_instance->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationsThatSupportMimeType(const char* pchMimeType, char* pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) { return fntable_Applications_006_instance->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationLaunchArguments(uint32_t unHandle, char* pchArgs, uint32_t unArgs) { return fntable_Applications_006_instance->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen) { return fntable_Applications_006_instance->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }
static vr::IVRApplications_006::EVRApplicationTransitionState OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetTransitionState() { return fntable_Applications_006_instance->GetTransitionState(); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_PerformApplicationPrelaunchCheck(const char* pchAppKey) { return fntable_Applications_006_instance->PerformApplicationPrelaunchCheck(pchAppKey); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_006::EVRApplicationTransitionState state) { return fntable_Applications_006_instance->GetApplicationsTransitionStateNameFromEnum(state); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_IsQuitUserPromptRequested() { return fntable_Applications_006_instance->IsQuitUserPromptRequested(); }
static vr::IVRApplications_006::EVRApplicationError OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory) { return fntable_Applications_006_instance->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
static uint32_t OPENVR_FNTABLE_CALLTYPE fntable_Applications_006_impl_GetCurrentSceneProcessId() { return fntable_Applications_006_instance->GetCurrentSceneProcessId(); }
static void *fntable_Applications_006_funcs[] = {
	fntable_Applications_006_impl_AddApplicationManifest,
	fntable_Applications_006_impl_RemoveApplicationManifest,
	fntable_Applications_006_impl_IsApplicationInstalled,
	fntable_Applications_006_impl_GetApplicationCount,
	fntable_Applications_006_impl_GetApplicationKeyByIndex,
	fntable_Applications_006_impl_GetApplicationKeyByProcessId,
	fntable_Applications_006_impl_LaunchApplication,
	fntable_Applications_006_impl_LaunchTemplateApplication,
	fntable_Applications_006_impl_LaunchApplicationFromMimeType,
	fntable_Applications_006_impl_LaunchDashboardOverlay,
	fntable_Applications_006_impl_CancelApplicationLaunch,
	fntable_Applications_006_impl_IdentifyApplication,
	fntable_Applications_006_impl_GetApplicationProcessId,
	fntable_Applications_006_impl_GetApplicationsErrorNameFromEnum,
	fntable_Applications_006_impl_GetApplicationPropertyString,
	fntable_Applications_006_impl_GetApplicationPropertyBool,
	fntable_Applications_006_impl_GetApplicationPropertyUint64,
	fntable_Applications_006_impl_SetApplicationAutoLaunch,
	fntable_Applications_006_impl_GetApplicationAutoLaunch,
	fntable_Applications_006_impl_SetDefaultApplicationForMimeType,
	fntable_Applications_006_impl_GetDefaultApplicationForMimeType,
	fntable_Applications_006_impl_GetApplicationSupportedMimeTypes,
	fntable_Applications_006_impl_GetApplicationsThatSupportMimeType,
	fntable_Applications_006_impl_GetApplicationLaunchArguments,
	fntable_Applications_006_impl_GetStartingApplication,
	fntable_Applications_006_impl_GetTransitionState,
	fntable_Applications_006_impl_PerformApplicationPrelaunchCheck,
	fntable_Applications_006_impl_GetApplicationsTransitionStateNameFromEnum,
	fntable_Applications_006_impl_IsQuitUserPromptRequested,
	fntable_Applications_006_impl_LaunchInternalProcess,
	fntable_Applications_006_impl_GetCurrentSceneProcessId,
};
void** CVRApplications_006::_GetStatFuncList() { fntable_Applications_006_instance = this; return fntable_Applications_006_funcs; }
#include "GVRInput.gen.h"
// Single inst of BaseInput
static std::weak_ptr<BaseInput> _single_inst_Input;
static BaseInput *_single_inst_Input_unsafe = NULL;
std::shared_ptr<BaseInput> GetBaseInput() { return _single_inst_Input.lock(); };
BaseInput* GetUnsafeBaseInput() { return _single_inst_Input_unsafe; };
std::shared_ptr<BaseInput> GetCreateBaseInput() {
	std::shared_ptr<BaseInput> ret = _single_inst_Input.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseInput>(new BaseInput(), [](BaseInput *obj){ _single_inst_Input_unsafe = NULL; delete obj; });
		_single_inst_Input = ret;
		_single_inst_Input_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRInput_004:
CVRInput_004::CVRInput_004() : base(GetCreateBaseInput()) {}
// Interface methods for CVRInput_004:
vr::EVRInputError CVRInput_004::SetActionManifestPath(const char* pchActionManifestPath) { return base->SetActionManifestPath(pchActionManifestPath); }
vr::EVRInputError CVRInput_004::GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return base->GetActionSetHandle(pchActionSetName, pHandle); }
vr::EVRInputError CVRInput_004::GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return base->GetActionHandle(pchActionName, pHandle); }
vr::EVRInputError CVRInput_004::GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return base->GetInputSourceHandle(pchInputSourcePath, pHandle); }
vr::EVRInputError CVRInput_004::UpdateActionState(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return base->UpdateActionState((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
vr::EVRInputError CVRInput_004::GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetDigitalActionData(action, (vr::InputDigitalActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetAnalogActionData(action, (vr::InputAnalogActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_004::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionData(action, eOrigin, fPredictedSecondsFromNow, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetSkeletalActionData(action, (vr::InputSkeletalActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetSkeletalBoneData(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetSkeletalBoneDataCompressed(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::DecompressSkeletalBoneData(void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_004::EVRSkeletalTransformSpace* peTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, (vr::EVRSkeletalTransformSpace*) peTransformSpace, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_004::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
vr::EVRInputError CVRInput_004::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return base->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
vr::EVRInputError CVRInput_004::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize) { return base->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize); }
vr::EVRInputError CVRInput_004::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_004::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return base->GetOriginTrackedDeviceInfo(origin, (vr::InputOriginInfo_t*) pOriginInfo, unOriginInfoSize); }
vr::EVRInputError CVRInput_004::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return base->ShowActionOrigins(actionSetHandle, ulActionHandle); }
vr::EVRInputError CVRInput_004::ShowBindingsForActionSet(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return base->ShowBindingsForActionSet((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
// FnTable for CVRInput_004:
static CVRInput_004 *fntable_Input_004_instance = NULL;
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_SetActionManifestPath(const char* pchActionManifestPath) { return fntable_Input_004_instance->SetActionManifestPath(pchActionManifestPath); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return fntable_Input_004_instance->GetActionSetHandle(pchActionSetName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return fntable_Input_004_instance->GetActionHandle(pchActionName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return fntable_Input_004_instance->GetInputSourceHandle(pchInputSourcePath, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_UpdateActionState(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return fntable_Input_004_instance->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_004::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetPoseActionData(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_004::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetSkeletalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::IVRInput_004::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->GetSkeletalBoneDataCompressed(action, eTransformSpace, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_DecompressSkeletalBoneData(void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_004::EVRSkeletalTransformSpace* peTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_004_instance->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, peTransformSpace, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_004_instance->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return fntable_Input_004_instance->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize) { return fntable_Input_004_instance->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_004::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return fntable_Input_004_instance->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return fntable_Input_004_instance->ShowActionOrigins(actionSetHandle, ulActionHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_004_impl_ShowBindingsForActionSet(vr::IVRInput_004::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return fntable_Input_004_instance->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
static void *fntable_Input_004_funcs[] = {
	fntable_Input_004_impl_SetActionManifestPath,
	fntable_Input_004_impl_GetActionSetHandle,
	fntable_Input_004_impl_GetActionHandle,
	fntable_Input_004_impl_GetInputSourceHandle,
	fntable_Input_004_impl_UpdateActionState,
	fntable_Input_004_impl_GetDigitalActionData,
	fntable_Input_004_impl_GetAnalogActionData,
	fntable_Input_004_impl_GetPoseActionData,
	fntable_Input_004_impl_GetSkeletalActionData,
	fntable_Input_004_impl_GetSkeletalBoneData,
	fntable_Input_004_impl_GetSkeletalBoneDataCompressed,
	fntable_Input_004_impl_DecompressSkeletalBoneData,
	fntable_Input_004_impl_TriggerHapticVibrationAction,
	fntable_Input_004_impl_GetActionOrigins,
	fntable_Input_004_impl_GetOriginLocalizedName,
	fntable_Input_004_impl_GetOriginTrackedDeviceInfo,
	fntable_Input_004_impl_ShowActionOrigins,
	fntable_Input_004_impl_ShowBindingsForActionSet,
};
void** CVRInput_004::_GetStatFuncList() { fntable_Input_004_instance = this; return fntable_Input_004_funcs; }
// Misc for CVRInput_005:
CVRInput_005::CVRInput_005() : base(GetCreateBaseInput()) {}
// Interface methods for CVRInput_005:
vr::EVRInputError CVRInput_005::SetActionManifestPath(const char* pchActionManifestPath) { return base->SetActionManifestPath(pchActionManifestPath); }
vr::EVRInputError CVRInput_005::GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return base->GetActionSetHandle(pchActionSetName, pHandle); }
vr::EVRInputError CVRInput_005::GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return base->GetActionHandle(pchActionName, pHandle); }
vr::EVRInputError CVRInput_005::GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return base->GetInputSourceHandle(pchInputSourcePath, pHandle); }
vr::EVRInputError CVRInput_005::UpdateActionState(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return base->UpdateActionState((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
vr::EVRInputError CVRInput_005::GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetDigitalActionData(action, (vr::InputDigitalActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_005::GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetAnalogActionData(action, (vr::InputAnalogActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_005::GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_005::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionData(action, eOrigin, fPredictedSecondsFromNow, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_005::GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return base->GetSkeletalActionData(action, (vr::InputSkeletalActionData_t*) pActionData, unActionDataSize); }
vr::EVRInputError CVRInput_005::GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return base->GetBoneCount(action, pBoneCount); }
vr::EVRInputError CVRInput_005::GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return base->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
vr::EVRInputError CVRInput_005::GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return base->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
vr::EVRInputError CVRInput_005::GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_005::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalReferenceTransforms(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, (vr::EVRSkeletalReferencePose) eReferencePose, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_005::GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return base->GetSkeletalTrackingLevel(action, (vr::EVRSkeletalTrackingLevel*) pSkeletalTrackingLevel); }
vr::EVRInputError CVRInput_005::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalBoneData(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_005::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_005::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return base->GetSkeletalSummaryData(action, (vr::VRSkeletalSummaryData_t*) pSkeletalSummaryData); }
vr::EVRInputError CVRInput_005::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return base->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
vr::EVRInputError CVRInput_005::DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, (vr::EVRSkeletalTransformSpace) eTransformSpace, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_005::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
vr::EVRInputError CVRInput_005::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return base->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
vr::EVRInputError CVRInput_005::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return base->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
vr::EVRInputError CVRInput_005::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_005::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return base->GetOriginTrackedDeviceInfo(origin, (vr::InputOriginInfo_t*) pOriginInfo, unOriginInfoSize); }
vr::EVRInputError CVRInput_005::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return base->ShowActionOrigins(actionSetHandle, ulActionHandle); }
vr::EVRInputError CVRInput_005::ShowBindingsForActionSet(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return base->ShowBindingsForActionSet((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
// FnTable for CVRInput_005:
static CVRInput_005 *fntable_Input_005_instance = NULL;
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_SetActionManifestPath(const char* pchActionManifestPath) { return fntable_Input_005_instance->SetActionManifestPath(pchActionManifestPath); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return fntable_Input_005_instance->GetActionSetHandle(pchActionSetName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return fntable_Input_005_instance->GetActionHandle(pchActionName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return fntable_Input_005_instance->GetInputSourceHandle(pchInputSourcePath, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_UpdateActionState(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return fntable_Input_005_instance->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_005_instance->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_005_instance->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_005::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_005_instance->GetPoseActionData(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_005::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return fntable_Input_005_instance->GetSkeletalActionData(action, pActionData, unActionDataSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return fntable_Input_005_instance->GetBoneCount(action, pBoneCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return fntable_Input_005_instance->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return fntable_Input_005_instance->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_005::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_005_instance->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return fntable_Input_005_instance->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_005_instance->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_005::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return fntable_Input_005_instance->GetSkeletalSummaryData(action, pSkeletalSummaryData); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return fntable_Input_005_instance->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_005::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_005_instance->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, eTransformSpace, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_005_instance->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return fntable_Input_005_instance->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return fntable_Input_005_instance->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_005::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return fntable_Input_005_instance->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return fntable_Input_005_instance->ShowActionOrigins(actionSetHandle, ulActionHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_005_impl_ShowBindingsForActionSet(vr::IVRInput_005::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return fntable_Input_005_instance->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
static void *fntable_Input_005_funcs[] = {
	fntable_Input_005_impl_SetActionManifestPath,
	fntable_Input_005_impl_GetActionSetHandle,
	fntable_Input_005_impl_GetActionHandle,
	fntable_Input_005_impl_GetInputSourceHandle,
	fntable_Input_005_impl_UpdateActionState,
	fntable_Input_005_impl_GetDigitalActionData,
	fntable_Input_005_impl_GetAnalogActionData,
	fntable_Input_005_impl_GetPoseActionData,
	fntable_Input_005_impl_GetSkeletalActionData,
	fntable_Input_005_impl_GetBoneCount,
	fntable_Input_005_impl_GetBoneHierarchy,
	fntable_Input_005_impl_GetBoneName,
	fntable_Input_005_impl_GetSkeletalReferenceTransforms,
	fntable_Input_005_impl_GetSkeletalTrackingLevel,
	fntable_Input_005_impl_GetSkeletalBoneData,
	fntable_Input_005_impl_GetSkeletalSummaryData,
	fntable_Input_005_impl_GetSkeletalBoneDataCompressed,
	fntable_Input_005_impl_DecompressSkeletalBoneData,
	fntable_Input_005_impl_TriggerHapticVibrationAction,
	fntable_Input_005_impl_GetActionOrigins,
	fntable_Input_005_impl_GetOriginLocalizedName,
	fntable_Input_005_impl_GetOriginTrackedDeviceInfo,
	fntable_Input_005_impl_ShowActionOrigins,
	fntable_Input_005_impl_ShowBindingsForActionSet,
};
void** CVRInput_005::_GetStatFuncList() { fntable_Input_005_instance = this; return fntable_Input_005_funcs; }
// Misc for CVRInput_006:
CVRInput_006::CVRInput_006() : base(GetCreateBaseInput()) {}
// Interface methods for CVRInput_006:
vr::EVRInputError CVRInput_006::SetActionManifestPath(const char* pchActionManifestPath) { return base->SetActionManifestPath(pchActionManifestPath); }
vr::EVRInputError CVRInput_006::GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return base->GetActionSetHandle(pchActionSetName, pHandle); }
vr::EVRInputError CVRInput_006::GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return base->GetActionHandle(pchActionName, pHandle); }
vr::EVRInputError CVRInput_006::GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return base->GetInputSourceHandle(pchInputSourcePath, pHandle); }
vr::EVRInputError CVRInput_006::UpdateActionState(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return base->UpdateActionState((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
vr::EVRInputError CVRInput_006::GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetDigitalActionData(action, (vr::InputDigitalActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_006::GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetAnalogActionData(action, (vr::InputAnalogActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_006::GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_006::GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionDataForNextFrame(action, eOrigin, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_006::GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return base->GetSkeletalActionData(action, (vr::InputSkeletalActionData_t*) pActionData, unActionDataSize); }
vr::EVRInputError CVRInput_006::GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return base->GetBoneCount(action, pBoneCount); }
vr::EVRInputError CVRInput_006::GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return base->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
vr::EVRInputError CVRInput_006::GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return base->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
vr::EVRInputError CVRInput_006::GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_006::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalReferenceTransforms(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, (vr::EVRSkeletalReferencePose) eReferencePose, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_006::GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return base->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel); }
vr::EVRInputError CVRInput_006::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalBoneData(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_006::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSummaryType eSummaryType, vr::IVRInput_006::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return base->GetSkeletalSummaryData(action, (vr::EVRSummaryType) eSummaryType, (vr::VRSkeletalSummaryData_t*) pSkeletalSummaryData); }
vr::EVRInputError CVRInput_006::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return base->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
vr::EVRInputError CVRInput_006::DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, (vr::EVRSkeletalTransformSpace) eTransformSpace, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_006::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
vr::EVRInputError CVRInput_006::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return base->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
vr::EVRInputError CVRInput_006::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return base->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
vr::EVRInputError CVRInput_006::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_006::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return base->GetOriginTrackedDeviceInfo(origin, (vr::InputOriginInfo_t*) pOriginInfo, unOriginInfoSize); }
vr::EVRInputError CVRInput_006::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return base->ShowActionOrigins(actionSetHandle, ulActionHandle); }
vr::EVRInputError CVRInput_006::ShowBindingsForActionSet(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return base->ShowBindingsForActionSet((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
bool CVRInput_006::IsUsingLegacyInput() { return base->IsUsingLegacyInput(); }
// FnTable for CVRInput_006:
static CVRInput_006 *fntable_Input_006_instance = NULL;
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_SetActionManifestPath(const char* pchActionManifestPath) { return fntable_Input_006_instance->SetActionManifestPath(pchActionManifestPath); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return fntable_Input_006_instance->GetActionSetHandle(pchActionSetName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return fntable_Input_006_instance->GetActionHandle(pchActionName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return fntable_Input_006_instance->GetInputSourceHandle(pchInputSourcePath, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_UpdateActionState(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return fntable_Input_006_instance->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_006_instance->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_006_instance->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_006_instance->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_006::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_006_instance->GetPoseActionDataForNextFrame(action, eOrigin, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_006::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return fntable_Input_006_instance->GetSkeletalActionData(action, pActionData, unActionDataSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return fntable_Input_006_instance->GetBoneCount(action, pBoneCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return fntable_Input_006_instance->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return fntable_Input_006_instance->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_006::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_006_instance->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return fntable_Input_006_instance->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_006_instance->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_006::EVRSummaryType eSummaryType, vr::IVRInput_006::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return fntable_Input_006_instance->GetSkeletalSummaryData(action, eSummaryType, pSkeletalSummaryData); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return fntable_Input_006_instance->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_006::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_006_instance->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, eTransformSpace, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_006_instance->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return fntable_Input_006_instance->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return fntable_Input_006_instance->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_006::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return fntable_Input_006_instance->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return fntable_Input_006_instance->ShowActionOrigins(actionSetHandle, ulActionHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_ShowBindingsForActionSet(vr::IVRInput_006::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return fntable_Input_006_instance->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Input_006_impl_IsUsingLegacyInput() { return fntable_Input_006_instance->IsUsingLegacyInput(); }
static void *fntable_Input_006_funcs[] = {
	fntable_Input_006_impl_SetActionManifestPath,
	fntable_Input_006_impl_GetActionSetHandle,
	fntable_Input_006_impl_GetActionHandle,
	fntable_Input_006_impl_GetInputSourceHandle,
	fntable_Input_006_impl_UpdateActionState,
	fntable_Input_006_impl_GetDigitalActionData,
	fntable_Input_006_impl_GetAnalogActionData,
	fntable_Input_006_impl_GetPoseActionDataRelativeToNow,
	fntable_Input_006_impl_GetPoseActionDataForNextFrame,
	fntable_Input_006_impl_GetSkeletalActionData,
	fntable_Input_006_impl_GetBoneCount,
	fntable_Input_006_impl_GetBoneHierarchy,
	fntable_Input_006_impl_GetBoneName,
	fntable_Input_006_impl_GetSkeletalReferenceTransforms,
	fntable_Input_006_impl_GetSkeletalTrackingLevel,
	fntable_Input_006_impl_GetSkeletalBoneData,
	fntable_Input_006_impl_GetSkeletalSummaryData,
	fntable_Input_006_impl_GetSkeletalBoneDataCompressed,
	fntable_Input_006_impl_DecompressSkeletalBoneData,
	fntable_Input_006_impl_TriggerHapticVibrationAction,
	fntable_Input_006_impl_GetActionOrigins,
	fntable_Input_006_impl_GetOriginLocalizedName,
	fntable_Input_006_impl_GetOriginTrackedDeviceInfo,
	fntable_Input_006_impl_ShowActionOrigins,
	fntable_Input_006_impl_ShowBindingsForActionSet,
	fntable_Input_006_impl_IsUsingLegacyInput,
};
void** CVRInput_006::_GetStatFuncList() { fntable_Input_006_instance = this; return fntable_Input_006_funcs; }
// Misc for CVRInput_007:
CVRInput_007::CVRInput_007() : base(GetCreateBaseInput()) {}
// Interface methods for CVRInput_007:
vr::EVRInputError CVRInput_007::SetActionManifestPath(const char* pchActionManifestPath) { return base->SetActionManifestPath(pchActionManifestPath); }
vr::EVRInputError CVRInput_007::GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return base->GetActionSetHandle(pchActionSetName, pHandle); }
vr::EVRInputError CVRInput_007::GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return base->GetActionHandle(pchActionName, pHandle); }
vr::EVRInputError CVRInput_007::GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return base->GetInputSourceHandle(pchInputSourcePath, pHandle); }
vr::EVRInputError CVRInput_007::UpdateActionState(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return base->UpdateActionState((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
vr::EVRInputError CVRInput_007::GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetDigitalActionData(action, (vr::InputDigitalActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_007::GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetAnalogActionData(action, (vr::InputAnalogActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_007::GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_007::GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->GetPoseActionDataForNextFrame(action, eOrigin, (vr::InputPoseActionData_t*) pActionData, unActionDataSize, ulRestrictToDevice); }
vr::EVRInputError CVRInput_007::GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return base->GetSkeletalActionData(action, (vr::InputSkeletalActionData_t*) pActionData, unActionDataSize); }
vr::EVRInputError CVRInput_007::GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return base->GetBoneCount(action, pBoneCount); }
vr::EVRInputError CVRInput_007::GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return base->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
vr::EVRInputError CVRInput_007::GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return base->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
vr::EVRInputError CVRInput_007::GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_007::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalReferenceTransforms(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, (vr::EVRSkeletalReferencePose) eReferencePose, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_007::GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return base->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel); }
vr::EVRInputError CVRInput_007::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->GetSkeletalBoneData(action, (vr::EVRSkeletalTransformSpace) eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_007::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSummaryType eSummaryType, vr::IVRInput_007::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return base->GetSkeletalSummaryData(action, (vr::EVRSummaryType) eSummaryType, (vr::VRSkeletalSummaryData_t*) pSkeletalSummaryData); }
vr::EVRInputError CVRInput_007::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return base->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
vr::EVRInputError CVRInput_007::DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return base->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, (vr::EVRSkeletalTransformSpace) eTransformSpace, pTransformArray, unTransformArrayCount); }
vr::EVRInputError CVRInput_007::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return base->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
vr::EVRInputError CVRInput_007::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return base->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
vr::EVRInputError CVRInput_007::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return base->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
vr::EVRInputError CVRInput_007::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_007::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return base->GetOriginTrackedDeviceInfo(origin, (vr::InputOriginInfo_t*) pOriginInfo, unOriginInfoSize); }
vr::EVRInputError CVRInput_007::GetActionBindingInfo(vr::VRActionHandle_t action, vr::IVRInput_007::InputBindingInfo_t* pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t* punReturnedBindingInfoCount) { return base->GetActionBindingInfo(action, (vr::InputBindingInfo_t*) pOriginInfo, unBindingInfoSize, unBindingInfoCount, punReturnedBindingInfoCount); }
vr::EVRInputError CVRInput_007::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return base->ShowActionOrigins(actionSetHandle, ulActionHandle); }
vr::EVRInputError CVRInput_007::ShowBindingsForActionSet(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return base->ShowBindingsForActionSet((vr::VRActiveActionSet_t*) pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
bool CVRInput_007::IsUsingLegacyInput() { return base->IsUsingLegacyInput(); }
// FnTable for CVRInput_007:
static CVRInput_007 *fntable_Input_007_instance = NULL;
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_SetActionManifestPath(const char* pchActionManifestPath) { return fntable_Input_007_instance->SetActionManifestPath(pchActionManifestPath); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetActionSetHandle(const char* pchActionSetName, vr::VRActionSetHandle_t* pHandle) { return fntable_Input_007_instance->GetActionSetHandle(pchActionSetName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetActionHandle(const char* pchActionName, vr::VRActionHandle_t* pHandle) { return fntable_Input_007_instance->GetActionHandle(pchActionName, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetInputSourceHandle(const char* pchInputSourcePath, vr::VRInputValueHandle_t* pHandle) { return fntable_Input_007_instance->GetInputSourceHandle(pchInputSourcePath, pHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_UpdateActionState(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) { return fntable_Input_007_instance->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetDigitalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_007_instance->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetAnalogActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_007_instance->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_007_instance->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::IVRInput_007::InputPoseActionData_t* pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_007_instance->GetPoseActionDataForNextFrame(action, eOrigin, pActionData, unActionDataSize, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalActionData(vr::VRActionHandle_t action, vr::IVRInput_007::InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize) { return fntable_Input_007_instance->GetSkeletalActionData(action, pActionData, unActionDataSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) { return fntable_Input_007_instance->GetBoneCount(action, pBoneCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetBoneHierarchy(vr::VRActionHandle_t action, vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) { return fntable_Input_007_instance->GetBoneHierarchy(action, pParentIndices, unIndexArayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, char* pchBoneName, uint32_t unNameBufferSize) { return fntable_Input_007_instance->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::IVRInput_007::EVRSkeletalReferencePose eReferencePose, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_007_instance->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) { return fntable_Input_007_instance->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalBoneData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_007_instance->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::IVRInput_007::EVRSummaryType eSummaryType, vr::IVRInput_007::VRSkeletalSummaryData_t* pSkeletalSummaryData) { return fntable_Input_007_instance->GetSkeletalSummaryData(action, eSummaryType, pSkeletalSummaryData); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize) { return fntable_Input_007_instance->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_DecompressSkeletalBoneData(const void* pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::IVRInput_007::EVRSkeletalTransformSpace eTransformSpace, vr::VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) { return fntable_Input_007_instance->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, eTransformSpace, pTransformArray, unTransformArrayCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) { return fntable_Input_007_instance->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, vr::VRInputValueHandle_t* originsOut, uint32_t originOutCount) { return fntable_Input_007_instance->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetOriginLocalizedName(vr::VRInputValueHandle_t origin, char* pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) { return fntable_Input_007_instance->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::IVRInput_007::InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) { return fntable_Input_007_instance->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_GetActionBindingInfo(vr::VRActionHandle_t action, vr::IVRInput_007::InputBindingInfo_t* pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t* punReturnedBindingInfoCount) { return fntable_Input_007_instance->GetActionBindingInfo(action, pOriginInfo, unBindingInfoSize, unBindingInfoCount, punReturnedBindingInfoCount); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) { return fntable_Input_007_instance->ShowActionOrigins(actionSetHandle, ulActionHandle); }
static vr::EVRInputError OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_ShowBindingsForActionSet(vr::IVRInput_007::VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) { return fntable_Input_007_instance->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_Input_007_impl_IsUsingLegacyInput() { return fntable_Input_007_instance->IsUsingLegacyInput(); }
static void *fntable_Input_007_funcs[] = {
	fntable_Input_007_impl_SetActionManifestPath,
	fntable_Input_007_impl_GetActionSetHandle,
	fntable_Input_007_impl_GetActionHandle,
	fntable_Input_007_impl_GetInputSourceHandle,
	fntable_Input_007_impl_UpdateActionState,
	fntable_Input_007_impl_GetDigitalActionData,
	fntable_Input_007_impl_GetAnalogActionData,
	fntable_Input_007_impl_GetPoseActionDataRelativeToNow,
	fntable_Input_007_impl_GetPoseActionDataForNextFrame,
	fntable_Input_007_impl_GetSkeletalActionData,
	fntable_Input_007_impl_GetBoneCount,
	fntable_Input_007_impl_GetBoneHierarchy,
	fntable_Input_007_impl_GetBoneName,
	fntable_Input_007_impl_GetSkeletalReferenceTransforms,
	fntable_Input_007_impl_GetSkeletalTrackingLevel,
	fntable_Input_007_impl_GetSkeletalBoneData,
	fntable_Input_007_impl_GetSkeletalSummaryData,
	fntable_Input_007_impl_GetSkeletalBoneDataCompressed,
	fntable_Input_007_impl_DecompressSkeletalBoneData,
	fntable_Input_007_impl_TriggerHapticVibrationAction,
	fntable_Input_007_impl_GetActionOrigins,
	fntable_Input_007_impl_GetOriginLocalizedName,
	fntable_Input_007_impl_GetOriginTrackedDeviceInfo,
	fntable_Input_007_impl_GetActionBindingInfo,
	fntable_Input_007_impl_ShowActionOrigins,
	fntable_Input_007_impl_ShowBindingsForActionSet,
	fntable_Input_007_impl_IsUsingLegacyInput,
};
void** CVRInput_007::_GetStatFuncList() { fntable_Input_007_instance = this; return fntable_Input_007_funcs; }
#include "GVRClientCore.gen.h"
// Single inst of BaseClientCore
static std::weak_ptr<BaseClientCore> _single_inst_ClientCore;
static BaseClientCore *_single_inst_ClientCore_unsafe = NULL;
std::shared_ptr<BaseClientCore> GetBaseClientCore() { return _single_inst_ClientCore.lock(); };
BaseClientCore* GetUnsafeBaseClientCore() { return _single_inst_ClientCore_unsafe; };
std::shared_ptr<BaseClientCore> GetCreateBaseClientCore() {
	std::shared_ptr<BaseClientCore> ret = _single_inst_ClientCore.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseClientCore>(new BaseClientCore(), [](BaseClientCore *obj){ _single_inst_ClientCore_unsafe = NULL; delete obj; });
		_single_inst_ClientCore = ret;
		_single_inst_ClientCore_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRClientCore_003:
CVRClientCore_003::CVRClientCore_003() : base(GetCreateBaseClientCore()) {}
// Interface methods for CVRClientCore_003:
vr::EVRInitError CVRClientCore_003::Init(vr::EVRApplicationType eApplicationType, const char* pStartupInfo) { return base->Init(eApplicationType, pStartupInfo); }
void CVRClientCore_003::Cleanup() { return base->Cleanup(); }
vr::EVRInitError CVRClientCore_003::IsInterfaceVersionValid(const char* pchInterfaceVersion) { return base->IsInterfaceVersionValid(pchInterfaceVersion); }
void* CVRClientCore_003::GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) { return base->GetGenericInterface(pchNameAndVersion, peError); }
bool CVRClientCore_003::BIsHmdPresent() { return base->BIsHmdPresent(); }
const char* CVRClientCore_003::GetEnglishStringForHmdError(vr::EVRInitError eError) { return base->GetEnglishStringForHmdError(eError); }
const char* CVRClientCore_003::GetIDForVRInitError(vr::EVRInitError eError) { return base->GetIDForVRInitError(eError); }
// FnTable for CVRClientCore_003:
static CVRClientCore_003 *fntable_ClientCore_003_instance = NULL;
static vr::EVRInitError OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_Init(vr::EVRApplicationType eApplicationType, const char* pStartupInfo) { return fntable_ClientCore_003_instance->Init(eApplicationType, pStartupInfo); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_Cleanup() { return fntable_ClientCore_003_instance->Cleanup(); }
static vr::EVRInitError OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_IsInterfaceVersionValid(const char* pchInterfaceVersion) { return fntable_ClientCore_003_instance->IsInterfaceVersionValid(pchInterfaceVersion); }
static void* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) { return fntable_ClientCore_003_instance->GetGenericInterface(pchNameAndVersion, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_BIsHmdPresent() { return fntable_ClientCore_003_instance->BIsHmdPresent(); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_GetEnglishStringForHmdError(vr::EVRInitError eError) { return fntable_ClientCore_003_instance->GetEnglishStringForHmdError(eError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_003_impl_GetIDForVRInitError(vr::EVRInitError eError) { return fntable_ClientCore_003_instance->GetIDForVRInitError(eError); }
static void *fntable_ClientCore_003_funcs[] = {
	fntable_ClientCore_003_impl_Init,
	fntable_ClientCore_003_impl_Cleanup,
	fntable_ClientCore_003_impl_IsInterfaceVersionValid,
	fntable_ClientCore_003_impl_GetGenericInterface,
	fntable_ClientCore_003_impl_BIsHmdPresent,
	fntable_ClientCore_003_impl_GetEnglishStringForHmdError,
	fntable_ClientCore_003_impl_GetIDForVRInitError,
};
void** CVRClientCore_003::_GetStatFuncList() { fntable_ClientCore_003_instance = this; return fntable_ClientCore_003_funcs; }
// Misc for CVRClientCore_002:
CVRClientCore_002::CVRClientCore_002() : base(GetCreateBaseClientCore()) {}
// Interface methods for CVRClientCore_002:
void CVRClientCore_002::Cleanup() { return base->Cleanup(); }
vr::EVRInitError CVRClientCore_002::IsInterfaceVersionValid(const char* pchInterfaceVersion) { return base->IsInterfaceVersionValid(pchInterfaceVersion); }
void* CVRClientCore_002::GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) { return base->GetGenericInterface(pchNameAndVersion, peError); }
bool CVRClientCore_002::BIsHmdPresent() { return base->BIsHmdPresent(); }
const char* CVRClientCore_002::GetEnglishStringForHmdError(vr::EVRInitError eError) { return base->GetEnglishStringForHmdError(eError); }
const char* CVRClientCore_002::GetIDForVRInitError(vr::EVRInitError eError) { return base->GetIDForVRInitError(eError); }
// FnTable for CVRClientCore_002:
static CVRClientCore_002 *fntable_ClientCore_002_instance = NULL;
static vr::EVRInitError OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_Init(vr::EVRApplicationType eApplicationType) { return fntable_ClientCore_002_instance->Init(eApplicationType); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_Cleanup() { return fntable_ClientCore_002_instance->Cleanup(); }
static vr::EVRInitError OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_IsInterfaceVersionValid(const char* pchInterfaceVersion) { return fntable_ClientCore_002_instance->IsInterfaceVersionValid(pchInterfaceVersion); }
static void* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError) { return fntable_ClientCore_002_instance->GetGenericInterface(pchNameAndVersion, peError); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_BIsHmdPresent() { return fntable_ClientCore_002_instance->BIsHmdPresent(); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_GetEnglishStringForHmdError(vr::EVRInitError eError) { return fntable_ClientCore_002_instance->GetEnglishStringForHmdError(eError); }
static const char* OPENVR_FNTABLE_CALLTYPE fntable_ClientCore_002_impl_GetIDForVRInitError(vr::EVRInitError eError) { return fntable_ClientCore_002_instance->GetIDForVRInitError(eError); }
static void *fntable_ClientCore_002_funcs[] = {
	fntable_ClientCore_002_impl_Init,
	fntable_ClientCore_002_impl_Cleanup,
	fntable_ClientCore_002_impl_IsInterfaceVersionValid,
	fntable_ClientCore_002_impl_GetGenericInterface,
	fntable_ClientCore_002_impl_BIsHmdPresent,
	fntable_ClientCore_002_impl_GetEnglishStringForHmdError,
	fntable_ClientCore_002_impl_GetIDForVRInitError,
};
void** CVRClientCore_002::_GetStatFuncList() { fntable_ClientCore_002_instance = this; return fntable_ClientCore_002_funcs; }
/* #include "GVROCSystem.gen.h"
// Single inst of OCBaseSystem
static std::weak_ptr<OCBaseSystem> _single_inst_OCSystem;
static OCBaseSystem *_single_inst_OCSystem_unsafe = NULL;
std::shared_ptr<OCBaseSystem> GetBaseOCSystem() { return _single_inst_OCSystem.lock(); };
OCBaseSystem* GetUnsafeBaseOCSystem() { return _single_inst_OCSystem_unsafe; };
std::shared_ptr<OCBaseSystem> GetCreateBaseOCSystem() {
	std::shared_ptr<OCBaseSystem> ret = _single_inst_OCSystem.lock();
	if(!ret) {
		ret = std::shared_ptr<OCBaseSystem>(new OCBaseSystem(), [](OCBaseSystem *obj){ _single_inst_OCSystem_unsafe = NULL; delete obj; });
		_single_inst_OCSystem = ret;
		_single_inst_OCSystem_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVROCSystem_001:
CVROCSystem_001::CVROCSystem_001() : base(GetCreateBaseOCSystem()) {}
// Interface methods for CVROCSystem_001:
uint64_t CVROCSystem_001::GetExtendedButtonStatus() { return base->GetExtendedButtonStatus(); }
// FnTable for CVROCSystem_001:
static CVROCSystem_001 *fntable_OCSystem_001_instance = NULL;
static uint64_t OPENVR_FNTABLE_CALLTYPE fntable_OCSystem_001_impl_GetExtendedButtonStatus() { return fntable_OCSystem_001_instance->GetExtendedButtonStatus(); }
static void *fntable_OCSystem_001_funcs[] = {
	fntable_OCSystem_001_impl_GetExtendedButtonStatus,
};
void** CVROCSystem_001::_GetStatFuncList() { fntable_OCSystem_001_instance = this; return fntable_OCSystem_001_funcs; } */
/* #include "GVRServerDriverHost.gen.h"
// Single inst of BaseServerDriverHost
static std::weak_ptr<BaseServerDriverHost> _single_inst_ServerDriverHost;
static BaseServerDriverHost *_single_inst_ServerDriverHost_unsafe = NULL;
std::shared_ptr<BaseServerDriverHost> GetBaseServerDriverHost() { return _single_inst_ServerDriverHost.lock(); };
BaseServerDriverHost* GetUnsafeBaseServerDriverHost() { return _single_inst_ServerDriverHost_unsafe; };
std::shared_ptr<BaseServerDriverHost> GetCreateBaseServerDriverHost() {
	std::shared_ptr<BaseServerDriverHost> ret = _single_inst_ServerDriverHost.lock();
	if(!ret) {
		ret = std::shared_ptr<BaseServerDriverHost>(new BaseServerDriverHost(), [](BaseServerDriverHost *obj){ _single_inst_ServerDriverHost_unsafe = NULL; delete obj; });
		_single_inst_ServerDriverHost = ret;
		_single_inst_ServerDriverHost_unsafe = ret.get();
	}
	return ret;
}
// Misc for CVRServerDriverHost_005:
CVRServerDriverHost_005::CVRServerDriverHost_005() : base(GetCreateBaseServerDriverHost()) {}
// Interface methods for CVRServerDriverHost_005:
void CVRServerDriverHost_005::VsyncEvent(double vsyncTimeOffsetSeconds) { return base->VsyncEvent(vsyncTimeOffsetSeconds); }
void CVRServerDriverHost_005::VendorSpecificEvent(uint32_t unWhichDevice, vr::EVREventType eventType, const vr::VREvent_Data_t& eventData, double eventTimeOffset) { return base->VendorSpecificEvent(unWhichDevice, eventType, eventData, eventTimeOffset); }
bool CVRServerDriverHost_005::IsExiting() { return base->IsExiting(); }
bool CVRServerDriverHost_005::PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return base->PollNextEvent(pEvent, uncbVREvent); }
void CVRServerDriverHost_005::GetRawTrackedDevicePoses(float fPredictedSecondsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return base->GetRawTrackedDevicePoses(fPredictedSecondsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
void CVRServerDriverHost_005::TrackedDeviceDisplayTransformUpdated(uint32_t unWhichDevice, vr::HmdMatrix34_t eyeToHeadLeft, vr::HmdMatrix34_t eyeToHeadRight) { return base->TrackedDeviceDisplayTransformUpdated(unWhichDevice, eyeToHeadLeft, eyeToHeadRight); }
// FnTable for CVRServerDriverHost_005:
static CVRServerDriverHost_005 *fntable_ServerDriverHost_005_instance = NULL;
static bool OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_TrackedDeviceAdded(const char* pchDeviceSerialNumber, vr::ETrackedDeviceClass eDeviceClass, vr::driver_ITrackedDeviceServerDriver_005::ITrackedDeviceServerDriver* pDriver) { return fntable_ServerDriverHost_005_instance->TrackedDeviceAdded(pchDeviceSerialNumber, eDeviceClass, pDriver); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_TrackedDevicePoseUpdated(uint32_t unWhichDevice, const vr::driver_ITrackedDeviceServerDriver_005::DriverPose_t& newPose, uint32_t unPoseStructSize) { return fntable_ServerDriverHost_005_instance->TrackedDevicePoseUpdated(unWhichDevice, newPose, unPoseStructSize); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_VsyncEvent(double vsyncTimeOffsetSeconds) { return fntable_ServerDriverHost_005_instance->VsyncEvent(vsyncTimeOffsetSeconds); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_VendorSpecificEvent(uint32_t unWhichDevice, vr::EVREventType eventType, const vr::VREvent_Data_t& eventData, double eventTimeOffset) { return fntable_ServerDriverHost_005_instance->VendorSpecificEvent(unWhichDevice, eventType, eventData, eventTimeOffset); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_IsExiting() { return fntable_ServerDriverHost_005_instance->IsExiting(); }
static bool OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent) { return fntable_ServerDriverHost_005_instance->PollNextEvent(pEvent, uncbVREvent); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_GetRawTrackedDevicePoses(float fPredictedSecondsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) { return fntable_ServerDriverHost_005_instance->GetRawTrackedDevicePoses(fPredictedSecondsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }
static void OPENVR_FNTABLE_CALLTYPE fntable_ServerDriverHost_005_impl_TrackedDeviceDisplayTransformUpdated(uint32_t unWhichDevice, vr::HmdMatrix34_t eyeToHeadLeft, vr::HmdMatrix34_t eyeToHeadRight) { return fntable_ServerDriverHost_005_instance->TrackedDeviceDisplayTransformUpdated(unWhichDevice, eyeToHeadLeft, eyeToHeadRight); }
static void *fntable_ServerDriverHost_005_funcs[] = {
	fntable_ServerDriverHost_005_impl_TrackedDeviceAdded,
	fntable_ServerDriverHost_005_impl_TrackedDevicePoseUpdated,
	fntable_ServerDriverHost_005_impl_VsyncEvent,
	fntable_ServerDriverHost_005_impl_VendorSpecificEvent,
	fntable_ServerDriverHost_005_impl_IsExiting,
	fntable_ServerDriverHost_005_impl_PollNextEvent,
	fntable_ServerDriverHost_005_impl_GetRawTrackedDevicePoses,
	fntable_ServerDriverHost_005_impl_TrackedDeviceDisplayTransformUpdated,
};
void** CVRServerDriverHost_005::_GetStatFuncList() { fntable_ServerDriverHost_005_instance = this; return fntable_ServerDriverHost_005_funcs; } */

class _InheritCVRLayout { virtual void _ignore() = 0; };
class CVRCorrectLayout : public _InheritCVRLayout, public CVRCommon {};

// Get interface by name
void *CreateInterfaceByName(const char *name) {
  getOut() << "create interface 0 " << name << std::endl;
  
  const char *fnTableStr = "FnTable:";
  if (!strncmp(fnTableStr, name, strlen(fnTableStr))) {
    const char *baseInterface = name + strlen(fnTableStr);
    
    getOut() << "create function table 0 " << baseInterface << std::endl;

    // Get the C++ interface
    // Note we can't directly cast to CVRCommon, as we'll then be referring to the OpenVR interface
    // vtable - look up how vtables work with multiple inheritance if you're confused about this.
    CVRCorrectLayout *interfaceClass = (CVRCorrectLayout*) CreateInterfaceByName(baseInterface);
    
    getOut() << "create function table 1 " << baseInterface << " " << interfaceClass << std::endl;

    // If the interface is NULL, then error will have been set and we can return null too.
    if (!interfaceClass) {
      return nullptr;
    }

    return interfaceClass->_GetStatFuncList();
  }
  
  getOut() << "create interface 1 " << name << std::endl;
  
	if(strcmp(vr::IVRCompositor_012::IVRCompositor_Version, name) == 0) return new CVRCompositor_012();
	if(strcmp(vr::IVRCompositor_013::IVRCompositor_Version, name) == 0) return new CVRCompositor_013();
	if(strcmp(vr::IVRCompositor_014::IVRCompositor_Version, name) == 0) return new CVRCompositor_014();
	if(strcmp(vr::IVRCompositor_015::IVRCompositor_Version, name) == 0) return new CVRCompositor_015();
	if(strcmp(vr::IVRCompositor_016::IVRCompositor_Version, name) == 0) return new CVRCompositor_016();
	if(strcmp(vr::IVRCompositor_017::IVRCompositor_Version, name) == 0) return new CVRCompositor_017();
	if(strcmp(vr::IVRCompositor_018::IVRCompositor_Version, name) == 0) return new CVRCompositor_018();
	if(strcmp(vr::IVRCompositor_019::IVRCompositor_Version, name) == 0) return new CVRCompositor_019();
	if(strcmp(vr::IVRCompositor_020::IVRCompositor_Version, name) == 0) return new CVRCompositor_020();
	if(strcmp(vr::IVRCompositor_021::IVRCompositor_Version, name) == 0) return new CVRCompositor_021();
	if(strcmp(vr::IVRCompositor_022::IVRCompositor_Version, name) == 0) return new CVRCompositor_022();
	if(strcmp(vr::IVRSystem_011::IVRSystem_Version, name) == 0) return new CVRSystem_011();
	if(strcmp(vr::IVRSystem_012::IVRSystem_Version, name) == 0) return new CVRSystem_012();
	if(strcmp(vr::IVRSystem_014::IVRSystem_Version, name) == 0) return new CVRSystem_014();
	if(strcmp(vr::IVRSystem_015::IVRSystem_Version, name) == 0) return new CVRSystem_015();
	if(strcmp(vr::IVRSystem_016::IVRSystem_Version, name) == 0) return new CVRSystem_016();
	if(strcmp(vr::IVRSystem_017::IVRSystem_Version, name) == 0) return new CVRSystem_017();
	if(strcmp(vr::IVRSystem_019::IVRSystem_Version, name) == 0) return new CVRSystem_019();
	if(strcmp(vr::IVRSystem_020::IVRSystem_Version, name) == 0) return new CVRSystem_020();
	if(strcmp(vr::IVRChaperone_003::IVRChaperone_Version, name) == 0) return new CVRChaperone_003();
	if(strcmp(vr::IVROverlay_010::IVROverlay_Version, name) == 0) return new CVROverlay_010();
	if(strcmp(vr::IVROverlay_011::IVROverlay_Version, name) == 0) return new CVROverlay_011();
	if(strcmp(vr::IVROverlay_013::IVROverlay_Version, name) == 0) return new CVROverlay_013();
	if(strcmp(vr::IVROverlay_014::IVROverlay_Version, name) == 0) return new CVROverlay_014();
	if(strcmp(vr::IVROverlay_016::IVROverlay_Version, name) == 0) return new CVROverlay_016();
	if(strcmp(vr::IVROverlay_017::IVROverlay_Version, name) == 0) return new CVROverlay_017();
	if(strcmp(vr::IVROverlay_018::IVROverlay_Version, name) == 0) return new CVROverlay_018();
	if(strcmp(vr::IVROverlay_019::IVROverlay_Version, name) == 0) return new CVROverlay_019();
	if(strcmp(vr::IVRChaperoneSetup_005::IVRChaperoneSetup_Version, name) == 0) return new CVRChaperoneSetup_005();
	if(strcmp(vr::IVRChaperoneSetup_006::IVRChaperoneSetup_Version, name) == 0) return new CVRChaperoneSetup_006();
	if(strcmp(vr::IVRRenderModels_004::IVRRenderModels_Version, name) == 0) return new CVRRenderModels_004();
	if(strcmp(vr::IVRRenderModels_005::IVRRenderModels_Version, name) == 0) return new CVRRenderModels_005();
	if(strcmp(vr::IVRRenderModels_006::IVRRenderModels_Version, name) == 0) return new CVRRenderModels_006();
	if(strcmp(vr::IVRScreenshots_001::IVRScreenshots_Version, name) == 0) return new CVRScreenshots_001();
	if(strcmp(vr::IVRSettings_001::IVRSettings_Version, name) == 0) return new CVRSettings_001();
	if(strcmp(vr::IVRSettings_002::IVRSettings_Version, name) == 0) return new CVRSettings_002();
	if(strcmp(vr::IVRExtendedDisplay_001::IVRExtendedDisplay_Version, name) == 0) return new CVRExtendedDisplay_001();
	if(strcmp(vr::IVRApplications_004::IVRApplications_Version, name) == 0) return new CVRApplications_004();
	if(strcmp(vr::IVRApplications_005::IVRApplications_Version, name) == 0) return new CVRApplications_005();
	if(strcmp(vr::IVRApplications_006::IVRApplications_Version, name) == 0) return new CVRApplications_006();
	if(strcmp(vr::IVRInput_004::IVRInput_Version, name) == 0) return new CVRInput_004();
	if(strcmp(vr::IVRInput_005::IVRInput_Version, name) == 0) return new CVRInput_005();
	if(strcmp(vr::IVRInput_006::IVRInput_Version, name) == 0) return new CVRInput_006();
	if(strcmp(vr::IVRInput_007::IVRInput_Version, name) == 0) return new CVRInput_007();
	if(strcmp(vr::IVRClientCore_003::IVRClientCore_Version, name) == 0) return new CVRClientCore_003();
	if(strcmp(vr::IVRClientCore_002::IVRClientCore_Version, name) == 0) return new CVRClientCore_002();
	// if(strcmp(ocapi::IVROCSystem_001::IVROCSystem_Version, name) == 0) return new CVROCSystem_001();
	// if(strcmp(vr::driver_IVRServerDriverHost_005::IVRServerDriverHost_Version, name) == 0) return new CVRServerDriverHost_005();
  getOut() << "create interface 2 " << name << std::endl;
	return nullptr;
}
// Get flags by name
uint64_t GetInterfaceFlagsByName(const char *name, const char *flag, bool *success) {
	if(success) *success = true;
	if(strcmp(vr::IVRApplications_004::IVRApplications_Version, name) == 0) {
		if(strcmp("APPTYPE", flag) == 0) return (~(1ull << VRApplication_Bootstrapper));
	}
	if(strcmp(vr::IVRApplications_005::IVRApplications_Version, name) == 0) {
		if(strcmp("APPTYPE", flag) == 0) return (~(1ull << VRApplication_Bootstrapper));
	}
	if(strcmp(vr::IVRApplications_006::IVRApplications_Version, name) == 0) {
		if(strcmp("APPTYPE", flag) == 0) return (~(1ull << VRApplication_Bootstrapper));
	}
	if(success) *success = false;
	return 0;
}
