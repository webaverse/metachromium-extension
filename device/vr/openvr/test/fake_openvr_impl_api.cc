// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
cd C:\Users\avaer\Documents\GitHub\metachromium\bin
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release ..
msbuild /p:Configuration=Release ALL_BUILD.vcxproj
msbuild /p:Configuration=Release /t:Clean ALL_BUILD.vcxproj

cd C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\bin

set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\
set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\config\
set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\log\
set PATH=%PATH%;C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\bin

VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\; VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\config\; VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\log\;

cd C:\Users\avaer\AppData\Local\Chromium\Application
.\chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality" --no-sandbox --test-type --disable-xr-device-consent-prompt-for-testing C:\Users\avaer\Documents\GitHub\metachromium\extension\index.html

--app --disable-xr-device-consent-prompt-for-testing --no-sandbox --add-gpu-appcontainer-caps --add-xr-appcontainer-caps --xr_compositing --allow-third-party-modules --allow-unsecure-dlls --allow-sandbox-debugging --gpu-launcher="C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\bin\process2.exe"

--gpu-launcher --no-startup-window --gpu-startup-dialog

cd C:\Program Files (x86)\Steam\steamapps\common\Space Pirate Trainer VR
.\SpacePirateVR.exe

cd C:\Program Files (x86)\Steam\steamapps\common\VRChat
.\VRChat.exe

cd C:\Program Files (x86)\Steam\steamapps\common\Blocks
.\Blocks.exe

cd C:\Program Files (x86)\obs-studio\data\obs-plugins\win-capture
.\get-graphics-offsets64.exe

C:\Windows\System32\cmd.exe /c "set VR_OVERRIDE=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\build\mock_vr_clients\ && set VR_CONFIG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\config\ && set VR_LOG_PATH=C:\Users\avaer\Documents\GitHub\metachromium\device\vr\log\ &&  C:\Program Files (x86)\Minecraft Launcher\MinecraftLauncher.exe"
*/

#include <iostream>
// #include <chrono>
#include <thread>
#include <memory>
#include <algorithm>
#include <filesystem>

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

