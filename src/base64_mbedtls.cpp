#include <cassert>
#include <mbedtls/base64.h>
#include <cstring>
#include "base64_mbedtls.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
std::string Port::Mbedtls::Base64::encode(Buffer const &data)
{
   char buf[46];

   // reinterpret_cast is safe, because base64 encoded data will not set the
   // high bit of any byte.
   uint8_t *buf_p = reinterpret_cast<uint8_t*>(&buf[0]);
   std::size_t olen;
   int result = mbedtls_base64_encode(buf_p, 
                                      46, 
                                      &olen,
                                      data.get(),
                                      data.size());
   assert(result == 0);
   std::string str(&buf[0], olen);
   return str;
}

////////////////////////////////////////////////////////////////////////////////
Buffer Port::Mbedtls::Base64::decode(std::string const &data) 
{
   uint8_t buf[32];
   std::size_t olen;
   uint8_t const *data_p = reinterpret_cast<uint8_t const*>(data.c_str());
   int result = mbedtls_base64_decode(&buf[0], 
                                      32, 
                                      &olen,
                                      data_p,
                                      data.size());
   assert(result == 0);
   Buffer output(buf, olen);
   return output;
}
