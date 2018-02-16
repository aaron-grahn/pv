#ifndef IN_BASE_H
#define IN_BASE_H

#include <memory>
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
      class Base
      {
      protected: 
         Base(std::istream &is);

      public:
         virtual ~Base() = default;

         Base(Base const&) = default;
         Base &operator=(Base const&) = default;
         Base(Base&&) = default;
         Base &operator=(Base&&) = default;

         Buffer read();

      private:
         std::istream &m_is;

         virtual Buffer decode(std::string const &data) = 0;
      };
   } // namespace Istream
} // namespace Io

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Io::Istream::Base> 
operator>>(std::istream &is, Io::Encoding enc);

#endif // IN_BASE_H
