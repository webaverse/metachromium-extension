#include "stdafx.h"
#define BASE_IMPL
#include "BaseInput.h"
// #include <string>


#include "static_bases.gen.h"
#include "BaseClientCore.h"
#include "BaseSystem.h"
// #include <fstream>
// #include <codecvt>
// #include <iostream>
// #include "Drivers/Backend.h"
// #include <map>
// #include <thread>
/* Json::Value _actionManifest;
Json::Value _bindingsJson; */

using namespace std;
using namespace vr;

EVRInputError BaseInput::SetActionManifestPath(const char *pchActionManifestPath) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::SetActionManifestPath" << std::endl; });
  return g_pvrinput->SetActionManifestPath(pchActionManifestPath);
}
EVRInputError BaseInput::GetActionSetHandle(const char *pchActionSetName, VRActionSetHandle_t *pHandle) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetActionSetHandle" << std::endl; });
  auto result = g_pvrinput->GetActionSetHandle(pchActionSetName, pHandle);
  getOut() << "BaseInput::GetActionSetHandle result '" << pchActionSetName << "' " << (int)result << " " << (void *)*pHandle << std::endl;
  return result;
}
EVRInputError BaseInput::GetActionHandle(const char *pchActionName, VRActionHandle_t *pHandle) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetActionHandle" << std::endl; });
  auto result = g_pvrinput->GetActionHandle(pchActionName, pHandle);
  getOut() << "BaseInput::GetActionHandle result '" << pchActionName << "' " << (int)result << " " << (void *)*pHandle << std::endl;
  return result;
}
EVRInputError BaseInput::GetInputSourceHandle(const char *pchInputSourcePath, VRInputValueHandle_t *pHandle) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetInputSourceHandle" << std::endl; });
  auto result = g_pvrinput->GetInputSourceHandle(pchInputSourcePath, pHandle);
  getOut() << "BaseInput::GetInputSourceHandle result " << (int)result << " " << (void *)*pHandle << std::endl;
  return result;
}

/* void BaseInput::BuildActionSet(const ActionSet *actionSet) {
	return g_pvrinput->BuildActionSet(actionSet);
} */

EVRInputError BaseInput::UpdateActionState(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t *pSets,
	  uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::UpdateActionState" << std::endl; });
	return g_pvrinput->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount);
}

// helper method:
/* void BaseInput::ProcessInputSource(Json::Value inputJson, VRActionHandle_t actionHandle, string actionHandle,
	  string parameterSubMode, string actionSetName) {
  return g_pvrinput->ProcessInputSource(inputJson, actionHandle, actionHandle, parameterSubMode, actionSetName);
} */

// helper method
/* void BaseInput::DetermineActionState(uint64_t buttonId, uint64_t buttonFlags, bool pressedButtonState,
  	bool& masterPressedButtonState, vr::VRControllerAxis_t axis, double activateThreshold, double deactivateThreshold,
	  bool& bState, bool& bChanged, bool& actionSourceDirectionState) {
	return g_pvrinput->DetermineActionState(buttonId, buttonFlags, pressedButtonState, masterPressedButtonState, axis, activateThreshold, deactivateThreshold, bState, bChanged, actionSourceDirectionState);
} */

