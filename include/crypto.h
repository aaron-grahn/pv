#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include "buffer.h"
#include "key."

class IEcb
{
public:
   virtual Buffer ecb(Key_base const &key, Buffer const &plaintext) = 0;
};

class IHash
{
public:
   virtual void operator<<(std::string const &data) = 0;
   virtual void operator<<(Buffer const &data) = 0;
   virtual Buffer finalize() = 0;
};

#endif // crypto.h
