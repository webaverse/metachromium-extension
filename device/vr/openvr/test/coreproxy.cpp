#include "device/vr/openvr/test/coreproxy.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRClientCore_Init[] = "IVRClientCore::Init";
char kIVRClientCore_Cleanup[] = "IVRClientCore::Cleanup";
char kPVRClientCore_PreWaitGetPoses[] = "PVRClientCore::PreWaitGetPoses";
char kPVRClientCore_PostWaitGetPoses[] = "PVRClientCore::PostWaitGetPoses";
char kPVRClientCore_PreSubmit[] = "PVRClientCore::PreSubmit";
char kPVRClientCore_PostSubmit[] = "PVRClientCore::PostSubmit";

constexpr size_t WAIT_MASK = 0x100000000;
constexpr size_t SUBMIT_MASK = 0x200000000;

PVRClientCore::PVRClientCore(FnProxy &fnp) :
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
    std::tuple<size_t, bool>
  >([=]() {
    size_t id = fnp.remoteCallbackId;
    
    // getOut() << "pre wait 1" << std::endl;
    
    {
      auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), id);
      if (iter == waitSemsOrder.end()) {
        waitSemsOrder.push_back(id);
        if (waitSemsOrder.size() == 1) {
          // getOut() << "get local sema 1" << std::endl;
          Semaphore *sem = getLocalSemaphore(fnp.remoteCallbackId | WAIT_MASK);
          // getOut() << "get local sema 2 " << (void *)sem << std::endl;
          sem->unlock();
          // getOut() << "get local sema 3" << (void *)sem << std::endl;
        }
        // getOut() << "wait sems order new size " << waitSemsOrder.size() << std::endl;
      }
    }
    
    // getOut() << "pre wait 2" << std::endl;

    bool foundPendingSubmit = false;
    std::remove_if(submitSemsOrder.begin(), submitSemsOrder.end(), [&](size_t id2) {
      if (id == id2) {
        foundPendingSubmit = true;
        return true;
      } else {
        return false;
      }
    });

    size_t nextSemId = !foundPendingSubmit ? (id | WAIT_MASK) : 0;
    auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), id);
    // getOut() << "iter distance " << id << " " << waitSemsOrder.size() << " " << (iter != waitSemsOrder.end()) << " " << std::distance(waitSemsOrder.begin(), iter) << std::endl;
    bool doRealWait = std::distance(waitSemsOrder.begin(), iter) == 0;

    // getOut() << "pre wait 3" << std::endl;

    return std::tuple<size_t, bool>(
      nextSemId,
      doRealWait
    );
  });
  fnp.reg<
    kPVRClientCore_PostWaitGetPoses,
    size_t
  >([=]() {
    size_t id = fnp.remoteCallbackId;
    size_t nextSemId;

    submitSemsOrder.push_back(id);
    submitSemsOrder.push_back(id);

    auto iter = std::find(waitSemsOrder.begin(), waitSemsOrder.end(), id);
    int index = std::distance(waitSemsOrder.begin(), iter);
    if ((index+1) < waitSemsOrder.size()) {
      // getOut() << "post wait get poses wait " << submitSemsOrder.size() << std::endl;
      nextSemId = waitSemsOrder[index+1] | WAIT_MASK;
    } else {
      // getOut() << "post wait get poses submit " << submitSemsOrder.size() << std::endl;
      nextSemId = submitSemsOrder.front() | SUBMIT_MASK;
      submitSemsOrder.pop_front();
    }

    return nextSemId;
  });
  fnp.reg<
    kPVRClientCore_PreSubmit,
    std::tuple<size_t, bool>
  >([=]() {
    size_t id = fnp.remoteCallbackId;
    size_t nextSemId = id | SUBMIT_MASK;

    // auto iter = std::find(submitSemsOrder.begin(), submitSemsOrder.end(), id);
    // getOut() << "do submit " << std::distance(submitSemsOrder.begin(), iter) << " " << submitSemsOrder.size() << std::endl;
    bool doRealSubmit = submitSemsOrder.size() == 0;
    
    // getOut() << "pre submit " << doRealSubmit << std::endl;

    return std::tuple<size_t, bool>(
      nextSemId,
      doRealSubmit
    );
  });
  fnp.reg<
    kPVRClientCore_PostSubmit,
    size_t
  >([=]() {
    size_t nextSemId;

    if (submitSemsOrder.size() > 0) {
      // getOut() << "post submit submit " << submitSemsOrder.size() << std::endl;
      nextSemId = submitSemsOrder.front() | SUBMIT_MASK;
      submitSemsOrder.pop_front();
    } else {
      // getOut() << "post submit wait " << submitSemsOrder.size() << std::endl;
      nextSemId = waitSemsOrder[0] | WAIT_MASK;
    }
    
    return nextSemId;
  });
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

void PVRClientCore::PreWaitGetPoses(bool *doRealWait) {
  // getOut() << "PreWaitGetPoses 1" << std::endl;
  auto result = fnp.call<kPVRClientCore_PreWaitGetPoses, std::tuple<size_t, bool>>();

  size_t id = std::get<0>(result);
  *doRealWait = std::get<1>(result);

  if (id != 0) {
    Semaphore *sem = getLocalSemaphore(id);
    // getOut() << "PreWaitGetPoses 2 " << id << " " << *doRealWait << std::endl;
    sem->lock();
    // getOut() << "PreWaitGetPoses 3 " << *doRealWait << std::endl;
  }
}
void PVRClientCore::PostWaitGetPoses() {
  // getOut() << "PostWaitGetPoses 1" << std::endl;
  
  auto result = fnp.call<kPVRClientCore_PostWaitGetPoses, size_t>();
  
  Semaphore *nextSem = getLocalSemaphore(result);
  
  // getOut() << "PostWaitGetPoses 2 " << result << std::endl;
  nextSem->unlock();
  // getOut() << "PostWaitGetPoses 3" << std::endl;
}
void PVRClientCore::PreSubmit(bool *doRealSubmit) {
  //  getOut() << "PreSubmit 1" << std::endl;

  auto result = fnp.call<kPVRClientCore_PreSubmit, std::tuple<size_t, bool>>();

  size_t id = std::get<0>(result);
  *doRealSubmit = std::get<1>(result);
  
  if (id != 0) {
    Semaphore *nextSem = getLocalSemaphore(id);

    // getOut() << "PreSubmit 2 " << fnp.callbackId << " " << localSems.size() << " " << id << " " << (id &~(WAIT_MASK|SUBMIT_MASK)) << " " << !!(id & WAIT_MASK) << " " << !!(id & SUBMIT_MASK) << " " << *doRealSubmit << std::endl;
    nextSem->lock();
    // getOut() << "PreSubmit 3" << std::endl;
  }
}
void PVRClientCore::PostSubmit() {
  // getOut() << "PostSubmit 1" << std::endl;

  auto result = fnp.call<kPVRClientCore_PostSubmit, size_t>();

  Semaphore *nextSem = getLocalSemaphore(result);

  // getOut() << "PostSubmit 2 " << result << std::endl;
  nextSem->unlock();
  // getOut() << "PostSubmit 3" << std::endl;
}
}