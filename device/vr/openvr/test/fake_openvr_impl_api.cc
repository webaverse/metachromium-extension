// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <memory>

#include "device/vr/openvr/test/test_helper.h"
#include "device/vr/test/test_hook.h"
#include "device/vr/windows/d3d11_device_helpers.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "third_party/openvr/src/src/ivrclientcore.h"

#include "device/vr/sample/hellovr_opengl_main.h"

namespace vr {

CMainApplication mainApplication;

class TestVRSystem : public IVRSystem {
 public: 
  void GetRecommendedRenderTargetSize(uint32_t* width,
                                      uint32_t* height) override;
  HmdMatrix44_t GetProjectionMatrix(EVREye eye,
                                    float near_z,
                                    float far_z) override {
    return mainApplication.m_pHMD->GetProjectionMatrix(eye, near_z, far_z);
  }
  void GetProjectionRaw(EVREye eye,
                        float* left,
                        float* right,
                        float* top,
                        float* bottom) override;
  bool ComputeDistortion(
      EVREye eye,
      float u,
      float v,
      DistortionCoordinates_t* distortion_coordinates) override {
    return mainApplication.m_pHMD->ComputeDistortion(eye, u, v, distortion_coordinates);
  }
  HmdMatrix34_t GetEyeToHeadTransform(EVREye eye) override;
  bool GetTimeSinceLastVsync(float* seconds_since_last_vsync,
                             uint64_t* frame_counter) override {
    return mainApplication.m_pHMD->GetTimeSinceLastVsync(seconds_since_last_vsync, frame_counter);
  }
  int32_t GetD3D9AdapterIndex() override {
    return mainApplication.m_pHMD->GetD3D9AdapterIndex();
  }
  void GetDXGIOutputInfo(int32_t* adapter_index) override;
  bool IsDisplayOnDesktop() override {
    return mainApplication.m_pHMD->IsDisplayOnDesktop();
  }
  bool SetDisplayVisibility(bool is_visible_on_desktop) override {
    return mainApplication.m_pHMD->SetDisplayVisibility(is_visible_on_desktop);
  }
  void GetDeviceToAbsoluteTrackingPose(
      ETrackingUniverseOrigin origin,
      float predicted_seconds_to_photons_from_now,
      VR_ARRAY_COUNT(tracked_device_pose_array_count)
          TrackedDevicePose_t* tracked_device_pose_array,
      uint32_t tracked_device_pose_array_count) override;
  void ResetSeatedZeroPose() override {
    return mainApplication.m_pHMD->ResetSeatedZeroPose();
  }
  HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() override;
  HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() override {
    return mainApplication.m_pHMD->GetRawZeroPoseToStandingAbsoluteTrackingPose();
  }
  uint32_t GetSortedTrackedDeviceIndicesOfClass(
      ETrackedDeviceClass tracked_device_class,
      VR_ARRAY_COUNT(tracked_device_index_array_count)
          TrackedDeviceIndex_t* tracked_device_index_array,
      uint32_t tracked_device_index_array_count,
      TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex =
          k_unTrackedDeviceIndex_Hmd) override {
    return mainApplication.m_pHMD->GetSortedTrackedDeviceIndicesOfClass(tracked_device_class, tracked_device_index_array, tracked_device_index_array_count, unRelativeToTrackedDeviceIndex);
  }
  EDeviceActivityLevel GetTrackedDeviceActivityLevel(
      TrackedDeviceIndex_t device_id) override {
    return mainApplication.m_pHMD->GetTrackedDeviceActivityLevel(device_id);
  }
  void ApplyTransform(TrackedDevicePose_t* output_pose,
                      const TrackedDevicePose_t* tracked_device_pose,
                      const HmdMatrix34_t* transform) override {
    return mainApplication.m_pHMD->ApplyTransform(output_pose, tracked_device_pose, transform);
  }
  TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole(
      ETrackedControllerRole device_type) override {
    return mainApplication.m_pHMD->GetTrackedDeviceIndexForControllerRole(device_type);
  }
  ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(
      TrackedDeviceIndex_t device_index) override;
  ETrackedDeviceClass GetTrackedDeviceClass(
      TrackedDeviceIndex_t device_index) override;
  bool IsTrackedDeviceConnected(TrackedDeviceIndex_t device_index) override {
    return mainApplication.m_pHMD->IsTrackedDeviceConnected(device_index);
  }
  bool GetBoolTrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      ETrackedPropertyError* error = 0L) override {
    return mainApplication.m_pHMD->GetBoolTrackedDeviceProperty(device_index, prop, error);
  }
  float GetFloatTrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      ETrackedPropertyError* error = 0L) override;
  int32_t GetInt32TrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      ETrackedPropertyError* error = 0L) override;
  uint64_t GetUint64TrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      ETrackedPropertyError* error = 0L) override;
  HmdMatrix34_t GetMatrix34TrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      ETrackedPropertyError* error = 0L) override {
    return mainApplication.m_pHMD->GetMatrix34TrackedDeviceProperty(device_index, prop, error);
  }
  uint32_t GetStringTrackedDeviceProperty(
      TrackedDeviceIndex_t device_index,
      ETrackedDeviceProperty prop,
      VR_OUT_STRING() char* value,
      uint32_t buffer_size,
      ETrackedPropertyError* error = 0L) override;
  const char* GetPropErrorNameFromEnum(ETrackedPropertyError error) override {
    return mainApplication.m_pHMD->GetPropErrorNameFromEnum(error);
  }
  bool PollNextEvent(VREvent_t* event, uint32_t vr_event) override;
  bool PollNextEventWithPose(
      ETrackingUniverseOrigin origin,
      VREvent_t* event,
      uint32_t vr_event,
      TrackedDevicePose_t* tracked_device_pose) override {
    return mainApplication.m_pHMD->PollNextEventWithPose(origin, event, vr_event, tracked_device_pose);
  }
  const char* GetEventTypeNameFromEnum(EVREventType type) override {
    return mainApplication.m_pHMD->GetEventTypeNameFromEnum(type);
  }
  HiddenAreaMesh_t GetHiddenAreaMesh(
      EVREye eye,
      EHiddenAreaMeshType type = k_eHiddenAreaMesh_Standard) override {
    return mainApplication.m_pHMD->GetHiddenAreaMesh(eye, type);
  }
  bool GetControllerState(TrackedDeviceIndex_t controller_device_index,
                          VRControllerState_t* controller_state,
                          uint32_t controller_state_size) override;
  bool GetControllerStateWithPose(
      ETrackingUniverseOrigin origin,
      TrackedDeviceIndex_t device_controller_index,
      VRControllerState_t* controller_state,
      uint32_t controller_state_size,
      TrackedDevicePose_t* tracked_device_pose) override;
  void TriggerHapticPulse(TrackedDeviceIndex_t device_index,
                          uint32_t axis_id,
                          unsigned short duration_micro_sec) override {
    mainApplication.m_pHMD->TriggerHapticPulse(device_index, axis_id, duration_micro_sec);
  }
  const char* GetButtonIdNameFromEnum(EVRButtonId button_id) override {
    return mainApplication.m_pHMD->GetButtonIdNameFromEnum(button_id);
  }
  const char* GetControllerAxisTypeNameFromEnum(
      EVRControllerAxisType axis_type) override {
    return mainApplication.m_pHMD->GetControllerAxisTypeNameFromEnum(axis_type);
  }
  bool CaptureInputFocus() override {
    return mainApplication.m_pHMD->CaptureInputFocus();
  }
  void ReleaseInputFocus() override {
     return mainApplication.m_pHMD->ReleaseInputFocus();
  }
  bool IsInputFocusCapturedByAnotherProcess() override {
    return mainApplication.m_pHMD->IsInputFocusCapturedByAnotherProcess();
  }
  uint32_t DriverDebugRequest(TrackedDeviceIndex_t device_index,
                              const char* request,
                              char* response_buffer,
                              uint32_t response_buffer_size) override {
    return mainApplication.m_pHMD->DriverDebugRequest(device_index, request, response_buffer, response_buffer_size);
  }
  EVRFirmwareError PerformFirmwareUpdate(
      TrackedDeviceIndex_t device_index) override {
    return mainApplication.m_pHMD->PerformFirmwareUpdate(device_index);
  }
  void AcknowledgeQuit_Exiting() override {
    return mainApplication.m_pHMD->AcknowledgeQuit_Exiting();
  }
  void AcknowledgeQuit_UserPrompt() override {
    return mainApplication.m_pHMD->AcknowledgeQuit_UserPrompt();
  }
};