EVRInputError BaseInput::GetDigitalActionData(VRActionHandle_t action, InputDigitalActionData_t *pActionData, uint32_t unActionDataSize,
	  VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetDigitalActionData" << std::endl; });
	return g_pvrinput->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetAnalogActionData(VRActionHandle_t action, InputAnalogActionData_t *pActionData, uint32_t unActionDataSize,
	  VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetAnalogActionData" << std::endl; });
	return g_pvrinput->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetPoseActionData(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow,
	  InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetPoseActionData" << std::endl; });
  return BaseInput::GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice);
}

EVRInputError BaseInput::GetPoseActionDataRelativeToNow(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetPoseActionDataRelativeToNow" << std::endl; });
	return g_pvrinput->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetPoseActionDataForNextFrame(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetPoseActionDataForNextFrame" << std::endl; });
  auto result = g_pvrinput->GetPoseActionDataForNextFrame(action, eOrigin, pActionData, unActionDataSize, ulRestrictToDevice);
  getOut() << "get pose action data for next frame " << (void *)action << " " << result << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[0][0] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[0][1] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[0][2] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[0][3] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[1][0] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[1][1] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[1][2] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[1][3] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[2][0] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[2][1] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[2][2] << " " <<
    pActionData->pose.mDeviceToAbsoluteTracking.m[2][3] << " " <<
    std::endl;
  return result;
}
EVRInputError BaseInput::GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize,
	  VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalActionData" << std::endl; });
	return g_pvrinput->GetSkeletalActionData(action, pActionData, unActionDataSize);
}
EVRInputError BaseInput::GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalActionData" << std::endl; });
  return g_pvrinput->GetSkeletalActionData(action, pActionData, unActionDataSize);
}
EVRInputError BaseInput::GetBoneCount(VRActionHandle_t action, uint32_t* pBoneCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetBoneCount" << std::endl; });
	return g_pvrinput->GetBoneCount(action, pBoneCount);
}
EVRInputError BaseInput::GetBoneHierarchy(VRActionHandle_t action, VR_ARRAY_COUNT(unIndexArayCount) BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetBoneHierarchy" << std::endl; });
	return g_pvrinput->GetBoneHierarchy(action, pParentIndices, unIndexArayCount);
}
EVRInputError BaseInput::GetBoneName(VRActionHandle_t action, BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetBoneName" << std::endl; });
	return g_pvrinput->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize);
}
EVRInputError BaseInput::GetSkeletalReferenceTransforms(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalReferenceTransforms" << std::endl; });
	return g_pvrinput->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalTrackingLevel(VRActionHandle_t action, EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalTrackingLevel" << std::endl; });
	return g_pvrinput->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel);
}
EVRInputError BaseInput::GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
  	EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray,
	  uint32_t unTransformArrayCount, VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalBoneData 1" << std::endl; });
	return g_pvrinput->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
	  EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalBoneData 1" << std::endl; });
	return g_pvrinput->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalSummaryData(VRActionHandle_t action, EVRSummaryType eSummaryType, VRSkeletalSummaryData_t * pSkeletalSummaryData) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalSummaryData 1" << std::endl; });
	return g_pvrinput->GetSkeletalSummaryData(action, eSummaryType, pSkeletalSummaryData);
}
EVRInputError BaseInput::GetSkeletalSummaryData(VRActionHandle_t action, VRSkeletalSummaryData_t * pSkeletalSummaryData) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalSummaryData 2" << std::endl; });
  return GetSkeletalSummaryData(action, VRSummaryType_FromAnimation, pSkeletalSummaryData);
}
EVRInputError BaseInput::GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
	  EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize,
	  uint32_t *punRequiredCompressedSize, VRInputValueHandle_t ulRestrictToDevice) {
  getOut() << "abort BaseInput::GetSkeletalBoneDataCompressed" << std::endl; abort();
  return VRInputError_None;
  // return g_pvrinput->GetSkeletalBoneDataCompressed(action, eTransformSpace, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange,
	  VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetSkeletalBoneDataCompressed 2" << std::endl; });
	return g_pvrinput->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize);
}
EVRInputError BaseInput::DecompressSkeletalBoneData(void *pvCompressedBuffer, uint32_t unCompressedBufferSize,
	  EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray,
	  uint32_t unTransformArrayCount) {
  getOut() << "abort BaseInput::DecompressSkeletalBoneData" << std::endl; abort();
  return VRInputError_None;
  // return g_pvrinput->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, peTransformSpace, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::DecompressSkeletalBoneData(const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace eTransformSpace,
	  VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::DecompressSkeletalBoneData" << std::endl; });
	return g_pvrinput->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, eTransformSpace, pTransformArray, unTransformArrayCount);
}

EVRInputError BaseInput::TriggerHapticVibrationAction(VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds,
	  float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::TriggerHapticVibrationAction" << std::endl; });
  return g_pvrinput->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice);
}
EVRInputError BaseInput::GetActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle,
	  VR_ARRAY_COUNT(originOutCount) VRInputValueHandle_t *originsOut, uint32_t originOutCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetActionOrigins" << std::endl; });
  return g_pvrinput->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount);
}
EVRInputError BaseInput::GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize) {
  getOut() << "abort BaseInput::GetOriginLocalizedName" << std::endl; abort();
  return VRInputError_None;
	// return g_pvrinput->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize);
}
EVRInputError BaseInput::GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize,
	  int32_t unStringSectionsToInclude) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetOriginLocalizedName" << std::endl; });
	return g_pvrinput->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude);
}
EVRInputError BaseInput::GetOriginTrackedDeviceInfo(VRInputValueHandle_t origin, InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetOriginTrackedDeviceInfo" << std::endl; });
  auto result = g_pvrinput->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize);
  getOut() << "get origin tracked device info '" << pOriginInfo->rchRenderModelComponentName << "'" << std::endl;
  return result;
}

/** Retrieves useful information about the bindings for an action */
EVRInputError BaseInput::GetActionBindingInfo(VRActionHandle_t actionHandle, vr::InputBindingInfo_t *pOriginInfo,
		uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t *punReturnedBindingInfoCount) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::GetActionBindingInfo" << std::endl; });
  return g_pvrinput->GetActionBindingInfo(actionHandle, pOriginInfo, unBindingInfoSize, unBindingInfoCount, punReturnedBindingInfoCount);
}

/* void BaseInput::GetActionSourceBindingInfo(const Action *action,
		const ActionSource *src, vr::InputBindingInfo_t *result) {
  return g_pvrinput->GetActionSourceBindingInfo(action, src, result);
} */

EVRInputError BaseInput::ShowActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::ShowActionOrigins" << std::endl; });
	return g_pvrinput->ShowActionOrigins(actionSetHandle, ulActionHandle);
}
EVRInputError BaseInput::ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t,
	  uint32_t unSetCount, VRInputValueHandle_t originToHighlight) {
  TRACE("BaseInput", []() { getOut() << "BaseInput::ShowBindingsForActionSet" << std::endl; });
  return g_pvrinput->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight);
}

bool BaseInput::IsUsingLegacyInput() {
  TRACE("BaseInput", []() { getOut() << "BaseInput::IsUsingLegacyInput" << std::endl; });
	return g_pvrinput->IsUsingLegacyInput();
}
