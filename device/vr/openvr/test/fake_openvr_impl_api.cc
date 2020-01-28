// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release ALL_BUILD.vcxproj
msbuild /p:Configuration=Release /t:Clean ALL_BUILD.vcxproj

cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin

set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\
set PATH=%PATH%;C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin

VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\; VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\; VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\;

cd C:\Users\avaer\AppData\Local\Chromium\Application
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality" --no-sandbox --test-type --disable-xr-device-consent-prompt-for-testing

--app --disable-xr-device-consent-prompt-for-testing --no-sandbox --add-gpu-appcontainer-caps --add-xr-appcontainer-caps --xr_compositing --allow-third-party-modules --allow-unsecure-dlls --allow-sandbox-debugging --gpu-launcher="C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin\process2.exe"

--gpu-launcher --no-startup-window --gpu-startup-dialog

cd C:\Program Files (x86)\Steam\steamapps\common\Space Pirate Trainer VR
.\SpacePirateVR.exe

cd C:\Program Files (x86)\Steam\steamapps\common\VRChat
.\VRChat.exe

cd C:\Program Files (x86)\Steam\steamapps\common\Blocks
.\Blocks.exe

cd C:\Program Files (x86)\obs-studio\data\obs-plugins\win-capture
.\get-graphics-offsets64.exe

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
#include "device/vr/openvr/test/hijack.h"

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
PVROverlay *g_pvroverlay = nullptr;
}

std::string dllDir;
std::ofstream out;
std::ostream &getOut() {
  // if (!isProcess) {
    if (!out.is_open()) {
      std::string logPath = dllDir + std::string("log") + logSuffix + std::string(".txt");
      std::cerr << "logging to: " << logPath << std::endl;
      out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
      out << "--------------------------------------------------------------------------------" << std::endl;
    }
    return out;
  /* } else {
    return std::cout;
  } */
}
/* void LocalGetDXGIOutputInfo(int32_t *pAdaterIndex) {
  vr::g_vrsystem->GetDXGIOutputInfo(pAdaterIndex);
} */
void ProxyGetDXGIOutputInfo(int32_t *pAdaterIndex) {
  vr::g_pvrsystem->GetDXGIOutputInfo(pAdaterIndex);
}
void ProxyGetRecommendedRenderTargetSize(uint32_t *pWidth, uint32_t *pHeight) {
  vr::g_pvrsystem->GetRecommendedRenderTargetSize(pWidth, pHeight);
}
void ProxyGetProjectionRaw(vr::EVREye eye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom) {
  vr::g_pvrsystem->GetProjectionRaw(eye, pfLeft, pfRight, pfTop, pfBottom);
}
float ProxyGetFloat(const char *pchSection, const char *pchSettingsKey, vr::EVRSettingsError *peError) {
  return vr::g_pvrsettings->GetFloat(pchSection, pchSettingsKey, peError);
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

FnProxy *g_fnp = nullptr;
Hijacker *g_hijacker = nullptr;
Offsets *g_offsets = nullptr;

// char p[] = "C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\process.exe";

// constexpr bool localLoop = true;
constexpr bool localLoop = false;

void *shMem = nullptr;
// bool hijacked = false;
bool booted = false;
bool isChrome = false;
// uint64_t *pFrameCount = nullptr;
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

    if (!booted) {
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
          vr::PVRSystem system(vr::g_vrsystem, *g_fnp);
          vr::PVRCompositor compositor(vr::g_vrcompositor, *g_hijacker, *g_fnp);
          vr::PVRClientCore clientcore(&compositor, *g_fnp);
          vr::PVRInput input(vr::g_vrinput, *g_fnp);
          vr::PVRScreenshots screenshots(vr::g_vrscreenshots, *g_fnp);
          vr::PVRChaperone chaperone(vr::g_vrchaperone, *g_fnp);
          vr::PVRChaperoneSetup chaperonesetup(vr::g_vrchaperonesetup, *g_fnp);
          vr::PVRSettings settings(vr::g_vrsettings, *g_fnp);
          vr::PVRRenderModels rendermodels(vr::g_vrrendermodels, *g_fnp);
          vr::PVRApplications applications(vr::g_vrapplications, *g_fnp);
          for (;;) {
            g_fnp->handle();
          }
        });
        t.detach();
      }
      
      booted = true;
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
    g_offsets = (Offsets *)shMem;
    
    char moduleFileName[MAX_PATH];
    if (!GetModuleFileName(NULL, moduleFileName, sizeof(moduleFileName))) {
      getOut() << "failed to get executable file name: " << (void *)GetLastError() << std::endl;
      abort();
    }
    std::string moduleString(moduleFileName);
    // getOut() << "exe file name: " << moduleFileName << std::endl;
    isChrome = (moduleString.find("chrome.exe") != std::string::npos);

    g_fnp = new FnProxy();
    g_hijacker = new Hijacker(*g_fnp);
    vr::g_pvrsystem = new vr::PVRSystem(vr::g_vrsystem, *g_fnp);
    vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrcompositor, *g_hijacker, *g_fnp);
    vr::g_pvrclientcore = new vr::PVRClientCore(vr::g_pvrcompositor, *g_fnp);
    vr::g_pvrinput = new vr::PVRInput(vr::g_vrinput, *g_fnp);
    vr::g_pvrscreenshots = new vr::PVRScreenshots(vr::g_vrscreenshots, *g_fnp);
    vr::g_pvrchaperone = new vr::PVRChaperone(vr::g_vrchaperone, *g_fnp);
    vr::g_pvrchaperonesetup = new vr::PVRChaperoneSetup(vr::g_vrchaperonesetup, *g_fnp);
    vr::g_pvrsettings = new vr::PVRSettings(vr::g_vrsettings, *g_fnp);
    vr::g_pvrrendermodels = new vr::PVRRenderModels(vr::g_vrrendermodels, *g_fnp);
    vr::g_pvrapplications = new vr::PVRApplications(vr::g_vrapplications, *g_fnp);
    vr::g_pvroverlay = new vr::PVROverlay(vr::g_vroverlay, *g_fnp);
    
    g_hijacker->hijackDxgi(hinstDLL);
    g_hijacker->hijackGl();

    // getOut() << "init dll 0" << std::endl;
    std::vector<char> buf(4096);
    GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
    getOut() << "init dll " << buf.data() << std::endl;
    // getOut() << "init dll 2 " << buf.data() << std::endl;
  } else if (fdwReason == DLL_PROCESS_DETACH) {
    g_hijacker->unhijackDxgi();
    g_hijacker->unhijackDx();
    g_hijacker->unhijackGl();
  }
  return true;
}