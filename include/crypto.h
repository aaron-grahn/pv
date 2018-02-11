#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include "buffer.h"
#include "block.h"

////////////////////////////////////////////////////////////////////////////////
class ICrypto
{
public:
   virtual Block operator()(Block const &data) = 0;
};

////////////////////////////////////////////////////////////////////////////////
class IHash
{
public:
   virtual IHash &operator<<(std::string const &data) = 0;
   virtual IHash &operator<<(Buffer const &data) = 0;
   virtual IHash &operator>>(Buffer &out) = 0;
};

////////////////////////////////////////////////////////////////////////////////
class IEncoding
{
public:
   virtual std::string encode(Buffer const &data) = 0;
   virtual Buffer decode(std::string const &data) = 0;
};

#endif // CRYPTO_H
