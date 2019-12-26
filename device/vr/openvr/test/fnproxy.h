#include <map>
#include <mutex>
// #include <semaphore>
#include <functional>
#include "device/vr/openvr/test/serializer.h"

class FnProxy {
public:
  std::mutex mut;
  // std::semaphore sem;
  std::vector<unsigned char> data;
  // staticvector<unsigned char> data2;
  std::map<std::string, std::function<void()>> fns;
  zpp::serializer::memory_input_archive in;
  zpp::serializer::memory_output_archive out;
  
  FnProxy() : /*data(4096), data2(data.data(), 0), */in(data), out(data) {}

  template<const char *name, typename R, typename A>
  R call(A a) {
    std::function<void()> &f = fns.find(std::string(name))->second;
    out(a);
    f();
    R r;
    in(r);
    return r;
  }
  template<const char *name, typename A>
  void callV(A a) {
    std::function<void()> &f = fns.find(std::string(name))->second;
    out(a);
    f();
  }
  
  template<const char *name, typename R, typename A, R (*f)(A)>
  void reg() {
    fns[std::string(name)] = [this]() -> void {
      A a;
      in(a);
      R r = f(a);
      out(r);
    };
  }
  template<const char *name, typename A, void (*f)(A)>
  void regV() {
    fns[std::string(name)] = [this]() -> void {
      A a;
      in(a);
      f(a);
    };
  }
};