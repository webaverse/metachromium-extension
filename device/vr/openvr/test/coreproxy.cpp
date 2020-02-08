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
    getOut() << "client core cleanup 1" << std::endl;

    size_t remoteProcessId = fnp.remoteProcessId;
    if (std::find(processIds.begin(), processIds.end(), remoteProcessId) != processIds.end()) {
      processIds.erase(remoteProcessId);

      {
        auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), remoteProcessId);
        if (iter != waitSemsOrder.end()) {
          waitSemsOrder.erase(iter);
        }
      }
      {
        auto iter = std::find(unlockWaitSemsOrder.begin(), unlockWaitSemsOrder.end(), remoteProcessId);
        if (iter != unlockWaitSemsOrder.end()) {
          unlockWaitSemsOrder.erase(iter);
        }
      }
      for (;;) {
        auto iter = std::find(unlockSubmitSemsOrder.begin(), unlockSubmitSemsOrder.end(), remoteProcessId);
        if (iter != unlockSubmitSemsOrder.end()) {
          unlockSubmitSemsOrder.erase(iter);
        } else {
          break;
        }
      }

      if (remoteProcessId == runningFrameProcessId) { // if we were currently dispatched, dispatch the next wait
        TickWait(remoteProcessId);
      }
    }

    return 0;
  });
  fnp.reg<
    kPVRClientCore_PreWaitGetPoses,
    size_t
  >([=, &fnp]() {
    size_t remoteProcessId = fnp.remoteProcessId;

    processIds.insert(remoteProcessId);

    // add wait sem
    {
      auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), remoteProcessId);
      if (iter == waitSemsOrder.end()) { // we were not already waiting 
        waitSemsOrder.push_back(remoteProcessId);
      } else {
        getOut() << "double wait for process id " << remoteProcessId << std::endl;
        abort();
      }
    }

    TickWait(remoteProcessId);

    return remoteProcessId;
  });
  fnp.reg<
    kPVRClientCore_PreSubmit,
    std::tuple<bool, bool>
  >([=, &fnp]() {
    size_t remoteProcessId = fnp.remoteProcessId;
    auto iter = std::find(unlockSubmitSemsOrder.begin(), unlockSubmitSemsOrder.end(), remoteProcessId);
    bool doQueueSubmit;
    bool doRealSubmit;
    if (iter != unlockSubmitSemsOrder.end()) {
      unlockSubmitSemsOrder.erase(iter);
      doQueueSubmit = true;
      doRealSubmit = unlockWaitSemsOrder.size() == 0 && unlockSubmitSemsOrder.size() == 0;
    } else {
      doQueueSubmit = false;
      doRealSubmit = false;
    }

    return std::tuple<bool, bool>(
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
void PVRClientCore::TickWait(size_t remoteProcessId) {
  // if we are not running and everyone is queued up, trigger a new frame
  if (unlockWaitSemsOrder.size() == 0 && waitSemsOrder.size() > 0 && waitSemsOrder.size() >= processIds.size()) {
    pvrcompositor->CacheWaitGetPoses();

    unlockWaitSemsOrder = std::move(waitSemsOrder);
    waitSemsOrder.clear();
    unlockSubmitSemsOrder.clear();
  }

  // dipatch next process in the frame
  if (unlockWaitSemsOrder.size() > 0) {
    size_t unlockProcessId = unlockWaitSemsOrder.front();
    unlockWaitSemsOrder.pop_front();

    Semaphore *sem = getLocalSemaphore(unlockProcessId);
    sem->unlock();

    unlockSubmitSemsOrder.push_back(unlockProcessId);
    unlockSubmitSemsOrder.push_back(unlockProcessId);

    runningFrameProcessId = remoteProcessId;
  } else {
    runningFrameProcessId = 0;
  }
}
}