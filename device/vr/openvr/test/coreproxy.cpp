#include "device/vr/openvr/test/coreproxy.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRClientCore_Init[] = "IVRClientCore::Init";
char kIVRClientCore_Cleanup[] = "IVRClientCore::Cleanup";

PVRClientCore::PVRClientCore(FnProxy &fnp) : fnp(fnp) {
  // getOut() << "init client core 1" << std::endl;
  fnp.reg<
    kIVRClientCore_Init,
    EVRInitError,
    EVRApplicationType
  >([=](EVRApplicationType eApplicationType) {
    // getOut() << "handle client init" << std::endl;
    // XXX
    return VRInitError_None;
  });
  // getOut() << "init client core 2 " << (fnp.fns.find(kIVRClientCore_Init) != fnp.fns.end()) << std::endl;
  fnp.reg<
    kIVRClientCore_Cleanup,
    int
  >([=]() {
    // XXX
    return 0;
  });
  // getOut() << "init client core 3" << std::endl;
}
EVRInitError PVRClientCore::Init(EVRApplicationType eApplicationType, const char *pStartupInfo) {
  // getOut() << "submit client core init" << std::endl;
  return fnp.call<kIVRClientCore_Init, EVRInitError, EVRApplicationType>(eApplicationType);
}
void PVRClientCore::Cleanup() {
  fnp.call<kIVRClientCore_Cleanup, int>();
}
// char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";

/* PVRCompositor::PVRCompositor(IVRSystem *vrsystem, IVRCompositor *vrcompositor, FnProxy &fnp) : vrcompositor(vrcompositor), fnp(fnp) {
  fnp.reg<
    kIVRCompositor_SetTrackingSpace,
    int,
    ETrackingUniverseOrigin
  >([=](ETrackingUniverseOrigin eOrigin) {
    vrcompositor->SetTrackingSpace(eOrigin);
    return 0;
  });
}
void PVRCompositor::SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) {
  fnp.call<kIVRCompositor_SetTrackingSpace, int, ETrackingUniverseOrigin>(eOrigin);
} */
}