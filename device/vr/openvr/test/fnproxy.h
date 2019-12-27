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
  staticvector<unsigned char> dataArg;
  staticvector<unsigned char> dataResult;
  std::map<std::string, std::function<void()>> fns;
  zpp::serializer::memory_input_archive readArg;
  zpp::serializer::memory_output_archive writeArg;
  zpp::serializer::memory_input_archive readResult;
  zpp::serializer::memory_output_archive writeResult;
  
  FnProxy();

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
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E>
  R call(A a, B b, C c, D d, E e) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a, b, c, d, e);
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
  template<const char *name, typename R, typename A, typename B, typename C, typename D, typename E, typename F>
  R call(A a, B b, C c, D d, E e, F f) {
    {
      std::lock_guard<Mutex> lock(mut);
      writeArg(std::string(name));
      writeArg(a, b, c, d, e, f);
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
  void reg(std::function<R()> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      R r = fn();
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A>
  void reg(std::function<R(A)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a);
      }
      R r = fn(a);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
      }
    };
  }
  template<const char *name, typename R, typename A, typename B>
  void reg(std::function<R(A, B)> fn) {
    fns[std::string(name)] = [this, fn]() -> void {
      A a;
      B b;
      {
        std::lock_guard<Mutex> lock(mut);
        readArg(a, b);
      }
      R r = fn(a, b);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
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
        readArg(a, b, c);
      }
      R r = fn(a, b, c);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
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
        readArg(a, b, c, d);
      }
      R r = fn(a, b, c, d);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
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
        readArg(a, b, c, d, e);
      }
      R r = fn(a, b, c, d, e);
      {
        std::lock_guard<Mutex> lock(mut);
        writeResult(r);
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
        readArg(a, b, c, d, e, f);
      }
      R r = fn(a, b, c, d, e, f);
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

#endif