#include "stdafx.h"
#define BASE_IMPL
#include "BaseInput.h"
#include <string>


#include "static_bases.gen.h"
#include "BaseClientCore.h"
#include "BaseSystem.h"
#include <fstream>
#include <codecvt>
#include <iostream>
// #include "Drivers/Backend.h"
// #include <map>
#include <thread>
/* Json::Value _actionManifest;
Json::Value _bindingsJson; */

using namespace std;
using namespace vr;

EVRInputError BaseInput::SetActionManifestPath(const char *pchActionManifestPath) {
  return g_vrinput->SetActionManifestPath(pchActionManifestPath);
}
EVRInputError BaseInput::GetActionSetHandle(const char *pchActionSetName, VRActionSetHandle_t *pHandle) {
  return g_vrinput->GetActionSetHandle(pchActionSetName, pHandle);
}
EVRInputError BaseInput::GetActionHandle(const char *pchActionName, VRActionHandle_t *pHandle) {
  return g_vrinput->GetActionHandle(pchActionName, pHandle);
}
EVRInputError BaseInput::GetInputSourceHandle(const char *pchInputSourcePath, VRInputValueHandle_t  *pHandle) {
  return g_vrinput->GetInputSourceHandle(pchInputSourcePath, pHandle);
}

/*  void BaseInput::BuildActionSet(const ActionSet *actionSet) {
	return g_vrinput->BuildActionSet(actionSet);
} */

EVRInputError BaseInput::UpdateActionState(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t *pSets,
	uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) {
	return g_vrinput->UpdateActionState(pSets, unSizeOfVRSelectedActionSet_t, unSetCount);
}

// helper method:
/* void BaseInput::ProcessInputSource(Json::Value inputJson, VRActionHandle_t actionHandle, string actionHandle,
	  string parameterSubMode, string actionSetName) {
  return g_vrinput->ProcessInputSource(inputJson, actionHandle, actionHandle, parameterSubMode, actionSetName);
} */

// helper method
/* void BaseInput::DetermineActionState(uint64_t buttonId, uint64_t buttonFlags, bool pressedButtonState,
  	bool& masterPressedButtonState, vr::VRControllerAxis_t axis, double activateThreshold, double deactivateThreshold,
	  bool& bState, bool& bChanged, bool& actionSourceDirectionState) {
	return g_vrinput->DetermineActionState(buttonId, buttonFlags, pressedButtonState, masterPressedButtonState, axis, activateThreshold, deactivateThreshold, bState, bChanged, actionSourceDirectionState);
} */

