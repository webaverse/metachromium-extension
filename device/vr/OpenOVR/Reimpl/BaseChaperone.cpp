#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperone.h"

// #include "Drivers/Backend.h"

#include <vector>

using namespace std;
using namespace vr;

BaseChaperone::BaseChaperoneCalibrationState BaseChaperone::GetCalibrationState() {
	return ChaperoneCalibrationState_OK;
}
bool BaseChaperone::GetPlayAreaSize(float *pSizeX, float *pSizeZ) {
	return g_vrchaperone->GetPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperone::GetPlayAreaRect(HmdQuad_t *rect) {
	return g_vrchaperone->GetPlayAreaRect(rect);
}
void BaseChaperone::ReloadInfo(void) {
	return g_vrchaperone->ReloadInfo();
}
void BaseChaperone::SetSceneColor(HmdColor_t color) {
	return g_vrchaperone->SetSceneColor(color);
}
void BaseChaperone::GetBoundsColor(HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor) {
	return g_vrchaperone->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
}
bool BaseChaperone::AreBoundsVisible() {
	return g_vrchaperone->AreBoundsVisible();
}
void BaseChaperone::ForceBoundsVisible(bool bForce) {
	return g_vrchaperone->ForceBoundsVisible(bForce);
}

bool BaseChaperone::GetMinMaxPoints(vr::HmdVector3_t &minPoint, vr::HmdVector3_t &maxPoint) {
  abort();
	// return g_vrchaperone->GetMinMaxPoints(minPoint, maxPoint);
}
