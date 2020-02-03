#include "qr.h"

using namespace cv;

QrEngine::QrEngine() :
  qrDecoder(QRCodeDetector::QRCodeDetector())
{
  getOut() << "qr cons 1" << std::endl;
  vr::PVRCompositor::CreateDevice(&qrDevice, &qrContext, &qrSwapChain);
  getOut() << "qr cons 2" << std::endl;
  
  HRESULT hr = qrDevice->QueryInterface(__uuidof(ID3D11InfoQueue), (void **)&qrInfoQueue);
  if (SUCCEEDED(hr)) {
    qrInfoQueue->PushEmptyStorageFilter();
  } else {
    getOut() << "info queue query failed" << std::endl;
    // abort();
  }

  std::thread([this]() -> void {
    for (;;) {
      getOut() << "thread 1" << std::endl;
      
      sem.lock();
      
      getOut() << "thread 2" << std::endl;

      Mat inputImage(colorBufferDesc.Width, colorBufferDesc.Height, CV_8UC4);
      
      getOut() << "thread 3" << std::endl;

      qrContext->Wait(fence, fenceValue);
      D3D11_MAPPED_SUBRESOURCE subresource;
      HRESULT hr = qrContext->Map(
        colorServerBufferTex,
        0,
        D3D11_MAP_READ,
        0,
        &subresource
      );
      
      getOut() << "thread 4" << std::endl;

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
      
      getOut() << "thread 5" << std::endl;

      qrContext->Unmap(
        colorServerBufferTex,
        0
      );
      
      getOut() << "thread 6" << std::endl;

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
      
      getOut() << "thread 7" << std::endl;

      running = false;
    }
  }).detach();
}
void QrEngine::registerCallback(vr::PVRCompositor *pvrcompositor) {
  pvrcompositor->submitCallbacks.push_back([this](ID3D11Device5 *device, ID3D11DeviceContext4 *context, ID3D11Texture2D *colorTex, ID3D11Texture2D *depthTex) -> void {
    getOut() << "cb 1" << std::endl;

    if (!running) {
      running = true;

      getOut() << "cb 2" << std::endl;

      D3D11_TEXTURE2D_DESC desc;
      colorTex->GetDesc(&desc);
      
      getOut() << "cb 3" << std::endl;

      HRESULT hr;
      if (!colorClientBufferTex || desc.Width != colorBufferDesc.Width || desc.Height != colorBufferDesc.Height) {
        getOut() << "cb 4" << std::endl;
        
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
          getOut() << "failed to create color buffer shared texture: " << (void *)hr << std::endl;
          InfoQueueLog();
          abort();
        }

        IDXGIResource *colorClientShRes;
        hr = colorClientBufferTex->QueryInterface(__uuidof(IDXGIResource), (void**)&colorClientShRes); 
        if (FAILED(hr)) {
          getOut() << "failed to query color buffer shared resource: " << (void *)hr << std::endl;
          abort();
        }

        hr = colorClientShRes->GetSharedHandle(&colorClientBufferHandle);
        if (FAILED(hr)) {
          getOut() << "failed to get color buffer share handle: " << (void *)hr << " " << (void *)colorClientShRes << std::endl;
          InfoQueueLog();
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
        
        getOut() << "cb 5" << std::endl;
      }
      
      getOut() << "cb 6" << std::endl;

      context->CopyResource(
        colorClientBufferTex,
        colorTex
      );
      
      getOut() << "cb 7" << std::endl;
      
      ++fenceValue;
      context->Signal(fence, fenceValue);

      getOut() << "cb 8" << std::endl;

      sem.unlock();
      
      getOut() << "cb 9" << std::endl;
    }
  });
}
void QrEngine::InfoQueueLog() {
  if (qrInfoQueue) {
    vr::PVRCompositor::InfoQueueLog(qrInfoQueue);
  }
}