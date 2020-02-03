#include "qr.h"

using namespace cv;

QrEngine::QrEngine() :
  qrDecoder(QRCodeDetector::QRCodeDetector())
{
  vr::PVRCompositor::CreateDevice(&qrDevice, &qrContext, &qrSwapChain);
  
  std::thread([this]() -> void {
    for (;;) {
      sem.lock();

      Mat inputImage(colorBufferDesc.Width, colorBufferDesc.Height, CV_8UC4);

      qrContext->Wait(fence, fenceValue);
      D3D11_MAPPED_SUBRESOURCE subresource;
      HRESULT hr = qrContext->Map(
        colorServerBufferTex,
        0,
        D3D11_MAP_READ,
        0,
        &subresource
      );

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

      memcpy(inputImage.ptr(), subresource.pData, colorBufferDesc.Width * colorBufferDesc.Height * 4);

      qrContext->Unmap(
        colorServerBufferTex,
        0
      );

      Mat bbox, rectifiedImage;
     
      std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
      if(data.length() > 0) {
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

      D3D11_TEXTURE2D_DESC desc;
      colorTex->GetDesc(&desc);

      HRESULT hr;
      if (!colorClientBufferTex || desc.Width != colorBufferDesc.Width || desc.Height != colorBufferDesc.Height) {
        desc.Usage = D3D11_USAGE_STAGING;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
        colorBufferDesc = desc;

        hr = device->CreateTexture2D(
          &colorBufferDesc,
          NULL,
          &colorClientBufferTex
        );
        if (FAILED(hr)) {
          getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
          // InfoQueueLog();
          abort();
        }

        IDXGIResource *colorClientShRes;
        hr = colorClientBufferTex->QueryInterface(__uuidof(IDXGIResource), (void**)&colorClientShRes); 
        if (FAILED(hr)) {
          getOut() << "failed to query color client shared resource: " << (void *)hr << std::endl;
          abort();
        }

        hr = colorClientShRes->GetSharedHandle(&colorClientBufferHandle);
        if (FAILED(hr)) {
          getOut() << "failed to get color buffer shared texture: " << (void *)hr << " " << (void *)colorClientShRes << std::endl;
          // InfoQueueLog();
          abort();
        }
        
        IDXGIResource *colorServerShRes;
        HRESULT hr = qrDevice->OpenSharedResource(colorClientBufferHandle, __uuidof(IDXGIResource), (void**)&colorServerShRes);
        if (FAILED(hr)) {
          getOut() << "failed to unpack color server shared texture handle: " << (void *)hr << " " << (void *)colorClientBufferHandle << std::endl;
          abort();
        }

        hr = colorServerShRes->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&colorServerBufferTex); 
        if (FAILED(hr)) {
          getOut() << "failed to unpack color server shared texture: " << (void *)hr << " " << (void *)colorServerShRes << std::endl;
          abort();
        }
        
        hr = device->CreateFence(
          0, // value
          D3D11_FENCE_FLAG_SHARED, // flags
          __uuidof(ID3D11Fence), // interface
          (void **)&fence // out
        );
        if (FAILED(hr)) {
          getOut() << "failed to create color buffer fence" << std::endl;
          abort();
        }

        colorClientShRes->Release();
        colorServerShRes->Release();
      }

      context->CopyResource(
        colorClientBufferTex,
        colorTex
      );
      
      ++fenceValue;
      context->Signal(fence, fenceValue);

      sem.unlock();
    }
  });
}