#include <iostream>
#include <exception>
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
      if(file_exists(salt_path))
      {
         throw std::exception();
      }

      std::ofstream salt_out(salt_path);
      Random_buffer salt(16);
      salt_out << Io::Encoding::Ascii << salt;
   }

   /////////////////////////////////////////////////////////////////////////////
   Buffer get_salt(std::string const &store)
   {
      std::string const salt_path = store + SALT_FILE;
      if(not file_exists(salt_path))
      {
         throw std::exception();
      }

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
      // hash the passphrase.
      Port::Hash hash;
      Buffer user_key_buffer(32);
      hash << passphrase;
      hash << get_salt(store);
      hash >> user_key_buffer;

      // return the user key.
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
      if(not file_exists(master_key_path))
      {
         throw std::exception();
      }

      Buffer master_key_buffer(16);
      std::ifstream key_in(master_key_path);
      key_in >> Io::Encoding::Ascii >> master_key_buffer;

      Key<128> master_key(decrypt(Block(master_key_buffer)));

      // return the user key.
      return master_key;
   }

   ////////////////////////////////////////////////////////////////////////////////
   void store_master_key(std::string const &store,
                         std::string const &passphrase,
                         Key<128> const &master_key)
   {
      // get the user key. 
      Key<256> user_key = get_user_key(store, passphrase);
      Port::Encryptor encrypt(user_key);

      // encrypt the master key with the user key.
      std::string const master_key_path = store + MASTER_KEY_FILE;
      if(file_exists(master_key_path))
      {
         throw std::exception();
      }
      std::ofstream key_out(master_key_path);
      key_out << Io::Encoding::Ascii << encrypt(Block(master_key));
   }

} // namespace

////////////////////////////////////////////////////////////////////////////////
Pv::Pv(std::string const &store)
   : m_store(store)
{
}

////////////////////////////////////////////////////////////////////////////////
void Pv::initialize(std::string const &passphrase)
{
   // create the directory. 
   if(mkdir(m_store.c_str(), 0700) != 0)
   {
      throw std::exception();
   }

   // initialize the store. First, make some salt.
   gen_salt(m_store);

   // then generate, and store, the master key. 
   Random_buffer master_key_buffer(16);
   Key<128> master_key(master_key_buffer);
   store_master_key(m_store, passphrase, master_key);
}

////////////////////////////////////////////////////////////////////////////////
void Pv::change(std::string const &old_passphrase, 
                std::string const &new_passphrase)
{
   // get the master key, using the old passphrase
   Key<128> master_key = get_master_key(m_store, old_passphrase);

   // move the old master key to a backup file. Don't want to lose it...
   std::string const master_key_path = m_store + MASTER_KEY_FILE;
   std::string const master_key_bak = m_store + MASTER_KEY_BACKUP_FILE;
   if(rename(master_key_path.c_str(), master_key_bak.c_str()) != 0)
   {
      throw std::exception();
   }

   // store the master key, using the new passphrase
   store_master_key(m_store, new_passphrase, master_key);
}

////////////////////////////////////////////////////////////////////////////////
void Pv::add(std::string const &site, std::string const &passphrase)
{
   std::string const site_file_path = get_site_path(m_store, site);
   if(file_exists(site_file_path))
   {
      throw std::exception();
   }

   std::ofstream site_out(site_file_path);
   Key<128> master_key = get_master_key(m_store, passphrase);
   Port::Encryptor encrypt(master_key);
   Random_buffer site_password(16);
   site_out << Io::Encoding::Ascii << encrypt(Block(site_password));
}

////////////////////////////////////////////////////////////////////////////////
std::string Pv::get(std::string const &site, std::string const &passphrase)
{
   std::string const site_file_path = get_site_path(m_store, site);
   if(not file_exists(site_file_path))
   {
      throw std::exception();
   }

   std::ifstream site_in(site_file_path);
   Key<128> master_key = get_master_key(m_store, passphrase);
   Port::Decryptor decrypt(master_key);
   Buffer site_password(16);
   site_in >> Io::Encoding::Ascii >> site_password;

   std::stringstream password;
   password << Io::Encoding::Ascii << decrypt(Block(site_password));
   return password.str();
}

////////////////////////////////////////////////////////////////////////////////
void Pv::change_site(std::string const &site, std::string const &passphrase)
{
   // get the site file path
   std::string const site_file_path = get_site_path(m_store, site);
   if(not file_exists(site_file_path))
   {
      throw std::exception();
   }

   // move the old site password to a backup file. Don't want to lose it...
   std::string const site_file_backup = site_file_path + BACKUP_FILE_EXTENSION;
   if(rename(site_file_path.c_str(), site_file_backup.c_str()) != 0)
   {
      throw std::exception();
   }

   // add a new password for the site. 
   add(site, passphrase);
}

