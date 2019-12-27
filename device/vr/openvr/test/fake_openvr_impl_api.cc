// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 ..
msbuild  ALL_BUILD.vcxproj

cd C:\Users\avaer\AppData\Local\Chromium\Application
set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality"

C:\Windows\System32\cmd.exe /c "set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\ && set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\ && set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\ &&  C:\Program Files (x86)\Minecraft Launcher\MinecraftLauncher.exe"
*/

#include <chrono>
#include <thread>
#include <algorithm>

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <memory>

// #include "device/vr/openvr/test/test_helper.h"
// #include "device/vr/test/test_hook.h"
#include "device/vr/windows/d3d11_device_helpers.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "third_party/openvr/src/src/ivrclientcore.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"

#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/sample/hellovr_opengl_main.h"
#include "device/vr/OpenOVR/Reimpl/static_bases.gen.h"
// #include "device/vr/openvr/test/serializer.h"
#include "device/vr/openvr/test/fnproxy.h"

std::string dllDir;
std::ofstream out;
std::ostream &getOut() {
  if (!out.is_open()) {
    std::string logPath = dllDir + "log.txt";
    out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return out;
}

void externalOpenVr(std::function<void()> &&fn) {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  SetEnvironmentVariable("VR_OVERRIDE", "");

  fn();

  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
}

namespace vr {

vr::IVRSystem *g_vrsystem = nullptr;
vr::IVRCompositor *g_vrcompositor = nullptr;
vr::IVRChaperone *g_vrchaperone = nullptr;
vr::IVRChaperoneSetup *g_vrchaperonesetup = nullptr;
vr::IVROverlay *g_vroverlay = nullptr;
vr::IVRRenderModels *vr::g_vrrendermodels = nullptr;
vr::IVRScreenshots *vr::g_vrscreenshots = nullptr;
vr::IVRSettings *vr::g_vrsettings = nullptr;
vr::IVRExtendedDisplay *vr::g_vrextendeddisplay = nullptr;
vr::IVRApplications *vr::g_vrapplications = nullptr;
vr::IVRInput *g_vrinput = nullptr;

char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";
char kIVRCompositor_GetTrackingSpace[] = "IVRCompositor::GetTrackingSpace";
char kIVRCompositor_WaitGetPoses[] = "IVRCompositor::WaitGetPoses";
char kIVRCompositor_GetLastPoses[] = "IVRCompositor::GetLastPoses";
char kIVRCompositor_GetLastPoseForTrackedDeviceIndex[] = "IVRCompositor::GetLastPoseForTrackedDeviceIndex";
char kIVRCompositor_Submit[] = "IVRCompositor::Submit";
char kIVRCompositor_ClearLastSubmittedFrame[] = "IVRCompositor::ClearLastSubmittedFrame";
char kIVRCompositor_PostPresentHandoff[] = "IVRCompositor::PostPresentHandoff";
char kIVRCompositor_GetFrameTiming[] = "IVRCompositor::GetFrameTiming";
char kIVRCompositor_GetFrameTimings[] = "IVRCompositor::GetFrameTimings";
char kIVRCompositor_GetFrameTimeRemaining[] = "IVRCompositor::GetFrameTimeRemaining";
class PVRCompositor /*: IVRCompositor*/ {
public:
  IVRCompositor *vrcompositor;
  FnProxy &fnp;
  PVRCompositor(IVRCompositor *vrcompositor, FnProxy &fnp) : vrcompositor(vrcompositor), fnp(fnp) {
    fnp.reg<
      kIVRCompositor_SetTrackingSpace,
      int,
      ETrackingUniverseOrigin
    >([=](ETrackingUniverseOrigin eOrigin) {
      vrcompositor->SetTrackingSpace(eOrigin);
      return 0;
    });
    fnp.reg<
      kIVRCompositor_GetTrackingSpace,
      ETrackingUniverseOrigin
    >([=]() {
      return vrcompositor->GetTrackingSpace();
    });
    fnp.reg<
      kIVRCompositor_WaitGetPoses,
      std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
      uint32_t,
      uint32_t
    >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
      zpp::serializer::managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
      zpp::serializer::managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

      EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

      return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
        error,
        std::move(renderPoseArray),
        std::move(gamePoseArray)
      );
    });
    fnp.reg<
      kIVRCompositor_GetLastPoses,
      std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
      uint32_t,
      uint32_t
    >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
      zpp::serializer::managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
      zpp::serializer::managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

      EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

      return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
        error,
        std::move(renderPoseArray),
        std::move(gamePoseArray)
      );
    });
    fnp.reg<
      kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
      std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>,
      TrackedDeviceIndex_t
    >([=](TrackedDeviceIndex_t unDeviceIndex) {
      zpp::serializer::managed_binary<TrackedDevicePose_t> outputPose(1);
      zpp::serializer::managed_binary<TrackedDevicePose_t> gamePose(1);

      EVRCompositorError error = vrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, outputPose.data(), gamePose.data());

      return std::tuple<EVRCompositorError, zpp::serializer::managed_binary<TrackedDevicePose_t>, zpp::serializer::managed_binary<TrackedDevicePose_t>>(
        error,
        std::move(outputPose),
        std::move(gamePose)
      );
    });
    fnp.reg<
      kIVRCompositor_Submit,
      int
    >([=]() {
      abort(); // XXX
      return 1;
    });
    fnp.reg<
      kIVRCompositor_ClearLastSubmittedFrame,
      int
    >([=]() {
      vrcompositor->ClearLastSubmittedFrame();
      return 0;
    });
    fnp.reg<
      kIVRCompositor_PostPresentHandoff,
      int
    >([=]() {
      vrcompositor->PostPresentHandoff();
      return 0;
    });
    fnp.reg<
      kIVRCompositor_GetFrameTiming,
      std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >([=](uint32_t unFramesAgo) {
      zpp::serializer::managed_binary<Compositor_FrameTiming> timing(1);

      bool result = vrcompositor->GetFrameTiming(timing.data(), unFramesAgo);

      return std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>(
        result,
        std::move(timing)
      );
    });
    fnp.reg<
      kIVRCompositor_GetFrameTimings,
      std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >([=](uint32_t nFrames) {
      zpp::serializer::managed_binary<Compositor_FrameTiming> timings(nFrames);

      uint32_t result = vrcompositor->GetFrameTimings(timings.data(), nFrames);

      return std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>(
        result,
        std::move(timings)
      );
    });
    fnp.reg<
      kIVRCompositor_GetFrameTimeRemaining,
      float
    >([=]() {
      return vrcompositor->GetFrameTimeRemaining();
    });
  }
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) {
    fnp.call<kIVRCompositor_SetTrackingSpace, int, ETrackingUniverseOrigin>(eOrigin);
  }
	virtual ETrackingUniverseOrigin GetTrackingSpace() {
    return fnp.call<kIVRCompositor_GetTrackingSpace, ETrackingUniverseOrigin>();
  }
	virtual EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		  VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
    auto result = fnp.call<
      kIVRCompositor_WaitGetPoses,
      std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
      uint32_t,
      uint32_t
    >(unRenderPoseArrayCount, unGamePoseArrayCount);
    memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size_in_bytes());
    memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size_in_bytes());
    return std::get<0>(result);
  }
	virtual EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
		  VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
    auto result = fnp.call<
      kIVRCompositor_GetLastPoses,
      std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
      uint32_t,
      uint32_t
    >(unRenderPoseArrayCount, unGamePoseArrayCount);
    memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size_in_bytes());
    memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size_in_bytes());
    return std::get<0>(result);
  }
	virtual EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) {
    auto result = fnp.call<
      kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
      std::tuple<EVRCompositorError, zpp::serializer::binary<TrackedDevicePose_t>, zpp::serializer::binary<TrackedDevicePose_t>>,
      TrackedDeviceIndex_t
    >(unDeviceIndex);
    *pOutputPose = *std::get<1>(result).data();
    *pOutputGamePose = *std::get<2>(result).data();
    return std::get<0>(result);
  }
	virtual EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) {
    fnp.call<
      kIVRCompositor_Submit,
      int
    >();
    abort(); // XXX
    return VRCompositorError_None;
  }
	virtual void ClearLastSubmittedFrame() {
    fnp.call<
      kIVRCompositor_ClearLastSubmittedFrame,
      int
    >();
  }
	virtual void PostPresentHandoff() {
    fnp.call<
      kIVRCompositor_PostPresentHandoff,
      int
    >();
  }
	virtual bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) {
    auto result = fnp.call<
      kIVRCompositor_GetFrameTiming,
      std::tuple<bool, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >(unFramesAgo);
    *pTiming = *std::get<1>(result).data();
    return std::get<0>(result);
  }
	virtual uint32_t GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
    auto result = fnp.call<
      kIVRCompositor_GetFrameTimings,
      std::tuple<uint32_t, zpp::serializer::managed_binary<Compositor_FrameTiming>>,
      uint32_t
    >(nFrames);
    *pTiming = *std::get<1>(result).data();
    return std::get<0>(result);
  }
	virtual float GetFrameTimeRemaining() {
    return fnp.call<
      kIVRCompositor_GetFrameTimeRemaining,
      float
    >();
  }
	/* virtual void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) = 0;
	virtual void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) = 0;
	virtual HmdColor_t GetCurrentFadeColor( bool bBackground = false ) = 0;
	virtual void FadeGrid( float fSeconds, bool bFadeIn ) = 0;
	virtual float GetCurrentGridAlpha() = 0;
	virtual EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) = 0;
	virtual void ClearSkyboxOverride() = 0;
	virtual void CompositorBringToFront() = 0;
	virtual void CompositorGoToBack() = 0;
	virtual void CompositorQuit() = 0;
	virtual bool IsFullscreen() = 0;
	virtual uint32_t GetCurrentSceneFocusProcess() = 0;
	virtual uint32_t GetLastFrameRenderer() = 0;
	virtual bool CanRenderScene() = 0;
	virtual void ShowMirrorWindow() = 0;
	virtual void HideMirrorWindow() = 0;
	virtual bool IsMirrorWindowVisible() = 0;
	virtual void CompositorDumpImages() = 0;
	virtual bool ShouldAppRenderWithLowResources() = 0;
	virtual void ForceInterleavedReprojectionOn( bool bOverride ) = 0;
	virtual void ForceReconnectProcess() = 0;
	virtual void SuspendRendering( bool bSuspend ) = 0;
	virtual vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) = 0;
	virtual void ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) = 0;
	virtual vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) = 0;
	virtual bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	virtual void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	virtual void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) = 0;
	virtual uint32_t GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
	virtual uint32_t GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) = 0;
	virtual void SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) = 0;
	virtual EVRCompositorError SubmitExplicitTimingData() = 0;
	virtual bool IsMotionSmoothingEnabled() = 0;
	virtual bool IsMotionSmoothingSupported() = 0;
	virtual bool IsCurrentSceneFocusAppLoading() = 0; */
};

}  // namespace vr

