#include "stdafx.h"
#define BASE_IMPL
#include "BaseChaperoneSetup.h"
// #include "libovr_wrapper.h"

#include <string>

using namespace vr;
using namespace std;

bool BaseChaperoneSetup::CommitWorkingCopy(vr::EChaperoneConfigFile configFile) {
	return g_vrchaperonesetup->CommitWorkingCopy(configFile);
}
void BaseChaperoneSetup::RevertWorkingCopy() {
	return g_vrchaperonesetup->RevertWorkingCopy();
}
bool BaseChaperoneSetup::GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ) {
	return g_vrchaperonesetup->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
}
bool BaseChaperoneSetup::GetWorkingPlayAreaRect(HmdQuad_t *rect) {
	return g_vrchaperonesetup->GetWorkingPlayAreaRect(rect);
}
bool BaseChaperoneSetup::GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
	return g_vrchaperonesetup->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
	return g_vrchaperonesetup->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
	return g_vrchaperonesetup->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
bool BaseChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose) {
	return g_vrchaperonesetup->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingPlayAreaSize(float sizeX, float sizeZ) {
	return g_vrchaperonesetup->SetWorkingPlayAreaSize(sizeX, sizeZ);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
	return g_vrchaperonesetup->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
}
void BaseChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose) {
	return g_vrchaperonesetup->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose(const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose) {
	return g_vrchaperonesetup->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::ReloadFromDisk(vr::EChaperoneConfigFile configFile) {
	return g_vrchaperonesetup->ReloadFromDisk(configFile);
}
bool BaseChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose(HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
	return g_vrchaperonesetup->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}
void BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount) {
  getOut() << "abort BaseChaperoneSetup::SetWorkingCollisionBoundsTagsInfo" << std::endl; abort();
	// return g_vrchaperonesetup->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
}
bool BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount) {
  getOut() << "abort BaseChaperoneSetup::GetLiveCollisionBoundsTagsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
}
bool BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  getOut() << "abort BaseChaperoneSetup::SetWorkingPhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
}
bool BaseChaperoneSetup::GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  getOut() << "abort BaseChaperoneSetup::GetLivePhysicalBoundsInfo" << std::endl; abort();
  return false;
	// return g_vrchaperonesetup->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
}
bool BaseChaperoneSetup::ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength) {
	return g_vrchaperonesetup->ExportLiveToBuffer(pBuffer, pnBufferLength);
}
bool BaseChaperoneSetup::ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags) {
	return g_vrchaperonesetup->ImportFromBufferToWorking(pBuffer, nImportFlags);
}
void BaseChaperoneSetup::SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) HmdVector2_t *pPointBuffer, uint32_t unPointCount) {
	return g_vrchaperonesetup->SetWorkingPerimeter(pPointBuffer, unPointCount);
}
void BaseChaperoneSetup::ShowWorkingSetPreview() {
	return g_vrchaperonesetup->ShowWorkingSetPreview();
}
void BaseChaperoneSetup::HideWorkingSetPreview() {
	return g_vrchaperonesetup->HideWorkingSetPreview();
}
void BaseChaperoneSetup::RoomSetupStarting() {
	return g_vrchaperonesetup->RoomSetupStarting();
}
