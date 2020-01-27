// #include <windows.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <io.h>
// #include <iostream>
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

int main(int argc, char **argv) {
  for (;;) {
    uint32_t size;
    std::cin >> size;
    if (std::cin.good()) {
      std::vector<uint8_t> readbuf(size);
      std::cin.read((char *)readbuf.data(), readbuf.size());
      if (std::cin.good()) {
        json req = json.parse(readbuf);
        const std::string method = req["method"].get<std::string>();
        auto args = req["args"];

        json res = {
          {"error", nullptr},
          {"result", "zol"}
        };
        std::string outString = j.dump();
        std::cout << (uint32_t)outString.size() << outString;
      } else {
        std::cerr << "got eof" << std::endl;
      }
    } else {
      std::cerr << "got eof" << std::endl;
      break;
    }
  }
}