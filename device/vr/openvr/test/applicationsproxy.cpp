// #include <chrono>
#include "device/vr/openvr/test/applicationsproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRApplications_AddApplicationManifest[] = "Applications::AddApplicationManifest";
char kIVRApplications_RemoveApplicationManifest[] = "Applications::RemoveApplicationManifest";
char kIVRApplications_IsApplicationInstalled[] = "Applications::IsApplicationInstalled";
char kIVRApplications_GetApplicationCount[] = "Applications::GetApplicationCount";
char kIVRApplications_GetApplicationKeyByIndex[] = "Applications::GetApplicationKeyByIndex";
char kIVRApplications_GetApplicationKeyByProcessId[] = "Applications::GetApplicationKeyByProcessId";
char kIVRApplications_LaunchApplication[] = "Applications::LaunchApplication";
char kIVRApplications_LaunchTemplateApplication[] = "Applications::LaunchTemplateApplication";
char kIVRApplications_LaunchApplicationFromMimeType[] = "Applications::LaunchApplicationFromMimeType";
char kIVRApplications_LaunchDashboardOverlay[] = "Applications::LaunchDashboardOverlay";
char kIVRApplications_CancelApplicationLaunch[] = "Applications::CancelApplicationLaunch";
char kIVRApplications_IdentifyApplication[] = "Applications::IdentifyApplication";
char kIVRApplications_GetApplicationProcessId[] = "Applications::GetApplicationProcessId";
char kIVRApplications_GetApplicationsErrorNameFromEnum[] = "Applications::GetApplicationsErrorNameFromEnum";
char kIVRApplications_GetApplicationPropertyString[] = "Applications::GetApplicationPropertyString";
char kIVRApplications_GetApplicationPropertyBool[] = "Applications::GetApplicationPropertyBool";
char kIVRApplications_GetApplicationPropertyUint64[] = "Applications::GetApplicationPropertyUint64";
char kIVRApplications_SetApplicationAutoLaunch[] = "Applications::SetApplicationAutoLaunch";
char kIVRApplications_GetApplicationAutoLaunch[] = "Applications::GetApplicationAutoLaunch";
char kIVRApplications_SetDefaultApplicationForMimeType[] = "Applications::SetDefaultApplicationForMimeType";
char kIVRApplications_GetDefaultApplicationForMimeType[] = "Applications::GetDefaultApplicationForMimeType";
char kIVRApplications_GetApplicationSupportedMimeTypes[] = "Applications::GetApplicationSupportedMimeTypes";
char kIVRApplications_GetApplicationsThatSupportMimeType[] = "Applications::GetApplicationsThatSupportMimeType";
char kIVRApplications_GetApplicationLaunchArguments[] = "Applications::GetApplicationLaunchArguments";
char kIVRApplications_GetStartingApplication[] = "Applications::GetStartingApplication";
char kIVRApplications_GetTransitionState[] = "Applications::GetTransitionState";
char kIVRApplications_PerformApplicationPrelaunchCheck[] = "Applications::PerformApplicationPrelaunchCheck";
char kIVRApplications_GetApplicationsTransitionStateNameFromEnum[] = "Applications::GetApplicationsTransitionStateNameFromEnum";
char kIVRApplications_IsQuitUserPromptRequested[] = "Applications::IsQuitUserPromptRequested";
char kIVRApplications_LaunchInternalProcess[] = "Applications::LaunchInternalProcess";
char kIVRApplications_GetCurrentSceneProcessId[] = "Applications::GetCurrentSceneProcessId";

