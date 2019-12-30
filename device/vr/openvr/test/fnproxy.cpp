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
  // getOut() << "mutex lock 1" << std::endl;
  auto r = WaitForSingleObject(
    h,
    INFINITE
  );
  // getOut() << "mutex lock 2 " << r << " " << GetLastError() << std::endl;
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
  // getOut() << "sempaphore lock 1" << std::endl;
  auto r = WaitForSingleObject(
    h,
    INFINITE
  );
  // getOut() << "sempaphore lock 2 " << r << " " << GetLastError() << std::endl;
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

  // getOut() << "allocate shared 0 " << szName << " " << s << std::endl;

  hMapFile = CreateFileMapping(
               INVALID_HANDLE_VALUE,    // use paging file
               NULL,                    // default security
               PAGE_READWRITE,          // read/write access
               0,                       // maximum object size (high-order DWORD)
               s,                       // maximum object size (low-order DWORD)
               szName);                 // name of mapping object

  // getOut() << "allocate shared 1 " << szName << " " << s << " " << hMapFile << " " << GetLastError() << std::endl;

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
  // getOut() << "allocate shared 2 " << pBuf << std::endl;

  if (pBuf == NULL)
  {
    /*_tprintf(TEXT("Could not map view of file (%d).\n"),
           GetLastError());*/

    CloseHandle(hMapFile);

    // return 1;
  }
  
  // getOut() << "allocate shared 3 " << pBuf << std::endl;
  
  return pBuf;
}

FnProxy::FnProxy() :
  callbackId((size_t)GetCurrentThreadId()),
  mut((std::string("Local\\OpenVrProxyMutex") + std::to_string(callbackId)).c_str()),
  inSem("Local\\OpenVrProxySemaphoreIn"),
  // outSem((std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(id)).c_str()),
  dataArg((unsigned char *)allocateShared("Local\\OpenVrProxyArg", FnProxy::BUF_SIZE + sizeof(unsigned char *)*2)),
  dataResult((unsigned char *)allocateShared("Local\\OpenVrProxyResult", FnProxy::BUF_SIZE + sizeof(unsigned char *)*2)),
  readArg(callbackId, dataArg + sizeof(unsigned char *)*2, *((unsigned char **)dataArg), *((unsigned char **)(dataArg + sizeof(unsigned char *))), FnProxy::BUF_SIZE),
  writeArg(callbackId, dataArg + sizeof(unsigned char *)*2, *((unsigned char **)dataArg), *((unsigned char **)(dataArg + sizeof(unsigned char *))), FnProxy::BUF_SIZE),
  readResult(callbackId, dataResult + sizeof(unsigned char *)*2, *((unsigned char **)dataResult), *((unsigned char **)(dataResult + sizeof(unsigned char *))), FnProxy::BUF_SIZE),
  writeResult(callbackId, dataResult + sizeof(unsigned char *)*2, *((unsigned char **)dataResult), *((unsigned char **)(dataResult + sizeof(unsigned char *))), FnProxy::BUF_SIZE)
  {
    // getOut() << "fn proxy init " << callbackId << " " << (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(callbackId)) << std::endl;
  }

void FnProxy::dispatchCall() {
  inSem.unlock();
  std::map<size_t, Semaphore>::iterator iter = outSems.find(callbackId);
  if (iter == outSems.end()) {
    outSems.emplace(callbackId, (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(callbackId)).c_str());
    iter = outSems.find(callbackId);
  }
  // getOut() << "callback " << (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(callbackId)) << " " << outSems.size() << std::endl;
  iter->second.lock();
}

void FnProxy::handle() {
  inSem.lock();

  size_t remoteCallbackId;
  std::string name;
  // {
    // std::lock_guard<Mutex> lock(mut);
    // getOut() << "read arg 1" << std::endl;
    readArg >> remoteCallbackId >> name;
    // getOut() << "read arg 2 " << name << std::endl;
  // }
  
  // getOut() << "read arg 3 " << name << std::endl;
  std::function<void()> &f = fns.find(name)->second;
  // getOut() << "read arg 4 " << name << std::endl;
  f();
  // getOut() << "read arg 5 " << name << std::endl;

  std::map<size_t, Semaphore>::iterator iter = outSems.find(remoteCallbackId);
  if (iter == outSems.end()) {
    outSems.emplace(remoteCallbackId, (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(remoteCallbackId)).c_str());
    iter = outSems.find(remoteCallbackId);
  }
  // getOut() << "callback " << (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(remoteCallbackId)) << " " << outSems.size() << std::endl;
  iter->second.unlock();
}

/* Mutex checkMutex("Local\\CheckMutex");
std::map<uint32_t, bool> tids;
checkTids::checkTids(Mutex &m) {
  uint32_t tid = GetCurrentThreadId();
  tids[tid] = true;
  
  int num = 0;
  for (auto iter : tids) {
    if (iter.second) {
      num++;
    }
  }
  if (num > 1) {
    getOut() << "num in" << num << std::endl;
  }
}
checkTids::~checkTids() {
  uint32_t tid = GetCurrentThreadId();
  tids[tid] = false;
} */