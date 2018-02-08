#ifndef BASE64_MBEDTLS_H
#define BASE64_MBEDTLS_H

#include <string>
#include "crypto.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Port
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Mbedtls
   {

////////////////////////////////////////////////////////////////////////////////
class Base64 : public IBase64
{
public:
   Base64() = default;
   virtual ~Base64() = default;
   Base64(Base64 const&) = default;
   Base64 &operator=(Base64 const&) = default;
   Base64(Base64&&) = default;
   Base64 &operator=(Base64&&) = default;

   std::string encode(Buffer const &data) override;
   Buffer decode(std::string const &data) override;
};

   } // namespae Mbedtls
} // namespace Port

#endif // BASE64_MBEDTLS_H

