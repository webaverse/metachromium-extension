// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 ..
msbuild  ALL_BUILD.vcxproj

cd C:\Users\avaer\AppData\Local\Chromium\Application
set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality"
*/

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <memory>

#include "device/vr/openvr/test/test_helper.h"
#include "device/vr/test/test_hook.h"
#include "device/vr/windows/d3d11_device_helpers.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "third_party/openvr/src/src/ivrclientcore.h"

#include "device/vr/sample/hellovr_opengl_main.h"

std::ofstream out;
std::ofstream &getOut() {
  if (!out.is_open()) {
    out.open("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\log\\log.txt", std::ofstream::out|std::ofstream::app);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return out;
}

namespace vr {

CMainApplication mainApplication;

class TestVRSystem : public IVRSystem {
 public: 
  void GetRecommendedRenderTargetSize(uint32_t* width,
                                      uint32_t* height) override;
  HmdMatrix44_t GetProjectionMatrix(EVREye eye,
                                    float near_z,
                                    float far_z) override {
    // getOut() << "get projection  matrix" <<  std::endl;
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
  EVRInitError Init(EVRApplicationType application_type) override;
  void Cleanup() override;
  EVRInitError IsInterfaceVersionValid(const char* interface_version) override;
  void* GetGenericInterface(const char* name_and_version,
                            EVRInitError* error) override;
  bool BIsHmdPresent() override;
  const char* GetEnglishStringForHmdError(EVRInitError error) override {
    // getOut() << "GetEnglishStringForHmdError" << std::endl;
    std::stringstream ss;
    ss << "error: " << (int)error << std::endl;
    return ss.str().c_str();
  }
  const char* GetIDForVRInitError(EVRInitError error) override {
    // getOut() << "GetIDForVRInitError" << std::endl;
    std::stringstream ss;
    ss << "error: " << (int)error << std::endl;
    return ss.str().c_str();
  }
};

TestHelper g_test_helper;
TestVRSystem g_system;
TestVRCompositor g_compositor;
TestVRClientCore g_loader;

EVRInitError TestVRClientCore::Init(EVRApplicationType application_type) {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  // getOut() << "init 1 " << buf.data() << std::endl;
  // return VRInitError_None;
  SetEnvironmentVariable("VR_OVERRIDE", "");
  EVRInitError result;
  if (mainApplication.BInit()) {
    // getOut() << "init 2" << std::endl;
    result = VRInitError_None;
  } else {
    // getOut() << "init 3" << std::endl;
    mainApplication.Shutdown();
    // getOut() << "init 4" << std::endl;
    result = VRInitError_Unknown;
  }
  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
  return result;
}

void TestVRClientCore::Cleanup() {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  // getOut() << "Cleanup " << buf.data() << std::endl;
  // return;
  SetEnvironmentVariable("VR_OVERRIDE", "");
  mainApplication.Shutdown();
  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
}

EVRInitError TestVRClientCore::IsInterfaceVersionValid(
    const char* interface_version) {
  // getOut() << "IsInterfaceVersionValid" << std::endl;
  return VRInitError_None;
}

void* TestVRClientCore::GetGenericInterface(const char* name_and_version,
                                            EVRInitError* error) {
  // getOut() << "GetGenericInterface 0 " << name_and_version << std::endl;
  *error = VRInitError_None;
  if (strcmp(name_and_version, IVRSystem_Version) == 0) {
    // getOut() << "GetGenericInterface 1 " << name_and_version << std::endl;
    return static_cast<IVRSystem*>(&g_system);
  }
  if (strcmp(name_and_version, IVRCompositor_Version) == 0) {
    // getOut() << "GetGenericInterface 2 " << name_and_version << std::endl;
    return static_cast<IVRCompositor*>(&g_compositor);
  }
  /*  if (strcmp(name_and_version, device::kChromeOpenVRTestHookAPI) == 0) {
    getOut() << "GetGenericInterface 3 " << name_and_version << std::endl;
    return static_cast<device::ServiceTestHook*>(&g_test_helper);
  } */
  if (strcmp(name_and_version, "IVRChaperone_003") == 0) {
    // getOut() << "GetGenericInterface 4.1 " << name_and_version << std::endl;
    void *chaperone = vr::VRChaperone();
    // getOut() << "GetGenericInterface 4.2 " << (uintptr_t)chaperone << std::endl;
    return chaperone;
  }
  
  // getOut() << "GetGenericInterface 5 " << name_and_version << std::endl;

  *error = VRInitError_Init_InvalidInterface;
  return nullptr;
}

bool TestVRClientCore::BIsHmdPresent() {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  // getOut() << "BIsHmdPresent 0 " << buf.data() << std::endl;
  // return true;
  SetEnvironmentVariable("VR_OVERRIDE", "");
  // unsetenv("VR_OVERRIDE");
  bool result = vr::VR_IsHmdPresent();
  // getOut() << "BIsHmdPresent 1 " << result << std::endl;
  // getOut() << "BIsHmdPresent 2" << std::endl;
  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
  return result;
}

void TestVRSystem::GetRecommendedRenderTargetSize(uint32_t* width,
                                                  uint32_t* height) {
  // getOut() << "GetRecommendedRenderTargetSize 1 " << (uintptr_t)mainApplication.m_pHMD << std::endl;
  /* *width = 1024;
  *height = 768; */
  mainApplication.m_pHMD->GetRecommendedRenderTargetSize(width, height);
  // getOut() << "GetRecommendedRenderTargetSize 2 " << *width << " " << *height << std::endl;
}

void TestVRSystem::GetDXGIOutputInfo(int32_t* adapter_index) {
  // getOut() << "GetDXGIOutputInfo 1 " << (uintptr_t)adapter_index << std::endl;
  // *adapter_index = 0;
  mainApplication.m_pHMD->GetDXGIOutputInfo(adapter_index);
  // getOut() << "GetDXGIOutputInfo 2 " << *adapter_index << std::endl;
}

void TestVRSystem::GetProjectionRaw(EVREye eye,
                                    float* left,
                                    float* right,
                                    float* top,
                                    float* bottom) {
  // getOut() << "GetProjectionRaw" << std::endl;
  /* auto proj = g_test_helper.GetProjectionRaw(eye == EVREye::Eye_Left);
  *left = proj.projection[0];
  *right = proj.projection[1];
  *top = proj.projection[2];
  *bottom = proj.projection[3];
  return; */
  return mainApplication.GetProjectionRaw(eye, left, right, top, bottom);
}

HmdMatrix34_t TestVRSystem::GetEyeToHeadTransform(EVREye eye) {
  // getOut() << "GetEyeToHeadTransform" << std::endl;
  /* HmdMatrix34_t ret = {};
  ret.m[0][0] = 1;
  ret.m[1][1] = 1;
  ret.m[2][2] = 1;
  float ipd = g_test_helper.GetInterpupillaryDistance();
  ret.m[0][3] = ((eye == Eye_Left) ? 1 : -1) * ipd / 2;
  return ret; */
  return mainApplication.m_pHMD->GetEyeToHeadTransform(eye);
}

void TestVRSystem::GetDeviceToAbsoluteTrackingPose(
    ETrackingUniverseOrigin origin,
    float predicted_seconds_to_photons_from_now,
    VR_ARRAY_COUNT(tracked_device_pose_array_count)
        TrackedDevicePose_t* tracked_device_pose_array,
    uint32_t tracked_device_pose_array_count) {
  // getOut() << "GetDeviceToAbsoluteTrackingPose" << std::endl;
  /*  TrackedDevicePose_t pose = g_test_helper.GetPose(false);
  tracked_device_pose_array[0] = pose;
  for (unsigned int i = 1; i < tracked_device_pose_array_count; ++i) {
    TrackedDevicePose_t pose = {};
    tracked_device_pose_array[i] = pose;
  }
  return; */
  return mainApplication.m_pHMD->GetDeviceToAbsoluteTrackingPose(origin, predicted_seconds_to_photons_from_now, tracked_device_pose_array, tracked_device_pose_array_count);
}

bool TestVRSystem::PollNextEvent(VREvent_t *pEvent, unsigned int uncbVREvent) {
  // getOut() << "PollNextEvent" << std::endl;
  // return false;
  return mainApplication.m_pHMD->PollNextEvent(pEvent, uncbVREvent);
}

bool TestVRSystem::GetControllerState(
    TrackedDeviceIndex_t controller_device_index,
    VRControllerState_t* controller_state,
    uint32_t controller_state_size) {
  // getOut() << "GetControllerState" << std::endl;
  /* return g_test_helper.GetControllerState(controller_device_index,
                                          controller_state); */
  return mainApplication.m_pHMD->GetControllerState(controller_device_index, controller_state, controller_state_size);
}

bool TestVRSystem::GetControllerStateWithPose(
    ETrackingUniverseOrigin origin,
    TrackedDeviceIndex_t controller_device_index,
    VRControllerState_t* controller_state,
    uint32_t controller_state_size,
    TrackedDevicePose_t* tracked_device_pose) {
  // getOut() << "GetControllerStateWithPose" << std::endl;
  /* g_test_helper.GetControllerState(controller_device_index, controller_state);
  return g_test_helper.GetControllerPose(controller_device_index,
                                         tracked_device_pose); */
  return mainApplication.m_pHMD->GetControllerStateWithPose(origin, controller_device_index, controller_state, controller_state_size, tracked_device_pose);
}

uint32_t TestVRSystem::GetStringTrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    VR_OUT_STRING() char* value,
    uint32_t buffer_size,
    ETrackedPropertyError* error) {
  // getOut() << "GetStringTrackedDeviceProperty" << std::endl;
  /* if (error) {
    *error = TrackedProp_Success;
  }
  sprintf_s(value, buffer_size, "test-value");
  return 11; */
  return mainApplication.m_pHMD->GetStringTrackedDeviceProperty(device_index, prop, value, buffer_size, error);
}

float TestVRSystem::GetFloatTrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  // getOut() << "GetFloatTrackedDeviceProperty" << std::endl;
  /* if (error) {
    *error = TrackedProp_Success;
  }
  switch (prop) {
    case Prop_UserIpdMeters_Float:
      return g_test_helper.GetInterpupillaryDistance();
    default:
      NOTIMPLEMENTED();
  }
  return 0; */
  return mainApplication.m_pHMD->GetFloatTrackedDeviceProperty(device_index, prop, error);
}

int32_t TestVRSystem::GetInt32TrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  // getOut() << "GetInt32TrackedDeviceProperty" << std::endl;
  /* int32_t ret;
  ETrackedPropertyError err =
      g_test_helper.GetInt32TrackedDeviceProperty(device_index, prop, ret);
  if (err != TrackedProp_Success) {
    NOTIMPLEMENTED();
  }
  if (error) {
    *error = err;
  }
  return ret; */
  return mainApplication.m_pHMD->GetInt32TrackedDeviceProperty(device_index, prop, error);
}

