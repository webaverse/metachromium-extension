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
  ID3D11Device5 *qrDevice = nullptr;
  ID3D11DeviceContext4 *qrContext = nullptr;
  IDXGISwapChain *qrSwapChain = nullptr;
  ID3D11InfoQueue *qrInfoQueue = nullptr;

  Semaphore sem;
  bool running = false;
  ID3D11Texture2D *colorReadTex = nullptr;
  D3D11_TEXTURE2D_DESC colorBufferDesc{};
  ID3D11Texture2D *colorMirrorClientTex = nullptr;
  ID3D11Texture2D *colorMirrorServerTex = nullptr;
  ID3D11Fence *fence = nullptr;
  size_t fenceValue = 0;
  cv::QRCodeDetector qrDecoder;

  QrEngine();
  void registerCallback(vr::PVRCompositor *pvrcompositor);
  void InfoQueueLog();
};

#endif