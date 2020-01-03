#ifndef _fake_openvr_impl_api_h_
#define _fake_openvr_impl_api_h_

// #include <functional>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/coreproxy.h"
#include "device/vr/openvr/test/systemproxy.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/inputproxy.h"
#include "device/vr/openvr/test/screenshotsproxy.h"
#include "device/vr/openvr/test/chaperoneproxy.h"

extern std::string dllDir;
extern void *shMem;
extern size_t *pBooted;
// extern GLFWwindow **ppWindow;
// extern size_t *pNumClients;

void wrapExternalOpenVr(std::function<void()> &&fn);

namespace vr {
  extern IVRSystem *g_vrsystem;
  extern IVRCompositor *g_vrcompositor;
  extern IVRChaperone *g_vrchaperone;
  extern IVRChaperoneSetup *g_vrchaperonesetup;
  extern IVROverlay *g_vroverlay;
  extern IVRRenderModels *g_vrrendermodels;
  extern IVRScreenshots *g_vrscreenshots;
  extern IVRSettings *g_vrsettings;
  extern IVRExtendedDisplay *g_vrextendeddisplay;
  extern IVRApplications *g_vrapplications;
  extern IVRInput *g_vrinput;

  extern PVRClientCore *g_pvrclientcore;
  extern PVRSystem *g_pvrsystem;
  extern PVRCompositor *g_pvrcompositor;
  extern PVRInput *g_pvrinput;
  extern PVRScreenshots *g_pvrscreenshots;
  extern PVRChaperone *g_pvrchaperone;
}

extern "C" {
  extern void *__imp_VR_GetGenericInterface;
  extern void *__imp_VR_IsInterfaceVersionVersion;
  extern void *__imp_VR_GetInitToken;
  extern void *__imp_VR_IsInterfaceVersion;
  extern void *__imp_VR_InitInternal2;
  extern void *__imp_VR_IsInterfaceVersionValid;
  extern void *__imp_VR_ShutdownInternal;
  extern void *__imp_VR_IsHmdPresent;
  extern void *__imp_VR_GetVRInitErrorAsSymbol;
  extern void *__imp_VR_GetVRInitErrorAsEnglishDescription;
}

#endif