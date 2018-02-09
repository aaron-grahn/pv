#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pv.h"
#include "crypto_port.h"
#include "key.h"
#include "random_buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   Key<256> get_user_key()
   {
      // Prompt for the passphrase.
      std::cout << "passphrase: ";

      // Get the passphrase.
      char buffer[256];
      std::cin.getline(buffer, 256);
      std::string passphrase(buffer);

      // Hash the passphrase.
      Port::Hash hash;
      Buffer user_key_buffer(32);
      hash << passphrase;
      // TODO: Needs more salt.
      hash >> user_key_buffer;

      // Return the user key.
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
   Random_buffer master_key(16);
   out << master_key;
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::get(std::string const &site)
{
}

