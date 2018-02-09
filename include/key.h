#ifndef KEY_H
#define KEY_H

#include <cassert>
#include <cstdint>
#include "buffer.h"

class Key_base
{
protected:
   Key_base(std::size_t size_bits);
   Key_base(Buffer const &data);

public:
   virtual ~Key_base() = default;

   Key_base(Key_base const&) = default;
   Key_base &operator=(Key_base const&) = delete;
   Key_base(Key_base&&) = delete;
   Key_base &operator=(Key_base&&) = delete;

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
   Key()
      : Key_base(size_bits)
   {
   }

   Key(Buffer const &data)
      : Key_base(data)
   {
      assert(data.size() * 8 == size_bits);
   }

   virtual ~Key() = default;

   Key(Key const&) = default;
   Key &operator=(Key const&) = delete;
   Key(Key&&) = delete;
   Key &operator=(Key&&) = delete;
};


#endif // KEY_H
