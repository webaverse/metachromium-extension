#include <io.h>
#include <fcntl.h>
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
#include "device/vr/openvr/test/base64.h"

using json = nlohmann::json;
using Base64 = macaron::Base64;

std::string logSuffix = "_native";
HWND g_hWnd = NULL;
// CHAR s_szDllPath[MAX_PATH] = "vrclient_x64.dll";
extern std::string dllDir;

DWORD chromePid = 0;
HWND chromeHwnd = NULL;

char kProcess_SetIsVr[] = "IVRCompositor::kIVRCompositor_SetIsVr";
char kProcess_SetTransform[] = "IVRCompositor::kIVRCompositor_SetTransform";
char kProcess_PrepareBindSurface[] = "IVRCompositor::kIVRCompositor_PrepareBindSurface";
char kProcess_SetDepthRenderEnabled[] = "IVRCompositor::kIVRCompositor_SetDepthRenderEnabled";
char kProcess_SetQrEngineEnabled[] = "IVRCompositor::kIVRCompositor_SetQrEngineEnabled";
char kProcess_GetQrCodes[] = "IVRCompositor::GetQrCodes";
char kProcess_SetCvEngineEnabled[] = "IVRCompositor::kIVRCompositor_SetCvEngineEnabled";
char kProcess_GetCvFeature[] = "IVRCompositor::GetCvFeature";
char kProcess_AddCvFeature[] = "IVRCompositor::AddCvFeature";
char kProcess_Terminate[] = "Process::Terminate";

class HwndSearchStruct {
public:
  const std::string &s;
  HWND hwnd;
};
BOOL CALLBACK enumWindowsProc(
  __in HWND hwnd,
  __in LPARAM lParam
) {
  HwndSearchStruct &o = *((HwndSearchStruct *)lParam);

  CHAR windowTitle[1024];
  GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
  
  getOut() << "get window title: " << windowTitle << std::endl;

  if (o.s == windowTitle) {
    o.hwnd = hwnd;
    return false;
  } else {
    return true;
  }
}
/* HWND getHwndFromPid(DWORD pid) {
  HwndSearchStruct o{
    pid,
    (HWND)NULL
  };
  EnumWindows(enumWindowsProc, (LPARAM)&o);
  return o.hwnd;
} */
HWND getHwndFromTitle(const std::string &s) {
  HwndSearchStruct o{
    s,
    (HWND)NULL
  };
  EnumWindows(enumWindowsProc, (LPARAM)&o);
  return o.hwnd;
}

inline uint32_t divCeil(uint32_t x, uint32_t y) {
  return (x + y - 1) / y;
}

constexpr uint32_t chunkSize = 1000*1000;
void respond(const json &j) {
  std::string outString = j.dump();
  uint32_t outSize = (uint32_t)outString.size();
  if (outSize < chunkSize) {
    std::cout.write((char *)&outSize, sizeof(outSize));
    std::cout.write(outString.data(), outString.size());
  } else {
    uint32_t numChunks = divCeil(outSize, chunkSize);
    // getOut() << "write chunks " << outSize << " " << chunkSize << " " << numChunks << std::endl;
    for (uint32_t i = 0; i < numChunks; i++) {
      // getOut() << "sending " << i << " " << numChunks << " " << outString.substr(i*chunkSize, chunkSize).size() << std::endl;
      json j2 = {
        {"index", 0},
        {"total", numChunks},
        {"continutation", outString.substr(i*chunkSize, chunkSize)},
      };
      std::string outString2 = j2.dump();
      uint32_t outSize2 = (uint32_t)outString2.size();
      std::cout.write((char *)&outSize2, sizeof(outSize2));
      std::cout.write(outString2.data(), outString2.size());
    }
    // getOut() << "done sending" << std::endl;
  }
}

