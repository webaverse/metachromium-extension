#ifndef _openvr_coreproxy_h_
#define _openvr_coreproxy_h_

#include <deque>
#include <set>
#include <algorithm>

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"
#include "device/vr/openvr/test/compositorproxy.h"

namespace vr {
class PVRClientCore {
public:
  PVRCompositor *pvrcompositor;
  FnProxy &fnp;

  std::set<size_t> processIds;
  size_t runningFrameProcessId = 0;
  std::deque<size_t> waitSemsOrder;
  std::deque<size_t> unlockWaitSemsOrder;
  std::deque<size_t> unlockSubmitSemsOrder;
  std::map<size_t, Semaphore> localSems;

  PVRClientCore(PVRCompositor *pvrcompositor, FnProxy &fnp);
  EVRInitError Init(EVRApplicationType eApplicationType, const char *pStartupInfo);
	void Cleanup();
  Semaphore *getLocalSemaphore(size_t id);
    
  void PreWaitGetPoses();
  void PreSubmit(bool *doQueueSubmit, bool *doRealSubmit);
  void TickWait();
};
}

#endif