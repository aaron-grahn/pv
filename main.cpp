#include <iostream>
#include <string>
#include "key.h"
#include "crypto_mbedtls.h"

int main(void)
{
   Key<128> k1;
   Key<256> k2;
   std::cout << k1 << std::endl;
   std::cout << k2 << std::endl;
   Hash_mbedtls hm;
   hm << "fish";
   std::cout << hm.finalize() << std::endl;

   return 0;
}

