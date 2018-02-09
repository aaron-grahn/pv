#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pv.h"
#include "crypto_port.h"
#include "key.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   Key<256> get_user_key()
   {
      // Get the passphrase.
      std::string passphrase;
      std::cout << "passphrase: ";
      std::cin >> passphrase;

      Port::Hash hash;
      Buffer user_key_buffer(32);
      hash << passphrase;
      hash >> user_key_buffer;

      Key<256> user_key(user_key_buffer);
      return user_key;
   }
} // namespace

////////////////////////////////////////////////////////////////////////////////
Pv::Pv(std::string const &store)
   : m_store(store)
   , m_user_key(get_user_key())
{
   static_cast<void>(mkdir(m_store.c_str(), 0700));
   std::cout << m_user_key.buffer() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
void Pv::initialize()
{
   std::string const MASTER_KEY_PATH = m_store + "/master.key";
   struct stat s;
   assert(stat(MASTER_KEY_PATH.c_str(), &s) != 0);

   std::ofstream out(MASTER_KEY_PATH);
   Key<128> master_key;
   out << master_key.buffer();
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::get(std::string const &site)
{
}

