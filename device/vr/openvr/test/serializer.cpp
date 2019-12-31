#include "device/vr/openvr/test/serializer.h"

Serializer::Serializer(size_t id, unsigned char *data, uintptr_t &read, uintptr_t &write, size_t size) : id(id), m_data(data), m_read(read), m_write(write), m_size(size) {
  // m_read = 0;
  // m_write = 0;
  // getOut() << "got read write "  << m_read << " " << m_write << std::endl;
}