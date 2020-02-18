#include "cv.h"
#include "matrix.h"

CvEngine::CvEngine(vr::PVRCompositor *pvrcompositor, vr::IVRSystem *vrsystem) :
  pvrcompositor(pvrcompositor),
  vrsystem(vrsystem)
{
  // getOut() << "cv cons 1" << std::endl;
  vr::PVRCompositor::CreateDevice(&cvDevice, &cvContext, &cvSwapChain);
  // getOut() << "cv cons 2" << std::endl;

  HRESULT hr = cvDevice->QueryInterface(__uuidof(ID3D11InfoQueue), (void **)&cvInfoQueue);
  if (SUCCEEDED(hr)) {
    cvInfoQueue->PushEmptyStorageFilter();
  } else {
    getOut() << "info queue query failed" << std::endl;
    // abort();
  }

  std::thread([this]() -> void {
    try {
      // getOut() << "thread 1" << std::endl;

      cv::Ptr<cv::ORB> orb = cv::ORB::create();
      cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
      
      // getOut() << "thread 2" << std::endl;

      // getOut() << "thread 3" << std::endl;

      for (;;) {
        // getOut() << "loop 1" << std::endl;
        
        sem.lock();
        
        // getOut() << "loop 2" << std::endl;

        cv::Mat inputImage(colorBufferDesc.Height, colorBufferDesc.Width, CV_8UC4);
        
        // getOut() << "loop 3" << std::endl;

        cvContext->Wait(fence, fenceValue);
        
        // getOut() << "loop 4" << std::endl;
        
        cvContext->CopyResource(
          colorReadTex,
          colorMirrorServerTex
        );
        
        // getOut() << "loop 5" << std::endl;
        
        D3D11_MAPPED_SUBRESOURCE resource;
        HRESULT hr = cvContext->Map(
          colorReadTex,
          0,
          D3D11_MAP_READ,
          0,
          &resource
        );
        if (FAILED(hr)) {
          getOut() << "failed to map read texture: " << (void *)hr << std::endl;
          InfoQueueLog();
          abort();
        }

        // getOut() << "loop 6 " << colorBufferDesc.Width << " " << (void *)resource.pData << " " << resource.RowPitch << " " << resource.DepthPitch << " " << (inputImage.total() * inputImage.elemSize()) << " " << (colorBufferDesc.Width * colorBufferDesc.Height * 4) << std::endl;

        UINT lBmpRowPitch = colorBufferDesc.Width * 4;
        BYTE *sptr = reinterpret_cast<BYTE *>(resource.pData);
        BYTE *dptr = (BYTE *)inputImage.ptr(); // + (lBmpRowPitch * colorBufferDesc.Height) - lBmpRowPitch;
        for (size_t h = 0; h < colorBufferDesc.Height; ++h) {
          memcpy(dptr, sptr, lBmpRowPitch);
          sptr += resource.RowPitch;
          // dptr -= lBmpRowPitch;
          dptr += lBmpRowPitch;
        }
        // memcpy(inputImage.ptr(), subresource.pData, colorBufferDesc.Width * colorBufferDesc.Height * 4);

        // getOut() << "thread 7" << std::endl;
        
        cv::Mat inputImage2;
        cv::cvtColor(inputImage, inputImage2, cv::COLOR_RGBA2GRAY);
        cv::Mat inputImage3;
        cv::resize(inputImage2, inputImage3, cv::Size(512, (float)512 * (float)inputImage2.rows / (float)inputImage2.cols), 0, 0, cv::INTER_CUBIC);

        // getOut() << "loop 7" << std::endl;

        cvContext->Unmap(colorReadTex, 0);
        
        // getOut() << "loop 8" << std::endl;

        std::vector<cv::KeyPoint> queryKeypoints;
        cv::Mat queryDescriptors;

        int minHessian = 400;
        cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create( minHessian );
        detector->detectAndCompute( inputImage2, cv::noArray(), queryKeypoints, queryDescriptors );
        // getOut() << "loop 11 " << feature.descriptors.rows << " " << feature.descriptors.cols << " " << feature.descriptors.total() << " " << feature.descriptors.elemSize() << " " << (feature.descriptors.total()*feature.descriptors.elemSize()) << std::endl;
        
        std::vector<cv::DMatch> matches;
        if (queryDescriptors.cols == feature.descriptors.cols) {
          std::vector< std::vector<cv::DMatch> > knn_matches;
          matcher->knnMatch( queryDescriptors, feature.descriptors, knn_matches, 2 );

          const float ratio_thresh = 0.7f;
          for (size_t i = 0; i < knn_matches.size(); i++) {
            if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance) {
              matches.push_back(knn_matches[i][0]);
            }
          }
        }

        if (matches.size() > 0) {
          getOut() << "matches yes " << queryDescriptors.cols << " " << feature.descriptors.cols << " " << matches.size() << std::endl;
        } else {
          getOut() << "matches no " << queryDescriptors.cols << " " << feature.descriptors.cols << " " << matches.size() << std::endl;
        }

        {
          std::lock_guard<Mutex> lock(mut);

          std::vector<float> queryPoints(matches.size() * 3);
          for (size_t i = 0; i < matches.size(); i++) {
            cv::DMatch &match = matches[i];
            int queryIdx = match.queryIdx;
            const cv::KeyPoint &keypoint = queryKeypoints[queryIdx];

            float worldPoint[4] = {
              (keypoint.pt.x/(float)eyeWidth) * 2.0f - 1.0f,
              (1.0f-(keypoint.pt.y/(float)eyeHeight)) * 2.0f - 1.0f,
              0.0f,
              1.0f,
            };
            applyVector4Matrix(worldPoint, projectionMatrixInverse);
            perspectiveDivideVector(worldPoint);
            applyVector4Matrix(worldPoint, viewMatrixInverse);
            applyVector4Matrix(worldPoint, stageMatrixInverse);

            queryPoints[i*3] = worldPoint[0];
            queryPoints[i*3+1] = worldPoint[1];
            queryPoints[i*3+2] = worldPoint[2];
          }
          std::vector<unsigned char> inputImageJpg;
          cv::imencode(".jpg", inputImage, inputImageJpg);
          feature = {
            (uint32_t)inputImage.cols,
            (uint32_t)inputImage.rows,
            std::move(inputImageJpg),
            std::move(queryDescriptors),
            std::move(queryPoints),
          };
        }

        getOut() << "feature set done" << std::endl;

        running = false;
      }
    } catch( cv::Exception& e ) {
      const char *err_msg = e.what();
      getOut() << "exception caught: " << err_msg << std::endl;
      abort();
    }
  }).detach();
}
void CvEngine::setEnabled(bool enabled) {
  pvrcompositor->submitCallbacks.push_back([this](ID3D11Device5 *device, ID3D11DeviceContext4 *context, ID3D11Texture2D *colorTex) -> void {
    // getOut() << "cb 1 " << running << std::endl;

    if (!running) {
      running = true;

      // getOut() << "cb 2" << std::endl;

      D3D11_TEXTURE2D_DESC desc;
      colorTex->GetDesc(&desc);

      // getOut() << "cb 3" << std::endl;

      HRESULT hr;
      if (!colorMirrorClientTex || desc.Width != colorBufferDesc.Width || desc.Height != colorBufferDesc.Height) {
        // getOut() << "cb 4" << std::endl;
        
        colorBufferDesc = desc;

        D3D11_TEXTURE2D_DESC mirrorDesc = desc;
        mirrorDesc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
        hr = device->CreateTexture2D(
          &colorBufferDesc,
          NULL,
          &colorMirrorClientTex
        );
        if (FAILED(hr)) {
          getOut() << "failed to create color mirror texture: " << (void *)hr << std::endl;
          this->pvrcompositor->InfoQueueLog();
          InfoQueueLog();
          abort();
        }

        D3D11_TEXTURE2D_DESC readDesc = desc;
        readDesc.Usage = D3D11_USAGE_STAGING;
        readDesc.BindFlags = 0;
        readDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        readDesc.MiscFlags = 0;
        hr = cvDevice->CreateTexture2D(
          &readDesc,
          NULL,
          &colorReadTex
        );
        if (FAILED(hr)) {
          getOut() << "failed to create color read texture: " << (void *)hr << std::endl;
          this->pvrcompositor->InfoQueueLog();
          InfoQueueLog();
          abort();
        }

        IDXGIResource *colorMirrorClientRes;
        hr = colorMirrorClientTex->QueryInterface(__uuidof(IDXGIResource), (void**)&colorMirrorClientRes); 
        if (FAILED(hr)) {
          getOut() << "failed to query color buffer shared resource: " << (void *)hr << std::endl;
          abort();
        }

        HANDLE colorMirrorHandle = NULL;
        hr = colorMirrorClientRes->GetSharedHandle(&colorMirrorHandle);
        if (FAILED(hr)) {
          getOut() << "failed to get color buffer share handle: " << (void *)hr << " " << (void *)colorMirrorClientRes << std::endl;
          this->pvrcompositor->InfoQueueLog();
          InfoQueueLog();
          abort();
        }
        
        IDXGIResource *colorMirrorServerRes;
        HRESULT hr = cvDevice->OpenSharedResource(colorMirrorHandle, __uuidof(IDXGIResource), (void**)&colorMirrorServerRes);
        if (FAILED(hr)) {
          getOut() << "failed to unpack color server shared texture handle: " << (void *)hr << " " << (void *)colorMirrorHandle << std::endl;
          abort();
        }

        hr = colorMirrorServerRes->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&colorMirrorServerTex); 
        if (FAILED(hr)) {
          getOut() << "failed to unpack color server shared texture: " << (void *)hr << " " << (void *)colorMirrorServerRes << std::endl;
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

        colorMirrorClientRes->Release();
        colorMirrorServerRes->Release();
        
        // getOut() << "cb 5" << std::endl;
      }
      
      // getOut() << "cb 6" << std::endl;

      context->CopyResource(
        colorMirrorClientTex,
        colorTex
      );
      
      // getOut() << "cb 7" << std::endl;
      
      ++fenceValue;
      context->Signal(fence, fenceValue);

      eyeWidth = pvrcompositor->width;
      eyeHeight = pvrcompositor->height;
      vr::HmdMatrix34_t viewMatrixHmd = pvrcompositor->GetViewMatrix();
      // float viewMatrix[16];
      setPoseMatrix(viewMatrixInverse, viewMatrixHmd);
      // getMatrixInverse(viewMatrix, viewMatrixInverse);

      vr::HmdMatrix34_t stageMatrixHmd = pvrcompositor->GetStageMatrix();
      // float stageMatrix[16];
      setPoseMatrix(stageMatrixInverse, stageMatrixHmd);
      // getMatrixInverse(stageMatrix, stageMatrixInverse);

      vr::HmdMatrix44_t projectionMatrixHmd = pvrcompositor->GetProjectionMatrix();
      float projectionMatrix[16];
      setPoseMatrix(projectionMatrix, projectionMatrixHmd);
      getMatrixInverse(projectionMatrix, projectionMatrixInverse);

      // getOut() << "cb 8" << std::endl;

      sem.unlock();
      
      // getOut() << "cb 9" << std::endl;
    }
  });
}
void CvEngine::getFeatures(std::function<void(const CvFeature &)> cb) {
  std::lock_guard<Mutex> lock(mut);
  // getOut() << "get feature " << feature.points.size() << std::endl;
  cb(feature);
}
void CvEngine::addFeature(int rows, int cols, int type, const managed_binary<char> &data) {
  std::lock_guard<Mutex> lock(mut);
  cv::Mat descriptor(rows, cols, type);
  memcpy(descriptor.ptr(), data.data(), data.size());
  matchDescriptors.push_back(std::move(descriptor));
}
void CvEngine::InfoQueueLog() {
  if (cvInfoQueue) {
    vr::PVRCompositor::InfoQueueLog(cvInfoQueue);
  }
}