extern "C" {
  void *__imp_VR_GetGenericInterface = nullptr;
  void *__imp_VR_IsInterfaceVersionVersion = nullptr;
  void *__imp_VR_GetInitToken = nullptr;
  void *__imp_VR_IsInterfaceVersion = nullptr;
  void *__imp_VR_InitInternal2 = nullptr;
  void *__imp_VR_IsInterfaceVersionValid = nullptr;
  void *__imp_VR_ShutdownInternal = nullptr;
  void *__imp_VR_IsHmdPresent = nullptr;
  void *__imp_VR_GetVRInitErrorAsSymbol = nullptr;
  void *__imp_VR_GetVRInitErrorAsEnglishDescription = nullptr;
  
  __declspec(dllexport) void* VRClientCoreFactory(const char* interface_name, int* return_code) {
    getOut() << "core 0 " << std::endl;
    getOut() << "core 1 " << interface_name << std::endl;
    externalOpenVr([&]() -> void {
      vr::EVRInitError result = vr::VRInitError_None;

      getOut() << "core 2 " << interface_name << std::endl;

      // only look in the override
      std::string openvrApiDllPath = dllDir + "openvr_api.dll";
      void *pMod = SharedLib_Load(openvrApiDllPath.c_str());
      // dumpbin /exports "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\vrclient_x64.dll"
      // nothing more to do if we can't load the DLL
      getOut() << "core 3 " << pMod << std::endl;
      if( !pMod )
      {
        getOut() << "core abort" << std::endl; abort();
        // return vr::VRInitError_Init_VRClientDLLNotFound;
      }
      
      getOut() << "core 4 " << pMod << std::endl;

      __imp_VR_GetGenericInterface = SharedLib_GetFunction( pMod, "VR_GetGenericInterface" );
      __imp_VR_IsInterfaceVersionVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionVersion" );
      __imp_VR_GetInitToken = SharedLib_GetFunction( pMod, "VR_GetInitToken" );
      __imp_VR_IsInterfaceVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersion" );
      __imp_VR_InitInternal2 = SharedLib_GetFunction( pMod, "VR_InitInternal2" );
      __imp_VR_IsInterfaceVersionValid = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionValid" );
      __imp_VR_ShutdownInternal = SharedLib_GetFunction( pMod, "VR_ShutdownInternal" );
      __imp_VR_IsHmdPresent = SharedLib_GetFunction( pMod, "VR_IsHmdPresent" );
      __imp_VR_GetVRInitErrorAsSymbol = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsSymbol" );
      __imp_VR_GetVRInitErrorAsEnglishDescription = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsEnglishDescription" );
      getOut() << "core 5 " << pMod << " " << __imp_VR_GetGenericInterface << std::endl;
      if( !__imp_VR_GetGenericInterface )
      {
        SharedLib_Unload( pMod );
        getOut() << "unload abort" << std::endl; abort();
        // return vr::VRInitError_Init_FactoryNotFound;
      }
      
      getOut() << "core 6 " << pMod << " " << __imp_VR_GetGenericInterface << std::endl;

      /* int nReturnCode = 0;
      g_pHmdSystem = static_cast< IVRClientCore * > ( fnFactory( vr::IVRClientCore_Version, &nReturnCode ) );
      if( !g_pHmdSystem )
      {
        SharedLib_Unload( pMod );
        return vr::VRInitError_Init_InterfaceNotFound;
      } */
      
      vr::VR_Init(&result, vr::VRApplication_Scene);
      if (result == vr::VRInitError_None) {
        getOut() << "init 2" << std::endl;
        vr::g_vrsystem = vr::VRSystem();
        vr::g_vrcompositor = vr::VRCompositor();
        vr::g_vrchaperone = vr::VRChaperone();
        vr::g_vrchaperonesetup = vr::VRChaperoneSetup();
        vr::g_vroverlay = vr::VROverlay();
        vr::g_vrrendermodels = vr::VRRenderModels();
        vr::g_vrscreenshots = vr::VRScreenshots();
        vr::g_vrsettings = vr::VRSettings();
        vr::g_vrextendeddisplay = vr::VRExtendedDisplay();
        vr::g_vrapplications = vr::VRApplications();
        vr::g_vrinput = vr::VRInput();
        result = vr::VRInitError_None;
        getOut() << "init 3" << std::endl;
      } else {
        getOut() << "init 4" << std::endl;
        // vr::VR_Shutdown();
        // getOut() << "init 4" << std::endl;
        result = vr::VRInitError_Unknown;
      }
      getOut() << "init 5" << std::endl;
    });
    getOut() << "init 6 " << interface_name << std::endl;
    void *iface = CreateInterfaceByName(interface_name);
    getOut() << "init 7 " << interface_name << " " << iface << std::endl;
    return iface;
  }
}

