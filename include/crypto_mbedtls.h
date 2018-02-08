#ifndef CRYPTO_MBEDTLS_H
#define CRYPTO_MBEDTLS_H

#include <string>
#include <mbedtls/aes.h>
#include "crypto.h"
#include "buffer.h"
#include "block.h"
#include "key.h"

namespace Port
{
   namespace Mbedtls
   {

////////////////////////////////////////////////////////////////////////////////
class Cryptor : public ICrypto
{
protected:
   Cryptor(int mode);

public:
   virtual ~Cryptor();

   Cryptor(Cryptor const&);
   Cryptor &operator=(Cryptor const&);
   Cryptor(Cryptor&&) = delete;
   Cryptor &operator=(Cryptor&&) = delete;

   virtual Block operator()(Block const &data) override;

protected:
   mbedtls_aes_context m_aes_context;
   int const m_mode;
};

////////////////////////////////////////////////////////////////////////////////
class Encryptor : public Cryptor
{
public:
   Encryptor(Key_base const &key);
   virtual ~Encryptor() = default;
};

////////////////////////////////////////////////////////////////////////////////
class Decryptor : public Cryptor
{
public:
   Decryptor(Key_base const &key);
   virtual ~Decryptor() = default;
};

   } // namespae Mbedtls
} // namespace Port

#endif // CRYPTO_MBEDTLS_H