QrEngine *g_pqrengine = nullptr;
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
void getChildEnvBuf(char *pEnvBuf, const std::string &baseDir) {
  LPSTR lpvEnv = GetEnvironmentStringsA();
  std::vector<std::string> vars;
  for (LPSTR lpszVariable = (LPTSTR)lpvEnv; *lpszVariable; lpszVariable++) {
    std::string var;
    while (*lpszVariable) {
      var += *lpszVariable++;
    }
    vars.push_back(std::move(var));
  }
  FreeEnvironmentStrings(lpvEnv);
  
  /* for (auto iter : vars) {
    std::string &s = iter;
    std::string s2 = s;
    for (auto &c : s2) {
      c = toupper(c);
    }
    if (s2.rfind("PATH=", 0) == 0) {
      s += ";";
      s += cwdBuf;
    }
  } */
  {
    std::string vrOverrideString = "VR_OVERRIDE=";
    vrOverrideString += std::filesystem::weakly_canonical(std::filesystem::path(baseDir)).string();
    vrOverrideString += R"EOF(\device\vr\build\mock_vr_clients\)EOF";

    bool vrOverrideFound = false;
    for (size_t i = 0; i < vars.size(); i++) {
      std::string &s = vars[i];
      std::string s2 = s;
      for (auto &c : s2) {
        c = toupper(c);
      }
      if (s2.rfind("VR_OVERRIDE=", 0) == 0) {
        s = std::move(vrOverrideString);
        vrOverrideFound = true;
        break;
      }
    }
    if (!vrOverrideFound) {
      vars.push_back(std::move(vrOverrideString));
    }
  }

  for (auto iter : vars) {
    const std::string &s = iter;
    getOut() << "write arg: " << s << std::endl;
    memcpy(pEnvBuf, s.c_str(), s.size() + 1);
    pEnvBuf += s.size() + 1;
  }
  pEnvBuf[0] = '\0';
}
size_t chromeProfileCount = 0;
HANDLE forkChrome(const std::string &startPage, bool detached) {
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  
  std::string baseDir = cwdBuf;
  baseDir += R"EOF(\..\..\..\..\..)EOF";

  std::string cmd = R"EOF(chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality" --no-sandbox --test-type --disable-xr-device-consent-prompt-for-testing --disable-background-timer-throttling --disable-renderer-backgrounding --disable-backgrounding-occluded-windows --load-extension="..\..\..\..\..\..\extension,..\..\..\..\..\..\metamask" --whitelisted-extension-id="glmgcjligejadkfhgebnplablaggjbmm" --auto-select-desktop-capture-source="Metachromium Share - Chromium")EOF";
  if (detached) {
    cmd += " --profile-directory=profile";
    cmd += std::to_string(++chromeProfileCount);
  }
  cmd += " ";
  cmd += startPage;
  std::vector<char> cmdVector(cmd.size() + 1);
  memcpy(cmdVector.data(), cmd.c_str(), cmd.size() + 1);

  getOut() << "launch chrome command: " << cmd << std::endl;
  
  char envBuf[64 * 1024];
  getChildEnvBuf(envBuf, baseDir);

  /* SECURITY_ATTRIBUTES saAttr;
  // Set the bInheritHandle flag so pipe handles are inherited. 
  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = NULL;
  //child process's STDOUT is the program output or data that child process returns
  // Create a pipe for the child process's STDOUT. 
  if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0)) {
    getOut() << "StdoutRd CreatePipe abort" << std::endl;
    abort();
  }
  // Ensure the read handle to the pipe for STDOUT is not inherited.
  if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) {
    getOut() << "Stdout SetHandleInformation abort" << std::endl;
    abort();
  }
  //child process's STDIN is the user input or data that you enter into the child process
  // Create a pipe for the child process's STDIN. 
  if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) {
    getOut() << "Stdin CreatePipe abort" << std::endl;
    abort();
  }
  // Ensure the write handle to the pipe for STDIN is not inherited. 
  if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0)) {
    getOut() << "Stdin SetHandleInformation abort" << std::endl;
    abort();
  } */

  STARTUPINFO si{};
  si.cb = sizeof(STARTUPINFO);
  /* si.hStdError = g_hChildStd_OUT_Wr;
  si.hStdOutput = g_hChildStd_OUT_Wr;
  si.hStdInput = g_hChildStd_IN_Rd;
  si.dwFlags |= STARTF_USESTDHANDLES; */

  HANDLE chromeProcessHandle;
  PROCESS_INFORMATION pi{};
  if (CreateProcessA(
    NULL,
    cmdVector.data(),
    NULL,
    NULL,
    true,
    CREATE_NO_WINDOW,
    envBuf,
    NULL,
    &si,
    &pi
  )) {
    chromeProcessHandle = pi.hProcess;
  } else {
    chromeProcessHandle = NULL;
  }
  
  return chromeProcessHandle;
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

void *shMem = nullptr;
// bool hijacked = false;
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

    // getOut() << "init 6 " << interface_name << std::endl;
    void *iface = CreateInterfaceByName(interface_name);
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
    vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrcompositor, *g_hijacker, false, *g_fnp);
    vr::g_pvrclientcore = new vr::PVRClientCore(vr::g_pvrcompositor, *g_fnp);
    vr::g_pvrinput = new vr::PVRInput(vr::g_vrinput, *g_fnp);
    vr::g_pvrscreenshots = new vr::PVRScreenshots(vr::g_vrscreenshots, *g_fnp);
    vr::g_pvrchaperone = new vr::PVRChaperone(vr::g_vrchaperone, *g_fnp);
    vr::g_pvrchaperonesetup = new vr::PVRChaperoneSetup(vr::g_vrchaperonesetup, *g_fnp);
    vr::g_pvrsettings = new vr::PVRSettings(vr::g_vrsettings, *g_fnp);
    vr::g_pvrrendermodels = new vr::PVRRenderModels(vr::g_vrrendermodels, *g_fnp);
    vr::g_pvrapplications = new vr::PVRApplications(vr::g_vrapplications, *g_fnp);
    vr::g_pvroverlay = new vr::PVROverlay(vr::g_vroverlay, *g_fnp);
    // vr::g_pqrengine = new QrEngine(vr::g_pvrcompositor, vr::g_vrsystem);
    
    /* g_hijacker->hijackDxgi(hinstDLL);
    g_hijacker->hijackGl(); */
    
    std::vector<char> buf(4096);
    GetEnvironmentVariable("VR_OVERRIDE", buf.data(), buf.size());

    getOut() << "init dll " << moduleString << " " << buf.data() << std::endl;
  } else if (fdwReason == DLL_PROCESS_DETACH) {
    /* g_hijacker->unhijackDxgi();
    g_hijacker->unhijackDx();
    g_hijacker->unhijackGl(); */

    vr::g_pvrclientcore->Cleanup();
  }
  return true;
}