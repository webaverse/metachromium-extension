#ifndef __serializer_h__
#define __serializer_h__

#include <vector>
#include <mutex>

#include "device/vr/openvr/test/out.h"

/* template<typename T>
class staticvector {
public:
  T *d;
  size_t &s;
  // staticvector<T>() : d(nullptr), s(0) {}
  staticvector<T>(T *d) : d((T *)((unsigned char *)d + sizeof(size_t))), s(*((size_t *)d)) {}
  // staticvector<T>(const staticvector<T> &other) : d(other.data()), s(other.size()) {}
  T *data() {
    return d;
  }
  size_t size() {
    return s;
  }
  void resize(size_t newS) {
    s = newS;
  }
  T *begin() {
    return d;
  }
  T *end() {
    return d + s;
  }
  void erase(T *x, T *y) {
    memcpy(x, y, (end() - y) * sizeof(T));
    s -= y - x;
  }
}; */

template <typename Item>
class binary
{
public:
    /**
     * Constructs the binary wrapper from pointer and count of items.
     */
    binary(Item * items, size_t count) : m_items(items), m_count(count)
    {
    }
    
    binary(const binary<Item> &o) : m_items(o.m_items), m_count(o.m_count)
    {
    }
    
    binary() : m_items(nullptr), m_count(0)
    {
    }

    /**
     * Returns a pointer to the first item.
     */
    Item * data() const noexcept
    {
        return m_items;
    }

    /**
     * Returns the size in bytes of the binary data.
     */
    size_t size() const noexcept
    {
        return m_count;
    }

    /**
     * Returns the count of items in the binary wrapper.
     */
    size_t count() const noexcept
    {
        return m_count;
    }

protected:
    /**
     * Pointer to the items.
     */
    Item * m_items = nullptr;

    /**
     * The number of items.
     */
    size_t m_count{};
};

template <typename Item>
class managed_binary : public binary<Item>
{
public:
    managed_binary() {}
    managed_binary(Item *t, size_t count) : m_managedItems(count)
    {
      memcpy(m_managedItems.data(), (void *)t, count * sizeof(Item));
      m_items = m_managedItems.data();
      m_count = m_managedItems.size();
    }
    managed_binary(size_t count) : m_managedItems(count)
    {
      m_items = m_managedItems.data();
      m_count = m_managedItems.size();
    }
    managed_binary(managed_binary<Item> &&o) : m_managedItems(std::move(o.m_managedItems))
    {
      m_items = m_managedItems.data();
      m_count = m_managedItems.size();
    }

    managed_binary &operator=(managed_binary<Item> &&o) {
      m_managedItems = std::move(o.m_managedItems);
      m_items = m_managedItems.data();
      m_count = m_managedItems.size();
      return *this;
    }
protected:
    std::vector<Item> m_managedItems;
};

