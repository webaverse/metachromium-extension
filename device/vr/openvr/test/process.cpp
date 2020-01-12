// #include <windows.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <io.h>
// #include <iostream>
// #include <fstream>

#include "device/vr/openvr/test/out.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

bool isProcess = true;
HWND g_hWnd = NULL;
bool live = true;

/* // maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 9999;
void RedirectIOToConsole()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
    // point to console as well
    std::ios::sync_with_stdio();
} */

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // getOut() << "WindowProc message " << message << " " << WM_DESTROY << std::endl;
  // sort through and find what code to run for the message given
  switch(message)
  {
      // this message is read when the window is closed
      case WM_DESTROY:
          {
              // close the application entirely
              live = false;
              PostQuitMessage(0);
              return 0;
          } break;
  }

  // Handle any messages the switch statement didn't
  return DefWindowProc (hWnd, message, wParam, lParam);
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
) {
  // RedirectIOToConsole();

  WNDCLASSEX wc{};
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszClassName = "RT1";
  RegisterClassEx(&wc);

  g_hWnd = CreateWindowExA(
    NULL,
    "RT1",    // name of the window class
    "Reality Tab",   // title of the window
    WS_OVERLAPPEDWINDOW,    // window style
    300,    // x-position of the window
    300,    // y-position of the window
    512,    // width of the window
    512,    // height of the window
    NULL,    // we have no parent window, NULL
    NULL,    // we aren't using menus, NULL
    hInstance,    // application handle
    NULL
  );    // used with multiple windows, NULL
  ShowWindow(g_hWnd, SW_SHOW);

  getOut() << "process start 1 " << (void *)g_hWnd << " " << (void *)GetLastError() << std::endl;

  {  
    char dllPath[MAX_PATH];
    HMODULE hm = GetModuleHandleW(NULL);
    if (hm == 0) {
        int ret = GetLastError();
        // getOut() << "GetModuleHandle failed, error = " << ret << std::endl;
        // Return or however you want to handle an error.
        getOut() << "dll abort 1" << std::endl; abort();
    }
    if (GetModuleFileName(hm, dllPath, sizeof(dllPath)) == 0) {
        int ret = GetLastError();
        // getOut() << "GetModuleFileName failed, error = " << ret << std::endl;
        getOut() << "dll abort 2" << std::endl; abort();
    }
    
    getOut() << "process start 2 " << dllPath << std::endl;
    
    char drive[MAX_PATH];
    char dir[MAX_PATH];
    // char fname[MAX_PATH];
    // char ext[MAX_PATH];
    _splitpath(dllPath, drive, dir, nullptr, nullptr);
    getOut() << "process start 3 " << dllPath << " " << drive << " " << dir << std::endl;
    dllDir = drive;
    dllDir += dir;
    getOut() << "process start 4 " << dllDir << std::endl;
  }
  
  getOut() << "process start 5 " << dllDir << std::endl;

  wrapExternalOpenVr([&]() -> void {
    // only look in the override
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
  while (live) {
    DWORD result = MsgWaitForMultipleObjects(
      1,
      &fnp.inSem.h,
      false,
      INFINITE,
      QS_ALLEVENTS
    );
    if (result == WAIT_OBJECT_0) {
      fnp.handle();
    } else if (result == (WAIT_OBJECT_0 + 1)) {
      MSG msg;
      // wait for the next message in the queue, store the result in 'msg'
      if (GetMessage(&msg, NULL, 0, 0)) {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
      }
    } else {
      getOut() << "unknown message wake: " << (void *)result << std::endl;
      abort();
    }
  }
  
  getOut() << "process exit" << std::endl;

  return 0;
}