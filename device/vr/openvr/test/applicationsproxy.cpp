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
// char kIVRApplications_GetTransitionState[] = "Applications::GetTransitionState";
char kIVRApplications_GetSceneApplicationState[] = "Applications::GetSceneApplicationState";
char kIVRApplications_PerformApplicationPrelaunchCheck[] = "Applications::PerformApplicationPrelaunchCheck";
char kIVRApplications_GetSceneApplicationStateNameFromEnum[] = "Applications::GetSceneApplicationState";
// char kIVRApplications_GetApplicationsTransitionStateNameFromEnum[] = "Applications::GetApplicationsTransitionStateNameFromEnum";
char kIVRApplications_IsQuitUserPromptRequested[] = "Applications::IsQuitUserPromptRequested";
char kIVRApplications_LaunchInternalProcess[] = "Applications::LaunchInternalProcess";
char kIVRApplications_GetCurrentSceneProcessId[] = "Applications::GetCurrentSceneProcessId";

PVRApplications::PVRApplications(IVRApplications *vrapplications, FnProxy &fnp) : vrapplications(vrapplications), fnp(fnp) {
  fnp.reg<
    kIVRApplications_AddApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >([=](managed_binary<char> applicationManifestFullPath, bool bTemporary) {
    return vrapplications->AddApplicationManifest(applicationManifestFullPath.data(), bTemporary);
  });
  fnp.reg<
    kIVRApplications_RemoveApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> applicationManifestFullPath) {
    return vrapplications->RemoveApplicationManifest(applicationManifestFullPath.data());
  });
  fnp.reg<
    kIVRApplications_IsApplicationInstalled,
    bool,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->IsApplicationInstalled(appKey.data());
  });
  fnp.reg<
    kIVRApplications_GetApplicationCount,
    uint32_t
  >([=]() {
    return vrapplications->GetApplicationCount();
  });
  fnp.reg<
    kIVRApplications_GetApplicationKeyByIndex,
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
    kIVRApplications_GetApplicationKeyByProcessId,
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
    kIVRApplications_LaunchApplication,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->LaunchApplication(appKey.data());
  });
  fnp.reg<
    kIVRApplications_LaunchTemplateApplication,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>,
    managed_binary<vr::AppOverrideKeys_t>
  >([=](managed_binary<char> appKey, managed_binary<char> newAppKey, managed_binary<vr::AppOverrideKeys_t> keys) {
    return vrapplications->LaunchTemplateApplication(appKey.data(), newAppKey.data(), keys.data(), keys.size());
  });
  fnp.reg<
    kIVRApplications_LaunchApplicationFromMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> mimeType, managed_binary<char> args) {
    return vrapplications->LaunchApplicationFromMimeType(mimeType.data(), args.data());
  });
  fnp.reg<
    kIVRApplications_LaunchDashboardOverlay,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->LaunchDashboardOverlay(appKey.data());
  });
  fnp.reg<
    kIVRApplications_CancelApplicationLaunch,
    bool,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->CancelApplicationLaunch(appKey.data());
  });
  fnp.reg<
    kIVRApplications_IdentifyApplication,
    vr::EVRApplicationError,
    uint32_t,
    managed_binary<char>
  >([=](uint32_t unProcessId, managed_binary<char> appKey) {
    return vrapplications->IdentifyApplication(unProcessId, appKey.data());
  });
  fnp.reg<
    kIVRApplications_GetApplicationProcessId,
    uint32_t,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->GetApplicationProcessId(appKey.data());
  });
  fnp.reg<
    kIVRApplications_GetApplicationsErrorNameFromEnum,
    int
  >([=]() {
    getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRApplications_GetApplicationPropertyString,
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
    kIVRApplications_GetApplicationPropertyBool,
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
  fnp.reg<
    kIVRApplications_GetApplicationPropertyUint64,
    std::tuple<uint64_t, vr::EVRApplicationError>,
    managed_binary<char>,
    vr::EVRApplicationProperty
  >([=](managed_binary<char> appKey, vr::EVRApplicationProperty eProperty) {
    vr::EVRApplicationError error;
    auto result = vrapplications->GetApplicationPropertyUint64(appKey.data(), eProperty, &error);
    return std::tuple<uint64_t, vr::EVRApplicationError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRApplications_SetApplicationAutoLaunch,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >([=](managed_binary<char> appKey, bool bAutoLaunch) {
    return vrapplications->SetApplicationAutoLaunch(appKey.data(), bAutoLaunch);
  });
  fnp.reg<
    kIVRApplications_GetApplicationAutoLaunch,
    bool,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->GetApplicationAutoLaunch(appKey.data());
  });
  fnp.reg<
    kIVRApplications_SetDefaultApplicationForMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> appKey, managed_binary<char> mimeType) {
    return vrapplications->SetDefaultApplicationForMimeType(appKey.data(), mimeType.data());
  });
  fnp.reg<
    kIVRApplications_GetDefaultApplicationForMimeType,
    std::tuple<bool, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> mimeType, uint32_t unAppKeyBufferLen) {
    managed_binary<char> appKeyBuffer(unAppKeyBufferLen);
    auto result = vrapplications->GetDefaultApplicationForMimeType(mimeType.data(), appKeyBuffer.data(), unAppKeyBufferLen);
    return std::tuple<bool, managed_binary<char>>(
      result,
      std::move(appKeyBuffer)
    );
  });
  fnp.reg<
    kIVRApplications_GetApplicationSupportedMimeTypes,
    std::tuple<bool, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> appKey, uint32_t unMimeTypesBuffer) {
    managed_binary<char> mimeTypesBuffer(unMimeTypesBuffer);
    auto result = vrapplications->GetApplicationSupportedMimeTypes(appKey.data(), mimeTypesBuffer.data(), unMimeTypesBuffer);
    return std::tuple<bool, managed_binary<char>>(
      result,
      std::move(mimeTypesBuffer)
    );
  });
  fnp.reg<
    kIVRApplications_GetApplicationsThatSupportMimeType,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> mimeType, uint32_t unAppKeysThatSupportBuffer) {
    managed_binary<char> ppKeysThatSupportBuffer(unAppKeysThatSupportBuffer);
    auto result = vrapplications->GetApplicationsThatSupportMimeType(mimeType.data(), ppKeysThatSupportBuffer.data(), unAppKeysThatSupportBuffer);
    return std::tuple<uint32_t, managed_binary<char>>(
      result,
      std::move(ppKeysThatSupportBuffer)
    );
  });
  fnp.reg<
    kIVRApplications_GetApplicationLaunchArguments,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unHandle, uint32_t unArgs) {
    managed_binary<char> args(unArgs);
    auto result = vrapplications->GetApplicationLaunchArguments(unHandle, args.data(), unArgs);
    return std::tuple<uint32_t, managed_binary<char>>(
      result,
      std::move(args)
    );
  });
  fnp.reg<
    kIVRApplications_GetStartingApplication,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t
  >([=](uint32_t unAppKeyBufferLen) {
    managed_binary<char> appKeyBuffer(unAppKeyBufferLen);
    auto result = vrapplications->GetStartingApplication(appKeyBuffer.data(), unAppKeyBufferLen);
    return std::tuple<vr::EVRApplicationError, managed_binary<char>>(
      result,
      std::move(appKeyBuffer)
    );
  });
  /* fnp.reg<
    kIVRApplications_GetTransitionState
  >([=](uint32_t unAppKeyBufferLen) {
    return vrapplications->GetTransitionState();
  }); */
  fnp.reg<
    kIVRApplications_GetSceneApplicationState,
    EVRSceneApplicationState
  >([=]() {
    return vrapplications->GetSceneApplicationState();
  });
  fnp.reg<
    kIVRApplications_PerformApplicationPrelaunchCheck,
    vr::EVRApplicationError,
    managed_binary<char>
  >([=](managed_binary<char> appKey) {
    return vrapplications->PerformApplicationPrelaunchCheck(appKey.data());
  });
  fnp.reg<
    kIVRApplications_GetSceneApplicationStateNameFromEnum,
    int
  >([=]() {
    getOut() << "GetSceneApplicationStateNameFromEnum abort" << std::endl;
    abort();
    return 0;
    // return vrapplications->GetSceneApplicationStateNameFromEnum(state);
  });
  /* fnp.reg<
    kIVRApplications_GetApplicationsTransitionStateNameFromEnum,
    int
  >([=]() {
    getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRApplications_IsQuitUserPromptRequested,
    bool
  >([=]() {
    return vrapplications->IsQuitUserPromptRequested();
  }); */
  fnp.reg<
    kIVRApplications_LaunchInternalProcess,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> binaryPath, managed_binary<char> arguments, managed_binary<char> workingDirectory) {
    return vrapplications->LaunchInternalProcess(binaryPath.data(), arguments.data(), workingDirectory.data());
  });
  fnp.reg<
    kIVRApplications_GetCurrentSceneProcessId,
    uint32_t
  >([=]() {
    return vrapplications->GetCurrentSceneProcessId();
  });
}
vr::EVRApplicationError PVRApplications::AddApplicationManifest(const char *pchApplicationManifestFullPath, bool bTemporary) {
  managed_binary<char> applicationManifestFullPath(strlen(pchApplicationManifestFullPath)+1);
  memcpy(applicationManifestFullPath.data(), pchApplicationManifestFullPath, applicationManifestFullPath.size());

  return fnp.call<
    kIVRApplications_AddApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >(std::move(applicationManifestFullPath), bTemporary);
}
vr::EVRApplicationError PVRApplications::RemoveApplicationManifest(const char *pchApplicationManifestFullPath) {
  managed_binary<char> applicationManifestFullPath(strlen(pchApplicationManifestFullPath)+1);
  memcpy(applicationManifestFullPath.data(), pchApplicationManifestFullPath, applicationManifestFullPath.size());

  return fnp.call<
    kIVRApplications_RemoveApplicationManifest,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(applicationManifestFullPath));
}
bool PVRApplications::IsApplicationInstalled(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_IsApplicationInstalled,
    bool,
    managed_binary<char>
  >(std::move(appKey));
}
uint32_t PVRApplications::GetApplicationCount() {
  return fnp.call<
    kIVRApplications_GetApplicationCount,
    uint32_t
  >();
}
vr::EVRApplicationError PVRApplications::GetApplicationKeyByIndex(uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRApplications_GetApplicationKeyByIndex,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unApplicationIndex, unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::GetApplicationKeyByProcessId(uint32_t unProcessId, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRApplications_GetApplicationKeyByProcessId,
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
    kIVRApplications_LaunchApplication,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(appKey));
}
vr::EVRApplicationError PVRApplications::LaunchTemplateApplication(const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT(unKeys) const vr::AppOverrideKeys_t *pKeys, uint32_t unKeys) {
  managed_binary<char> appKey(strlen(pchTemplateAppKey)+1);
  memcpy(appKey.data(), pchTemplateAppKey, appKey.size());
  managed_binary<char> newAppKey(strlen(pchNewAppKey)+1);
  memcpy(newAppKey.data(), pchNewAppKey, newAppKey.size());
  managed_binary<vr::AppOverrideKeys_t> keys(unKeys);
  memcpy(keys.data(), pKeys, unKeys * sizeof(vr::AppOverrideKeys_t));

  return fnp.call<
    kIVRApplications_LaunchTemplateApplication,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>,
    managed_binary<vr::AppOverrideKeys_t>
  >(std::move(appKey), std::move(newAppKey), std::move(keys));
}
vr::EVRApplicationError PVRApplications::LaunchApplicationFromMimeType(const char *pchMimeType, const char *pchArgs) {
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());
  managed_binary<char> args(strlen(pchArgs)+1);
  memcpy(args.data(), pchArgs, args.size());

  return fnp.call<
    kIVRApplications_LaunchApplicationFromMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(mimeType), std::move(args));
}
vr::EVRApplicationError PVRApplications::LaunchDashboardOverlay(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_LaunchDashboardOverlay,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(appKey));
}
bool PVRApplications::CancelApplicationLaunch(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_CancelApplicationLaunch,
    bool,
    managed_binary<char>
  >(std::move(appKey));
}
vr::EVRApplicationError PVRApplications::IdentifyApplication(uint32_t unProcessId, const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_IdentifyApplication,
    vr::EVRApplicationError,
    uint32_t,
    managed_binary<char>
  >(unProcessId, std::move(appKey));
}
uint32_t PVRApplications::GetApplicationProcessId(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_GetApplicationProcessId,
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
    kIVRApplications_GetApplicationPropertyString,
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
    kIVRApplications_GetApplicationPropertyBool,
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
    kIVRApplications_GetApplicationPropertyUint64,
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
    kIVRApplications_SetApplicationAutoLaunch,
    vr::EVRApplicationError,
    managed_binary<char>,
    bool
  >(std::move(appKey), bAutoLaunch);
}
bool PVRApplications::GetApplicationAutoLaunch(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_GetApplicationAutoLaunch,
    bool,
    managed_binary<char>
  >(std::move(appKey));
}
vr::EVRApplicationError PVRApplications::SetDefaultApplicationForMimeType(const char *pchAppKey, const char *pchMimeType) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());

  return fnp.call<
    kIVRApplications_SetDefaultApplicationForMimeType,
    vr::EVRApplicationError,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(appKey), std::move(mimeType));
}
bool PVRApplications::GetDefaultApplicationForMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  managed_binary<char> mimeType(strlen(pchMimeType)+1);
  memcpy(mimeType.data(), pchMimeType, mimeType.size());

  auto result = fnp.call<
    kIVRApplications_GetDefaultApplicationForMimeType,
    std::tuple<bool, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >(std::move(mimeType), unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
bool PVRApplications::GetApplicationSupportedMimeTypes(const char *pchAppKey, VR_OUT_STRING() char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  auto result = fnp.call<
    kIVRApplications_GetApplicationSupportedMimeTypes,
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
    kIVRApplications_GetApplicationsThatSupportMimeType,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    uint32_t
  >(std::move(mimeType), unAppKeysThatSupportBuffer);
  memcpy(pchAppKeysThatSupportBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
uint32_t PVRApplications::GetApplicationLaunchArguments(uint32_t unHandle, VR_OUT_STRING() char *pchArgs, uint32_t unArgs) {
  auto result = fnp.call<
    kIVRApplications_GetApplicationLaunchArguments,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unHandle, unArgs);
  memcpy(pchArgs, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
vr::EVRApplicationError PVRApplications::GetStartingApplication(VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  auto result = fnp.call<
    kIVRApplications_GetStartingApplication,
    std::tuple<vr::EVRApplicationError, managed_binary<char>>,
    uint32_t
  >(unAppKeyBufferLen);
  memcpy(pchAppKeyBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
/* vr::EVRApplicationTransitionState PVRApplications::GetTransitionState() {
  return fnp.call<
    kIVRApplications_GetTransitionState,
    vr::EVRApplicationTransitionState
  >();
} */
EVRSceneApplicationState PVRApplications::GetSceneApplicationState() {
  return fnp.call<
    kIVRApplications_GetSceneApplicationState,
    EVRSceneApplicationState
  >();
}
vr::EVRApplicationError PVRApplications::PerformApplicationPrelaunchCheck(const char *pchAppKey) {
  managed_binary<char> appKey(strlen(pchAppKey)+1);
  memcpy(appKey.data(), pchAppKey, appKey.size());

  return fnp.call<
    kIVRApplications_PerformApplicationPrelaunchCheck,
    vr::EVRApplicationError,
    managed_binary<char>
  >(std::move(appKey));
}
const char *PVRApplications::GetSceneApplicationStateNameFromEnum( EVRSceneApplicationState state ) {
  getOut() << "GetSceneApplicationStateNameFromEnum abort" << std::endl;
  abort();
  return "";
}
/* const char *PVRApplications::GetApplicationsTransitionStateNameFromEnum(vr::EVRApplicationTransitionState state) {
  getOut() << "GetApplicationsErrorNameFromEnum abort" << std::endl;
  abort();
  return "";
}
bool PVRApplications::IsQuitUserPromptRequested() {
  return fnp.call<
    kIVRApplications_IsQuitUserPromptRequested,
    bool
  >();
} */
vr::EVRApplicationError PVRApplications::LaunchInternalProcess(const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory) {
  managed_binary<char> binaryPath(strlen(pchBinaryPath)+1);
  memcpy(binaryPath.data(), pchBinaryPath, binaryPath.size());
  managed_binary<char> arguments(strlen(pchArguments)+1);
  memcpy(arguments.data(), pchArguments, arguments.size());
  managed_binary<char> workingDirectory(strlen(pchWorkingDirectory)+1);
  memcpy(workingDirectory.data(), pchWorkingDirectory, workingDirectory.size());

  return fnp.call<
    kIVRApplications_LaunchInternalProcess,
    vr::EVRApplicationError
  >(std::move(binaryPath), std::move(arguments), std::move(workingDirectory));
}
uint32_t PVRApplications::GetCurrentSceneProcessId() {
  return fnp.call<
    kIVRApplications_GetCurrentSceneProcessId,
    uint32_t
  >();
}
}