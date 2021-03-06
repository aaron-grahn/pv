#include <iostream>
#include <string>
#include "in_ascii.h"
#include "crypto_port.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Io::Istream::Ascii::Ascii(std::istream &is)
   : Io::Istream::Base(is)
{
}

////////////////////////////////////////////////////////////////////////////////
Buffer Io::Istream::Ascii::decode(std::string const &data)
{
   Port::Encoding base64;
   return base64.decode(data);
}

