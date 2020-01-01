// #include <chrono>
#include "device/vr/openvr/test/systemproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRSystem_GetRecommendedRenderTargetSize[] = "IVRSystem::GetRecommendedRenderTargetSize";
char kIVRSystem_GetProjectionMatrix[] = "IVRSystem::GetProjectionMatrix";
char kIVRSystem_GetProjectionRaw[] = "IVRSystem::GetProjectionRaw";
char kIVRSystem_ComputeDistortion[] = "IVRSystem::ComputeDistortion";
char kIVRSystem_GetEyeToHeadTransform[] = "IVRSystem::GetEyeToHeadTransform";
char kIVRSystem_GetTimeSinceLastVsync[] = "IVRSystem::GetTimeSinceLastVsync";
char kIVRSystem_GetD3D9AdapterIndex[] = "IVRSystem::GetD3D9AdapterIndex";
char kIVRSystem_GetDXGIOutputInfo[] = "IVRSystem::GetDXGIOutputInfo";
char kIVRSystem_GetOutputDevice[] = "IVRSystem::GetOutputDevice";
char kIVRSystem_GetOutputDevice[] = "IVRSystem::GetOutputDevice";
char kIVRSystem_IsDisplayOnDesktop[] = "IVRSystem::IsDisplayOnDesktop";
char kIVRSystem_SetDisplayVisibility[] = "IVRSystem::SetDisplayVisibility";
char kIVRSystem_GetDeviceToAbsoluteTrackingPose[] = "IVRSystem::GetDeviceToAbsoluteTrackingPose";
char kIVRSystem_ResetSeatedZeroPose[] = "IVRSystem::ResetSeatedZeroPose";
char kIVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose[] = "IVRSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose";
char kIVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose[] = "IVRSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose";
char kIVRSystem_GetSortedTrackedDeviceIndicesOfClass[] = "IVRSystem::GetSortedTrackedDeviceIndicesOfClass";
char kIVRSystem_GetTrackedDeviceActivityLevel[] = "IVRSystem::GetTrackedDeviceActivityLevel";
char kIVRSystem_ApplyTransform[] = "IVRSystem::ApplyTransform";
char kIVRSystem_GetTrackedDeviceIndexForControllerRole[] = "IVRSystem::GetTrackedDeviceIndexForControllerRole";
char kIVRSystem_GetControllerRoleForTrackedDeviceIndex[] = "IVRSystem::GetControllerRoleForTrackedDeviceIndex";
char kIVRSystem_GetTrackedDeviceClass[] = "IVRSystem::GetTrackedDeviceClass";
char kIVRSystem_IsTrackedDeviceConnected[] = "IVRSystem::IsTrackedDeviceConnected";
char kIVRSystem_GetBoolTrackedDeviceProperty[] = "IVRSystem::GetBoolTrackedDeviceProperty";
char kIVRSystem_GetFloatTrackedDeviceProperty[] = "IVRSystem::GetFloatTrackedDeviceProperty";
char kIVRSystem_GetInt32TrackedDeviceProperty[] = "IVRSystem::GetInt32TrackedDeviceProperty";
char kIVRSystem_GetUint64TrackedDeviceProperty[] = "IVRSystem::GetUint64TrackedDeviceProperty";
char kIVRSystem_GetMatrix34TrackedDeviceProperty[] = "IVRSystem::GetMatrix34TrackedDeviceProperty";
char kIVRSystem_GetArrayTrackedDeviceProperty[] = "IVRSystem::GetArrayTrackedDeviceProperty";
char kIVRSystem_GetStringTrackedDeviceProperty[] = "IVRSystem::GetStringTrackedDeviceProperty";
char kIVRSystem_GetPropErrorNameFromEnum[] = "IVRSystem::GetPropErrorNameFromEnum";
char kIVRSystem_IsInputAvailable[] = "IVRSystem::IsInputAvailable";
char kIVRSystem_IsSteamVRDrawingControllers[] = "IVRSystem::IsSteamVRDrawingControllers";
char kIVRSystem_ShouldApplicationPause[] = "IVRSystem::ShouldApplicationPause";
char kIVRSystem_ShouldApplicationReduceRenderingWork[] = "IVRSystem::ShouldApplicationReduceRenderingWork";
char kIVRSystem_PollNextEvent[] = "IVRSystem::PollNextEvent";
char kIVRSystem_PollNextEventWithPose[] = "IVRSystem::PollNextEventWithPose";
char kIVRSystem_GetEventTypeNameFromEnum[] = "IVRSystem::GetEventTypeNameFromEnum";
char kIVRSystem_GetHiddenAreaMesh[] = "IVRSystem::GetHiddenAreaMesh";
char kIVRSystem_GetControllerState[] = "IVRSystem::GetControllerState";
char kIVRSystem_GetControllerStateWithPose[] = "IVRSystem::GetControllerStateWithPose";
char kIVRSystem_TriggerHapticPulse[] = "IVRSystem::TriggerHapticPulse";
char kIVRSystem_GetButtonIdNameFromEnum[] = "IVRSystem::GetButtonIdNameFromEnum";
char kIVRSystem_GetControllerAxisTypeNameFromEnum[] = "IVRSystem::GetControllerAxisTypeNameFromEnum";
char kIVRSystem_CaptureInputFocus[] = "IVRSystem::CaptureInputFocus";
char kIVRSystem_ReleaseInputFocus[] = "IVRSystem::ReleaseInputFocus";
char kIVRSystem_IsInputFocusCapturedByAnotherProcess[] = "IVRSystem::IsInputFocusCapturedByAnotherProcess";
char kIVRSystem_DriverDebugRequest[] = "IVRSystem::DriverDebugRequest";
char kIVRSystem_PerformFirmwareUpdate[] = "IVRSystem::PerformFirmwareUpdate";
char kIVRSystem_AcknowledgeQuit_Exiting[] = "IVRSystem::AcknowledgeQuit_Exiting";
char kIVRSystem_AcknowledgeQuit_UserPrompt[] = "IVRSystem::AcknowledgeQuit_UserPrompt";
char kIVRSystem_GetAppContainerFilePaths[] = "IVRSystem::GetAppContainerFilePaths";
char kIVRSystem_GetRuntimeVersion[] = "IVRSystem::GetRuntimeVersion";
char kIVRSystem_ComputeDistortion[] = "IVRSystem::ComputeDistortion";
char kIVRSystem_GetProjectionMatrix[] = "IVRSystem::GetProjectionMatrix";
char kIVRSystem_PerformanceTestEnableCapture[] = "IVRSystem::PerformanceTestEnableCapture";
char kIVRSystem_PerformanceTestReportFidelityLevelChange[] = "IVRSystem::PerformanceTestReportFidelityLevelChange";

