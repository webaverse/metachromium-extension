// #include <chrono>
#include "device/vr/openvr/test/screenshotsproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRChaperone_GetCalibrationState[] = "Chaperone::GetCalibrationState";
char kIVRChaperone_GetPlayAreaSize[] = "Chaperone::GetPlayAreaSize";
char kIVRChaperone_GetPlayAreaRect[] = "Chaperone::GetPlayAreaRect";
char kIVRChaperone_ReloadInfo[] = "Chaperone::ReloadInfo";
char kIVRChaperone_SetSceneColor[] = "Chaperone::SetSceneColor";
char kIVRChaperone_GetBoundsColor[] = "Chaperone::GetBoundsColor";
char kIVRChaperone_AreBoundsVisible[] = "Chaperone::AreBoundsVisible";
char kIVRChaperone_ForceBoundsVisible[] = "Chaperone::ForceBoundsVisible";

PVRChaperone::PVRChaperone(IVRChaperone *vrchaperone, FnProxy &fnp) : vrchaperone(vrchaperone), fnp(fnp) {
  fnp.reg<
    kIVRChaperone_GetCalibrationState,
    ChaperoneCalibrationState
  >([=]() {
    return vrchaperone->GetCalibrationState();
  });
  fnp.reg<
    kIVRChaperone_GetPlayAreaSize,
    std::tuple<bool, float, float>
  >([=]() {
    float sizeX, sizeZ;
    auto result = vrchaperone->GetPlayAreaSize(&sizeX, &sizeZ);
    return std::tuple<bool, float, float>(
      result,
      sizeX,
      sizeZ
    );
  });
  fnp.reg<
    kIVRChaperone_GetPlayAreaRect,
    std::tuple<bool, HmdQuad_t>
  >([=]() {
    HmdQuad_t hmdQuad;
    auto result = vrchaperone->GetPlayAreaRect(&hmdQuad);
    return std::tuple<bool, HmdQuad_t>(
      result,
      hmdQuad
    );
  });
  fnp.reg<
    kIVRChaperone_ReloadInfo,
    int
  >([=]() {
    vrchaperone->ReloadInfo();
    return 0;
  });
  fnp.reg<
    kIVRChaperone_SetSceneColor,
    int,
    vr::HmdColor_t
  >([=](vr::HmdColor_t color) {
    vrchaperone->SetSceneColor(color);
    return 0;
  });
  fnp.reg<
    kIVRChaperone_GetBoundsColor,
    std::tuple<managed_binary<vr::HmdColor_t>, vr::HmdColor_t>,
    int,
    float
  >([=](int nNumOutputColors, float flCollisionBoundsFadeDistance) {
    managed_binary<vr::HmdColor_t> outputColorArray(nNumOutputColors);
    vr::HmdColor_t outputCameraColor;
    vrchaperone->GetBoundsColor(outputColorArray.data(), nNumOutputColors, flCollisionBoundsFadeDistance, &outputCameraColor);
    return std::tuple<managed_binary<vr::HmdColor_t>, vr::HmdColor_t>(
      std::move(outputColorArray),
      outputCameraColor
    );
  });
  fnp.reg<
    kIVRChaperone_AreBoundsVisible,
    bool
  >([=]() {
    return vrchaperone->AreBoundsVisible();
  });
  fnp.reg<
    kIVRChaperone_ForceBoundsVisible,
    int,
    bool
  >([=](bool bForce) {
    vrchaperone->ForceBoundsVisible(bForce);
    return 0;
  });
}
ChaperoneCalibrationState PVRChaperone::GetCalibrationState() {
  return fnp.call<
    kIVRChaperone_GetCalibrationState,
    ChaperoneCalibrationState
  >();
}
bool PVRChaperone::GetPlayAreaSize(float *pSizeX, float *pSizeZ) {
  auto result = fnp.call<
    kIVRChaperone_GetPlayAreaSize,
    std::tuple<bool, float, float>
  >();
  *pSizeX = std::get<1>(result);
  *pSizeZ = std::get<2>(result);
  return std::get<0>(result);
}
bool PVRChaperone::GetPlayAreaRect(vr::HmdQuad_t *rect) {
  auto result = fnp.call<
    kIVRChaperone_GetPlayAreaRect,
    std::tuple<bool, HmdQuad_t>
  >();
  *rect = std::get<1>(result);
  return std::get<0>(result);
}
void PVRChaperone::ReloadInfo(void) {
  fnp.call<
    kIVRChaperone_ReloadInfo,
    int
  >();
}
void PVRChaperone::PVRChaperone::SetSceneColor(vr::HmdColor_t color) {
  fnp.call<
    kIVRChaperone_SetSceneColor,
    int,
    vr::HmdColor_t
  >(color);
}
void PVRChaperone::GetBoundsColor(vr::HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, vr::HmdColor_t *pOutputCameraColor) {
  auto result = fnp.call<
    kIVRChaperone_GetBoundsColor,
    std::tuple<managed_binary<vr::HmdColor_t>, vr::HmdColor_t>,
    int,
    float
  >(nNumOutputColors, flCollisionBoundsFadeDistance);
  memcpy(pOutputColorArray, std::get<0>(result).data(), std::get<0>(result).size() * sizeof(vr::HmdColor_t));
  *pOutputCameraColor = std::get<1>(result);
}
bool PVRChaperone::AreBoundsVisible() {
  return fnp.call<
    kIVRChaperone_AreBoundsVisible,
    bool
  >();
}
void PVRChaperone::ForceBoundsVisible(bool bForce) {
  fnp.call<
    kIVRChaperone_ForceBoundsVisible,
    int,
    bool
  >(bForce);
}
}