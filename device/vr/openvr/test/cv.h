#ifndef _test_cv_h_
#define _test_cv_h_

#include <stdlib.h>
#include <windows.h>

#include "device/vr/openvr/test/out.h"
#include "device/vr/openvr/test/compositorproxy.h"

#include <opencv2/core/core.hpp>
// #include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

// using namespace cv;

class CvEngine {
public:
  vr::PVRCompositor *pvrcompositor;
  vr::IVRSystem *vrsystem;

  ID3D11Device5 *cvDevice = nullptr;
  ID3D11DeviceContext4 *cvContext = nullptr;
  IDXGISwapChain *cvSwapChain = nullptr;
  ID3D11InfoQueue *cvInfoQueue = nullptr;

  Mutex mut;
  Semaphore sem;
  bool running = false;
  ID3D11Texture2D *colorReadTex = nullptr;
  D3D11_TEXTURE2D_DESC colorBufferDesc{};
  ID3D11Texture2D *colorMirrorClientTex = nullptr;
  ID3D11Texture2D *colorMirrorServerTex = nullptr;
  ID3D11Fence *fence = nullptr;
  size_t fenceValue = 0;

  uint32_t eyeWidth = 0;
  uint32_t eyeHeight = 0;
  float viewMatrixInverse[16] = {};
  float stageMatrixInverse[16] = {};
  float projectionMatrixInverse[16] = {};
  std::vector<float> features;

public:
  CvEngine(vr::PVRCompositor *pvrcompositor, vr::IVRSystem *vrsystem);
  void setEnabled(bool enabled);
  void getFeatures(std::function<void(const std::vector<float> &)> cb);
  void InfoQueueLog();
};

#endif