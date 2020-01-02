// #include <chrono>
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRInput_SetActionManifestPath[] = "Input::SetActionManifestPath";
char kIVRInput_GetActionSetHandle[] = "Input::GetActionSetHandle";
char kIVRInput_GetInputSourceHandle[] = "Input::GetInputSourceHandle";
char kIVRInput_UpdateActionState[] = "Input::UpdateActionState";
char kIVRInput_GetDigitalActionData[] = "Input::GetDigitalActionData";
char kIVRInput_GetAnalogActionData[] = "Input::GetAnalogActionData";
char kIVRInput_GetPoseActionData[] = "Input::GetPoseActionData";
char kIVRInput_GetPoseActionDataRelativeToNow[] = "Input::GetPoseActionDataRelativeToNow";
char kIVRInput_GetPoseActionDataForNextFrame[] = "Input::GetPoseActionDataForNextFrame";
char kIVRInput_GetSkeletalActionData[] = "Input::GetSkeletalActionData";
char kIVRInput_GetSkeletalActionData[] = "Input::GetSkeletalActionData";
char kIVRInput_GetBoneCount[] = "Input::GetBoneCount";
char kIVRInput_GetBoneHierarchy[] = "Input::GetBoneHierarchy";
char kIVRInput_GetBoneName[] = "Input::GetBoneName";
char kIVRInput_GetSkeletalReferenceTransforms[] = "Input::GetSkeletalReferenceTransforms";
char kIVRInput_GetSkeletalTrackingLevel[] = "Input::GetSkeletalTrackingLevel";
char kIVRInput_GetSkeletalBoneData[] = "Input::GetSkeletalBoneData";
char kIVRInput_GetSkeletalBoneData[] = "Input::GetSkeletalBoneData";
char kIVRInput_GetSkeletalSummaryData[] = "Input::GetSkeletalSummaryData";
char kIVRInput_GetSkeletalBoneDataCompressed[] = "Input::GetSkeletalBoneDataCompressed";
char kIVRInput_DecompressSkeletalBoneData[] = "Input::DecompressSkeletalBoneData";
char kIVRInput_TriggerHapticVibrationAction[] = "Input::TriggerHapticVibrationAction";
char kIVRInput_GetActionOrigins[] = "Input::GetActionOrigins";
char kIVRInput_GetOriginLocalizedName[] = "Input::GetOriginLocalizedName";
char kIVRInput_GetOriginLocalizedName[] = "Input::GetOriginLocalizedName";
char kIVRInput_GetOriginTrackedDeviceInfo[] = "Input::GetOriginTrackedDeviceInfo";
char kIVRInput_GetActionBindingInfo[] = "Input::GetActionBindingInfo";
char kIVRInput_ShowActionOrigins[] = "Input::ShowActionOrigins";
char kIVRInput_ShowBindingsForActionSet[] = "Input::ShowBindingsForActionSet";
char kIVRInput_IsUsingLegacyInput[] = "Input::IsUsingLegacyInput";

