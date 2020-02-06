#include "device/vr/openvr/test/coreproxy.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRClientCore_Init[] = "IVRClientCore::Init";
char kIVRClientCore_Cleanup[] = "IVRClientCore::Cleanup";
char kPVRClientCore_PreWaitGetPoses[] = "PVRClientCore::PreWaitGetPoses";
char kPVRClientCore_PreSubmit[] = "PVRClientCore::PreSubmit";

PVRClientCore::PVRClientCore(PVRCompositor *pvrcompositor, FnProxy &fnp) :
  pvrcompositor(pvrcompositor),
  fnp(fnp)
  // mut("Local\\OpenVrClientCoreMutex"),
  // rightEye(false)
{
  fnp.reg<
    kIVRClientCore_Init,
    EVRInitError,
    EVRApplicationType
  >([=](EVRApplicationType eApplicationType) {
    return VRInitError_None;
  });
  fnp.reg<
    kIVRClientCore_Cleanup,
    int
  >([=]() {
    // XXX
    return 0;
  });
  fnp.reg<
    kPVRClientCore_PreWaitGetPoses,
    size_t
  >([=, &fnp]() {
    size_t remoteProcessId = fnp.remoteProcessId;

    if (processIds.find(remoteProcessId) == processIds.end()) {
      processIds.insert(remoteProcessId);
    }

    {
      auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), remoteProcessId);
      if (iter == waitSemsOrder.end()) { // we were not already waiting 
        waitSemsOrder.push_back(remoteProcessId);
      }
    }
    {
      auto newEnd = std::remove_if(submitSemsOrder.begin(), submitSemsOrder.end(), [&](size_t id2) {
        if (id2 == remoteProcessId) {
          return true;
        } else {
          return false;
        }
      });
      submitSemsOrder.erase(newEnd, submitSemsOrder.end());
    }

    if (waitSemsOrder.size() >= processIds.size()) {
      pvrcompositor->CacheWaitGetPoses();

      unlockSemsOrder = std::move(waitSemsOrder);
      waitSemsOrder.clear();
    }
    
    if (unlockSemsOrder.size() > 0) {
      size_t unlockProcessId = unlockSemsOrder.front();
      unlockSemsOrder.pop_front();

      Semaphore *sem = getLocalSemaphore(unlockProcessId);
      sem->unlock();

      submitSemsOrder.push_back(unlockProcessId);
      submitSemsOrder.push_back(unlockProcessId);
    }

    return remoteProcessId;
  });
  fnp.reg<
    kPVRClientCore_PreSubmit,
    std::tuple<bool, bool>
  >([=, &fnp]() {
    size_t remoteProcessId = fnp.remoteProcessId;
    auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), remoteProcessId);
    bool doQueueSubmit;
    bool doRealSubmit;
    if (iter != submitSemsOrder.end()) {
      submitSemsOrder.erase(iter);
      doQueueSubmit = true;
      doRealSubmit = unlockSemsOrder.size() == 0 && submitSemsOrder.size() == 0;
    } else {
      doQueueSubmit = false;
      doRealSubmit = false;
    }

    return std::tuple<bool, bool>(
      // nextSemId,
      doQueueSubmit,
      doRealSubmit
    );
  });
}
EVRInitError PVRClientCore::Init(EVRApplicationType eApplicationType, const char *pStartupInfo) {
  auto result = fnp.call<kIVRClientCore_Init, EVRInitError, EVRApplicationType>(eApplicationType);
  return result;
}
void PVRClientCore::Cleanup() {
  fnp.call<kIVRClientCore_Cleanup, int>();
}

Semaphore *PVRClientCore::getLocalSemaphore(size_t id) {
  auto iter = localSems.find(id);
  if (iter == localSems.end()) {
    localSems.emplace(id, (std::string("Local\\OpenVrWaitSem") + std::to_string(id)).c_str());
    iter = localSems.find(id);
  }
  return &iter->second;
}

void PVRClientCore::PreWaitGetPoses() {
  auto result = fnp.call<kPVRClientCore_PreWaitGetPoses, size_t>();
  Semaphore *sem = getLocalSemaphore(result);
  sem->lock();
}
void PVRClientCore::PreSubmit(bool *doQueueSubmit, bool *doRealSubmit) {
  auto result = fnp.call<kPVRClientCore_PreSubmit, std::tuple<bool, bool>>();

  *doQueueSubmit = std::get<0>(result);
  *doRealSubmit = std::get<1>(result);
}
}