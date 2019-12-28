#ifndef _openvr_test_fnproxy_h_
#define _openvr_test_fnproxy_h_

#include <map>
// #include <mutex>
// #include <semaphore>
#include <functional>

#include <D3D11_1.h>
#include <DXGI1_4.h>

#include "device/vr/openvr/test/out.h"
#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/serializer.h"

class Mutex {
public:
  HANDLE h;
  Mutex(const char *name);
  void lock();
  void unlock();
};

class Semaphore {
public:
  HANDLE h;
  Semaphore(const char *name);
  void lock();
  void unlock();
};

void *allocateShared(const char *szName, size_t s);

class FnProxy {
public:
  Mutex mut;
  Semaphore inSem;
  Semaphore outSem;
  // std::vector<unsigned char> data;
  unsigned char *dataArg;
  unsigned char *dataResult;
  std::map<std::string, std::function<void()>> fns;
  Serializer readArg;
  Serializer writeArg;
  Serializer readResult;
  Serializer writeResult;
  
  FnProxy();

  template<const char *name, typename R>
  R call() {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name);
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }
  template<const char *name, typename R, typename A>
  R call(A a) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name) << a;
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B>
  R call(A a, B b) {
    {
      // getOut() << "proxy call 1" << std::endl;
      std::lock_guard<Mutex> lock(mut);
      // getOut() << "proxy call 2" << std::endl;
      writeArg << std::string(name) << a << b;
      // getOut() << "proxy call 3" << std::endl;
    }
    inSem.unlock();
    outSem.lock();
    {
      // getOut() << "proxy call 4" << std::endl;
      std::lock_guard<Mutex> lock(mut);
      // getOut() << "proxy call 5" << std::endl;
      R r;
      // getOut() << "proxy call 6" << std::endl;
      readResult >> r;
      // getOut() << "proxy call 7" << std::endl;
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  R call(A a, B b, C c) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name) << a << b << c;
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  R call(A a, B b, C c, D d) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name) << a << b << c << d;
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E>
  R call(A a, B b, C c, D d, E e) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name) << a << b << c << d << e;
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E, typename F>
  R call(A a, B b, C c, D d, E e, F f) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg << std::string(name) << a << b << c << d << e << f;
    }
    inSem.unlock();
    outSem.lock();
    {
      std::lock_guard<Mutex> lock(mut);
      R r;
      readResult >> r;
      return r;
    }
  }

  template<const char *name, typename R>
  void reg(std::function<R()> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      R r = fn();
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
    };
  }
  template<const char *name, typename R, typename A>
  void reg(std::function<R(A)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg >> a;
      }
      R r = fn(std::move(a));
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
    };
  }
  template<const char *name, typename R, typename A, typename B>
  void reg(std::function<R(A, B)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      // getOut() << "proxy handle 0" << std::endl;
      A a;
      B b;
      // getOut() << "proxy handle 1" << std::endl;
      {
        // getOut() << "proxy handle 2" << std::endl;
        std::lock_guard<Mutex> lock(mut);
        // getOut() << "proxy handle 3" << std::endl;
        readArg >> a >> b;
        // getOut() << "proxy handle 4" << std::endl;
      }
      // getOut() << "proxy handle 5" << std::endl;
      R r = fn(std::move(a), std::move(b));
      // getOut() << "proxy handle 6" << std::endl;
      {
        // getOut() << "proxy handle 7" << std::endl;
        std::lock_guard<Mutex> lock(mut);
        // getOut() << "proxy handle 8" << std::endl;
        writeResult << r;
        // getOut() << "proxy handle 9" << std::endl;
      }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C>
  void reg(std::function<R(A, B, C)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c;
      }
      R r = fn(std::move(a), std::move(b), std::move(c));
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
    };
  }
  template<const char *name, typename R, typename A, typename B, typename C, typename D>
  void reg(std::function<R(A, B, C, D)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      C c;
      D d;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d;
      }
      R r = fn(std::move(a), std::move(b), std::move(c), std::move(d));
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
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
      {
        std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d >> e;
      }
      R r = fn(std::move(a), std::move(b), std::move(c), std::move(d), std::move(e));
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
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
      {
        std::lock_guard<Mutex> lock(mut);
        readArg >> a >> b >> c >> d >> e >> f;
      }
      R r = fn(std::move(a), std::move(b), std::move(c), std::move(d), std::move(e), std::move(f));
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult << r;
      }
    };
  }
  
  void handle();
  
  static constexpr size_t BUF_SIZE = 4096;
};

#endif