#ifndef HASH_MBEDTLS_H
#define HASH_MBEDTLS_H

#include <string>
#include <mbedtls/md.h>
#include "crypto.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Port
{
   /////////////////////////////////////////////////////////////////////////////
   namespace Mbedtls
   {

////////////////////////////////////////////////////////////////////////////////
class Hash : public IHash
{
public:
   Hash();
   virtual ~Hash();

   Hash(Hash const&);
   Hash &operator=(Hash const&);
   Hash(Hash&&) = delete;
   Hash &operator=(Hash&&) = delete;

   virtual IHash &operator<<(std::string const &data) override;
   virtual IHash &operator<<(Buffer const &data) override;
   virtual IHash &operator>>(Buffer &out) override;

private:
   mbedtls_md_context_t m_md_context;
};

   } // namespae Mbedtls
} // namespace Port

#endif // HASH_MBEDTLS_H

