#ifndef ENCODING_MBEDTLS_H
#define ENCODING_MBEDTLS_H

#include <string>
#include "crypto.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Port
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Mbedtls
   {
      //////////////////////////////////////////////////////////////////////////
      class Encoding : public IEncoding
      {
      public:
         Encoding() = default;
         virtual ~Encoding() = default;
         Encoding(Encoding const&) = default;
         Encoding &operator=(Encoding const&) = default;
         Encoding(Encoding&&) = default;
         Encoding &operator=(Encoding&&) = default;

         std::string encode(Buffer const &data) override;
         Buffer decode(std::string const &data) override;
      };
   } // namespae Mbedtls
} // namespace Port

#endif // ENCODING _MBEDTLS_H

