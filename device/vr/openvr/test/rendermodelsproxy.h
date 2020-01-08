#ifndef _openvr_rendermodelsproxy_h_
#define _openvr_rendermodelsproxy_h_

// #include <deque>

#include <D3D11_4.h>
#include <DXGI1_4.h>
#include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRRenderModels : public IVRRenderModels {
public:
  IVRRenderModels *vrrendermodels;
  FnProxy &fnp;

  PVRRenderModels(IVRRenderModels *vrrendermodels, FnProxy &fnp);
	virtual vr::EVRRenderModelError LoadRenderModel_Async(const char *pchRenderModelName, vr::RenderModel_t **ppRenderModel);
  virtual void FreeRenderModel(vr::RenderModel_t *pRenderModel);
  virtual vr::EVRRenderModelError LoadTexture_Async(vr::TextureID_t textureId, vr::RenderModel_TextureMap_t **ppTexture);
  virtual void FreeTexture(vr::RenderModel_TextureMap_t *pTexture);
  virtual vr::EVRRenderModelError LoadTextureD3D11_Async(vr::TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D);
  virtual vr::EVRRenderModelError LoadIntoTextureD3D11_Async(vr::TextureID_t textureId, void *pDstTexture);
  virtual void FreeTextureD3D11(void *pD3D11Texture2D);
  virtual uint32_t GetRenderModelName(uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen);
  virtual uint32_t GetRenderModelCount();
  virtual uint32_t GetComponentCount(const char *pchRenderModelName);
  virtual uint32_t GetComponentName(const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING() char *pchComponentName, uint32_t unComponentNameLen);
  virtual uint64_t GetComponentButtonMask(const char *pchRenderModelName, const char *pchComponentName);
  virtual uint32_t GetComponentRenderModelName(const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING() char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
  virtual bool GetComponentStateForDevicePath(const char *pchRenderModelName, const char *pchComponentName, vr::VRInputValueHandle_t devicePath, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState);
  virtual bool GetComponentState(const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const vr::RenderModel_ControllerMode_State_t *pState, vr::RenderModel_ComponentState_t *pComponentState);
  virtual bool RenderModelHasComponent(const char *pchRenderModelName, const char *pchComponentName);
  virtual uint32_t GetRenderModelThumbnailURL(const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError);
  virtual uint32_t GetRenderModelOriginalPath(const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError);
  virtual const char *GetRenderModelErrorNameFromEnum(vr::EVRRenderModelError error);
};
}

#endif