#ifndef RANDOM_BUFFER_H
#define RANDOM_BUFFER_H

#include "buffer.h"

class Random_buffer : public Buffer
{
public:
   Random_buffer(std::size_t size_bytes);
   ~Random_buffer() = default;

   Random_buffer(Random_buffer const&) = default;
   Random_buffer &operator=(Random_buffer const&) = default;
   Random_buffer(Random_buffer&&) = default;
   Random_buffer &operator=(Random_buffer&&) = default;
};

#endif // RANDOM_BUFFER_H
