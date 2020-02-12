#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/matrix.h"

#include <psapi.h>

namespace compositor2d {

std::vector<HWND> hwnds;
BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
  hwnds.push_back(hwnd);
  return true;
}
void homeRenderLoop() {
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    getOut() << "failed to get current directory" << std::endl;
    abort();
  }
  std::string cwd(cwdBuf);
  cwd += "\\chrome.exe";
  
  getOut() << "try cwd " << cwd << std::endl;

  for (;;) {
    hwnds.clear();
    BOOL result = EnumWindows(
      EnumWindowsProc,
      NULL
    );
    for (auto iter : hwnds) {
      if (IsWindowVisible(iter)) {
        char buffer[MAX_PATH];
        DWORD dwProcId = 0; 

        GetWindowThreadProcessId(iter, &dwProcId);   

        HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcId);    
        DWORD result = GetModuleFileNameExA(hProc, NULL, buffer, sizeof(buffer));
        CloseHandle(hProc);

        char txt[MAX_PATH];
        GetWindowTextA(
          iter,
          txt,
          sizeof(txt)
        );

        if (result > 0) {
          getOut() << "got window " << result << " " << buffer << " " << txt << std::endl;
        }
      }
    }
    Sleep(1000);
  }
}

}