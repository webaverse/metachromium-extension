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
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->FindOverlay(pchOverlayKey, pOverlayHandle);
}
EVROverlayError BaseOverlay::CreateOverlay(const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t * pOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->CreateOverlay(pchOverlayKey, pchOverlayName, pOverlayHandle);
}
EVROverlayError BaseOverlay::DestroyOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->DestroyOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetHighQualityOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::SetHighQualityOverlay" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->SetHighQualityOverlay(ulOverlayHandle);
}
VROverlayHandle_t BaseOverlay::GetHighQualityOverlay() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::GetHighQualityOverlay" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->GetHighQualityOverlay();
}
uint32_t BaseOverlay::GetOverlayKey(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
}
uint32_t BaseOverlay::GetOverlayName(VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
}
EVROverlayError BaseOverlay::SetOverlayName(VROverlayHandle_t ulOverlayHandle, const char *pchName) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayName(ulOverlayHandle, pchName);
}
EVROverlayError BaseOverlay::GetOverlayImageData(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
}
const char * BaseOverlay::GetOverlayErrorNameFromEnum(EVROverlayError error) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  return g_vroverlay->GetOverlayErrorNameFromEnum(error);
}
EVROverlayError BaseOverlay::SetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle, uint32_t unPID) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayRenderingPid(ulOverlayHandle, unPID);
}
uint32_t BaseOverlay::GetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayRenderingPid(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
}
EVROverlayError BaseOverlay::GetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
}
EVROverlayError BaseOverlay::SetOverlayColor(VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
}
EVROverlayError BaseOverlay::GetOverlayColor(VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  return g_vroverlay->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
}
EVROverlayError BaseOverlay::SetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float fAlpha) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayAlpha(ulOverlayHandle, fAlpha);
}
EVROverlayError BaseOverlay::GetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float *pfAlpha) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayAlpha(ulOverlayHandle, pfAlpha);
}
EVROverlayError BaseOverlay::SetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float fTexelAspect) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
}
EVROverlayError BaseOverlay::GetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTexelAspect(ulOverlayHandle, pfTexelAspect);
}
EVROverlayError BaseOverlay::SetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
}
EVROverlayError BaseOverlay::GetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlaySortOrder(ulOverlayHandle, punSortOrder);
}
EVROverlayError BaseOverlay::SetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
}
EVROverlayError BaseOverlay::GetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
}
EVROverlayError BaseOverlay::SetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::SetOverlayAutoCurveDistanceRangeInMeters" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
}
EVROverlayError BaseOverlay::GetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::GetOverlayAutoCurveDistanceRangeInMeters" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
}
EVROverlayError BaseOverlay::SetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
}
EVROverlayError BaseOverlay::GetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
}
EVROverlayError BaseOverlay::SetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}
EVROverlayError BaseOverlay::GetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}
uint32_t BaseOverlay::GetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, EVROverlayError *pError) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayRenderModel(ulOverlayHandle, pchValue, unBufferSize, pColor, pError);
}
EVROverlayError BaseOverlay::SetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayRenderModel(ulOverlayHandle, pchRenderModel, pColor);
}
EVROverlayError BaseOverlay::GetOverlayTransformType(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTransformType(ulOverlayHandle, peTransformType);
}
EVROverlayError BaseOverlay::SetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}
EVROverlayError BaseOverlay::GetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}
EVROverlayError BaseOverlay::GetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
}
EVROverlayError BaseOverlay::GetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
}
EVROverlayError BaseOverlay::GetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
}
EVROverlayError BaseOverlay::SetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTransformOverlayRelative(ulOverlayHandle, ulOverlayHandleParent, pmatParentOverlayToOverlayTransform);
}
EVROverlayError BaseOverlay::ShowOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ShowOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::HideOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->HideOverlay(ulOverlayHandle);
}
bool BaseOverlay::IsOverlayVisible(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->IsOverlayVisible(ulOverlayHandle);
}
EVROverlayError BaseOverlay::GetTransformForOverlayCoordinates(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
}
bool BaseOverlay::PollNextOverlayEvent(VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t eventSize) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->PollNextOverlayEvent(ulOverlayHandle, pEvent, eventSize);
}
EVROverlayError BaseOverlay::GetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
}

