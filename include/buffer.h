#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   namespace Ostream
   {
      class Base;
   }
   namespace Istream
   {
      class Base;
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
std::shared_ptr<Io::Ostream::Base> 
operator<<(std::shared_ptr<Io::Ostream::Base> os, Buffer const &data);

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Istream::Base> 
operator>>(std::shared_ptr<Io::Istream::Base> is, Buffer &data);

#endif // BUFFER_H
