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
      class Base64 : public Byte
      {
      public:
         Base64(std::ostream &os);
         virtual ~Base64() = default;

         Base64(Base64 const&) = default;
         Base64 &operator=(Base64 const&) = default;
         Base64(Base64&&) = default;
         Base64 &operator=(Base64&&) = default;

      private:
         virtual std::string encode(Buffer const &data) override;
      };
   } // namespace Ostream
} // namespace Io

#endif // OUT_ASCII_H
