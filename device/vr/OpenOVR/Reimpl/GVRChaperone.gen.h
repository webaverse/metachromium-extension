#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRChaperone_003.h"
#include "BaseChaperone.h"
class CVRChaperone_003 : public vr::IVRChaperone_003::IVRChaperone, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperone> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRChaperone_003();
	// Interface methods:
	vr::IVRChaperone_003::ChaperoneCalibrationState GetCalibrationState();
	bool GetPlayAreaSize(float* pSizeX, float* pSizeZ);
	bool GetPlayAreaRect(vr::HmdQuad_t* rect);
	void ReloadInfo();
	void SetSceneColor(vr::HmdColor_t color);
	void GetBoundsColor(vr::HmdColor_t* pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t* pOutputCameraColor);
	bool AreBoundsVisible();
	void ForceBoundsVisible(bool bForce);
};
