// #include <chrono>
#include "device/vr/openvr/test/chaperonesetupproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRChaperoneSetup_CommitWorkingCopy[] = "IVRChaperoneSetup::CommitWorkingCopy";
char kIVRChaperoneSetup_RevertWorkingCopy[] = "IVRChaperoneSetup::RevertWorkingCopy";
char kIVRChaperoneSetup_GetWorkingPlayAreaSize[] = "IVRChaperoneSetup::GetWorkingPlayAreaSize";
char kIVRChaperoneSetup_GetWorkingPlayAreaRect[] = "IVRChaperoneSetup::GetWorkingPlayAreaRect";
char kIVRChaperoneSetup_GetWorkingCollisionBoundsInfo[] = "IVRChaperoneSetup::GetWorkingCollisionBoundsInfo";
char kIVRChaperoneSetup_GetLiveCollisionBoundsInfo[] = "IVRChaperoneSetup::GetLiveCollisionBoundsInfo";
char kIVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose[] = "IVRChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose";
char kIVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose[] = "IVRChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose";
char kIVRChaperoneSetup_SetWorkingPlayAreaSize[] = "IVRChaperoneSetup::SetWorkingPlayAreaSize";
char kIVRChaperoneSetup_SetWorkingCollisionBoundsInfo[] = "IVRChaperoneSetup::SetWorkingCollisionBoundsInfo";
char kIVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose[] = "IVRChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose";
char kIVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose[] = "IVRChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose";
char kIVRChaperoneSetup_ReloadFromDisk[] = "IVRChaperoneSetup::ReloadFromDisk";
char kIVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose[] = "IVRChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose";
char kIVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo[] = "IVRChaperoneSetup::SetWorkingCollisionBoundsTagsInfo";
char kIVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo[] = "IVRChaperoneSetup::GetLiveCollisionBoundsTagsInfo";
char kIVRChaperoneSetup_SetWorkingPhysicalBoundsInfo[] = "IVRChaperoneSetup::SetWorkingPhysicalBoundsInfo";
char kIVRChaperoneSetup_GetLivePhysicalBoundsInfo[] = "IVRChaperoneSetup::GetLivePhysicalBoundsInfo";
char kIVRChaperoneSetup_ExportLiveToBuffer[] = "IVRChaperoneSetup::ExportLiveToBuffer";
char kIVRChaperoneSetup_ImportFromBufferToWorking[] = "IVRChaperoneSetup::ImportFromBufferToWorking";
char kIVRChaperoneSetup_SetWorkingPerimeter[] = "IVRChaperoneSetup::SetWorkingPerimeter";
char kIVRChaperoneSetup_ShowWorkingSetPreview[] = "IVRChaperoneSetup::ShowWorkingSetPreview";
char kIVRChaperoneSetup_HideWorkingSetPreview[] = "IVRChaperoneSetup::HideWorkingSetPreview";
char kIVRChaperoneSetup_RoomSetupStarting[] = "IVRChaperoneSetup::RoomSetupStarting";

