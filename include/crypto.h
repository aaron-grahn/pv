#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include "buffer.h"
#include "block.h"
#include "key.h"

class IEcb
{
public:
   virtual Block operator()(Block const &data) = 0;
};

class IHash
{
public:
   virtual IHash &operator<<(std::string const &data) = 0;
   virtual IHash &operator<<(Buffer const &data) = 0;
   virtual Buffer finalize() = 0;
};

#endif // CRYPTO_H
