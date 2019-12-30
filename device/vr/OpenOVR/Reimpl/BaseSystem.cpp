#include "stdafx.h"
#define BASE_IMPL
#include "BaseSystem.h"
// #include "OVR_CAPI.h"
// #include "libovr_wrapper.h"
// #include "convert.h"
#include "BaseCompositor.h"
#include "BaseOverlay.h"
// #include "Misc/Haptics.h"
// #include "Misc/Config.h"
#include "static_bases.gen.h"
// #include "Drivers/Backend.h"

#include <string>

#ifdef SUPPORT_DX
#include <dxgi.h> // for GetDefaultAdapterLuid
#pragma comment(lib, "dxgi.lib")
#endif

// Needed for GetOutputDevice if Vulkan is enabled
/* #if defined(SUPPORT_VK)
#include "OVR_CAPI_Vk.h"
#endif */

using namespace std;

BaseSystem::BaseSystem() {
	// Set the default origin
	// _SetTrackingOrigin(origin);
}

void BaseSystem::GetRecommendedRenderTargetSize(uint32_t * width, uint32_t * height) {
  return g_vrsystem->GetRecommendedRenderTargetSize(width, height);
}

HmdMatrix44_t BaseSystem::GetProjectionMatrix(EVREye eye, float znear, float zfar) {
	return g_vrsystem->GetProjectionMatrix(eye, znear, zfar);
}

void BaseSystem::GetProjectionRaw(EVREye eye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom) {
	return g_vrsystem->GetProjectionRaw(eye, pfLeft, pfRight, pfTop, pfBottom);
}

bool BaseSystem::ComputeDistortion(EVREye eEye, float fU, float fV, DistortionCoordinates_t * out) {
	return g_vrsystem->ComputeDistortion(eEye, fU, fV, out);
}

HmdMatrix34_t BaseSystem::GetEyeToHeadTransform(EVREye ovr_eye) {
	return g_vrsystem->GetEyeToHeadTransform(ovr_eye);
}

bool BaseSystem::GetTimeSinceLastVsync(float * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter) {
	return g_vrsystem->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
}

int32_t BaseSystem::GetD3D9AdapterIndex() {
  return g_vrsystem->GetD3D9AdapterIndex();
}

void BaseSystem::GetDXGIOutputInfo(int32_t * adapterIndex) {
  return g_vrsystem->GetDXGIOutputInfo(adapterIndex);
}

void BaseSystem::GetOutputDevice(uint64_t * pnDevice, ETextureType textureType, VkInstance_T * pInstance) {
  return g_vrsystem->GetOutputDevice(pnDevice, textureType, pInstance);
}

bool BaseSystem::IsDisplayOnDesktop() {
	return g_vrsystem->IsDisplayOnDesktop();
}

bool BaseSystem::SetDisplayVisibility(bool bIsVisibleOnDesktop) {
	return g_vrsystem->SetDisplayVisibility(bIsVisibleOnDesktop);
}

void BaseSystem::GetDeviceToAbsoluteTrackingPose(ETrackingUniverseOrigin toOrigin, float predictedSecondsToPhotonsFromNow,
  	TrackedDevicePose_t * poseArray, uint32_t poseArrayCount) {
  return g_vrsystem->GetDeviceToAbsoluteTrackingPose(toOrigin, predictedSecondsToPhotonsFromNow, poseArray, poseArrayCount);
}

HmdMatrix34_t BaseSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
	return g_vrsystem->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
}

HmdMatrix34_t BaseSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose() {
	return g_vrsystem->GetRawZeroPoseToStandingAbsoluteTrackingPose();
}

uint32_t BaseSystem::GetSortedTrackedDeviceIndicesOfClass(ETrackedDeviceClass targetClass,
		vr::TrackedDeviceIndex_t *indexArray, uint32_t indexCount,
		vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) {
  return g_vrsystem->GetSortedTrackedDeviceIndicesOfClass(targetClass, indexArray, indexCount, unRelativeToTrackedDeviceIndex);
}

EDeviceActivityLevel BaseSystem::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) {
	return g_vrsystem->GetTrackedDeviceActivityLevel(unDeviceId);
}

void BaseSystem::ApplyTransform(TrackedDevicePose_t * pOutputPose, const TrackedDevicePose_t * pTrackedDevicePose, const HmdMatrix34_t * pTransform) {
	return g_vrsystem->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
}

vr::TrackedDeviceIndex_t BaseSystem::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) {
	return g_vrsystem->GetTrackedDeviceIndexForControllerRole(unDeviceType);
}

vr::ETrackedControllerRole BaseSystem::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) {
	return g_vrsystem->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
}

ETrackedDeviceClass BaseSystem::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t deviceIndex) {
	return g_vrsystem->GetTrackedDeviceClass(deviceIndex);
}

bool BaseSystem::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t deviceIndex) {
	return g_vrsystem->IsTrackedDeviceConnected(deviceIndex);
}

bool BaseSystem::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

float BaseSystem::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

int32_t BaseSystem::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

uint64_t BaseSystem::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

HmdMatrix34_t BaseSystem::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

uint32_t BaseSystem::GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, void * pBuffer, uint32_t unBufferSize, ETrackedPropertyError * pError) {
	return g_vrsystem->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError);
}

uint32_t BaseSystem::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop,
	VR_OUT_STRING() char * value, uint32_t bufferSize, ETrackedPropertyError * pErrorL) {
	return g_vrsystem->GetStringTrackedDeviceProperty(unDeviceIndex, prop, value, bufferSize, pErrorL);
}

const char * BaseSystem::GetPropErrorNameFromEnum(ETrackedPropertyError error) {
	return g_vrsystem->GetPropErrorNameFromEnum(error);
}

