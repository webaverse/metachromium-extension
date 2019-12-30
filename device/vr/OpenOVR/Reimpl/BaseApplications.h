#pragma once
#include "BaseCommon.h"

class BaseApplications {
public:
	// ---------------  Application management  --------------- //

	/** Adds an application manifest to the list to load when building the list of installed applications.
	* Temporary manifests are not automatically loaded */
	virtual vr::EVRApplicationError AddApplicationManifest(const char *pchApplicationManifestFullPath, bool bTemporary = false);

	/** Removes an application manifest from the list to load when building the list of installed applications. */
	virtual vr::EVRApplicationError RemoveApplicationManifest(const char *pchApplicationManifestFullPath);

	/** Returns true if an application is installed */
	virtual bool IsApplicationInstalled(const char *pchAppKey);

	/** Returns the number of applications available in the list */
	virtual uint32_t GetApplicationCount();

	/** Returns the key of the specified application. The index is at least 0 and is less than the return
	* value of GetApplicationCount(). The buffer should be at least k_unMaxApplicationKeyLength in order to
	* fit the key. */
	virtual vr::EVRApplicationError GetApplicationKeyByIndex(uint32_t unApplicationIndex, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);

	/** Returns the key of the application for the specified Process Id. The buffer should be at least
	* k_unMaxApplicationKeyLength in order to fit the key. */
	virtual vr::EVRApplicationError GetApplicationKeyByProcessId(uint32_t unProcessId, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);

	/** Launches the application. The existing scene application will exit and then the new application will start.
	* This call is not valid for dashboard overlay applications. */
	virtual vr::EVRApplicationError LaunchApplication(const char *pchAppKey);

	/** Launches an instance of an application of type template, with its app key being pchNewAppKey (which must be unique) and optionally override sections
	* from the manifest file via AppOverrideKeys_t
	*/
	virtual vr::EVRApplicationError LaunchTemplateApplication(const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT(unKeys) const vr::AppOverrideKeys_t *pKeys, uint32_t unKeys);

	/** launches the application currently associated with this mime type and passes it the option args, typically the filename or object name of the item being launched */
	virtual vr::EVRApplicationError LaunchApplicationFromMimeType(const char *pchMimeType, const char *pchArgs);

	/** Launches the dashboard overlay application if it is not already running. This call is only valid for
	* dashboard overlay applications. */
	virtual vr::EVRApplicationError LaunchDashboardOverlay(const char *pchAppKey);

	/** Cancel a pending launch for an application */
	virtual bool CancelApplicationLaunch(const char *pchAppKey);

	/** Identifies a running application. OpenVR can't always tell which process started in response
	* to a URL. This function allows a URL handler (or the process itself) to identify the app key
	* for the now running application. Passing a process ID of 0 identifies the calling process.
	* The application must be one that's known to the system via a call to AddApplicationManifest. */
	virtual vr::EVRApplicationError IdentifyApplication(uint32_t unProcessId, const char *pchAppKey);

	/** Returns the process ID for an application. Return 0 if the application was not found or is not running. */
	virtual uint32_t GetApplicationProcessId(const char *pchAppKey);

	/** Returns a string for an applications error */
	virtual const char *GetApplicationsErrorNameFromEnum(vr::EVRApplicationError error);

	// ---------------  Application properties  --------------- //

	/** Returns a value for an application property. The required buffer size to fit this value will be returned. */
	virtual uint32_t GetApplicationPropertyString(const char *pchAppKey, vr::EVRApplicationProperty eProperty, VR_OUT_STRING() char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, vr::EVRApplicationError *peError = nullptr);

	/** Returns a bool value for an application property. Returns false in all error cases. */
	virtual bool GetApplicationPropertyBool(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError = nullptr);

	/** Returns a uint64 value for an application property. Returns 0 in all error cases. */
	virtual uint64_t GetApplicationPropertyUint64(const char *pchAppKey, vr::EVRApplicationProperty eProperty, vr::EVRApplicationError *peError = nullptr);

	/** Sets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
	virtual vr::EVRApplicationError SetApplicationAutoLaunch(const char *pchAppKey, bool bAutoLaunch);

	/** Gets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
	virtual bool GetApplicationAutoLaunch(const char *pchAppKey);

	/** Adds this mime-type to the list of supported mime types for this application*/
	virtual vr::EVRApplicationError SetDefaultApplicationForMimeType(const char *pchAppKey, const char *pchMimeType);

	/** return the app key that will open this mime type */
	virtual bool GetDefaultApplicationForMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);

	/** Get the list of supported mime types for this application, comma-delimited */
	virtual bool GetApplicationSupportedMimeTypes(const char *pchAppKey, VR_OUT_STRING() char *pchMimeTypesBuffer, uint32_t unMimeTypesBuffer);

	/** Get the list of app-keys that support this mime type, comma-delimited, the return value is number of bytes you need to return the full string */
	virtual uint32_t GetApplicationsThatSupportMimeType(const char *pchMimeType, VR_OUT_STRING() char *pchAppKeysThatSupportBuffer, uint32_t unAppKeysThatSupportBuffer);

	/** Get the args list from an app launch that had the process already running, you call this when you get a VREvent_ApplicationMimeTypeLoad */
	virtual uint32_t GetApplicationLaunchArguments(uint32_t unHandle, VR_OUT_STRING() char *pchArgs, uint32_t unArgs);

	// ---------------  Transition methods --------------- //

	/** Returns the app key for the application that is starting up */
	virtual vr::EVRApplicationError GetStartingApplication(VR_OUT_STRING() char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen);

	/** Returns the application transition state */
	virtual vr::EVRApplicationTransitionState GetTransitionState();

	/** Returns errors that would prevent the specified application from launching immediately. Calling this function will
	* cause the current scene application to quit, so only call it when you are actually about to launch something else.
	* What the caller should do about these failures depends on the failure:
	*   VRApplicationError_OldApplicationQuitting - An existing application has been told to quit. Wait for a VREvent_ProcessQuit
	*                                               and try again.
	*   VRApplicationError_ApplicationAlreadyStarting - This application is already starting. This is a permanent failure.
	*   VRApplicationError_LaunchInProgress	      - A different application is already starting. This is a permanent failure.
	*   VRApplicationError_None                   - Go ahead and launch. Everything is clear.
	*/
	virtual vr::EVRApplicationError PerformApplicationPrelaunchCheck(const char *pchAppKey);

	/** Returns a string for an application transition state */
	virtual const char *GetApplicationsTransitionStateNameFromEnum(vr::EVRApplicationTransitionState state);

	/** Returns true if the outgoing scene app has requested a save prompt before exiting */
	virtual bool IsQuitUserPromptRequested();

	/** Starts a subprocess within the calling application. This
	* suppresses all application transition UI and automatically identifies the new executable
	* as part of the same application. On success the calling process should exit immediately.
	* If working directory is NULL or "" the directory portion of the binary path will be
	* the working directory. */
	virtual vr::EVRApplicationError LaunchInternalProcess(const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory);

	/** Returns the current scene process ID according to the application system. A scene process will get scene
	* focus once it starts rendering, but it will appear here once it calls VR_Init with the Scene application
	* type. */
	virtual uint32_t GetCurrentSceneProcessId();
};
