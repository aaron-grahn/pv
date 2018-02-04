#include <mbedtls/md.h>
#include <cstring>
#include "crypto_mbedtls.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   int const NO_HMAC = 0;
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls::Hash_mbedtls()
   : IHash()
   , m_md_context()
{
   mbedtls_md_info_t const * md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
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
Hash_mbedtls &Hash_mbedtls::operator=(Hash_mbedtls const&)
{
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls::Hash_mbedtls(Hash_mbedtls &&other)
   : m_md_context()
{
   mbedtls_md_clone(&m_md_context, &other.m_md_context);
}

////////////////////////////////////////////////////////////////////////////////
Hash_mbedtls &Hash_mbedtls::operator=(Hash_mbedtls&&)
{
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Hash_mbedtls::operator<<(std::string const &data)
{
   uint8_t data_buf[32];
   memcpy(&data_buf, data.c_str(), data.size());
   mbedtls_md_update(&m_md_context, data_buf, data.size());
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
IHash &Hash_mbedtls::operator<<(Buffer const &data)
{
   uint8_t data_buf[32];
   memcpy(&data_buf, data.get(), data.size());
   mbedtls_md_update(&m_md_context, data_buf, data.size());
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
Buffer Hash_mbedtls::finalize()
{
   uint8_t hash_buf[32];
   mbedtls_md_finish(&m_md_context, hash_buf);
   mbedtls_md_starts(&m_md_context);

   Buffer hash(hash_buf, 32);
   return hash;
}

