#ifndef IN_ASCII_H
#define IN_ASCII_H

#include <iostream>
#include <string>
#include "in_base.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Istream
   {
      //////////////////////////////////////////////////////////////////////////
      class Ascii : public Base
      {
      public:
         Ascii(std::istream &is);
         virtual ~Ascii() = default;

         Ascii(Ascii const&) = default;
         Ascii &operator=(Ascii const&) = default;
         Ascii(Ascii&&) = default;
         Ascii &operator=(Ascii&&) = default;

      private:
         virtual Buffer decode(std::string const &data) override;
      };
   } // namespace Istream
} // namespace Io

#endif // IN_ASCII_H
