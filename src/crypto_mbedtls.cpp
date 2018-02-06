#include <cassert>
#include <mbedtls/md.h>
#include <mbedtls/aes.h>
#include <cstring>
#include "crypto_mbedtls.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace
{
   /////////////////////////////////////////////////////////////////////////////
   void initialize_cipher_context(
      mbedtls_aes_context &context,
      Key_base const &key,
      int operation)
   {
      mbedtls_aes_init(&context);
      int result;
      if(operation == MBEDTLS_AES_ENCRYPT)
      {
         result = mbedtls_aes_setkey_enc(&context, 
                                         key.buffer().get(), 
                                         key.size());
      }
      else if(operation == MBEDTLS_AES_DECRYPT)
      {
         result = mbedtls_aes_setkey_dec(&context, 
                                         key.buffer().get(), 
                                         key.size());
      }
      else
      {
         // Unreachable.
         assert(false);
      }
      assert(result == 0);
   }
}

////////////////////////////////////////////////////////////////////////////////
Ecb_mbedtls::Ecb_mbedtls(Key_base const &key)
   : m_encipher_context()
   , m_decipher_context()
{
   initialize_cipher_context(m_encipher_context, key, MBEDTLS_AES_ENCRYPT);
   initialize_cipher_context(m_decipher_context, key, MBEDTLS_AES_DECRYPT);
}

////////////////////////////////////////////////////////////////////////////////
Ecb_mbedtls::~Ecb_mbedtls()
{
   mbedtls_aes_free(&m_encipher_context);
   mbedtls_aes_free(&m_decipher_context);
}

////////////////////////////////////////////////////////////////////////////////
Block Ecb_mbedtls::encrypt(Block const &data)
{
   Buffer cipher(data.size());
   int result = mbedtls_aes_crypt_ecb(&m_encipher_context, 
                                      MBEDTLS_AES_ENCRYPT,
                                      data.buffer().get(),
                                      &cipher[0]);
   assert(result == 0);
   return Block(cipher);
}

////////////////////////////////////////////////////////////////////////////////
Block Ecb_mbedtls::decrypt(Block const &data)
{
   Buffer cipher(data.size());
   int result = mbedtls_aes_crypt_ecb(&m_decipher_context, 
                                      MBEDTLS_AES_DECRYPT,
                                      data.buffer().get(),
                                      &cipher[0]);
   assert(result == 0);
   return Block(cipher);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace
{
   int const NO_HMAC = 0;
   std::size_t HASH_SIZE_BYTES = 32;
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls::Hash_mbedtls()
   : IHash()
   , m_md_context()
{
   mbedtls_md_info_t const *md_info = 
      mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
   mbedtls_md_init(&m_md_context);
   mbedtls_md_setup(&m_md_context, md_info, NO_HMAC);
   mbedtls_md_starts(&m_md_context);
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls::~Hash_mbedtls()
{
   mbedtls_md_free(&m_md_context);
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls::Hash_mbedtls(Hash_mbedtls const &other)
   : m_md_context()
{
   mbedtls_md_clone(&m_md_context, &other.m_md_context);
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls &Hash_mbedtls::operator=(Hash_mbedtls const &other)
{
   mbedtls_md_free(&m_md_context);
   mbedtls_md_clone(&m_md_context, &other.m_md_context);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Hash_mbedtls::operator<<(std::string const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.c_str(), data.size());
   mbedtls_md_update(&m_md_context, data_buf, data.size());
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Hash_mbedtls::operator<<(Buffer const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.get(), data.size());
   mbedtls_md_update(&m_md_context, data_buf, data.size());
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
Buffer Hash_mbedtls::finalize()
{
   uint8_t hash_buf[HASH_SIZE_BYTES];
   mbedtls_md_finish(&m_md_context, hash_buf);
   mbedtls_md_starts(&m_md_context);

   Buffer hash(hash_buf, HASH_SIZE_BYTES);
   return hash;
}

