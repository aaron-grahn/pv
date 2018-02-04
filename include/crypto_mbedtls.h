#ifndef CRYPTO_MBEDTLS_H
#define CRYPTO_MBEDTLS_H

#include <string>
#include <mbedtls/md.h>
#include "crypto.h"
#include "buffer.h"
#include "block.h"
#include "key.h"

class Ecb_mbedtls : public IEcb
{
public:
   virtual Block ecb_encrypt(Key_base const &key, Block const &data) override;
   virtual Block ecb_decrypt(Key_base const &key, Block const &data) override;
};

class Hash_mbedtls : public IHash
{
public:
   Hash_mbedtls();
   virtual ~Hash_mbedtls();

   Hash_mbedtls(Hash_mbedtls const&);
   Hash_mbedtls &operator=(Hash_mbedtls const&);
   Hash_mbedtls(Hash_mbedtls&&);
   Hash_mbedtls &operator=(Hash_mbedtls&&);

   virtual IHash &operator<<(std::string const &data) override;
   virtual IHash &operator<<(Buffer const &data) override;
   virtual Buffer finalize() override;
private:
   mbedtls_md_context_t m_md_context;
};

#endif // CRYPTO_MBEDTLS_H

