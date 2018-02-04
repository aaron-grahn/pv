#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <cstdint>

class Buffer
{
public: 
   Buffer(uint8_t const * const data, std::size_t size_bytes);
   Buffer(std::size_t size_bytes);
   ~Buffer() = default;

   Buffer(Buffer const&);
   Buffer &operator=(Buffer const&);
   Buffer(Buffer&&);
   Buffer &operator=(Buffer&&);

   uint8_t operator[](std::size_t index) const;
   uint8_t &operator[](std::size_t index);
   std::size_t size() const;
   uint8_t const *get() const;
private:
   std::size_t m_size_bytes;
   uint8_t m_buffer[32];
};

std::ostream &operator<<(std::ostream &os, Buffer const &buffer);

#endif // BUFFER_H
