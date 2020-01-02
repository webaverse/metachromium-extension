// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build
cmake -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release ALL_BUILD.vcxproj

cd C:\Users\avaer\AppData\Local\Chromium\Application
set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\log\
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality"

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
#ifndef IS_PROCESS
  if (!out.is_open()) {
    std::string logPath = dllDir + "log.txt";
    out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return out;
#else
  return std::cout;
#endif
}
constexpr bool tracing = true;
// constexpr bool tracing = false;
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
}

// char p[] = "C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\process.exe";

void *shMem = nullptr;
size_t *pBooted = nullptr;
// GLFWwindow **ppWindow;
size_t *pNumClients = nullptr;
extern "C" {
  __declspec(dllexport) void* VRClientCoreFactory(const char* interface_name, int* return_code) {
    getOut() << "get interface " << interface_name << std::endl;
    // size_t &id = *((size_t *)shMem + 1);
    // getOut() << "core 1 " << interface_name << std::endl;

    if (!vr::g_pvrclientcore) {
      FnProxy *fnp = new FnProxy();
      vr::g_pvrclientcore = new vr::PVRClientCore(*fnp);
      vr::g_pvrsystem = new vr::PVRSystem(vr::g_vrsystem, *fnp);
      vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrsystem, vr::g_vrcompositor, *fnp);
    }

    if (!*pBooted) {
      getOut() << "create process" << std::endl;
      *pBooted = 1;
      // *ppWindow = initGl();

      /* STARTUPINFO si;
      PROCESS_INFORMATION pi;
      std::string p2 = dllDir + "process.exe";
      getOut() << "starting " << p << " " << p2 << std::endl;
      auto result = CreateProcessA(
        NULL,   // No module name (use command line)
        p,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure
      );
      if (!result) {
        getOut() << "create process failed " << p << " " << GetLastError() << std::endl;
        abort();
      } */
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

  // getOut() << "dll main " << fdwReason << std::endl;

  if (fdwReason == DLL_PROCESS_ATTACH) {
    shMem = allocateShared("Local\\OpenVrProxyInit", 16);
    pBooted = (size_t *)shMem;
    // ppWindow = (GLFWwindow **)((unsigned char *)shMem + sizeof(void *));
    //  pNumClients = (size_t *)((unsigned char *)shMem + sizeof(size_t *));
    
    // getOut() << "init dll 0" << std::endl;
    std::vector<char> buf(4096);
    GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());
    getOut() << "init dll " << buf.data() << std::endl;
    // getOut() << "init dll 2 " << buf.data() << std::endl;
  }
  return true;
}