class Serializer {
public:
  Serializer(size_t id, unsigned char *data, unsigned char *&read, unsigned char *&write, size_t initSize);
  template<typename T>
  Serializer &operator>>(T &t) {
    Serializer &in = *this;
    static_assert(std::is_trivially_copyable<T>::value, "Must be trivially copyable");
    // getOut() << "reader T 1 " << (in.m_read - in.m_data) << std::endl;
    if ((in.m_read + sizeof(T)) > (in.m_data + m_size)) {
      // getOut() << "reset reader T " << (in.m_read - in.m_data) << " " << sizeof(T) << std::endl;
      in.m_read = in.m_data;
    }
    // getOut() << "reader T 2 " << (in.m_read - in.m_data) << std::endl;

    memcpy((void *)&t, in.m_read, sizeof(T));
    // getOut() << "read raw " << id << " " << sizeof(T) << " " << (void *)in.m_read << std::endl;
    in.m_read += sizeof(T);
    
    // getOut() << "reader T 3 " << (in.m_read - in.m_data) << std::endl;

    return in;
  }
  template<>
  Serializer &operator>>(std::string &t) {
    Serializer &in = *this;

    if (((uintptr_t)in.m_read) % 8 != 0) {
      in.m_read += 8 - (((uintptr_t)in.m_read) % 8);
    }
    
    // getOut() << "reader string 1 " << (in.m_read - in.m_data) << std::endl;
    if ((in.m_read + sizeof(size_t)) > (in.m_data + m_size)) {
      // getOut() << "reset reader string " << (in.m_read - in.m_data) << " " << sizeof(size_t) << std::endl;
      in.m_read = in.m_data;
    }
    
    // getOut() << "reader string 2 " << (in.m_read - in.m_data) << std::endl;

    size_t size = *((size_t *)in.m_read);
    // getOut() << "read size 1 " << id << " " << size << " " << (void *)in.m_read << std::endl;
    in.m_read += sizeof(size_t);
    
    if ((in.m_read + size) > (in.m_data + m_size)) {
      // getOut() << "reset reader string 2 " << (in.m_read - in.m_data) << " " << size << std::endl;
      in.m_read = in.m_data;
    }
    
    // getOut() << "reader string 3 " << (in.m_read - in.m_data) << " " << size << std::endl;

    t = std::string((char *)in.m_read, size);
    in.m_read += size;
    
    if (size > 512*1024) {
      // getOut() << "size overflow 1 " << id << " " << size << " " << (void *)in.m_read << std::endl;
      abort();
    }
    
    // getOut() << "reader string 4 " << (in.m_read - in.m_data) << std::endl;

    return in;
  }
  template<typename T>
  Serializer &operator>>(managed_binary<T> &t) {
    Serializer &in = *this;
    
    if (((uintptr_t)in.m_read) % 8 != 0) {
      in.m_read += 8 - (((uintptr_t)in.m_read) % 8);
    }
    
    // getOut() << "reader binary 1 " << (in.m_read - in.m_data) << std::endl;
    if ((in.m_read + sizeof(size_t)) > (in.m_data + m_size)) {
      // getOut() << "reset reader managed_binary " << (in.m_read - in.m_data) << " " << sizeof(size_t) << std::endl;
      in.m_read = in.m_data;
    }
    
    // getOut() << "reader binary 2 " << (in.m_read - in.m_data) << std::endl;

    size_t size = *((size_t *)in.m_read);
    // getOut() << "read size 2 " << id << " " << size << " " << sizeof(T) << " " << (void *)in.m_read << std::endl;
    in.m_read += sizeof(size_t);
    
    if (size > 512*1024) {
      // getOut() << "size overflow 2 " << size << " " << (void *)in.m_read << std::endl;
      abort();
    }
    
    if ((in.m_read + size*sizeof(T)) > (in.m_data + m_size)) {
      // getOut() << "reset reader managed_binary 2 " << id << " " << (in.m_read - in.m_data) << " " << size << " " << sizeof(T) << std::endl;
      in.m_read = in.m_data;
    }
    
    // getOut() << "reader binary 3 " << (in.m_read - in.m_data) << " " << size << std::endl;

    t = managed_binary<T>((T *)in.m_read, size);
    in.m_read += size * sizeof(T);
    
    // getOut() << "reader binary 4 " << (in.m_read - in.m_data) << std::endl;

    return in;
  }
  template<int I = 0, typename... Ts>
  inline typename std::enable_if<I == sizeof...(Ts), void>::type deserializeTuple(std::tuple<Ts...> &ts) {
    // nothing
  }
  template<int I = 0, typename... Ts>
  inline typename std::enable_if<I < sizeof...(Ts), void>::type deserializeTuple(std::tuple<Ts...> &ts) {
    *this >> std::get<I>(ts);
    deserializeTuple<I + 1, Ts...>(ts);
  }
  template<typename... Ts>
  Serializer &operator>>(std::tuple<Ts...> &ts) {
    deserializeTuple<0, Ts...>(ts);
    return *this;
  }
  template<typename T>
  Serializer &operator<<(const T &t) {
    Serializer &out = *this;
    // getOut() << "writer T 1 " << (out.m_write - out.m_data) << std::endl;
    static_assert(std::is_trivially_copyable<T>::value, "Must be trivially copyable");
    if ((out.m_write + sizeof(T)) > (out.m_data + m_size)) {
      // getOut() << "reset writer T " << (out.m_write - out.m_data) << " " << sizeof(T) << std::endl;
      out.m_write = out.m_data;
    }

    // getOut() << "writer T 2 " << (out.m_write - out.m_data) << std::endl;
    
    /* if (((uintptr_t)out.m_write) % 8 != 0) {
      getOut() << "unaligned size T " << (void *)out.m_write << std::endl;
    } */

    memcpy(out.m_write, (void *)&t, sizeof(T));
    // getOut() << "write raw " << id << " " << sizeof(T) << " " << (void *)out.m_write << std::endl;
    out.m_write += sizeof(T);
    
    // getOut() << "writer T 3 " << (out.m_write - out.m_data) << std::endl;

    return out;
  }
  template<>
  Serializer &operator<<(const std::string &t) {
    Serializer &out = *this;
    
    if (((uintptr_t)out.m_write) % 8 != 0) {
      // getOut() << "unaligned size string " << (void *)out.m_write << std::endl;
      out.m_write += 8 - (((uintptr_t)out.m_write) % 8); 
    }
    
    // getOut() << "writer string 1 " << (out.m_write - out.m_data) << std::endl;
    if ((out.m_write + sizeof(size_t)) > (out.m_data + m_size)) {
      // getOut() << "reset writer string " << (out.m_write - out.m_data) << " " << sizeof(size_t) << std::endl;
      out.m_write = out.m_data;
    }
    
    // getOut() << "writer string 2 " << (out.m_write - out.m_data) << std::endl;

    *((size_t *)out.m_write) = t.size();
    // getOut() << "write size 1 " << id << " " << t.size() << " " << (void *)out.m_write << std::endl;
    out.m_write += sizeof(size_t);
    
    if ((out.m_write + t.size()) > (out.m_data + m_size)) {
      // getOut() << "reset writer string 2 " << (out.m_write - out.m_data) << " " << t.size() << std::endl;
      out.m_write = out.m_data;
    }
    
    // getOut() << "writer string 3 " << (out.m_write - out.m_data) << " " << t.size() << std::endl;
    
    memcpy(out.m_write, (void *)t.data(), t.size());
    out.m_write += t.size();
    
    // getOut() << "writer string 4 " << (out.m_write - out.m_data) << std::endl;

    return out;
  }
  template<typename T>
  Serializer &operator<<(const binary<T> &t) {
    Serializer &out = *this;
    
    if (((uintptr_t)out.m_write) % 8 != 0) {
      // getOut() << "unaligned size binary " << (void *)out.m_write << std::endl;
      out.m_write += 8 - (((uintptr_t)out.m_write) % 8); 
    }
    
    // getOut() << "writer binary 1 " << (out.m_write - out.m_data) << std::endl;
    if ((out.m_write + sizeof(size_t)) > (out.m_data + m_size)) {
      // getOut() << "reset writer binary " << (out.m_write - out.m_data) << " " << sizeof(size_t) << std::endl;
      out.m_write = out.m_data;
    }

    // getOut() << "writer binary 2 " << (out.m_write - out.m_data) << std::endl;
    *((size_t *)out.m_write) = t.size();
    // getOut() << "write size 2 " << id << " " << t.size() << " " << sizeof(T) << " " << (void *)out.m_write << std::endl;
    // getOut() << "writer binary 3 " << (out.m_write - out.m_data) << " " << t.size() << std::endl;
    out.m_write += sizeof(size_t);
    // getOut() << "writer binary 4 " << (out.m_write - out.m_data) << std::endl;

    if ((out.m_write + t.size()*sizeof(T)) > (out.m_data + m_size)) {
      // getOut() << "reset writer binary 2 " << (out.m_write - out.m_data) << " " << t.size() << " " << sizeof(T) << std::endl;
      out.m_write = out.m_data;
    }

    memcpy(out.m_write, (void *)t.data(), t.size() * sizeof(T));
    // getOut() << "writer binary 5 " << (out.m_write - out.m_data) << std::endl;
    out.m_write += t.size() * sizeof(T);
    // getOut() << "writer binary 6 " << (out.m_write - out.m_data) << std::endl;

    return out;
  }
  template<typename T>
  Serializer &operator<<(const managed_binary<T> &t) {
    return *this << *((const binary<T> *)(&t));
  }
  template<int I = 0, typename... Ts>
  inline typename std::enable_if<I == sizeof...(Ts), void>::type serializeTuple(std::tuple<Ts...> &ts) {
    // nothing
  }
  template<int I = 0, typename... Ts>
  inline typename std::enable_if<I < sizeof...(Ts), void>::type serializeTuple(std::tuple<Ts...> &ts) {
    *this << std::get<I>(ts);
    serializeTuple<I + 1, Ts...>(ts);
  }
  template<typename... Ts>
  Serializer &operator<<(std::tuple<Ts...> &ts) {
    serializeTuple<0, Ts...>(ts);
    return *this;
  }
// protected:
public:
  size_t id;
  unsigned char * const m_data;
  unsigned char *m_read;
  unsigned char *m_write;
  const size_t m_size;
};

#endif
