#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/IVRCompositor_012.h"
#include "OpenVR/interfaces/IVRCompositor_013.h"
#include "OpenVR/interfaces/IVRCompositor_014.h"
#include "OpenVR/interfaces/IVRCompositor_015.h"
#include "OpenVR/interfaces/IVRCompositor_016.h"
#include "OpenVR/custom_interfaces/IVRCompositor_017.h"
#include "OpenVR/interfaces/IVRCompositor_018.h"
#include "OpenVR/interfaces/IVRCompositor_019.h"
#include "OpenVR/interfaces/IVRCompositor_020.h"
#include "OpenVR/interfaces/IVRCompositor_021.h"
#include "OpenVR/interfaces/IVRCompositor_022.h"
#include "BaseCompositor.h"
class CVRCompositor_012 : public vr::IVRCompositor_012::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_012();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_012::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_012::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_012::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_012::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_012::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	float GetFrameTimeRemaining();
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_012::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
};
#include "BaseCompositor.h"
class CVRCompositor_013 : public vr::IVRCompositor_013::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_013();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_013::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_013::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_013::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_013::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_013::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	float GetFrameTimeRemaining();
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_013::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
};
#include "BaseCompositor.h"
class CVRCompositor_014 : public vr::IVRCompositor_014::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_014();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_014::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_014::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_014::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_014::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_014::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	float GetFrameTimeRemaining();
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_014::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
};
#include "BaseCompositor.h"
class CVRCompositor_015 : public vr::IVRCompositor_015::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_015();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_015::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_015::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_015::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_015::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_015::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_015::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_015::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_015::EVRCompositorError RequestScreenshot(vr::EVRScreenshotType type, const char* pchDestinationFileName, const char* pchVRDestinationFileName);
	vr::EVRScreenshotType GetCurrentScreenshotType();
	vr::IVRCompositor_015::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	vr::IVRCompositor_015::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
};
#include "BaseCompositor.h"
class CVRCompositor_016 : public vr::IVRCompositor_016::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_016();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_016::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_016::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_016::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_016::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_016::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_016::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_016::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_016::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	vr::IVRCompositor_016::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
};
#include "BaseCompositor.h"
class CVRCompositor_017 : public vr::IVRCompositor_017::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_017();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_017::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_017::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_017::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_017::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::IVRCompositor_017::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_017::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	vr::IVRCompositor_017::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_017::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	vr::IVRCompositor_017::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
};
#include "BaseCompositor.h"
class CVRCompositor_018 : public vr::IVRCompositor_018::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_018();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_018::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_018::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_018::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_018::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::IVRCompositor_018::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_018::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	float GetCurrentGridAlpha();
	vr::IVRCompositor_018::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_018::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	vr::IVRCompositor_018::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
};
#include "BaseCompositor.h"
class CVRCompositor_019 : public vr::IVRCompositor_019::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_019();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_019::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_019::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_019::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_019::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::IVRCompositor_019::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_019::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	float GetCurrentGridAlpha();
	vr::IVRCompositor_019::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_019::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	vr::IVRCompositor_019::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize);
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize);
};
#include "BaseCompositor.h"
class CVRCompositor_020 : public vr::IVRCompositor_020::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_020();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_020::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_020::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_020::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_020::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::IVRCompositor_020::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_020::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	float GetCurrentGridAlpha();
	vr::IVRCompositor_020::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_020::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView);
	vr::IVRCompositor_020::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize);
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize);
};
#include "BaseCompositor.h"
class CVRCompositor_021 : public vr::IVRCompositor_021::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_021();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_021::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_021::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_021::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_021::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::IVRCompositor_021::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_021::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	float GetCurrentGridAlpha();
	vr::IVRCompositor_021::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_021::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView);
	vr::IVRCompositor_021::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize);
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize);
	void SetExplicitTimingMode(bool bExplicitTimingMode);
	vr::IVRCompositor_021::EVRCompositorError SubmitExplicitTimingData();
};
#include "BaseCompositor.h"
class CVRCompositor_022 : public vr::IVRCompositor_022::IVRCompositor, public CVRCommon {
private:
	const std::shared_ptr<BaseCompositor> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRCompositor_022();
	// Interface methods:
	void SetTrackingSpace(vr::ETrackingUniverseOrigin eOrigin);
	vr::ETrackingUniverseOrigin GetTrackingSpace();
	vr::IVRCompositor_022::EVRCompositorError WaitGetPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_022::EVRCompositorError GetLastPoses(vr::TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount, vr::TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount);
	vr::IVRCompositor_022::EVRCompositorError GetLastPoseForTrackedDeviceIndex(vr::TrackedDeviceIndex_t unDeviceIndex, vr::TrackedDevicePose_t* pOutputPose, vr::TrackedDevicePose_t* pOutputGamePose);
	vr::IVRCompositor_022::EVRCompositorError Submit(vr::EVREye eEye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds, vr::EVRSubmitFlags nSubmitFlags);
	void ClearLastSubmittedFrame();
	void PostPresentHandoff();
	bool GetFrameTiming(vr::Compositor_FrameTiming* pTiming, uint32_t unFramesAgo);
	uint32_t GetFrameTimings(vr::Compositor_FrameTiming* pTiming, uint32_t nFrames);
	float GetFrameTimeRemaining();
	void GetCumulativeStats(vr::IVRCompositor_022::Compositor_CumulativeStats* pStats, uint32_t nStatsSizeInBytes);
	void FadeToColor(float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
	vr::HmdColor_t GetCurrentFadeColor(bool bBackground);
	void FadeGrid(float fSeconds, bool bFadeIn);
	float GetCurrentGridAlpha();
	vr::IVRCompositor_022::EVRCompositorError SetSkyboxOverride(const vr::Texture_t* pTextures, uint32_t unTextureCount);
	void ClearSkyboxOverride();
	void CompositorBringToFront();
	void CompositorGoToBack();
	void CompositorQuit();
	bool IsFullscreen();
	uint32_t GetCurrentSceneFocusProcess();
	uint32_t GetLastFrameRenderer();
	bool CanRenderScene();
	void ShowMirrorWindow();
	void HideMirrorWindow();
	bool IsMirrorWindowVisible();
	void CompositorDumpImages();
	bool ShouldAppRenderWithLowResources();
	void ForceInterleavedReprojectionOn(bool bOverride);
	void ForceReconnectProcess();
	void SuspendRendering(bool bSuspend);
	vr::IVRCompositor_022::EVRCompositorError GetMirrorTextureD3D11(vr::EVREye eEye, void* pD3D11DeviceOrResource, void** ppD3D11ShaderResourceView);
	void ReleaseMirrorTextureD3D11(void* pD3D11ShaderResourceView);
	vr::IVRCompositor_022::EVRCompositorError GetMirrorTextureGL(vr::EVREye eEye, vr::glUInt_t* pglTextureId, vr::glSharedTextureHandle_t* pglSharedTextureHandle);
	bool ReleaseSharedGLTexture(vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle);
	void LockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	void UnlockGLSharedTextureForAccess(vr::glSharedTextureHandle_t glSharedTextureHandle);
	uint32_t GetVulkanInstanceExtensionsRequired(char* pchValue, uint32_t unBufferSize);
	uint32_t GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T* pPhysicalDevice, char* pchValue, uint32_t unBufferSize);
	void SetExplicitTimingMode(vr::IVRCompositor_022::EVRCompositorTimingMode eTimingMode);
	vr::IVRCompositor_022::EVRCompositorError SubmitExplicitTimingData();
	bool IsMotionSmoothingEnabled();
	bool IsMotionSmoothingSupported();
	bool IsCurrentSceneFocusAppLoading();
};