PVRChaperoneSetup::PVRChaperoneSetup(IVRChaperoneSetup *vrchaperonesetup, FnProxy &fnp) :
  vrchaperonesetup(vrchaperonesetup),
  fnp(fnp)
{
  fnp.reg<
    kIVRChaperoneSetup_CommitWorkingCopy,
    bool,
    EChaperoneConfigFile
  >([=](EChaperoneConfigFile configFile) {
    return vrcompositor->CommitWorkingCopy(configFile);
  });
  fnp.reg<
    kIVRChaperoneSetup_RevertWorkingCopy,
    int
  >([=]() {
    vrcompositor->RevertWorkingCopy();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingPlayAreaSize,
    std::tuple<bool, float, float>
  >([=]() {
    float sizeX;
    float sizeZ;
    auto result = vrcompositor->GetWorkingPlayAreaSize(&sizeX, &sizeZ);
    return std::tuple<bool, float, float>(
      result,
      sizeX,
      sizeZ
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingPlayAreaRect,
    std::tuple<bool, vr::HmdQuad_t>
  >([=]() {
    vr::HmdQuad_t rect;
    auto result = vrcompositor->GetWorkingPlayAreaRect(&rect);
    return std::tuple<bool, vr::HmdQuad_t>(
      result,
      quad
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    auto result = vrcompositor->GetWorkingCollisionBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    return std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>(
      result,
      std::move(quadsBuffer),
      unQuadsCount
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    auto result = vrcompositor->GetLiveCollisionBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    return std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>(
      result,
      std::move(quadsBuffer),
      unQuadsCount
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >([=]() {
    vr::HmdMatrix34_t seatedZeroPoseToRawTrackingPose;
    auto result = vrcompositor->GetWorkingSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
    return std::tuple<bool, vr::HmdMatrix34_t>(
      result,
      seatedZeroPoseToRawTrackingPose
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >([=]() {
    vr::HmdMatrix34_t standingZeroPoseToRawTrackingPose;
    auto result = vrcompositor->GetWorkingStandingZeroPoseToRawTrackingPose(&standingZeroPoseToRawTrackingPose);
    return std::tuple<bool, vr::HmdMatrix34_t>(
      result,
      standingZeroPoseToRawTrackingPose
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingPlayAreaSize,
    int,
    float,
    float
  >([=](float sizeX, float sizeZ) {
    vrcompositor->SetWorkingPlayAreaSize(sizeX, sizeZ);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsInfo,
    int,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    vrcompositor->SetWorkingCollisionBoundsInfo(quadsBuffer.data(), unQuadsCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >([=](vr::HmdMatrix34_t seatedZeroPoseToRawTrackingPose) {
    vrcompositor->SetWorkingSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >([=](vr::HmdMatrix34_t standingZeroPoseToRawTrackingPose) {
    vrcompositor->SetWorkingStandingZeroPoseToRawTrackingPose(&standingZeroPoseToRawTrackingPose);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_ReloadFromDisk,
    int,
    vr::EChaperoneConfigFile
  >([=](vr::EChaperoneConfigFile configFile) {
    vrcompositor->ReloadFromDisk(configFile);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >([=]() {
    vr::HmdMatrix34_t seatedZeroPoseToRawTrackingPose;
    auto result = vrcompositor->GetLiveSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
    return std::tuple<bool, vr::HmdMatrix34_t>(
      result,
      seatedZeroPoseToRawTrackingPose
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo,
    int,
    managed_binary<uint8_t>,
    uint32_t
  >([=](managed_binary<uint8_t> tagsBuffer, uint32_t unTagCount) {
    vrcompositor->SetWorkingCollisionBoundsTagsInfo(tagsBuffer.data(), unTagCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo,
    std::tuple<bool, managed_binary<uint8_t>, uint32_t>,
    managed_binary<uint8_t>,
    uint32_t
  >([=](managed_binary<uint8_t> tagsBuffer, uint32_t unTagCount) {
    vrcompositor->GetLiveCollisionBoundsTagsInfo(tagsBuffer.size() > 0 ? tagsBuffer.data() : nullptr, &unTagCount);
    return std::tuple<bool, managed_binary<uint8_t>, uint32_t>(
      std::move(tagsBuffer),
      unTagCount
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingPhysicalBoundsInfo,
    bool,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    return vrcompositor->SetWorkingPhysicalBoundsInfo(quadsBuffer.data(), unQuadsCount);
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLivePhysicalBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    auto result = vrcompositor->GetLivePhysicalBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    return std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>(
      result,
      std::move(quadsBuffer),
      unQuadsCount
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_ExportLiveToBuffer,
    std::tuple<bool, managed_binary<char>, uint32_t>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> buffer, uint32_t nBufferLength) {
    auto result = vrcompositor->ExportLiveToBuffer(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &nBufferLength);
    return std::tuple<bool, managed_binary<char>, uint32_t>(
      result,
      std::move(buffer),
      nBufferLength
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_ImportFromBufferToWorking,
    bool,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> buffer, uint32_t nImportFlags) {
    return vrcompositor->ImportFromBufferToWorking(buffer.data(), nImportFlags);
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingPerimeter,
    int,
    managed_binary<vr::HmdVector2_t>,
    uint32_t
  >([=](managed_binary<vr::HmdVector2_t> pointBuffer, uint32_t unPointCount) {
    vrcompositor->SetWorkingPerimeter(pointBuffer.data(), unPointCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_ShowWorkingSetPreview,
    int
  >([=]() {
    vrcompositor->ShowWorkingSetPreview();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_HideWorkingSetPreview,
    int
  >([=]() {
    vrcompositor->HideWorkingSetPreview();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_RoomSetupStarting,
    int
  >([=]() {
    vrcompositor->RoomSetupStarting();
    return 0;
  });
}
bool PVRCompositor::CommitWorkingCopy(vr::EChaperoneConfigFile configFile) {
  return fnp.call<
    kIVRChaperoneSetup_CommitWorkingCopy,
    bool,
    EChaperoneConfigFile
  >(configFile);
}
void PVRCompositor::RevertWorkingCopy() {
  fnp.call<
    kIVRChaperoneSetup_RevertWorkingCopy,
    int
  >();
}
bool PVRCompositor::GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingPlayAreaSize,
    std::tuple<bool, float, float>
  >();
  *pSizeX = std::get<1>(result);
  *pSizeZ = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::GetWorkingPlayAreaRect(vr::HmdQuad_t *rect) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingPlayAreaRect,
    std::tuple<bool, vr::HmdQuad_t>
  >();
  *rect = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRCompositor::GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), *punQuadsCount);
  if (pQuadsBuffer) {
    memcpy(pQuadsBuffer, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::HmdQuad_t));
  }
  *punQuadsCount = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLiveCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), *punQuadsCount);
  if (pQuadsBuffer) {
    memcpy(pQuadsBuffer, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::HmdQuad_t));
  }
  *punQuadsCount = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatSeatedZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRCompositor::GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatStandingZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
void PVRCompositor::SetWorkingPlayAreaSize(float sizeX, float sizeZ) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingPlayAreaSize,
    int,
    float,
    float
  >(sizeX, sizeZ);
}
void PVRCompositor::SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(unQuadsCount);
  memcpy(quadsBuffer.data(), pQuadsBuffer, unQuadsCount * sizeof(vr::HmdQuad_t));
  fnp.call<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsInfo,
    int,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), unQuadsCount);
}
void PVRCompositor::SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >(*pMatSeatedZeroPoseToRawTrackingPose);
}
void PVRCompositor::SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >(*pMatStandingZeroPoseToRawTrackingPose);
}
void PVRCompositor::ReloadFromDisk(vr::EChaperoneConfigFile configFile) {
  fnp.call<
    kIVRChaperoneSetup_ReloadFromDisk,
    int,
    vr::EChaperoneConfigFile
  >(configFile);
}
bool PVRCompositor::GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatSeatedZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
void PVRCompositor::SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount) {
  managed_binary<uint8_t> tagsBuffer(unTagCount);
  memcpy(tagsBuffer.data(), pTagsBuffer, unTagCount);
  fnp.call<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo,
    int,
    managed_binary<uint8_t>,
    uint32_t
  >(std::move(tagsBuffer), unTagCount);
}
bool PVRCompositor::GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount) {
  managed_binary<uint8_t> tagsBuffer(pTagsBuffer ? *punTagCount : 0);
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo,
    std::tuple<bool, managed_binary<uint8_t>, uint32_t>,
    managed_binary<uint8_t>,
    uint32_t
  >(std::move(tagsBuffer), *punTagCount);
  if (pTagsBuffer) {
    memcpy(pTagsBuffer, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(uint8_t));
  }
  *punTagCount = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(unQuadsCount);
  memcpy(quadsBuffer.data(), pQuadsBuffer, unQuadsCount * sizeof(vr::HmdQuad_t));
  return fnp.call<
    kIVRChaperoneSetup_SetWorkingPhysicalBoundsInfo,
    bool,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), unQuadsCount);
}
bool PVRCompositor::GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLivePhysicalBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), *punQuadsCount);
  if (pQuadsBuffer) {
    memcpy(pQuadsBuffer, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::HmdQuad_t));
  }
  *punQuadsCount = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength) {
  auto result = fnp.call<
    kIVRChaperoneSetup_ExportLiveToBuffer,
    std::tuple<bool, managed_binary<char>, uint32_t>
  >();
  memcpy(pBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  *pnBufferLength = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRCompositor::ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags) {
  managed_binary<char> buffer(strlen(pBuffer)+1);
  memcpy(buffer.data(), pBuffer, buffer.size());
  return fnp.call<
    kIVRChaperoneSetup_ImportFromBufferToWorking,
    bool,
    managed_binary<char>,
    uint32_t
  >(std::move(buffer), nImportFlags);
}
void PVRCompositor::SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) vr::HmdVector2_t *pPointBuffer, uint32_t unPointCount) {
  managed_binary<vr::HmdVector2_t> pointBuffer(unPointCount);
  memcpy(pointBuffer.data(), pPointBuffer, unPointCount * sizeof(vr::HmdVector2_t));
  fnp.call<
    kIVRChaperoneSetup_SetWorkingPerimeter,
    int,
    managed_binary<vr::HmdVector2_t>,
    uint32_t
  >(std::move(pointBuffer), unPointCount);
}
void PVRCompositor::ShowWorkingSetPreview() {
  fnp.call<
    kIVRChaperoneSetup_ShowWorkingSetPreview,
    int
  >();
}
void PVRCompositor::HideWorkingSetPreview() {
  fnp.call<
    kIVRChaperoneSetup_HideWorkingSetPreview,
    int
  >();
}
void PVRCompositor::RoomSetupStarting() {
  fnp.call<
    kIVRChaperoneSetup_RoomSetupStarting,
    int
  >();
}
}