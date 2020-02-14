#include <filesystem>

#include "device/vr/openvr/test/out.h"
#include "extension/json.hpp"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/qr.h"

#include <psapi.h>
#include <dcomp.h>

using json = nlohmann::json;

std::string logSuffix = "_process";
HWND g_hWnd = NULL;
bool live = true;

decltype(D3D11CreateDeviceAndSwapChain) *RealD3D11CreateDeviceAndSwapChain = nullptr;
decltype(DCompositionCreateDevice2) *RealDCompositionCreateDevice2 = nullptr;

char kProcess_Terminate[] = "Process::Terminate";

inline uint32_t vtable_offset(HMODULE module, void *cls, unsigned int offset) {
	uintptr_t *vtable = *(uintptr_t **)cls;
	return (uint32_t)(vtable[offset] - (uintptr_t)module);
}

HANDLE chromeProcessHandle = NULL;

void terminateProcesses(const std::vector<const char *> &candidateFilenames) {
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  std::string cwdBufString(cwdBuf);
  
  DWORD aProcesses[1024], cbNeeded, cProcesses;
  if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
    cProcesses = cbNeeded / sizeof(DWORD);

    for (DWORD i = 0; i < cProcesses; i++) {
      DWORD pid = aProcesses[i];
      if (pid != 0) {
        HANDLE h = OpenProcess(
          PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,
          FALSE,
          pid
        );
        if (h) {
          char p[MAX_PATH];
          if (GetModuleFileNameExA(h, 0, p, MAX_PATH)) {
            std::string pString(p);
            if (pString.rfind(cwdBufString, 0) == 0) {
              std::string filenameString(p + cwdBufString.length() + 1); // cwd slash
              bool match = false;
              for (auto candidateFileName : candidateFilenames) {
                if (filenameString == candidateFileName && pid != GetCurrentProcessId()) {
                  match = true;
                  break;
                }
              }
              if (match) {
                getOut() << "terminate process " << p << " " << pid << std::endl;
                TerminateProcess(h, 0);
              }
            }
          } else {
            getOut() << "failed to get process file name: " << (void *)GetLastError() << std::endl;
          }
          CloseHandle(h);
        }
      }
    }
  } else {
    getOut() << "failed to enum chrome processes" << std::endl;
  }
}
void terminateKnownProcesses() {
  terminateProcesses(std::vector<const char *>{
    "chrome.exe",
  });
  terminateProcesses(std::vector<const char *>{
    "native_host.exe",
  });
  terminateProcesses(std::vector<const char *>{
    "process.exe",
  });
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  // getOut() << "WindowProc message " << message << " " << WM_DESTROY << std::endl;
  // sort through and find what code to run for the message given

  switch (message) {
    case WM_LBUTTONDOWN: {
      /* if (g_hChildStd_IN_Wr) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        DWORD flags = wParam;
        // getOut() << "mouse down " << x << " " << y << " " << flags << std::endl;

        const json j = {
          {"method", "mousedown"},
          {"args", {
            {"x", x},
            {"y", y},
          }},
        };
        writeChromeJson(j);
      } */

      break;
    }
    case WM_LBUTTONUP: {
      /* if (g_hChildStd_IN_Wr) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        DWORD flags = wParam;
        // getOut() << "mouse up " << x << " " << y << " " << flags << std::endl;
      
        const json j = {
          {"method", "mouseup"},
          {"args", {
            {"x", x},
            {"y", y},
          }},
        };
        writeChromeJson(j);
      } */

      break;
    }
    case WM_MOUSEMOVE: {
      /* if (g_hChildStd_IN_Wr) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        DWORD flags = wParam;
        // getOut() << "mouse move " << x << " " << y << " " << flags << std::endl;

        const json j = {
          {"method", "mousemove"},
          {"args", {
            {"x", x},
            {"y", y},
          }},
        };
        writeChromeJson(j);
      } */
      
      break;
    }
    // this message is read when the window is closed
    case WM_DESTROY: {
      // close the application entirely
      live = false;
      PostQuitMessage(0);
      return 0;
    }
  }

  // Handle any messages the switch statement didn't
  return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
) {
  SetProcessDPIAware();

  terminateKnownProcesses();

  shMem = allocateShared("Local\\OpenVrProxyInit", 1024);
  g_offsets = (Offsets *)shMem;

  {
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(WNDCLASSEX);
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    // wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "RT1";
    RegisterClassExA(&wc);

    g_hWnd = CreateWindowExA(
      NULL,
      wc.lpszClassName,    // name of the window class
      "Monochromium",   // title of the window
      WS_OVERLAPPEDWINDOW,    // window style
      CW_USEDEFAULT,    // x-position of the window
      CW_USEDEFAULT,    // y-position of the window
      1,    // width of the window
      1,    // height of the window
      NULL,    // we have no parent window, NULL
      NULL,    // we aren't using menus, NULL
      hInstance,    // application handle
      NULL
    );    // used with multiple windows, NULL
    // ShowWindow(g_hWnd, SW_SHOW);
  }
  {
    HMODULE d3d11Module = LoadLibraryA("d3d11.dll");
    if (!d3d11Module) {
      getOut() << "failed to load d3d11 module" << std::endl;
      abort();
    }
    HMODULE dxgiModule = LoadLibraryA("dxgi.dll");
    if (!dxgiModule) {
      getOut() << "failed to load dxgi module" << std::endl;
      abort();
    }
    HMODULE dcompModule = LoadLibraryA("dcomp.dll");
    if (!dcompModule) {
      getOut() << "failed to load dcomp module" << std::endl;
      abort();
    }
    
    ID3D11Device *deviceBasic;
    ID3D11DeviceContext *contextBasic;
    IDXGISwapChain *swapChain;

    D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_11_1
    };
    DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Width = 2;
    swapChainDesc.BufferDesc.Height = 2;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = g_hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = true;

    RealD3D11CreateDeviceAndSwapChain = (decltype(D3D11CreateDeviceAndSwapChain) *)GetProcAddress(d3d11Module, "D3D11CreateDeviceAndSwapChain");
    HRESULT hr = RealD3D11CreateDeviceAndSwapChain(
      NULL, // pAdapter
      D3D_DRIVER_TYPE_HARDWARE, // DriverType
      NULL, // Software
      0, // D3D11_CREATE_DEVICE_DEBUG, // Flags
      featureLevels, // pFeatureLevels
      ARRAYSIZE(featureLevels), // FeatureLevels
      D3D11_SDK_VERSION, // SDKVersion
      &swapChainDesc, // pSwapChainDesc,
      &swapChain, // ppSwapChain
      &deviceBasic, // ppDevice
      NULL, // pFeatureLevel
      &contextBasic // ppImmediateContext
    );
    
    IDXGISwapChain1 *swapChain1;
		hr = swapChain->QueryInterface(__uuidof(IDXGISwapChain1), (void **)&swapChain1);

    IDCompositionDesktopDevice *dcompDevice;
    RealDCompositionCreateDevice2 = (decltype(DCompositionCreateDevice2) *)GetProcAddress(dcompModule, "DCompositionCreateDevice2");
    hr = RealDCompositionCreateDevice2(deviceBasic, __uuidof(IDCompositionDesktopDevice), (void **)&dcompDevice);
    
    g_offsets->Present = vtable_offset(dxgiModule, swapChain, 8);
    g_offsets->Present1 = vtable_offset(dxgiModule, swapChain1, 22);
    g_offsets->CreateTargetForHwnd = vtable_offset(dcompModule, dcompDevice, 0);
    
    getOut() << "offset " << g_offsets->Present << " " << g_offsets->Present1 << std::endl;
  }

  getOut() << "process start " << (void *)g_hWnd << " " << (void *)GetLastError() << std::endl;

  wrapExternalOpenVr([&]() -> void {
    // only look in the override
    getOut() << "got dll dir " << dllDir << std::endl;
    std::string openvrApiDllPath = dllDir + "openvr_api.dll";
    getOut() << "core 2 " << openvrApiDllPath << std::endl;
    void *pMod = SharedLib_Load(openvrApiDllPath.c_str());
    getOut() << "core 3 " << (void *)pMod << std::endl;
    // dumpbin /exports "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\vrclient_x64.dll"
    // nothing more to do if we can't load the DLL
    // getOut() << "core 3 " << pMod << std::endl;
    if( !pMod )
    {
      getOut() << "core abort" << std::endl;
      abort();
      // return vr::VRInitError_Init_VRClientDLLNotFound;
    }
    
    // getOut() << "core 4 " << pMod << std::endl;

    __imp_VR_GetGenericInterface = SharedLib_GetFunction( pMod, "VR_GetGenericInterface" );
    getOut() << "core 4" << std::endl;
    __imp_VR_IsInterfaceVersionVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionVersion" );
    __imp_VR_GetInitToken = SharedLib_GetFunction( pMod, "VR_GetInitToken" );
    __imp_VR_IsInterfaceVersion = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersion" );
    __imp_VR_InitInternal2 = SharedLib_GetFunction( pMod, "VR_InitInternal2" );
    __imp_VR_IsInterfaceVersionValid = SharedLib_GetFunction( pMod, "VR_IsInterfaceVersionValid" );
    // __imp_VR_ShutdownInternal = SharedLib_GetFunction( pMod, "VR_ShutdownInternal" );
    __imp_VR_IsHmdPresent = SharedLib_GetFunction( pMod, "VR_IsHmdPresent" );
    __imp_VR_GetVRInitErrorAsSymbol = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsSymbol" );
    __imp_VR_GetVRInitErrorAsEnglishDescription = SharedLib_GetFunction( pMod, "VR_GetVRInitErrorAsEnglishDescription" );
    getOut() << "core 5" << std::endl;
    if (!__imp_VR_GetGenericInterface) {
      getOut() << "unload abort" << std::endl;
      // SharedLib_Unload( pMod );
      abort();
      // return vr::VRInitError_Init_FactoryNotFound;
    }
    
    // getOut() << "core 6 " << pMod << " " << __imp_VR_GetGenericInterface << std::endl;

    /* int nReturnCode = 0;
    g_pHmdSystem = static_cast< IVRClientCore * > ( fnFactory( vr::IVRClientCore_Version, &nReturnCode ) );
    if( !g_pHmdSystem )
    {
      SharedLib_Unload( pMod );
      return vr::VRInitError_Init_InterfaceNotFound;
    } */

    getOut() << "core 6" << std::endl;

    getOut() << "vr_init " << GetCurrentThreadId() << std::endl;
    vr::EVRInitError result;
    vr::VR_Init(&result, vr::VRApplication_Scene);
    if (result != vr::VRInitError_None) {
      getOut() << "vr_init failed" << std::endl;
      abort();
    }
    getOut() << "classes init 1" << std::endl;

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

    getOut() << "classes init 2" << std::endl;
  });

  g_fnp = new FnProxy();
  g_hijacker = new Hijacker(*g_fnp);
  vr::g_pvrsystem = new vr::PVRSystem(vr::g_vrsystem, *g_fnp);
  vr::g_pvrcompositor = new vr::PVRCompositor(vr::g_vrcompositor, *g_hijacker, true, *g_fnp);
  vr::g_pvrclientcore = new vr::PVRClientCore(vr::g_pvrcompositor, *g_fnp);
  vr::g_pvrinput = new vr::PVRInput(vr::g_vrinput, *g_fnp);
  vr::g_pvrscreenshots = new vr::PVRScreenshots(vr::g_vrscreenshots, *g_fnp);
  vr::g_pvrchaperone = new vr::PVRChaperone(vr::g_vrchaperone, *g_fnp);
  vr::g_pvrchaperonesetup = new vr::PVRChaperoneSetup(vr::g_vrchaperonesetup, *g_fnp);
  vr::g_pvrsettings = new vr::PVRSettings(vr::g_vrsettings, *g_fnp);
  vr::g_pvrrendermodels = new vr::PVRRenderModels(vr::g_vrrendermodels, *g_fnp);
  vr::g_pvrapplications = new vr::PVRApplications(vr::g_vrapplications, *g_fnp);
  vr::g_pvroverlay = new vr::PVROverlay(vr::g_vroverlay, *g_fnp);
  vr::g_pqrengine = new QrEngine(vr::g_pvrcompositor, vr::g_vrsystem);
  vr::g_pcvengine = new CvEngine(vr::g_pvrcompositor, vr::g_vrsystem);

  g_fnp->reg<
    kProcess_Terminate,
    int
  >([&]() {
    getOut() << "terminate 1" << std::endl;
    TerminateProcess(chromeProcessHandle, 0);
    getOut() << "terminate 2" << std::endl;
    return 0;
  });

  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  {
    std::string manifestTemplateFilePath = std::filesystem::weakly_canonical(std::filesystem::path(std::string(cwdBuf) + std::string(R"EOF(\extension\native-manifest-template.json)EOF"))).string();
    std::string manifestFilePath = std::filesystem::weakly_canonical(std::filesystem::path(std::string(cwdBuf) + std::string(R"EOF(\extension\native-manifest.json)EOF"))).string();

    std::string s;
    {
      std::ifstream inFile(manifestTemplateFilePath);
      s = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    }
    {
      json j = json::parse(s);
      j["path"] = std::filesystem::weakly_canonical(std::filesystem::path(std::string(cwdBuf) + std::string(R"EOF(\native_host.exe)EOF"))).string();
      s = j.dump(2);
    }
    {    
      std::ofstream outFile(manifestFilePath);
      outFile << s;
      outFile.close();
    }
    
    HKEY hKey;
    LPCTSTR sk = R"EOF(Software\Google\Chrome\NativeMessagingHosts\com.exokit.xrchrome)EOF";
    LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS , &hKey);
    if (openRes == ERROR_FILE_NOT_FOUND) {
      openRes = RegCreateKeyExA(HKEY_CURRENT_USER, sk, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);
      
      if (openRes != ERROR_SUCCESS) {
        getOut() << "failed to create registry key: " << (void*)openRes << std::endl;
        abort();
      }
    } else if (openRes != ERROR_SUCCESS) {
      getOut() << "failed to open registry key: " << (void*)openRes << std::endl;
      abort();
    }

    LPCTSTR value = "";
    LPCTSTR data = manifestFilePath.c_str();
    LONG setRes = RegSetValueEx(hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
    if (setRes != ERROR_SUCCESS) {
      getOut() << "failed to set registry key: " << (void*)setRes << std::endl;
      abort();
    }

    LONG closeRes = RegCloseKey(hKey);
    if (closeRes != ERROR_SUCCESS) {
      getOut() << "failed to close registry key: " << (void*)closeRes << std::endl;
      abort();
    }
  }
  {
    std::string cmd = R"EOF(chrome.exe --enable-features="WebXR,OpenVR" --disable-features="WindowsMixedReality" --no-sandbox --test-type --disable-xr-device-consent-prompt-for-testing --disable-background-timer-throttling --disable-renderer-backgrounding --disable-backgrounding-occluded-windows --load-extension="..\extension,..\metamask" --whitelisted-extension-id="glmgcjligejadkfhgebnplablaggjbmm" --disable-direct-composition --allow-file-access-from-files --auto-select-desktop-capture-source="Metachromium Share - Chromium" )EOF";
    cmd += cwdBuf;
    cmd += R"EOF(\extension\index.html)EOF";
    std::vector<char> cmdVector(cmd.size() + 1);
    memcpy(cmdVector.data(), cmd.c_str(), cmd.size() + 1);

    getOut() << "launch chrome command: " << cmd << std::endl;
    
    char envBuf[64 * 1024];
    getChildEnvBuf(envBuf);

    STARTUPINFO si{};
    si.cb = sizeof(STARTUPINFO);
    
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

      getOut() << "launched chrome ui process: " << pi.dwProcessId << std::endl;
    } else {
      getOut() << "failed to launch chrome ui process: " << (void *)GetLastError() << std::endl;
    }
 
    std::thread([=]() -> void {
      WaitForSingleObject(chromeProcessHandle, INFINITE);

      Sleep(500);

      terminateKnownProcesses();
      
      PostMessage(g_hWnd, WM_DESTROY, 0, 0);
    }).detach();
  }
  
  std::thread([=]() -> void {
    compositor2d::homeRenderLoop();
  }).detach();

  while (live) {
    bool isMessage = g_fnp->handle();

    if (isMessage) {
      MSG msg;
      // wait for the next message in the queue, store the result in 'msg'
      while (PeekMessageA(&msg, NULL, 0, 0, true)) {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);
        // send the message to the WindowProc function
        DispatchMessage(&msg);
      }
    }
  }
  
  getOut() << "process exit" << std::endl;

  return 0;
}