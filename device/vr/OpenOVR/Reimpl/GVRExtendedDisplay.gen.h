#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRExtendedDisplay_001.h"
#include "BaseExtendedDisplay.h"
class CVRExtendedDisplay_001 : public vr::IVRExtendedDisplay_001::IVRExtendedDisplay, public CVRCommon {
private:
	const std::shared_ptr<BaseExtendedDisplay> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRExtendedDisplay_001();
	// Interface methods:
	void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight);
	void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight);
	void GetDXGIOutputInfo(int32_t* pnAdapterIndex, int32_t* pnAdapterOutputIndex);
};
