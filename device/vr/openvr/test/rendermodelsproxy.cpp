// #include <chrono>
#include "device/vr/openvr/test/rendermodelsproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRRenderModels_LoadRenderModel_Async[] = "RenderModels::LoadRenderModel_Async";
char kIVRRenderModels_FreeRenderModel[] = "RenderModels::FreeRenderModel";
char kIVRRenderModels_LoadTexture_Async[] = "RenderModels::LoadTexture_Async";
char kIVRRenderModels_FreeTexture[] = "RenderModels::FreeTexture";
char kIVRRenderModels_LoadTextureD3D11_Async[] = "RenderModels::LoadTextureD3D11_Async";
char kIVRRenderModels_LoadIntoTextureD3D11_Async[] = "RenderModels::LoadIntoTextureD3D11_Async";
char kIVRRenderModels_FreeTextureD3D11[] = "RenderModels::FreeTextureD3D11";
char kIVRRenderModels_GetRenderModelName[] = "RenderModels::GetRenderModelName";
char kIVRRenderModels_GetRenderModelCount[] = "RenderModels::GetRenderModelCount";
char kIVRRenderModels_GetComponentCount[] = "RenderModels::GetComponentCount";
char kIVRRenderModels_GetComponentName[] = "RenderModels::GetComponentName";
char kIVRRenderModels_GetComponentButtonMask[] = "RenderModels::GetComponentButtonMask";
char kIVRRenderModels_GetComponentRenderModelName[] = "RenderModels::GetComponentRenderModelName";
char kIVRRenderModels_GetComponentStateForDevicePath[] = "RenderModels::GetComponentStateForDevicePath";
char kIVRRenderModels_GetComponentState[] = "RenderModels::GetComponentState";
char kIVRRenderModels_RenderModelHasComponent[] = "RenderModels::RenderModelHasComponent";
char kIVRRenderModels_GetRenderModelThumbnailURL[] = "RenderModels::GetRenderModelThumbnailURL";
char kIVRRenderModels_GetRenderModelOriginalPath[] = "RenderModels::GetRenderModelOriginalPath";
char kIVRRenderModels_GetRenderModelErrorNameFromEnum[] = "RenderModels::GetRenderModelErrorNameFromEnum";

