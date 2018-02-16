#ifndef OUT_BASE_H
#define OUT_BASE_H

#include <memory>
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
      class Base
      {
      protected: 
         Base(std::ostream &os);

      public:
         virtual ~Base() = default;

         Base(Base const&) = default;
         Base &operator=(Base const&) = default;
         Base(Base&&) = default;
         Base &operator=(Base&&) = default;

         void write(Buffer const &data);

      private:
         virtual std::string encode(Buffer const &data) = 0;

         std::ostream &m_os;
      };
   } // namespace Ostream
} // namespace Io

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Ostream::Base>
operator<<(std::ostream &os, Io::Encoding enc);

#endif // OUT_BASE_H