class TestVRCompositor : public IVRCompositor {
 public:
  void SetTrackingSpace(ETrackingUniverseOrigin origin) override;
  ETrackingUniverseOrigin GetTrackingSpace() override {
    return mainApplication.m_pCompositor->GetTrackingSpace();
  }
  EVRCompositorError WaitGetPoses(VR_ARRAY_COUNT(render_pose_array_count)
                                      TrackedDevicePose_t* render_pose_array,
                                  uint32_t render_pose_array_count,
                                  VR_ARRAY_COUNT(game_pose_array_count)
                                      TrackedDevicePose_t* game_pose_array,
                                  uint32_t game_pose_array_count) override;
  EVRCompositorError GetLastPoses(VR_ARRAY_COUNT(render_pose_array_count)
                                      TrackedDevicePose_t* render_pose_array,
                                  uint32_t render_pose_array_count,
                                  VR_ARRAY_COUNT(game_pose_array_count)
                                      TrackedDevicePose_t* game_pose_array,
                                  uint32_t game_pose_array_count) override {
    return mainApplication.m_pCompositor->GetLastPoses(render_pose_array, render_pose_array_count, game_pose_array, game_pose_array_count);
  }
  EVRCompositorError GetLastPoseForTrackedDeviceIndex(
      TrackedDeviceIndex_t device_index,
      TrackedDevicePose_t* output_pose,
      TrackedDevicePose_t* output_game_pose) override {
    return mainApplication.m_pCompositor->GetLastPoseForTrackedDeviceIndex(device_index, output_pose, output_game_pose);
  }
  EVRCompositorError Submit(
      EVREye eye,
      const Texture_t* texture,
      const VRTextureBounds_t* bounds = 0,
      EVRSubmitFlags submit_flags = Submit_Default) override;
  void ClearLastSubmittedFrame() override {
    mainApplication.m_pCompositor->ClearLastSubmittedFrame();
  }
  void PostPresentHandoff() override;
  bool GetFrameTiming(Compositor_FrameTiming* timing,
                      uint32_t frames_ago = 0) override;
  uint32_t GetFrameTimings(Compositor_FrameTiming* timing,
                           uint32_t frames) override {
    return mainApplication.m_pCompositor->GetFrameTimings(timing, frames);
  }
  float GetFrameTimeRemaining() override {
    return mainApplication.m_pCompositor->GetFrameTimeRemaining();
  }
  void GetCumulativeStats(Compositor_CumulativeStats* stats,
                          uint32_t stats_size_in_bytes) override {
    mainApplication.m_pCompositor->GetCumulativeStats(stats, stats_size_in_bytes);
  }
  void FadeToColor(float seconds,
                   float red,
                   float green,
                   float blue,
                   float alpha,
                   bool background = false) override {
    mainApplication.m_pCompositor->FadeToColor(seconds, seconds, red, green, blue, alpha);
  }
  HmdColor_t GetCurrentFadeColor(bool background = false) override {
    return mainApplication.m_pCompositor->GetCurrentFadeColor(background);
  }
  void FadeGrid(float seconds, bool fade_in) override {
    mainApplication.m_pCompositor->FadeGrid(seconds, fade_in);
  }
  float GetCurrentGridAlpha() override {
    return mainApplication.m_pCompositor->GetCurrentGridAlpha();
  }
  EVRCompositorError SetSkyboxOverride(VR_ARRAY_COUNT(texture_count)
                                           const Texture_t* textures,
                                       uint32_t texture_count) override {
    return mainApplication.m_pCompositor->SetSkyboxOverride(textures, texture_count);
  }
  void ClearSkyboxOverride() override {
    mainApplication.m_pCompositor->ClearSkyboxOverride();
  }
  void CompositorBringToFront() override {
    mainApplication.m_pCompositor->CompositorBringToFront();
  }
  void CompositorGoToBack() override {
    mainApplication.m_pCompositor->CompositorGoToBack();
  }
  void CompositorQuit() override {
    mainApplication.m_pCompositor->CompositorQuit();
  }
  bool IsFullscreen() override {
    return mainApplication.m_pCompositor->IsFullscreen();
  }
  uint32_t GetCurrentSceneFocusProcess() override {
    return mainApplication.m_pCompositor->GetCurrentSceneFocusProcess();
  }
  uint32_t GetLastFrameRenderer() override {
    return mainApplication.m_pCompositor->GetLastFrameRenderer();
  }
  bool CanRenderScene() override {
    return mainApplication.m_pCompositor->CanRenderScene();
  }
  void ShowMirrorWindow() override {
    mainApplication.m_pCompositor->ShowMirrorWindow();
  }
  void HideMirrorWindow() override {
    mainApplication.m_pCompositor->HideMirrorWindow();
  }
  bool IsMirrorWindowVisible() override {
    return mainApplication.m_pCompositor->IsMirrorWindowVisible();
  }
  void CompositorDumpImages() override {
    mainApplication.m_pCompositor->CompositorDumpImages();
  }
  bool ShouldAppRenderWithLowResources() override {
    return mainApplication.m_pCompositor->ShouldAppRenderWithLowResources();
  }
  void ForceInterleavedReprojectionOn(bool override) override {
    return mainApplication.m_pCompositor->ForceInterleavedReprojectionOn(override);
  }
  void ForceReconnectProcess() override {
    return mainApplication.m_pCompositor->ForceReconnectProcess();
  }
  void SuspendRendering(bool suspend) override;
  EVRCompositorError GetMirrorTextureD3D11(
      EVREye eye,
      void* d3d11_device_or_resource,
      void** d3d11_shader_resource_view) override {
    return mainApplication.m_pCompositor->GetMirrorTextureD3D11(eye, d3d11_device_or_resource, d3d11_shader_resource_view);
  }
  void ReleaseMirrorTextureD3D11(void* d3d11_shader_resource_view) override {
    mainApplication.m_pCompositor->ReleaseMirrorTextureD3D11(d3d11_shader_resource_view);
  }
  EVRCompositorError GetMirrorTextureGL(
      EVREye eye,
      glUInt_t* texture_id,
      glSharedTextureHandle_t* shared_texture_handle) override {
    return mainApplication.m_pCompositor->GetMirrorTextureGL(eye, texture_id, shared_texture_handle);
  }
  bool ReleaseSharedGLTexture(
      glUInt_t texture_id,
      glSharedTextureHandle_t shared_texture_handle) override {
    return mainApplication.m_pCompositor->ReleaseSharedGLTexture(texture_id, shared_texture_handle);
  }
  void LockGLSharedTextureForAccess(
      glSharedTextureHandle_t shared_texture_handle) override {
    mainApplication.m_pCompositor->LockGLSharedTextureForAccess(shared_texture_handle);
  }
  void UnlockGLSharedTextureForAccess(
      glSharedTextureHandle_t shared_texture_handle) override {
    mainApplication.m_pCompositor->UnlockGLSharedTextureForAccess(shared_texture_handle);
  }
  uint32_t GetVulkanInstanceExtensionsRequired(VR_OUT_STRING() char* value,
                                               uint32_t buffer_size) override {
    return mainApplication.m_pCompositor->GetVulkanInstanceExtensionsRequired(value, buffer_size);
  }
  uint32_t GetVulkanDeviceExtensionsRequired(
      VkPhysicalDevice_T* physical_device,
      VR_OUT_STRING() char* value,
      uint32_t buffer_size) override {
    return mainApplication.m_pCompositor->GetVulkanDeviceExtensionsRequired(physical_device, value, buffer_size);
  }
};

