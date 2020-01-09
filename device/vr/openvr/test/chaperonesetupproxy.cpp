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
    return vrchaperonesetup->CommitWorkingCopy(configFile);
  });
  fnp.reg<
    kIVRChaperoneSetup_RevertWorkingCopy,
    int
  >([=]() {
    vrchaperonesetup->RevertWorkingCopy();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingPlayAreaSize,
    std::tuple<bool, float, float>
  >([=]() {
    float sizeX;
    float sizeZ;
    auto result = vrchaperonesetup->GetWorkingPlayAreaSize(&sizeX, &sizeZ);
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
    auto result = vrchaperonesetup->GetWorkingPlayAreaRect(&rect);
    return std::tuple<bool, vr::HmdQuad_t>(
      result,
      rect
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetWorkingCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    auto result = vrchaperonesetup->GetWorkingCollisionBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    return std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>(
      result,
      std::move(quadsBuffer),
      unQuadsCount
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    getOut() << "server GetLiveCollisionBoundsInfo 1 " << quadsBuffer.size() << " " << unQuadsCount << std::endl;
    auto result = vrchaperonesetup->GetLiveCollisionBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    getOut() << "server GetLiveCollisionBoundsInfo 2 " << quadsBuffer.size() << " " << unQuadsCount << std::endl;
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
    auto result = vrchaperonesetup->GetWorkingSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
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
    auto result = vrchaperonesetup->GetWorkingStandingZeroPoseToRawTrackingPose(&standingZeroPoseToRawTrackingPose);
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
    vrchaperonesetup->SetWorkingPlayAreaSize(sizeX, sizeZ);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsInfo,
    int,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >([=](managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount) {
    vrchaperonesetup->SetWorkingCollisionBoundsInfo(quadsBuffer.data(), unQuadsCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >([=](vr::HmdMatrix34_t seatedZeroPoseToRawTrackingPose) {
    vrchaperonesetup->SetWorkingSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >([=](vr::HmdMatrix34_t standingZeroPoseToRawTrackingPose) {
    vrchaperonesetup->SetWorkingStandingZeroPoseToRawTrackingPose(&standingZeroPoseToRawTrackingPose);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_ReloadFromDisk,
    int,
    vr::EChaperoneConfigFile
  >([=](vr::EChaperoneConfigFile configFile) {
    vrchaperonesetup->ReloadFromDisk(configFile);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >([=]() {
    vr::HmdMatrix34_t seatedZeroPoseToRawTrackingPose;
    auto result = vrchaperonesetup->GetLiveSeatedZeroPoseToRawTrackingPose(&seatedZeroPoseToRawTrackingPose);
    return std::tuple<bool, vr::HmdMatrix34_t>(
      result,
      seatedZeroPoseToRawTrackingPose
    );
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo,
    int/*,
    managed_binary<uint8_t>,
    uint32_t*/
  >([=](/*managed_binary<uint8_t> tagsBuffer, uint32_t unTagCount*/) {
    getOut() << "SetWorkingCollisionBoundsTagsInfo abort" << std::endl;
    abort();
    // vrchaperonesetup->SetWorkingCollisionBoundsTagsInfo(tagsBuffer.data(), unTagCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo,
    int
    /* std::tuple<bool, managed_binary<uint8_t>, uint32_t>,
    managed_binary<uint8_t>,
    uint32_t */
  >([=](/*managed_binary<uint8_t> tagsBuffer, uint32_t unTagCount*/) {
    getOut() << "GetLiveCollisionBoundsTagsInfo abort" << std::endl;
    abort();
    return 0;
    /* vrchaperonesetup->GetLiveCollisionBoundsTagsInfo(tagsBuffer.size() > 0 ? tagsBuffer.data() : nullptr, &unTagCount);
    return std::tuple<bool, managed_binary<uint8_t>, uint32_t>(
      std::move(tagsBuffer),
      unTagCount
    ); */
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingPhysicalBoundsInfo,
    int
    /* bool,
    managed_binary<vr::HmdQuad_t>,
    uint32_t */
  >([=](/*managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount*/) {
    getOut() << "SetWorkingPhysicalBoundsInfo abort" << std::endl;
    abort();
    return 0;
    // return vrchaperonesetup->SetWorkingPhysicalBoundsInfo(quadsBuffer.data(), unQuadsCount);
  });
  fnp.reg<
    kIVRChaperoneSetup_GetLivePhysicalBoundsInfo,
    int
    /* std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>,
    managed_binary<vr::HmdQuad_t>,
    uint32_t */
  >([=](/*managed_binary<vr::HmdQuad_t> quadsBuffer, uint32_t unQuadsCount*/) {
    getOut() << "GetLivePhysicalBoundsInfo abort" << std::endl;
    abort();
    return 0;
    /* auto result = vrchaperonesetup->GetLivePhysicalBoundsInfo(quadsBuffer.size() > 0 ? quadsBuffer.data() : nullptr, &unQuadsCount);
    return std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>(
      result,
      std::move(quadsBuffer),
      unQuadsCount
    ); */
  });
  fnp.reg<
    kIVRChaperoneSetup_ExportLiveToBuffer,
    std::tuple<bool, managed_binary<char>, uint32_t>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> buffer, uint32_t nBufferLength) {
    auto result = vrchaperonesetup->ExportLiveToBuffer(buffer.size() > 0 ? buffer.data() : nullptr, &nBufferLength);
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
    return vrchaperonesetup->ImportFromBufferToWorking(buffer.data(), nImportFlags);
  });
  fnp.reg<
    kIVRChaperoneSetup_SetWorkingPerimeter,
    int,
    managed_binary<vr::HmdVector2_t>,
    uint32_t
  >([=](managed_binary<vr::HmdVector2_t> pointBuffer, uint32_t unPointCount) {
    vrchaperonesetup->SetWorkingPerimeter(pointBuffer.data(), unPointCount);
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_ShowWorkingSetPreview,
    int
  >([=]() {
    vrchaperonesetup->ShowWorkingSetPreview();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_HideWorkingSetPreview,
    int
  >([=]() {
    vrchaperonesetup->HideWorkingSetPreview();
    return 0;
  });
  fnp.reg<
    kIVRChaperoneSetup_RoomSetupStarting,
    int
  >([=]() {
    vrchaperonesetup->RoomSetupStarting();
    return 0;
  });
}
bool PVRChaperoneSetup::CommitWorkingCopy(vr::EChaperoneConfigFile configFile) {
  return fnp.call<
    kIVRChaperoneSetup_CommitWorkingCopy,
    bool,
    EChaperoneConfigFile
  >(configFile);
}
void PVRChaperoneSetup::RevertWorkingCopy() {
  fnp.call<
    kIVRChaperoneSetup_RevertWorkingCopy,
    int
  >();
}
bool PVRChaperoneSetup::GetWorkingPlayAreaSize(float *pSizeX, float *pSizeZ) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingPlayAreaSize,
    std::tuple<bool, float, float>
  >();
  *pSizeX = std::get<1>(result);
  *pSizeZ = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRChaperoneSetup::GetWorkingPlayAreaRect(vr::HmdQuad_t *rect) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingPlayAreaRect,
    std::tuple<bool, vr::HmdQuad_t>
  >();
  *rect = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRChaperoneSetup::GetWorkingCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingCollisionBoundsInfo,
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
bool PVRChaperoneSetup::GetLiveCollisionBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  getOut() << "get live 1 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
  managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
  getOut() << "get live 2 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLiveCollisionBoundsInfo,
    std::tuple<bool, managed_binary<vr::HmdQuad_t>, uint32_t>,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), *punQuadsCount);
  getOut() << "get live 3 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
  if (pQuadsBuffer) {
    getOut() << "get live 4 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
    memcpy(pQuadsBuffer, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(vr::HmdQuad_t));
  }
  getOut() << "get live 5 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
  *punQuadsCount = std::get<2>(result);
  getOut() << "get live 6 " << (void *)pQuadsBuffer << " " << *punQuadsCount << std::endl;
  return std::get<0>(result);
}
bool PVRChaperoneSetup::GetWorkingSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatSeatedZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRChaperoneSetup::GetWorkingStandingZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatStandingZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
void PVRChaperoneSetup::SetWorkingPlayAreaSize(float sizeX, float sizeZ) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingPlayAreaSize,
    int,
    float,
    float
  >(sizeX, sizeZ);
}
void PVRChaperoneSetup::SetWorkingCollisionBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  managed_binary<vr::HmdQuad_t> quadsBuffer(unQuadsCount);
  memcpy(quadsBuffer.data(), pQuadsBuffer, unQuadsCount * sizeof(vr::HmdQuad_t));
  fnp.call<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsInfo,
    int,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), unQuadsCount);
}
void PVRChaperoneSetup::SetWorkingSeatedZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >(*pMatSeatedZeroPoseToRawTrackingPose);
}
void PVRChaperoneSetup::SetWorkingStandingZeroPoseToRawTrackingPose(const vr::HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose) {
  fnp.call<
    kIVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose,
    int,
    vr::HmdMatrix34_t
  >(*pMatStandingZeroPoseToRawTrackingPose);
}
void PVRChaperoneSetup::ReloadFromDisk(vr::EChaperoneConfigFile configFile) {
  fnp.call<
    kIVRChaperoneSetup_ReloadFromDisk,
    int,
    vr::EChaperoneConfigFile
  >(configFile);
}
bool PVRChaperoneSetup::GetLiveSeatedZeroPoseToRawTrackingPose(vr::HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose) {
  auto result = fnp.call<
    kIVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose,
    std::tuple<bool, vr::HmdMatrix34_t>
  >();
  *pmatSeatedZeroPoseToRawTrackingPose = std::get<1>(result);
  return std::get<0>(result);
}
void PVRChaperoneSetup::SetWorkingCollisionBoundsTagsInfo(VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount) {
  getOut() << "SetWorkingCollisionBoundsTagsInfo abort" << std::endl;
  abort();
  /* managed_binary<uint8_t> tagsBuffer(unTagCount);
  memcpy(tagsBuffer.data(), pTagsBuffer, unTagCount);
  fnp.call<
    kIVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo,
    int,
    managed_binary<uint8_t>,
    uint32_t
  >(std::move(tagsBuffer), unTagCount); */
}
bool PVRChaperoneSetup::GetLiveCollisionBoundsTagsInfo(VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount) {
  getOut() << "GetLiveCollisionBoundsTagsInfo abort" << std::endl;
  abort();
  return false;
  /* managed_binary<uint8_t> tagsBuffer(pTagsBuffer ? *punTagCount : 0);
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
  return std::get<0>(result); */
}
bool PVRChaperoneSetup::SetWorkingPhysicalBoundsInfo(VR_ARRAY_COUNT(unQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount) {
  getOut() << "SetWorkingPhysicalBoundsInfo abort" << std::endl;
  abort();
  return false; 
  /* managed_binary<vr::HmdQuad_t> quadsBuffer(unQuadsCount);
  memcpy(quadsBuffer.data(), pQuadsBuffer, unQuadsCount * sizeof(vr::HmdQuad_t));
  return fnp.call<
    kIVRChaperoneSetup_SetWorkingPhysicalBoundsInfo,
    bool,
    managed_binary<vr::HmdQuad_t>,
    uint32_t
  >(std::move(quadsBuffer), unQuadsCount); */
}
bool PVRChaperoneSetup::GetLivePhysicalBoundsInfo(VR_OUT_ARRAY_COUNT(punQuadsCount) vr::HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount) {
  getOut() << "GetLivePhysicalBoundsInfo abort" << std::endl;
  abort();
  return false; 
  /* managed_binary<vr::HmdQuad_t> quadsBuffer(pQuadsBuffer ? *punQuadsCount : 0);
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
  return std::get<0>(result); */
}
bool PVRChaperoneSetup::ExportLiveToBuffer(VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength) {
  auto result = fnp.call<
    kIVRChaperoneSetup_ExportLiveToBuffer,
    std::tuple<bool, managed_binary<char>, uint32_t>
  >();
  memcpy(pBuffer, std::get<1>(result).data(), std::get<1>(result).size());
  *pnBufferLength = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRChaperoneSetup::ImportFromBufferToWorking(const char *pBuffer, uint32_t nImportFlags) {
  managed_binary<char> buffer(strlen(pBuffer)+1);
  memcpy(buffer.data(), pBuffer, buffer.size());
  return fnp.call<
    kIVRChaperoneSetup_ImportFromBufferToWorking,
    bool,
    managed_binary<char>,
    uint32_t
  >(std::move(buffer), nImportFlags);
}
void PVRChaperoneSetup::SetWorkingPerimeter(VR_ARRAY_COUNT(unPointCount) vr::HmdVector2_t *pPointBuffer, uint32_t unPointCount) {
  managed_binary<vr::HmdVector2_t> pointBuffer(unPointCount);
  memcpy(pointBuffer.data(), pPointBuffer, unPointCount * sizeof(vr::HmdVector2_t));
  fnp.call<
    kIVRChaperoneSetup_SetWorkingPerimeter,
    int,
    managed_binary<vr::HmdVector2_t>,
    uint32_t
  >(std::move(pointBuffer), unPointCount);
}
void PVRChaperoneSetup::ShowWorkingSetPreview() {
  fnp.call<
    kIVRChaperoneSetup_ShowWorkingSetPreview,
    int
  >();
}
void PVRChaperoneSetup::HideWorkingSetPreview() {
  fnp.call<
    kIVRChaperoneSetup_HideWorkingSetPreview,
    int
  >();
}
void PVRChaperoneSetup::RoomSetupStarting() {
  fnp.call<
    kIVRChaperoneSetup_RoomSetupStarting,
    int
  >();
}
}