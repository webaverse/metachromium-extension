#include "stdafx.h"
#define BASE_IMPL
#include "BaseSystem.h"
// #include "OVR_CAPI.h"
// #include "libovr_wrapper.h"
// #include "convert.h"
#include "BaseSystem.h"
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
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetRecommendedRenderTargetSize" << std::endl; });
  return g_pvrsystem->GetRecommendedRenderTargetSize(width, height);
}

HmdMatrix44_t BaseSystem::GetProjectionMatrix(EVREye eye, float znear, float zfar) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetProjectionMatrix" << std::endl; });
	return g_pvrsystem->GetProjectionMatrix(eye, znear, zfar);
}

void BaseSystem::GetProjectionRaw(EVREye eye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetProjectionRaw" << std::endl; });
	return g_pvrsystem->GetProjectionRaw(eye, pfLeft, pfRight, pfTop, pfBottom);
}

bool BaseSystem::ComputeDistortion(EVREye eEye, float fU, float fV, DistortionCoordinates_t * out) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ComputeDistortion" << std::endl; });
	return g_pvrsystem->ComputeDistortion(eEye, fU, fV, out);
}

HmdMatrix34_t BaseSystem::GetEyeToHeadTransform(EVREye ovr_eye) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetEyeToHeadTransform" << std::endl; });
	return g_pvrsystem->GetEyeToHeadTransform(ovr_eye);
}

bool BaseSystem::GetTimeSinceLastVsync(float * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetTimeSinceLastVsync" << std::endl; });
	return g_pvrsystem->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
}

int32_t BaseSystem::GetD3D9AdapterIndex() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetD3D9AdapterIndex" << std::endl; });
  return g_pvrsystem->GetD3D9AdapterIndex();
}

void BaseSystem::GetDXGIOutputInfo(int32_t * adapterIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetDXGIOutputInfo" << std::endl; });
  return g_pvrsystem->GetDXGIOutputInfo(adapterIndex);
}

void BaseSystem::GetOutputDevice(uint64_t * pnDevice, ETextureType textureType, VkInstance_T * pInstance) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetOutputDevice" << std::endl; });
  return g_pvrsystem->GetOutputDevice(pnDevice, textureType, pInstance);
}

bool BaseSystem::IsDisplayOnDesktop() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::IsDisplayOnDesktop" << std::endl; });
	return g_pvrsystem->IsDisplayOnDesktop();
}

bool BaseSystem::SetDisplayVisibility(bool bIsVisibleOnDesktop) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::SetDisplayVisibility" << std::endl; });
	return g_pvrsystem->SetDisplayVisibility(bIsVisibleOnDesktop);
}

void BaseSystem::GetDeviceToAbsoluteTrackingPose(ETrackingUniverseOrigin toOrigin, float predictedSecondsToPhotonsFromNow,
  	TrackedDevicePose_t * poseArray, uint32_t poseArrayCount) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetDeviceToAbsoluteTrackingPose" << std::endl; });
  return g_pvrsystem->GetDeviceToAbsoluteTrackingPose(toOrigin, predictedSecondsToPhotonsFromNow, poseArray, poseArrayCount);
}

HmdMatrix34_t BaseSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose" << std::endl; });
	return g_pvrsystem->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
}

HmdMatrix34_t BaseSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetRawZeroPoseToStandingAbsoluteTrackingPose" << std::endl; });
	return g_pvrsystem->GetRawZeroPoseToStandingAbsoluteTrackingPose();
}

uint32_t BaseSystem::GetSortedTrackedDeviceIndicesOfClass(ETrackedDeviceClass targetClass,
		vr::TrackedDeviceIndex_t *indexArray, uint32_t indexCount,
		vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetSortedTrackedDeviceIndicesOfClass" << std::endl; });
  return g_pvrsystem->GetSortedTrackedDeviceIndicesOfClass(targetClass, indexArray, indexCount, unRelativeToTrackedDeviceIndex);
}

EDeviceActivityLevel BaseSystem::GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetTrackedDeviceActivityLevel" << std::endl; });
	return g_pvrsystem->GetTrackedDeviceActivityLevel(unDeviceId);
}

void BaseSystem::ApplyTransform(TrackedDevicePose_t * pOutputPose, const TrackedDevicePose_t * pTrackedDevicePose, const HmdMatrix34_t * pTransform) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ApplyTransform" << std::endl; });
	return g_pvrsystem->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
}