PVRInput::PVRInput(IVRInput *vrinput, FnProxy &fnp) : vrinput(vrinput), fnp(fnp) {
  fnp.reg<
    kIVRCompositor_SetActionManifestPath,
    vr::EVRInputError,
    managed_binary<char>
  >([=](managed_binary<char> actionManifestPath) {
    return vrinput->SetActionManifestPath(actionManifestPath.data());
  });
  fnp.reg<
    kIVRInput_GetActionSetHandle,
    std::tuple<vr::EVRInputError, VRActionSetHandle_t>,
    managed_binary<char>
  >([=](managed_binary<char> actionSetName) {
    VRActionSetHandle_t handle;
    auto result = vrinput->GetActionSetHandle(actionSetName.data(), &handle);
    return std::tuple<vr::EVRInputError, VRActionSetHandle_t>(
      result,
      handle
    );
  });
  fnp.reg<
    kIVRInput_GetActionHandle,
    std::tuple<vr::EVRInputError, VRActionHandle_t>,
    managed_binary<char>
  >([=](managed_binary<char> actionName) {
    VRActionHandle_t handle;
    auto result = vrinput->GetActionHandle(actionName.data(), &handle);
    return std::tuple<vr::EVRInputError, VRActionHandle_t>(
      result,
      handle
    );
  });
  fnp.reg<
    kIVRInput_GetInputSourceHandle,
    std::tuple<vr::EVRInputError, VRInputValueHandle_t>,
    managed_binary<char>
  >([=](managed_binary<char> inputSource) {
    VRInputValueHandle_t handle;
    auto result = vrinput->GetInputSourceHandle(inputSource.data(), &handle);
    return std::tuple<vr::EVRInputError, VRInputValueHandle_t>(
      result,
      handle
    );
  });
  fnp.reg<
    kIVRInput_UpdateActionState,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) {
    managed_binary<vr::VRActiveActionSet_t> actionSets(unSetCount);
    auto result = vrinput->UpdateActionState(actionSets.data(), unSizeOfVRSelectedActionSet_t, unSetCount);
    return std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>>(
      result,
      std::move(actionSets)
    );
  });
  fnp.reg<
    kIVRInput_GetDigitalActionData,
    std::tuple<vr::EVRInputError, vr::InputDigitalActionData_t>,
    VRActionHandle_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](VRActionHandle_t action, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
    vr::InputDigitalActionData_t actionData;
    auto result = vrinput->GetDigitalActionData(action, &actionData, unActionDataSize, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, vr::InputDigitalActionData_t>>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetAnalogActionData,
    std::tuple<vr::EVRInputError, vr::InputAnalogActionData_t>,
    VRActionHandle_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](VRActionHandle_t action, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
    vr::InputAnalogActionData_t actionData;
    auto result = vrinput->GetAnalogActionData(action, &actionData, unActionDataSize, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, vr::InputAnalogActionData_t>>(
      result,
      actionData
    );
  });
}
vr::EVRInputError PVRInput::SetActionManifestPath(const char *pchActionManifestPath) {
  managed_binary<char> actionManifestPath(strlen(pchActionManifestPath) + 1);
  memcpy(actionManifestPath.data(), pchActionManifestPath, actionManifestPath.size());
  return fnp.call<
    kIVRInput_SetActionManifestPath,
    vr::EVRInputError,
    managed_binary<char>
  >(std::move(actionManifestPath));
}
vr::EVRInputError PVRInput::GetActionSetHandle(const char *pchActionSetName, vr::VRActionSetHandle_t *pHandle) {
  managed_binary<char> actionSetName(strlen(pchActionSetName) + 1);
  memcpy(actionSetName.data(), pchActionSetName, actionSetName.size());
  auto result = fnp.call<
    kIVRInput_GetActionSetHandle,
    std::tuple<vr::EVRInputError, VRActionSetHandle_t>,
    managed_binary<char>
  >(std::move(actionSetName));
  *pHandle = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetActionHandle(const char *pchActionName, vr::VRActionHandle_t *pHandle) {
  managed_binary<char> actionName(strlen(pchActionName) + 1);
  memcpy(actionName.data(), pchActionName, actionName.size());
  auto result = fnp.call<
    kIVRInput_GetActionHandle,
    std::tuple<vr::EVRInputError, VRActionHandle_t>,
    managed_binary<char>
  >(std::move(actionSetName));
  *pHandle = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetInputSourceHandle(const char *pchInputSourcePath, vr::VRInputValueHandle_t *pHandle) {
  managed_binary<char> inputSource(strlen(pchInputSourcePath) + 1);
  memcpy(inputSource.data(), pchInputSourcePath, inputSource.size());
  auto result = fnp.call<
    kIVRInput_GetInputSourceHandle,
    std::tuple<vr::EVRInputError, VRInputValueHandle_t>,
    managed_binary<char>
  >(std::move(inputSource));
  *pHandle = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::UpdateActionState(VR_ARRAY_COUNT(unSetCount) vr::VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) {
  auto result = fnp.call<
    kIVRInput_UpdateActionState,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>>,
    uint32_t,
    uint32_t
  >(unSizeOfVRSelectedActionSet_t, unSetCount);
  memcpy(pSets, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(VRActiveActionSet_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetDigitalActionData(vr::VRActionHandle_t action, vr::InputDigitalActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetDigitalActionData,
    std::tuple<vr::EVRInputError, managed_binary<vr::InputDigitalActionData_t>>,
    vr::VRActionHandle_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, unActionDataSize, ulRestrictToDevice);
  memcpy(pActionData, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(InputDigitalActionData_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetAnalogActionData(vr::VRActionHandle_t action, vr::InputAnalogActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetAnalogActionData,
    std::tuple<vr::EVRInputError, managed_binary<vr::InputAnalogActionData_t>>,
    vr::VRActionHandle_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, unActionDataSize, ulRestrictToDevice);
  memcpy(pActionData, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(InputAnalogActionData_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize);
vr::EVRInputError PVRInput::GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount);
vr::EVRInputError PVRInput::GetBoneHierarchy(vr::VRActionHandle_t action, VR_ARRAY_COUNT(unIndexArayCount) vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount);
vr::EVRInputError PVRInput::GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize);
vr::EVRInputError PVRInput::GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
vr::EVRInputError PVRInput::GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel);
vr::EVRInputError PVRInput::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
vr::EVRInputError PVRInput::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::EVRSummaryType eSummaryType, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData);
vr::EVRInputError PVRInput::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData);
vr::EVRInputError PVRInput::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize);
vr::EVRInputError PVRInput::DecompressSkeletalBoneData(void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
vr::EVRInputError PVRInput::DecompressSkeletalBoneData(const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace eTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
vr::EVRInputError PVRInput::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice);
vr::EVRInputError PVRInput::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT(originOutCount) vr::VRInputValueHandle_t *originsOut, uint32_t originOutCount);
vr::EVRInputError PVRInput::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize);
vr::EVRInputError PVRInput::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude);
vr::EVRInputError PVRInput::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize);
vr::EVRInputError PVRInput::GetActionBindingInfo(vr::VRActionHandle_t action, vr::InputBindingInfo_t *pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t *punReturnedBindingInfoCount);
vr::EVRInputError PVRInput::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle);
vr::EVRInputError PVRInput::ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) vr::VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight);
bool PVRInput::IsUsingLegacyInput() {
  getOut() << "IsUsingLegacyInput" << std::endl;
  return false;
}
}