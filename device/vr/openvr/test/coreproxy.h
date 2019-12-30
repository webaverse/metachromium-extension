#ifndef _openvr_coreproxy_h_
#define _openvr_coreproxy_h_

#include <D3D11_1.h>
#include <DXGI1_4.h>
#include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRClientCore {
public:
  FnProxy &fnp;

  std::map<size_t, Semaphore> waitSems;
  std::map<size_t, Semaphore> submitSems;

  PVRClientCore(FnProxy &fnp);
  EVRInitError Init(EVRApplicationType eApplicationType, const char *pStartupInfo);
	void Cleanup();
  /* IVRSystem *vrsystem;
  IVRCompositor *vrcompositor;
  FnProxy &fnp;
  
  Microsoft::WRL::ComPtr<ID3D11Device> device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
  ID3D11Texture2D *shTexLeft = nullptr;
  ID3D11Texture2D *shTexRight = nullptr;
  ID3D11Texture2D *shTexLeftOld = nullptr;
  ID3D11Texture2D *shTexRightOld = nullptr;
  ID3D11Texture2D *shTexLeft2 = nullptr;
  ID3D11Texture2D *shTexRight2 = nullptr;
  HANDLE hDevice = NULL;
  HANDLE shTexInLeftObjectHandle = NULL;
  HANDLE shTexInRightObjectHandle = NULL;
  HANDLE shTexOutLeftObjectHandle = NULL;
  HANDLE shTexOutRightObjectHandle = NULL;
  GLuint shFboLeft = 0;
  GLuint shFboRight = 0;
  GLuint shTexInLeft = 0;
  GLuint shTexInRight = 0;
  GLuint shFboId = 0;
  GLuint shVaoId = 0;
  HANDLE shTexLeftHandle = 0;
  HANDLE shTexRightHandle = 0;
  
  HANDLE handleLeftLatched = nullptr;
  HANDLE handleRightLatched = nullptr;
  ID3D11Texture2D *texLeftLatched = nullptr;
  ID3D11Texture2D *texRightLatched = nullptr;
  
  GLFWwindow *subWindow = nullptr;

  PVRCompositor(IVRSystem *vrsystem, IVRCompositor *vrcompositor, FnProxy &fnp);
	virtual void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ); */
};
}

#endif