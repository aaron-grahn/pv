#include <cassert>
#include <iostream>
#include <iomanip>
#include <fcntl.h>
#include <unistd.h>
#include "key.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   Buffer get_key(std::size_t size_bytes)
   {
      Buffer buffer(size_bytes);
      int fd = open("/dev/urandom", O_RDONLY);
      std::size_t bytes_read = 0;
      uint8_t *cbuf = buffer.get();
      while(bytes_read < size_bytes)
      {
         bytes_read += read(fd, cbuf + bytes_read, size_bytes - bytes_read);
      }
      close(fd);
      return buffer;
   }
}

////////////////////////////////////////////////////////////////////////////////
Key_base::Key_base(std::size_t size_bits)
   : m_buffer(get_key(size_bits / 8))
{
}

////////////////////////////////////////////////////////////////////////////////
std::size_t Key_base::size() const
{
   return m_buffer.size() * 8;
}

////////////////////////////////////////////////////////////////////////////////
Buffer const &Key_base::buffer() const
{
   return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, Key_base const &key)
{
   os << std::dec << key.size()
      << "-bit key ["
      << key.buffer()
      << "]";
   return os;
}