bool BaseSystem::IsInputAvailable() {
	return g_vrsystem->IsInputAvailable();
}

bool BaseSystem::IsSteamVRDrawingControllers() {
	return g_vrsystem->IsSteamVRDrawingControllers();
}

bool BaseSystem::ShouldApplicationPause() {
	return g_vrsystem->ShouldApplicationPause();
}

bool BaseSystem::ShouldApplicationReduceRenderingWork() {
	return g_vrsystem->ShouldApplicationReduceRenderingWork();
}

/* float BaseSystem::SGetIpd() {
	ovrPosef &left = ovr::hmdToEyeViewPose[ovrEye_Left];
	ovrPosef &right = ovr::hmdToEyeViewPose[ovrEye_Right];

	return abs(left.Position.x - right.Position.x);
}

void BaseSystem::CheckControllerEvents(TrackedDeviceIndex_t hand, VRControllerState_t &last) {
	return g_vrsystem->CheckControllerEvents(hand, last);
} */

bool BaseSystem::PollNextEvent(VREvent_t * pEvent, uint32_t uncbVREvent) {
	return g_vrsystem->PollNextEvent(pEvent, uncbVREvent);
}

bool BaseSystem::PollNextEventWithPose(ETrackingUniverseOrigin eOrigin, VREvent_t * pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t * pTrackedDevicePose) {
	return g_vrsystem->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose);
}

const char * BaseSystem::GetEventTypeNameFromEnum(EVREventType eType) {
	return g_vrsystem->GetEventTypeNameFromEnum(eType);
}

HiddenAreaMesh_t BaseSystem::GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type) {
	return g_vrsystem->GetHiddenAreaMesh(eEye, type);
}

bool BaseSystem::GetControllerState(vr::TrackedDeviceIndex_t controllerDeviceIndex, vr::VRControllerState_t * controllerState, uint32_t controllerStateSize) {
	return g_vrsystem->GetControllerState(controllerDeviceIndex, controllerState, controllerStateSize);
}

bool BaseSystem::GetControllerStateWithPose(ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex,
  	vr::VRControllerState_t * pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t * pTrackedDevicePose) {
  return g_vrsystem->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose);
}

void BaseSystem::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) {
	return g_vrsystem->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
}

const char * BaseSystem::GetButtonIdNameFromEnum(EVRButtonId eButtonId) {
	return g_vrsystem->GetButtonIdNameFromEnum(eButtonId);
}

const char * BaseSystem::GetControllerAxisTypeNameFromEnum(EVRControllerAxisType eAxisType) {
	return g_vrsystem->GetControllerAxisTypeNameFromEnum(eAxisType);
}

bool BaseSystem::CaptureInputFocus() {
  getOut() << "abort BaseSystem::CaptureInputFocus" << std::endl; abort();
	// return g_vrsystem->CaptureInputFocus();
}

void BaseSystem::ReleaseInputFocus() {
  getOut() << "abort BaseSystem::ReleaseInputFocus" << std::endl; abort();
	// return g_vrsystem->ReleaseInputFocus();
}

bool BaseSystem::IsInputFocusCapturedByAnotherProcess() {
  getOut() << "abort BaseSystem::IsInputFocusCapturedByAnotherProcess" << std::endl; abort();
  return false;
	// return g_vrsystem->IsInputFocusCapturedByAnotherProcess();
}

uint32_t BaseSystem::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize) {
  getOut() << "abort BaseSystem::DriverDebugRequest" << std::endl; abort();
  return 0;
	// return g_vrsystem->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
}

vr::EVRFirmwareError BaseSystem::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) {
	return g_vrsystem->PerformFirmwareUpdate(unDeviceIndex);
}

void BaseSystem::AcknowledgeQuit_Exiting() {
	return g_vrsystem->AcknowledgeQuit_Exiting();
}

void BaseSystem::AcknowledgeQuit_UserPrompt() {
  getOut() << "abort BaseSystem::AcknowledgeQuit_UserPrompt" << std::endl; abort();
	// return g_vrsystem->AcknowledgeQuit_UserPrompt();
}

uint32_t BaseSystem::GetAppContainerFilePaths(VR_OUT_STRING() char *pchBuffer, uint32_t unBufferSize) {
	return g_vrsystem->GetAppContainerFilePaths(pchBuffer, unBufferSize);
}

const char *BaseSystem::GetRuntimeVersion() {
	return g_vrsystem->GetRuntimeVersion();
}

DistortionCoordinates_t BaseSystem::ComputeDistortion(EVREye eEye, float fU, float fV) {
  DistortionCoordinates_t result;
	g_vrsystem->ComputeDistortion(eEye, fU, fV, &result);
  return result;
}

HmdMatrix44_t BaseSystem::GetProjectionMatrix(EVREye eye, float znear, float zfar, EGraphicsAPIConvention convention) {
	return g_vrsystem->GetProjectionMatrix(eye, znear, zfar);
}

void BaseSystem::PerformanceTestEnableCapture(bool bEnable) {
  getOut() << "abort BaseSystem::PerformanceTestEnableCapture" << std::endl; abort();
	// return g_vrsystem->PerformanceTestEnableCapture(bEnable);
}

void BaseSystem::PerformanceTestReportFidelityLevelChange(int nFidelityLevel) {
  getOut() << "abort BaseSystem::PerformanceTestReportFidelityLevelChange" << std::endl; abort();
	// return g_vrsystem->PerformanceTestReportFidelityLevelChange(nFidelityLevel);
}

void BaseSystem::ResetSeatedZeroPose() {
	return g_vrsystem->ResetSeatedZeroPose();
}
