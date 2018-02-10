#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pv.h"
#include "crypto_port.h"
#include "key.h"
#include "random_buffer.h"
#include "block.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
} // namespace

////////////////////////////////////////////////////////////////////////////////
Pv::Pv(std::string const &store)
   : m_store(store)
{
   static_cast<void>(mkdir(m_store.c_str(), 0700));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::initialize()
{
   std::string const MASTER_KEY_PATH = m_store + "/master.key";

   // Verify that the store is not already initialized.
   struct stat s;
   assert(stat(MASTER_KEY_PATH.c_str(), &s) != 0);

   // Initialize the store. First, make some salt.
   gen_salt();

   // Encrypt the master key with the user key.
   Key<256> user_key = get_user_key();
   Port::Encryptor encrypt(user_key);
   std::ofstream key_out(MASTER_KEY_PATH);
   Random_buffer master_key(16);
   std::cout << "Master key: " << master_key << std::endl;
   key_out << encrypt(Block(master_key));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
   Key<128> master_key = get_master_key();

   Buffer salt = get_salt();
   Port::Hash sitehash;
   Buffer filebuf(32);
   sitehash << site;
   sitehash << salt;
   sitehash >> filebuf;

   std::stringstream filename;
   filename << filebuf;
   std::string const SITE_FILE = m_store + "/" + filename.str();
   std::cout << SITE_FILE << std::endl;


}

////////////////////////////////////////////////////////////////////////////////
void Pv::get(std::string const &site)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::gen_salt()
{
   std::string const SALT_PATH = m_store + "/salt";

   // Verify that the salt is not already initialized.
   struct stat s;
   assert(stat(SALT_PATH.c_str(), &s) != 0);

   std::ofstream salt_out(SALT_PATH);
   Random_buffer salt(16);
   salt_out << salt;
}

////////////////////////////////////////////////////////////////////////////////
Buffer Pv::get_salt()
{
   struct stat s;
   std::string const SALT_PATH = m_store + "/salt";
   assert(stat(SALT_PATH.c_str(), &s) == 0);

   std::ifstream salt_in(SALT_PATH);
   Buffer salt(16);
   salt_in >> salt;
   std::cout << "Salt: " << salt << std::endl;
   return salt;
}

////////////////////////////////////////////////////////////////////////////////
Key<256> Pv::get_user_key()
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
   hash << get_salt();
   hash >> user_key_buffer;

   // Return the user key.
   Key<256> user_key(user_key_buffer);
   std::cout << "User key: " << user_key.buffer() << std::endl;
   return user_key;
}

////////////////////////////////////////////////////////////////////////////////
Key<128> Pv::get_master_key()
{
   Key<256> user_key = get_user_key();
   Port::Decryptor decrypt(user_key);

   std::string const MASTER_KEY_PATH = m_store + "/master.key";
   Buffer master_key_buffer(16);
   std::ifstream key_in(MASTER_KEY_PATH);
   key_in >> master_key_buffer;

   Key<128> master_key(decrypt(Block(master_key_buffer)));
   std::cout << "Master key: " << master_key << std::endl;

   // Return the user key.
   return master_key;
}
