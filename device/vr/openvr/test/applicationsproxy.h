#ifndef _openvr_applicationsproxy_h_
#define _openvr_applicationsproxy_h_

// #include <deque>

#include <D3D11_4.h>
#include <DXGI1_4.h>
#include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRApplications : public IVRApplications {
public:
  IVRApplications *vrapplications;
  FnProxy &fnp;

  PVRApplications(IVRApplications *vrapplications, FnProxy &fnp);
	virtual vr::EVRApplicationError AddApplicationManifest(const char *pchApplicationManifestFullPath, bool bTemporary = false);
  virtual vr::EVRApplicationError RemoveApplicationManifest(const char *pchApplicationManifestFullPath);
  virtual bool IsApplicationInstalled(const char *pchAppKey);
  virtual uint32_t GetApplicationCount();
  virtual vr::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
  virtual vr::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
  virtual vr::EVRApplicationError LaunchApplication(const char *pchAppKey);
  virtual vr::EVRApplicationError LaunchTemplateApplication(const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT(unKeys) const vr::AppOverrideKeys_t *pKeys, uint32_t unKeys);
  virtual vr::EVRApplicationError LaunchApplicationFromMimeType(const char *pchMimeType, const char *pchArgs);
  virtual vr::EVRApplicationError LaunchDashboardOverlay(const char *pchAppKey);
  virtual bool CancelApplicationLaunch(const char *pchAppKey);
  virtual vr::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char *pchAppKey);
  virtual uint32_t GetApplicationProcessId(const char *pchAppKey);
  virtual const char *GetApplicationsErrorNameFromEnum(vr::EVRApplicationError error);
  virtual uint32_t GetApplicationPropertyString(const char *pchAppKey, vr::EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::EVRApplicationError *peError = nullptr);
  virtual bool GetApplicationPropertyBool(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError = nullptr);
  virtual uint64_t GetApplicationPropertyUint64(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError = nullptr);
  virtual vr::EVRApplicationError SetApplicationAutoLaunch(const char *pchAppKey, bool bAutoLaunch);
  virtual bool GetApplicationAutoLaunch(const char *pchAppKey);
  virtual vr::EVRApplicationError SetDefaultApplicationForMimeType(const char *pchAppKey, const char *pchMimeType);
  virtual bool GetDefaultApplicationForMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
  virtual bool GetApplicationSupportedMimeTypes(const char *pchAppKey, VR_OUT_STRING() char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer);
  virtual uint32_t GetApplicationsThatSupportMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer);
  virtual uint32_t GetApplicationLaunchArguments(uint32_t unHandle, VR_OUT_STRING() char *pchArgs, uint32_t unArgs);
  virtual vr::EVRApplicationError GetStartingApplication(VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
  virtual vr::EVRApplicationTransitionState GetTransitionState();
  virtual vr::EVRApplicationError PerformApplicationPrelaunchCheck(const char *pchAppKey);
  virtual const char *GetApplicationsTransitionStateNameFromEnum(vr::EVRApplicationTransitionState state);
  virtual bool IsQuitUserPromptRequested();
  virtual vr::EVRApplicationError LaunchInternalProcess(const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory);
  virtual uint32_t GetCurrentSceneProcessId();
};
}

#endif