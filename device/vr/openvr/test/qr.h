#ifndef _test_qr_h_
#define _test_qr_h_

#include <stdlib.h>
#include <windows.h>

#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/compositorproxy.h"

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>

class QrEngine {
public:
  Semaphore sem;
  bool running;
  ID3D11Texture2D *colorBufferTex;
  QRCodeDetector qrDecoder;

  QrEngine() {}
  void registerCallback(vr::PVRCompositor *pvrcompositor);
};

#endif