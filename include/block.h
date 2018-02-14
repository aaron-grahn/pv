#ifndef BLOCK_H
#define BLOCK_H

#include "io.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
class Block
{
public:
   explicit Block(Buffer const &data);
   virtual ~Block() = default;

   Block(Block const&) = default;
   Block &operator=(Block const&) = default;
   Block(Block&&) = default;
   Block &operator=(Block&&) = default;

   Buffer const &buffer() const;
   std::size_t size() const;

private:
   Buffer m_buffer;
};

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Base &operator<<(Io::Ostream::Base &os, Block const &data);

#endif // BLOCK_H
