#include "device/vr/openvr/test/out.h"

std::ostream &getOut() {
  if (!out.is_open()) {
    std::string logPath = dllDir + "log.txt";
    out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return out;
}