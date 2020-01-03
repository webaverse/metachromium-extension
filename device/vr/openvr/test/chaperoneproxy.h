#ifndef _openvr_chaperoneproxy_h_
#define _openvr_chaperoneproxy_h_

// #include <D3D11_1.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
// #include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRChaperone : public IVRChaperone {
public:
  IVRChaperone *vrchaperone;
  FnProxy &fnp;

  PVRChaperone(IVRChaperone *vrchaperone, FnProxy &fnp);
	virtual ChaperoneCalibrationState GetCalibrationState();
	virtual bool GetPlayAreaSize(float *pSizeX, float *pSizeZ);
	virtual bool GetPlayAreaRect(vr::HmdQuad_t *rect);
	virtual void ReloadInfo(void);
	virtual void SetSceneColor(vr::HmdColor_t color);
	virtual void GetBoundsColor(vr::HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t *pOutputCameraColor);
	virtual bool AreBoundsVisible();
	virtual void ForceBoundsVisible(bool bForce);
/* private:
	bool GetMinMaxPoints(vr::HmdVector3_t &minPoint, vr::HmdVector3_t &maxPoint); */
};
}

#endif