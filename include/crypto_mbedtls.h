#ifndef CRYPTO_MBEDTLS_H
#define CRYPTO_MBEDTLS_H

#include <string>
#include <mbedtls/md.h>
#include <mbedtls/aes.h>
#include "crypto.h"
#include "buffer.h"
#include "block.h"
#include "key.h"

class Ecb_mbedtls : public IEcb
{
public:
   Ecb_mbedtls(Key_base const &key);
   virtual ~Ecb_mbedtls();

   Ecb_mbedtls(Ecb_mbedtls const&);
   Ecb_mbedtls &operator=(Ecb_mbedtls const&);
   Ecb_mbedtls(Ecb_mbedtls&&) = delete;
   Ecb_mbedtls &operator=(Ecb_mbedtls&&) = delete;

   virtual Block encrypt(Block const &data) override;
   virtual Block decrypt(Block const &data) override;

private:
   mbedtls_aes_context m_encipher_context;
   mbedtls_aes_context m_decipher_context;
};

class Hash_mbedtls : public IHash
{
public:
   Hash_mbedtls();
   virtual ~Hash_mbedtls();

   Hash_mbedtls(Hash_mbedtls const&);
   Hash_mbedtls &operator=(Hash_mbedtls const&);
   Hash_mbedtls(Hash_mbedtls&&) = delete;
   Hash_mbedtls &operator=(Hash_mbedtls&&) = delete;

   virtual IHash &operator<<(std::string const &data) override;
   virtual IHash &operator<<(Buffer const &data) override;
   virtual Buffer finalize() override;
private:
   mbedtls_md_context_t m_md_context;
};

#endif // CRYPTO_MBEDTLS_H

