#ifndef _fake_openvr_impl_api_h_
#define _fake_openvr_impl_api_h_

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/proxy.h"

#include <functional>

void externalOpenVr(std::function<void()> &&fn);

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

  extern PVRCompositor *g_pvrcompositor;
}

#endif