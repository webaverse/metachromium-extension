#include "device/vr/openvr/test/fnproxy.h"

Mutex::Mutex(const char *name) {
  h = CreateMutex(
    NULL,
    false,
    name
  );
  if (!h) {
    getOut() << "mutex error " << GetLastError() << std::endl;
    // abort();
  }
}
void Mutex::lock() {
  getOut() << "mutex lock 1" << std::endl;
  auto r = WaitForSingleObject(
    h,
    INFINITE
  );
  getOut() << "mutex lock 2 " << r << " " << GetLastError() << std::endl;
}
void Mutex::unlock() {
  ReleaseMutex(
    h
  );
}

Semaphore::Semaphore(const char *name) {
  h = CreateSemaphore(
    NULL,
    0,
    1024,
    name
  );
  if (!h) {
    getOut() << "semaphore error " << GetLastError() << std::endl;
    // abort();
  }
}
void Semaphore::lock() {
  getOut() << "sempaphore lock 1" << std::endl;
  auto r = WaitForSingleObject(
    h,
    INFINITE
  );
  getOut() << "sempaphore lock 2 " << r << " " << GetLastError() << std::endl;
}
void Semaphore::unlock() {
  ReleaseSemaphore(
    h,
    1,
    NULL
  );
}

void *allocateShared(const char *szName, size_t s) {
  HANDLE hMapFile;
  void *pBuf;

  getOut() << "allocate shared 0 " << szName << " " << s << std::endl;

  hMapFile = CreateFileMapping(
               INVALID_HANDLE_VALUE,    // use paging file
               NULL,                    // default security
               PAGE_READWRITE,          // read/write access
               0,                       // maximum object size (high-order DWORD)
               s,                       // maximum object size (low-order DWORD)
               szName);                 // name of mapping object

  getOut() << "allocate shared 1 " << szName << " " << s << " " << hMapFile << " " << GetLastError() << std::endl;

  if (hMapFile == NULL)
  {
    /*_tprintf(TEXT("Could not create file mapping object (%d).\n"),
           GetLastError());*/
    // return 1;
  }
  pBuf = MapViewOfFile(hMapFile,   // handle to map object
                      FILE_MAP_ALL_ACCESS, // read/write permission
                      0,
                      0,
                      s);
  getOut() << "allocate shared 2 " << pBuf << std::endl;

  if (pBuf == NULL)
  {
    /*_tprintf(TEXT("Could not map view of file (%d).\n"),
           GetLastError());*/

    CloseHandle(hMapFile);

    // return 1;
  }
  
  getOut() << "allocate shared 3 " << pBuf << std::endl;
  
  return pBuf;
}

FnProxy::FnProxy() :
  mut("Local\\OpenVrProxyMutex"),
  inSem("Local\\OpenVrProxySemaphoreIn"),
  outSem("Local\\OpenVrProxySemaphoreOut"),
  dataArg((unsigned char *)allocateShared("Local\\OpenVrProxyArg", 4096)),
  dataResult((unsigned char *)allocateShared("Local\\OpenVrProxyResult", 4096)),
  readArg(dataArg),
  writeArg(dataArg),
  readResult(dataResult),
  writeResult(dataResult)
  {}