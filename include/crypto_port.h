#ifndef CRYPTO_PORT_H
#define CRYPTO_PORT_H

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef USE_MBED_TLS
#include "crypto_mbedtls.h"
#include "hash_mbedtls.h"
#include "encoding_mbedtls.h"

////////////////////////////////////////////////////////////////////////////////
namespace Port
{
   using Encryptor = Mbedtls::Encryptor;
   using Decryptor = Mbedtls::Decryptor;
   using Hash = Mbedtls::Hash;
   using Encoding = Mbedtls::Encoding;
} // namespace Port

#endif // USE_MBEDTLS

#endif // CRYPTO_PORT_H
