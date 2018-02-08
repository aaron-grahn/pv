#include <cassert>
#include <mbedtls/aes.h>
#include <cstring>
#include "crypto_mbedtls.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Cryptor::Cryptor(int mode)
   : m_aes_context()
   , m_mode(mode)
{
   mbedtls_aes_init(&m_aes_context);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Cryptor::~Cryptor()
{
   mbedtls_aes_free(&m_aes_context);
}

////////////////////////////////////////////////////////////////////////////////
Block Port::Mbedtls::Cryptor::operator()(Block const &data)
{
   Buffer cipher(data.size());
   int result = mbedtls_aes_crypt_ecb(&m_aes_context, 
                                      m_mode,
                                      data.buffer().get(),
                                      &cipher[0]);
   assert(result == 0);
   return Block(cipher);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Encryptor::Encryptor(Key_base const &key)
   : Port::Mbedtls::Cryptor(MBEDTLS_AES_ENCRYPT)
{
   int result = mbedtls_aes_setkey_enc(&m_aes_context, 
                                       key.buffer().get(), 
                                       key.size());
   assert(result == 0);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Decryptor::Decryptor(Key_base const &key)
   : Port::Mbedtls::Cryptor(MBEDTLS_AES_DECRYPT)
{
   int result = mbedtls_aes_setkey_dec(&m_aes_context, 
                                       key.buffer().get(), 
                                       key.size());
   assert(result == 0);
}

