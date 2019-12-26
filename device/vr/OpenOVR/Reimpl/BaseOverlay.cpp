#include "stdafx.h"
#define BASE_IMPL
#include "BaseOverlay.h"
#include "BaseSystem.h"
// #include "OVR_CAPI.h"
#include <string>
// #include "Compositor/compositor.h"
// #include "libovr_wrapper.h"
// #include "convert.h"
#include "BaseCompositor.h"
#include "static_bases.gen.h"
// #include "Misc/Config.h"
#include "Misc/ScopeGuard.h"

using namespace std;
// using Vec3 = OVR::Vector3f;
// using Mat4 = OVR::Matrix4f;

EVROverlayError BaseOverlay::FindOverlay(const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle) {
	return g_vroverlay->FindOverlay(pchOverlayKey, pOverlayHandle);
}
EVROverlayError BaseOverlay::CreateOverlay(const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle) {
	return g_vroverlay->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle);
}
EVROverlayError BaseOverlay::DestroyOverlay(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->DestroyOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetHighQualityOverlay(VROverlayHandle_t ulOverlayHandle) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->SetHighQualityOverlay(ulOverlayHandle);
}
VROverlayHandle_t BaseOverlay::GetHighQualityOverlay() {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->GetHighQualityOverlay();
}
uint32_t BaseOverlay::GetOverlayKey(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
	return g_vroverlay->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
}
uint32_t BaseOverlay::GetOverlayName(VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
	return g_vroverlay->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
}
EVROverlayError BaseOverlay::SetOverlayName(VROverlayHandle_t ulOverlayHandle, const char *pchName) {
	return g_vroverlay->SetOverlayName(ulOverlayHandle, pchName);
}
EVROverlayError BaseOverlay::GetOverlayImageData(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight) {
	return g_vroverlay->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
}
const char * BaseOverlay::GetOverlayErrorNameFromEnum(EVROverlayError error) {
  return g_vroverlay->GetOverlayErrorNameFromEnum(error);
}
EVROverlayError BaseOverlay::SetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle, uint32_t unPID) {
	return g_vroverlay->SetOverlayRenderingPid(ulOverlayHandle, unPID);
}
uint32_t BaseOverlay::GetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->GetOverlayRenderingPid(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) {
	return g_vroverlay->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
}
EVROverlayError BaseOverlay::GetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled) {
	return g_vroverlay->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
}
EVROverlayError BaseOverlay::SetOverlayColor(VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) {
	return g_vroverlay->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
}
EVROverlayError BaseOverlay::GetOverlayColor(VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue) {
  return g_vroverlay->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
}
EVROverlayError BaseOverlay::SetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float fAlpha) {
	return g_vroverlay->SetOverlayAlpha(ulOverlayHandle, fAlpha);
}
EVROverlayError BaseOverlay::GetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float *pfAlpha) {
	return g_vroverlay->GetOverlayAlpha(ulOverlayHandle, pfAlpha);
}
EVROverlayError BaseOverlay::SetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float fTexelAspect) {
	return g_vroverlay->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
}
EVROverlayError BaseOverlay::GetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect) {
	return g_vroverlay->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect);
}
EVROverlayError BaseOverlay::SetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) {
	return g_vroverlay->SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
}
EVROverlayError BaseOverlay::GetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder) {
	return g_vroverlay->GetOverlaySortOrder(ulOverlayHandle, punSortOrder);
}
EVROverlayError BaseOverlay::SetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
	return g_vroverlay->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
}
EVROverlayError BaseOverlay::GetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters) {
	return g_vroverlay->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
}
EVROverlayError BaseOverlay::SetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
}
EVROverlayError BaseOverlay::GetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
}
EVROverlayError BaseOverlay::SetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {
	return g_vroverlay->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
}
EVROverlayError BaseOverlay::GetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace) {
	return g_vroverlay->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
}
EVROverlayError BaseOverlay::SetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds) {
	return g_vroverlay->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}
EVROverlayError BaseOverlay::GetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds) {
	return g_vroverlay->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}
uint32_t BaseOverlay::GetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, EVROverlayError *pError) {
	return g_vroverlay->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError);
}
EVROverlayError BaseOverlay::SetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor) {
	return g_vroverlay->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor);
}
EVROverlayError BaseOverlay::GetOverlayTransformType(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType) {
	return g_vroverlay->GetOverlayTransformType(ulOverlayHandle, peTransformType);
}
EVROverlayError BaseOverlay::SetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
	return g_vroverlay->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}
EVROverlayError BaseOverlay::GetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
	return g_vroverlay->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
	return g_vroverlay->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}
EVROverlayError BaseOverlay::GetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
	return g_vroverlay->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName) {
	return g_vroverlay->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
}
EVROverlayError BaseOverlay::GetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize) {
	return g_vroverlay->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
}
EVROverlayError BaseOverlay::GetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
	return g_vroverlay->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
	return g_vroverlay->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
}
EVROverlayError BaseOverlay::ShowOverlay(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->ShowOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::HideOverlay(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->HideOverlay(ulOverlayHandle);
}
bool BaseOverlay::IsOverlayVisible(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->IsOverlayVisible(ulOverlayHandle);
}
EVROverlayError BaseOverlay::GetTransformForOverlayCoordinates(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform) {
	return g_vroverlay->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
}
bool BaseOverlay::PollNextOverlayEvent(VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t eventSize) {
	return g_vroverlay->PollNextOverlayEvent(ulOverlayHandle, pEvent, eventSize);
}
EVROverlayError BaseOverlay::GetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod) {
	return g_vroverlay->GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
}

