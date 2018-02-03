#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <cstdint>

class Buffer
{
public: 
   Buffer(std::size_t size_bytes);
   ~Buffer() = default;

   Buffer(Buffer const&);
   Buffer &operator=(Buffer const&);
   Buffer(Buffer&&);
   Buffer &operator=(Buffer&&);

   uint8_t operator[](std::size_t index) const;
   uint8_t &operator[](std::size_t index);
   std::size_t size() const;
   uint8_t *get();
private:
   std::size_t m_size_bytes;
   uint8_t m_buffer[32];
};

std::ostream &operator<<(std::ostream &os, Buffer const &buffer);

#endif // BUFFER_H
