#include <iostream>
#include <string>
#include "key.h"
#include "block.h"
#include "buffer.h"
#include "crypto_port.h"

int main(void)
{
   Key<128> k1;
   Key<256> k2;
   std::cout << k1.buffer() << std::endl;
   std::cout << k2.buffer() << std::endl;

   Port::Hash h;
   h << "fish" << "swish";
   Buffer hash(32);
   h >> hash;
   std::cout << hash << std::endl;

   Block b(k1.buffer());
   std::cout << b.buffer() << std::endl;
   Port::Encryptor encrypt(k1);
   Port::Decryptor decrypt(k1);
   Block ct(encrypt(b));
   std::cout << ct.buffer() << std::endl;
   Block pt(decrypt(ct));
   std::cout << pt.buffer() << std::endl;

   return 0;
}

