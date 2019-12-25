#pragma once
#include "BaseCommon.h"
#include "OpenVR/custom_interfaces/IVRClientCore_003.h"
#include "OpenVR/custom_interfaces/IVRClientCore_002.h"
#include "BaseClientCore.h"
class CVRClientCore_003 : public vr::IVRClientCore_003::IVRClientCore, public CVRCommon {
private:
	const std::shared_ptr<BaseClientCore> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRClientCore_003();
	// Interface methods:
	vr::EVRInitError Init(vr::EVRApplicationType eApplicationType, const char* pStartupInfo);
	void Cleanup();
	vr::EVRInitError IsInterfaceVersionValid(const char* pchInterfaceVersion);
	void* GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError);
	bool BIsHmdPresent();
	const char* GetEnglishStringForHmdError(vr::EVRInitError eError);
	const char* GetIDForVRInitError(vr::EVRInitError eError);
};
#include "BaseClientCore.h"
class CVRClientCore_002 : public vr::IVRClientCore_002::IVRClientCore, public CVRCommon {
private:
	const std::shared_ptr<BaseClientCore> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRClientCore_002();
	// Interface methods:
	vr::EVRInitError Init(vr::EVRApplicationType eApplicationType);
	void Cleanup();
	vr::EVRInitError IsInterfaceVersionValid(const char* pchInterfaceVersion);
	void* GetGenericInterface(const char* pchNameAndVersion, vr::EVRInitError* peError);
	bool BIsHmdPresent();
	const char* GetEnglishStringForHmdError(vr::EVRInitError eError);
	const char* GetIDForVRInitError(vr::EVRInitError eError);
};
