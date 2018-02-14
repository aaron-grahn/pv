#ifndef IN_BASE_H
#define IN_BASE_H

#include <iostream>
#include <string>
#include "io.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Istream
   {
      //////////////////////////////////////////////////////////////////////////
      class Byte
      {
      protected: 
         Byte(std::istream &is);

      public:
         virtual ~Byte() = default;

         Byte(Byte const&) = default;
         Byte &operator=(Byte const&) = default;
         Byte(Byte&&) = default;
         Byte &operator=(Byte&&) = default;

         Buffer read();

      private:
         std::istream &m_is;

         virtual Buffer decode(std::string const &data) = 0;
      };
   } // namespace Istream
} // namespace Io

////////////////////////////////////////////////////////////////////////////////
Io::Istream::Byte &operator>>(std::istream &is, Io::Encoding enc);

#endif // IN_BASE_H