int main(int argc, char **argv) {
  setmode(fileno(stdout), O_BINARY);
  setmode(fileno(stdin), O_BINARY);

  freopen(NULL, "rb", stdin);
  freopen(NULL, "wb", stdout);
  
  g_fnp = new FnProxy();

  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(
    sizeof(cwdBuf),
    cwdBuf
  )) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }

  std::cerr << "start native host" << std::endl;
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
          /* } else if (
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
            } */
          } else if (
            methodString == "getHwndFromTitle" &&
            args.size() >= 1 && args[0].is_string()
          ) {
            const std::string &title = args[0].get<std::string>();
            HWND hwnd = getHwndFromTitle(title);
            uint32_t a = (uint32_t)(((uint64_t)hwnd & 0xFFFFFFFF00000000ull) >> 32ull);
            uint32_t b = (uint32_t)((uint64_t)hwnd & 0x00000000FFFFFFFFull);

            json array = json::array();
            array.push_back(a);
            array.push_back(b);
            json res = {
              {"error", nullptr},
              {"result", array}
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
            methodString == "setCvEngineEnabled" &&
            args.size() >= 1 && args[0].is_boolean()
          ) {
            const bool enabled = args[0].get<bool>();
            getOut() << "set cv engine enabled " << enabled << std::endl;
            g_fnp->call<
              kProcess_SetCvEngineEnabled,
              int,
              bool
            >(enabled);
            
            json res = {
              {"error", nullptr},
              {"result", nullptr}
            };
            respond(res);
          } else if (
            methodString == "activate" &&
            args.size() >= 1 && args[0].is_array() &&
            args[0].size() == 2 && args[0][0].is_number() && args[0][1].is_number()
          ) {
            HWND hwnd = (HWND)(((uint64_t)args[0][0].get<uint32_t>() << 32ull) | (uint64_t)args[0][1].get<uint32_t>());
            HWND oldHwnd = GetForegroundWindow();
            if (oldHwnd != hwnd) {
              SetForegroundWindow(hwnd);
            }

            HKL keyboardLayout = LoadKeyboardLayoutA("00000409", KLF_ACTIVATE);
            {
              INPUT input{};
              input.type = INPUT_KEYBOARD;
              input.ki.wVk = VK_TAB;
              input.ki.wScan = MapVirtualKeyExA(input.ki.wVk, MAPVK_VK_TO_VSC, keyboardLayout);
              for (int i = 0; i < 3; i++) {
                input.ki.dwFlags = 0;
                SendInput(1, &input, sizeof(input));
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(input));
              }
            }
            {
              INPUT input{};
              input.type = INPUT_KEYBOARD;
              input.ki.wVk = VK_CONTROL;
              input.ki.wScan = MapVirtualKeyExA(input.ki.wVk, MAPVK_VK_TO_VSC, keyboardLayout);
              input.ki.dwFlags = 0;
              SendInput(1, &input, sizeof(input));
              input.ki.dwFlags = KEYEVENTF_KEYUP;
              SendInput(1, &input, sizeof(input));
            }
            if (oldHwnd != chromeHwnd) {
              SetForegroundWindow(oldHwnd);
            }

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
          } else if (
            methodString == "getCvFeature"
          ) {
            getOut() << "get cv feature 1" << std::endl;
            auto feature = g_fnp->call<
              kProcess_GetCvFeature,
              std::tuple<managed_binary<int>, managed_binary<char>, managed_binary<int>, managed_binary<char>, managed_binary<float>>
            >();
            
            getOut() << "get cv feature 2.1 " << std::get<0>(feature).size() << std::endl;

            int rows = std::get<0>(feature)[0];
            int cols = std::get<0>(feature)[1];
            int type = std::get<0>(feature)[2];
            const managed_binary<char> &dataBuffer = std::get<1>(feature);
            getOut() << "get cv feature 2.2 " << rows << " " << cols << " " << type << " " << dataBuffer.size() << std::endl;
            const std::string &data = Base64::Encode(dataBuffer);
            getOut() << "get cv feature 2.3 " << data.size() << std::endl;
            json image = {
              {"rows", rows},
              {"cols", cols},
              {"type", type},
              {"data", data},
            };
            
            getOut() << "get cv feature 3 " << std::get<2>(feature).size() << std::endl;

            int descriptorRows = std::get<2>(feature)[0];
            int descriptorCols = std::get<2>(feature)[1];
            int descriptorType = std::get<2>(feature)[2];
            const managed_binary<char> &descriptorDataBuffer = std::get<3>(feature);
            const std::string &descriptorData = Base64::Encode(descriptorDataBuffer);
            json descriptor = {
              {"rows", descriptorRows},
              {"cols", descriptorCols},
              {"type", descriptorType},
              {"data", descriptorData},
            };

            getOut() << "get cv feature 4" << std::endl;

            const managed_binary<float> &pointsBuffer = std::get<4>(feature);
            const std::string &pointsData = Base64::Encode(pointsBuffer);

            getOut() << "get cv feature 5" << std::endl;

            json o = {
              {"image", image},
              {"descriptor", descriptor},
              {"points", pointsData},
            };
            json res = {
              {"error", nullptr},
              {"result", o}
            };
            respond(res);
          } else if (
            methodString == "addCvFeature" &&
            args.size() >= 4 && args[0].is_number() && args[1].is_number() && args[2].is_number() && args[3].is_string()
          ) {
            int rows = args[0].get<int>();
            int cols = args[1].get<int>();
            int type = args[2].get<int>();
            const std::string &data = args[3].get<std::string>();
            managed_binary<char> dataBuffer = Base64::Decode<char>(data);
            auto result = g_fnp->call<
              kProcess_AddCvFeature,
              int,
              int,
              int,
              int,
              managed_binary<char>
            >(rows, cols, type, std::move(dataBuffer));

            json res = {
              {"error", nullptr},
              {"result", nullptr}
            };
            respond(res);
          } else if (
            methodString == "terminate"
          ) {
            getOut() << "call terminate 1" << std::endl;
            auto result = g_fnp->call<
              kProcess_Terminate,
              int
            >();
            getOut() << "call terminate 2" << std::endl;

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
  
  std::cerr << "end native host" << std::endl;
}