#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperone.h"

// #include "Drivers/Backend.h"

#include <vector>

using namespace std;
using namespace vr;

BaseChaperone::BaseChaperoneCalibrationState BaseChaperone::GetCalibrationState() {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::BaseChaperoneCalibrationState " << GetCurrentProcessId() << std::endl; });
	return ChaperoneCalibrationState_OK;
}
bool BaseChaperone::GetPlayAreaSize(float *pSizeX, float *pSizeZ) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetPlayAreaSize " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->GetPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperone::GetPlayAreaRect(HmdQuad_t *rect) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetPlayAreaRect " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->GetPlayAreaRect(rect);
}
void BaseChaperone::ReloadInfo(void) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::ReloadInfo " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->ReloadInfo();
}
void BaseChaperone::SetSceneColor(HmdColor_t color) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::SetSceneColor " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->SetSceneColor(color);
}
void BaseChaperone::GetBoundsColor(HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetBoundsColor " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
}
bool BaseChaperone::AreBoundsVisible() {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::AreBoundsVisible " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->AreBoundsVisible();
}
void BaseChaperone::ForceBoundsVisible(bool bForce) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::ForceBoundsVisible " << GetCurrentProcessId() << std::endl; });
	return g_pvrchaperone->ForceBoundsVisible(bForce);
}

bool BaseChaperone::GetMinMaxPoints(vr::HmdVector3_t &minPoint, vr::HmdVector3_t &maxPoint) {
  TRACE("BaseChaperone", []() { getOut() << "BaseChaperone::GetMinMaxPoints " << GetCurrentProcessId() << std::endl; });
  getOut() << "abort BaseChaperone::GetMinMaxPoints" << std::endl; abort();
  return false;
	// return g_pvrchaperone->GetMinMaxPoints(minPoint, maxPoint);
}
