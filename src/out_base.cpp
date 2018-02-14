#include <memory>
#include <iostream>
#include <cassert>
#include "io.h"
#include "out_base.h"
#include "out_hex.h"
#include "out_ascii.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte::Byte(std::ostream &os)
   : m_os(os)
{
}

////////////////////////////////////////////////////////////////////////////////
void Io::Ostream::Byte::write(Buffer const &data)
{
   m_os << encode(data);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace
{
   // If you've ever read "The Ones who Walk Away from Omelas," you'll
   // understand this code.
   std::unique_ptr<Io::Ostream::Byte> out(nullptr);

   /////////////////////////////////////////////////////////////////////////////
   Io::Ostream::Byte &get_stream(std::ostream &os, Io::Encoding enc)
   {
      if(enc == Io::Encoding::Hex)
      {
         out.reset(new Io::Ostream::Hex(os));
      }
      else if(enc == Io::Encoding::Ascii)
      {
         out.reset(new Io::Ostream::Base64(os));
      }
      else
      {
         assert(false);
      }
      return *out;
   }
} // namespace

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte &operator<<(std::ostream &os, Io::Encoding enc)
{
   return get_stream(os, enc);
}

