#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "config.h"
#include "pv.h"
#include "io.h"
#include "in_base.h"
#include "out_base.h"
#include "crypto_port.h"
#include "key.h"
#include "random_buffer.h"
#include "block.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   /////////////////////////////////////////////////////////////////////////////
   bool file_exists(std::string const &path)
   {
      struct stat s;
      return stat(path.c_str(), &s) == 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   void gen_salt(std::string const &store)
   {
      std::string const salt_path = store + SALT_FILE;
      assert(not file_exists(salt_path));

      std::ofstream salt_out(salt_path);
      Random_buffer salt(16);
      salt_out << Io::Encoding::Ascii << salt;
   }

   /////////////////////////////////////////////////////////////////////////////
   Buffer get_salt(std::string const &store)
   {
      std::string const salt_path = store + SALT_FILE;
      assert(file_exists(salt_path));

      std::ifstream salt_in(salt_path);
      Buffer salt(16);
      salt_in >> Io::Encoding::Ascii >> salt;
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
      std::string const site_file_path = store + "/" + filename.str();

      return site_file_path;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   Key<256> get_user_key(std::string const &store, 
                         std::string const &passphrase)
   {
      // Hash the passphrase.
      Port::Hash hash;
      Buffer user_key_buffer(32);
      hash << passphrase;
      hash << get_salt(store);
      hash >> user_key_buffer;

      // Return the user key.
      Key<256> user_key(user_key_buffer);
      return user_key;
   }

   ////////////////////////////////////////////////////////////////////////////////
   Key<128> get_master_key(std::string const &store, 
                           std::string const &passphrase)
   {
      Key<256> user_key = get_user_key(store, passphrase);
      Port::Decryptor decrypt(user_key);

      std::string const master_key_path = store + MASTER_KEY_FILE;
      assert(file_exists(master_key_path));

      Buffer master_key_buffer(16);
      std::ifstream key_in(master_key_path);
      key_in >> Io::Encoding::Ascii >> master_key_buffer;

      Key<128> master_key(decrypt(Block(master_key_buffer)));

      // Return the user key.
      return master_key;
   }

} // namespace

////////////////////////////////////////////////////////////////////////////////
Pv::Pv(std::string const &store, std::string const &passphrase)
   : m_store(store)
   , m_passphrase(passphrase)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::initialize()
{
   // Create the directory. 
   assert(mkdir(m_store.c_str(), 0700) == 0);

   // Initialize the store. First, make some salt.
   gen_salt(m_store);

   // Get the user key. 
   Key<256> user_key = get_user_key(m_store, m_passphrase);
   Port::Encryptor encrypt(user_key);

   // Encrypt the master key with the user key.
   std::string const master_key_path = m_store + MASTER_KEY_FILE;
   assert(not file_exists(master_key_path));
   std::ofstream key_out(master_key_path);
   Random_buffer master_key(16);
   key_out << Io::Encoding::Ascii << encrypt(Block(master_key));
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site)
{
   std::string const site_file_path = get_site_path(m_store, site);
   assert(not file_exists(site_file_path));

   std::ofstream site_out(site_file_path);
   Key<128> master_key = get_master_key(m_store, m_passphrase);
   Port::Encryptor encrypt(master_key);
   Random_buffer site_password(16);
   site_out << Io::Encoding::Ascii << encrypt(Block(site_password));
}

////////////////////////////////////////////////////////////////////////////////
std::string Pv::get(std::string const &site)
{
   std::string const site_file_path = get_site_path(m_store, site);
   assert(file_exists(site_file_path));

   std::ifstream site_in(site_file_path);
   Key<128> master_key = get_master_key(m_store, m_passphrase);
   Port::Decryptor decrypt(master_key);
   Buffer site_password(16);
   site_in >> Io::Encoding::Ascii >> site_password;

   std::stringstream password;
   password << Io::Encoding::Ascii << decrypt(Block(site_password));
   return password.str();
}