PVRSystem::PVRSystem(IVRSystem *vrsystem, FnProxy &fnp) : vrsystem(vrsystem)(vrsystem(vrsystem)), fnp(fnp) {
  fnp.reg<
    kIVRSystem_GetRecommendedRenderTargetSize,
    std::tuple<uint32_t, uint32_t>
  >([=]() {
    uint32_t width, height;
    vrsystem->GetRecommendedRenderTargetSize(&width, &height);
    return std::tuple<uint32_t, uint32_t>(width, height);
  });
  fnp.reg<
    kIVRSystem_GetProjectionMatrix,
    HmdMatrix44_t,
    EVREye,
    float,
    float
  >([=](EVREye eEye, float fNearZ, float fFarZ) {
    return vrsystem->GetProjectionMatrix(eEye, fNearZ, fFarZ);
  });
  fnp.reg<
    kIVRSystem_GetProjectionRaw,
    std:tuple<float, float, float, float>,
    EVREye
  >([=](EVREye eEye) {
    float left, right, top, bottom;
    vrsystem->GetProjectionRaw(eEye, &left, &right, &top, &bottom);
    return std:tuple<float, float, float, float>(left, right, top, bottom);
  });
  fnp.reg<
    kIVRSystem_ComputeDistortion,
    std::tuple<bool, DistortionCoordinates_t>,
    float,
    float
  >([=](EVREye eEye, float fU, fV) {
    DistortionCoordinates_t distCoords;
    auto result = vrsystem->ComputeDistortion(eEye, &distCoords);
    return std:tuple<bool, DistortionCoordinates_t>(result, distCoords);
  });
  fnp.reg<
    kIVRSystem_GetEyeToHeadTransform,
    HmdMatrix34_t,
    EVREye
  >([=](EVREye eEye) {
    return vrsystem->GetEyeToHeadTransform(eEye);
  });
  fnp.reg<
    kIVRSystem_GetTimeSinceLastVsync,
    std::tuple<bool, float, uint64_t>
  >([=]() {
    float fSecondsSinceLastVsync, ulFrameCounter;
    auto result = vrsystem->GetTimeSinceLastVsync(eEye, &fSecondsSinceLastVsync, &ulFrameCounter);
    return std::tuple<bool, float, uint64_t>(result, fSecondsSinceLastVsync, ulFrameCounter);
  });
  fnp.reg<
    kIVRSystem_GetD3D9AdapterIndex,
    int32_t
  >([=]() {
    return vrsystem->GetD3D9AdapterIndex();
  });
  fnp.reg<
    kIVRSystem_GetDXGIOutputInfo,
    int32_t
  >([=]() {
    int32_t result;
    vrsystem->GetDXGIOutputInfo(&result);
    return result;
  });
  fnp.reg<
    kIVRSystem_GetOutputDevice,
    int
  >([=]() {
    getOut() << "GetOutputDevice abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_IsDisplayOnDesktop,
    bool
  >([=]() {
    return vrsystem->kIVRSystem_IsDisplayOnDesktop();
  });
  fnp.reg<
    kIVRSystem_SetDisplayVisibility,
    bool,
    bool
  >([=](bool bIsVisibleOnDesktop) {
    return vrsystem->SetDisplayVisibility(bIsVisibleOnDesktop);
  });
  fnp.reg<
    kIVRSystem_GetDeviceToAbsoluteTrackingPose,
    managed_binary<TrackedDevicePose_t>,
    ETrackingUniverseOrigin,
    float,
    uint32_t
  >([=](ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, uint32_t unTrackedDevicePoseArrayCount) {
    managed_binary<TrackedDevicePose_t> result(unTrackedDevicePoseArrayCount);
    vrsystem->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, result.data(), unTrackedDevicePoseArrayCount);
    return std::move(result);
  });
  fnp.reg<
    kIVRSystem_ResetSeatedZeroPose,
    int
  >([=]() {
    vrsystem->ResetSeatedZeroPose();
    return 0;
  });
  fnp.reg<
    kIVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
    HmdMatrix34_t
  >([=]() {
    return vrsystem->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
  });
  fnp.reg<
    kIVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose,
    HmdMatrix34_t
  >([=]() {
    return vrsystem->GetRawZeroPoseToStandingAbsoluteTrackingPose();
  });
  fnp.reg<
    kIVRSystem_GetSortedTrackedDeviceIndicesOfClass,
    std::tuple<int32_t, managed_binary<vr::TrackedDeviceIndex_t>>,
    ETrackedDeviceClass,
    uint32_t,
    vr::TrackedDeviceIndex_t
  >([=](ETrackedDeviceClass eTrackedDeviceClass, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) {
    managed_binary<vr::TrackedDeviceIndex_t> trackedDeviceIndexArray(unTrackedDeviceIndexArrayCount);
    auto result = vrsystem->GetSortedTrackedDeviceIndicesOfClass(
      eTrackedDeviceClass,
      trackedDeviceIndexArray.data(),
      unTrackedDeviceIndexArrayCount,
      unRelativeToTrackedDeviceIndex
    );
    return std::tuple<int32_t, managed_binary<vr::TrackedDeviceIndex_t>>(
      result,
      std::move(trackedDeviceIndexArray)
    );
  });
  fnp.reg<
    kIVRSystem_GetTrackedDeviceActivityLevel,
    EDeviceActivityLevel,
    vr::TrackedDeviceIndex_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex) {
    return vrsystem->GetTrackedDeviceActivityLevel(unDeviceIndex);
  });
  fnp.reg<
    kIVRSystem_ApplyTransform,
    TrackedDevicePose_t,
    TrackedDevicePose_t,
    HmdMatrix34_t
  >([=](TrackedDevicePose_t trackedDevicePose, HmdMatrix34_t transform) {
    TrackedDevicePose_t result;
    vrsystem->ApplyTransform(&result, &trackedDevicePose, &transform);
    return result;
  });
  fnp.reg<
    kIVRSystem_GetTrackedDeviceIndexForControllerRole,
    vr::TrackedDeviceIndex_t,
    vr::ETrackedControllerRole
  >([=](vr::ETrackedControllerRole unDeviceType) {
    return vrsystem->GetTrackedDeviceIndexForControllerRole(unDeviceType);
  });
  fnp.reg<
    kIVRSystem_GetControllerRoleForTrackedDeviceIndex,
    vr::ETrackedControllerRole,
    vr::TrackedDeviceIndex_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex) {
    return vrsystem->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
  });
  fnp.reg<
    kIVRSystem_GetTrackedDeviceClass,
    vr::ETrackedControllerRole,
    vr::TrackedDeviceIndex_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex) {
    return vrsystem->GetTrackedDeviceClass(unDeviceIndex);
  });
  fnp.reg<
    kIVRSystem_IsTrackedDeviceConnected,
    bool,
    vr::TrackedDeviceIndex_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex) {
    return vrsystem->IsTrackedDeviceConnected(unDeviceIndex);
  });
  fnp.reg<
    kIVRSystem_GetBoolTrackedDeviceProperty,
    std::tuple<bool, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop) {
    ETrackedPropertyError result2;
    auto result1 = vrsystem->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, &result2);
    return std::tuple<bool, ETrackedPropertyError>(result1, result2);
  });
  fnp.reg<
    kIVRSystem_GetFloatTrackedDeviceProperty,
    std::tuple<float, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop) {
    ETrackedPropertyError result2;
    auto result1 = vrsystem->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, &result2);
    return std::tuple<float, ETrackedPropertyError>(result1, result2);
  });
  fnp.reg<
    kIVRSystem_GetInt32TrackedDeviceProperty,
    std::tuple<int32_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop) {
    ETrackedPropertyError result2;
    auto result1 = vrsystem->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, &result2);
    return std::tuple<int32_t, ETrackedPropertyError>(result1, result2);
  });
  fnp.reg<
    kIVRSystem_GetUint64TrackedDeviceProperty,
    std::tuple<uint64_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop) {
    ETrackedPropertyError result2;
    auto result1 = vrsystem->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, &result2);
    return std::tuple<uint64_t, ETrackedPropertyError>(result1, result2);
  });
  fnp.reg<
    kIVRSystem_GetMatrix34TrackedDeviceProperty,
    std::tuple<HmdMatrix34_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop) {
    ETrackedPropertyError result2;
    auto result1 = vrsystem->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, &result2);
    return std::tuple<HmdMatrix34_t, ETrackedPropertyError>(result1, result2);
  });
  fnp.reg<
    kIVRSystem_GetArrayTrackedDeviceProperty,
    std::tuple<uint32_t, managed_binary<unsigned char>, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty,
    PropertyTypeTag_t,
    uint32_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedDeviceProperty propType, uint32_t unBufferSize) {
    managed_binary<unsigned char> buffer(unBufferSize);
    ETrackedPropertyError error;
    auto numBytes = vrsystem->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, buffer.data(), unBufferSize, &error);
    return std::tuple<HmdMatrix34_t, ETrackedPropertyError>(
      numBytes,
      std::move(buffer),
      error
    );
  });
  fnp.reg<
    kIVRSystem_GetStringTrackedDeviceProperty,
    std::tuple<uint32_t, managed_binary<char>, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty,
    uint32_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, uint32_t unBufferSize) {
    managed_binary<char> buffer(unBufferSize);
    ETrackedPropertyError error;
    auto numBytes = vrsystem->GetStringTrackedDeviceProperty(unDeviceIndex, prop, buffer.data(), unBufferSize, &error);
    return std::tuple<HmdMatrix34_t, ETrackedPropertyError>(
      numBytes,
      std::move(buffer),
      error
    );
  });
  fnp.reg<
    kIVRSystem_GetPropErrorNameFromEnum,
    int
  >([=]() { // XXX
    getOut() << "GetPropErrorNameFromEnum" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_IsInputAvailable,
    bool
  >([=]() {
    return vrsystem->IsInputAvailable();
  });
  fnp.reg<
    kIVRSystem_IsSteamVRDrawingControllers,
    bool
  >([=]() {
    return vrsystem->IsSteamVRDrawingControllers();
  });
  fnp.reg<
    kIVRSystem_ShouldApplicationPause,
    bool
  >([=]() {
    return vrsystem->ShouldApplicationPause();
  });
  fnp.reg<
    kIVRSystem_ShouldApplicationReduceRenderingWork,
    bool
  >([=]() {
    return vrsystem->ShouldApplicationReduceRenderingWork();
  });
  fnp.reg<
    kIVRSystem_PollNextEvent,
    std::tuple<bool, VREvent_t>,
    uint32_t
  >([=](uint32_t uncbVREvent) {
    VREvent_t event;
    auto result = vrsystem->PollNextEvent(&event, uncbVREvent);
    return std::tuple<bool, VREvent_t>(result, event);
  });
  fnp.reg<
    kIVRSystem_PollNextEventWithPose,
    std::tuple<bool, VREvent_t, vr::TrackedDevicePose_t>,
    ETrackingUniverseOrigin,
    uint32_t
  >([=](ETrackingUniverseOrigin eOrigin, uint32_t uncbVREvent) {
    VREvent_t event;
    vr::TrackedDevicePose_t pose;
    auto result = vrsystem->PollNextEventWithPose(eOrigin, &event, uncbVREvent, &pose);
    return std::tuple<bool, VREvent_t, vr::TrackedDevicePose_t>(result, event, pose);
  });
  fnp.reg<
    kIVRSystem_GetEventTypeNameFromEnum,
    int
  >([=](ETrackingUniverseOrigin eOrigin, uint32_t uncbVREvent) {
    getOut() << "GetPropErrorNameFromEnum" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_GetHiddenAreaMesh,
    int
  >([=](ETrackingUniverseOrigin eOrigin, uint32_t uncbVREvent) {
    getOut() << "GetHiddenAreaMesh" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_GetControllerState,
    std::tuple<bool, vr::VRControllerState_t>,
    vr::TrackedDeviceIndex_t,
    uint32_t
  >([=](vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unControllerStateSize) {
    vr::VRControllerState_t state;
    auto result = vrsystem->GetControllerState(unControllerDeviceIndex, &state, unControllerStateSize);
    return std::tuple<bool, vr::VRControllerState_t>(result, state);
  });
  fnp.reg<
    kIVRSystem_GetControllerStateWithPose,
    std::tuple<bool, vr::VRControllerState_t, TrackedDevicePose_t>,
    vr::TrackedDeviceIndex_t,
    uint32_t
  >([=](vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unControllerStateSize) {
    vr::VRControllerState_t state;
    TrackedDevicePose_t pose;
    auto result = vrsystem->GetControllerStateWithPose(unControllerDeviceIndex, &state, unControllerStateSize, &pose);
    return std::tuple<bool, vr::VRControllerState_t, TrackedDevicePose_t>(result, state, pose);
  });
  fnp.reg<
    kIVRSystem_TriggerHapticPulse,
    int,
    vr::TrackedDeviceIndex_t,
    uint32_t,
    unsigned short
  >([=](vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) {
    vrsystem->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
    return 0;
  });
  fnp.reg<
    kIVRSystem_GetButtonIdNameFromEnum,
    int
  >([=]() {
    getOut() << "GetButtonIdNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_GetControllerAxisTypeNameFromEnum,
    int
  >([=]() {
    getOut() << "GetControllerAxisTypeNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_CaptureInputFocus,
    bool
  >([=]() {
    return vrsystem->CaptureInputFocus();
  });
  fnp.reg<
    kIVRSystem_ReleaseInputFocus,
    int
  >([=]() {
    vrsystem->ReleaseInputFocus();
    return 0;
  });
  fnp.reg<
    kIVRSystem_IsInputFocusCapturedByAnotherProcess,
    bool
  >([=]() {
    return vrsystem->IsInputFocusCapturedByAnotherProcess();
  });
  fnp.reg<
    kIVRSystem_DriverDebugRequest,
    int
  >([=]() {
    getOut() << "DriverDebugRequest abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRSystem_PerformFirmwareUpdate,
    vr::EVRFirmwareError,
    vr::TrackedDeviceIndex_t
  >([=](vr::TrackedDeviceIndex_t unDeviceIndex) {
    return vrsystem->PerformFirmwareUpdate(unDeviceIndex);
  });
}
void PVRSystem::GetRecommendedRenderTargetSize(uint32_t *pWidth, uint32_t *pHeight) {
  auto result = fnp.call<kIVRSystem_GetRecommendedRenderTargetSize, std::tuple<uint32_t, uint32_t>>();
  *pWidth = std::get<0>(result);
  *pHeight = std::get<1>(result);
}
HmdMatrix44_t PVRSystem::GetProjectionMatrix(EVREye eEye, float fNearZ, float fFarZ) {
  return fnp.call<
    kIVRSystem_GetProjectionMatrix,
    HmdMatrix44_t,
    EVREye,
    float,
    float
  >(eEye, fNearZ, fFarZ);
}
void PVRSystem::GetProjectionRaw(EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom) {
  auto result = fnp.call<
    kIVRSystem_GetProjectionRaw,
    std:tuple<float, float, float, float>,
    EVREye
  >(eEye);
  *pfLeft = std::get<0>(result);
  *pfRight = std::get<1>(result);
  *pfTop = std::get<2>(result);
  *pfBottom = std::get<3>(result);
}
bool PVRSystem::ComputeDistortion(EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates) {
  auto result = fnp.call<
    kIVRSystem_ComputeDistortion,
    std::tuple<bool, DistortionCoordinates_t>,
    EVREye,
    float,
    float
  >(eEye, fU, fV);
  *pDistortionCoordinates = std::get<1>(result);
  return std::get<0>(result);
}
HmdMatrix34_t PVRSystem::GetEyeToHeadTransform(EVREye eEye) {
  return fnp.call<
    kIVRSystem_GetEyeToHeadTransform,
    HmdMatrix34_t,
    EVREye
  >(eEye);
}
bool PVRSystem::GetTimeSinceLastVsync(float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter) {
  auto result = fnp.call<
    kIVRSystem_GetTimeSinceLastVsync,
    std::tuple<bool, float, uint64_t>
  >(eEye);
  *pfSecondsSinceLastVsync = std::get<1>(result);
  *pulFrameCounter = std::get<2>(result);
  return std::get<0>(result);
}
int32_t PVRSystem::GetD3D9AdapterIndex() {
  return fnp.call<
    kIVRSystem_GetD3D9AdapterIndex,
    int32_t
  >();
}
void PVRSystem::GetDXGIOutputInfo(int32_t *pnAdapterIndex) {
  auto result = fnp.call<
    kIVRSystem_GetDXGIOutputInfo,
    int32_t
  >();
  *pnAdapterIndex = result;
}
void PVRSystem::GetOutputDevice(uint64_t *pnDevice, ETextureType textureType, VkInstance_T *pInstance = nullptr) {
  getOut() << "GetOutputDevice abort" << std::endl;
  abort();
  return fnp.call<
    kIVRSystem_GetOutputDevice,
    int
  >();
}
bool PVRSystem::IsDisplayOnDesktop() {
  return fnp.call<
    kIVRSystem_IsDisplayOnDesktop,
    bool
  >();
}
bool PVRSystem::SetDisplayVisibility(bool bIsVisibleOnDesktop) {
  return fnp.call<
    kIVRSystem_SetDisplayVisibility,
    bool,
    bool
  >(bIsVisibleOnDesktop);
}
void PVRSystem::GetDeviceToAbsoluteTrackingPose(ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) {
  auto result = fnp.call<
    kIVRSystem_GetDeviceToAbsoluteTrackingPose,
    managed_binary<TrackedDevicePose_t>,
    ETrackingUniverseOrigin,
    float,
    uint32_t
  >(eOrigin, fPredictedSecondsToPhotonsFromNow, unTrackedDevicePoseArrayCount);
  memcopy(pTrackedDevicePoseArray, result.data(), result.size() * sizeof(TrackedDevicePose_t));
}
void PVRSystem::ResetSeatedZeroPose() {
  fnp.call<
    kIVRSystem_ResetSeatedZeroPose,
    managed_binary<TrackedDevicePose_t>,
    int
  >();
}
HmdMatrix34_t PVRSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
  return fnp.call<
    kIVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose,
    HmdMatrix34_t
  >();
}
HmdMatrix34_t PVRSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose() {
  return fnp.call<
    kIVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose,
    HmdMatrix34_t
  >();
}
uint32_t PVRSystem::GetSortedTrackedDeviceIndicesOfClass(ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd) {
  auto result = fnp.call<
    kIVRSystem_GetSortedTrackedDeviceIndicesOfClass,
    std::tuple<int32_t, managed_binary<vr::TrackedDeviceIndex_t>>,
    ETrackedDeviceClass,
    uint32_t,
    vr::TrackedDeviceIndex_t
  >(eTrackedDeviceClass, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
  memcpy(punTrackedDeviceIndexArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::TrackedDeviceIndex_t));
  return std::get<0>(result);
}
EDeviceActivityLevel PVRSystem::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) {
  return fnp.call<
    kIVRSystem_GetTrackedDeviceActivityLevel,
    EDeviceActivityLevel,
    vr::TrackedDeviceIndex_t
  >();
}
void PVRSystem::ApplyTransform(TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform) {
  auto result = fnp.call<
    kIVRSystem_ApplyTransform,
    TrackedDevicePose_t,
    TrackedDevicePose_t,
    HmdMatrix34_t
  >(*pTrackedDevicePose, *pTransform);
  *pOutputPose = result;
}
vr::TrackedDeviceIndex_t PVRSystem::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) {
  return fnp.call<
    kIVRSystem_GetTrackedDeviceIndexForControllerRole,
    vr::TrackedDeviceIndex_t,
    vr::ETrackedControllerRole
  >(unDeviceType);
}
vr::ETrackedControllerRole PVRSystem::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) {
  return fnp.call<
    kIVRSystem_GetControllerRoleForTrackedDeviceIndex,
    vr::ETrackedControllerRole,
    vr::TrackedDeviceIndex_t
  >(unDeviceIndex);
}
ETrackedDeviceClass PVRSystem::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex) {
  return fnp.call<
    kIVRSystem_GetTrackedDeviceClass,
    vr::ETrackedDeviceClass,
    vr::TrackedDeviceIndex_t
  >(unDeviceIndex);
}
bool PVRSystem::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex) {
  return fnp.call<
    kIVRSystem_IsTrackedDeviceConnected,
    bool,
    vr::TrackedDeviceIndex_t
  >(unDeviceIndex);
}
bool PVRSystem::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetBoolTrackedDeviceProperty,
    std::tuple<bool, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >(unDeviceIndex, prop);
  *pErrorL = std::get<1>(result);
  return std::get<0>(result);
}
float PVRSystem::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetFloatTrackedDeviceProperty,
    std::tuple<float, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >(unDeviceIndex, prop);
  *pErrorL = std::get<1>(result);
  return std::get<0>(result);
}
int32_t PVRSystem::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetInt32TrackedDeviceProperty,
    std::tuple<int32_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >(unDeviceIndex, prop);
  *pErrorL = std::get<1>(result);
  return std::get<0>(result);
}
uint64_t PVRSystem::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetUint64TrackedDeviceProperty,
    std::tuple<uint64_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >(unDeviceIndex, prop);
  *pErrorL = std::get<1>(result);
  return std::get<0>(result);
}
HmdMatrix34_t PVRSystem::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetMatrix34TrackedDeviceProperty,
    std::tuple<HmdMatrix34_t, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty
  >(unDeviceIndex, prop);
  *pErrorL = std::get<1>(result);
  return std::get<0>(result);
}
uint32_t PVRSystem::GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, void *pBuffer, uint32_t unBufferSize, ETrackedPropertyError *pError) {
  auto result = fnp.call<
    kIVRSystem_GetArrayTrackedDeviceProperty,
    std::tuple<uint32_t, managed_binary<unsigned char>, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty,
    PropertyTypeTag_t,
    uint32_t
  >(unDeviceIndex, prop, propType, unBufferSize);
  memcpy(pBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  *pError = std::get<2>(result);
  return std::get<0>(result);
}
uint32_t PVRSystem::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pErrorL) {
  auto result = fnp.call<
    kIVRSystem_GetStringTrackedDeviceProperty,
    std::tuple<uint32_t, managed_binary<char>, ETrackedPropertyError>,
    vr::TrackedDeviceIndex_t,
    ETrackedDeviceProperty,
    uint32_t
  >(unDeviceIndex, prop, unBufferSize);
  memcpy(pchValue, std::get<1>(result).data(), std::get<1>(result).size());
  *pError = std::get<2>(result);
  return std::get<0>(result);
}
const char *PVRSystem::GetPropErrorNameFromEnum(ETrackedPropertyError error) {
  return fnp.call<
    kIVRSystem_GetPropErrorNameFromEnum,
    int
  >();
}
bool PVRSystem::IsInputAvailable() {
  return fnp.call<
    kIVRSystem_IsInputAvailable,
    bool
  >();
}
bool PVRSystem::IsSteamVRDrawingControllers() {
  return fnp.call<
    kIVRSystem_IsSteamVRDrawingControllers,
    bool
  >();
}
bool PVRSystem::ShouldApplicationPause() {
  return fnp.call<
    kIVRSystem_ShouldApplicationPause,
    bool
  >();
}
bool PVRSystem::ShouldApplicationReduceRenderingWork() {
  return fnp.call<
    kIVRSystem_ShouldApplicationReduceRenderingWork,
    bool
  >();
}
bool PVRSystem::PollNextEvent(VREvent_t *pEvent, uint32_t uncbVREvent) {
  auto result = fnp.call<
    kIVRSystem_PollNextEvent,
    std::tuple<bool, VREvent_t>,
    uint32_t
  >(uncbVREvent);
  *pEvent = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRSystem::PollNextEventWithPose(ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose) {
  auto result = fnp.call<
    kIVRSystem_PollNextEventWithPose,
    std::tuple<bool, VREvent_t, vr::TrackedDevicePose_t>,
    ETrackingUniverseOrigin,
    uint32_t
  >(eOrigin, uncbVREvent);
  *pEvent = std::get<1>(result);
  *pTrackedDevicePose = std::get<2>(result);
  return std::get<0>(result);
}
const char *PVRSystem::GetEventTypeNameFromEnum(EVREventType eType) {
  getOut() << "GetEventTypeNameFromEnum abort" << std::endl;
  abort();
  return 0;
}
HiddenAreaMesh_t PVRSystem::GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard) {
  getOut() << "GetHiddenAreaMesh abort" << std::endl;
  abort();
  return 0;
}
bool PVRSystem::GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize) {
  auto result = fnp.call<
    kIVRSystem_GetControllerState,
    std::tuple<bool, vr::VRControllerState_t>,
    vr::TrackedDeviceIndex_t,
    uint32_t
  >(unControllerDeviceIndex, unControllerStateSize);
  *pControllerState = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRSystem::GetControllerStateWithPose(ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose) {
  auto result = fnp.call<
    kIVRSystem_GetControllerStateWithPose,
    std::tuple<bool, vr::VRControllerState_t, TrackedDevicePose_t>,
    ETrackingUniverseOrigin,
    vr::TrackedDeviceIndex_t,
    uint32_t
  >(eOrigin, unControllerDeviceIndex, unControllerStateSize);
  *pControllerState = std::get<1>(result);
  *pTrackedDevicePose = std::get<2>(result);
  return std::get<0>(result);
}
void PVRSystem::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) {
  fnp.call<
    kIVRSystem_TriggerHapticPulse,
    int,
    vr::TrackedDeviceIndex_t,
    uint32_t,
    unsigned short
  >(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
}
const char *PVRSystem::GetButtonIdNameFromEnum(EVRButtonId eButtonId) {
  getOut() << "GetButtonIdNameFromEnum abort" << std::endl;
  abort();
  return 0;
}
const char *PVRSystem::GetControllerAxisTypeNameFromEnum(EVRControllerAxisType eAxisType) {
  getOut() << "GetControllerAxisTypeNameFromEnum abort" << std::endl;
  abort();
  return 0;
}
bool PVRSystem::CaptureInputFocus() {
  return fnp.call<
    kIVRSystem_CaptureInputFocus,
    bool
  >();
}
void PVRSystem::ReleaseInputFocus() {
  fnp.call<
    kIVRSystem_ReleaseInputFocus,
    int
  >();
}
bool PVRSystem::IsInputFocusCapturedByAnotherProcess() {
  return fnp.call<
    kIVRSystem_IsInputFocusCapturedByAnotherProcess,
    bool
  >();
}
uint32_t PVRSystem::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize) {
  getOut() << "DriverDebugRequest abort" << std::endl;
  abort();
  return 0;
}
vr::EVRFirmwareError PVRSystem::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) {
  return fnp.call<
    kIVRSystem_PerformFirmwareUpdate,
    vr::EVRFirmwareError,
    vr::TrackedDeviceIndex_t
  >(unDeviceIndex);
}
void PVRSystem::AcknowledgeQuit_Exiting() {
  // XXX
}
void PVRSystem::AcknowledgeQuit_UserPrompt() {
  // XXX
}
uint32_t PVRSystem::GetAppContainerFilePaths(VR_OUT_STRING() char *pchBuffer, uint32_t unBufferSize) {
  // XXX
}
const char *PVRSystem::GetRuntimeVersion() {
  // XXX
}
DistortionCoordinates_t PVRSystem::ComputeDistortion(EVREye eEye, float fU, float fV) {
  // XXX
}
HmdMatrix44_t PVRSystem::GetProjectionMatrix(EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention convention) {
  // XXX
}
void PVRSystem::PerformanceTestEnableCapture(bool bEnable) {
  // XXX
}
void PVRSystem::PerformanceTestReportFidelityLevelChange(int nFidelityLevel) {
  // XXX
}
}