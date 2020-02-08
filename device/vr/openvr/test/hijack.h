#ifndef _hijack_h_
#define _hijack_h_

#include "device/vr/openvr/test/fnproxy.h"

/* class ProxyTexture {
public:
  void *texHandle;
  std::tuple<float, float> zBufferParams;
  int eye;
  bool isFull;
}; */

class IDCompositionDesktopDevice;
class IDCompositionTarget;

class Hijacker {
public:
  FnProxy fnp;
  // bool hijackedPre = false;
  bool hijackedDxgi = false;
  bool hijackedDx = false;
  bool hijackedGl = false;
  
  Hijacker(FnProxy &fnp);

  // static void ensureClientDevice();
  void hijackPre();
  void hijackDxgi(HINSTANCE hinstDLL);
  void unhijackDxgi();
  void hijackDx(ID3D11DeviceContext *context);
  void unhijackDx();
  void hijackGl();
  void unhijackGl();
};

#endif