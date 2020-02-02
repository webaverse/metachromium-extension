#include "qr.h"
#include <iostream>

using namespace cv;

void detectQrCodes() {
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  std::string qrPngPath = cwdBuf;
  qrPngPath += R"EOF(\..\..\..\..\..\qr.png)EOF";
  getOut() << "read qr code image 1 " << qrPngPath << std::endl;
  Mat inputImage = imread(qrPngPath, CV_LOAD_IMAGE_COLOR);
  getOut() << "read qr code image 2" << std::endl;

  QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();
 
  Mat bbox, rectifiedImage;
 
  std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
  if(data.length()>0)
  {
    std::cout << "Decoded Data : " << data << std::endl;
 
    // display(inputImage, bbox);
    // rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
    // imshow("Rectified QRCode", rectifiedImage);
  } else {
    std::cout << "QR Code not detected" << std::endl;
  }
}