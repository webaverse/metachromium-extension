#include "qr.h"
#include <iostream>

using namespace cv;

void detectQrCodes() {
  Mat inputImage(1024, 1024, CV_8U);
 
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