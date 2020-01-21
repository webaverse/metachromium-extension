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
    kIVROverlay_FindOverlay,
    std::tuple<EVROverlayError, VROverlayHandle_t>,
    managed_binary<char>
  >([=](managed_binary<char> overlayKey) {
    VROverlayHandle_t overlayHandle;
    auto error = vroverlay->FindOverlay(overlayKey.data(), &overlayHandle);

    return std::tuple<EVROverlayError, VROverlayHandle_t>(
      error,
      overlayHadle
    );
  });
  fnp.reg<
    kIVROverlay_CreateOverlay,
    std::tuple<EVROverlayError, VROverlayHandle_t>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> overlayKey, managed_binary<char> overlayName) {
    VROverlayHandle_t overlayHandle;
    auto error = vroverlay->CreateOverlay(overlayKey.data(), overlayName.data(), &overlayHandle);

    return std::tuple<EVROverlayError, VROverlayHandle_t>(
      error,
      overlayHadle
    );
  });
  fnp.reg<
    kIVROverlay_DestroyOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    return vroverlay->DestroyOverlay(ulOverlayHandle);
  });
  fnp.reg<
    kIVROverlay_SetHighQualityOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    return vroverlay->SetHighQualityOverlay(ulOverlayHandle);
  });
  fnp.reg<
    kIVROverlay_GetHighQualityOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >([=]() {
    return vroverlay->GetHighQualityOverlay();
  });
  fnp.reg<
    kIVROverlay_GetOverlayKey,
    std::tuple<uint32_t, managed_binary<char>, EVROverlayError>,
    VROverlayHandle_t,
    uint32_t
  >([=](VROverlayHandle_t ulOverlayHandle, uint32_t unBufferSize) {
    managed_binary<char> buffer(unBufferSize);
    EVROverlayError error;
    auto result = vroverlay->GetOverlayKey(ulOverlayHandle, buffer.data(), unBufferSize, &error);
    return std::tuple<uint32_t, managed_binary<char>, EVROverlayError>(
      result,
      std::move(buffer),
      error
    );
  });
  fnp.reg<
    kIVROverlay_GetOverlayName,
    std::tuple<uint32_t, managed_binary<char>, EVROverlayError>,
    VROverlayHandle_t,
    uint32_t
  >([=](VROverlayHandle_t ulOverlayHandle, uint32_t unBufferSize) {
    managed_binary<char> buffer(unBufferSize);
    EVROverlayError error;
    auto result = vroverlay->GetOverlayName(ulOverlayHandle, buffer.data(), unBufferSize, &error);
    return std::tuple<uint32_t, managed_binary<char>, EVROverlayError>(
      result,
      std::move(buffer),
      error
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayName,
    EVROverlayError,
    VROverlayHandle_t,
    managed_binary<char>
  >([=](VROverlayHandle_t ulOverlayHandle, managed_binary<char> name) {
    return vroverlay->SetOverlayName(ulOverlayHandle, name.data());
  });
  fnp.reg<
    kIVROverlay_GetOverlayImageData,
    std:tuple<EVROverlayError, managed_binary<char>, uint32_t, uint32_t>,
    VROverlayHandle_t,
    uint32_t
  >([=](VROverlayHandle_t ulOverlayHandle, uint32_t unBufferSize) {
    managed_binary<char> buffer(unBufferSize);
    uint32_t width;
    uint32_t height;
    auto error = vroverlay->GetOverlayImageData(ulOverlayHandle, buffer.data(), &width, &height);
    return std:tuple<EVROverlayError, managed_binary<char>, uint32_t, uint32_t>(
      error,
      std::move(buffer),
      width,
      height
    );
  });
  fnp.reg<
    kIVROverlay_GetOverlayErrorNameFromEnum,
    int
  >([=]() {
    getOut() << "GetOverlayErrorNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVROverlay_SetOverlayRenderingPid,
    EVROverlayError,
    VROverlayHandle_t,
    uint32_t
  >([=](VROverlayHandle_t ulOverlayHandle, uint32_t unPID) {
    return vroverlay->SetOverlayRenderingPid(ulOverlayHandle, unPID);
  });
  fnp.reg<
    kIVROverlay_GetOverlayRenderingPid,
    uint32_t,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    return vroverlay->GetOverlayRenderingPid(ulOverlayHandle);
  });
  fnp.reg<
    kIVROverlay_SetOverlayFlag,
    EVROverlayError,
    VROverlayHandle_t,
    VROverlayFlags,
    bool
  >([=](VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) {
    return vroverlay->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
  });
  fnp.reg<
    kIVROverlay_GetOverlayFlag,
    std::tuple<EVROverlayError, bool>,
    VROverlayHandle_t,
    VROverlayFlags
  >([=](VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag) {
    bool enabled;
    auto error = vroverlay->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, &enabled);
    return std::tuple<EVROverlayError, bool>(
      error,
      enabled
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayColor,
    EVROverlayError,
    VROverlayHandle_t,
    float,
    float,
    float
  >([=](VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) {
    return vroverlay->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
  });
  fnp.reg<
    kIVROverlay_GetOverlayColor,
    std::tuple<EVROverlayError, float, float, float>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    float red;
    float green;
    float blue;
    auto error = vroverlay->GetOverlayColor(ulOverlayHandle, &red, &green, &blue);
    return std::tuple<EVROverlayError, float, float, float>(
      error,
      red,
      green,
      blue
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayAlpha,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >([=](VROverlayHandle_t ulOverlayHandle, float fAlpha) {
    return vroverlay->SetOverlayAlpha(ulOverlayHandle, fAlpha);
  });
  fnp.reg<
    kIVROverlay_GetOverlayAlpha,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    float alpha;
    auto error = vroverlay->GetOverlayAlpha(ulOverlayHandle, &alpha);
    std::tuple<EVROverlayError, float>(
      error,
      alpha
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayTexelAspect,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >([=](VROverlayHandle_t ulOverlayHandle, float fTexelAspect) {
    return vroverlay->SetOverlayTexelAspect(ulOverlayHandle, fTexelAspect);
  });
  fnp.reg<
    kIVROverlay_GetOverlayTexelAspect,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    float texelAspect;
    auto error = vroverlay->GetOverlayTexelAspect(ulOverlayHandle, &texelAspect);
    return std::tuple<EVROverlayError, float>(
      error,
      texelAspect
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlaySortOrder,
    EVROverlayError,
    VROverlayHandle_t,
    uint32_t
  >([=](VROverlayHandle_t ulOverlayHandle, uint32_t unSortOrder) {
    return vroverlay->SetOverlaySortOrder(ulOverlayHandle, unSortOrder);
  });
  fnp.reg<
    kIVROverlay_GetOverlaySortOrder,
    std::tuple<EVROverlayError, uint32_t>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    uint32_t sortOrder;
    auto error = vroverlay->GetOverlaySortOrder(ulOverlayHandle, &sortOrder);
    return std::tuple<EVROverlayError, uint32_t>(
      error,
      sortOrder
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayWidthInMeters,
    EVROverlayError,
    VROverlayHandle_t,
    float
  >([=](VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
    return vroverlay->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
  });
  fnp.reg<
    kIVROverlay_GetOverlayWidthInMeters,
    std::tuple<EVROverlayError, float>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
    float widthInMeters;
    auto error = vroverlay->GetOverlayWidthInMeters(ulOverlayHandle, &widthInMeters);
    return std::tuple<EVROverlayError, float>(
      error,
      widthInMeters
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayAutoCurveDistanceRangeInMeters,
    EVROverlayError,
    float,
    float
  >([=](VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) {
    return vroverlay->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
  });
  fnp.reg<
    kIVROverlay_GetOverlayAutoCurveDistanceRangeInMeters,
    std::tuple<EVROverlayError, float, float>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    float minDistanceInMeters;
    float maxDistanceInMeters;
    auto error = vroverlay->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, &minDistanceInMeters, &maxDistanceInMeters);
    return std::tuple<EVROverlayError, float, float>(
      error,
      minDistanceInMeters,
      maxDistanceInMeters
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayTextureColorSpace,
    EVROverlayError,
    VROverlayHandle_t,
    EColorSpace
  >([=](VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {
    return vroverlay->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
  });
  fnp.reg<
    kIVROverlay_GetOverlayTextureColorSpace,
    std::tuple<EVROverlayError, EColorSpace>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    EColorSpace textureColorSpace;
    auto error = vroverlay->GetOverlayTextureColorSpace(ulOverlayHandle, &textureColorSpace);
    return std::tuple<EVROverlayError, EColorSpace>(
      error,
      textureColorSpace
    );
  });
  fnp.reg<
    kIVROverlay_SetOverlayTextureBounds,
    EVROverlayError,
    VROverlayHandle_t,
    VRTextureBounds_t
  >([=](VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t overlayTextureBounds) {
    return vroverlay->SetOverlayTextureBounds(ulOverlayHandle, &overlayTextureBounds);
  });
  fnp.reg<
    kIVROverlay_GetOverlayTextureBounds,
    std::tuple<EVROverlayError, VRTextureBounds_t>,
    VROverlayHandle_t
  >([=](VROverlayHandle_t ulOverlayHandle) {
    VRTextureBounds_t overlayTextureBounds;
    auto error = vroverlay->GetOverlayTextureBounds(ulOverlayHandle, &overlayTextureBounds);
    return std::tuple<EVROverlayError, VRTextureBounds_t>(
      error,
      overlayTextureBounds
    );
  });
  // XXX
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
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unBufferSize);
  memcpy(pvBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  *punWidth = std::get<2>(result);
  *punHeight = std::get<3>(result);
  return std::get<0>(result);
}
const char *PVROverlay::GetOverlayErrorNameFromEnum(EVROverlayError error) {
  getOut() << "GetOverlayErrorNameFromEnum abort" << std::endl;
  abort();
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
  return fnp.call<
    kIVROverlay_SetOverlayAutoCurveDistanceRangeInMeters,
    EVROverlayError,
    float,
    float
  >(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
}
EVROverlayError PVROverlay::GetOverlayAutoCurveDistanceRangeInMeters(VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayAutoCurveDistanceRangeInMeters,
    std::tuple<EVROverlayError, float, float>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pfMinDistanceInMeters = std::get<1>(result);
  *pfMaxDistanceInMeters = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {
  return fnp.call<
    kIVROverlay_SetOverlayTextureColorSpace,
    EVROverlayError,
    VROverlayHandle_t,
    EColorSpace
  >(ulOverlayHandle, eTextureColorSpace);
}
EVROverlayError PVROverlay::GetOverlayTextureColorSpace(VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTextureColorSpace,
    std::tuple<EVROverlayError, EColorSpace>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *peTextureColorSpace = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds) {
  return fnp.call<
    kIVROverlay_SetOverlayTextureBounds,
    EVROverlayError,
    VROverlayHandle_t,
    VRTextureBounds_t
  >(ulOverlayHandle, *pOverlayTextureBounds);
}
EVROverlayError PVROverlay::GetOverlayTextureBounds(VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTextureBounds,
    std::tuple<EVROverlayError, VRTextureBounds_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pOverlayTextureBounds = std::get<1>(result);
  return std::get<0>(result);
}
uint32_t PVROverlay::GetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, char *pchValue, uint32_t unBufferSize, HmdColor_t *pColor, EVROverlayError *pError) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayRenderModel,
    std::tuple<uint32_t, managed_binary<char>, HmdColor_t, EVROverlayError>,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unBufferSize);
  memcpy(pchValue, std::get<1>(result).data(), std::get<1>(result).size());
  *pColor = std::get<2>(result);
  if (pError) {
    *pError = std::get<3>(result);
  }
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayRenderModel(VROverlayHandle_t ulOverlayHandle, const char *pchRenderModel, const HmdColor_t *pColor) {
  managed_binary<char> renderModel(strlen(pchRenderModel)+1);
  memcpy(renderModel.data(), pchRenderModel, renderModel.size());
  return fnp.call<
    kIVROverlay_SetOverlayRenderModel,
    EVROverlayError,
    VROverlayHandle_t,
    managed_binary<char>,
    HmdColor_t
  >(ulOverlayHandle, std::move(renderModel), *pColor);
}
EVROverlayError PVROverlay::GetOverlayTransformType(VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTransformType,
    std::tuple<EVROverlayError, VROverlayTransformType>,
    VROverlayHandle_t
  >(ulOverlayHandle, unBufferSize);
  *peTransformType = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
  return fnp.call<
    kIVROverlay_SetOverlayTransformAbsolute,
    EVROverlayError,
    VROverlayHandle_t,
    ETrackingUniverseOrigin,
    HmdMatrix34_t
  >(ulOverlayHandle, eTrackingOrigin, *pmatTrackingOriginToOverlayTransform);
}
EVROverlayError PVROverlay::GetOverlayTransformAbsolute(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTransformAbsolute,
    std::tuple<EVROverlayError, ETrackingUniverseOrigin, HmdMatrix34_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *peTrackingOrigin = std::get<1>(result);
  *pmatTrackingOriginToOverlayTransform = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
  return fnp.call<
    kIVROverlay_SetOverlayTransformTrackedDeviceRelative,
    EVROverlayError,
    VROverlayHandle_t,
    TrackedDeviceIndex_t,
    HmdMatrix34_t
  >(ulOverlayHandle, unTrackedDevice, *pmatTrackedDeviceToOverlayTransform);
}
EVROverlayError PVROverlay::GetOverlayTransformTrackedDeviceRelative(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTransformTrackedDeviceRelative,
    std::tuple<EVROverlayError, TrackedDeviceIndex_t, HmdMatrix34_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *punTrackedDevice = std::get<1>(result);
  *pmatTrackedDeviceToOverlayTransform = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName) {
  managed_binary<char> name(strlen(pchComponentName)+1);
  memcpy(name.data(), pchComponentName, name.size());
  return fnp.call<
    kIVROverlay_SetOverlayTransformTrackedDeviceComponent,
    EVROverlayError,
    VROverlayHandle_t,
    TrackedDeviceIndex_t,
    managed_binary<char>
  >(ulOverlayHandle, unDeviceIndex, std::move(name));
}
EVROverlayError PVROverlay::GetOverlayTransformTrackedDeviceComponent(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTransformTrackedDeviceRelative,
    std::tuple<EVROverlayError, TrackedDeviceIndex_t, managed_binary<char>>,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unComponentNameSize);
  *punTrackedDevice = std::get<1>(result);
  memcpy(pchComponentName, std::get<2>(result).data(), std::get<2>(result).size());
  return std::get<0>(result);
}
EVROverlayError GetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t *ulOverlayHandleParent, HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTransformOverlayRelative,
    std::tuple<EVROverlayError, VROverlayHandle_t, HmdMatrix34_t>,
    VROverlayHandle_t
  >(ulOverlayHandle, unComponentNameSize);
  *ulOverlayHandleParent = std::get<1>(result);
  *pmatParentOverlayToOverlayTransform = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTransformOverlayRelative(VROverlayHandle_t ulOverlayHandle, VROverlayHandle_t ulOverlayHandleParent, const HmdMatrix34_t *pmatParentOverlayToOverlayTransform) {
  return fnp.call<
    kIVROverlay_SetOverlayTransformOverlayRelative,
    EVROverlayError,
    VROverlayHandle_t,
    HmdMatrix34_t
  >(ulOverlayHandle, ulOverlayHandleParent, *pmatParentOverlayToOverlayTransform);
}
EVROverlayError PVROverlay::ShowOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_ShowOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
EVROverlayError PVROverlay::HideOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_HideOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
bool PVROverlay::IsOverlayVisible(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_IsOverlayVisible,
    bool,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
EVROverlayError PVROverlay::GetTransformForOverlayCoordinates(VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform) {
  auto result = fnp.call<
    kIVROverlay_GetTransformForOverlayCoordinates,
    std::tuple<EVROverlayError, HmdMatrix34_t>,
    VROverlayHandle_t,
    ETrackingUniverseOrigin,
    HmdVector2_t
  >(ulOverlayHandle, coordinatesInOverlay);
  *pmatTransform = std::get<1>(result);
  return std::get<0>(result);
}
bool PVROverlay::PollNextOverlayEvent(VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t uncbVREvent) {
  auto result = fnp.call<
    kIVROverlay_PollNextOverlayEvent,
    std::tuple<bool, VREvent_t>,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, uncbVREvent);
  *pEvent = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::GetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayInputMethod,
    std::tuple<EVROverlayError, VROverlayInputMethod>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *peInputMethod = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayInputMethod(VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod) {
  return fnp.call<
    kIVROverlay_SetOverlayInputMethod,
    std::tuple<EVROverlayError, VROverlayInputMethod>,
    VROverlayHandle_t,
    VROverlayInputMethod
  >(ulOverlayHandle, eInputMethod);
}
EVROverlayError PVROverlay::GetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayMouseScale,
    std::tuple<EVROverlayError, HmdVector2_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pvecMouseScale = std::get<1>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayMouseScale(VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale) {
  return fnp.call<
    kIVROverlay_SetOverlayMouseScale,
    EVROverlayError,
    VROverlayHandle_t,
    HmdVector2_t
  >(ulOverlayHandle, *pvecMouseScale);
}
bool PVROverlay::ComputeOverlayIntersection(VROverlayHandle_t ulOverlayHandle, const vr::VROverlayIntersectionParams_t *pParams, vr::VROverlayIntersectionResults_t *pResults) {
  auto result = fnp.call<
    kIVROverlay_ComputeOverlayIntersection,
    std::tuple<bool, vr::VROverlayIntersectionResults_t>,
    VROverlayHandle_t,
    vr::VROverlayIntersectionParams_t
  >(ulOverlayHandle, *pParams);
  *pResults = std::get<1>(result);
  return std::get<0>(result);
}
bool PVROverlay::HandleControllerOverlayInteractionAsMouse(VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex) {
  return fnp.call<
    kIVROverlay_ComputeOverlayIntersection,
    bool,
    VROverlayHandle_t,
    TrackedDeviceIndex_t
  >(ulOverlayHandle, unControllerDeviceIndex);
}
bool PVROverlay::IsHoverTargetOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_IsHoverTargetOverlay,
    bool,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
VROverlayHandle_t PVROverlay::GetGamepadFocusOverlay() {
  return fnp.call<
    kIVROverlay_GetGamepadFocusOverlay,
    VROverlayHandle_t
  >();
}
EVROverlayError PVROverlay::SetGamepadFocusOverlay(VROverlayHandle_t ulNewFocusOverlay) {
  return fnp.call<
    kIVROverlay_SetGamepadFocusOverlay,
    EVROverlayError,
    VROverlayHandle_t
  >(ulNewFocusOverlay);
}
EVROverlayError PVROverlay::SetOverlayNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo) {
  return fnp.call<
    kIVROverlay_SetOverlayNeighbor,
    EVROverlayError,
    EOverlayDirection,
    VROverlayHandle_t,
    VROverlayHandle_t
  >(eDirection, ulFrom, ulTo);
}
EVROverlayError PVROverlay::MoveGamepadFocusToNeighbor(EOverlayDirection eDirection, VROverlayHandle_t ulFrom) {
  return fnp.call<
    kIVROverlay_MoveGamepadFocusToNeighbor,
    EVROverlayError,
    EOverlayDirection,
    VROverlayHandle_t
  >(eDirection, ulFrom);
}
EVROverlayError PVROverlay::SetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, const HmdVector2_t & vCenter, float fRadius) {
  return fnp.call<
    kIVROverlay_SetOverlayDualAnalogTransform,
    EVROverlayError,
    VROverlayHandle_t,
    EDualAnalogWhich,
    HmdVector2_t,
    float
  >(ulOverlay, vCenter, fRadius);
}
EVROverlayError PVROverlay::GetOverlayDualAnalogTransform(VROverlayHandle_t ulOverlay, EDualAnalogWhich eWhich, HmdVector2_t *pvCenter, float *pfRadius) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayDualAnalogTransform,
    std::tuple<EVROverlayError, HmdVector2_t, float>,
    VROverlayHandle_t,
    EDualAnalogWhich
  >(ulOverlayHandle, eWhich);
  *pvCenter = std::get<1>(result);
  *pfRadius = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::SetOverlayTexture(VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture) {
  getOut() << "SetOverlayTexture not implemented" << std::endl;
  return VROverlayError_None;
}
EVROverlayError PVROverlay::ClearOverlayTexture(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_ClearOverlayTexture,
    EVROverlayError,
    VROverlayHandle_t
  >(ulOverlay);
}
EVROverlayError PVROverlay::SetOverlayRaw(VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) {
  getOut() << "SetOverlayRaw not implemented" << std::endl;
  return VROverlayError_None;
}
EVROverlayError PVROverlay::SetOverlayFromFile(VROverlayHandle_t ulOverlayHandle, const char *pchFilePath) {
  getOut() << "SetOverlayFromFile not implemented" << std::endl;
  return VROverlayError_None;
}
EVROverlayError PVROverlay::GetOverlayTexture(VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, ETextureType *pAPIType, EColorSpace *pColorSpace, VRTextureBounds_t *pTextureBounds) {
  getOut() << "GetOverlayTexture abort" << std::endl;
  abort();
  return VROverlayError_None;
}
EVROverlayError PVROverlay::ReleaseNativeOverlayHandle(VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle) {
  getOut() << "ReleaseNativeOverlayHandle abort" << std::endl;
  abort();
  return VROverlayError_None;
}
EVROverlayError PVROverlay::GetOverlayTextureSize(VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayTextureSize,
    std::tuple<EVROverlayError, uint32_t, uint32_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pWidth = std::get<1>(result);
  *pHeight = std::get<2>(result);
  return std::get<0>(result);
}
EVROverlayError PVROverlay::CreateDashboardOverlay(const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle) {
  managed_binary<char> overlayKey(strlen(pchOverlayKey)+1);
  memcpy(overlayKey.data(), pchOverlayKey, overlayKey.size());
  managed_binary<char> overlayFriendlyName(strlen(pchOverlayFriendlyName)+1);
  memcpy(overlayFriendlyName.data(), pchOverlayFriendlyName, overlayFriendlyName.size());

  auto result = fnp.call<
    kIVROverlay_CreateDashboardOverlay,
    std::tuple<EVROverlayError, VROverlayHandle_t, VROverlayHandle_t>,
    VROverlayHandle_t
  >(std::move(overlayKey), std::move(overlayFriendlyName));
  *pMainHandle = std::get<1>(result);
  *pThumbnailHandle = std::get<2>(result);
  return std::get<0>(result);
}
bool PVROverlay::IsDashboardVisible() {
  return fnp.call<
    kIVROverlay_IsDashboardVisible,
    bool
  >();
}
bool PVROverlay::IsActiveDashboardOverlay(VROverlayHandle_t ulOverlayHandle) {
  return fnp.call<
    kIVROverlay_IsActiveDashboardOverlay,
    bool,
    VROverlayHandle_t
  >(ulOverlayHandle);
}
EVROverlayError PVROverlay::SetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) {
  return fnp.call<
    kIVROverlay_SetDashboardOverlaySceneProcess,
    EVROverlayError,
    VROverlayHandle_t,
    uint32_t
  >(ulOverlayHandle, unProcessId);
}
EVROverlayError PVROverlay::GetDashboardOverlaySceneProcess(VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId) {
  auto result = fnp.call<
    kIVROverlay_GetDashboardOverlaySceneProcess,
    std::tuple<EVROverlayError, uint32_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *punProcessId = std::get<1>(result);
  return std::get<0>(result);
}
void PVROverlay::ShowDashboard(const char *pchOverlayToShow) {
  managed_binary<char> overlayToShow(strlen(pchOverlayToShow)+1);
  memcpy(overlayToShow.data(), pchOverlayToShow, overlayToShow.size());

  fnp.call<
    kIVROverlay_ShowDashboard,
    int,
    managed_binary<char>
  >(std::move(overlayToShow));
}
TrackedDeviceIndex_t PVROverlay::GetPrimaryDashboardDevice() {
  return fnp.call<
    kIVROverlay_GetPrimaryDashboardDevice,
    TrackedDeviceIndex_t
  >();
}
EVROverlayError PVROverlay::ShowKeyboard(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
  managed_binary<char> description(strlen(pchDescription)+1);
  memcpy(description.data(), pchDescription, description.size());
  managed_binary<char> existingText(strlen(pchExistingText)+1);
  memcpy(existingText.data(), pchExistingText, existingText.size());

  return fnp.call<
    kIVROverlay_ShowKeyboard,
    EVROverlayError,
    EGamepadTextInputMode,
    EGamepadTextInputLineMode,
    managed_binary<char>,
    uint32_t,
    managed_binary<char>,
    bool,
    uint64_t
  >(eInputMode, eLineInputMode, std::move(description), unCharMax, std::move(existingText), bUseMinimalMode, uUserValue);
}
EVROverlayError PVROverlay::ShowKeyboardForOverlay(VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
  managed_binary<char> description(strlen(pchDescription)+1);
  memcpy(description.data(), pchDescription, description.size());
  managed_binary<char> existingText(strlen(pchExistingText)+1);
  memcpy(existingText.data(), pchExistingText, existingText.size());

  return fnp.call<
    kIVROverlay_ShowKeyboardForOverlay,
    EVROverlayError,
    VROverlayHandle_t,
    EGamepadTextInputMode,
    EGamepadTextInputLineMode,
    managed_binary<char>,
    uint32_t,
    managed_binary<char>,
    bool,
    uint64_t
  >(ulOverlayHandle, eInputMode, eLineInputMode, std::move(description), unCharMax, std::move(existingText), bUseMinimalMode, uUserValue);
}
uint32_t PVROverlay::GetKeyboardText(char *pchText, uint32_t cchText) {
  auto result = fnp.call<
    kIVROverlay_GetKeyboardText,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t
  >(ulOverlayHandle);
  memcpy(pchText, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
void PVROverlay::HideKeyboard() {
  fnp.call<
    kIVROverlay_HideKeyboard,
    int
  >();
}
void PVROverlay::SetKeyboardTransformAbsolute(ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform) {
  fnp.call<
    kIVROverlay_SetKeyboardTransformAbsolute,
    int,
    ETrackingUniverseOrigin,
    HmdMatrix34_t
  >(eTrackingOrigin, *pmatTrackingOriginToKeyboardTransform);
}
void PVROverlay::SetKeyboardPositionForOverlay(VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect) {
  fnp.call<
    kIVROverlay_SetKeyboardPositionForOverlay,
    int,
    VROverlayHandle_t,
    HmdRect2_t
  >(ulOverlayHandle, avoidRect);
}
EVROverlayError PVROverlay::SetOverlayIntersectionMask(VROverlayHandle_t ulOverlayHandle, vr::VROverlayIntersectionMaskPrimitive_t *pMaskPrimitives, uint32_t unNumMaskPrimitives, uint32_t unPrimitiveSize) {
  managed_binary<vr::VROverlayIntersectionMaskPrimitive_t> maskPrimitives(unNumMaskPrimitives);
  memcpy(maskPrimitives.data(), pMaskPrimitives, maskPrimitives.size() * sizeof(vr::VROverlayIntersectionMaskPrimitive_t));

  return fnp.call<
    kIVROverlay_SetOverlayIntersectionMask,
    EVROverlayError,
    VROverlayHandle_t,
    managed_binary<vr::VROverlayIntersectionMaskPrimitive_t>,
    uint32_t,
    uint32_t
  >(ulOverlayHandle, std::move(maskPrimitives), unNumMaskPrimitives, unPrimitiveSize);
}
EVROverlayError PVROverlay::GetOverlayFlags(VROverlayHandle_t ulOverlayHandle, uint32_t *pFlags) {
  auto result = fnp.call<
    kIVROverlay_GetOverlayFlags,
    std::tuple<EVROverlayError, uint32_t>,
    VROverlayHandle_t
  >(ulOverlayHandle);
  *pFlags = std::get<1>(result);
  return std::get<0>(result);
}
VRMessageOverlayResponse PVROverlay::ShowMessageOverlay(const char* pchText, const char* pchCaption, const char* pchButton0Text, const char* pchButton1Text = nullptr, const char* pchButton2Text = nullptr, const char* pchButton3Text = nullptr) {
  managed_binary<char> text(pchText ? strlen(pchText)+1 : 0);
  memcpy(text.data(), pchText, text.size());
  managed_binary<char> caption(pchCaption ? strlen(pchCaption)+1 : 0);
  memcpy(caption.data(), pchCaption, caption.size());
  managed_binary<char> button0Text(pchButton0Text ? strlen(pchButton0Text)+1 : 0);
  memcpy(button0Text.data(), pchButton0Text, button0Text.size());
  managed_binary<char> button1Text(pchButton1Text ? strlen(pchButton1Text)+1 : 0);
  memcpy(button1Text.data(), pchButton1Text, button1Text.size());
  managed_binary<char> button2Text(pchButton2Text ? strlen(pchButton2Text)+1 : 0);
  memcpy(button2Text.data(), pchButton2Text, button2Text.size());
  managed_binary<char> button3Text(pchButton3Text ? strlen(pchButton3Text)+1 : 0);
  memcpy(button3Text.data(), pchButton3Text, button3Text.size());

  return fnp.call<
    kIVROverlay_ShowMessageOverlay,
    VRMessageOverlayResponse,
    managed_binary<char>
  >(std::move(text), std::move(caption), std::move(button0Text), std::move(button1Text), std::move(button2Text), std::move(button3Text));
}
void PVROverlay::CloseMessageOverlay() {
  fnp.call<
    kIVROverlay_CloseMessageOverlay,
    int
  >();
}
}