class TestVRClientCore : public IVRClientCore {
 public:
  std::string err;

  EVRInitError Init(EVRApplicationType application_type) override;
  void Cleanup() override;
  EVRInitError IsInterfaceVersionValid(const char* interface_version) override;
  void* GetGenericInterface(const char* name_and_version,
                            EVRInitError* error) override;
  bool BIsHmdPresent() override;
  const char* GetEnglishStringForHmdError(EVRInitError error) override {
    std::stringstream ss;
    ss << "error: " << (int)error << std::endl;
    err = ss.str();
    return err.c_str();
  }
  const char* GetIDForVRInitError(EVRInitError error) override {
    std::stringstream ss;
    ss << "error: " << (int)error << std::endl;
    err = ss.str();
    return err.c_str();
  }
};

TestHelper g_test_helper;
TestVRSystem g_system;
TestVRCompositor g_compositor;
TestVRClientCore g_loader;

EVRInitError TestVRClientCore::Init(EVRApplicationType application_type) {
  if (mainApplication.BInit()) {
    return VRInitError_None;
  } else {
    mainApplication.Shutdown();
    return VRInitError_Unknown;
  }
}

void TestVRClientCore::Cleanup() {
  mainApplication.Shutdown();
}

EVRInitError TestVRClientCore::IsInterfaceVersionValid(
    const char* interface_version) {
  return VRInitError_None;
}

