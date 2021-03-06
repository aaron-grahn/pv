#include <memory>
#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include "buffer.h"
#include "crypto_port.h"
#include "out_base.h"
#include "in_base.h"

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(uint8_t const * const data, std::size_t size_bytes)
   : m_size_bytes(size_bytes)
   , m_buffer()
{
   if(m_size_bytes > 32)
   {
      throw std::exception();
   }
   static_cast<void>(memcpy(m_buffer, data, m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(std::string const &data)
   : m_size_bytes(data.size())
   , m_buffer()
{
   if(m_size_bytes > 32)
   {
      throw std::exception();
   }
   static_cast<void>(memcpy(m_buffer, data.c_str(), m_size_bytes));
}

////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer(size_t size_bytes)
   : m_size_bytes(size_bytes)
   , m_buffer()
{
   if(m_size_bytes > 32)
   {
      throw std::exception();
   }
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
std::shared_ptr<Io::Ostream::Base> 
operator<<(std::shared_ptr<Io::Ostream::Base> os, Buffer const &data)
{
   os->write(data);
   return os;
}

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Istream::Base> 
operator>>(std::shared_ptr<Io::Istream::Base> is, Buffer &data)
{
   data = is->read();
   return is;
}
