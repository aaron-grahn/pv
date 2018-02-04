#include <cassert>
#include <iostream>
#include <iomanip>
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
   assert(data.size() == BLOCK_SIZE_BYTES);
}

////////////////////////////////////////////////////////////////////////////////
Buffer const &Block::buffer() const
{
   return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, Block const &block)
{
   os << std::dec << 128
      << "-bit block ["
      << block.buffer()
      << "]";
   return os;
}