uint64_t TestVRSystem::GetUint64TrackedDeviceProperty(
    TrackedDeviceIndex_t device_index,
    ETrackedDeviceProperty prop,
    ETrackedPropertyError* error) {
  // getOut() << "GetUint64TrackedDeviceProperty" << std::endl;
  /* uint64_t ret;
  ETrackedPropertyError err =
      g_test_helper.GetUint64TrackedDeviceProperty(device_index, prop, ret);
  if (err != TrackedProp_Success) {
    NOTIMPLEMENTED();
  }
  if (error) {
    *error = err;
  }
  return ret; */
  return mainApplication.m_pHMD->GetUint64TrackedDeviceProperty(device_index, prop, error);
}

HmdMatrix34_t TestVRSystem::GetSeatedZeroPoseToStandingAbsoluteTrackingPose() {
  // getOut() << "GetSeatedZeroPoseToStandingAbsoluteTrackingPose" << std::endl;
  /* HmdMatrix34_t ret = {};
  ret.m[0][0] = 1;
  ret.m[1][1] = 1;
  ret.m[2][2] = 1;
  ret.m[1][3] = 1.2f;
  return ret; */
  return mainApplication.m_pHMD->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
}

ETrackedControllerRole TestVRSystem::GetControllerRoleForTrackedDeviceIndex(
    TrackedDeviceIndex_t device_index) {
  // getOut() << "GetControllerRoleForTrackedDeviceIndex" << std::endl;
  // return g_test_helper.GetControllerRoleForTrackedDeviceIndex(device_index);
  return mainApplication.m_pHMD->GetControllerRoleForTrackedDeviceIndex(device_index);
}