EVROverlayError BaseOverlay::SetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
}
EVROverlayError BaseOverlay::GetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}
EVROverlayError BaseOverlay::SetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}
bool BaseOverlay::ComputeOverlayIntersection(VROverlayHandle_t ulOverlayHandle, const vr::VROverlayIntersectionParams_t *pParams, vr::VROverlayIntersectionResults_t *pResults) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
}
bool BaseOverlay::HandleControllerOverlayInteractionAsMouse(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::HandleControllerOverlayInteractionAsMouse" << std::endl; abort();
  return false;
	// return g_vroverlay->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
}
bool BaseOverlay::IsHoverTargetOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->IsHoverTargetOverlay(ulOverlayHandle);
}
VROverlayHandle_t BaseOverlay::GetGamepadFocusOverlay() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::GetGamepadFocusOverlay" << std::endl; abort();
  return VROverlayHandle_t();
	// return g_vroverlay->GetGamepadFocusOverlay();
}
EVROverlayError BaseOverlay::SetGamepadFocusOverlay(VROverlayHandle_t ulNewFocusOverlay) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::SetGamepadFocusOverlay" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->SetGamepadFocusOverlay(ulNewFocusOverlay);
}
EVROverlayError BaseOverlay::SetOverlayNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::SetOverlayNeighbor" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->SetOverlayNeighbor(eDirection, ulFrom, ulTo);
}
EVROverlayError BaseOverlay::MoveGamepadFocusToNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  getOut() << "abort BaseOverlay::MoveGamepadFocusToNeighbor" << std::endl; abort();
  return VROverlayError_None;
	// return g_vroverlay->MoveGamepadFocusToNeighbor(eDirection, ulFrom);
}
EVROverlayError BaseOverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t & vCenter, float fRadius) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayDualAnalogTransform(ulOverlay, eWhich, &vCenter, fRadius);
}
EVROverlayError BaseOverlay::GetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, HmdVector2_t *pvCenter, float *pfRadius) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, pfRadius);
}
EVROverlayError BaseOverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t *pvCenter, float fRadius) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayDualAnalogTransform(ulOverlay, eWhich, pvCenter, fRadius);
}
EVROverlayError BaseOverlay::SetOverlayTexture(VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayTexture(ulOverlayHandle, pTexture);
}
EVROverlayError BaseOverlay::ClearOverlayTexture(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ClearOverlayTexture(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetOverlayRaw(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
}
EVROverlayError BaseOverlay::SetOverlayFromFile(VROverlayHandle_t ulOverlayHandle, const char *pchFilePath) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayFromFile(ulOverlayHandle, pchFilePath);
}
EVROverlayError BaseOverlay::GetOverlayTexture(VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPIType, pColorSpace, pTextureBounds);
}
EVROverlayError BaseOverlay::ReleaseNativeOverlayHandle(VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
}
EVROverlayError BaseOverlay::GetOverlayTextureSize(VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight);
}
EVROverlayError BaseOverlay::CreateDashboardOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
}
bool BaseOverlay::IsDashboardVisible() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->IsDashboardVisible();
}
bool BaseOverlay::IsActiveDashboardOverlay(VROverlayHandle_t ulOverlayHandle) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->IsActiveDashboardOverlay(ulOverlayHandle);
}
EVROverlayError BaseOverlay::SetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
}
EVROverlayError BaseOverlay::GetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
}
void BaseOverlay::ShowDashboard(const char *pchOverlayToShow) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ShowDashboard(pchOverlayToShow);
}
TrackedDeviceIndex_t BaseOverlay::GetPrimaryDashboardDevice() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetPrimaryDashboardDevice();
}
/* EVROverlayError BaseOverlay::ShowKeyboardWithDispatch(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
	  const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue,
	  VRKeyboard::eventDispatch_t eventDispatch) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ShowKeyboardWithDispatch(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue, eventDispatch);
} */
EVROverlayError BaseOverlay::ShowKeyboard(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
	  const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  return g_vroverlay->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}
EVROverlayError BaseOverlay::ShowKeyboardForOverlay(VROverlayHandle_t ulOverlayHandle,
	  EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode,
  	const char *pchDescription, uint32_t unCharMax, const char *pchExistingText,
	  bool bUseMinimalMode, uint64_t uUserValue) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
  return g_vroverlay->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}
uint32_t BaseOverlay::GetKeyboardText(char *pchText, uint32_t cchText) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetKeyboardText(pchText, cchText);
}
void BaseOverlay::HideKeyboard() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->HideKeyboard();
}
void BaseOverlay::SetKeyboardTransformAbsolute(ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
}
void BaseOverlay::SetKeyboardPositionForOverlay(VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
}
EVROverlayError BaseOverlay::SetOverlayIntersectionMask(VROverlayHandle_t ulOverlayHandle, vr::VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->SetOverlayIntersectionMask(ulOverlayHandle, pMaskPrimitives, unNumMaskPrimitives, unPrimitiveSize);
}
EVROverlayError BaseOverlay::GetOverlayFlags(VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->GetOverlayFlags(ulOverlayHandle, pFlags);
}
VRMessageOverlayResponse BaseOverlay::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text, const char* pchButton2Text, const char* pchButton3Text) {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->ShowMessageOverlay(pchText, pchCaption, pchButton0Text, pchButton1Text, pchButton2Text, pchButton3Text);
}
void BaseOverlay::CloseMessageOverlay() {
  TRACE("BaseOverlay", []() { getOut() << "BaseOverlay::FindOverlay" << std::endl; });
	return g_vroverlay->CloseMessageOverlay();
}
