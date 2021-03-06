#include <memory>
#include "io.h"
#include "key.h"
#include "buffer.h"
#include "block.h"

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

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Ostream::Base> 
operator<<(std::shared_ptr<Io::Ostream::Base> os, Key_base const &data)
{
   os << data.buffer();
   return os;
}

