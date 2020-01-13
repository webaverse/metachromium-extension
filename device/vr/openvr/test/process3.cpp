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

#include "device/vr/detours/detours.h"

#include "device/vr/openvr/test/out.h"
// #include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

std::string logSuffix = "_bin";
HWND g_hWnd = NULL;
CHAR s_szDllPath[MAX_PATH] = "vrclient_x64.dll";

BOOL CALLBACK AddBywayCallback(_In_opt_ PVOID pContext,
                                      _In_opt_ LPCSTR pszFile,
                                      _Outptr_result_maybenull_ LPCSTR *ppszOutFile)
{
    PBOOL pbAddedDll = (PBOOL)pContext;
    if (!pszFile && !*pbAddedDll) {                  // Add new byway.
        *pbAddedDll = TRUE;
        *ppszOutFile = s_szDllPath;
        getOut() << "adding " << !!pszFile << " " << !!*pbAddedDll << std::endl;
    } else if (pszFile) {
      getOut() << "keeping " << pszFile << std::endl;
      *ppszOutFile = pszFile;
    }
    return TRUE;
}

BOOL CALLBACK ListBywayCallback(_In_opt_ PVOID pContext,
                                       _In_opt_ LPCSTR pszFile,
                                       _Outptr_result_maybenull_ LPCSTR *ppszOutFile)
{
    (void)pContext;

    *ppszOutFile = pszFile;
    if (pszFile) {
        getOut() << pszFile << std::endl;
    }
    return TRUE;
}

BOOL CALLBACK ListFileCallback(_In_opt_ PVOID pContext,
                                      _In_ LPCSTR pszOrigFile,
                                      _In_ LPCSTR pszFile,
                                      _Outptr_result_maybenull_ LPCSTR *ppszOutFile)
{
    (void)pContext;

    *ppszOutFile = pszFile;
    getOut() << pszOrigFile << " -> " << pszFile << std::endl;
    return TRUE;
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
) {
  // std::vector<char> cmd(strlen(lpCmdLine)+1);
  // memcpy(cmd.data(), lpCmdLine, cmd.size());
  
  dllDir = R"END(C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin\)END";
  getOut() << "gpu process start 1: " << std::endl;
  
  // memcpy(s_szDllPath, "lol.dll", strlen("lol.dll")+1);

  auto hOld = CreateFileA(R"END(C:\Users\avaer\AppData\Local\Chromium\Application\chrome.exe)END",
     GENERIC_READ,
     FILE_SHARE_READ,
     NULL,
     OPEN_EXISTING,
     FILE_ATTRIBUTE_NORMAL,
     NULL);
  if (hOld == INVALID_HANDLE_VALUE) {
      getOut() << "Couldn't open input file" << std::endl;
      abort();
  }
  
  auto hNew = CreateFileA(R"END(C:\Users\avaer\AppData\Local\Chromium\Application\chrome2.exe)END",
                       GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hNew == INVALID_HANDLE_VALUE) {
        getOut() << "Couldn't open output file" << std::endl;
        abort();
    }

  PDETOUR_BINARY pBinary;
  if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
      getOut() << "DetourBinaryOpen failed" << std::endl;
      abort();
  }
  
  
  // DetourBinaryResetImports(pBinary);
  
  BOOL ctx = 0;
   if (!DetourBinaryEditImports(pBinary,
                               &ctx,
                               AddBywayCallback, NULL, NULL, NULL)) {
      getOut() << "DetourBinaryEditImports failed" << std::endl;
  }
  if (!DetourBinaryEditImports(pBinary,
                               NULL,
                               ListBywayCallback, ListFileCallback, NULL, NULL)) {
      getOut() << "DetourBinaryEditImports failed" << std::endl;
  }
   if (!DetourBinaryWrite(pBinary, hNew)) {
        getOut() << "DetourBinaryWrite failed" << std::endl;
        abort();
    }
    DetourBinaryClose(pBinary);
    CloseHandle(hNew);

    getOut() << "---" << std::endl;
  
  // check
  hOld = CreateFileA(R"END(C:\Users\avaer\AppData\Local\Chromium\Application\chrome2.exe)END",
     GENERIC_READ,
     FILE_SHARE_READ,
     NULL,
     OPEN_EXISTING,
     FILE_ATTRIBUTE_NORMAL,
     NULL);
  if (hOld == INVALID_HANDLE_VALUE) {
      getOut() << "Couldn't open input file" << std::endl;
      abort();
  }
  if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
      getOut() << "DetourBinaryOpen failed" << std::endl;
      abort();
  }
  CloseHandle(hOld);
   if (!DetourBinaryEditImports(pBinary,
                               NULL,
                               ListBywayCallback, ListFileCallback, NULL, NULL)) {
      getOut() << "DetourBinaryEditImports failed" << std::endl;
  }
  DetourBinaryClose(pBinary);
  
  return 0;
}