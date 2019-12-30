#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRRenderModels_004.h"
#include "OpenVR/interfaces/IVRRenderModels_005.h"
#include "OpenVR/interfaces/IVRRenderModels_006.h"
#include "BaseRenderModels.h"
class CVRRenderModels_004 : public vr::IVRRenderModels_004::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRRenderModels_004();
	// Interface methods:
	vr::IVRRenderModels_004::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_004::RenderModel_t** ppRenderModel);
	void FreeRenderModel(vr::IVRRenderModels_004::RenderModel_t* pRenderModel);
	vr::IVRRenderModels_004::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_004::TextureID_t textureId, vr::IVRRenderModels_004::RenderModel_TextureMap_t** ppTexture);
	void FreeTexture(vr::IVRRenderModels_004::RenderModel_TextureMap_t* pTexture);
	vr::IVRRenderModels_004::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_004::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D);
	void FreeTextureD3D11(void* pD3D11Texture2D);
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t GetRenderModelCount();
	uint32_t GetComponentCount(const char* pchRenderModelName);
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen);
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName);
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_004::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_004::RenderModel_ComponentState_t* pComponentState);
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName);
};
#include "BaseRenderModels.h"
class CVRRenderModels_005 : public vr::IVRRenderModels_005::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRRenderModels_005();
	// Interface methods:
	vr::IVRRenderModels_005::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_005::RenderModel_t** ppRenderModel);
	void FreeRenderModel(vr::IVRRenderModels_005::RenderModel_t* pRenderModel);
	vr::IVRRenderModels_005::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_005::TextureID_t textureId, vr::IVRRenderModels_005::RenderModel_TextureMap_t** ppTexture);
	void FreeTexture(vr::IVRRenderModels_005::RenderModel_TextureMap_t* pTexture);
	vr::IVRRenderModels_005::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D);
	vr::IVRRenderModels_005::EVRRenderModelError LoadIntoTextureD3D11_Async(vr::IVRRenderModels_005::TextureID_t textureId, void* pDstTexture);
	void FreeTextureD3D11(void* pD3D11Texture2D);
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t GetRenderModelCount();
	uint32_t GetComponentCount(const char* pchRenderModelName);
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen);
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName);
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_005::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_005::RenderModel_ComponentState_t* pComponentState);
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName);
	uint32_t GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_005::EVRRenderModelError* peError);
	uint32_t GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_005::EVRRenderModelError* peError);
	const char* GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_005::EVRRenderModelError error);
};
#include "BaseRenderModels.h"
class CVRRenderModels_006 : public vr::IVRRenderModels_006::IVRRenderModels, public CVRCommon {
private:
	const std::shared_ptr<BaseRenderModels> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRRenderModels_006();
	// Interface methods:
	vr::IVRRenderModels_006::EVRRenderModelError LoadRenderModel_Async(const char* pchRenderModelName, vr::IVRRenderModels_006::RenderModel_t** ppRenderModel);
	void FreeRenderModel(vr::IVRRenderModels_006::RenderModel_t* pRenderModel);
	vr::IVRRenderModels_006::EVRRenderModelError LoadTexture_Async(vr::IVRRenderModels_006::TextureID_t textureId, vr::IVRRenderModels_006::RenderModel_TextureMap_t** ppTexture);
	void FreeTexture(vr::IVRRenderModels_006::RenderModel_TextureMap_t* pTexture);
	vr::IVRRenderModels_006::EVRRenderModelError LoadTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pD3D11Device, void** ppD3D11Texture2D);
	vr::IVRRenderModels_006::EVRRenderModelError LoadIntoTextureD3D11_Async(vr::IVRRenderModels_006::TextureID_t textureId, void* pDstTexture);
	void FreeTextureD3D11(void* pD3D11Texture2D);
	uint32_t GetRenderModelName(uint32_t unRenderModelIndex, char* pchRenderModelName, uint32_t unRenderModelNameLen);
	uint32_t GetRenderModelCount();
	uint32_t GetComponentCount(const char* pchRenderModelName);
	uint32_t GetComponentName(const char* pchRenderModelName, uint32_t unComponentIndex, char* pchComponentName, uint32_t unComponentNameLen);
	uint64_t GetComponentButtonMask(const char* pchRenderModelName, const char* pchComponentName);
	uint32_t GetComponentRenderModelName(const char* pchRenderModelName, const char* pchComponentName, char* pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
	bool GetComponentStateForDevicePath(const char* pchRenderModelName, const char* pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState);
	bool GetComponentState(const char* pchRenderModelName, const char* pchComponentName, const vr::VRControllerState_t* pControllerState, const vr::IVRRenderModels_006::RenderModel_ControllerMode_State_t* pState, vr::IVRRenderModels_006::RenderModel_ComponentState_t* pComponentState);
	bool RenderModelHasComponent(const char* pchRenderModelName, const char* pchComponentName);
	uint32_t GetRenderModelThumbnailURL(const char* pchRenderModelName, char* pchThumbnailURL, uint32_t unThumbnailURLLen, vr::IVRRenderModels_006::EVRRenderModelError* peError);
	uint32_t GetRenderModelOriginalPath(const char* pchRenderModelName, char* pchOriginalPath, uint32_t unOriginalPathLen, vr::IVRRenderModels_006::EVRRenderModelError* peError);
	const char* GetRenderModelErrorNameFromEnum(vr::IVRRenderModels_006::EVRRenderModelError error);
};