void* TestVRClientCore::GetGenericInterface(const char* name_and_version,
                                            EVRInitError* error) {
  *error = VRInitError_None;
  if (strcmp(name_and_version, IVRSystem_Version) == 0)
    return static_cast<IVRSystem*>(&g_system);
  if (strcmp(name_and_version, IVRCompositor_Version) == 0)
    return static_cast<IVRCompositor*>(&g_compositor);
  /* if (strcmp(name_and_version, device::kChromeOpenVRTestHookAPI) == 0)
    return static_cast<device::ServiceTestHook*>(&g_test_helper); */

  *error = VRInitError_Init_InvalidInterface;
  return nullptr;
}

bool TestVRClientCore::BIsHmdPresent() {
  return vr::VR_IsHmdPresent();
}

void TestVRSystem::GetRecommendedRenderTargetSize(uint32_t* width,
                                                  uint32_t* height) {
  mainApplication.m_pHMD->GetRecommendedRenderTargetSize(width, height);
}

void TestVRSystem::GetDXGIOutputInfo(int32_t* adapter_index) {
  mainApplication.m_pHMD->GetDXGIOutputInfo(adapter_index);
}

void TestVRSystem::GetProjectionRaw(EVREye eye,
                                    float* left,
                                    float* right,
                                    float* top,
                                    float* bottom) {
  return mainApplication.m_pHMD->GetProjectionRaw(eye, left, right, top, bottom);
}

