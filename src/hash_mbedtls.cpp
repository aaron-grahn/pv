#include <exception>
#include <mbedtls/md.h>
#include <cstring>
#include "hash_mbedtls.h"
#include "buffer.h"

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
   if(mbedtls_md_setup(&m_md_context, md_info, NO_HMAC) != 0)
   {
      throw std::exception();
   }
   if(mbedtls_md_starts(&m_md_context) != 0)
   {
      throw std::exception();
   }
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
   if(mbedtls_md_clone(&m_md_context, &other.m_md_context) != 0)
   {
      throw std::exception();
   }
}

////////////////////////////////////////////////////////////////////////////////
Port::Mbedtls::Hash 
&Port::Mbedtls::Hash::operator=(Hash const &other)
{
   mbedtls_md_free(&m_md_context);
   if(mbedtls_md_clone(&m_md_context, &other.m_md_context) != 0)
   {
      throw std::exception();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator<<(std::string const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.c_str(), data.size());
   if(mbedtls_md_update(&m_md_context, data_buf, data.size()) != 0)
   {
      throw std::exception();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator<<(Buffer const &data)
{
   uint8_t data_buf[HASH_SIZE_BYTES];
   memcpy(&data_buf, data.get(), data.size());
   if(mbedtls_md_update(&m_md_context, data_buf, data.size()) != 0)
   {
      throw std::exception();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Port::Mbedtls::Hash::operator>>(Buffer &out)
{
   uint8_t hash_buf[HASH_SIZE_BYTES];
   if(mbedtls_md_finish(&m_md_context, hash_buf) != 0)
   {
      throw std::exception();
   }
   if(mbedtls_md_starts(&m_md_context) != 0)
   {
      throw std::exception();
   }

   Buffer hash(hash_buf, HASH_SIZE_BYTES);
   out = hash;
   return *this;
}