/* TCHAR processExe[4096] = TEXT("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\process.exe");
char lol[] = "lol";
char lol2[] = "lol2"; */
BOOL WINAPI DllMain(
  _In_ HINSTANCE hinstDLL,
  _In_ DWORD     fdwReason,
  _In_ LPVOID    lpvReserved
) {
  { 
    // getOut() << "loading paths" << std::endl;
    char dllPath[MAX_PATH];
    HMODULE hm = NULL;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR) &VRClientCoreFactory, &hm) == 0)
    {
        int ret = GetLastError();
        // getOut() << "GetModuleHandle failed, error = " << ret << std::endl;
        // Return or however you want to handle an error.
        getOut() << "dll abort 1" << std::endl; abort();
    }
    if (GetModuleFileName(hm, dllPath, sizeof(dllPath)) == 0)
    {
        int ret = GetLastError();
        // getOut() << "GetModuleFileName failed, error = " << ret << std::endl;
        getOut() << "dll abort 2" << std::endl; abort();
    }
    
    char drive[MAX_PATH];
    char dir[MAX_PATH];
    // char fname[MAX_PATH];
    // char ext[MAX_PATH];
    _splitpath(dllPath, drive, dir, nullptr, nullptr);
    dllDir = drive;
    dllDir += dir;
  }
  
  getOut() << "init dll 0" << std::endl;
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  getOut() << "init dll 1 " << buf.data() << std::endl;
  getOut() << "init dll 2 " << buf.data() << std::endl;
  
  return true;
}