HmdMatrix34_t TestVRSystem::GetEyeToHeadTransform(EVREye eye) {
  return mainApplication.m_pHMD->GetEyeToHeadTransform(eye);
}

void TestVRSystem::GetDeviceToAbsoluteTrackingPose(
    ETrackingUniverseOrigin origin,
    float predicted_seconds_to_photons_from_now,
    VR_ARRAY_COUNT(tracked_device_pose_array_count)
        TrackedDevicePose_t* tracked_device_pose_array,
    uint32_t tracked_device_pose_array_count) {
  return mainApplication.m_pHMD->GetDeviceToAbsoluteTrackingPose(origin, predicted_seconds_to_photons_from_now, tracked_device_pose_array, tracked_device_pose_array_count);
}

bool TestVRSystem::PollNextEvent(VREvent_t *pEvent, unsigned int uncbVREvent) {
  return mainApplication.m_pHMD->PollNextEvent(pEvent, uncbVREvent);
}

bool TestVRSystem::GetControllerState(
    TrackedDeviceIndex_t controller_device_index,
    VRControllerState_t* controller_state,
    uint32_t controller_state_size) {
  return mainApplication.m_pHMD->GetControllerState(controller_device_index, controller_state, controller_state_size);
}

bool TestVRSystem::GetControllerStateWithPose(
    ETrackingUniverseOrigin origin,
    TrackedDeviceIndex_t controller_device_index,
    VRControllerState_t* controller_state,
    uint32_t controller_state_size,
    TrackedDevicePose_t* tracked_device_pose) {
  return mainApplication.m_pHMD->GetControllerStateWithPose(origin, controller_device_index, controller_state, controller_state_size, tracked_device_pose);
}

