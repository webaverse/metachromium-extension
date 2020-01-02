#ifndef _openvr_inputproxy_h_
#define _openvr_inputproxy_h_

// #include <D3D11_1.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
// #include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRInput : public IVRInput {
public:
  IVRInput *vrinput;

  PVRInput(IVRInput *vrinput, FnProxy &fnp);
	virtual vr::EVRInputError SetActionManifestPath(const char *pchActionManifestPath);
  virtual vr::EVRInputError GetActionSetHandle(const char *pchActionSetName, vr::VRActionSetHandle_t *pHandle);
  virtual vr::EVRInputError GetActionHandle(const char *pchActionName, vr::VRActionHandle_t *pHandle);
  virtual vr::EVRInputError GetInputSourceHandle(const char *pchInputSourcePath, vr::VRInputValueHandle_t  *pHandle);
  virtual vr::EVRInputError UpdateActionState(VR_ARRAY_COUNT(unSetCount) vr::VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount);
  virtual vr::EVRInputError GetDigitalActionData(vr::VRActionHandle_t action, vr::InputDigitalActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetAnalogActionData(vr::VRActionHandle_t action, vr::InputAnalogActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetPoseActionData(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetPoseActionDataRelativeToNow(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetPoseActionDataForNextFrame(vr::VRActionHandle_t action, vr::ETrackingUniverseOrigin eOrigin, vr::InputPoseActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetSkeletalActionData(vr::VRActionHandle_t action, vr::InputSkeletalActionData_t *pActionData, uint32_t unActionDataSize);
  virtual vr::EVRInputError GetBoneCount(vr::VRActionHandle_t action, uint32_t* pBoneCount);
  virtual vr::EVRInputError GetBoneHierarchy(vr::VRActionHandle_t action, VR_ARRAY_COUNT(unIndexArayCount) vr::BoneIndex_t* pParentIndices, uint32_t unIndexArayCount);
  virtual vr::EVRInputError GetBoneName(vr::VRActionHandle_t action, vr::BoneIndex_t nBoneIndex, VR_OUT_STRING() char* pchBoneName, uint32_t unNameBufferSize);
  virtual vr::EVRInputError GetSkeletalReferenceTransforms(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalReferencePose eReferencePose, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
  virtual vr::EVRInputError GetSkeletalTrackingLevel(vr::VRActionHandle_t action, vr::EVRSkeletalTrackingLevel* pSkeletalTrackingLevel);
  virtual vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetSkeletalBoneData(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
  virtual vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::EVRSummaryType eSummaryType, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData);
  virtual vr::EVRInputError GetSkeletalSummaryData(vr::VRActionHandle_t action, vr::VRSkeletalSummaryData_t * pSkeletalSummaryData);
  virtual vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalTransformSpace eTransformSpace, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetSkeletalBoneDataCompressed(vr::VRActionHandle_t action, vr::EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void *pvCompressedData, uint32_t unCompressedSize, uint32_t *punRequiredCompressedSize);
  virtual vr::EVRInputError DecompressSkeletalBoneData(void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace *peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
  virtual vr::EVRInputError DecompressSkeletalBoneData(const void *pvCompressedBuffer, uint32_t unCompressedBufferSize, vr::EVRSkeletalTransformSpace eTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) vr::VRBoneTransform_t *pTransformArray, uint32_t unTransformArrayCount);
  virtual vr::EVRInputError TriggerHapticVibrationAction(vr::VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, vr::VRInputValueHandle_t ulRestrictToDevice);
  virtual vr::EVRInputError GetActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT(originOutCount) vr::VRInputValueHandle_t *originsOut, uint32_t originOutCount);
  virtual vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize);
  virtual vr::EVRInputError GetOriginLocalizedName(vr::VRInputValueHandle_t origin, VR_OUT_STRING() char *pchNameArray, uint32_t unNameArraySize, int32_t unStringSectionsToInclude);
  virtual vr::EVRInputError GetOriginTrackedDeviceInfo(vr::VRInputValueHandle_t origin, vr::InputOriginInfo_t *pOriginInfo, uint32_t unOriginInfoSize);
  virtual vr::EVRInputError GetActionBindingInfo(vr::VRActionHandle_t action, vr::InputBindingInfo_t *pOriginInfo, uint32_t unBindingInfoSize, uint32_t unBindingInfoCount, uint32_t *punReturnedBindingInfoCount);
  virtual vr::EVRInputError ShowActionOrigins(vr::VRActionSetHandle_t actionSetHandle, vr::VRActionHandle_t ulActionHandle);
  virtual vr::EVRInputError ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) vr::VRActiveActionSet_t *pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, vr::VRInputValueHandle_t originToHighlight);
  virtual bool IsUsingLegacyInput();
};
}

#endif