EVRInputError BaseInput::GetDigitalActionData(VRActionHandle_t action, InputDigitalActionData_t *pActionData, uint32_t unActionDataSize,
	  VRInputValueHandle_t ulRestrictToDevice) {
	return g_vrinput->GetDigitalActionData(action, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetAnalogActionData(VRActionHandle_t action, InputAnalogActionData_t *pActionData, uint32_t unActionDataSize,
	   VRInputValueHandle_t ulRestrictToDevice) {
	return g_vrinput->GetAnalogActionData(action, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetPoseActionData(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow,
	  InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
  return BaseInput::GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice);
}

EVRInputError BaseInput::GetPoseActionDataRelativeToNow(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
	return g_vrinput->GetPoseActionDataRelativeToNow(action, eOrigin, fPredictedSecondsFromNow, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetPoseActionDataForNextFrame(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, InputPoseActionData_t *pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) {
  return g_vrinput->GetPoseActionDataForNextFrame(action, eOrigin, pActionData, unActionDataSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize,
	  VRInputValueHandle_t ulRestrictToDevice) {
	return g_vrinput->GetSkeletalActionData(action, pActionData, unActionDataSize);
}
EVRInputError BaseInput::GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize) {
  return g_vrinput->GetSkeletalActionData(action, pActionData, unActionDataSize);
}
EVRInputError BaseInput::GetBoneCount(VRActionHandle_t action, uint32_t* pBoneCount) {
	return g_vrinput->GetBoneCount(action, pBoneCount);
}
EVRInputError BaseInput::GetBoneHierarchy(VRActionHandle_t action, VR_ARRAY_COUNT(unIndexArayCount) BoneIndex_t* pParentIndices, uint32_t unIndexArayCount) {
	return g_vrinput->GetBoneHierarchy(action, pParentIndices, unIndexArayCount);
}
EVRInputError BaseInput::GetBoneName(VRActionHandle_t action, BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize) {
	return g_vrinput->GetBoneName(action, nBoneIndex, pchBoneName, unNameBufferSize);
}
EVRInputError BaseInput::GetSkeletalReferenceTransforms(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
	return g_vrinput->GetSkeletalReferenceTransforms(action, eTransformSpace, eReferencePose, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalTrackingLevel(VRActionHandle_t action, EVRSkeletalTrackingLevel* pSkeletalTrackingLevel) {
	return g_vrinput->GetSkeletalTrackingLevel(action, pSkeletalTrackingLevel);
}
EVRInputError BaseInput::GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
  	EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray,
	  uint32_t unTransformArrayCount, VRInputValueHandle_t ulRestrictToDevice) {
	return g_vrinput->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
	  EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
	return g_vrinput->GetSkeletalBoneData(action, eTransformSpace, eMotionRange, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::GetSkeletalSummaryData(VRActionHandle_t action, EVRSummaryType eSummaryType, VRSkeletalSummaryData_t * pSkeletalSummaryData) {
	return g_vrinput->GetSkeletalSummaryData(action, eSummaryType, pSkeletalSummaryData);
}
EVRInputError BaseInput::GetSkeletalSummaryData(VRActionHandle_t action, VRSkeletalSummaryData_t * pSkeletalSummaryData) {
  return GetSkeletalSummaryData(action, VRSummaryType_FromAnimation, pSkeletalSummaryData);
}
EVRInputError BaseInput::GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace,
	  EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize,
	  uint32_t *punRequiredCompressedSize, VRInputValueHandle_t ulRestrictToDevice) {
  getOut() << "abort BaseInput::GetSkeletalBoneDataCompressed" << std::endl; abort();
  return VRInputError_None;
  // return g_vrinput->GetSkeletalBoneDataCompressed(action, eTransformSpace, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize, ulRestrictToDevice);
}
EVRInputError BaseInput::GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalMotionRange eMotionRange,
	  VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize) {
	return g_vrinput->GetSkeletalBoneDataCompressed(action, eMotionRange, pvCompressedData, unCompressedSize, punRequiredCompressedSize);
}
EVRInputError BaseInput::DecompressSkeletalBoneData(void *pvCompressedBuffer, uint32_t unCompressedBufferSize,
	  EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray,
	  uint32_t unTransformArrayCount) {
  getOut() << "abort BaseInput::DecompressSkeletalBoneData" << std::endl; abort();
  return VRInputError_None;
  // return g_vrinput->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, peTransformSpace, pTransformArray, unTransformArrayCount);
}
EVRInputError BaseInput::DecompressSkeletalBoneData(const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace eTransformSpace,
	  VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount) {
	return g_vrinput->DecompressSkeletalBoneData(pvCompressedBuffer, unCompressedBufferSize, eTransformSpace, pTransformArray, unTransformArrayCount);
}

EVRInputError BaseInput::TriggerHapticVibrationAction(VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds,
	  float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice) {
  return g_vrinput->TriggerHapticVibrationAction(action, fStartSecondsFromNow, fDurationSeconds, fFrequency, fAmplitude, ulRestrictToDevice);
}
EVRInputError BaseInput::GetActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle,
	  VR_ARRAY_COUNT(originOutCount) VRInputValueHandle_t *originsOut, uint32_t originOutCount) {
  return g_vrinput->GetActionOrigins(actionSetHandle, digitalActionHandle, originsOut, originOutCount);
}
EVRInputError BaseInput::GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize) {
  getOut() << "abort BaseInput::GetOriginLocalizedName" << std::endl; abort();
  return VRInputError_None;
	// return g_vrinput->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize);
}
EVRInputError BaseInput::GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize,
	  int32_t unStringSectionsToInclude) {
	return g_vrinput->GetOriginLocalizedName(origin, pchNameArray, unNameArraySize, unStringSectionsToInclude);
}
EVRInputError BaseInput::GetOriginTrackedDeviceInfo(VRInputValueHandle_t origin, InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize) {
  return g_vrinput->GetOriginTrackedDeviceInfo(origin, pOriginInfo, unOriginInfoSize);
}

/** Retrieves useful information about the bindings for an action */
EVRInputError BaseInput::GetActionBindingInfo(VRActionHandle_t actionHandle, vr::InputBindingInfo_t *pOriginInfo,
		uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t *punReturnedBindingInfoCount) {
  return g_vrinput->GetActionBindingInfo(actionHandle, pOriginInfo, unBindingInfoSize, unBindingInfoCount, punReturnedBindingInfoCount);
}

/* void BaseInput::GetActionSourceBindingInfo(const Action *action,
		const ActionSource *src, vr::InputBindingInfo_t *result) {
  return g_vrinput->GetActionSourceBindingInfo(action, src, result);
} */

EVRInputError BaseInput::ShowActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle) {
	return g_vrinput->ShowActionOrigins(actionSetHandle, ulActionHandle);
}
EVRInputError BaseInput::ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t,
	  uint32_t unSetCount, VRInputValueHandle_t originToHighlight) {
  return g_vrinput->ShowBindingsForActionSet(pSets, unSizeOfVRSelectedActionSet_t, unSetCount, originToHighlight);
}

bool BaseInput::IsUsingLegacyInput() {
	return g_vrinput->IsUsingLegacyInput();
}
