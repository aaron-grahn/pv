#include <iostream>
#include <string>
#include "key.h"
#include "block.h"
#include "crypto_mbedtls.h"

int main(void)
{
   Key<128> k1;
   Key<256> k2;
   std::cout << k1 << std::endl;
   std::cout << k2 << std::endl;
   Hash_mbedtls hm;
   hm << "fish" << "swish";
   std::cout << hm.finalize() << std::endl;

   Block b(k1.buffer());
   std::cout << b << std::endl;
   Ecb_mbedtls ecb(k1);
   Block ct(ecb.encrypt(b));
   std::cout << ct << std::endl;
   Block pt(ecb.decrypt(ct));
   std::cout << pt << std::endl;


   return 0;
}

