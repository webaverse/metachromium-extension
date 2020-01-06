#include "stdafx.h"
#define BASE_IMPL
#include "BaseRenderModels.h"
#include "resources.h"
// #include "convert.h"
#include "Misc/Config.h"

// Used for the hand offsets
#include "BaseCompositor.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;
// using namespace OVR;
using namespace vr;

EVRRenderModelError BaseRenderModels::LoadRenderModel_Async(const char * pchRenderModelName, RenderModel_t ** renderModel) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::LoadRenderModel_Async" << std::endl; });
  // return VRRenderModelError_NotSupported; // XXX
  return g_pvrrendermodels->LoadRenderModel_Async(pchRenderModelName, renderModel);
}

void BaseRenderModels::FreeRenderModel(RenderModel_t * renderModel) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::FreeRenderModel" << std::endl; });
	return g_pvrrendermodels->FreeRenderModel(renderModel);
}

EVRRenderModelError BaseRenderModels::LoadTexture_Async(TextureID_t textureId, RenderModel_TextureMap_t ** texture) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::LoadTexture_Async" << std::endl; });
	return g_pvrrendermodels->LoadTexture_Async(textureId, texture);
}

void BaseRenderModels::FreeTexture(RenderModel_TextureMap_t * texture) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::FreeTexture" << std::endl; });
	return g_pvrrendermodels->FreeTexture(texture);
}

EVRRenderModelError BaseRenderModels::LoadTextureD3D11_Async(TextureID_t textureId, void * pD3D11Device, void ** ppD3D11Texture2D) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::LoadTextureD3D11_Async" << std::endl; });
	return g_pvrrendermodels->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
}

EVRRenderModelError BaseRenderModels::LoadIntoTextureD3D11_Async(TextureID_t textureId, void * pDstTexture) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::LoadIntoTextureD3D11_Async" << std::endl; });
	return g_pvrrendermodels->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
}

void BaseRenderModels::FreeTextureD3D11(void * pD3D11Texture2D) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::FreeTextureD3D11" << std::endl; });
	return g_pvrrendermodels->FreeTextureD3D11(pD3D11Texture2D);
}

uint32_t BaseRenderModels::GetRenderModelName(uint32_t unRenderModelIndex, VR_OUT_STRING() char * pchRenderModelName, uint32_t unRenderModelNameLen) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetRenderModelName" << std::endl; });
	return g_pvrrendermodels->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
}

uint32_t BaseRenderModels::GetRenderModelCount() {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetRenderModelCount" << std::endl; });
	auto result = g_pvrrendermodels->GetRenderModelCount();
  getOut() << "get render model count " << result << std::endl;
  return result;
}

uint32_t BaseRenderModels::GetComponentCount(const char * pchRenderModelName) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentCount" << std::endl; });
  // return 0; // XXX
	return g_pvrrendermodels->GetComponentCount(pchRenderModelName);
}

uint32_t BaseRenderModels::GetComponentName(const char * pchRenderModelName, uint32_t unComponentIndex,
	  char * pchComponentName, uint32_t unComponentNameLen) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentName" << std::endl; });
  return g_pvrrendermodels->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
}

uint64_t BaseRenderModels::GetComponentButtonMask(const char * pchRenderModelName, const char * pchComponentName) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentButtonMask" << std::endl; });
	auto result = g_pvrrendermodels->GetComponentButtonMask(pchRenderModelName, pchComponentName);
  getOut() << "GetComponentButtonMask result " << (void *)result << std::endl;
  return result;
}

uint32_t BaseRenderModels::GetComponentRenderModelName(const char * pchRenderModelName, const char * pchComponentName,
	  char * componentModelName, uint32_t componentModelNameLen) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentRenderModelName" << std::endl; });
  return g_pvrrendermodels->GetComponentRenderModelName(pchRenderModelName, pchComponentName, componentModelName, componentModelNameLen);
}

bool BaseRenderModels::GetComponentStateForDevicePath(const char *pchRenderModelName, const char *pchComponentName,
    vr::VRInputValueHandle_t devicePath, const vr::RenderModel_ControllerMode_State_t *pState,
    vr::RenderModel_ComponentState_t *pComponentState) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentStateForDevicePath" << std::endl; });
  auto result = g_pvrrendermodels->GetComponentStateForDevicePath(pchRenderModelName, pchComponentName, devicePath, pState, pComponentState);
  getOut() << "get component state tracking " << pchRenderModelName << " " << pchComponentName << " " << result << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[0][0] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[0][1] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[0][2] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[0][3] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[1][0] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[1][1] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[1][2] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[1][3] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[2][0] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[2][1] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[2][2] << " " <<
    pComponentState->mTrackingToComponentRenderModel.m[2][3] << " " <<
    std::endl;
  return result;
}

bool BaseRenderModels::GetComponentState(const char * pchRenderModelName, const char * pchComponentName,
    const vr::VRControllerState_t * pControllerState,const vr::RenderModel_ControllerMode_State_t * pState,
    vr::RenderModel_ComponentState_t * pComponentState) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetComponentState" << std::endl; });
	return g_pvrrendermodels->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState);
}

bool BaseRenderModels::RenderModelHasComponent(const char * pchRenderModelName, const char * pchComponentName) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::RenderModelHasComponent" << std::endl; });
	return g_pvrrendermodels->RenderModelHasComponent(pchRenderModelName, pchComponentName);
}

uint32_t BaseRenderModels::GetRenderModelThumbnailURL(const char * pchRenderModelName, VR_OUT_STRING() char * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetRenderModelThumbnailURL" << std::endl; });
	return g_pvrrendermodels->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
}

uint32_t BaseRenderModels::GetRenderModelOriginalPath(const char * pchRenderModelName, VR_OUT_STRING() char * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetRenderModelOriginalPath" << std::endl; });
	return g_pvrrendermodels->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
}

const char * BaseRenderModels::GetRenderModelErrorNameFromEnum(EVRRenderModelError error) {
  TRACE("BaseRenderModels", []() { getOut() << "BaseRenderModels::GetRenderModelErrorNameFromEnum" << std::endl; });
  return g_pvrrendermodels->GetRenderModelErrorNameFromEnum(error);
}
