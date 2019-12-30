#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRChaperoneSetup_005.h"
#include "OpenVR/interfaces/IVRChaperoneSetup_006.h"
#include "BaseChaperoneSetup.h"
class CVRChaperoneSetup_005 : public vr::IVRChaperoneSetup_005::IVRChaperoneSetup, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperoneSetup> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRChaperoneSetup_005();
	// Interface methods:
	bool CommitWorkingCopy(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile);
	void RevertWorkingCopy();
	bool GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ);
	bool GetWorkingPlayAreaRect(vr::HmdQuad_t* rect);
	bool GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount);
	bool GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount);
	bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose);
	bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose);
	void SetWorkingPlayAreaSize(float sizeX, float sizeZ);
	void SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount);
	void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose);
	void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose);
	void ReloadFromDisk(vr::IVRChaperoneSetup_005::EChaperoneConfigFile configFile);
	bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose);
	void SetWorkingCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t unTagCount);
	bool GetLiveCollisionBoundsTagsInfo(uint8_t* pTagsBuffer, uint32_t* punTagCount);
	bool SetWorkingPhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount);
	bool GetLivePhysicalBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount);
	bool ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength);
	bool ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags);
};
#include "BaseChaperoneSetup.h"
class CVRChaperoneSetup_006 : public vr::IVRChaperoneSetup_006::IVRChaperoneSetup, public CVRCommon {
private:
	const std::shared_ptr<BaseChaperoneSetup> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRChaperoneSetup_006();
	// Interface methods:
	bool CommitWorkingCopy(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile);
	void RevertWorkingCopy();
	bool GetWorkingPlayAreaSize(float* pSizeX, float* pSizeZ);
	bool GetWorkingPlayAreaRect(vr::HmdQuad_t* rect);
	bool GetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount);
	bool GetLiveCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t* punQuadsCount);
	bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose);
	bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatStandingZeroPoseToRawTrackingPose);
	void SetWorkingPlayAreaSize(float sizeX, float sizeZ);
	void SetWorkingCollisionBoundsInfo(vr::HmdQuad_t* pQuadsBuffer, uint32_t unQuadsCount);
	void SetWorkingPerimeter(vr::HmdVector2_t* pPointBuffer, uint32_t unPointCount);
	void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatSeatedZeroPoseToRawTrackingPose);
	void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t* pMatStandingZeroPoseToRawTrackingPose);
	void ReloadFromDisk(vr::IVRChaperoneSetup_006::EChaperoneConfigFile configFile);
	bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t* pmatSeatedZeroPoseToRawTrackingPose);
	bool ExportLiveToBuffer(char* pBuffer, uint32_t* pnBufferLength);
	bool ImportFromBufferToWorking(const char* pBuffer, uint32_t nImportFlags);
	void ShowWorkingSetPreview();
	void HideWorkingSetPreview();
	void RoomSetupStarting();
};