PVRApplications::PVRApplications(IVRApplications *vrapplications, FnProxy &fnp) : vrapplications(vrapplications), fnp(fnp) {
  fnp.reg<
    kIVRRenderModels_AddApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >([=](managed_binary<char> applicationManifestFullPath, bool bTemporary) {
    return vrapplications->AddApplicationManifest(applicationManifestFullPath.data(), bTemporary);
  });
  fnp.reg<
    kIVRRenderModels_RemoveApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> applicationManifestFullPath) {
    return vrapplications->RemoveApplicationManifest(applicationManifestFullPath.data());
  });
  fnp.reg<
    kIVRRenderModels_IsApplicationInstalled,
    bool,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->IsApplicationInstalled(appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationCount,
    uint32_t
  >([=]() {
    return vrapplications->GetApplicationCount();
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationKeyByIndex,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unApplicationIndex, uint32_t unAppKeyBufferLen) {
    managed_binary<char> appKeyBuffer(unAppKeyBufferLen);
    auto result = vrapplications->GetApplicationKeyByIndex(unApplicationIndex, appKeyBuffer.data(), unAppKeyBufferLen);
    return std::tuple<vr::EVRApplicationError, managed_binary<char>>(
      result,
      std::move(appKeyBuffer)
    );
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationKeyByProcessId,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unApplicationIndex, uint32_t unAppKeyBufferLen) {
    managed_binary<char> appKeyBuffer(unAppKeyBufferLen);
    auto result = vrapplications->GetApplicationKeyByProcessId(unApplicationIndex, appKeyBuffer.data(), unAppKeyBufferLen);
    return std::tuple<vr::EVRApplicationError, managed_binary<char>>(
      result,
      std::move(appKeyBuffer)
    );
  });
  fnp.reg<
    kIVRRenderModels_LaunchApplication,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->LaunchApplication(appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_LaunchTemplateApplication,
    std::tuple<vr::EVRApplicationError, managed_binary<vr::AppOverrideKeys_t>>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> appKey, managed_binary<char> newAppKey, uint32_t unKeys) {
    managed_binary<vr::AppOverrideKeys_t> keys(unKeys);
    auto result = vrapplications->LaunchTemplateApplication(appKey.data(), newAppKey.data(), keys.data(), unKeys);
    return std::tuple<vr::EVRApplicationError, managed_binary<vr::AppOverrideKeys_t>>(
      result,
      std::move(keys)
    );
  });
  fnp.reg<
    kIVRRenderModels_LaunchApplicationFromMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> mimeType, managed_binary<char> args) {
    return vrapplications->LaunchApplicationFromMimeType(mimeType.data(), args.data());
  });
  fnp.reg<
    kIVRRenderModels_LaunchDashboardOverlay,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->LaunchDashboardOverlay(appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_CancelApplicationLaunch,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->CancelApplicationLaunch(appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_IdentifyApplication,
    vr::EVRApplicationError,
    uint32_t,
    managed_binary<char>
  >([=](uint32_t unProcessId, managed_binary<char> appKey) {
    return vrapplications->IdentifyApplication(unProcessId, appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationProcessId,
    uint32_t,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->GetApplicationProcessId(appKey.data());
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationsErrorNameFromEnum,
    int
  >([=]() {
    getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationPropertyString,
    std::tuple<uint32_t, managed_binary<char>, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty,
    uint32_t
  >([=](managed_binary<char> appKey, vr::EVRApplicationProperty eProperty, uint32_t unPropertyValueBufferLen) {
    managed_binary<char> propertyValueBuffer(unPropertyValueBufferLen);
    vr::EVRApplicationError error;
    auto result = vrapplications->GetApplicationPropertyString(appKey.data(), eProperty, propertyValueBuffer.data(), unPropertyValueBufferLen, &error);
    return std::tuple<uint32_t, managed_binary<char>, vr::EVRApplicationError>(
      result,
      std::move(propertyValueBuffer),
      error
    );
  });
  fnp.reg<
    kIVRRenderModels_GetApplicationPropertyBool,
    std::tuple<bool, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty
  >([=](managed_binary<char> appKey, vr::EVRApplicationProperty eProperty) {
    vr::EVRApplicationError error;
    auto result = vrapplications->GetApplicationPropertyBool(appKey.data(), eProperty, &error);
    return std::tuple<bool, vr::EVRApplicationError>(
      result,
      error
    );
  });
}
vr::EVRApplicationError PVRApplications::AddApplicationManifest(const char *pchApplicationManifestFullPath, bool bTemporary) {
  managed_binary<char> applicationManifestFullPath(strlen(pchApplicationManifestFullPath)+1);
  memcpy(applicationManifestFullPath.data(), pchApplicationManifestFullPath, applicationManifestFullPath.size());

  return fnp.call<
    kIVRRenderModels_AddApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >(std::move(applicationManifestFullPath), bTemporary);
}
vr::EVRApplicationError PVRApplications::RemoveApplicationManifest(const char *pchApplicationManifestFullPath) {
  managed_binary<char> applicationManifestFullPath(strlen(pchApplicationManifestFullPath)+1);
  memcpy(applicationManifestFullPath.data(), pchApplicationManifestFullPath, applicationManifestFullPath.size());

  return fnp.call<
    kIVRRenderModels_RemoveApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>
  >(applicationManifestFullPath);
}
bool PVRApplications::IsApplicationInstalled(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_IsApplicationInstalled,
    bool,
    managed_binary<char>
  >(std::move(appKey));
}
uint32_t PVRApplications::GetApplicationCount() {
  return fnp.call<
    kIVRRenderModels_GetApplicationCount,
    uint32_t
  >();
}
vr::EVRApplicationError PVRApplications::GetApplicationKeyByIndex(uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRRenderModels_GetApplicationKeyByIndex,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unApplicationIndex, unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::GetApplicationKeyByProcessId(uint32_t unProcessId, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRRenderModels_GetApplicationKeyByProcessId,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unProcessId, unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::LaunchApplication(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_LaunchApplication,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(appKey));
}
vr::EVRApplicationError PVRApplications::LaunchTemplateApplication(const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT(unKeys) const vr::AppOverrideKeys_t *pKeys, uint32_t unKeys) {
  managed_binary<char> appKey(strlen(pchTemplateAppKey)+1);
  memcpy(appKey.data(), pchTemplateAppKey, appKey.size());
  managed_binary<char> appKey(strlen(pchNewAppKey)+1);
  memcpy(newAppKey.data(), pchNewAppKey, newAppKey.size());

  return fnp.call<
    kIVRRenderModels_LaunchTemplateApplication,
    std::tuple<vr::EVRApplicationError, managed_binary<vr::AppOverrideKeys_t>>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >(std::move(appKey), std::move(newAppKey), unKeys);
}
vr::EVRApplicationError PVRApplications::LaunchApplicationFromMimeType(const char *pchMimeType, const char *pchArgs) {
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());
  managed_binary<char> appKey(strlen(pchArgs)+1);
  memcpy(args.data(), pchArgs, args.size());

  return fnp.call<
    kIVRRenderModels_LaunchApplicationFromMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(mimeType), std::move(args));
}
vr::EVRApplicationError PVRApplications::LaunchDashboardOverlay(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_LaunchDashboardOverlay,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(appKey));
}
bool PVRApplications::CancelApplicationLaunch(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_CancelApplicationLaunch,
    bool,
    managed_binary<char>
  >(std::move(appKey));
}
vr::EVRApplicationError PVRApplications::IdentifyApplication(uint32_t unProcessId, const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_IdentifyApplication,
    vr::EVRApplicationError,
    uint32_t,
    managed_binary<char>
  >(unProcessId, std::move(appKey));
}
uint32_t PVRApplications::GetApplicationProcessId(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_GetApplicationProcessId,
    uint32_t,
    managed_binary<char>
  >(std::move(appKey));
}
const char *PVRApplications::GetApplicationsErrorNameFromEnum(vr::EVRApplicationError error) {
  getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
  abort();
  return "";
}
uint32_t PVRApplications::GetApplicationPropertyString(const char *pchAppKey, vr::EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::EVRApplicationError *peError) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  auto result = fnp.call<
    kIVRRenderModels_GetApplicationPropertyString,
    std::tuple<uint32_t, managed_binary<char>, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty,
    uint32_t
  >(std::move(appKey), eProperty, unPropertyValueBufferLen);
  memcpy(pchPropertyValueBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  if (peError) {
    *peError = std::get<2>(result);
  }
  return std::get<0>(result);
}
bool PVRApplications::GetApplicationPropertyBool(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  auto result = fnp.call<
    kIVRRenderModels_GetApplicationPropertyBool,
    std::tuple<bool, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty
  >(std::move(appKey), eProperty);
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
uint64_t PVRApplications::GetApplicationPropertyUint64(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  auto result = fnp.call<
    kIVRRenderModels_GetApplicationPropertyUint64,
    std::tuple<uint64_t, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty
  >(std::move(appKey), eProperty);
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::SetApplicationAutoLaunch(const char *pchAppKey, bool bAutoLaunch) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_SetApplicationAutoLaunch,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >(std::move(appKey), bAutoLaunch);
}
bool PVRApplications::GetApplicationAutoLaunch(const char *pchAppKey) {

}
vr::EVRApplicationError PVRApplications::SetDefaultApplicationForMimeType(const char *pchAppKey, const char *pchMimeType) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());

  return fnp.call<
    kIVRRenderModels_SetDefaultApplicationForMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(appKey), std::move(mimeType));
}
bool PVRApplications::GetDefaultApplicationForMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());
  managed_binary<char> appKeyBuffer(strlen(pchAppKeyBuffer)+1);
  memcpy(appKeyBuffer.data(), pchAppKeyBuffer, appKeyBuffer.size());

  auto result = fnp.call<
    kIVRRenderModels_GetDefaultApplicationForMimeType,
    std::tuple<bool, managed_binary<char>>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >(std::move(mimeType), std::move(appKeyBuffer), unAppKeyBufferLen);
  memcpy(pchMimeTypesBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
bool PVRApplications::GetApplicationSupportedMimeTypes(const char *pchAppKey, VR_OUT_STRING() char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) {
  managed_binary<char> mimeType(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  auto result = fnp.call<
    kIVRRenderModels_GetApplicationSupportedMimeTypes,
    std::tuple<bool, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >(std::move(appKey), unMimeTypesBuffer);
  memcpy(pchMimeTypesBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
uint32_t PVRApplications::GetApplicationsThatSupportMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) {
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());

  auto result = fnp.call<
    kIVRRenderModels_GetApplicationsThatSupportMimeType,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >(std::move(mimeType), unAppKeysThatSupportBuffer);
  memcpy(pchAppKeysThatSupportBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
uint32_t PVRApplications::GetApplicationLaunchArguments(uint32_t unHandle, VR_OUT_STRING() char *pchArgs, uint32_t unArgs) {
  auto result = fnp.call<
    kIVRRenderModels_GetApplicationLaunchArguments,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unHandle, unArgs);
  memcpy(pchArgs, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::GetStartingApplication(VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRRenderModels_GetStartingApplication,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t
  >(unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationTransitionState PVRApplications::GetTransitionState() {
  return fnp.call<
    kIVRRenderModels_GetTransitionState,
    vr::EVRApplicationTransitionState
  >();
}
vr::EVRApplicationError PVRApplications::PerformApplicationPrelaunchCheck(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRRenderModels_PerformApplicationPrelaunchCheck,
    vr::EVRApplicationTransitionState
  >();
}
const char *PVRApplications::GetApplicationsTransitionStateNameFromEnum(vr::EVRApplicationTransitionState state) {
  getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
  abort();
  return "";
}
bool PVRApplications::IsQuitUserPromptRequested() {
  return fnp.call<
    kIVRRenderModels_IsQuitUserPromptRequested,
    bool
  >();
}
vr::EVRApplicationError PVRApplications::LaunchInternalProcess(const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory) {
  managed_binary<char> binaryPath(strlen(pchBinaryPath)+1);
  memcpy(binaryPath.data(), pchBinaryPath, binaryPath.size());
  managed_binary<char> arguments(strlen(pchArguments)+1);
  memcpy(arguments.data(), pchArguments, pchArguments.size());
  managed_binary<char> workingDirectory(strlen(pchWorkingDirectory)+1);
  memcpy(workingDirectory.data(), pchWorkingDirectory, workingDirectory.size());

  return fnp.call<
    kIVRRenderModels_LaunchInternalProcess,
    vr::EVRApplicationError
  >(std::move(binaryPath), std::move(arguments), std::move(workingDirectory));
}
uint32_t PVRApplications::GetCurrentSceneProcessId() {
  return fnp.call<
    kIVRRenderModels_GetCurrentSceneProcessId,
    uint32_t
  >();
}
}