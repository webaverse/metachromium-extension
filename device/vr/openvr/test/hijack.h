#ifndef _hijack_h_
#define _hijack_h_

#include "device/vr/openvr/test/fnproxy.h"

class ProxyTexture {
public:
  void *texHandle;
  std::tuple<float, float, float, float> zBufferParams;
};

class Hijacker {
public:
  FnProxy fnp;
  bool hijacked = false;
  bool hijackedGl = false;
  
  Hijacker(FnProxy &fnp);

  // static void ensureClientDevice();
  void hijackDx(ID3D11DeviceContext *context);
  void hijackGl();
  ProxyTexture getDepthTextureMatching(ID3D11Texture2D *tex);
  void flushTextureLatches();
};

#endif