// #include <windows.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <io.h>
#include <iostream>
#include <filesystem>

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
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

using json = nlohmann::json;

std::string logSuffix = "_native";
HWND g_hWnd = NULL;
// CHAR s_szDllPath[MAX_PATH] = "vrclient_x64.dll";
extern std::string dllDir;

void respond(const json &j) {
  std::string outString = j.dump();
  // getOut() << "start app 10" << std::endl;
  
  uint32_t outSize = (uint32_t)outString.size();
  std::cout.write((char *)&outSize, sizeof(uint32_t));
  std::cout.write(outString.data(), outString.size());
}

int main(int argc, char **argv) {
  freopen(NULL, "rb", stdin);
  freopen(NULL, "wb", stdout);
  
  // dllDir = "C:\\Users\\avaer\\Documents\\GitHub\\chromium-79.0.3945.88\\device\\vr\\build\\mock_vr_clients\\bin\\";
  std::cerr << "start app" << std::endl;
  // getOut() << "start app" << std::endl;
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

          /* int i = 0;
          for (json::iterator it = args.begin(); it != args.end(); ++it) {
            const std::string argString = it->get<std::string>();
            getOut() << "arg " << i << ": " << argString << std::endl;
            i++;
          } */
          if (methodString == "launchApp" && args.size() > 0 && args[0].is_string()) {
            std::string argString = args[0].get<std::string>();

            char envBuf[64 * 1024];
            getChildEnvBuf(envBuf);
            
            std::vector<char> argVec(argString.size() + 1);
            memcpy(argVec.data(), argString.c_str(), argString.size() + 1);

            STARTUPINFO si{};
            PROCESS_INFORMATION pi{};
            if (CreateProcessA(
              NULL,
              argVec.data(),
              NULL,
              NULL,
              false,
              0,
              envBuf,
              NULL,
              &si,
              &pi
            )) {
              int processId = pi.dwProcessId;
              getOut() << "launch ok: " << argString << " " << processId << std::endl;

              json result = {
                {"processId", processId}
              };
              json res = {
                {"error", nullptr},
                {"result", result}
              };
              respond(res);
            } else {
              getOut() << "launch failed: " << argString << " " << (void *)GetLastError() << std::endl;

              json res = {
                {"error", "launch failed"},
                {"result", nullptr}
              };
              respond(res);
            }
          } else if (methodString == "listSteamApps") {
            const std::string path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\";
            std::vector<std::string> executables; 
            for (const auto &appDirEntry : std::filesystem::directory_iterator(path)) {
              if (appDirEntry.is_directory()) {
                const auto &appDirName = appDirEntry.path().filename().string();
                for (const auto &appFileEntry : std::filesystem::directory_iterator(appDirEntry.path())) {
                  if (appFileEntry.path().extension().string() == ".exe") {
                    const auto &appFileName = appFileEntry.path().filename().string();
                    size_t count = 0;
                    for (size_t i = 0; i < appDirName.size() && i < appFileName.size(); i++) {
                      if (appDirName[i] == appFileName[i]) {
                        count++;
                      } else {
                        break;
                      }
                    }
                    if (count >= 2) {
                      getOut() << "check executable " << appDirName << " " << appFileName << " " << count << std::endl;
                      executables.push_back(appFileEntry.path().string());
                    }
                  }
                }
              }
            }
            json array = json::array();
            for (size_t i = 0; i < executables.size(); i++) {
              getOut() << "got executable " << executables[i] << std::endl;
              array.push_back(executables[i]);
            }
            json res = {
              {"error", nullptr},
              {"result", array}
            };
            respond(res);
          } else if (methodString == "killApp" && args.size() > 0 && args[0].is_number()) {
            int processId = args[0].get<int>();

            HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
            TerminateProcess(processHandle, 1);
            CloseHandle(processHandle);

            json res = {
              {"error", nullptr},
              {"result", "ok"}
            };
            respond(res);
          } else {
            json res = {
              {"error", "invalid method"},
              {"result", nullptr}
            };
            respond(res);
          }
        } else {
          json res = {
            {"error", nullptr},
            {"result", "pong"}
          };
          respond(res);
        }
      } else {
        break;
      }
    } else {
      // getOut() << "got eof" << std::endl;
      break;
    }
  }
}