#ifndef OUT_BASE_H
#define OUT_BASE_H

#include <iostream>
#include <string>
#include "io.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Ostream
   {
      //////////////////////////////////////////////////////////////////////////
      class Byte
      {
      protected: 
         Byte(std::ostream &os);

      public:
         virtual ~Byte() = default;

         Byte(Byte const&) = default;
         Byte &operator=(Byte const&) = default;
         Byte(Byte&&) = default;
         Byte &operator=(Byte&&) = default;

         void write(Buffer const &data);

      private:
         virtual std::string encode(Buffer const &data) = 0;

         std::ostream &m_os;
      };
   } // namespace Ostream
} // namespace Io

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte &operator<<(std::ostream &os, Io::Encoding enc);

#endif // OUT_BASE_H
