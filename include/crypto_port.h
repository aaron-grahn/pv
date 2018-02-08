#ifndef CRYPTO_PORT_H
#define CRYPTO_PORT_H

#ifdef USE_MBED_TLS
#include "crypto_mbedtls.h"
namespace Port
{
   using Encryptor = Mbedtls::Encryptor;
   using Decryptor = Mbedtls::Decryptor;
   using Hash = Mbedtls::Hash;
   using Base64 = Mbedtls::Base64;
} // namespace Port
#endif // USE_MBEDTLS

#endif // CRYPTO_PORT_H
