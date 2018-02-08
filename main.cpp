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
   std::cout << k1 << std::endl;
   std::cout << k2 << std::endl;

   Port::Hash h;
   h << "fish" << "swish";
   Buffer hash(32);
   h >> hash;
   std::cout << hash << std::endl;
   Port::Base64 base64;
   std::string encoded = base64.encode(hash);
   std::cout << encoded << std::endl;
   Buffer decoded(base64.decode(encoded));
   std::cout << decoded << std::endl;

   Block b(k1.buffer());
   std::cout << b << std::endl;
   Port::Encryptor encrypt(k1);
   Port::Decryptor decrypt(k1);
   Block ct(encrypt(b));
   std::cout << ct << std::endl;
   Block pt(decrypt(ct));
   std::cout << pt << std::endl;

   return 0;
}

