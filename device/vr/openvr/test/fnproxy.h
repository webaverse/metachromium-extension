#include <map>
#include <mutex>
// #include <semaphore>
#include <functional>
#include "device/vr/openvr/test/serializer.h"

// #define BUF_SIZE 256
/* TCHAR szName[]=TEXT("Global\\MyFileMappingObject");
TCHAR szMsg[]=TEXT("Message from first process.");

int _tmain()
{
   HANDLE hMapFile;
   LPCTSTR pBuf;

   hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 BUF_SIZE,                // maximum object size (low-order DWORD)
                 szName);                 // name of mapping object

   if (hMapFile == NULL)
   {
      _tprintf(TEXT("Could not create file mapping object (%d).\n"),
             GetLastError());
      return 1;
   }
   pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,
                        0,
                        BUF_SIZE);

   if (pBuf == NULL)
   {
      _tprintf(TEXT("Could not map view of file (%d).\n"),
             GetLastError());

       CloseHandle(hMapFile);

      return 1;
   }
} */

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

class FnProxy {
public:
  // std::mutex mut;
  // std::semaphore sem;
  // std::vector<unsigned char> data;
  staticvector<unsigned char> data2;
  std::map<std::string, std::function<void()>> fns;
  zpp::serializer::memory_input_archive in;
  zpp::serializer::memory_output_archive out;
  
  FnProxy() : data2((unsigned char *)allocateShared("Local\\OpenVrProxy", 4096), 0), in(data2), out(data2) {}

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