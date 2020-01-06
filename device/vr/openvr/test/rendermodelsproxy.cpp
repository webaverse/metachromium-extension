// #include <chrono>
#include "device/vr/openvr/test/rendermodelproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";

PVRRenderModels::PVRRenderModels(IVRRenderModels *vrrendermodels, FnProxy &fnp) : vrrendermodels(vrrendermodels), fnp(fnp) {
  fnp.reg<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

    // auto start = std::chrono::high_resolution_clock::now();
    EVRCompositorError error = vrcompositor->GetLastPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);
    /* auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    getOut() << "get last poses real " << elapsed.count() << std::endl; */

    return std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
  });
}
EVRCompositorError PVRRenderModels::WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  // getOut() << "wait get poses client 1" << std::endl;
  
}
vr::EVRRenderModelError PVRRenderModels::LoadRenderModel_Async(const char *pchRenderModelName, vr::RenderModel_t **ppRenderModel) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  auto result = fnp.call<
    kIVRRenderModels_LoadRenderModel_Async,
    std::tuple<vr::EVRRenderModelError, managed_binary<RenderModel_Vertex_t>, uint32_t, managed_binary<uint16_t>, uint32_t, TextureID_t>,
    managed_binary<char>
  >(std::move(renderModelName));
  RenderModel_Vertex_t *rVertexData = std::get<1>(result).size() > 0 ? std::get<1>(result).release() : nullptr;
  uint32_t unVertexCount = std::get<2>(result);
  uint16_t *rIndexData = std::get<3>(result).size() > 0 ? std::get<3>(result).release() : nullptr;
  uint32_t unTriangleCount = std::get<4>(result);
  TextureID_t diffuseTextureId = std::get<5>(result);
  if (rVertexData) {
    *ppRenderModel = new vr::RenderModel_t{
      rVertexData,
      unVertexCount,
      rIndexData,
      unTriangleCount
    };
  } else {
    *ppRenderModel = nullptr;
  }
  return std::get<0>(result);
}
void PVRRenderModels::FreeRenderModel(vr::RenderModel_t *pRenderModel) {
  delete[] pRenderModel->rVertexData;
  delete[] pRenderModel->rIndexData;
  delete pRenderModel;
}
vr::EVRRenderModelError PVRRenderModels::LoadTexture_Async(vr::TextureID_t textureId, vr::RenderModel_TextureMap_t **ppTexture) {
  // managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  // memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  auto result = fnp.call<
    kIVRRenderModels_LoadTexture_Async,
    std:tuple<vr::EVRRenderModelError, uint16_t, uint16_t, managed_binary<uint8_t>>,
    vr::TextureID_t
  >(textureId);
  uint16_t unWidth = std::get<1>(result);
  uint16_t unHeight = std::get<2>(result);
  uint8_t *rubTextureMapData = std::get<3>(result).size() > 0 ? std::get<3>(result).release() : nullptr;
  if (rubTextureMapData) {
    *ppTexture = new vr::RenderModel_TextureMap_t{
      unWidth,
      unHeight,
      rubTextureMapData
    };
  } else {
    *ppTexture = nullptr;
  }
  return std::get<0>(result);
}
virtual void PVRRenderModels::FreeTexture(vr::RenderModel_TextureMap_t *pTexture) {
  delete[] pTexture->rubTextureMapData;
}
virtual vr::EVRRenderModelError PVRRenderModels::LoadTextureD3D11_Async(vr::TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D) {
  getOut() << "LoadTextureD3D11_Async abort" << std::endl;
  abort();
  return VRRenderModelError_None;
}
virtual vr::EVRRenderModelError PVRRenderModels::LoadIntoTextureD3D11_Async(vr::TextureID_t textureId, void *pDstTexture) {
  getOut() << "LoadIntoTextureD3D11_Async abort" << std::endl;
  abort();
  return VRRenderModelError_None;
}
virtual void PVRRenderModels::FreeTextureD3D11(void *pD3D11Texture2D) {
  getOut() << "FreeTextureD3D11 abort" << std::endl;
  abort();
  return VRRenderModelError_None;
}
virtual uint32_t PVRRenderModels::GetRenderModelName(uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen) {
  auto result = fnp.call<
    kIVRRenderModels_GetRenderModelName,
    std:tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unRenderModelIndex, unRenderModelNameLen);
  memcpy(pchRenderModelName, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
virtual uint32_t PVRRenderModels::GetRenderModelCount() {
  return fnp.call<
    kIVRRenderModels_GetRenderModelCount,
    uint32_t
  >();
}
virtual uint32_t PVRRenderModels::GetComponentCount(const char *pchRenderModelName) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  return fnp.call<
    kIVRRenderModels_GetComponentCount,
    uint32_t,
    managed_binary<char>
  >(std::move(renderModelName));
}
virtual uint32_t PVRRenderModels::GetComponentName(const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING() char *pchComponentName, uint32_t unComponentNameLen) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  auto result = fnp.call<
    kIVRRenderModels_GetComponentName,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    uint32_t,
    uint32_t
  >(std::move(renderModelName), unComponentIndex, unComponentNameLen);
  return std::get<0>(result);
}
virtual uint64_t PVRRenderModels::GetComponentButtonMask(const char *pchRenderModelName, const char *pchComponentName) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());

  auto result = fnp.call<
    kIVRRenderModels_GetComponentButtonMask,
    uint64_t,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(renderModelName), std::move(componentName), unComponentIndex, unComponentNameLen);
  return std::get<0>(result);
}
virtual uint32_t PVRRenderModels::GetComponentRenderModelName(const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING() char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());

  auto result = fnp.call<
    kIVRRenderModels_GetComponentRenderModelName,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >(std::move(renderModelName), std::move(componentName), unComponentRenderModelNameLen);
  return std::get<0>(result);
}
virtual bool PVRRenderModels::GetComponentStateForDevicePath(const char *pchRenderModelName, const char *pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());
  vr::RenderModel_ControllerMode_State_t state = *vr::RenderModel_ControllerMode_State_t;

  auto result = fnp.call<
    kIVRRenderModels_GetComponentStateForDevicePath,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRInputValueHandle_t,
    vr::RenderModel_ControllerMode_State_t
  >(std::move(renderModelName), std::move(componentName), devicePath, state);
  return std::get<0>(result);
}
virtual bool PVRRenderModels::GetComponentState(const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());
  vr::RenderModel_ControllerMode_State_t state = *vr::RenderModel_ControllerMode_State_t;

  auto result = fnp.call<
    kIVRRenderModels_GetComponentState,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRInputValueHandle_t,
    vr::RenderModel_ControllerMode_State_t
  >(std::move(renderModelName), std::move(componentName), devicePath, state);
  return std::get<0>(result);
}
virtual bool PVRRenderModels::RenderModelHasComponent(const char *pchRenderModelName, const char *pchComponentName) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());

  return fnp.call<
    kIVRRenderModels_RenderModelHasComponent,
    bool,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(renderModelName), std::move(componentName));
}
virtual uint32_t PVRRenderModels::GetRenderModelThumbnailURL(const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  // managed_binary<char> thumbnailUrl(strlen(pchThumbnailURL)+1);
  // memcpy(thumbnailUrl.data(), pchThumbnailURL, thumbnailUrl.size());

  auto result = fnp.call<
    kIVRRenderModels_RenderModelHasComponent,
    std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>,
    managed_binary<char>,
    uint32_t
  >(std::move(renderModelName), unThumbnailURLLen);
  memcpy(pchThumbnailURL, std::get<1>(result).data(), std::get<1>(result).size());
  if (peError) {
    *peError = std::get<2>(result);
  }
  return std::get<0>(result);
}
virtual uint32_t PVRRenderModels::GetRenderModelOriginalPath(const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  auto result = fnp.call<
    kIVRRenderModels_GetRenderModelOriginalPath,
    std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>,
    managed_binary<char>,
    uint32_t
  >(std::move(renderModelName), unThumbnailURLLen);
  memcpy(pchThumbnailURL, std::get<1>(result).data(), std::get<1>(result).size());
  if (peError) {
    *peError = std::get<2>(result);
  }
  return std::get<0>(result);
}
virtual const char *PVRRenderModels::GetRenderModelErrorNameFromEnum(vr::EVRRenderModelError error) {
  getOut() << "GetRenderModelErrorNameFromEnum abort" << std::endl;
  abort();
  return "";
}
}