#include "device/vr/openvr/test/coreproxy.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRClientCore_Init[] = "IVRClientCore::Init";
char kIVRClientCore_Cleanup[] = "IVRClientCore::Cleanup";
char kPVRClientCore_PreWaitGetPoses[] = "PVRClientCore::PreWaitGetPoses";
char kPVRClientCore_PreSubmit[] = "PVRClientCore::PreSubmit";

/* constexpr size_t WAIT_MASK = 0x100000000;
constexpr size_t SUBMIT_MASK = 0x200000000; */

PVRClientCore::PVRClientCore(PVRCompositor *pvrcompositor, FnProxy &fnp) :
  pvrcompositor(pvrcompositor),
  fnp(fnp)
  // mut("Local\\OpenVrClientCoreMutex"),
  // rightEye(false)
{
  // getOut() << "init client core 1" << std::endl;

  fnp.reg<
    kIVRClientCore_Init,
    EVRInitError,
    EVRApplicationType
  >([=](EVRApplicationType eApplicationType) {
    // getOut() << "handle client core init" << std::endl;
 
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
  fnp.reg<
    kPVRClientCore_PreWaitGetPoses,
    size_t
  >([=, &fnp]() {
    // size_t id = fnp.remoteCallbackId;
    size_t remoteProcessId = fnp.remoteProcessId;
    
    if (processIds.find(remoteProcessId) == processIds.end()) {
      processIds.insert(remoteProcessId);
    }
    
    // getOut() << "pre wait 1 " << id << std::endl;

    {
      auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), remoteProcessId);
      if (iter == waitSemsOrder.end()) { // we were not already waiting 
        waitSemsOrder.push_back(remoteProcessId);
        /* if (waitSemsOrder.size() == 1) {
          // getOut() << "get local sema 1" << std::endl;
          Semaphore *sem = getLocalSemaphore(id);
          // getOut() << "get local sema 2 " << (void *)sem << std::endl;
          sem->unlock();
          // getOut() << "get local sema 3" << (void *)sem << std::endl;
        }
        // getOut() << "wait sems order new size " << waitSemsOrder.size() << std::endl; */
      }
    }
    
    // getOut() << "pre wait 2 " << submitSemsOrder.size() << " " << (id | WAIT_MASK) << " " << id << std::endl;

    // bool foundPendingSubmit = false;
    {
      auto newEnd = std::remove_if(submitSemsOrder.begin(), submitSemsOrder.end(), [&](size_t id2) {
        if (id2 == remoteProcessId) {
          // getOut() << "pre wait remove " << id << std::endl;
          // foundPendingSubmit = true;
          return true;
        } else {
          return false;
        }
      });
      submitSemsOrder.erase(newEnd, submitSemsOrder.end());
    }

    submitSemsOrder.push_back(remoteProcessId);
    submitSemsOrder.push_back(remoteProcessId);

    if (waitSemsOrder.size() >= processIds.size()) {
      getOut() << "wait get poses flush 1 " << waitSemsOrder.size() << " " << processIds.size() << std::endl;
      pvrcompositor->CacheWaitGetPoses();
      getOut() << "wait get poses flush 2 " << waitSemsOrder.size() << " " << processIds.size() << std::endl;

      for (auto iter : waitSemsOrder) {
        Semaphore *sem = getLocalSemaphore(iter);
        sem->unlock();
      }
      /* {
        auto newEnd = std::remove_if(waitSemsOrder.begin(), waitSemsOrder.end(), [&](size_t id2) {
          if (id2 == remoteProcessId) {
            return true;
          } else {
            return false;
          }
        });
        waitSemsOrder.erase(newEnd, waitSemsOrder.end());
      } */
      waitSemsOrder.clear();
    } else {
      getOut() << "wait get poses do not flush " << waitSemsOrder.size() << " " << processIds.size() << std::endl;
    }
    /* auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), id);
    // getOut() << "iter distance " << id << " " << waitSemsOrder.size() << " " << (iter != waitSemsOrder.end()) << " " << std::distance(waitSemsOrder.begin(), iter) << std::endl;
    bool doRealWait = std::distance(waitSemsOrder.begin(), iter) == 0; */

    // getOut() << "pre wait 3 " << submitSemsOrder.size() << " " << nextSemId << " " << id << std::endl;

    return remoteProcessId;
  });
  fnp.reg<
    kPVRClientCore_PreSubmit,
    std::tuple<bool, bool>
  >([=, &fnp]() {
    size_t remoteProcessId = fnp.remoteProcessId;
    auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), remoteProcessId);
    // size_t nextSemId;
    bool doQueueSubmit;
    bool doRealSubmit;
    if (iter != submitSemsOrder.end()) {
      submitSemsOrder.erase(iter);
      // nextSemId = id | SUBMIT_MASK;
      doQueueSubmit = true;
      doRealSubmit = submitSemsOrder.size() == 0;
      getOut() << "pre submit yes submit " << submitSemsOrder.size() << std::endl;
    } else {
      // nextSemId = 0;
      doQueueSubmit = false;
      doRealSubmit = false;
      getOut() << "pre submit do not submit " << submitSemsOrder.size() << std::endl;
    }
 
    // auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), id);
    // getOut() << "do submit " << std::distance(submitSemsOrder.begin(), iter) << " " << submitSemsOrder.size() << std::endl;
    
    // getOut() << "pre submit " << doRealSubmit << std::endl;

    return std::tuple<bool, bool>(
      // nextSemId,
      doQueueSubmit,
      doRealSubmit
    );
  });
  
  // getOut() << "init client core 2" << std::endl;
}
EVRInitError PVRClientCore::Init(EVRApplicationType eApplicationType, const char *pStartupInfo) {
  // getOut() << "client core init 1 " << fnp.fns.size() << std::endl;
  auto result = fnp.call<kIVRClientCore_Init, EVRInitError, EVRApplicationType>(eApplicationType);
  // getOut() << "client core init 2" << std::endl;
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
  // getOut() << "PreWaitGetPoses 1" << std::endl;
  auto result = fnp.call<kPVRClientCore_PreWaitGetPoses, size_t>();
  Semaphore *sem = getLocalSemaphore(result);
  getOut() << "wait get poses lock 1 " << result << " " << (void *)sem << std::endl;
  // {
    // fnp.mut.unlock();
    sem->lock();
    // fnp.mut.lock();
  // }
  getOut() << "wait get poses lock 2 " << result << std::endl;
}
void PVRClientCore::PreSubmit(bool *doQueueSubmit, bool *doRealSubmit) {
  //  getOut() << "PreSubmit 1" << std::endl;

  auto result = fnp.call<kPVRClientCore_PreSubmit, std::tuple<bool, bool>>();

  // size_t id = std::get<0>(result);
  *doQueueSubmit = std::get<0>(result);
  *doRealSubmit = std::get<1>(result);
  
  /* if (id != 0) {
    Semaphore *nextSem = getLocalSemaphore(id);

    // getOut() << "PreSubmit 2 " << fnp.callbackId << " " << localSems.size() << " " << id << " " << (id &~(WAIT_MASK|SUBMIT_MASK)) << " " << !!(id & WAIT_MASK) << " " << !!(id & SUBMIT_MASK) << " " << *doRealSubmit << std::endl;
    nextSem->lock();
    // getOut() << "PreSubmit 3" << std::endl;
  } */
}
}