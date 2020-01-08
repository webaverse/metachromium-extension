#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperoneSetup.h"
// #include "libovr_wrapper.h"

#include <string>

using namespace vr;
using namespace std;

bool BaseChaperoneSetup::CommitWorkingCopy(vr::EChaperoneConfigFile configFile) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::CommitWorkingCopy" << std::endl; });
	return g_pvrchaperonesetup->CommitWorkingCopy(configFile);
}
void BaseChaperoneSetup::RevertWorkingCopy() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::RevertWorkingCopy" << std::endl; });
	return g_pvrchaperonesetup->RevertWorkingCopy();
}
bool BaseChaperoneSetup::GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetWorkingPlayAreaSize" << std::endl; });
	return g_pvrchaperonesetup->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperoneSetup::GetWorkingPlayAreaRect(HmdQuad_t *rect) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetWorkingPlayAreaRect" << std::endl; });
	return g_pvrchaperonesetup->GetWorkingPlayAreaRect(rect);
}
bool BaseChaperoneSetup::GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetWorkingCollisionBoundsInfo" << std::endl; });
	return g_pvrchaperonesetup->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetLiveCollisionBoundsInfo" << std::endl; });
	return g_pvrchaperonesetup->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_pvrchaperonesetup->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
bool BaseChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose" << std::endl; });
	return g_pvrchaperonesetup->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingPlayAreaSize(float sizeX, float sizeZ) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingPlayAreaSize" << std::endl; });
	return g_pvrchaperonesetup->SetWorkingPlayAreaSize(sizeX, sizeZ);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingCollisionBoundsInfo" << std::endl; });
	return g_pvrchaperonesetup->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
}
void BaseChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_pvrchaperonesetup->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose" << std::endl; });
	return g_pvrchaperonesetup->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::ReloadFromDisk(vr::EChaperoneConfigFile configFile) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::ReloadFromDisk" << std::endl; });
	return g_pvrchaperonesetup->ReloadFromDisk(configFile);
}
bool BaseChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose" << std::endl; });
	return g_pvrchaperonesetup->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo" << std::endl; abort();
	// return g_pvrchaperonesetup->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo" << std::endl; abort();
  return false;
	// return g_pvrchaperonesetup->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
}
bool BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_pvrchaperonesetup->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
}
bool BaseChaperoneSetup::GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::GetLivePhysicalBoundsInfo" << std::endl; });
  getOut() << "abort BaseChaperoneSetup::GetLivePhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_pvrchaperonesetup->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::ExportLiveToBuffer" << std::endl; });
	return g_pvrchaperonesetup->ExportLiveToBuffer(pBuffer, pnBufferLength);
}
bool BaseChaperoneSetup::ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::ImportFromBufferToWorking" << std::endl; });
	return g_pvrchaperonesetup->ImportFromBufferToWorking(pBuffer, nImportFlags);
}
void BaseChaperoneSetup::SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) HmdVector2_t *pPointBuffer, uint32_t unPointCount) {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::SetWorkingPerimeter" << std::endl; });
	return g_pvrchaperonesetup->SetWorkingPerimeter(pPointBuffer, unPointCount);
}
void BaseChaperoneSetup::ShowWorkingSetPreview() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::ShowWorkingSetPreview" << std::endl; });
	return g_pvrchaperonesetup->ShowWorkingSetPreview();
}
void BaseChaperoneSetup::HideWorkingSetPreview() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::HideWorkingSetPreview" << std::endl; });
	return g_pvrchaperonesetup->HideWorkingSetPreview();
}
void BaseChaperoneSetup::RoomSetupStarting() {
  TRACE("BaseChaperoneSetup", []() { getOut() << "BaseChaperoneSetup::RoomSetupStarting" << std::endl; });
	return g_pvrchaperonesetup->RoomSetupStarting();
}
