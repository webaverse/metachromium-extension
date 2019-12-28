#ifndef __zpp_serializer_h__
#define __zpp_serializer_h__

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <new>
#include <shared_mutex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#if __cplusplus >= 201703L
#include <optional>
#include <variant>
#endif

template <typename Item>
class binary
{
public:
    /**
     * Constructs the binary wrapper from pointer and count of items.
     */
    binary(Item * items, size_type count) : m_items(items), m_count(count)
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
    size_type size_in_bytes() const noexcept
    {
        return m_count * sizeof(Item);
    }

    /**
     * Returns the count of items in the binary wrapper.
     */
    size_type count() const noexcept
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
    size_type m_count{};
};

template <typename Item>
class managed_binary : public binary<Item>
{
public:
    managed_binary() {}
    managed_binary(size_type count) : m_managedItems(count)
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
  Serializer(unsigned char *data, size_t size) : m_data(data), m_read(data), m_write(data), m_size(size) {}
  template<typename T>
  Serializer &operator>>(Serializer &in, T &t) {
    static_assert(std::is_trivially_copyable<T>::value, "Must be trivially copyable");
    if (((in.m_data + in.m_size) - in.m_read) > sizeof(T)) {
      in.m_read = 0;
    }
    memcpy((void *)&t, in.m_read, sizeof(T));
    in.m_read += sizeof(T);
    return in;
  }
  template<>
  Serializer &operator>>(Serializer &in, std::string &t) {
    if (((in.m_data + in.m_size) - in.m_read) > t.size()) {
      in.m_read = 0;
    }
    memcpy((void *)t.data(), in.m_read, t.size());
    in.m_read += t.size();
    return in;
  }
  template<typename T>
  Serializer &operator>>(Serializer &in, binary<T> &t) {
    if (((in.m_data + in.m_size) - in.m_read) > t.size()) {
      in.m_read = 0;
    }
    memcpy((void *)t.data(), in.m_read, t.size());
    in.m_read += t.size();
    return in;
  }
  template<typename T>
  Serializer &operator<<(Serializer &out, const T &t) {
    static_assert(std::is_trivially_copyable<T>::value, "Must be trivially copyable");
    if (((out.m_data + out.m_size) - out.m_write) > sizeof(T)) {
      out.m_write = 0;
    }
    memcpy(out.m_write, (void *)&t, sizeof(T));
    out.m_write += sizeof(T);
    return out;
  }
  template<>
  Serializer &operator<<(Serializer &out, const std::string &t) {
    if (((out.m_data + out.m_size) - out.m_write) > t.size()) {
      out.m_write = 0;
    }
    memcpy(out.m_write, (void *)t.data(), t.size());
    out.m_write += t.size();
    return out;
  }
  template<typename T>
  Serializer &operator<<(Serializer &out, const binary<T> &t) {
    if (((out.m_data + out.m_size) - out.m_write) > t.size()) {
      out.m_write = 0;
    }
    memcpy(out.m_write, (void *)t.data(), t.size());
    out.m_write += t.size();
    return out;
  }
protected:
  unsigned char *m_data;
  unsigned char *m_read;
  unsigned char *m_write;
  size_t m_size;
};

#endif