ETrackedDeviceClass TestVRSystem::GetTrackedDeviceClass(
    TrackedDeviceIndex_t device_index) {
  // getOut() << "GetTrackedDeviceClass" << std::endl;
  // return g_test_helper.GetTrackedDeviceClass(device_index);
  return mainApplication.m_pHMD->GetTrackedDeviceClass(device_index);
}

void TestVRCompositor::SuspendRendering(bool suspend) {
  // getOut() << "SuspendRendering " << suspend << std::endl;
  // return;
  mainApplication.m_pCompositor->SuspendRendering(suspend);
}

void TestVRCompositor::SetTrackingSpace(ETrackingUniverseOrigin origin) {
  // getOut() << "SetTrackingSpace" << std::endl;
  // return;
  mainApplication.m_pCompositor->SetTrackingSpace(origin);
}

EVRCompositorError TestVRCompositor::WaitGetPoses(TrackedDevicePose_t* poses1,
                                                  unsigned int count1,
                                                  TrackedDevicePose_t* poses2,
                                                  unsigned int count2) {
  // getOut() << "WaitGetPoses 1" << std::endl;
  
  float fSecondsSinceLastVsync;
  mainApplication.m_pHMD->GetTimeSinceLastVsync( &fSecondsSinceLastVsync, NULL );
  float fDisplayFrequency = mainApplication.m_pHMD->GetFloatTrackedDeviceProperty( vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_DisplayFrequency_Float );
  float fFrameDuration = 1.f / fDisplayFrequency;
  float fVsyncToPhotons = mainApplication.m_pHMD->GetFloatTrackedDeviceProperty( vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SecondsFromVsyncToPhotons_Float );
  float fPredictedSecondsFromNow = fFrameDuration - fSecondsSinceLastVsync + fVsyncToPhotons;
  
  mainApplication.m_pHMD->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, fPredictedSecondsFromNow, poses1, count1);
  mainApplication.PreRender();
  return VRCompositorError_None;
  
  /* TrackedDevicePose_t pose;
  for (unsigned int i = 0; i < count1; ++i) {
    if (i != vr::k_unTrackedDeviceIndex_Hmd) {
      VRControllerState_t controller_state;
      g_test_helper.GetControllerPose(i, &pose);
      pose.bDeviceIsConnected =
          g_test_helper.GetControllerState(i, &controller_state);
    } else {
      pose = g_test_helper.GetPose(true);
      pose.bDeviceIsConnected = true;
    }
    poses1[i] = pose;
  }

  for (unsigned int i = 0; i < count2; ++i) {
    if (i != vr::k_unTrackedDeviceIndex_Hmd) {
      VRControllerState_t controller_state;
      g_test_helper.GetControllerPose(i, &pose);
      pose.bDeviceIsConnected =
          g_test_helper.GetControllerState(i, &controller_state);
    } else {
      pose = g_test_helper.GetPose(true);
      pose.bDeviceIsConnected = true;
    }
    poses2[i] = pose;
  }

  return VRCompositorError_None; */
  
  EVRCompositorError err = mainApplication.m_pCompositor->WaitGetPoses(poses1, count1, poses2, count2);
  if (!err) {
    mainApplication.PreRender();
  }
  // getOut() << "WaitGetPoses 2 " << (int)err << std::endl;
  return err;
}