PVRRenderModels::PVRRenderModels(IVRRenderModels *vrrendermodels, FnProxy &fnp) : vrrendermodels(vrrendermodels), fnp(fnp) {
  fnp.reg<
    kIVRRenderModels_LoadRenderModel_Async,
    std::tuple<vr::EVRRenderModelError, managed_binary<RenderModel_Vertex_t>, uint32_t, managed_binary<uint16_t>, uint32_t, TextureID_t>,
    managed_binary<char>
  >([=](managed_binary<char> renderModelName) {
    vr::RenderModel_t *pRenderModel = nullptr;
    auto result = vrrendermodels->LoadRenderModel_Async(renderModelName.data(), &pRenderModel);
    if (pRenderModel) {
      const RenderModel_Vertex_t *rVertexData = pRenderModel->rVertexData;
      uint32_t unVertexCount = pRenderModel->unVertexCount;
      const uint16_t *rIndexData = pRenderModel->rIndexData;
      uint32_t unTriangleCount = pRenderModel->unTriangleCount;
      TextureID_t diffuseTextureId = pRenderModel->diffuseTextureId;

      managed_binary<RenderModel_Vertex_t> vertexData(unVertexCount);
      memcpy(vertexData.data(), rVertexData, vertexData.size() * sizeof(RenderModel_Vertex_t));
      managed_binary<uint16_t> indexData(unTriangleCount * 3);
      memcpy(indexData.data(), rVertexData, indexData.size() * sizeof(uint16_t));

      return std::tuple<vr::EVRRenderModelError, managed_binary<RenderModel_Vertex_t>, uint32_t, managed_binary<uint16_t>, uint32_t, TextureID_t>(
        result,
        std::move(vertexData),
        unVertexCount,
        std::move(indexData),
        unTriangleCount,
        diffuseTextureId
      );
    } else {
      managed_binary<RenderModel_Vertex_t> vertexData;
      uint32_t unVertexCount = 0;
      managed_binary<uint16_t> indexData;
      uint32_t unTriangleCount = 0;
      TextureID_t diffuseTextureId = 0;
      return std::tuple<vr::EVRRenderModelError, managed_binary<RenderModel_Vertex_t>, uint32_t, managed_binary<uint16_t>, uint32_t, TextureID_t>(
        result,
        std::move(vertexData),
        unVertexCount,
        std::move(indexData),
        unTriangleCount,
        diffuseTextureId
      );
    }
  });
  fnp.reg<
    kIVRRenderModels_FreeRenderModel,
    int
  >([=]() {
    getOut() << "FreeRenderModel abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_LoadTexture_Async,
    std::tuple<vr::EVRRenderModelError, uint16_t, uint16_t, managed_binary<uint8_t>>,
    vr::TextureID_t
  >([=](vr::TextureID_t textureId) {
    vr::RenderModel_TextureMap_t *pTexture = nullptr;
    auto result = vrrendermodels->LoadTexture_Async(textureId, &pTexture);
    if (pTexture) {
      uint16_t unWidth = pTexture->unWidth;
      uint16_t unHeight = pTexture->unHeight;
      const uint8_t *rubTextureMapData = pTexture->rubTextureMapData;
      managed_binary<uint8_t> textureMapData(unWidth * unHeight * 4);
      memcpy(textureMapData.data(), rubTextureMapData, textureMapData.size());

      return std::tuple<vr::EVRRenderModelError, uint16_t, uint16_t, managed_binary<uint8_t>>(
        result,
        unWidth,
        unHeight,
        std::move(textureMapData)
      );
    } else {
      uint16_t unWidth = 0;
      uint16_t unHeight = 0;
      managed_binary<uint8_t> textureMapData;
      return std::tuple<vr::EVRRenderModelError, uint16_t, uint16_t, managed_binary<uint8_t>>(
        result,
        unWidth,
        unHeight,
        std::move(textureMapData)
      );
    }
  });
  fnp.reg<
    kIVRRenderModels_FreeTexture,
    int
  >([=]() {
    getOut() << "FreeRenderModel abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_LoadTextureD3D11_Async,
    int
  >([=]() {
    getOut() << "LoadTextureD3D11_Async abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_LoadIntoTextureD3D11_Async,
    int
  >([=]() {
    getOut() << "LoadIntoTextureD3D11_Async abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_FreeTextureD3D11,
    int
  >([=]() {
    getOut() << "FreeTextureD3D11 abort" << std::endl;
    abort();
    return 0;
  });
  fnp.reg<
    kIVRRenderModels_GetRenderModelName,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderModelIndex, uint32_t unRenderModelNameLen) {
    managed_binary<char> renderModelName(unRenderModelNameLen);
    auto result = vrrendermodels->GetRenderModelName(unRenderModelIndex, renderModelName.data(), unRenderModelNameLen);
    return std::tuple<uint32_t, managed_binary<char>>(
      result,
      std::move(renderModelName)
    );
  });
  fnp.reg<
    kIVRRenderModels_GetRenderModelCount,
    uint32_t
  >([=]() {
    return vrrendermodels->GetRenderModelCount();
  });
  fnp.reg<
    kIVRRenderModels_GetComponentCount,
    uint32_t,
    managed_binary<char>
  >([=](managed_binary<char> renderModelName) {
    return vrrendermodels->GetComponentCount(renderModelName.data());
  });
  fnp.reg<
    kIVRRenderModels_GetComponentName,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    uint32_t,
    uint32_t
  >([=](managed_binary<char> renderModelName, uint32_t unComponentIndex, uint32_t unComponentNameLen) {
    managed_binary<char> componentName(unComponentNameLen);
    auto result = vrrendermodels->GetComponentName(renderModelName.data(), unComponentIndex, componentName.data(), unComponentNameLen);
    return std::tuple<uint32_t, managed_binary<char>>(
      result,
      std::move(componentName)
    );
  });
  fnp.reg<
    kIVRRenderModels_GetComponentButtonMask,
    uint64_t,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> renderModelName, managed_binary<char> componentName) {
    return vrrendermodels->GetComponentButtonMask(renderModelName.data(), componentName.data());
  });
  fnp.reg<
    kIVRRenderModels_GetComponentRenderModelName,
    std::tuple<uint32_t, managed_binary<char>>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> renderModelName, managed_binary<char> componentName, uint32_t unComponentRenderModelNameLen) {
    managed_binary<char> componentRenderModelName(unComponentRenderModelNameLen);
    auto result = vrrendermodels->GetComponentRenderModelName(renderModelName.data(), componentName.data(), componentRenderModelName.data(), unComponentRenderModelNameLen);
    return std::tuple<uint32_t, managed_binary<char>>(
      result,
      std::move(componentRenderModelName)
    );
  });
  fnp.reg<
    kIVRRenderModels_GetComponentStateForDevicePath,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRInputValueHandle_t,
    vr::RenderModel_ControllerMode_State_t
  >([=](managed_binary<char> renderModelName, managed_binary<char> componentName, vr::VRInputValueHandle_t devicePath, vr::RenderModel_ControllerMode_State_t state) {
    RenderModel_ComponentState_t componentState;
    auto result = vrrendermodels->GetComponentStateForDevicePath(renderModelName.data(), componentName.data(), devicePath, &state, &componentState);
    return std::tuple<bool, RenderModel_ComponentState_t>(
      result,
      componentState
    );
  });
  fnp.reg<
    kIVRRenderModels_GetComponentState,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRControllerState_t,
    vr::RenderModel_ControllerMode_State_t
  >([=](managed_binary<char> renderModelName, managed_binary<char> componentName, vr::VRControllerState_t controllerState, vr::RenderModel_ControllerMode_State_t state) {
    RenderModel_ComponentState_t componentState;
    auto result = vrrendermodels->GetComponentState(renderModelName.data(), componentName.data(), &controllerState, &state, &componentState);
    return std::tuple<bool, RenderModel_ComponentState_t>(
      result,
      componentState
    );
  });
  fnp.reg<
    kIVRRenderModels_RenderModelHasComponent,
    bool,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> renderModelName, managed_binary<char> componentName) {
    return vrrendermodels->RenderModelHasComponent(renderModelName.data(), componentName.data());
  });
  fnp.reg<
    kIVRRenderModels_GetRenderModelThumbnailURL,
    std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> renderModelName, uint32_t unThumbnailURLLen) {
    managed_binary<char> thumbnailUrl(unThumbnailURLLen);
    vr::EVRRenderModelError error;
    auto result = vrrendermodels->GetRenderModelThumbnailURL(renderModelName.data(), thumbnailUrl.data(), unThumbnailURLLen, &error);
    return std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>(
      result,
      std::move(thumbnailUrl),
      error
    );
  });
  fnp.reg<
    kIVRRenderModels_GetRenderModelOriginalPath,
    std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> renderModelName, uint32_t unOriginalPathLen) {
    managed_binary<char> originalPath(unOriginalPathLen);
    vr::EVRRenderModelError error;
    auto result = vrrendermodels->GetRenderModelThumbnailURL(renderModelName.data(), originalPath.data(), unOriginalPathLen, &error);
    return std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>(
      result,
      std::move(originalPath),
      error
    );
  });
  fnp.reg<
    kIVRRenderModels_GetRenderModelErrorNameFromEnum,
    int
  >([=]() {
    getOut() << "GetRenderModelErrorNameFromEnum abort" << std::endl;
    abort();
    return 0;
  });
}
vr::EVRRenderModelError PVRRenderModels::LoadRenderModel_Async(const char *pchRenderModelName, vr::RenderModel_t **ppRenderModel) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  auto result = fnp.call<
    kIVRRenderModels_LoadRenderModel_Async,
    std::tuple<vr::EVRRenderModelError, managed_binary<RenderModel_Vertex_t>, uint32_t, managed_binary<uint16_t>, uint32_t, TextureID_t>,
    managed_binary<char>
  >(std::move(renderModelName));
  RenderModel_Vertex_t *rVertexData = new RenderModel_Vertex_t[std::get<1>(result).size()];
  memcpy(rVertexData, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(RenderModel_Vertex_t));
  uint32_t unVertexCount = std::get<2>(result);
  uint16_t *rIndexData = new uint16_t[std::get<3>(result).size()];
  memcpy(rIndexData, std::get<3>(result).data(), std::get<3>(result).size() * sizeof(uint16_t));
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
  auto result = fnp.call<
    kIVRRenderModels_LoadTexture_Async,
    std::tuple<vr::EVRRenderModelError, uint16_t, uint16_t, managed_binary<uint8_t>>,
    vr::TextureID_t
  >(textureId);
  uint16_t unWidth = std::get<1>(result);
  uint16_t unHeight = std::get<2>(result);
  uint8_t *rubTextureMapData = new uint8_t[std::get<3>(result).size()];
  memcpy(rubTextureMapData, std::get<3>(result).data(), std::get<3>(result).size() * sizeof(uint8_t));
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
void PVRRenderModels::FreeTexture(vr::RenderModel_TextureMap_t *pTexture) {
  delete[] pTexture->rubTextureMapData;
}
vr::EVRRenderModelError PVRRenderModels::LoadTextureD3D11_Async(vr::TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D) {
  getOut() << "LoadTextureD3D11_Async abort" << std::endl;
  abort();
  return VRRenderModelError_None;
}
vr::EVRRenderModelError PVRRenderModels::LoadIntoTextureD3D11_Async(vr::TextureID_t textureId, void *pDstTexture) {
  getOut() << "LoadIntoTextureD3D11_Async abort" << std::endl;
  abort();
  return VRRenderModelError_None;
}
void PVRRenderModels::FreeTextureD3D11(void *pD3D11Texture2D) {
  getOut() << "FreeTextureD3D11 abort" << std::endl;
  abort();
}
uint32_t PVRRenderModels::GetRenderModelName(uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen) {
  auto result = fnp.call<
    kIVRRenderModels_GetRenderModelName,
    std::tuple<uint32_t, managed_binary<char>>,
    uint32_t,
    uint32_t
  >(unRenderModelIndex, unRenderModelNameLen);
  memcpy(pchRenderModelName, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
uint32_t PVRRenderModels::GetRenderModelCount() {
  return fnp.call<
    kIVRRenderModels_GetRenderModelCount,
    uint32_t
  >();
}
uint32_t PVRRenderModels::GetComponentCount(const char *pchRenderModelName) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  return fnp.call<
    kIVRRenderModels_GetComponentCount,
    uint32_t,
    managed_binary<char>
  >(std::move(renderModelName));
}
uint32_t PVRRenderModels::GetComponentName(const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING() char *pchComponentName, uint32_t unComponentNameLen) {
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
uint64_t PVRRenderModels::GetComponentButtonMask(const char *pchRenderModelName, const char *pchComponentName) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());

  getOut() << "calling GetComponentButtonMask 1" << std::endl;
  auto result = fnp.call<
    kIVRRenderModels_GetComponentButtonMask,
    uint64_t,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(renderModelName), std::move(componentName));
  getOut() << "calling GetComponentButtonMask 2 " << (void *)result << " " << pchRenderModelName << " " << pchComponentName << std::endl;
  return result;
}
uint32_t PVRRenderModels::GetComponentRenderModelName(const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING() char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) {
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
  memcpy(pchComponentRenderModelName, std::get<1>(result).data(), std::get<1>(result).size());
  return std::get<0>(result);
}
bool PVRRenderModels::GetComponentStateForDevicePath(const char *pchRenderModelName, const char *pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());
  vr::RenderModel_ControllerMode_State_t state = *pState;

  auto result = fnp.call<
    kIVRRenderModels_GetComponentStateForDevicePath,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRInputValueHandle_t,
    vr::RenderModel_ControllerMode_State_t
  >(std::move(renderModelName), std::move(componentName), devicePath, state);
  *pComponentState = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRRenderModels::GetComponentState(const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  managed_binary<char> componentName(strlen(pchComponentName)+1);
  memcpy(componentName.data(), pchComponentName, componentName.size());
  vr::VRControllerState_t controllerState = *pControllerState;
  vr::RenderModel_ControllerMode_State_t state = *pState;

  auto result = fnp.call<
    kIVRRenderModels_GetComponentState,
    std::tuple<bool, RenderModel_ComponentState_t>,
    managed_binary<char>,
    managed_binary<char>,
    vr::VRControllerState_t,
    vr::RenderModel_ControllerMode_State_t
  >(std::move(renderModelName), std::move(componentName), controllerState, state);
  *pComponentState = std::get<1>(result);
  return std::get<0>(result);
}
bool PVRRenderModels::RenderModelHasComponent(const char *pchRenderModelName, const char *pchComponentName) {
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
uint32_t PVRRenderModels::GetRenderModelThumbnailURL(const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());
  // managed_binary<char> thumbnailUrl(strlen(pchThumbnailURL)+1);
  // memcpy(thumbnailUrl.data(), pchThumbnailURL, thumbnailUrl.size());

  auto result = fnp.call<
    kIVRRenderModels_GetRenderModelThumbnailURL,
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
uint32_t PVRRenderModels::GetRenderModelOriginalPath(const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError) {
  managed_binary<char> renderModelName(strlen(pchRenderModelName)+1);
  memcpy(renderModelName.data(), pchRenderModelName, renderModelName.size());

  auto result = fnp.call<
    kIVRRenderModels_GetRenderModelOriginalPath,
    std::tuple<bool, managed_binary<char>, vr::EVRRenderModelError>,
    managed_binary<char>,
    uint32_t
  >(std::move(renderModelName), unOriginalPathLen);
  memcpy(pchOriginalPath, std::get<1>(result).data(), std::get<1>(result).size());
  if (peError) {
    *peError = std::get<2>(result);
  }
  return std::get<0>(result);
}
const char *PVRRenderModels::GetRenderModelErrorNameFromEnum(vr::EVRRenderModelError error) {
  getOut() << "GetRenderModelErrorNameFromEnum abort" << std::endl;
  abort();
  return "";
}
}