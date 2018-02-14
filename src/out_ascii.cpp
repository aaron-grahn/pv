#include <iostream>
#include <string>
#include <sstream>
#include "out_ascii.h"
#include "out_base.h"
#include "buffer.h"
#include "crypto_port.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Ascii::Ascii(std::ostream &os)
   : Io::Ostream::Base(os)
{
}

////////////////////////////////////////////////////////////////////////////////
std::string Io::Ostream::Ascii::encode(Buffer const &data)
{
   std::stringstream ss;
   Port::Encoding base64;
   ss << base64.encode(data);
   return ss.str();
}

