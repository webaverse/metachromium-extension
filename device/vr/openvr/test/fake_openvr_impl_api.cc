// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release ALL_BUILD.vcxproj

set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\

cd C:\Users\avaer\AppData\Local\Chromium\Application
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality"

C:\Program Files (x86)\Steam\steamapps\common\Space Pirate Trainer VR
.\SpacePirateVR.exe

C:\Windows\System32\cmd.exe /c "set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\ && set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\ && set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\ &&  C:\Program Files (x86)\Minecraft Launcher\MinecraftLauncher.exe"
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <algorithm>

#include <D3D11_1.h>
#include <DXGI1_4.h>
// #include <wrl.h>

// #include "device/vr/openvr/test/test_helper.h"
// #include "device/vr/test/test_hook.h"
// #include "device/vr/windows/d3d11_device_helpers.h"
// #include "third_party/openvr/src/headers/openvr.h"
// #include "third_party/openvr/src/src/ivrclientcore.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"

#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/glcontext.h"
// #include "device/vr/sample/hellovr_opengl_main.h"
#include "device/vr/OpenOVR/Reimpl/static_bases.gen.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/fnproxy.h"

std::string dllDir;
std::ofstream out;
std::ostream &getOut() {
  if (!isProcess) {
    if (!out.is_open()) {
      std::string logPath = dllDir + "log.txt";
      out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
      out << "--------------------------------------------------------------------------------" << std::endl;
    }
    return out;
  } else {
    return std::cout;
  }
}
// constexpr bool tracing = true;
constexpr bool tracing = false;
void TRACE(const char *module, const std::function<void()> &fn) {
  if (tracing) {
    fn();
  }
}

void wrapExternalOpenVr(std::function<void()> &&fn) {
  std::vector<char> buf(4096);
  GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
  SetEnvironmentVariable("VR_OVERRIDE", "");

  fn();

  SetEnvironmentVariable("VR_OVERRIDE", buf.data());
}

void vrShutdownInternal() {
  getOut() << "vr shutdown internal" << std::endl;
}

namespace vr {
IVRSystem *g_vrsystem = nullptr;
IVRCompositor *g_vrcompositor = nullptr;
IVRChaperone *g_vrchaperone = nullptr;
IVRChaperoneSetup *g_vrchaperonesetup = nullptr;
IVROverlay *g_vroverlay = nullptr;
IVRRenderModels *vr::g_vrrendermodels = nullptr;
IVRScreenshots *vr::g_vrscreenshots = nullptr;
IVRSettings *vr::g_vrsettings = nullptr;
IVRExtendedDisplay *vr::g_vrextendeddisplay = nullptr;
IVRApplications *vr::g_vrapplications = nullptr;
IVRInput *g_vrinput = nullptr;

PVRClientCore *g_pvrclientcore = nullptr;
PVRSystem *g_pvrsystem = nullptr;
PVRCompositor *g_pvrcompositor = nullptr;
PVRInput *g_pvrinput = nullptr;
PVRScreenshots *g_pvrscreenshots = nullptr;
PVRChaperone *g_pvrchaperone = nullptr;
PVRChaperoneSetup *g_pvrchaperonesetup = nullptr;
PVRSettings *g_pvrsettings = nullptr;
PVRRenderModels *g_pvrrendermodels = nullptr;
PVRApplications *g_pvrapplications = nullptr;
}

// char p[] = "C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\process.exe";

// constexpr bool localLoop = true;
constexpr bool localLoop = false;

