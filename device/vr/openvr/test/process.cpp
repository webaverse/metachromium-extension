#include <iostream>

#include "device/vr/openvr/test/out.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

bool isProcess = true;

int main() {
  getOut() << "process start 1" << std::endl;

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
    std::cout << "process start 4 " << dllDir << std::endl;
  }
  
  getOut() << "process start 5 " << dllDir << std::endl;

  void *shMem = allocateShared("Local\\OpenVrProxyInit", 1024);
  uint64_t *pFence = ((uint64_t *)shMem) + 1;

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
  vr::PVRCompositor compositor(vr::g_vrcompositor, *pFence, fnp);
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
    // getOut() << "handled" << std::endl;
  }
  
  getOut() << "process exit" << std::endl;

  return 0;
}