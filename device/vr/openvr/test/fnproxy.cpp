#include <string>

#include "device/vr/openvr/test/fnproxy.h"

#include <windows.h>

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
Mutex::~Mutex() {
  // CloseHandle(h);
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
bool Mutex::tryLock() {
  auto r = WaitForSingleObject(
    h,
    0
  );
  return r == WAIT_OBJECT_0;
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
Semaphore::~Semaphore() {
  // CloseHandle(h);
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
bool Semaphore::tryLock() {
  // getOut() << "sempaphore lock 1" << std::endl;
  auto r = WaitForSingleObject(
    h,
    0
  );
  return r == WAIT_OBJECT_0;
  // getOut() << "sempaphore lock 2 " << r << " " << GetLastError() << std::endl;
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
  processId((size_t)GetCurrentProcessId()),
  // mut("Local\\OpenVrProxyMutex"),
  mut("Local\\OpenVrProxyMutex"),
  inSem("Local\\OpenVrProxySemaphoreIn"),
  // outSem((std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(id)).c_str()),
  dataArg((unsigned char *)allocateShared("Local\\OpenVrProxyArg", FnProxy::BUF_SIZE + sizeof(unsigned char *)*2)),
  dataResult((unsigned char *)allocateShared("Local\\OpenVrProxyResult", FnProxy::BUF_SIZE + sizeof(unsigned char *)*2)),
  readArg(callbackId, dataArg + sizeof(uintptr_t)*2, *((uintptr_t *)dataArg), *((uintptr_t *)(dataArg + sizeof(uintptr_t))), FnProxy::BUF_SIZE),
  writeArg(callbackId, dataArg + sizeof(uintptr_t)*2, *((uintptr_t *)dataArg), *((uintptr_t *)(dataArg + sizeof(uintptr_t))), FnProxy::BUF_SIZE),
  readResult(callbackId, dataResult + sizeof(uintptr_t)*2, *((uintptr_t *)dataResult), *((uintptr_t *)(dataResult + sizeof(uintptr_t))), FnProxy::BUF_SIZE),
  writeResult(callbackId, dataResult + sizeof(uintptr_t)*2, *((uintptr_t *)dataResult), *((uintptr_t *)(dataResult + sizeof(uintptr_t))), FnProxy::BUF_SIZE)
{
  // getOut() << "fn proxy init" << std::endl;
  // getOut() << "fn proxy init " << callbackId << " " << (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(callbackId)) << std::endl;
}

void FnProxy::lock_guard(std::function<void()> &fn) {
  std::lock_guard<Mutex> lock(mut);
  fn();
}

void FnProxy::dispatchCall() {
  inSem.unlock();
  std::map<size_t, Semaphore>::iterator iter = outSems.find(callbackId);
  if (iter == outSems.end()) {
    outSems.emplace(callbackId, (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(callbackId)).c_str());
    iter = outSems.find(callbackId);
  }
  iter->second.lock();
}

void FnProxy::handle() {
  while (inSem.tryLock()) {
    // getOut() << "fn proxy handle 1" << std::endl;

    std::string name;
    readArg >> remoteCallbackId >> remoteProcessId >> name;

    if (name.size() == 0) {
      getOut() << "error: got blank function name " << remoteCallbackId << " " << remoteProcessId << " " << name.size() << " " << name << " " << fns.size() << " " << (fns.find(name) != fns.end()) << std::endl;
      for (auto iter : fns) {
        getOut() << iter.first << std::endl;
      }
      abort();
    }

    std::function<void()> &f = fns.find(name)->second;
    f();

    std::map<size_t, Semaphore>::iterator iter = outSems.find(remoteCallbackId);
    if (iter == outSems.end()) {
      outSems.emplace(remoteCallbackId, (std::string("Local\\OpenVrProxySemaphoreOut") + std::to_string(remoteCallbackId)).c_str());
      iter = outSems.find(remoteCallbackId);
    }
    iter->second.unlock();
  }
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