EVRCompositorError TestVRCompositor::Submit(EVREye eye,
                                            Texture_t const* texture,
                                            VRTextureBounds_t const* bounds,
                                            EVRSubmitFlags) {
  ID3D11Texture2D *dxTexture = reinterpret_cast<ID3D11Texture2D*>(texture->handle);
  // g_test_helper.OnPresentedFrame(reinterpret_cast<ID3D11Texture2D*>(texture->handle), bounds, eye);
  // getOut() << "Submit " << bounds->uMin << " " << bounds->vMin << " " << bounds->uMax << " " << bounds->vMax << " " << (uintptr_t)dxTexture << std::endl;
  mainApplication.PostRender((uintptr_t)dxTexture);
  // vr::Texture_t rightEyeTexture = {(void*)(uintptr_t)dxTexture, vr::TextureType_DirectX, vr::ColorSpace_Gamma};
  // vr::VROverlay()->SetOverlayTexture(mainApplication.m_ulOverlayHandle, &rightEyeTexture);
  return VRCompositorError_None;
}

void TestVRCompositor::PostPresentHandoff() {}

bool TestVRCompositor::GetFrameTiming(Compositor_FrameTiming *pTiming, unsigned int unFramesAgo) {
  // getOut() << "GetFrameTiming" << std::endl;
  // return false;
  return mainApplication.m_pCompositor->GetFrameTiming(pTiming, unFramesAgo);
}

}  // namespace vr

extern "C" {
__declspec(dllexport) void* VRClientCoreFactory(const char* interface_name,
                                                int* return_code) {
  // getOut() << "core " << (uintptr_t)&vr::g_loader << std::endl;
  return &vr::g_loader;
}
}
