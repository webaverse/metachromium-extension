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
char kIVRInput_GetSkeletalSummaryData[] = "Input::GetSkeletalSummaryData";
char kIVRInput_GetSkeletalBoneDataCompressed[] = "Input::GetSkeletalBoneDataCompressed";
char kIVRInput_DecompressSkeletalBoneData[] = "Input::DecompressSkeletalBoneData";
char kIVRInput_TriggerHapticVibrationAction[] = "Input::TriggerHapticVibrationAction";
char kIVRInput_GetActionOrigins[] = "Input::GetActionOrigins";
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
    return std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>(
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
    return std::tuple<vr::EVRInputError, vr::InputDigitalActionData_t>(
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
    return std::tuple<vr::EVRInputError, vr::InputAnalogActionData_t>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetPoseActionData,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    float,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
    vr::InputPoseActionData_t actionData;
    auto result = vrinput->GetPoseActionData(action, &actionData, unActionDataSize, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetPoseActionDataRelativeToNow,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    float,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
    vr::InputPoseActionData_t actionData;
    auto result = vrinput->GetPoseActionDataRelativeToNow(action, &actionData, unActionDataSize, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetPoseActionDataForNextFrame,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
    vr::InputPoseActionData_t actionData;
    auto result = vrinput->GetPoseActionDataForNextFrame(action, eOrigin, &actionData, unActionDataSize, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalActionData,
    std::tuple<vr::EVRInputError, vr::InputSkeletalActionData_t>,
    vr::VRActionHandle_t,
    uint32_t
  >([=](vr::VRActionHandle_t action, uint32_t unActionDataSize) {
    vr::InputSkeletalActionData_t actionData;
    auto result = vrinput->GetSkeletalActionData(action, &actionData, unActionDataSize);
    return std::tuple<vr::EVRInputError, vr::InputSkeletalActionData_t>(
      result,
      actionData
    );
  });
  fnp.reg<
    kIVRInput_GetBoneCount,
    std::tuple<vr::EVRInputError, uint32_t>,
    vr::VRActionHandle_t
  >([=](vr::VRActionHandle_t action) {
    uint32_t boneCount;
    auto result = vrinput->GetBoneCount(action, &boneCount);
    return std::tuple<vr::EVRInputError, uint32_t>(
      result,
      boneCount
    );
  });
  fnp.reg<
    kIVRInput_GetBoneHierarchy,
    std::tuple<vr::EVRInputError, managed_binary<vr::BoneIndex_t>>,
    vr::VRActionHandle_t,
    uint32_t
  >([=](vr::VRActionHandle_t action, uint32_t unIndexArayCount) {
    uint32_t boneCount;
    managed_binary<vr::BoneIndex_t> parentIndices(unIndexArayCount);
    auto result = vrinput->GetBoneHierarchy(action, parentIndices.data(), unIndexArayCount);
    return std::tuple<vr::EVRInputError, managed_binary<vr::BoneIndex_t>>(
      result,
      std::move(parentIndices)
    );
  });
  fnp.reg<
    kIVRInput_GetBoneName,
    std::tuple<vr::EVRInputError, managed_binary<char>>,
    vr::VRActionHandle_t,
    vr::BoneIndex_t,
    uint32_t
  >([=](vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, uint32_t unNameBufferSize) {
    managed_binary<char> boneName(unNameBufferSize);
    auto result = vrinput->GetBoneName(action, nBoneIndex, boneName.data(), unNameBufferSize);
    return std::tuple<vr::EVRInputError, managed_binary<char>>(
      result,
      std::move(boneName)
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalReferenceTransforms,
    std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>,
    vr::VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    vr::EVRSkeletalReferencePose,
    uint32_t
  >([=](vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalReferencePose eReferencePose, uint32_t unTransformArrayCount) {
    managed_binary<VRBoneTransform_t> transformArray(unTransformArrayCount);
    auto result = vrinput->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, transformArray.data(), unTransformArrayCount);
    return std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>(
      result,
      std::move(transformArray)
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalTrackingLevel,
    std::tuple<vr::EVRInputError, EVRSkeletalTrackingLevel>
  >([=]() {
    EVRSkeletalTrackingLevel skeletalTrackingLevel;
    auto result = vrinput->GetSkeletalTrackingLevel(&skeletalTrackingLevel);
    return std::tuple<vr::EVRInputError, EVRSkeletalTrackingLevel>(
      result,
      skeletalTrackingLevel
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalBoneData,
    std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>,
    vr::VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    vr::EVRSkeletalMotionRange,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice) {
    managed_binary<VRBoneTransform_t> transformArray(unTransformArrayCount);
    auto result = vrinput->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, transformArray.data(), unTransformArrayCount, ulRestrictToDevice);
    return std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>(
      result,
      std::move(transformArray)
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalSummaryData,
    std::tuple<vr::EVRInputError, VRSkeletalSummaryData_t>,
    vr::VRActionHandle_t,
    vr::EVRSummaryType
  >([=](vr::VRActionHandle_t action, vr::EVRSummaryType eSummaryType) {
    VRSkeletalSummaryData_t skeletalSummaryData;
    auto result = vrinput->GetSkeletalBoneData(action, eSummaryType, &skeletalSummaryData);
    return std::tuple<vr::EVRInputError, VRSkeletalSummaryData_t>(
      result,
      skeletalSummaryData
    );
  });
  fnp.reg<
    kIVRInput_GetSkeletalBoneDataCompressed,
    std::tuple<vr::EVRInputError, managed_binary<unsigned char>, uint32_t>,
    VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    EVRSkeletalMotionRange,
    uint32_t
  >([=](vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, uint32_t unCompressedSize) {
    managed_binary<unsigned char> compressedData(unCompressedSize);
    uint32_t unRequiredCompressedSize;
    auto result = vrinput->GetSkeletalBoneDataCompressed(action, eTransformSpace, eMotionRange, compressedData.data(), unCompressedSize, &unRequiredCompressedSize);
    return std::tuple<vr::EVRInputError, managed_binary<unsigned char>, uint32_t>(
      result,
      std::move(compressedData),
      unRequiredCompressedSize
    );
  });
  fnp.reg<
    kIVRInput_DecompressSkeletalBoneData,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRBoneTransform_t>>,
    std::managed_binary<unsigned char>,
    uint32_t,
    vr::EVRSkeletalTransformSpace,
    uint32_t
  >([=](std::managed_binary<unsigned char> compressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace eTransformSpace, uint32_t unTransformArrayCount) {
    managed_binary<unsigned char> transformArray(unTransformArrayCount);
    auto result = vrinput->DecompressSkeletalBoneData(compressedBuffer.data(), unCompressedBufferSize, eTransformSpace, transformArray.data(), unTransformArrayCount);
    return std::tuple<vr::EVRInputError, managed_binary<vr::VRBoneTransform_t>>(
      result,
      std::move(transformArray)
    );
  });
  fnp.reg<
    kIVRInput_TriggerHapticVibrationAction,
    vr::EVRInputError,
    vr::VRActionHandle_t,
    float,
    float,
    float,
    vr::VRInputValueHandle_t
  >([=](vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) {
    return vrinput->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice);
  });
  fnp.reg<
    kIVRInput_GetActionOrigins,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRInputValueHandle_t>>,
    vr::VRActionSetHandle_t,
    vr::VRActionHandle_t,
    uint32_t
  >([=](vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, uint32_t originOutCount) {
    managed_binary<vr::VRInputValueHandle_t> originsOut(originOutCount);
    auto result = vrinput->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut.data(), originOutCount);
    return std::tuple<vr::EVRInputError, managed_binary<vr::VRBoneTransform_t>>(
      result,
      std::move(originsOut)
    );
  });
  fnp.reg<
    kIVRInput_GetOriginLocalizedName,
    std::tuple<vr::EVRInputError, managed_binary<char>>,
    VRInputValueHandle_t,
    uint32_t,
    int32_t,
  >([=](VRInputValueHandle_t origin, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) {
    managed_binary<char> nameArray(unNameArraySize);
    auto result = vrinput->GetOriginLocalizedName(origin, nameArray.data(), unNameArraySize, unStringSectionsToInclude);
    return std::tuple<vr::EVRInputError, managed_binary<char>>(
      result,
      std::move(nameArray)
    );
  });
  fnp.reg<
    kIVRInput_GetOriginTrackedDeviceInfo,
    std::tuple<vr::EVRInputError, InputOriginInfo_t>
    vr::VRActionHandle_t,
    uint32_t
  >([=](vr::VRInputValueHandle_t origin, vr::InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize) {
     vr::InputOriginInfo_t originInfo;
    auto result = vrinput->GetOriginTrackedDeviceInfo(origin, &originInfo, unOriginInfoSize);
    return std::tuple<vr::EVRInputError, InputOriginInfo_t>(
      result,
      originInfo
    );
  });
  fnp.reg<
    kIVRInput_GetActionBindingInfo,
    std::tuple<vr::EVRInputError, managed_binary<vr::InputBindingInfo_t>, uint32_t>
    vr::VRActionHandle_t,
    uint32_t,
    uint32_t
  >([=](vr::VRActionHandle_t action, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount) {
    managed_binary<vr::InputOriginInfo_t> originInfo(unBindingInfoCount);
    uint32_t unReturnedBindingInfoCount;
    auto result = vrinput->GetActionBindingInfo(action, originInfo.data(), unBindingInfoSize, unBindingInfoCount, &unReturnedBindingInfoCount);
    return std::tuple<vr::EVRInputError, InputOriginInfo_t>(
      result,
      std::move(originInfo),
      unReturnedBindingInfoCount
    );
  });
  fnp.reg<
    kIVRInput_ShowActionOrigins,
    vr::EVRInputError,
    vr::VRActionSetHandle_t,
    vr::VRActionHandle_t
  >([=](vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) {
    return vrinput->ShowActionOrigins(actionSetHandle, ulActionHandle);
  });
  fnp.reg<
    kIVRInput_ShowBindingsForActionSet,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>>,
    uint32_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >([=](uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) {
    managed_binary<vr::VRActiveActionSet_t> sets(unSetCount);
    auto result = vrinput->ShowActionOrigins(sets.data(), unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight);
    return std::tuple<vr::EVRInputError, InputOriginInfo_t>(
      result,
      std::move(sets)
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
    std::tuple<vr::EVRInputError, vr::InputDigitalActionData_t>,
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
    std::tuple<vr::EVRInputError, vr::InputAnalogActionData_t>,
    vr::VRActionHandle_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, unActionDataSize, ulRestrictToDevice);
  memcpy(pActionData, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(InputAnalogActionData_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetPoseActionData,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    float,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, eOrigin, fPredictedSecondsFromNow, unActionDataSize, ulRestrictToDevice);
  *pActionData = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetPoseActionDataRelativeToNow,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    float,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, eOrigin, fPredictedSecondsFromNow, unActionDataSize, ulRestrictToDevice);
  *pActionData = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetPoseActionDataForNextFrame,
    std::tuple<vr::EVRInputError, vr::InputPoseActionData_t>,
    vr::VRActionHandle_t,
    vr::ETrackingUniverseOrigin,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, eOrigin, unActionDataSize, ulRestrictToDevice);
  *pActionData = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  return GetSkeletalActionData(action, pActionData, unActionDataSize);
}
vr::EVRInputError PVRInput::GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalActionData,
    std::tuple<vr::EVRInputError, vr::InputSkeletalActionData_t>,
    vr::VRActionHandle_t,
    uint32_t
  >(action, unActionDataSize);
  *pActionData = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount) {
  auto result = fnp.call<
    kIVRInput_GetBoneCount,
    std::tuple<vr::EVRInputError, uint32_t>,
    vr::VRActionHandle_t
  >(action);
  *pBoneCount = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetBoneHierarchy(vr::VRActionHandle_t action, VR_ARRAY_COUNT(unIndexArayCount) vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) {
  auto result = fnp.call<
    kIVRInput_GetBoneHierarchy,
    std::tuple<vr::EVRInputError, managed_binary<vr::BoneIndex_t>>,
    vr::VRActionHandle_t,
    uint32_t
  >(action, unIndexArayCount);
  memcpy(pParentIndices, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::BoneIndex_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize) {
  auto result = fnp.call<
    kIVRInput_GetBoneName,
    std::tuple<vr::EVRInputError, managed_binary<char>>,
    vr::VRActionHandle_t,
    vr::BoneIndex_t,
    uint32_t
  >(action, nBoneIndex, unNameBufferSize);
  memcpy(pchBoneName, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalReferenceTransforms,
    std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>,
    vr::VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    vr::EVRSkeletalReferencePose,
    uint32_t
  >(action, eTransformSpace, eReferencePose, unTransformArrayCount);
  memcpy(pTransformArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(VRBoneTransform_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalTrackingLevel,
    std::tuple<vr::EVRInputError, EVRSkeletalTrackingLevel>
  >();
  *pSkeletalTrackingLevel = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice) {
  return GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount);
}
vr::EVRInputError PVRInput::GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalBoneData,
    std::tuple<vr::EVRInputError, managed_binary<VRBoneTransform_t>>,
    vr::VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    vr::EVRSkeletalMotionRange,
    uint32_t,
    vr::VRInputValueHandle_t
  >(action, eTransformSpace, eMotionRange, unTransformArrayCount, ulRestrictToDevice);
  memcpy(pTransformArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(VRBoneTransform_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::EVRSummaryType eSummaryType, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalSummaryData,
    std::tuple<vr::EVRInputError, VRSkeletalSummaryData_t>,
    vr::VRActionHandle_t,
    vr::EVRSummaryType
  >(action, eSummaryType);
  *pSkeletalSummaryData = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData) {
  return GetSkeletalSummaryData(action, vr::EVRSummaryType::VRSummaryType_FromAnimation, pSkeletalSummaryData);
}
vr::EVRInputError PVRInput::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice) {
  auto result = fnp.call<
    kIVRInput_GetSkeletalBoneDataCompressed,
    std::tuple<vr::EVRInputError, managed_binary<unsigned char>, uint32_t>,
    VRActionHandle_t,
    vr::EVRSkeletalTransformSpace,
    EVRSkeletalMotionRange,
    uint32_t
  >(action, eTransformSpace, eMotionRange, unCompressedSize);
  memcpy(pvCompressedData, std::get<1>(result).data(), std::get<1>(result).size());
  *punRequiredCompressedSize = std::get<2>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize) {
  return GetSkeletalBoneDataCompressed(action, vr::EVRSkeletalTransformSpace::VRSkeletalTransformSpace_Model, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize, 0);
}
vr::EVRInputError PVRInput::DecompressSkeletalBoneData(void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, peTransformSpace, pTransformArray, unTransformArrayCount);
}
vr::EVRInputError PVRInput::DecompressSkeletalBoneData(const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace eTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  std::managed_binary<unsigned char> compressedBuffer(pvCompressedBuffer, unCompressedBufferSize);
  auto result = fnp.call<
    kIVRInput_DecompressSkeletalBoneData,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRBoneTransform_t>>,
    std::managed_binary<unsigned char>,
    uint32_t,
    vr::EVRSkeletalTransformSpace,
    uint32_t
  >(std::move(compressedBuffer), unCompressedBufferSize, unTransformArrayCount);
  memcpy(pTransformArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::VRBoneTransform_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice) {
  return fnp.call<
    kIVRInput_TriggerHapticVibrationAction,
    vr::EVRInputError,
    vr::VRActionHandle_t,
    float,
    float,
    float,
    vr::VRInputValueHandle_t
  >(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice);
}
vr::EVRInputError PVRInput::GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT(originOutCount) vr::VRInputValueHandle_t *originsOut, uint32_t originOutCount) {
  auto result = fnp.call<
    kIVRInput_GetActionOrigins,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRInputValueHandle_t>>,
    vr::VRActionSetHandle_t,
    vr::VRActionHandle_t,
    uint32_t
  >(actionSetHandle, digitalActionHandle, originOutCount);
  memcpy(originsOut, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::VRInputValueHandle_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize) {
  return GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, vr::EVRInputStringBits::VRInputString_All);
}
vr::EVRInputError PVRInput::GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude) {
  auto result = fnp.call<
    kIVRInput_GetOriginLocalizedName,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRInputValueHandle_t>>,
    vr::VRActionSetHandle_t,
    vr::VRActionHandle_t,
    uint32_t,
    int32_t
  >(actionSetHandle, digitalActionHandle, originOutCount, unStringSectionsToInclude);
  memcpy(originsOut, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::VRInputValueHandle_t));
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize) {
  auto result = fnp.call<
    kIVRInput_GetOriginTrackedDeviceInfo,
    std::tuple<vr::EVRInputError, InputOriginInfo_t>
    vr::VRActionHandle_t,
    uint32_t
  >(origin, unOriginInfoSize);
  *pOriginInfo = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::GetActionBindingInfo(vr::VRActionHandle_t action, vr::InputBindingInfo_t *pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t *punReturnedBindingInfoCount) {
  auto result = fnp.call<
    kIVRInput_GetActionBindingInfo,
    std::tuple<vr::EVRInputError, managed_binary<vr::InputBindingInfo_t>, uint32_t>,
    vr::VRActionHandle_t,
    uint32_t,
    uint32_t
  >(origin, unBindingInfoSize, unBindingInfoCount);
  memcpy(pOriginInfo, std::get<1>(result).data(), std::get<0>(result).size() * sizeof(vr::InputBindingInfo_t));
  *punReturnedBindingInfoCount = std::get<2>(result);
  return std::get<0>(result);
}
vr::EVRInputError PVRInput::ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle) {
  return fnp.call<
    kIVRInput_ShowActionOrigins,
    vr::EVRInputError,
    vr::VRActionSetHandle_t,
    vr::VRActionHandle_t
  >(actionSetHandle, ulActionHandle);
}
vr::EVRInputError PVRInput::ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) vr::VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight) {
  auto result = fnp.call<
    kIVRInput_ShowBindingsForActionSet,
    std::tuple<vr::EVRInputError, managed_binary<vr::VRActiveActionSet_t>>,
    uint32_t,
    uint32_t,
    vr::VRInputValueHandle_t
  >(actionSetHandle, ulActionHandle);
  memcpy(pSets, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::VRActiveActionSet_t));
  return std::get<0>(result);
}
bool PVRInput::IsUsingLegacyInput() {
  getOut() << "IsUsingLegacyInput" << std::endl;
  return false;
}
}