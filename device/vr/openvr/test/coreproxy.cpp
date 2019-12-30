#include "device/vr/openvr/test/coreproxy.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRClientCore_Init[] = "IVRClientCore::Init";
char kIVRClientCore_Cleanup[] = "IVRClientCore::Cleanup";

PVRClientCore::PVRClientCore(FnProxy &fnp) :
  fnp(fnp),
  mut("Local\\OpenVrClientCoreMutex"),
  rightEye(false)
{
  // getOut() << "init client core 1" << std::endl;

  {
    std::lock_guard<Mutex> lock(mut);
    waitSems.emplace(fnp.callbackId, (std::string("Local\\OpenVrWaitSem") + std::to_string(fnp.callbackId)).c_str());
    waitSemsOrder.push_back(&waitSems.find(fnp.callbackId)->second);
    submitSems.emplace(fnp.callbackId, (std::string("Local\\OpenVrSubmitSem") + std::to_string(fnp.callbackId)).c_str());
    // submitSemsOrder.push_back(&submitSems.find(fnp.callbackId)->second);
    if (waitSemsOrder.size() == 1) {
      waitSemsOrder[0]->unlock();
    }
  }

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

void PVRClientCore::PreWaitGetPoses(bool *doRealWait) {
  // getOut() << "PreWaitGetPoses 1" << std::endl;
  Semaphore *sem;
  {
    std::lock_guard<Mutex> lock(mut);
    sem = &waitSems.find(fnp.callbackId)->second;
    auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), sem);
    *doRealWait = std::distance(waitSemsOrder.begin(), iter) == 0;
  }
  // getOut() << "PreWaitGetPoses 2 " << *doRealWait << std::endl;
  sem->lock();
  //  getOut() << "PreWaitGetPoses 3" << std::endl;
}
void PVRClientCore::PostWaitGetPoses() {
  // getOut() << "PostWaitGetPoses 1" << std::endl;
  Semaphore *nextSem;
  {
    std::lock_guard<Mutex> lock(mut);

    Semaphore *submitSem = &submitSems.find(fnp.callbackId)->second;
    submitSemsOrder.push_back(submitSem);

    Semaphore *sem = &waitSems.find(fnp.callbackId)->second;
    auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), sem);
    int index = std::distance(waitSemsOrder.begin(), iter);
    if ((index+1) < waitSemsOrder.size()) {
      nextSem = waitSemsOrder[index+1];
    } else {
      nextSem = submitSemsOrder[0];
    }
  }
  // getOut() << "PostWaitGetPoses 2" << std::endl;
  nextSem->unlock();
  // getOut() << "PostWaitGetPoses 3" << std::endl;
}
void PVRClientCore::PreSubmit(bool *doRealSubmit) {
  // getOut() << "PreSubmit 1" << std::endl;
  Semaphore *submitSem;
  {
    std::lock_guard<Mutex> lock(mut);

    submitSem = &submitSems.find(fnp.callbackId)->second;
    auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), submitSem);
    *doRealSubmit = std::distance(submitSemsOrder.begin(), iter) == (submitSemsOrder.size() - 1);
  }
  // getOut() << "PreSubmit 2 " << *doRealSubmit << std::endl;
  submitSem->lock();
  // getOut() << "PreSubmit 3" << std::endl;
}
void PVRClientCore::PostSubmit() {
  // getOut() << "PostSubmit 1" << std::endl;
  Semaphore *nextSem;
  {
    std::lock_guard<Mutex> lock(mut);
    
    bool localRightEye = rightEye;
    rightEye = !rightEye;

    Semaphore *submitSem = &submitSems.find(fnp.callbackId)->second;
    if (!localRightEye) {
      // getOut() << "PostSubmit next right eye" << std::endl;
      nextSem = submitSem;
    } else {
      auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), submitSem);
      int index = std::distance(submitSemsOrder.begin(), iter);
      if ((index+1) < submitSemsOrder.size()) {
        // getOut() << "PostSubmit next submit" << std::endl;
        nextSem = submitSemsOrder[index+1];
      } else {
        // getOut() << "PostSubmit next wait" << std::endl;
        nextSem = waitSemsOrder[0];
        submitSemsOrder.clear();
      }
    }
  }
  // getOut() << "PostSubmit 2" << std::endl;
  nextSem->unlock();
  // getOut() << "PostSubmit 3" << std::endl;
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