EVROverlayError BaseOverlay::SetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod) {
	return g_vroverlay->SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
}
EVROverlayError BaseOverlay::GetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale) {
	return g_vroverlay->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}
EVROverlayError BaseOverlay::SetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale) {
	return g_vroverlay->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}
bool BaseOverlay::ComputeOverlayIntersection(VROverlayHandle_t ulOverlayHandle, const vr::VROverlayIntersectionParams_t *pParams, vr::VROverlayIntersectionResults_t *pResults) {
	return g_vroverlay->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
}
bool BaseOverlay::HandleControllerOverlayInteractionAsMouse(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex) {
  abort();
  return false;
	// return g_vroverlay->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
}
bool BaseOverlay::IsHoverTargetOverlay(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->IsHoverTargetOverlay(ulOverlayHandle);
}
VROverlayHandle_t BaseOverlay::GetGamepadFocusOverlay() {
  abort();
  return VROverlayHandle_t();
	// return g_vroverlay->GetGamepadFocusOverlay();
}
EVROverlayError BaseOverlay::SetGamepadFocusOverlay(VROverlayHandle_t ulNewFocusOverlay) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->SetGamepadFocusOverlay(ulNewFocusOverlay);
}
EVROverlayError BaseOverlay::SetOverlayNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->SetOverlayNeighbor(eDirection, ulFrom, ulTo);
}
EVROverlayError BaseOverlay::MoveGamepadFocusToNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom) {
  abort();
  return VROverlayError_None;
	// return g_vroverlay->MoveGamepadFocusToNeighbor(eDirection, ulFrom);
}
EVROverlayError BaseOverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t & vCenter, float fRadius) {
	return g_vroverlay->SetOverlayDualAnalogTransform(ulOverlay, eWhich, &vCenter, fRadius);
}
EVROverlayError BaseOverlay::GetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, HmdVector2_t *pvCenter, float *pfRadius) {
	return g_vroverlay->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius);
}
EVROverlayError BaseOverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t *pvCenter, float fRadius) {
	return g_vroverlay->SetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, fRadius);
}
EVROverlayError BaseOverlay::SetOverlayTexture(VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture) {
	return g_vroverlay->SetOverlayTexture(ulOverlayHandle, pTexture);
}
EVROverlayError BaseOverlay::ClearOverlayTexture(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->ClearOverlayTexture(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetOverlayRaw(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) {
	return g_vroverlay->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
}
EVROverlayError BaseOverlay::SetOverlayFromFile(VROverlayHandle_t ulOverlayHandle, const char *pchFilePath) {
	return g_vroverlay->SetOverlayFromFile(ulOverlayHandle, pchFilePath);
}
EVROverlayError BaseOverlay::GetOverlayTexture(VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds) {
	return g_vroverlay->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
}
EVROverlayError BaseOverlay::ReleaseNativeOverlayHandle(VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle) {
	return g_vroverlay->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
}
EVROverlayError BaseOverlay::GetOverlayTextureSize(VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight) {
	return g_vroverlay->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight);
}
EVROverlayError BaseOverlay::CreateDashboardOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle) {
	return g_vroverlay->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
}
bool BaseOverlay::IsDashboardVisible() {
	return g_vroverlay->IsDashboardVisible();
}
bool BaseOverlay::IsActiveDashboardOverlay(VROverlayHandle_t ulOverlayHandle) {
	return g_vroverlay->IsActiveDashboardOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) {
	return g_vroverlay->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
}
EVROverlayError BaseOverlay::GetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId) {
	return g_vroverlay->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
}
void BaseOverlay::ShowDashboard(const char *pchOverlayToShow) {
	return g_vroverlay->ShowDashboard(pchOverlayToShow);
}
TrackedDeviceIndex_t BaseOverlay::GetPrimaryDashboardDevice() {
	return g_vroverlay->GetPrimaryDashboardDevice();
}
/* EVROverlayError BaseOverlay::ShowKeyboardWithDispatch(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
	  const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue,
	  VRKeyboard::eventDispatch_t eventDispatch) {
	return g_vroverlay->ShowKeyboardWithDispatch(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue, eventDispatch);
} */
EVROverlayError BaseOverlay::ShowKeyboard(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
	  const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
  return g_vroverlay->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}
EVROverlayError BaseOverlay::ShowKeyboardForOverlay(VROverlayHandle_t ulOverlayHandle,
	  EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
  	const char *pchDescription, uint32_t unCharMax, const char *pchExistingText,
	  bool bUseMinimalMode, uint64_t uUserValue) {
  return g_vroverlay->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}
uint32_t BaseOverlay::GetKeyboardText(char *pchText, uint32_t cchText) {
	return g_vroverlay->GetKeyboardText(pchText, cchText);
}
void BaseOverlay::HideKeyboard() {
	return g_vroverlay->HideKeyboard();
}
void BaseOverlay::SetKeyboardTransformAbsolute(ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform) {
	return g_vroverlay->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
}
void BaseOverlay::SetKeyboardPositionForOverlay(VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect) {
	return g_vroverlay->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
}
EVROverlayError BaseOverlay::SetOverlayIntersectionMask(VROverlayHandle_t ulOverlayHandle, vr::VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) {
	return g_vroverlay->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize);
}
EVROverlayError BaseOverlay::GetOverlayFlags(VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags) {
	return g_vroverlay->GetOverlayFlags(ulOverlayHandle, pFlags);
}
VRMessageOverlayResponse BaseOverlay::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) {
	return g_vroverlay->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text);
}
void BaseOverlay::CloseMessageOverlay() {
	return g_vroverlay->CloseMessageOverlay();
}
