#ifndef CRYPTO_PORT_H
#define CRYPTO_PORT_H

#include "crypto_mbedtls.h"
namespace Port
{
   using Encryptor = Mbedtls::Encryptor;
   using Decryptor = Mbedtls::Decryptor;
   using Hash = Mbedtls::Hash;
} // namespace Port

#endif // CRYPTO_PORT_H
