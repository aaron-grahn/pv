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
      class Base64 : public Byte
      {
      public:
         Base64(std::istream &is);
         virtual ~Base64() = default;

         Base64(Base64 const&) = default;
         Base64 &operator=(Base64 const&) = default;
         Base64(Base64&&) = default;
         Base64 &operator=(Base64&&) = default;

      private:
         virtual Buffer decode(std::string const &data) override;
      };
   } // namespace Istream
} // namespace Io

#endif // IN_ASCII_H
