#include "device/vr/openvr/test/serializer.h"

Serializer::Serializer(unsigned char *data, size_t size) : m_data(data), m_read(data), m_write(data), m_size(size) {}