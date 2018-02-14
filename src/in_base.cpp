#include <memory>
#include <iostream>
#include <string>
#include <cassert>
#include "io.h"
#include "in_base.h"
#include "in_ascii.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Io::Istream::Byte::Byte(std::istream &is)
   : m_is(is)
{
}

////////////////////////////////////////////////////////////////////////////////
Buffer Io::Istream::Byte::read()
{
   std::string data;
   m_is >> data;
   return decode(data);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace
{
   // If you've ever read "The Ones who Walk Away from Omelas," you'll
   // understand this code.
   std::unique_ptr<Io::Istream::Byte> in(nullptr); 

   /////////////////////////////////////////////////////////////////////////////
   Io::Istream::Byte &get_stream(std::istream &is, Io::Encoding enc)
   {
      if(enc == Io::Encoding::Ascii)
      {
         in.reset(new Io::Istream::Base64(is));
      }
      else
      {
         assert(false);
      }
      return *in;
   }
} // namespace

////////////////////////////////////////////////////////////////////////////////
Io::Istream::Byte &operator>>(std::istream &is, Io::Encoding enc)
{
   return get_stream(is, enc);
}

