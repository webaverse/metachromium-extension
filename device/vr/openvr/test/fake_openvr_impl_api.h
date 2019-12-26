#ifndef _fake_openvr_impl_api_h_
#define _fake_openvr_impl_api_h_

#include "third_party/openvr/src/headers/openvr.h"

#include <fstream>
#include <functional>

std::ostream &getOut();
void externalOpenVr(std::function<void()> &&fn);

namespace vr {
  extern vr::IVRSystem *g_vrsystem;
  extern vr::IVRCompositor *g_vrcompositor;
  extern vr::IVRChaperone *g_vrchaperone;
  extern vr::IVRChaperoneSetup *g_vrchaperonesetup;
  extern vr::IVROverlay *g_vroverlay;
  extern vr::IVRRenderModels *g_vrrendermodels;
  extern vr::IVRScreenshots *g_vrscreenshots;
  extern vr::IVRSettings *g_vrsettings;
  extern vr::IVRExtendedDisplay *g_vrextendeddisplay;
  extern vr::IVRApplications *g_vrapplications;
  extern vr::IVRInput *g_vrinput;
}

#endif