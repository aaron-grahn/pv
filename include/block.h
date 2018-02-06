#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdint>
#include "buffer.h"

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

std::ostream &operator<<(std::ostream &os, Block const &block);


#endif // BLOCK_H
