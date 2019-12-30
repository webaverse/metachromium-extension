#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRApplications_004.h"
#include "OpenVR/interfaces/IVRApplications_005.h"
#include "OpenVR/interfaces/IVRApplications_006.h"
#include "BaseApplications.h"
class CVRApplications_004 : public vr::IVRApplications_004::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRApplications_004();
	// Interface methods:
	vr::IVRApplications_004::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary);
	vr::IVRApplications_004::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath);
	bool IsApplicationInstalled(const char* pchAppKey);
	uint32_t GetApplicationCount();
	vr::IVRApplications_004::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_004::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_004::EVRApplicationError LaunchApplication(const char* pchAppKey);
	vr::IVRApplications_004::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey);
	bool CancelApplicationLaunch(const char* pchAppKey);
	vr::IVRApplications_004::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey);
	uint32_t GetApplicationProcessId(const char* pchAppKey);
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_004::EVRApplicationError error);
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_004::EVRApplicationError* peError);
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError);
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_004::EVRApplicationProperty eProperty, vr::IVRApplications_004::EVRApplicationError* peError);
	vr::IVRApplications_004::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch);
	bool GetApplicationAutoLaunch(const char* pchAppKey);
	vr::IVRApplications_004::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_004::EVRApplicationTransitionState GetTransitionState();
	vr::IVRApplications_004::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey);
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_004::EVRApplicationTransitionState state);
	bool IsQuitUserPromptRequested();
	vr::IVRApplications_004::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory);
};
#include "BaseApplications.h"
class CVRApplications_005 : public vr::IVRApplications_005::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRApplications_005();
	// Interface methods:
	vr::IVRApplications_005::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary);
	vr::IVRApplications_005::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath);
	bool IsApplicationInstalled(const char* pchAppKey);
	uint32_t GetApplicationCount();
	vr::IVRApplications_005::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_005::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_005::EVRApplicationError LaunchApplication(const char* pchAppKey);
	vr::IVRApplications_005::EVRApplicationError LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_005::AppOverrideKeys_t* pKeys, uint32_t unKeys);
	vr::IVRApplications_005::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey);
	bool CancelApplicationLaunch(const char* pchAppKey);
	vr::IVRApplications_005::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey);
	uint32_t GetApplicationProcessId(const char* pchAppKey);
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_005::EVRApplicationError error);
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_005::EVRApplicationError* peError);
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError);
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_005::EVRApplicationProperty eProperty, vr::IVRApplications_005::EVRApplicationError* peError);
	vr::IVRApplications_005::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch);
	bool GetApplicationAutoLaunch(const char* pchAppKey);
	vr::IVRApplications_005::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_005::EVRApplicationTransitionState GetTransitionState();
	vr::IVRApplications_005::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey);
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_005::EVRApplicationTransitionState state);
	bool IsQuitUserPromptRequested();
	vr::IVRApplications_005::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory);
};
#include "BaseApplications.h"
class CVRApplications_006 : public vr::IVRApplications_006::IVRApplications, public CVRCommon {
private:
	const std::shared_ptr<BaseApplications> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRApplications_006();
	// Interface methods:
	vr::IVRApplications_006::EVRApplicationError AddApplicationManifest(const char* pchApplicationManifestFullPath, bool bTemporary);
	vr::IVRApplications_006::EVRApplicationError RemoveApplicationManifest(const char* pchApplicationManifestFullPath);
	bool IsApplicationInstalled(const char* pchAppKey);
	uint32_t GetApplicationCount();
	vr::IVRApplications_006::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_006::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_006::EVRApplicationError LaunchApplication(const char* pchAppKey);
	vr::IVRApplications_006::EVRApplicationError LaunchTemplateApplication(const char* pchTemplateAppKey, const char* pchNewAppKey, const vr::IVRApplications_006::AppOverrideKeys_t* pKeys, uint32_t unKeys);
	vr::IVRApplications_006::EVRApplicationError LaunchApplicationFromMimeType(const char* pchMimeType, const char* pchArgs);
	vr::IVRApplications_006::EVRApplicationError LaunchDashboardOverlay(const char* pchAppKey);
	bool CancelApplicationLaunch(const char* pchAppKey);
	vr::IVRApplications_006::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char* pchAppKey);
	uint32_t GetApplicationProcessId(const char* pchAppKey);
	const char* GetApplicationsErrorNameFromEnum(vr::IVRApplications_006::EVRApplicationError error);
	uint32_t GetApplicationPropertyString(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, char* pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::IVRApplications_006::EVRApplicationError* peError);
	bool GetApplicationPropertyBool(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError);
	uint64_t GetApplicationPropertyUint64(const char* pchAppKey, vr::IVRApplications_006::EVRApplicationProperty eProperty, vr::IVRApplications_006::EVRApplicationError* peError);
	vr::IVRApplications_006::EVRApplicationError SetApplicationAutoLaunch(const char* pchAppKey, bool bAutoLaunch);
	bool GetApplicationAutoLaunch(const char* pchAppKey);
	vr::IVRApplications_006::EVRApplicationError SetDefaultApplicationForMimeType(const char* pchAppKey, const char* pchMimeType);
	bool GetDefaultApplicationForMimeType(const char* pchMimeType, char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	bool GetApplicationSupportedMimeTypes(const char* pchAppKey, char* pchMimeTypesBuffer, uint32_t unMimeTypesBuffer);
	uint32_t GetApplicationsThatSupportMimeType(const char* pchMimeType, char* pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer);
	uint32_t GetApplicationLaunchArguments(uint32_t unHandle, char* pchArgs, uint32_t unArgs);
	vr::IVRApplications_006::EVRApplicationError GetStartingApplication(char* pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
	vr::IVRApplications_006::EVRApplicationTransitionState GetTransitionState();
	vr::IVRApplications_006::EVRApplicationError PerformApplicationPrelaunchCheck(const char* pchAppKey);
	const char* GetApplicationsTransitionStateNameFromEnum(vr::IVRApplications_006::EVRApplicationTransitionState state);
	bool IsQuitUserPromptRequested();
	vr::IVRApplications_006::EVRApplicationError LaunchInternalProcess(const char* pchBinaryPath, const char* pchArguments, const char* pchWorkingDirectory);
	uint32_t GetCurrentSceneProcessId();
};
