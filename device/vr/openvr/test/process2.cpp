// #include <windows.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <io.h>
// #include <iostream>
// #include <fstream>

#include "device/vr/openvr/test/out.h"
#include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

std::string logSuffix = "_gpu";
HWND g_hWnd = NULL;

BOOL IsElevated( ) {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken ) {
        CloseHandle( hToken );
    }
    return fRet;
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
) {
  std::vector<char> cmd(strlen(lpCmdLine)+1);
  memcpy(cmd.data(), lpCmdLine, cmd.size());
  
  dllDir = R"END(C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin\)END";
  getOut() << "gpu process start 1: " << cmd.data() << " " << IsElevated() << std::endl;

  std::string cmdString(lpCmdLine);
  std::string target = "--mojo-platform-channel-handle=";
  size_t found = cmdString.find(target);
  if (found != std::string::npos) {
    HANDLE h = (HANDLE)std::stoll(cmdString.substr(found + target.size()));
    DWORD flags;
    GetHandleInformation(h, &flags);
    getOut() << "found handle " << (void *)h << " " << (void *)flags << std::endl;
  } else {
    getOut() << "no handle" << std::endl;
  }

  // STARTUPINFOEXA si2{};
  // STARTUPINFO &si = si2.StartupInfo;
  STARTUPINFO si{};
  si.cb = sizeof(si);
  si.dwFlags |= STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_HIDE;
  PROCESS_INFORMATION pi{};
  bool ok = CreateProcessA( NULL,   // No module name (use command line)
    cmd.data(),        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    true,          // Set handle inheritance to FALSE
    CREATE_NO_WINDOW,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory 
    &si,            // Pointer to STARTUPINFO structure
    &pi           // Pointer to PROCESS_INFORMATION structure
  );
  getOut() << "gpu process start 2: " << ok << " " << GetLastError() << " " << pi.dwProcessId << " " << pi.dwThreadId << std::endl;
  
  WaitForSingleObject(pi.hProcess, INFINITE);
  DWORD exitCode;
  GetExitCodeProcess(pi.hProcess, &exitCode);
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );

  getOut() << "gpu process exit: " << (void *)exitCode << std::endl;
  
  return *reinterpret_cast<int *>(&exitCode);
}