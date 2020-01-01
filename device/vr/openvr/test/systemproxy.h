#ifndef _openvr_systemproxy_h_
#define _openvr_systemproxy_h_

// #include <D3D11_1.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
// #include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRSystem : public IVRSystem {
public:
  IVRSystem *vrsystem;
  FnProxy &fnp;

  virtual void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight);
  virtual HmdMatrix44_t GetProjectionMatrix(EVREye eEye, float fNearZ, float fFarZ);
  virtual void GetProjectionRaw(EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom);
  virtual bool ComputeDistortion(EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates);
  virtual HmdMatrix34_t GetEyeToHeadTransform(EVREye eEye);
  virtual bool GetTimeSinceLastVsync(float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter);
  virtual int32_t GetD3D9AdapterIndex();
  virtual void GetDXGIOutputInfo(int32_t *pnAdapterIndex);
  virtual void GetOutputDevice(uint64_t *pnDevice, ETextureType textureType, VkInstance_T *pInstance = nullptr);
  virtual bool IsDisplayOnDesktop();
  virtual bool SetDisplayVisibility(bool bIsVisibleOnDesktop);
  virtual void GetDeviceToAbsoluteTrackingPose(ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
  virtual void ResetSeatedZeroPose();
  virtual HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
  virtual HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose();
  virtual uint32_t GetSortedTrackedDeviceIndicesOfClass(ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd);
  virtual EDeviceActivityLevel GetTrackedDeviceActivityLevel(vr::TrackedDeviceIndex_t unDeviceId);
  virtual void ApplyTransform(TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform);
  virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(vr::ETrackedControllerRole unDeviceType);
  virtual vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex);
  virtual ETrackedDeviceClass GetTrackedDeviceClass(vr::TrackedDeviceIndex_t unDeviceIndex);
  virtual bool IsTrackedDeviceConnected(vr::TrackedDeviceIndex_t unDeviceIndex);
  virtual bool GetBoolTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL);
  virtual float GetFloatTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL);
  virtual int32_t GetInt32TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL);
  virtual uint64_t GetUint64TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL);
  virtual HmdMatrix34_t GetMatrix34TrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pErrorL);
  virtual uint32_t GetArrayTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, PropertyTypeTag_t propType, void *pBuffer, uint32_t unBufferSize, ETrackedPropertyError *pError);
  virtual uint32_t GetStringTrackedDeviceProperty(vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pErrorL);
  virtual const char *GetPropErrorNameFromEnum(ETrackedPropertyError error);
  virtual bool IsInputAvailable();
  virtual bool IsSteamVRDrawingControllers();
  virtual bool ShouldApplicationPause();
  virtual bool ShouldApplicationReduceRenderingWork();
  virtual bool PollNextEvent(VREvent_t *pEvent, uint32_t uncbVREvent);
  virtual bool PollNextEventWithPose(ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose);
  virtual const char *GetEventTypeNameFromEnum(EVREventType eType);
  virtual HiddenAreaMesh_t GetHiddenAreaMesh(EVREye eEye, EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard);
  virtual bool GetControllerState(vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize);
  virtual bool GetControllerStateWithPose(ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, uint32_t unControllerStateSize, TrackedDevicePose_t *pTrackedDevicePose);
  virtual void TriggerHapticPulse(vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
  virtual const char *GetButtonIdNameFromEnum(EVRButtonId eButtonId);
  virtual const char *GetControllerAxisTypeNameFromEnum(EVRControllerAxisType eAxisType);
  virtual bool CaptureInputFocus();
  virtual void ReleaseInputFocus();
  virtual bool IsInputFocusCapturedByAnotherProcess();
  virtual uint32_t DriverDebugRequest(vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize);
  virtual vr::EVRFirmwareError PerformFirmwareUpdate(vr::TrackedDeviceIndex_t unDeviceIndex);
  virtual void AcknowledgeQuit_Exiting();
  virtual void AcknowledgeQuit_UserPrompt();
  virtual uint32_t GetAppContainerFilePaths(VR_OUT_STRING() char *pchBuffer, uint32_t unBufferSize);
  virtual const char *GetRuntimeVersion();
  virtual DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV);
  virtual HmdMatrix44_t GetProjectionMatrix(EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention convention);
  virtual void PerformanceTestEnableCapture(bool bEnable);
  virtual void PerformanceTestReportFidelityLevelChange(int nFidelityLevel);
};
}

#endif