uint32_t TestVRSystem::GetStringTrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    VR_OUT_STRING() char* value,
    uint32_t buffer_size,
    ETrackedPropertyError* error) {
  return mainApplication.m_pHMD->GetStringTrackedDeviceProperty(device_index, prop, value, buffer_size, error);
}

float TestVRSystem::GetFloatTrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  return mainApplication.m_pHMD->GetFloatTrackedDeviceProperty(device_index, prop, error);
}

int32_t TestVRSystem::GetInt32TrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  return mainApplication.m_pHMD->GetInt32TrackedDeviceProperty(device_index, prop, error);
}

uint64_t TestVRSystem::GetUint64TrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  return mainApplication.m_pHMD->GetUint64TrackedDeviceProperty(device_index, prop, error);
}

HmdMatrix34_t TestVRSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
  return mainApplication.m_pHMD->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
}

ETrackedControllerRole TestVRSystem::GetControllerRoleForTrackedDeviceIndex(
    TrackedDeviceIndex_t device_index) {
  return mainApplication.m_pHMD->GetControllerRoleForTrackedDeviceIndex(device_index);
}

ETrackedDeviceClass TestVRSystem::GetTrackedDeviceClass(
    TrackedDeviceIndex_t device_index) {
  return mainApplication.m_pHMD->GetTrackedDeviceClass(device_index);
}

void TestVRCompositor::SuspendRendering(bool suspend) {
  mainApplication.m_pCompositor->SuspendRendering(suspend);
}

void TestVRCompositor::SetTrackingSpace(ETrackingUniverseOrigin origin) {
  mainApplication.m_pCompositor->SetTrackingSpace(origin);
}

EVRCompositorError TestVRCompositor::WaitGetPoses(TrackedDevicePose_t* poses1,
                                                  unsigned int count1,
                                                  TrackedDevicePose_t* poses2,
                                                  unsigned int count2) {
  return mainApplication.m_pCompositor->WaitGetPoses(poses1, count1, poses2, count2);
}

EVRCompositorError TestVRCompositor::Submit(EVREye eye,
                                            Texture_t const* texture,
                                            VRTextureBounds_t const* bounds,
                                            EVRSubmitFlags) {
  g_test_helper.OnPresentedFrame(reinterpret_cast<ID3D11Texture2D*>(texture->handle), bounds, eye);
  return VRCompositorError_None;
}

void TestVRCompositor::PostPresentHandoff() {}

bool TestVRCompositor::GetFrameTiming(Compositor_FrameTiming *pTiming, unsigned int unFramesAgo) {
  return mainApplication.m_pCompositor->GetFrameTiming(pTiming, unFramesAgo);
}

}  // namespace vr

extern "C" {
__declspec(dllexport) void* VRClientCoreFactory(const char* interface_name,
                                                int* return_code) {
  return &vr::g_loader;
}
}
