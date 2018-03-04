#ifndef PV_H
#define PV_H

#include <string>
#include "key.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
class Pv
{
public:
   Pv(std::string const &store);
   ~Pv() = default;

   Pv(Pv const&) = delete;
   Pv &operator=(Pv const&) = delete;
   Pv(Pv&&) = delete;
   Pv &operator=(Pv&&) = delete;

   void initialize(std::string const &passphrase);
   void add(std::string const &site, std::string const &passphrase);
   void change(std::string const &old_passphrase, 
               std::string const &new_passphrase);
   std::string get(std::string const &site, std::string const &passphrase);

private:
   std::string const &m_store;
};

#endif // PV_H
