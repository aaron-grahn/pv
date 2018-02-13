#ifndef PV_H
#define PV_H

#include <string>
#include "key.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
class Pv
{
public:
   Pv(std::string const &store, std::string const &passphrase);
   ~Pv() = default;

   Pv(Pv const&) = delete;
   Pv &operator=(Pv const&) = delete;
   Pv(Pv&&) = delete;
   Pv &operator=(Pv&&) = delete;

   void initialize();
   void add(std::string const &site);
   std::string get(std::string const &site);

private:
   std::string const &m_store;
   std::string const &m_passphrase;
};

#endif // PV_H