vr::TrackedDeviceIndex_t BaseSystem::GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetTrackedDeviceIndexForControllerRole" << std::endl; });
	return g_pvrsystem->GetTrackedDeviceIndexForControllerRole(unDeviceType);
}

vr::ETrackedControllerRole BaseSystem::GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetControllerRoleForTrackedDeviceIndex" << std::endl; });
	return g_pvrsystem->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
}

ETrackedDeviceClass BaseSystem::GetTrackedDeviceClass(vr::TrackedDeviceIndex_t deviceIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetTrackedDeviceClass" << std::endl; });
	return g_pvrsystem->GetTrackedDeviceClass(deviceIndex);
}

bool BaseSystem::IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t deviceIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::IsTrackedDeviceConnected" << std::endl; });
	return g_pvrsystem->IsTrackedDeviceConnected(deviceIndex);
}

bool BaseSystem::GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetBoolTrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

float BaseSystem::GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetFloatTrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

int32_t BaseSystem::GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetInt32TrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

uint64_t BaseSystem::GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetUint64TrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

HmdMatrix34_t BaseSystem::GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetMatrix34TrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pErrorL);
}

uint32_t BaseSystem::GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, void * pBuffer, uint32_t unBufferSize, ETrackedPropertyError * pError) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetArrayTrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetArrayTrackedDeviceProperty(unDeviceIndex, prop, propType, pBuffer, unBufferSize, pError);
}

uint32_t BaseSystem::GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop,
	  VR_OUT_STRING() char * value, uint32_t bufferSize, ETrackedPropertyError * pErrorL) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetStringTrackedDeviceProperty" << std::endl; });
	return g_pvrsystem->GetStringTrackedDeviceProperty(unDeviceIndex, prop, value, bufferSize, pErrorL);
}

const char * BaseSystem::GetPropErrorNameFromEnum(ETrackedPropertyError error) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetPropErrorNameFromEnum" << std::endl; });
	return g_pvrsystem->GetPropErrorNameFromEnum(error);
}

bool BaseSystem::IsInputAvailable() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::IsInputAvailable" << std::endl; });
	return g_pvrsystem->IsInputAvailable();
}

bool BaseSystem::IsSteamVRDrawingControllers() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::IsSteamVRDrawingControllers" << std::endl; });
	return g_pvrsystem->IsSteamVRDrawingControllers();
}

bool BaseSystem::ShouldApplicationPause() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ShouldApplicationPause" << std::endl; });
	return g_pvrsystem->ShouldApplicationPause();
}

bool BaseSystem::ShouldApplicationReduceRenderingWork() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ShouldApplicationReduceRenderingWork" << std::endl; });
	return g_pvrsystem->ShouldApplicationReduceRenderingWork();
}

/* float BaseSystem::SGetIpd() {
	ovrPosef &left = ovr::hmdToEyeViewPose[ovrEye_Left];
	ovrPosef &right = ovr::hmdToEyeViewPose[ovrEye_Right];

	return abs(left.Position.x - right.Position.x);
}

void BaseSystem::CheckControllerEvents(TrackedDeviceIndex_t hand, VRControllerState_t &last) {
	return g_pvrsystem->CheckControllerEvents(hand, last);
} */

bool BaseSystem::PollNextEvent(VREvent_t * pEvent, uint32_t uncbVREvent) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::PollNextEvent" << std::endl; });
	return g_pvrsystem->PollNextEvent(pEvent, uncbVREvent);
}

bool BaseSystem::PollNextEventWithPose(ETrackingUniverseOrigin eOrigin, VREvent_t * pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t * pTrackedDevicePose) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::PollNextEventWithPose" << std::endl; });
	return g_pvrsystem->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose);
}

const char * BaseSystem::GetEventTypeNameFromEnum(EVREventType eType) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetEventTypeNameFromEnum" << std::endl; });
	return g_pvrsystem->GetEventTypeNameFromEnum(eType);
}

HiddenAreaMesh_t BaseSystem::GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetHiddenAreaMesh" << std::endl; });
	return g_pvrsystem->GetHiddenAreaMesh(eEye, type);
}

bool BaseSystem::GetControllerState(vr::TrackedDeviceIndex_t controllerDeviceIndex, vr::VRControllerState_t * controllerState, uint32_t controllerStateSize) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetControllerState" << std::endl; });
	return g_pvrsystem->GetControllerState(controllerDeviceIndex, controllerState, controllerStateSize);
}

