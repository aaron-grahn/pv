#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "buffer.h"
#include "crypto_port.h"
#include "io.h"

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(uint8_t const * const data, std::size_t size_bytes)
   : m_size_bytes(size_bytes)
   , m_buffer()
{
   assert(m_size_bytes <= 32);
   static_cast<void>(memcpy(m_buffer, data, m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(std::string const &data)
   : m_size_bytes(data.size())
   , m_buffer()
{
   assert(m_size_bytes <= 32);
   static_cast<void>(memcpy(m_buffer, data.c_str(), m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(size_t size_bytes)
   : m_size_bytes(size_bytes)
   , m_buffer()
{
   assert(size_bytes <= 32);
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(Buffer const &other)
   : m_size_bytes(other.m_size_bytes)
   , m_buffer()
{
   static_cast<void>(memcpy(m_buffer, other.m_buffer, other.m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer &Buffer::operator=(Buffer const &other)
{
   m_size_bytes = other.m_size_bytes;
   static_cast<void>(memcpy(m_buffer, other.m_buffer, other.m_size_bytes));
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(Buffer &&other)
   : m_size_bytes(other.m_size_bytes)
   , m_buffer()
{
   static_cast<void>(memcpy(m_buffer, other.m_buffer, other.m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer &Buffer::operator=(Buffer &&other)
{
   m_size_bytes = other.m_size_bytes;
   static_cast<void>(memcpy(m_buffer, other.m_buffer, other.m_size_bytes));
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
uint8_t Buffer::operator[](size_t index) const
{
   return m_buffer[index];
}

////////////////////////////////////////////////////////////////////////////////
uint8_t &Buffer::operator[](size_t index)
{
   return m_buffer[index];
}

////////////////////////////////////////////////////////////////////////////////
size_t Buffer::size() const
{
   return m_size_bytes;
}

////////////////////////////////////////////////////////////////////////////////
uint8_t const *Buffer::get() const
{
   return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte &operator<<(Io::Ostream::Byte &os, Buffer const &data)
{
   os.write(data);
   return os;
}

////////////////////////////////////////////////////////////////////////////////
Io::Istream::Byte &operator>>(Io::Istream::Byte &is, Buffer &data)
{
   data = is.read();
   return is;
}
