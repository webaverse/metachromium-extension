#ifndef _openvr_compositorproxy_h_
#define _openvr_compositorproxy_h_

#include <deque>

#include <D3D11_4.h>
#include <d3dcompiler.h>
#include <DXGI1_4.h>
#include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"
#include "device/vr/openvr/test/hijack.h"

namespace vr {
class PVRCompositor : public IVRCompositor {
public:
  IVRCompositor *vrcompositor;
  Hijacker &hijacker;
  FnProxy &fnp;

  // system
  TrackedDevicePose_t cachedRenderPoses[vr::k_unMaxTrackedDeviceCount];
  TrackedDevicePose_t cachedGamePoses[vr::k_unMaxTrackedDeviceCount];

  // main
  Microsoft::WRL::ComPtr<ID3D11Device5> device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext4> context;
  Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
  Microsoft::WRL::ComPtr<ID3D11InfoQueue> infoQueue;
  GLFWwindow *subWindow = nullptr;
  HANDLE hInteropDevice = NULL;
  uint32_t width = 0;
  uint32_t height = 0;
  HWND hWnd = NULL;
  DWORD chromePid = 0;
  HWND chromeHwnd = NULL;
  std::map<size_t, std::deque<std::string>> messages;

  // controls
  bool isVr = true;
  float position[3] = {0, 1.5, 0};
  float quaternion[4] = {0, 0, 0, 1};
  float scale[3] = {1, 1, 1};

  Microsoft::WRL::ComPtr<ID3D11Fence> fence;
  HANDLE fenceHandle;
  uint64_t fenceValue = 0;

  ID3D11Buffer *vertexBuffer = nullptr;
  ID3D11Buffer *indexBuffer = nullptr;
  std::vector<ID3D11Buffer *> vsConstantBuffers;
  std::vector<ID3D11Buffer *> psConstantBuffers;
  // ID3D11SamplerState *linearSampler = nullptr;
  ID3DBlob *vsBlob = nullptr;
  ID3D11VertexShader *vsShader = nullptr;
  ID3DBlob *psBlob = nullptr;
  // ID3DBlob *psCopyBlob = nullptr;
  ID3D11PixelShader *psShader = nullptr;
  // ID3D11PixelShader *psCopyShader = nullptr;
  ID3D11InputLayout *vertexLayout = nullptr;
  // ID3D11RasterizerState *rasterizerState = nullptr;
  // ID3D11ShaderResourceView *shaderResourceView = nullptr;
  // ID3D11RenderTargetView *renderTargetView = nullptr;
  // ID3D11DepthStencilView *depthStencilView = nullptr;
  // bool depthRenderEnabled = false;

  std::vector<GLuint> texLocations;
  std::vector<GLuint> depthTexLocations;
  std::vector<GLuint> hasTexLocations;
  std::vector<GLuint> texBoundsLocations;

  GLuint blitVao;
  GLuint blitProgram;

  // input front
  std::map<std::pair<size_t, EVREye>, size_t> inFrontIndices;
  std::vector<ID3D11Texture2D *> inDxTexs;
  std::vector<ID3D11ShaderResourceView *> shaderResourceViews;
  std::vector<HANDLE> inShDxShareHandles;
  std::vector<uintptr_t> inTexLatches;
  std::vector<GLuint> interopTexs;
  std::vector<HANDLE> inReadInteropHandles;
  ID3D11Fence *remoteServerFence = nullptr;

  // input back
  std::map<std::pair<size_t, EVREye>, size_t> inBackIndices;
  std::vector<ID3D11Texture2D *> inBackTexs;
  std::vector<float> inBackTextureFulls;
  std::vector<HANDLE> inBackHandleLatches;
  std::vector<ID3D11Fence *> inBackFences;
  std::deque<HANDLE> surfaceShHandles;
  std::deque<std::pair<HANDLE, D3D11_TEXTURE2D_DESC>> surfaceBindQueue;

  // output
  std::vector<ID3D11Texture2D *> shTexOuts;
  std::vector<HANDLE> shTexOutHandles;
  std::vector<ID3D11RenderTargetView *> renderTargetViews;

  // callbacks
  std::vector<std::function<void(ID3D11Device5 *, ID3D11DeviceContext4 *, ID3D11Texture2D *)>> submitCallbacks;

  PVRCompositor(IVRCompositor *vrcompositor, Hijacker &hijacker, bool isProcess, FnProxy &fnp);
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin );
	virtual ETrackingUniverseOrigin GetTrackingSpace();
	virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount );
	virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount );
	virtual void GetCachedLastPoses(VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
  virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose );
	virtual void PrepareSubmit(const Texture_t *pTexture);
  virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default );
  virtual EVRCompositorError SubmitFrame( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default );
  virtual void FlushSubmit();
	virtual void ClearLastSubmittedFrame();
	virtual void PostPresentHandoff();
	virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 );
	virtual uint32_t GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames );
	virtual float GetFrameTimeRemaining();
	virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes );
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false );
	virtual HmdColor_t GetCurrentFadeColor( bool bBackground = false );
	virtual void FadeGrid( float fSeconds, bool bFadeIn );
	virtual float GetCurrentGridAlpha();
	virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount );
	virtual void ClearSkyboxOverride();
	virtual void CompositorBringToFront();
	virtual void CompositorGoToBack();
	virtual void CompositorQuit();
	virtual bool IsFullscreen();
	virtual uint32_t GetCurrentSceneFocusProcess();
  virtual uint32_t GetLastFrameRenderer();
	virtual bool CanRenderScene();
	virtual void ShowMirrorWindow();
	virtual void HideMirrorWindow();
	virtual bool IsMirrorWindowVisible();
	virtual void CompositorDumpImages();
	virtual bool ShouldAppRenderWithLowResources();
	virtual void ForceInterleavedReprojectionOn( bool bOverride );
	virtual void ForceReconnectProcess();
	virtual void SuspendRendering( bool bSuspend );
	virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView );
	virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView );
	virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle );
	virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle );
	virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle );
	virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle );
	virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize );
	virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize );
	virtual void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode );
	virtual EVRCompositorError SubmitExplicitTimingData();
	virtual bool IsMotionSmoothingEnabled();
	virtual bool IsMotionSmoothingSupported();
	virtual bool IsCurrentSceneFocusAppLoading();
  
  void CacheWaitGetPoses();
  HmdMatrix34_t GetViewMatrix();
  HmdMatrix34_t GetStageMatrix();
  HmdMatrix44_t GetProjectionMatrix();
  void InitShader();
  void InfoQueueLog();
  static void InfoQueueLog(ID3D11InfoQueue *infoQueue);
  static void CreateDevice(ID3D11Device5 **device, ID3D11DeviceContext4 **context, IDXGISwapChain **swapChain);
  void HomeRenderLoop();
};
}

#endif