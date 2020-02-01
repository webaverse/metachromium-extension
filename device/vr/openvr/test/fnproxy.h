#ifndef _openvr_test_fnproxy_h_
#define _openvr_test_fnproxy_h_

#include <map>
// #include <mutex>
// #include <semaphore>
#include <functional>

// #include <D3D11_1.h>
// #include <DXGI1_4.h>

#include "device/vr/openvr/test/out.h"
// #include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/serializer.h"

typedef void *HANDLE;

class Mutex {
public:
  HANDLE h;
  Mutex(const char *name = nullptr);
  ~Mutex();
  void lock();
  void unlock();
  bool tryLock();
};

class Semaphore {
public:
  HANDLE h;
  Semaphore(const char *name = nullptr);
  ~Semaphore();
  void lock();
  void unlock();
  bool tryLock();
};

void *allocateShared(const char *szName, size_t s);

extern Mutex checkMutex;
class checkTids {
public:
  checkTids(Mutex &m);
  ~checkTids();
};
class FnProxy {
public:
  size_t callbackId;
  size_t processId;
  size_t remoteCallbackId;
  size_t remoteProcessId;
  Mutex mut;
  Semaphore inSem;
  // Semaphore outSem;
  std::map<size_t, Semaphore> outSems;
  // std::vector<unsigned char> data;
  unsigned char *dataArg;
  unsigned char *dataResult;
  std::map<std::string, std::function<void()>> fns;
  Serializer readArg;
  Serializer writeArg;
  Serializer readResult;
  Serializer writeResult;