bool BaseSystem::GetControllerStateWithPose(ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex,
  	vr::VRControllerState_t * pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t * pTrackedDevicePose) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetControllerStateWithPose" << std::endl; });
  return g_pvrsystem->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, unControllerStateSize, pTrackedDevicePose);
}

void BaseSystem::TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::TriggerHapticPulse" << std::endl; });
	return g_pvrsystem->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
}

const char * BaseSystem::GetButtonIdNameFromEnum(EVRButtonId eButtonId) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetButtonIdNameFromEnum" << std::endl; });
	return g_pvrsystem->GetButtonIdNameFromEnum(eButtonId);
}

const char * BaseSystem::GetControllerAxisTypeNameFromEnum(EVRControllerAxisType eAxisType) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetControllerAxisTypeNameFromEnum" << std::endl; });
	return g_pvrsystem->GetControllerAxisTypeNameFromEnum(eAxisType);
}

bool BaseSystem::CaptureInputFocus() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::CaptureInputFocus" << std::endl; });
	return g_pvrsystem->CaptureInputFocus();
}

void BaseSystem::ReleaseInputFocus() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ReleaseInputFocus" << std::endl; });
	return g_pvrsystem->ReleaseInputFocus();
}

bool BaseSystem::IsInputFocusCapturedByAnotherProcess() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::IsInputFocusCapturedByAnotherProcess" << std::endl; });
	return g_pvrsystem->IsInputFocusCapturedByAnotherProcess();
}

uint32_t BaseSystem::DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::DriverDebugRequest" << std::endl; });
	return g_pvrsystem->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
}

vr::EVRFirmwareError BaseSystem::PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::PerformFirmwareUpdate" << std::endl; });
	return g_pvrsystem->PerformFirmwareUpdate(unDeviceIndex);
}

void BaseSystem::AcknowledgeQuit_Exiting() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::AcknowledgeQuit_Exiting" << std::endl; });
	return g_pvrsystem->AcknowledgeQuit_Exiting();
}

void BaseSystem::AcknowledgeQuit_UserPrompt() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::AcknowledgeQuit_UserPrompt" << std::endl; });
	return g_pvrsystem->AcknowledgeQuit_UserPrompt();
}

uint32_t BaseSystem::GetAppContainerFilePaths(VR_OUT_STRING() char *pchBuffer, uint32_t unBufferSize) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetAppContainerFilePaths" << std::endl; });
	return g_pvrsystem->GetAppContainerFilePaths(pchBuffer, unBufferSize);
}

const char *BaseSystem::GetRuntimeVersion() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetRuntimeVersion" << std::endl; });
	return g_pvrsystem->GetRuntimeVersion();
}

DistortionCoordinates_t BaseSystem::ComputeDistortion(EVREye eEye, float fU, float fV) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ComputeDistortion" << std::endl; });
  DistortionCoordinates_t result;
	g_pvrsystem->ComputeDistortion(eEye, fU, fV, &result);
  return result;
}

HmdMatrix44_t BaseSystem::GetProjectionMatrix(EVREye eye, float znear, float zfar, EGraphicsAPIConvention convention) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::GetProjectionMatrix" << std::endl; });
	return g_pvrsystem->GetProjectionMatrix(eye, znear, zfar);
}

void BaseSystem::PerformanceTestEnableCapture(bool bEnable) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::PerformanceTestEnableCapture" << std::endl; });
  getOut() << "abort BaseSystem::PerformanceTestEnableCapture" << std::endl; abort();
	// return g_pvrsystem->PerformanceTestEnableCapture(bEnable);
}

void BaseSystem::PerformanceTestReportFidelityLevelChange(int nFidelityLevel) {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::PerformanceTestReportFidelityLevelChange" << std::endl; });
  getOut() << "abort BaseSystem::PerformanceTestReportFidelityLevelChange" << std::endl; abort();
	// return g_pvrsystem->PerformanceTestReportFidelityLevelChange(nFidelityLevel);
}

void BaseSystem::ResetSeatedZeroPose() {
  TRACE("BaseSystem", []() { getOut() << "BaseSystem::ResetSeatedZeroPose" << std::endl; });
	return g_pvrsystem->ResetSeatedZeroPose();
}
