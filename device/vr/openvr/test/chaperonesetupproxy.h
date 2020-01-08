#ifndef _openvr_chaperonesetupproxy_h_
#define _openvr_chaperonesetupproxy_h_

// #include <deque>

// #include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRChaperoneSetup {
public:
  IVRChaperoneSetup *vrchaperonesetup;
  FnProxy &fnp;

  PVRChaperoneSetup(IVRChaperoneSetup *vrchaperonesetup, FnProxy &fnp);
	bool CommitWorkingCopy(vr::EChaperoneConfigFile configFile);
  void RevertWorkingCopy();
  bool GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ);
  bool GetWorkingPlayAreaRect(vr::HmdQuad_t *rect);
  bool GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount);
  bool GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount);
  bool GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose);
  bool GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose);
  void SetWorkingPlayAreaSize(float sizeX, float sizeZ);
  void SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount);
  void SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose);
  void SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose);
  void ReloadFromDisk(vr::EChaperoneConfigFile configFile);
  bool GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose);
  void SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount);
  bool GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount);
  bool SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount);
  bool GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount);
  bool ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength);
  bool ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags);
  void SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) vr::HmdVector2_t *pPointBuffer, uint32_t unPointCount);
  void ShowWorkingSetPreview();
  void HideWorkingSetPreview();
  void RoomSetupStarting();
};
}

#endif