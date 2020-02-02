#include "qr.h"

using namespace cv;

QrEngine::QrEngine() :
  running(false),
  colorBufferTex(nullptr),
  qrDecoder(QRCodeDetector::QRCodeDetector())
{
  std::thread([this]() -> void {
    for (;;) {
      sem.lock();

      /* char cwdBuf[MAX_PATH];
      if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
        getOut() << "failed to get current directory" << std::endl;
        abort();
      }
      std::string qrPngPath = cwdBuf;
      qrPngPath += R"EOF(\..\..\..\..\..\qr.png)EOF";
      getOut() << "read qr code image 1 " << qrPngPath << std::endl;
      Mat inputImage = imread(qrPngPath, IMREAD_COLOR);
      getOut() << "read qr code image 2" << std::endl; */

      Mat inputImage, bbox, rectifiedImage;
     
      std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
      if(data.length() > 0)
      {
        if (bbox.type() == CV_32FC2 && bbox.rows == 4 && bbox.cols == 1) {
          Point2f points[4] = {
            bbox.at<Point2f>(0),
            bbox.at<Point2f>(1),
            bbox.at<Point2f>(2),
            bbox.at<Point2f>(3),
          };
          getOut() << "Decoded Data : " << data << " " <<
            points[0].x << " " << points[0].y << " " <<
            points[1].x << " " << points[1].y << " " <<
            points[2].x << " " << points[2].y << " " <<
            points[3].x << " " << points[3].y << " " <<
            std::endl;
        } else {
          getOut() << "unknown qr code type: " << bbox.type() << std::endl;
        }
      } else {
        getOut() << "QR Code not detected" << std::endl;
      }

      running = false;
    }
  }).detach();
}
void QrEngine::registerCallback(vr::PVRCompositor *pvrcompositor) {
  pvrcompositor->submitCallbacks.push_back([this](ID3D11Device5 *device, ID3D11DeviceContext4 *context, ID3D11Texture2D *colorTex, ID3D11Texture2D *depthTex) -> void {
    if (!running) {
      running = true;

      HRESULT hr;
      if (!colorBufferTex) {
        D3D11_TEXTURE2D_DESC desc;
        colorTex->GetDesc(&desc);

        hr = device->CreateTexture2D(
          &desc,
          NULL,
          &colorBufferTex
        );
        if (FAILED(hr)) {
          getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
          InfoQueueLog();
          abort();
        }
      }

      context->CopyResource(
        colorBufferTex,
        colorTex
      );

      sem->unlock();
    }
  });
}