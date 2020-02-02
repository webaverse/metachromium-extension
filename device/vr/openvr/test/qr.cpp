#include "qr.h"

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
  Mat inputImage = imread(qrPngPath, IMREAD_COLOR);
  getOut() << "read qr code image 2" << std::endl;

  QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();
 
  Mat bbox, rectifiedImage;
 
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
}