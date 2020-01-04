#include "stdafx.h"
#define BASE_IMPL
#include "BaseApplications.h"
#include <string>

using namespace std;
using namespace vr;

/** The maximum length of an application key */
static const uint32_t k_unMaxApplicationKeyLength = 128;

// Used by Viveport
EVRApplicationError BaseApplications::AddApplicationManifest(const char *pchApplicationManifestFullPath, bool bTemporary) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::AddApplicationManifest" << std::endl; });
	return g_vrapplications->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
}
EVRApplicationError BaseApplications::RemoveApplicationManifest(const char *pchApplicationManifestFullPath) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::RemoveApplicationManifest" << std::endl; });
	return g_vrapplications->RemoveApplicationManifest(pchApplicationManifestFullPath);
}

bool BaseApplications::IsApplicationInstalled(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::IsApplicationInstalled" << std::endl; });
	return g_vrapplications->IsApplicationInstalled(pchAppKey);
}
uint32_t BaseApplications::GetApplicationCount() {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationCount" << std::endl; });
	return g_vrapplications->GetApplicationCount();
}
EVRApplicationError BaseApplications::GetApplicationKeyByIndex(uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationKeyByIndex" << std::endl; });
	return g_vrapplications->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
}
EVRApplicationError BaseApplications::GetApplicationKeyByProcessId(uint32_t unProcessId, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationKeyByProcessId" << std::endl; });
	return g_vrapplications->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
}
EVRApplicationError BaseApplications::LaunchApplication(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::LaunchApplication" << std::endl; });
	return g_vrapplications->LaunchApplication(pchAppKey);
}
EVRApplicationError BaseApplications::LaunchTemplateApplication(const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT(unKeys) const AppOverrideKeys_t *pKeys, uint32_t unKeys) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::LaunchTemplateApplication" << std::endl; });
	return g_vrapplications->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
}
EVRApplicationError BaseApplications::LaunchApplicationFromMimeType(const char *pchMimeType, const char *pchArgs) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::LaunchApplicationFromMimeType" << std::endl; });
	return g_vrapplications->LaunchApplicationFromMimeType(pchMimeType, pchArgs);
}
EVRApplicationError BaseApplications::LaunchDashboardOverlay(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::LaunchDashboardOverlay" << std::endl; });
	return g_vrapplications->LaunchDashboardOverlay(pchAppKey);
}
bool BaseApplications::CancelApplicationLaunch(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::CancelApplicationLaunch" << std::endl; });
	return g_vrapplications->CancelApplicationLaunch(pchAppKey);
}
EVRApplicationError BaseApplications::IdentifyApplication(uint32_t unProcessId, const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::IdentifyApplication" << std::endl; });
	return g_vrapplications->IdentifyApplication(unProcessId, pchAppKey);
}
uint32_t BaseApplications::GetApplicationProcessId(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationProcessId" << std::endl; });
	return g_vrapplications->GetApplicationProcessId(pchAppKey);
}
const char * BaseApplications::GetApplicationsErrorNameFromEnum(EVRApplicationError error) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationsErrorNameFromEnum" << std::endl; });
	return g_vrapplications->GetApplicationsErrorNameFromEnum(error);
}
uint32_t BaseApplications::GetApplicationPropertyString(const char *pchAppKey, EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationPropertyString" << std::endl; });
	return g_vrapplications->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
}
bool BaseApplications::GetApplicationPropertyBool(const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationPropertyBool" << std::endl; });
	return g_vrapplications->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
}
uint64_t BaseApplications::GetApplicationPropertyUint64(const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationPropertyUint64" << std::endl; });
	return g_vrapplications->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
}
EVRApplicationError BaseApplications::SetApplicationAutoLaunch(const char *pchAppKey, bool bAutoLaunch) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::SetApplicationAutoLaunch" << std::endl; });
	return g_vrapplications->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
}
bool BaseApplications::GetApplicationAutoLaunch(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationAutoLaunch" << std::endl; });
	return g_vrapplications->GetApplicationAutoLaunch(pchAppKey);
}
EVRApplicationError BaseApplications::SetDefaultApplicationForMimeType(const char *pchAppKey, const char *pchMimeType) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::SetDefaultApplicationForMimeType" << std::endl; });
	return g_vrapplications->SetDefaultApplicationForMimeType(pchAppKey, pchMimeType);
}
bool BaseApplications::GetDefaultApplicationForMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetDefaultApplicationForMimeType" << std::endl; });
	return g_vrapplications->GetDefaultApplicationForMimeType(pchMimeType, pchAppKeyBuffer, unAppKeyBufferLen);
}
bool BaseApplications::GetApplicationSupportedMimeTypes(const char *pchAppKey, VR_OUT_STRING() char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationSupportedMimeTypes" << std::endl; });
	return g_vrapplications->GetApplicationSupportedMimeTypes(pchAppKey, pchMimeTypesBuffer, unMimeTypesBuffer);
}
uint32_t BaseApplications::GetApplicationsThatSupportMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationsThatSupportMimeType" << std::endl; });
	return g_vrapplications->GetApplicationsThatSupportMimeType(pchMimeType, pchAppKeysThatSupportBuffer, unAppKeysThatSupportBuffer);
}
uint32_t BaseApplications::GetApplicationLaunchArguments(uint32_t unHandle, VR_OUT_STRING() char *pchArgs, uint32_t unArgs) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetApplicationLaunchArguments" << std::endl; });
	return g_vrapplications->GetApplicationLaunchArguments(unHandle, pchArgs, unArgs);
}
EVRApplicationError BaseApplications::GetStartingApplication(VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetStartingApplication" << std::endl; });
	return g_vrapplications->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
}
EVRApplicationTransitionState BaseApplications::GetTransitionState() {
  getOut() << "abort BaseApplications::GetTransitionState" << std::endl; abort();
  return EVRApplicationTransitionState();
	// return g_vrapplications->GetTransitionState();
}
EVRApplicationError BaseApplications::PerformApplicationPrelaunchCheck(const char *pchAppKey) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::PerformApplicationPrelaunchCheck" << std::endl; });
	return g_vrapplications->PerformApplicationPrelaunchCheck(pchAppKey);
}
const char * BaseApplications::GetApplicationsTransitionStateNameFromEnum(EVRApplicationTransitionState state) {
  getOut() << "abort BaseApplications::GetApplicationsTransitionStateNameFromEnum" << std::endl; abort();
  return nullptr;
	// return g_vrapplications->GetApplicationsTransitionStateNameFromEnum(state);
}
bool BaseApplications::IsQuitUserPromptRequested() {
  getOut() << "abort BaseApplications::IsQuitUserPromptRequested" << std::endl; abort();
  return false;
	// return g_vrapplications->IsQuitUserPromptRequested();
}
EVRApplicationError BaseApplications::LaunchInternalProcess(const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory) {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::LaunchInternalProcess" << std::endl; });
	return g_vrapplications->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
}
uint32_t BaseApplications::GetCurrentSceneProcessId() {
  TRACE("BaseApplications", []() { getOut() << "BaseApplications::GetCurrentSceneProcessId" << std::endl; });
	return g_vrapplications->GetCurrentSceneProcessId();
}
