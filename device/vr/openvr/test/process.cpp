#include <iostream>
#include <fstream>
// #include <chrono>
#include <thread>
#include <algorithm>
#include <Windows.h>

#include "device/vr/openvr/test/fnproxy.h"

char lol[] = "lol";
char lol2[] = "lol2";
std::string dllDir("C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\");
std::ofstream out;
std::ostream &getOut() {
  if (!out.is_open()) {
    std::string logPath = dllDir + "log.txt";
    out.open(logPath.c_str(), std::ofstream::out|std::ofstream::app|std::ofstream::binary);
    out << "--------------------------------------------------------------------------------" << std::endl;
  }
  return std::cout;
  // return out;
}

int main() {
  int *p = (int *)allocateShared("Local\\OpenVrProxyLol", 4096);
  p[0] = 7;
  getOut() << "init thread 1" << std::endl;
  FnProxy fnp;
  getOut() << "init thread 2" << std::endl;
  fnp.reg<lol, std::string, std::string>([](std::string s) -> std::string {
    getOut() << "fn 1" << std::endl;
    return s + " concat 1";
  });
  getOut() << "init thread 3" << std::endl;
  bool done = false;
  fnp.reg<lol2, std::string, std::string>([&](std::string s) -> std::string {
    // done = true;
    getOut() << "fn 2" << std::endl;
    return s + " concat 2";
  });
  getOut() << "init thread 4" << std::endl;
  while (!done) {
    getOut() << "init thread tick 1" << std::endl;
    fnp.handle();
    getOut() << "init thread tick 2" << std::endl;
  }
  getOut() << "init thread 5" << std::endl;
  
  return 0;
}