#ifndef OUT_ASCII_H
#define OUT_ASCII_H

#include <iostream>
#include <string>
#include "out_base.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Ostream
   {
      //////////////////////////////////////////////////////////////////////////
      class Ascii : public Base
      {
      public:
         Ascii(std::ostream &os);
         virtual ~Ascii() = default;

         Ascii(Ascii const&) = default;
         Ascii &operator=(Ascii const&) = default;
         Ascii(Ascii&&) = default;
         Ascii &operator=(Ascii&&) = default;

      private:
         virtual std::string encode(Buffer const &data) override;
      };
   } // namespace Ostream
} // namespace Io

#endif // OUT_ASCII_H
