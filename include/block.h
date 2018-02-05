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
   Block &operator=(Block const&) = delete;
   Block(Block&&) = delete;
   Block &operator=(Block&&) = delete;

   Buffer const &buffer() const;

private:
   Buffer const m_buffer;
};

std::ostream &operator<<(std::ostream &os, Block const &block);


#endif // BLOCK_H
