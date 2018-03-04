#include <memory>
#include <exception>
#include <fcntl.h>
#include <unistd.h>
#include "block.h"
#include "key.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   std::size_t const BLOCK_SIZE_BYTES = 16;
}

////////////////////////////////////////////////////////////////////////////////
Block::Block(Buffer const &data)
   : m_buffer(data)
{
   if(data.size() != BLOCK_SIZE_BYTES)
   {
      throw std::exception();
   }
}

////////////////////////////////////////////////////////////////////////////////
Buffer const &Block::buffer() const
{
   return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
std::size_t Block::size() const
{
   return m_buffer.size();
}

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Ostream::Base> 
operator<<(std::shared_ptr<Io::Ostream::Base> os, Block const &data)
{
   os << data.buffer();
   return os;
}
