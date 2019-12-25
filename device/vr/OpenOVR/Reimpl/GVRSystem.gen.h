#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRSystem_011.h"
#include "OpenVR/interfaces/IVRSystem_012.h"
#include "OpenVR/interfaces/IVRSystem_014.h"
#include "OpenVR/interfaces/IVRSystem_015.h"
#include "OpenVR/interfaces/IVRSystem_016.h"
#include "OpenVR/interfaces/IVRSystem_017.h"
#include "OpenVR/interfaces/IVRSystem_019.h"
#include "OpenVR/interfaces/IVRSystem_020.h"
#include "BaseSystem.h"
class CVRSystem_011 : public vr::IVRSystem_011::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_011();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
	void PerformanceTestEnableCapture(bool bEnable);
	void PerformanceTestReportFidelityLevelChange(int nFidelityLevel);
};
#include "BaseSystem.h"
class CVRSystem_012 : public vr::IVRSystem_012::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_012();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_014 : public vr::IVRSystem_014::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_014();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_015 : public vr::IVRSystem_015::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_015();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_016 : public vr::IVRSystem_016::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_016();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_017 : public vr::IVRSystem_017::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_017();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool CaptureInputFocus();
	void ReleaseInputFocus();
	bool IsInputFocusCapturedByAnotherProcess();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_019 : public vr::IVRSystem_019::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_019();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool IsInputAvailable();
	bool IsSteamVRDrawingControllers();
	bool ShouldApplicationPause();
	bool ShouldApplicationReduceRenderingWork();
	uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize);
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
};
#include "BaseSystem.h"
class CVRSystem_020 : public vr::IVRSystem_020::IVRSystem, public CVRCommon {
private:
	const std::shared_ptr<BaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRSystem_020();
	// Interface methods:
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight);
	vr::HmdMatrix44_t GetProjectionMatrix(vr::EVREye eEye, float fNearZ, float fFarZ);
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);
	bool ComputeDistortion(vr::EVREye eEye, float fU, float fV, vr::DistortionCoordinates_t* pDistortionCoordinates);
	vr::HmdMatrix34_t GetEyeToHeadTransform(vr::EVREye eEye);
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter);
	int32_t GetD3D9AdapterIndex();
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex);
	void GetOutputDevice(uint64_t* pnDevice, vr::ETextureType textureType, VkInstance_T* pInstance);
	bool IsDisplayOnDesktop();
	bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
	void GetDeviceToAbsoluteTrackingPose(vr::ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void ResetSeatedZeroPose();
	vr::HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
	vr::HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
	uint32_t GetSortedTrackedDeviceIndicesOfClass(vr::ETrackedDeviceClass eTrackedDeviceClass, vr::TrackedDeviceIndex_t* punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
	vr::EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
	void ApplyTransform(vr::TrackedDevicePose_t* pOutputPose, const vr::TrackedDevicePose_t* pTrackedDevicePose, const vr::HmdMatrix34_t* pTransform);
	vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
	vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
	vr::ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
	bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* pError);
	uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, vr::PropertyTypeTag_t propType, void* pBuffer, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, vr::ETrackedDeviceProperty prop, char* pchValue, uint32_t unBufferSize, vr::ETrackedPropertyError* pError);
	const char* GetPropErrorNameFromEnum(vr::ETrackedPropertyError error);
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	bool PollNextEventWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::VREvent_t* pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t* pTrackedDevicePose);
	const char* GetEventTypeNameFromEnum(vr::EVREventType eType);
	vr::HiddenAreaMesh_t GetHiddenAreaMesh(vr::EVREye eEye, vr::EHiddenAreaMeshType type);
	bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize);
	bool GetControllerStateWithPose(vr::ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t* pControllerState, uint32_t unControllerStateSize, vr::TrackedDevicePose_t* pTrackedDevicePose);
	void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
	const char* GetButtonIdNameFromEnum(vr::EVRButtonId eButtonId);
	const char* GetControllerAxisTypeNameFromEnum(vr::EVRControllerAxisType eAxisType);
	bool IsInputAvailable();
	bool IsSteamVRDrawingControllers();
	bool ShouldApplicationPause();
	bool ShouldApplicationReduceRenderingWork();
	vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
	void AcknowledgeQuit_Exiting();
	void AcknowledgeQuit_UserPrompt();
	uint32_t GetAppContainerFilePaths(char* pchBuffer, uint32_t unBufferSize);
	const char* GetRuntimeVersion();
};
