#include <cassert>
#include <mbedtls/md.h>
#include <mbedtls/aes.h>
#include <cstring>
#include "crypto_mbedtls.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace
{
   int const NO_HMAC = 0;
   std::size_t HASH_SIZE_BYTES = 32;
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Hash::Hash()
   : IHash()
   , m_md_context()
{
   mbedtls_md_info_t const *md_info = 
      mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
   mbedtls_md_init(&m_md_context);
   assert(mbedtls_md_setup(&m_md_context, md_info, NO_HMAC) == 0);
   assert(mbedtls_md_starts(&m_md_context) == 0);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Hash::~Hash()
{
   mbedtls_md_free(&m_md_context);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Hash::Hash(Hash const &other)
   : m_md_context()
{
   int result = mbedtls_md_clone(&m_md_context, &other.m_md_context);
   assert(result == 0);
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Hash 
&Port::Mbedtls::Hash::operator=(Hash const &other)
{
   mbedtls_md_free(&m_md_context);
   int result = mbedtls_md_clone(&m_md_context, &other.m_md_context);
   assert(result == 0);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator<<(std::string const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.c_str(), data.size());
   int result = mbedtls_md_update(&m_md_context, data_buf, data.size());
   assert(result == 0);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator<<(Buffer const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.get(), data.size());
   int result = mbedtls_md_update(&m_md_context, data_buf, data.size());
   assert(result == 0);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator>>(Buffer &out)
{
   uint8_t hash_buf[HASH_SIZE_BYTES];
   assert(mbedtls_md_finish(&m_md_context, hash_buf) == 0);
   assert(mbedtls_md_starts(&m_md_context) == 0);

   Buffer hash(hash_buf, HASH_SIZE_BYTES);
   out = hash;
   return *this;
}

