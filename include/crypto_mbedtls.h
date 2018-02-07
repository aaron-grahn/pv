#ifndef CRYPTO_MBEDTLS_H
#define CRYPTO_MBEDTLS_H

#include <string>
#include <mbedtls/md.h>
#include <mbedtls/aes.h>
#include "crypto.h"
#include "buffer.h"
#include "block.h"
#include "key.h"

namespace Port
{
   namespace Mbedtls
   {

class Cryptor : public IEcb
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

class Encryptor : public Cryptor
{
public:
   Encryptor(Key_base const &key);
   virtual ~Encryptor() = default;
};

class Decryptor : public Cryptor
{
public:
   Decryptor(Key_base const &key);
   virtual ~Decryptor() = default;
};

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
   virtual Buffer finalize() override;
private:
   mbedtls_md_context_t m_md_context;
};

   } // namespae Mbedtls
} // namespace Port

#endif // CRYPTO_MBEDTLS_H

