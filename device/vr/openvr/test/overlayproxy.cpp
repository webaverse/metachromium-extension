#include "device/vr/openvr/test/overlayproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVROverlay_FindOverlay[] = "Input::FindOverlay";
char kIVROverlay_CreateOverlay[] = "Input::CreateOverlay";
char kIVROverlay_DestroyOverlay[] = "Input::DestroyOverlay";
char kIVROverlay_SetHighQualityOverlay[] = "Input::SetHighQualityOverlay";
char kIVROverlay_GetHighQualityOverlay[] = "Input::GetHighQualityOverlay";
char kIVROverlay_GetOverlayKey[] = "Input::GetOverlayKey";
char kIVROverlay_GetOverlayName[] = "Input::GetOverlayName";
char kIVROverlay_SetOverlayName[] = "Input::SetOverlayName";
char kIVROverlay_GetOverlayImageData[] = "Input::GetOverlayImageData";
char kIVROverlay_GetOverlayErrorNameFromEnum[] = "Input::GetOverlayErrorNameFromEnum";
char kIVROverlay_SetOverlayRenderingPid[] = "Input::SetOverlayRenderingPid";
char kIVROverlay_GetOverlayRenderingPid[] = "Input::GetOverlayRenderingPid";
char kIVROverlay_SetOverlayFlag[] = "Input::SetOverlayFlag";
char kIVROverlay_GetOverlayFlag[] = "Input::GetOverlayFlag";
char kIVROverlay_SetOverlayColor[] = "Input::SetOverlayColor";
char kIVROverlay_GetOverlayColor[] = "Input::GetOverlayColor";
char kIVROverlay_SetOverlayAlpha[] = "Input::SetOverlayAlpha";
char kIVROverlay_GetOverlayAlpha[] = "Input::GetOverlayAlpha";
char kIVROverlay_SetOverlayTexelAspect[] = "Input::SetOverlayTexelAspect";
char kIVROverlay_GetOverlayTexelAspect[] = "Input::SetOverlayTexelAspect";
char kIVROverlay_SetOverlaySortOrder[] = "Input::SetOverlaySortOrder";
char kIVROverlay_GetOverlaySortOrder[] = "Input::GetOverlaySortOrder";
char kIVROverlay_SetOverlayWidthInMeters[] = "Input::SetOverlayWidthInMeters";
char kIVROverlay_GetOverlayWidthInMeters[] = "Input::GetOverlayWidthInMeters";
char kIVROverlay_SetOverlayAutoCurveDistanceRangeInMeters[] = "Input::SetOverlayAutoCurveDistanceRangeInMeters";
char kIVROverlay_GetOverlayAutoCurveDistanceRangeInMeters[] = "Input::GetOverlayAutoCurveDistanceRangeInMeters";
char kIVROverlay_SetOverlayTextureColorSpace[] = "Input::SetOverlayTextureColorSpace";
char kIVROverlay_GetOverlayTextureColorSpace[] = "Input::GetOverlayTextureColorSpace";
char kIVROverlay_SetOverlayTextureBounds[] = "Input::SetOverlayTextureBounds";
char kIVROverlay_GetOverlayTextureBounds[] = "Input::GetOverlayTextureBounds";
char kIVROverlay_GetOverlayRenderModel[] = "Input::GetOverlayRenderModel";
char kIVROverlay_SetOverlayRenderModel[] = "Input::SetOverlayRenderModel";
char kIVROverlay_GetOverlayTransformType[] = "Input::GetOverlayTransformType";
char kIVROverlay_SetOverlayTransformAbsolute[] = "Input::SetOverlayTransformAbsolute";
char kIVROverlay_GetOverlayTransformAbsolute[] = "Input::GetOverlayTransformAbsolute";
char kIVROverlay_SetOverlayTransformTrackedDeviceRelative[] = "Input::SetOverlayTransformTrackedDeviceRelative";
char kIVROverlay_GetOverlayTransformTrackedDeviceRelative[] = "Input::GetOverlayTransformTrackedDeviceRelative";
char kIVROverlay_SetOverlayTransformTrackedDeviceComponent[] = "Input::SetOverlayTransformTrackedDeviceComponent";
char kIVROverlay_GetOverlayTransformTrackedDeviceComponent[] = "Input::GetOverlayTransformTrackedDeviceComponent";
char kIVROverlay_GetOverlayTransformOverlayRelative[] = "Input::GetOverlayTransformOverlayRelative";
char kIVROverlay_SetOverlayTransformOverlayRelative[] = "Input::SetOverlayTransformOverlayRelative";
char kIVROverlay_ShowOverlay[] = "Input::ShowOverlay";
char kIVROverlay_HideOverlay[] = "Input::HideOverlay";
char kIVROverlay_IsOverlayVisible[] = "Input::IsOverlayVisible";
char kIVROverlay_GetTransformForOverlayCoordinates[] = "Input::GetTransformForOverlayCoordinates";
char kIVROverlay_PollNextOverlayEvent[] = "Input::PollNextOverlayEvent";
char kIVROverlay_GetOverlayInputMethod[] = "Input::GetOverlayInputMethod";
char kIVROverlay_SetOverlayInputMethod[] = "Input::SetOverlayInputMethod";
char kIVROverlay_GetOverlayMouseScale[] = "Input::GetOverlayMouseScale";
char kIVROverlay_SetOverlayMouseScale[] = "Input::SetOverlayMouseScale";
char kIVROverlay_ComputeOverlayIntersection[] = "Input::ComputeOverlayIntersection";
char kIVROverlay_HandleControllerOverlayInteractionAsMouse[] = "Input::HandleControllerOverlayInteractionAsMouse";
char kIVROverlay_IsHoverTargetOverlay[] = "Input::IsHoverTargetOverlay";
char kIVROverlay_GetGamepadFocusOverlay[] = "Input::GetGamepadFocusOverlay";
char kIVROverlay_SetGamepadFocusOverlay[] = "Input::SetGamepadFocusOverlay";
char kIVROverlay_SetOverlayNeighbor[] = "Input::SetOverlayNeighbor";
char kIVROverlay_MoveGamepadFocusToNeighbor[] = "Input::MoveGamepadFocusToNeighbor";
char kIVROverlay_SetOverlayDualAnalogTransform[] = "Input::SetOverlayDualAnalogTransform";
char kIVROverlay_GetOverlayDualAnalogTransform[] = "Input::GetOverlayDualAnalogTransform";
char kIVROverlay_SetOverlayDualAnalogTransform[] = "Input::SetOverlayDualAnalogTransform";
char kIVROverlay_SetOverlayTexture[] = "Input::SetOverlayTexture";
char kIVROverlay_ClearOverlayTexture[] = "Input::ClearOverlayTexture";
char kIVROverlay_SetOverlayRaw[] = "Input::SetOverlayRaw";
char kIVROverlay_SetOverlayFromFile[] = "Input::SetOverlayFromFile";
char kIVROverlay_GetOverlayTexture[] = "Input::GetOverlayTexture";
char kIVROverlay_ReleaseNativeOverlayHandle[] = "Input::ReleaseNativeOverlayHandle";
char kIVROverlay_GetOverlayTextureSize[] = "Input::GetOverlayTextureSize";
char kIVROverlay_CreateDashboardOverlay[] = "Input::CreateDashboardOverlay";
char kIVROverlay_IsDashboardVisible[] = "Input::IsDashboardVisible";
char kIVROverlay_IsActiveDashboardOverlay[] = "Input::IsActiveDashboardOverlay";
char kIVROverlay_SetDashboardOverlaySceneProcess[] = "Input::SetDashboardOverlaySceneProcess";
char kIVROverlay_GetDashboardOverlaySceneProcess[] = "Input::GetDashboardOverlaySceneProcess";
char kIVROverlay_ShowDashboard[] = "Input::ShowDashboard";
char kIVROverlay_GetPrimaryDashboardDevice[] = "Input::GetPrimaryDashboardDevice";
char kIVROverlay_ShowKeyboard[] = "Input::ShowKeyboard";
char kIVROverlay_ShowKeyboardForOverlay[] = "Input::ShowKeyboardForOverlay";
char kIVROverlay_GetKeyboardText[] = "Input::GetKeyboardText";
char kIVROverlay_HideKeyboard[] = "Input::HideKeyboard";
char kIVROverlay_SetKeyboardTransformAbsolute[] = "Input::SetKeyboardTransformAbsolute";
char kIVROverlay_SetKeyboardPositionForOverlay[] = "Input::SetKeyboardPositionForOverlay";
char kIVROverlay_SetOverlayIntersectionMask[] = "Input::SetOverlayIntersectionMask";
char kIVROverlay_GetOverlayFlags[] = "Input::GetOverlayFlags";
char kIVROverlay_ShowMessageOverlay[] = "Input::ShowMessageOverlay";
char kIVROverlay_CloseMessageOverlay[] = "Input::CloseMessageOverlay";

