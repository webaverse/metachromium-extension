#include "device/vr/openvr/test/serializer.h"

Serializer::Serializer(size_t id, unsigned char *data, unsigned char *&read, unsigned char *&write, size_t size) : id(id), m_data(data), m_read(data), m_write(data), m_size(size) {
  m_read = m_data;
  m_write = m_data;
}