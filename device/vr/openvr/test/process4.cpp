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

char kProcess_SetIsVr[] = "IVRCompositor::kIVRCompositor_SetIsVr";
char kProcess_SetTransform[] = "IVRCompositor::kIVRCompositor_SetTransform";
char kProcess_PrepareBindSurface[] = "IVRCompositor::kIVRCompositor_PrepareBindSurface";
char kProcess_SendMouse[] = "IVRCompositor::kIVRCompositor_SendMouse";
char kProcess_SetDepthRenderEnabled[] = "IVRCompositor::kIVRCompositor_SetDepthRenderEnabled";
char kProcess_SetQrEngineEnabled[] = "IVRCompositor::kIVRCompositor_SetQrEngineEnabled";
char kProcess_GetQrCodes[] = "IVRCompositor::GetQrCodes";

void respond(const json &j) {
  std::string outString = j.dump();
  // getOut() << "start app 10" << std::endl;
  
  uint32_t outSize = (uint32_t)outString.size();
  std::cout.write((char *)&outSize, sizeof(uint32_t));
  std::cout.write(outString.data(), outString.size());
}

int main(int argc, char **argv) {
  g_fnp = new FnProxy();

  freopen(NULL, "rb", stdin);
  freopen(NULL, "wb", stdout);

  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(
    sizeof(cwdBuf),
    cwdBuf
  )) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  std::string baseDir = cwdBuf;
  baseDir += R"EOF(\..\..\..\..\..)EOF";
  // getOut() << "got base dir " << baseDir << std::endl;
  
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
            getChildEnvBuf(envBuf, baseDir);

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
          } else if (
            methodString == "setIsVr" &&
            args.size() >= 1 && args[0].is_boolean()
          ) {
            const bool isVr = args[0].get<bool>();

            auto result = g_fnp->call<
              kProcess_SetIsVr,
              int,
              bool
            >(isVr);

            json res = {
              {"error", nullptr},
              {"result", "ok"}
            };
            respond(res);
          } else if (
            methodString == "setTransform" &&
            args.size() >= 3 &&
            args[0].is_array() && args[0].size() >= 3 && args[0][0].is_number() && args[0][1].is_number() && args[0][2].is_number() &&
            args[1].is_array() && args[1].size() >= 3 && args[1][0].is_number() && args[1][1].is_number() && args[1][2].is_number() && args[1][3].is_number() &&
            args[2].is_array() && args[2].size() >= 3 && args[2][0].is_number() && args[2][1].is_number() && args[2][2].is_number()
          ) {
            managed_binary<float> position(3);
            float *positionData = (float *)position.data();
            positionData[0] = args[0][0].get<float>();
            positionData[1] = args[0][1].get<float>();
            positionData[2] = args[0][2].get<float>();

            managed_binary<float> quaternion(4);
            float *quaternionData = (float *)quaternion.data();
            quaternionData[0] = args[1][0].get<float>();
            quaternionData[1] = args[1][1].get<float>();
            quaternionData[2] = args[1][2].get<float>();
            quaternionData[3] = args[1][3].get<float>();

            managed_binary<float> scale(3);
            float *scaleData = (float *)scale.data();
            scaleData[0] = args[2][0].get<float>();
            scaleData[1] = args[2][1].get<float>();
            scaleData[2] = args[2][2].get<float>();

            auto result = g_fnp->call<
              kProcess_SetTransform,
              int,
              managed_binary<float>,
              managed_binary<float>,
              managed_binary<float>
            >(std::move(position), std::move(quaternion), std::move(scale));

            json res = {
              {"error", nullptr},
              {"result", "ok"}
            };
            respond(res);
          } else if (
            methodString == "prepareBindSurface"
          ) {
            auto desc = g_fnp->call<
              kProcess_PrepareBindSurface,
              D3D11_TEXTURE2D_DESC
            >();

            if (desc.Width > 0 && desc.Height > 0) {
              json res = {
                {"error", nullptr},
                {"result", {
                  {"width", desc.Width},
                  {"height", desc.Height},
                }}
              };
              respond(res);
            } else {
              json res = {
                {"error", nullptr},
                {"result", nullptr}
              };
              respond(res);
            }
          } else if (
            methodString == "sendMouse" &&
            args.size() >= 3 && args[0].is_number() && args[1].is_number() && args[2].is_number()
          ) {
            int x = args[0].get<int>();
            int y = args[1].get<int>();
            int type = args[1].get<int>();
            g_fnp->call<
              kProcess_SendMouse,
              int,
              int,
              int,
              int
            >(x, y, type);

            json res = {
              {"error", nullptr},
              {"result", nullptr}
            };
            respond(res);
          } else if (
            methodString == "setDepthRenderEnabled" &&
            args.size() >= 1 && args[0].is_boolean()
          ) {
            const bool enabled = args[0].get<bool>();
            getOut() << "set depth render enabled " << enabled << std::endl;
            g_fnp->call<
              kProcess_SetDepthRenderEnabled,
              int,
              bool
            >(enabled);
            
            json res = {
              {"error", nullptr},
              {"result", nullptr}
            };
            respond(res);
          } else if (
            methodString == "setQrEngineEnabled" &&
            args.size() >= 1 && args[0].is_boolean()
          ) {
            const bool enabled = args[0].get<bool>();
            getOut() << "set qr engine enabled " << enabled << std::endl;
            g_fnp->call<
              kProcess_SetQrEngineEnabled,
              int,
              bool
            >(enabled);
            
            json res = {
              {"error", nullptr},
              {"result", nullptr}
            };
            respond(res);
          } else if (
            methodString == "getQrCodes"
          ) {
            auto qrCode = g_fnp->call<
              kProcess_GetQrCodes,
              std::tuple<managed_binary<char>, managed_binary<float>>
            >();

            managed_binary<char> &data = std::get<0>(qrCode);
            managed_binary<float> &points = std::get<1>(qrCode);

            json array = json::array();
            if (data.size() > 0) {
              std::string dataString;
              json pointsArray = json::array();
              
              dataString = std::string(data.data(), data.size());
              for (size_t i = 0; i < points.size(); i++) {
                pointsArray.push_back(points.data()[i]);
              }
              
              json qrCodeValue = {
                {"data", dataString},
                {"points", pointsArray},
              };
              array.push_back(qrCodeValue);
            }

            json res = {
              {"error", nullptr},
              {"result", array}
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