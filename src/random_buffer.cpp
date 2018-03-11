#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "random_buffer.h"
#include "buffer.h"
#include "config.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   Buffer get_data(std::size_t size_bytes)
   {
      Buffer buffer(size_bytes);
      int fd = open(RANDOM_SOURCE, O_RDONLY);
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
Random_buffer::Random_buffer(std::size_t size_bytes)
   : Buffer(get_data(size_bytes))
{
}