PVROverlay::PVROverlay(IVROverlay *vroverlay, FnProxy &fnp) : vroverlay(vroverlay), fnp(fnp) {
  fnp.reg<
    kIVRInput_SetActionManifestPath,
    vr::EVRInputError,
    managed_binary<char>
  >([=](managed_binary<char> actionManifestPath) {
    // getOut() << "set action manifest path" << actionManifestPath.data() << std::endl;
    return vrinput->SetActionManifestPath(actionManifestPath.data());
  });
}
EVROverlayError PVROverlay::FindOverlay(const char *pchOverlayKey, VROverlayHandle_t *pOverlayHandle) {
  managed_binary<char> overlayKey(strlen(pchOverlayKey)+1);
  memcpy(overlayKey.data(), pchOverlayKey, overlayKey.size());

  auto result = fnp.call<
    kIVROverlay_FindOverlay,
    std::tuple<EVROverlayError, VROverlayHandle_t>,
    managed_binary<char>
  >(std::move(overlayKey));

  *pOverlayHandle = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::CreateOverlay(const char *pchOverlayKey, const char *pchOverlayName, VROverlayHandle_t *pOverlayHandle) {
  managed_binary<char> overlayKey(strlen(pchOverlayKey)+1);
  memcpy(overlayKey.data(), pchOverlayKey, overlayKey.size());
  managed_binary<char> overlayName(strlen(pchOverlayName)+1);
  memcpy(overlayName.data(), pchOverlayName, overlayName.size());

  auto result = fnp.call<
    kIVROverlay_CreateOverlay,
    std::tuple<EVROverlayError, VROverlayHandle_t>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(overlayKey), std::move(overlayName));

  *pOverlayHandle = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::DestroyOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_DestroyOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
EVROverlayError PVROverlay::SetHighQualityOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_SetHighQualityOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
VROverlayHandle_t PVROverlay::GetHighQualityOverlay() {
  return fnp.call<
    kIVROverlay_GetHighQualityOverlay,
    VROverlayHandle_t
  >();
}
uint32_t PVROverlay::GetOverlayKey(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayKey,
    std::tuple<uint32_t, managed_binary<char>, EVROverlayError>,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unBufferSize);
  memcpy(pchValue, std::get<1>(result).data(), std::get<1>(result).size());
  if (pError) {
    *pError = std::get<2>(result);
  }
  return std::get<0>(result);
}
uint32_t PVROverlay::GetOverlayName(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, EVROverlayError *pError) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayName,
    std::tuple<uint32_t, managed_binary<char>, EVROverlayError>,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unBufferSize);
  memcpy(pchValue, std::get<1>(result).data(), std::get<1>(result).size());
  if (pError) {
    *pError = std::get<2>(result);
  }
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayName(VROverlayHandle_t ulOverlayHandle, const char *pchName) {
  managed_binary<char> name(strlen(pchName)+1);
  memcpy(name.data(), pchName, name.size());

  return fnp.call<
    kIVROverlay_SetOverlayName,
    EVROverlayError,
    VROverlayHandle_t,
    managed_binary<char>
  >(ulOverlayHandle, std::move(name));
}
EVROverlayError PVROverlay::GetOverlayImageData(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayImageData,
    std:tuple<EVROverlayError, managed_binary<char>, uint32_t, uint32_t>,
    VROverlayHandle_t
  >(ulOverlayHandle, unBufferSize);
  memcpy(pvBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  *punWidth = std::get<2>(result);
  *punHeight = std::get<3>(result);
  return std::get<0>(result);
}
const char *PVROverlay::GetOverlayErrorNameFromEnum(EVROverlayError error) {
  getOut() << "GetOverlayErrorNameFromEnum abort" << std::endl;
  return "";
}
EVROverlayError PVROverlay::SetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle, uint32_t unPID) {
  return fnp.call<
    kIVROverlay_SetOverlayRenderingPid,
    EVROverlayError,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unPID);
}
uint32_t PVROverlay::GetOverlayRenderingPid(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_GetOverlayRenderingPid,
    uint32_t,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
EVROverlayError PVROverlay::SetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) {
  return fnp.call<
    kIVROverlay_SetOverlayFlag,
    EVROverlayError,
    VROverlayHandle_t,
    VROverlayFlags,
    bool
  >(ulOverlayHandle, eOverlayFlag, bEnabled);
}
EVROverlayError PVROverlay::GetOverlayFlag(VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayFlag,
    std::tuple<EVROverlayError, bool>,
    VROverlayHandle_t,
    VROverlayFlags
  >(ulOverlayHandle, eOverlayFlag);
  *pbEnabled = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayColor(VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) {
  return fnp.call<
    kIVROverlay_SetOverlayColor,
    EVROverlayError,
    VROverlayHandle_t,
    float,
    float,
    float
  >(ulOverlayHandle, fRed, fGreen, fBlue);
}
EVROverlayError PVROverlay::GetOverlayColor(VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayColor,
    std::tuple<EVROverlayError, float, float, float>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pfRed = std::get<1>(result);
  *pfGreen = std::get<2>(result);
  *pfBlue = std::get<3>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float fAlpha) {
  return fnp.call<
    kIVROverlay_SetOverlayAlpha,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >(ulOverlayHandle, fAlpha);
}
EVROverlayError PVROverlay::GetOverlayAlpha(VROverlayHandle_t ulOverlayHandle, float *pfAlpha) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayAlpha,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pfAlpha = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float fTexelAspect) {
  return fnp.call<
    kIVROverlay_SetOverlayTexelAspect,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >(ulOverlayHandle, fTexelAspect);
}
EVROverlayError PVROverlay::GetOverlayTexelAspect(VROverlayHandle_t ulOverlayHandle, float *pfTexelAspect) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTexelAspect,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pfTexelAspect = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) {
  return fnp.call<
    kIVROverlay_SetOverlaySortOrder,
    EVROverlayError,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unSortOrder);
}
EVROverlayError PVROverlay::GetOverlaySortOrder(VROverlayHandle_t ulOverlayHandle, uint32_t *punSortOrder) {
  auto result = fnp.call<
    kIVROverlay_GetOverlaySortOrder,
    std::tuple<EVROverlayError, uint32_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *punSortOrder = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
  return fnp.call<
    kIVROverlay_SetOverlayWidthInMeters,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >(ulOverlayHandle, fWidthInMeters);
}
EVROverlayError PVROverlay::GetOverlayWidthInMeters(VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayWidthInMeters,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pfWidthInMeters = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) {

}
EVROverlayError PVROverlay::GetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters) {

}
EVROverlayError PVROverlay::SetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {

}
EVROverlayError PVROverlay::GetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace) {

}
EVROverlayError PVROverlay::SetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds) {

}
EVROverlayError PVROverlay::GetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds) {

}
uint32_t PVROverlay::GetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, EVROverlayError *pError) {

}
EVROverlayError PVROverlay::SetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor) {

}
EVROverlayError PVROverlay::GetOverlayTransformType(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType) {

}
EVROverlayError PVROverlay::SetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {

}
EVROverlayError PVROverlay::GetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {

}
EVROverlayError PVROverlay::SetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {

}
EVROverlayError PVROverlay::GetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {

}
EVROverlayError PVROverlay::SetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName) {

}
EVROverlayError PVROverlay::GetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize) {

}
EVROverlayError GetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {

}
EVROverlayError PVROverlay::SetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {

}
EVROverlayError PVROverlay::ShowOverlay(VROverlayHandle_t ulOverlayHandle) {

}
EVROverlayError PVROverlay::HideOverlay(VROverlayHandle_t ulOverlayHandle) {

}
bool PVROverlay::IsOverlayVisible(VROverlayHandle_t ulOverlayHandle) {

}
EVROverlayError PVROverlay::GetTransformForOverlayCoordinates(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform) {

}
bool PVROverlay::PollNextOverlayEvent(VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t uncbVREvent) {

}
EVROverlayError PVROverlay::GetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod) {

}
EVROverlayError PVROverlay::SetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod) {

}
EVROverlayError PVROverlay::GetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale) {

}
EVROverlayError PVROverlay::SetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale) {

}
bool PVROverlay::ComputeOverlayIntersection(VROverlayHandle_t ulOverlayHandle, const vr::VROverlayIntersectionParams_t *pParams, vr::VROverlayIntersectionResults_t *pResults) {

}
bool PVROverlay::HandleControllerOverlayInteractionAsMouse(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex) {

}
bool PVROverlay::IsHoverTargetOverlay(VROverlayHandle_t ulOverlayHandle) {

}
VROverlayHandle_t PVROverlay::GetGamepadFocusOverlay() {

}
EVROverlayError PVROverlay::SetGamepadFocusOverlay(VROverlayHandle_t ulNewFocusOverlay) {
}
EVROverlayError PVROverlay::SetOverlayNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo) {

}
EVROverlayError PVROverlay::MoveGamepadFocusToNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom) {

}
EVROverlayError PVROverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t & vCenter, float fRadius) {

}
EVROverlayError PVROverlay::GetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, HmdVector2_t *pvCenter, float *pfRadius) {

}
EVROverlayError PVROverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t *pvCenter, float fRadius) {

}
EVROverlayError PVROverlay::SetOverlayTexture(VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture) {

}
EVROverlayError PVROverlay::ClearOverlayTexture(VROverlayHandle_t ulOverlayHandle) {

}
EVROverlayError PVROverlay::SetOverlayRaw(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) {

}
EVROverlayError PVROverlay::SetOverlayFromFile(VROverlayHandle_t ulOverlayHandle, const char *pchFilePath) {

}
EVROverlayError PVROverlay::GetOverlayTexture(VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds) {

}
EVROverlayError PVROverlay::ReleaseNativeOverlayHandle(VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle) {

}
EVROverlayError PVROverlay::GetOverlayTextureSize(VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight) {

}
EVROverlayError PVROverlay::CreateDashboardOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle) {

}
bool PVROverlay::IsDashboardVisible() {

}
bool PVROverlay::IsActiveDashboardOverlay(VROverlayHandle_t ulOverlayHandle) {

}
EVROverlayError PVROverlay::SetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) {

}
EVROverlayError PVROverlay::GetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId) {

}
void PVROverlay::ShowDashboard(const char *pchOverlayToShow) {

}
TrackedDeviceIndex_t PVROverlay::GetPrimaryDashboardDevice() {

}
EVROverlayError PVROverlay::ShowKeyboard(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {

}
EVROverlayError PVROverlay::ShowKeyboardForOverlay(VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {

}
uint32_t PVROverlay::GetKeyboardText(char *pchText, uint32_t cchText) {

}
void PVROverlay::HideKeyboard() {

}
void PVROverlay::SetKeyboardTransformAbsolute(ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform) {

}
void PVROverlay::SetKeyboardPositionForOverlay(VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect) {

}
EVROverlayError PVROverlay::SetOverlayIntersectionMask(VROverlayHandle_t ulOverlayHandle, vr::VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize = sizeof(vr::VROverlayIntersectionMaskPrimitive_t)) {

}
EVROverlayError PVROverlay::GetOverlayFlags(VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags) {

}
VRMessageOverlayResponse PVROverlay::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text = nullptr, const char* pchButton2Text = nullptr, const char* pchButton3Text = nullptr) {

}
void PVROverlay::CloseMessageOverlay() {

}
}