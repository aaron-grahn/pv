#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pv.h"
#include "key.h"

////////////////////////////////////////////////////////////////////////////////
Pv::Pv(std::string const &store)
   : m_store(store)
{
   static_cast<void>(mkdir(m_store.c_str(), 0700));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::initialize()
{
   std::string const PW_KEY_PATH = m_store + "/pw.key";
   std::string const FN_KEY_PATH = m_store + "/fn.key";
   struct stat s;
   assert(stat(PW_KEY_PATH.c_str(), &s) != 0);
   assert(stat(FN_KEY_PATH.c_str(), &s) != 0);

   std::ofstream pw(PW_KEY_PATH);
   Key<128> pw_key;
   pw << pw_key.buffer();

   std::ofstream fn(FN_KEY_PATH);
   Key<128> fn_key;
   fn << fn_key.buffer();
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::get(std::string const &site)
{
}

