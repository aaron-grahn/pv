#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "out_hex.h"
#include "out_base.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Hex::Hex(std::ostream &os)
   : Io::Ostream::Base(os)
{
}

////////////////////////////////////////////////////////////////////////////////
std::string Io::Ostream::Hex::encode(Buffer const &data)
{
   std::stringstream ss;
   for(size_t i = 0; i < data.size(); i++)
   {
      ss << std::hex << std::setw(2) << std::setfill('0');
      ss << static_cast<int>(data[i]);
   }
   return ss.str();
}

