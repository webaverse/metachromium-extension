// #include <windows.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <io.h>
#include <iostream>
// #include <fstream>

// #define CINTERFACE
// #define D3D11_NO_HELPERS
#include <windows.h>
// #include <D3D11_4.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

// #include "device/vr/detours/detours.h"
#include "extension/json.hpp"

#include "device/vr/openvr/test/out.h"
// #include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
// #include "device/vr/openvr/test/fake_openvr_impl_api.h"

using json = nlohmann::json;

std::string logSuffix = "_native";
HWND g_hWnd = NULL;
// CHAR s_szDllPath[MAX_PATH] = "vrclient_x64.dll";
extern std::string dllDir;

int main(int argc, char **argv) {
  freopen(NULL, "rb", stdin);
  freopen(NULL, "wb", stdout);
  
  dllDir = "C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\";
  std::cerr << "start app" << std::endl;
  getOut() << "start app" << std::endl;
  for (;;) {
    uint32_t size;
    std::cin.read((char *)&size, sizeof(uint32_t));
    // getOut() << "start app 2 " << size << " " << std::cin.good() << " " << std::cin.bad() << " " << std::cin.fail() << " " << std::cin.eof() << std::endl;
    if (std::cin.good()) {
      // getOut() << "start app 3 " << size << std::endl;
      std::vector<uint8_t> readbuf(size);
      std::cin.read((char *)readbuf.data(), readbuf.size());
      // getOut() << "start app 4" << std::endl;
      if (std::cin.good()) {
        // getOut() << "start app 5" << std::endl;
        json req = json::parse(readbuf);
        // getOut() << "start app 6 " << req.size() << std::endl;
        json method;
        json args;
        for (json::iterator it = req.begin(); it != req.end(); ++it) {
          // getOut() << it.key() << " " << it.value() << std::endl;
          if (it.key() == "method") {
            method = it.value();
          } else if (it.key() == "args") {
            args = it.value();
          }
        }
        
        if (method.is_string() && args.is_array()) {
          const std::string methodString = method.get<std::string>();
          getOut() << "method: " << methodString << std::endl;

          int i = 0;
          for (json::iterator it = args.begin(); it != args.end(); ++it) {
            const std::string argString = it->get<std::string>();
            getOut() << "arg " << i << ": " << argString << std::endl;
            i++;
          }
        }

        json res = {
          {"error", nullptr},
          {"result", "zol"}
        };
        // getOut() << "start app 9" << std::endl;
        std::string outString = res.dump();
        // getOut() << "start app 10" << std::endl;
        
        uint32_t outSize = (uint32_t)outString.size();
        std::cout.write((char *)&outSize, sizeof(uint32_t));
        std::cout.write(outString.data(), outString.size());
        // getOut() << "start app 11" << std::endl;
      } /* else {
        getOut() << "got eof" << std::endl;
      } */
    } else {
      // getOut() << "got eof" << std::endl;
      break;
    }
  }
}