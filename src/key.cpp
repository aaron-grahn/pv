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
      uint8_t *cbuf = &buffer[0];
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
Key_base::Key_base(Buffer const &data)
   : m_buffer(data)
{
}

////////////////////////////////////////////////////////////////////////////////
std::size_t Key_base::size() const
{
   std::size_t size_bits = m_buffer.size() * 8;
   return size_bits;
}

////////////////////////////////////////////////////////////////////////////////
Buffer const &Key_base::buffer() const
{
   return m_buffer;
}