void *shMem = nullptr;
uint64_t *pBooted = nullptr;
// GLFWwindow **ppWindow;
// size_t *pNumClients = nullptr;
extern "C" {
  void *__imp_VR_GetGenericInterface = nullptr;
  void *__imp_VR_IsInterfaceVersionVersion = nullptr;
  void *__imp_VR_GetInitToken = nullptr;
  void *__imp_VR_IsInterfaceVersion = nullptr;
  void *__imp_VR_InitInternal2 = nullptr;
  void *__imp_VR_IsInterfaceVersionValid = nullptr;
  void *__imp_VR_ShutdownInternal = vrShutdownInternal;
  void *__imp_VR_IsHmdPresent = nullptr;
  void *__imp_VR_GetVRInitErrorAsSymbol = nullptr;
  void *__imp_VR_GetVRInitErrorAsEnglishDescription = nullptr;
  
  __declspec(dllexport) void* VRClientCoreFactory(const char* interface_name, int* return_code) {
    getOut() << "get interface " << interface_name << std::endl;
    // size_t &id = *((size_t *)shMem + 1);
    // getOut() << "core 1 " << interface_name << std::endl;

    if (!*pBooted) {
      if (localLoop) {
        wrapExternalOpenVr([&]() -> void {
          // getOut() << "core 2 " << interface_name << std::endl;

          // only look in the override
          std::string openvrApiDllPath = dllDir + "openvr_api.dll";
          void *pMod = SharedLib_Load(openvrApiDllPath.c_str());
          // dumpbin /exports "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\vrclient_x64.dll"
          // nothing more to do if we can't load the DLL
          // getOut() << "core 3 " << pMod << std::endl;
          if( !pMod )
          {
            getOut() << "core abort" << std::endl; abort();
            abort();
            // return vr::VRInitError_Init_VRClientDLLNotFound;
          }
          
          // getOut() << "core 4 " << pMod << std::endl;

          __imp_VR_GetGenericInterface = SharedLib_GetFunction( pMod, "VR_GetGenericInterface" );
          __imp_VR_IsInterfaceVersionVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionVersion" );
          __imp_VR_GetInitToken = SharedLib_GetFunction( pMod, "VR_GetInitToken" );
          __imp_VR_IsInterfaceVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersion" );
          __imp_VR_InitInternal2 = SharedLib_GetFunction( pMod, "VR_InitInternal2" );
          __imp_VR_IsInterfaceVersionValid = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionValid" );
          // __imp_VR_ShutdownInternal = SharedLib_GetFunction( pMod, "VR_ShutdownInternal" );
          __imp_VR_IsHmdPresent = SharedLib_GetFunction( pMod, "VR_IsHmdPresent" );
          __imp_VR_GetVRInitErrorAsSymbol = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsSymbol" );
          __imp_VR_GetVRInitErrorAsEnglishDescription = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsEnglishDescription" );
          if (!__imp_VR_GetGenericInterface) {
            SharedLib_Unload( pMod );
            getOut() << "unload abort" << std::endl; abort();
            // return vr::VRInitError_Init_FactoryNotFound;
          }

          vr::EVRInitError result = vr::VRInitError_None;
          if (!*pBooted) {
            getOut() << "vr_init " << GetCurrentThreadId() << std::endl;
            vr::VR_Init(&result, vr::VRApplication_Scene);
          }
          if (result != vr::VRInitError_None) {
            getOut() << "vr_init failed" << std::endl;
            abort();
          }
          getOut() << "proxy init" << std::endl;
          
          // if (!vr::g_pvrclientcore) {
            getOut() << "boot 1" << std::endl;
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
            
            getOut() << "boot 2 " << (void *)vr::g_vrsystem << " " << (void *)vr::g_vrcompositor << std::endl;
          // }
        });
      // }

      // if (localLoop) {
        getOut() << "create thread" << std::endl;
        
        std::thread t([=]() {
          FnProxy fnp;
          vr::PVRSystem system(vr::g_vrsystem, fnp);
          vr::PVRCompositor compositor(vr::g_vrcompositor, fnp);
          vr::PVRClientCore clientcore(&compositor, fnp);
          vr::PVRInput input(vr::g_vrinput, fnp);
          vr::PVRScreenshots screenshots(vr::g_vrscreenshots, fnp);
          vr::PVRChaperone chaperone(vr::g_vrchaperone, fnp);
          vr::PVRChaperoneSetup chaperonesetup(vr::g_vrchaperonesetup, fnp);
          vr::PVRSettings settings(vr::g_vrsettings, fnp);
          vr::PVRRenderModels rendermodels(vr::g_vrrendermodels, fnp);
          vr::PVRApplications applications(vr::g_vrapplications, fnp);
          for (;;) {
            fnp.handle();
          }
        });
        t.detach();
      }
      
      *pBooted = 1;
    }
    
    if (!vr::g_pvrclientcore) {
      FnProxy *fnp = new FnProxy();
      vr::g_pvrsystem = new vr::PVRSystem(vr::g_vrsystem, *fnp);
      vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrcompositor, *fnp);
      vr::g_pvrclientcore = new vr::PVRClientCore(vr::g_pvrcompositor, *fnp);
      vr::g_pvrinput = new vr::PVRInput(vr::g_vrinput, *fnp);
      vr::g_pvrscreenshots = new vr::PVRScreenshots(vr::g_vrscreenshots, *fnp);
      vr::g_pvrchaperone = new vr::PVRChaperone(vr::g_vrchaperone, *fnp);
      vr::g_pvrchaperonesetup = new vr::PVRChaperoneSetup(vr::g_vrchaperonesetup, *fnp);
      vr::g_pvrsettings = new vr::PVRSettings(vr::g_vrsettings, *fnp);
      vr::g_pvrrendermodels = new vr::PVRRenderModels(vr::g_vrrendermodels, *fnp);
      vr::g_pvrapplications = new vr::PVRApplications(vr::g_vrapplications, *fnp);
    }

    // result = vr::VRInitError_None;
    getOut() << "init 3 " << interface_name << std::endl;

    // getOut() << "init 6 " << interface_name << std::endl;
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
  if (fdwReason == DLL_PROCESS_ATTACH) {
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

  getOut() << "dll main " << fdwReason << /*" " << DetourIsHelperProcess() << */ std::endl;

  if (fdwReason == DLL_PROCESS_ATTACH) {
    shMem = allocateShared("Local\\OpenVrProxyInit", 1024);
    pBooted = (uint64_t *)shMem;
    // ppWindow = (GLFWwindow **)((unsigned char *)shMem + sizeof(void *));
    //  pNumClients = (size_t *)((unsigned char *)shMem + sizeof(size_t *));

    /* realFn();
    getOut() << "detour 6" << std::endl; */

    // getOut() << "init dll 0" << std::endl;
    std::vector<char> buf(4096);
    GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
    getOut() << "init dll " << buf.data() << std::endl;
    // getOut() << "init dll 2 " << buf.data() << std::endl;
  }
  return true;
}