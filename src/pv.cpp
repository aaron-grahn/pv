#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pv.h"
#include "io.h"
#include "crypto_port.h"
#include "key.h"
#include "random_buffer.h"
#include "block.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   /////////////////////////////////////////////////////////////////////////////
   void gen_salt(std::string const &store)
   {
      std::string const SALT_PATH = store + "/salt";

      // Verify that the salt is not already initialized.
      struct stat s;
      assert(stat(SALT_PATH.c_str(), &s) != 0);

      std::ofstream salt_out(SALT_PATH);
      Random_buffer salt(16);
      salt_out << Io::Encoding::Base64 << salt;
   }

   /////////////////////////////////////////////////////////////////////////////
   Buffer get_salt(std::string const &store)
   {
      struct stat s;
      std::string const SALT_PATH = store + "/salt";
      assert(stat(SALT_PATH.c_str(), &s) == 0);

      std::ifstream salt_in(SALT_PATH);
      Buffer salt(16);
      salt_in >> Io::Encoding::Base64 >> salt;
      std::cout << "Salt: " << Io::Encoding::Base64 << salt;
      std::cout << std::endl;
      return salt;
   }

   /////////////////////////////////////////////////////////////////////////////
   std::string get_site_path(std::string const &store, std::string const &site)
   {
      Buffer salt = get_salt(store);
      Port::Hash sitehash;
      Buffer filebuf(32);
      sitehash << site;
      sitehash << salt;
      sitehash >> filebuf;

      std::stringstream filename;
      filename << Io::Encoding::Hex << filebuf;
      std::string const SITE_FILE_PATH = store + "/" + filename.str();
      std::cout << "Site file path: " << SITE_FILE_PATH;
      std::cout << std::endl;

      return SITE_FILE_PATH;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   Key<256> get_user_key(std::string const &store)
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
      hash << get_salt(store);
      hash >> user_key_buffer;

      // Return the user key.
      Key<256> user_key(user_key_buffer);
      std::cout << "User key: " << Io::Encoding::Base64 << user_key;
      std::cout << std::endl;
      return user_key;
   }

   ////////////////////////////////////////////////////////////////////////////////
   Key<128> get_master_key(std::string const &store)
   {
      Key<256> user_key = get_user_key(store);
      Port::Decryptor decrypt(user_key);

      std::string const MASTER_KEY_PATH = store + "/master.key";
      Buffer master_key_buffer(16);
      std::ifstream key_in(MASTER_KEY_PATH);
      key_in >> Io::Encoding::Base64 >> master_key_buffer;

      Key<128> master_key(decrypt(Block(master_key_buffer)));
      std::cout << "Master key: " << Io::Encoding::Base64 << master_key;
      std::cout << std::endl;

      // Return the user key.
      return master_key;
   }

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
   gen_salt(m_store);

   // Encrypt the master key with the user key.
   Key<256> user_key = get_user_key(m_store);
   Port::Encryptor encrypt(user_key);
   std::ofstream key_out(MASTER_KEY_PATH);
   Random_buffer master_key(16);
   std::cout << "Master key: " << Io::Encoding::Base64 << master_key;
   std::cout << std::endl;
   key_out << Io::Encoding::Base64 << encrypt(Block(master_key));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
   std::string const SITE_FILE_PATH = get_site_path(m_store, site);

   std::ofstream site_out(SITE_FILE_PATH);
   Key<128> master_key = get_master_key(m_store);
   Port::Encryptor encrypt(master_key);
   Random_buffer site_password(16);
   std::cout << "Site password: " << Io::Encoding::Base64 << site_password;
   std::cout << std::endl;
   site_out << Io::Encoding::Base64 << encrypt(Block(site_password));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::get(std::string const &site)
{
   std::string const SITE_FILE_PATH = get_site_path(m_store, site);

   std::ifstream site_in(SITE_FILE_PATH);
   Key<128> master_key = get_master_key(m_store);
   Port::Decryptor decrypt(master_key);
   Buffer site_password(16);
   site_in >> Io::Encoding::Base64 >> site_password;
   std::cout << "Site password: " << Io::Encoding::Base64 << decrypt(Block(site_password));
   std::cout << std::endl;
}

