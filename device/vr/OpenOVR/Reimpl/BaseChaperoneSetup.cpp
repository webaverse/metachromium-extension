#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperoneSetup.h"
// #include "libovr_wrapper.h"

#include <string>

using namespace vr;
using namespace std;

bool BaseChaperoneSetup::CommitWorkingCopy(vr::EChaperoneConfigFile configFile) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::CommitWorkingCopy" << std::endl; });
	return g_vrchaperonesetup->CommitWorkingCopy(configFile);
}
void BaseChaperoneSetup::RevertWorkingCopy() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::RevertWorkingCopy" << std::endl; });
	return g_vrchaperonesetup->RevertWorkingCopy();
}
bool BaseChaperoneSetup::GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetWorkingPlayAreaSize" << std::endl; });
	return g_vrchaperonesetup->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperoneSetup::GetWorkingPlayAreaRect(HmdQuad_t *rect) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetWorkingPlayAreaRect" << std::endl; });
	return g_vrchaperonesetup->GetWorkingPlayAreaRect(rect);
}
bool BaseChaperoneSetup::GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetWorkingCollisionBoundsInfo" << std::endl; });
	return g_vrchaperonesetup->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetLiveCollisionBoundsInfo" << std::endl; });
	return g_vrchaperonesetup->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetWorkingSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_vrchaperonesetup->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
bool BaseChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetWorkingStandingZeroPoseToRawTrackingPose" << std::endl; });
	return g_vrchaperonesetup->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingPlayAreaSize(float sizeX, float sizeZ) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingPlayAreaSize" << std::endl; });
	return g_vrchaperonesetup->SetWorkingPlayAreaSize(sizeX, sizeZ);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingCollisionBoundsInfo" << std::endl; });
	return g_vrchaperonesetup->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
}
void BaseChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_vrchaperonesetup->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingStandingZeroPoseToRawTrackingPose" << std::endl; });
	return g_vrchaperonesetup->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::ReloadFromDisk(vr::EChaperoneConfigFile configFile) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::ReloadFromDisk" << std::endl; });
	return g_vrchaperonesetup->ReloadFromDisk(configFile);
}
bool BaseChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetLiveSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_vrchaperonesetup->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingCollisionBoundsTagsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo" << std::endl; abort();
	// return g_vrchaperonesetup->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetLiveCollisionBoundsTagsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
}
bool BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingPhysicalBoundsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
}
bool BaseChaperoneSetup::GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::GetLivePhysicalBoundsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::GetLivePhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::ExportLiveToBuffer" << std::endl; });
	return g_vrchaperonesetup->ExportLiveToBuffer(pBuffer, pnBufferLength);
}
bool BaseChaperoneSetup::ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::ImportFromBufferToWorking" << std::endl; });
	return g_vrchaperonesetup->ImportFromBufferToWorking(pBuffer, nImportFlags);
}
void BaseChaperoneSetup::SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) HmdVector2_t *pPointBuffer, uint32_t unPointCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::SetWorkingPerimeter" << std::endl; });
	return g_vrchaperonesetup->SetWorkingPerimeter(pPointBuffer, unPointCount);
}
void BaseChaperoneSetup::ShowWorkingSetPreview() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::ShowWorkingSetPreview" << std::endl; });
	return g_vrchaperonesetup->ShowWorkingSetPreview();
}
void BaseChaperoneSetup::HideWorkingSetPreview() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::HideWorkingSetPreview" << std::endl; });
	return g_vrchaperonesetup->HideWorkingSetPreview();
}
void BaseChaperoneSetup::RoomSetupStarting() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperone::RoomSetupStarting" << std::endl; });
	return g_vrchaperonesetup->RoomSetupStarting();
}
