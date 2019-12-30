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
  getOut() << "init dll 2.0 " << (void *)p << std::endl;
  getOut() << "init dll 2.1 " << p[0] << std::endl;
  
  FnProxy fnp2;

  /* STARTUPINFO si;
  PROCESS_INFORMATION pi;
  
  bool started = CreateProcess(NULL,   // No module name (use command line)
      processExe,        // Command line
      NULL,           // Process handle not inheritable
      NULL,           // Thread handle not inheritable
      FALSE,          // Set handle inheritance to FALSE
      NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,              // No creation flags
      NULL,           // Use parent's environment block
      NULL,           // Use parent's starting directory 
      &si,            // Pointer to STARTUPINFO structure
      &pi );          // Pointer to PROCESS_INFORMATION structure */

  // getOut() << "init dll 3 " << (int)started << (void *)GetLastError() << std::endl;
  getOut() << "init dll 4" << std::endl;
  fnp2.call<lol, std::string>(std::string("woot 1"));
  fnp2.call<lol, std::string>(std::string("woot 2"));
  std::string woot3 = fnp2.call<lol2, std::string, std::string>(std::string("woot 3"));
  getOut() << "init dll 5" << woot3 << std::endl;

  getOut() << "init dll 6" << woot3 << std::endl;
  /* std::string woot("lol");
  int i = 7;
  std::string woot2;
  int i2;
  out(woot, i);
  in(woot2, i2);
  
  getOut() << "got data " << woot2 << " " << i2 << std::endl; */
  
  return 0;
}