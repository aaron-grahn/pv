#ifndef OUT_HEX_H
#define OUT_HEX_H

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
      class Hex : public Base
      {
      public:
         Hex(std::ostream &os);
         virtual ~Hex() = default;

         Hex(Hex const&) = default;
         Hex &operator=(Hex const&) = default;
         Hex(Hex&&) = default;
         Hex &operator=(Hex&&) = default;

      private:
         virtual std::string encode(Buffer const &data) override;
      };
   } // namespace Ostream
} // namespace Io

#endif // OUT_HEX_H
