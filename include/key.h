#ifndef KEY_H
#define KEY_H

#include <cassert>
#include <cstdint>
#include "buffer.h"

class Key_base
{
protected:
   explicit Key_base(Buffer const &data);

public:
   virtual ~Key_base() = default;

   Key_base(Key_base const&) = default;
   Key_base &operator=(Key_base const&) = default;
   Key_base(Key_base&&) = default;
   Key_base &operator=(Key_base&&) = default;

   std::size_t size() const;
   Buffer const &buffer() const;

private:
   Buffer m_buffer;
};

template <std::size_t size_bits>
class Key : public Key_base 
{
   static_assert((size_bits == 256) || (size_bits == 128), "");
public:

   explicit Key(Buffer const &data)
      : Key_base(data)
   {
      assert(data.size() * 8 == size_bits);
   }

   virtual ~Key() = default;

   Key(Key const&) = default;
   Key &operator=(Key const&) = default;
   Key(Key&&) = default;
   Key &operator=(Key&&) = default;
};

#endif // KEY_H
