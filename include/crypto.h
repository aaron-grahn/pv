#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include "buffer.h"
#include "key.h"

class IEcb
{
public:
   virtual Buffer ecb(Key_base const &key, Buffer const &plaintext) = 0;
};

class IHash
{
public:
   virtual IHash &operator<<(std::string const &data) = 0;
   virtual IHash &operator<<(Buffer const &data) = 0;
   virtual Buffer finalize() = 0;
};

#endif // CRYPTO_H
