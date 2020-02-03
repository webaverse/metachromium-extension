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

#include "device/vr/detours/detours.h"

#include "device/vr/openvr/test/out.h"
// #include "third_party/openvr/src/src/vrcommon/sharedlibtools_public.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

std::string logSuffix = "_add_hook";
HWND g_hWnd = NULL;
CHAR s_szDllPath[MAX_PATH] = "vrclient_x64.dll";

PCHAR *CommandLineToArgvA(
    PCHAR CmdLine,
    int* _argc
) {
    PCHAR* argv;
    PCHAR  _argv;
    ULONG   len;
    ULONG   argc;
    CHAR   a;
    ULONG   i, j;

    BOOLEAN  in_QM;
    BOOLEAN  in_TEXT;
    BOOLEAN  in_SPACE;

    len = strlen(CmdLine);
    i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

    argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
        i + (len+2)*sizeof(CHAR));

    _argv = (PCHAR)(((PUCHAR)argv)+i);

    argc = 0;
    argv[argc] = _argv;
    in_QM = FALSE;
    in_TEXT = FALSE;
    in_SPACE = TRUE;
    i = 0;
    j = 0;

    while( a = CmdLine[i] ) {
        if(in_QM) {
            if(a == '\"') {
                in_QM = FALSE;
            } else {
                _argv[j] = a;
                j++;
            }
        } else {
            switch(a) {
            case '\"':
                in_QM = TRUE;
                in_TEXT = TRUE;
                if(in_SPACE) {
                    argv[argc] = _argv+j;
                    argc++;
                }
                in_SPACE = FALSE;
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                if(in_TEXT) {
                    _argv[j] = '\0';
                    j++;
                }
                in_TEXT = FALSE;
                in_SPACE = TRUE;
                break;
            default:
                in_TEXT = TRUE;
                if(in_SPACE) {
                    argv[argc] = _argv+j;
                    argc++;
                }
                _argv[j] = a;
                j++;
                in_SPACE = FALSE;
                break;
            }
        }
        i++;
    }
    _argv[j] = '\0';
    argv[argc] = NULL;

    (*_argc) = argc;
    return argv;
}

BOOL CALLBACK AddBywayCallback(_In_opt_ PVOID pContext,
                                      _In_opt_ LPCSTR pszFile,
                                      _Outptr_result_maybenull_ LPCSTR *ppszOutFile)
{
    PBOOL pbAddedDll = (PBOOL)pContext;
    if (!pszFile && !*pbAddedDll) {                  // Add new byway.
        *pbAddedDll = TRUE;
        *ppszOutFile = s_szDllPath;
        std::cout << "adding " << !!pszFile << " " << !!*pbAddedDll << std::endl;
    } else if (pszFile) {
      std::cout << "keeping " << pszFile << std::endl;
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
        std::cout << pszFile << std::endl;
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
    std::cout << pszOrigFile << " -> " << pszFile << std::endl;
    return TRUE;
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
) {
  char cwdBuf[MAX_PATH];
  if (!GetCurrentDirectory(sizeof(cwdBuf), cwdBuf)) {
    std::cout << "failed to get current directory" << std::endl;
    abort();
  }
  
  // dllDir = R"END(C:\Users\avaer\Documents\GitHub\chromium-79.0.3945.88\device\vr\build\mock_vr_clients\bin\)END";
  std::cout << "add_hook start " << cwdBuf << std::endl;

  int numArgs;
  PCHAR *args = CommandLineToArgvA(lpCmdLine, &numArgs);

  if (numArgs >= 2) {
    std::cout << "add_hook args " << args[0] << " " << args[1] << std::endl;

    auto hOld = CreateFileA(args[0],
       GENERIC_READ,
       FILE_SHARE_READ,
       NULL,
       OPEN_EXISTING,
       FILE_ATTRIBUTE_NORMAL,
       NULL);
    if (hOld == INVALID_HANDLE_VALUE) {
        std::cout << "Couldn't open input file" << std::endl;
        abort();
    }
    
    auto hNew = CreateFileA(args[1],
                         GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
      if (hNew == INVALID_HANDLE_VALUE) {
          std::cout << "Couldn't open output file" << std::endl;
          abort();
      }

    PDETOUR_BINARY pBinary;
    if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
        std::cout << "DetourBinaryOpen failed" << std::endl;
        abort();
    }
    
    
    // DetourBinaryResetImports(pBinary);
    
    BOOL ctx = 0;
     if (!DetourBinaryEditImports(pBinary,
                                 &ctx,
                                 AddBywayCallback, NULL, NULL, NULL)) {
        std::cout << "DetourBinaryEditImports failed" << std::endl;
    }
    if (!DetourBinaryEditImports(pBinary,
                                 NULL,
                                 ListBywayCallback, ListFileCallback, NULL, NULL)) {
        std::cout << "DetourBinaryEditImports failed" << std::endl;
    }
     if (!DetourBinaryWrite(pBinary, hNew)) {
          std::cout << "DetourBinaryWrite failed" << std::endl;
          abort();
      }
      DetourBinaryClose(pBinary);
      CloseHandle(hNew);

      std::cout << "---" << std::endl;
    
    // check
    hOld = CreateFileA(args[1],
       GENERIC_READ,
       FILE_SHARE_READ,
       NULL,
       OPEN_EXISTING,
       FILE_ATTRIBUTE_NORMAL,
       NULL);
    if (hOld == INVALID_HANDLE_VALUE) {
        std::cout << "Couldn't open output file" << std::endl;
        abort();
    }
    if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
        std::cout << "DetourBinaryOpen failed" << std::endl;
        abort();
    }
    CloseHandle(hOld);
    if (!DetourBinaryEditImports(pBinary,
                                 NULL,
                                 ListBywayCallback, ListFileCallback, NULL, NULL)) {
        std::cout << "DetourBinaryEditImports failed" << std::endl;
    }
    DetourBinaryClose(pBinary);

    std::cout << "add_hook ok" << std::endl;
    
    return 0;
  } else {
    std::cout << "invalid number of arguments" << std::endl;

    return 1;
  }
}