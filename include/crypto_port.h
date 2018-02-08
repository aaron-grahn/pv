#ifndef CRYPTO_PORT_H
#define CRYPTO_PORT_H

#ifdef USE_MBED_TLS
#include "crypto_mbedtls.h"
namespace Port
{
   using Encryptor = Mbedtls::Encryptor;
   using Decryptor = Mbedtls::Decryptor;
   using Hash = Mbedtls::Hash;
} // namespace Port
#endif // USE_MBEDTLS

#endif // CRYPTO_PORT_H