  FnProxy();
  void lock_guard(std::function<void()> &fn);
  void dispatchCall();
  template<const char *name, typename R>
  R call() {
    // getOut() << "proxy0 call 1" << std::endl;
    std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy0 call 2" << std::endl;
    writeArg << callbackId << processId << std::string(name);
    // getOut() << "proxy0 call 3" << std::endl;
    // }
    dispatchCall();
    // {
    // getOut() << "proxy0 call 4" << std::endl;
    // std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy0 call 5" << std::endl;
    R r;
    // getOut() << "proxy0 call 6" << std::endl;
    readResult >> r;
    // getOut() << "proxy0 call 7" << std::endl;
    return r;
  }
  template<const char *name, typename R, typename A>
  R call(A a) {
    // getOut() << "proxy1 call 1" << std::endl;
    std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy1 call 2" << std::endl;
    writeArg << callbackId << processId << std::string(name) << a;
    // getOut() << "proxy1 call 3" << std::endl;
    // }
    dispatchCall();
    // {
    // getOut() << "proxy1 call 4" << std::endl;
    // std::lock_guard<Mutex> lock(mut);
    //  getOut() << "proxy1 call 5" << std::endl;
    R r;
    // getOut() << "proxy1 call 6" << std::endl;
    readResult >> r;
    // getOut() << "proxy1 call 7" << std::endl;
    return r;
  }
  template<const char *name, typename R, typename A, typename B>
  R call(A a, B b) {
    // getOut() << "proxy2 call 1" << std::endl;
    std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy2 call 2" << std::endl;
    writeArg << callbackId << processId << std::string(name) << a << b;
    // getOut() << "proxy2 call 3" << std::endl;
    // }
    dispatchCall();
    // {
    // getOut() << "proxy2 call 4" << std::endl;
    // std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy2 call 5" << std::endl;
    R r;
    // getOut() << "proxy2 call 6" << std::endl;
    readResult >> r;
    // getOut() << "proxy call 7" << std::endl;
    return r;
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  R call(A a, B b, C c) {
    // getOut() << "proxy3 call 1" << std::endl;
    std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy3 call 2" << std::endl;
    writeArg << callbackId << processId << std::string(name) << a << b << c;
    // getOut() << "proxy3 call 3" << std::endl;
    // }
    dispatchCall();
    // {
    // getOut() << "proxy3 call 4" << std::endl;
    // std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy3 call 5" << std::endl;
    R r;
    // getOut() << "proxy3 call 6" << std::endl;
    readResult >> r;
    // getOut() << "proxy3 call 7" << std::endl;
    return r;
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  R call(A a, B b, C c, D d) {
    // getOut() << "proxy4 call 1" << std::endl;
    std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy4 call 2" << std::endl;
    writeArg << callbackId << processId << std::string(name) << a << b << c << d;
    // getOut() << "proxy4 call 3" << std::endl;
    // }
    dispatchCall();
    // {
    // getOut() << "proxy4 call 4" << std::endl;
    // std::lock_guard<Mutex> lock(mut);
    // getOut() << "proxy4 call 5" << std::endl;
    R r;
    // getOut() << "proxy4 call 6" << std::endl;
    readResult >> r;
    // getOut() << "proxy4 call 7" << std::endl;
    return r;
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E>
  R call(A a, B b, C c, D d, E e) {
    std::lock_guard<Mutex> lock(mut);
    writeArg << callbackId << processId << std::string(name) << a << b << c << d << e;
    // }
    dispatchCall();
    // {
    // std::lock_guard<Mutex> lock(mut);
    R r;
    readResult >> r;
    return r;
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E, typename F>
  R call(A a, B b, C c, D d, E e, F f) {
    std::lock_guard<Mutex> lock(mut);
    writeArg << callbackId << processId << std::string(name) << a << b << c << d << e << f;
    // }
    dispatchCall();
    // {
    // std::lock_guard<Mutex> lock(mut);
    R r;
    readResult >> r;
    return r;
  }

  template<const char *name, typename R>
  void reg(std::function<R()> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      R r = fn();
      // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  template<const char *name, typename R, typename A>
  void reg(std::function<R(A)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      // {
        // std::lock_guard<Mutex> lock(mut);
        readArg >> a;
        // }
        R r = fn(std::move(a));
        // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  template<const char *name, typename R, typename A, typename B>
  void reg(std::function<R(A, B)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      // getOut() << "proxy handle 0" << std::endl;
      A a;
      B b;
      // getOut() << "proxy handle 1" << std::endl;
      // {
        // getOut() << "proxy handle 2" << std::endl;
        // std::lock_guard<Mutex> lock(mut);
        // getOut() << "proxy handle 3" << std::endl;
        readArg >> a >> b;
        // getOut() << "proxy handle 4" << std::endl;
        // }
        // getOut() << "proxy handle 5" << std::endl;
        R r = fn(std::move(a), std::move(b));
        // getOut() << "proxy handle 6" << std::endl;
        // {
        // getOut() << "proxy handle 7" << std::endl;
        // std::lock_guard<Mutex> lock(mut);
        // getOut() << "proxy handle 8" << std::endl;
        writeResult << r;
        // getOut() << "proxy handle 9" << std::endl;
      // }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  void reg(std::function<R(A, B, C)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      // {
        // std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c;
        // }
        R r = fn(std::move(a), std::move(b), std::move(c));
        // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  void reg(std::function<R(A, B, C, D)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      D d;
      // {
        // std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d;
        // }
        R r = fn(std::move(a), std::move(b), std::move(c), std::move(d));
        // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E>
  void reg(std::function<R(A, B, C, D, E)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      D d;
      E e;
      // {
        // std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d >> e;
        // }
        R r = fn(std::move(a), std::move(b), std::move(c), std::move(d), std::move(e));
        // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E, typename F>
  void reg(std::function<R(A, B, C, D, E, F)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      D d;
      E e;
      F f;
      // {
        // std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d >> e >> f;
        // }
        R r = fn(std::move(a), std::move(b), std::move(c), std::move(d), std::move(e), std::move(f));
        // {
        // std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      // }
    };
  }
  
  void handle();
  
  static constexpr size_t BUF_SIZE = 512*1024;
};

#endif