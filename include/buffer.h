#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   namespace Ostream
   {
      class Byte;
   }
   namespace Istream
   {
      class Byte;
   }
}

////////////////////////////////////////////////////////////////////////////////
class Buffer
{
public: 
   Buffer(uint8_t const * const data, std::size_t size_bytes);
   Buffer(std::string const &data);
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

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte &operator<<(Io::Ostream::Byte &os, Buffer const &data);
Io::Istream::Byte &operator>>(Io::Istream::Byte &is, Buffer &data);

#endif // BUFFER_H
