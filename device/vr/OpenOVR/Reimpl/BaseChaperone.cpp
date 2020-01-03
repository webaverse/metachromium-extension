#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperone.h"

// #include "Drivers/Backend.h"

#include <vector>

using namespace std;
using namespace vr;

BaseChaperone::BaseChaperoneCalibrationState BaseChaperone::GetCalibrationState() {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::BaseChaperoneCalibrationState" << std::endl; });
	return ChaperoneCalibrationState_OK;
}
bool BaseChaperone::GetPlayAreaSize(float *pSizeX, float *pSizeZ) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetPlayAreaSize" << std::endl; });
	return g_vrchaperone->GetPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperone::GetPlayAreaRect(HmdQuad_t *rect) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetPlayAreaRect" << std::endl; });
	return g_vrchaperone->GetPlayAreaRect(rect);
}
void BaseChaperone::ReloadInfo(void) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::ReloadInfo" << std::endl; });
	return g_vrchaperone->ReloadInfo();
}
void BaseChaperone::SetSceneColor(HmdColor_t color) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::SetSceneColor" << std::endl; });
	return g_vrchaperone->SetSceneColor(color);
}
void BaseChaperone::GetBoundsColor(HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetBoundsColor" << std::endl; });
	return g_vrchaperone->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
}
bool BaseChaperone::AreBoundsVisible() {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::AreBoundsVisible" << std::endl; });
	return g_vrchaperone->AreBoundsVisible();
}
void BaseChaperone::ForceBoundsVisible(bool bForce) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::ForceBoundsVisible" << std::endl; });
	return g_vrchaperone->ForceBoundsVisible(bForce);
}

bool BaseChaperone::GetMinMaxPoints(vr::HmdVector3_t &minPoint, vr::HmdVector3_t &maxPoint) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetMinMaxPoints" << std::endl; });
  getOut() << "abort BaseChaperone::GetMinMaxPoints" << std::endl; abort();
	// return g_vrchaperone->GetMinMaxPoints(minPoint, maxPoint);
}
