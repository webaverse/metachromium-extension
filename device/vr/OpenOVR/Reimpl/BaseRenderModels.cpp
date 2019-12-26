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
  return g_vrrendermodels->LoadRenderModel_Async(pchRenderModelName, renderModel);
}

void BaseRenderModels::FreeRenderModel(RenderModel_t * renderModel) {
	return g_vrrendermodels->FreeRenderModel(renderModel);
}

EVRRenderModelError BaseRenderModels::LoadTexture_Async(TextureID_t textureId, RenderModel_TextureMap_t ** texture) {
	return g_vrrendermodels->LoadTexture_Async(textureId, texture);
}

void BaseRenderModels::FreeTexture(RenderModel_TextureMap_t * texture) {
	return g_vrrendermodels->FreeTexture(texture);
}

EVRRenderModelError BaseRenderModels::LoadTextureD3D11_Async(TextureID_t textureId, void * pD3D11Device, void ** ppD3D11Texture2D) {
	return g_vrrendermodels->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
}

EVRRenderModelError BaseRenderModels::LoadIntoTextureD3D11_Async(TextureID_t textureId, void * pDstTexture) {
	return g_vrrendermodels->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
}

void BaseRenderModels::FreeTextureD3D11(void * pD3D11Texture2D) {
	return g_vrrendermodels->FreeTextureD3D11(pD3D11Texture2D);
}

uint32_t BaseRenderModels::GetRenderModelName(uint32_t unRenderModelIndex, VR_OUT_STRING() char * pchRenderModelName, uint32_t unRenderModelNameLen) {
	return g_vrrendermodels->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
}

uint32_t BaseRenderModels::GetRenderModelCount() {
	return g_vrrendermodels->GetRenderModelCount();
}

uint32_t BaseRenderModels::GetComponentCount(const char * pchRenderModelName) {
	return g_vrrendermodels->GetComponentCount(pchRenderModelName);
}

uint32_t BaseRenderModels::GetComponentName(const char * pchRenderModelName, uint32_t unComponentIndex,
	  char * pchComponentName, uint32_t unComponentNameLen) {
  return g_vrrendermodels->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
}

uint64_t BaseRenderModels::GetComponentButtonMask(const char * pchRenderModelName, const char * pchComponentName) {
	return g_vrrendermodels->GetComponentButtonMask(pchRenderModelName, pchComponentName);
}

uint32_t BaseRenderModels::GetComponentRenderModelName(const char * pchRenderModelName, const char * pchComponentName,
	char * componentModelName, uint32_t componentModelNameLen) {
  return g_vrrendermodels->GetComponentRenderModelName(pchRenderModelName, pchComponentName, componentModelName, componentModelNameLen);
}

bool BaseRenderModels::GetComponentStateForDevicePath(const char *pchRenderModelName, const char *pchComponentName,
	vr::VRInputValueHandle_t devicePath, const vr::RenderModel_ControllerMode_State_t *pState,
	vr::RenderModel_ComponentState_t *pComponentState)
{
	return g_vrrendermodels->GetComponentStateForDevicePath(pchRenderModelName, pchComponentName, devicePath, pState, pComponentState);
}

bool BaseRenderModels::GetComponentState(const char * pchRenderModelName, const char * pchComponentName,
	const vr::VRControllerState_t * pControllerState,const vr::RenderModel_ControllerMode_State_t * pState,
	vr::RenderModel_ComponentState_t * pComponentState) {
	return g_vrrendermodels->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState);
}

bool BaseRenderModels::RenderModelHasComponent(const char * pchRenderModelName, const char * pchComponentName) {
	return g_vrrendermodels->RenderModelHasComponent(pchRenderModelName, pchComponentName);
}

uint32_t BaseRenderModels::GetRenderModelThumbnailURL(const char * pchRenderModelName, VR_OUT_STRING() char * pchThumbnailURL, uint32_t unThumbnailURLLen, EVRRenderModelError * peError) {
	return g_vrrendermodels->GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError);
}

uint32_t BaseRenderModels::GetRenderModelOriginalPath(const char * pchRenderModelName, VR_OUT_STRING() char * pchOriginalPath, uint32_t unOriginalPathLen, EVRRenderModelError * peError) {
	return g_vrrendermodels->GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError);
}

const char * BaseRenderModels::GetRenderModelErrorNameFromEnum(EVRRenderModelError error) {
  return g_vrrendermodels->GetRenderModelErrorNameFromEnum(error);
}
