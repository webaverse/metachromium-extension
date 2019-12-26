#include <map>
// #include <mutex>
// #include <semaphore>
#include <functional>

#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/serializer.h"

class Mutex {
public:
  HANDLE h;
  Mutex(const char *name) {
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
  void lock() {
    getOut() << "mutex lock 1" << std::endl;
    auto r = WaitForSingleObject(
      h,
      INFINITE
    );
    getOut() << "mutex lock 2 " << r << " " << GetLastError() << std::endl;
  }
  void unlock() {
    ReleaseMutex(
      h
    );
  }
};

class Semaphore {
public:
  HANDLE h;
  Semaphore(const char *name) {
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
  void lock() {
    getOut() << "sempaphore lock 1" << std::endl;
    auto r = WaitForSingleObject(
      h,
      INFINITE
    );
    getOut() << "sempaphore lock 2 " << r << " " << GetLastError() << std::endl;
  }
  void unlock() {
    ReleaseSemaphore(
      h,
      1,
      NULL
    );
  }
};

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

class FnProxy {
public:
  Mutex mut;
  Semaphore inSem;
  Semaphore outSem;
  // std::vector<unsigned char> data;
  staticvector<unsigned char> dataArg;
  staticvector<unsigned char> dataResult;
  std::map<std::string, std::function<void()>> fns;
  zpp::serializer::memory_input_archive readArg;
  zpp::serializer::memory_output_archive writeArg;
  zpp::serializer::memory_input_archive readResult;
  zpp::serializer::memory_output_archive writeResult;
  
  FnProxy() :
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

  template<const char *name, typename R>
  R call() {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult(r);
      return r;
    }
  }
  template<const char *name, typename R, typename A>
  R call(A a) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a);
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult(r);
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B>
  R call(A a, B b) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a, b);
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult(r);
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  R call(A a, B b, C c) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a, b, c);
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult(r);
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  R call(A a, B b, C c, D d) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a, b, c, d);
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult(r);
      return r;
    }
  }

  template<const char *name, typename R>
  void reg(std::function<R()> f) {
    fns[std::string(name)] = [this, f]() -> void {
      R r = f();
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A>
  void reg(std::function<R(A)> f) {
    fns[std::string(name)] = [this, f]() -> void {
      A a;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a);
      }
      R r = f(a);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A, typename B>
  void reg(std::function<R(A, B)> f) {
    fns[std::string(name)] = [this, f]() -> void {
      A a;
      B b;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a, b);
      }
      R r = f(a, b);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  void reg(std::function<R(A, B, C)> f) {
    fns[std::string(name)] = [this, f]() -> void {
      A a;
      B b;
      C c;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a, b, c);
      }
      R r = f(a, b, c);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  void reg(std::function<R(A, B, C, D)> f) {
    fns[std::string(name)] = [this, f]() -> void {
      A a;
      B b;
      C c;
      D d;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a, b, c, d);
      }
      R r = f(a, b, c, d);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  
  void handle() {
    inSem.lock();
    
    std::string name;
    {
      std::lock_guard<Mutex> lock(mut);
      // getOut() << "read arg 1" << std::endl;
      readArg(name);
      // getOut() << "read arg 2 " << name << std::endl;
    }
    std::function<void()> &f = fns.find(name)->second;
    f();
    
    outSem.unlock();
  }
};