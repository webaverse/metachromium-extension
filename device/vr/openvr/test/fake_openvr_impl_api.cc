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

#include "device/vr/openvr/test/test_helper.h"
#include "device/vr/test/test_hook.h"
#include "device/vr/windows/d3d11_device_helpers.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "third_party/openvr/src/src/ivrclientcore.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"

#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/sample/hellovr_opengl_main.h"
#include "device/vr/OpenOVR/Reimpl/static_bases.gen.h"
std::ofstream out;
std::ofstream &getOut() {
  if (!out.is_open()) {
    out.open("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\log\\log.txt", std::ofstream::out|std::ofstream::app|std::ofstream::binary);
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
      void *pMod = SharedLib_Load("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\third_party\\openvr\\src\\bin\\win64\\openvr_api.dll");
      // dumpbin /exports "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\vrclient_x64.dll"
      // nothing more to do if we can't load the DLL
      getOut() << "core 3 " << pMod << std::endl;
      if( !pMod )
      {
        abort();
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
        abort();
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
  
BOOL WINAPI DllMain(
  _In_ HINSTANCE hinstDLL,
  _In_ DWORD     fdwReason,
  _In_ LPVOID    lpvReserved
) {
  getOut() << "init dll 0" << std::endl;
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  getOut() << "init dll 1 " << buf.data() << std::endl;
  getOut() << "init dll 2 " << buf.data() << std::endl;
  return true;
}