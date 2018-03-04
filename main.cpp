#include <exception>
#include <iostream>
#include <string>
#include <string.h>
#include "config.h"
#include "pv.h"
#include "key.h"
#include "block.h"
#include "buffer.h"
#include "random_buffer.h"
#include "crypto_port.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
   /////////////////////////////////////////////////////////////////////////////
   std::string findhome(char **env)
   {
      for (int i = 0; env [i]; i ++)
      {
         char *key = strtok (env [i], "=");
         char *val = strtok (0, "");
         if (! strcmp (key, "HOME"))
         {
            std::string home(val);
            return home;
         }
      }
      throw std::exception();
   }

   /////////////////////////////////////////////////////////////////////////////
   int usage(std::string const &name)
   {
      std::cout << "Usage: "
                << name << " "
                << "-v | init | change | {add | get} <site>"
                << std::endl;
      return 1;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   std::string read_passphrase(std::string const &prompt)
   {
      // Prompt for the passphrase.
      std::cout << prompt << ": ";

      // Get the passphrase.
      char buffer[256];
      std::cin.getline(buffer, 256);
      std::string passphrase(buffer);

      // And return it.
      return passphrase;
   }

   /////////////////////////////////////////////////////////////////////////////
   std::string read_passphrase()
   {
      return read_passphrase("passphrase");
   }
} //namespace

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv, char **env)
{
   std::string const home = findhome(env);
   std::string const store_path = home + STORE;
   Pv pv(store_path);

   // Parse the arguments. 
   if(argc == 2)
   {
      if(std::string("init") == argv[1])
      {
         std::string const passphrase = read_passphrase();
         pv.initialize(passphrase);
      }
      else if(std::string("change") == argv[1])
      {
         std::string const old_passphrase = read_passphrase("old passphrase");
         std::string const new_passphrase = read_passphrase("new passphrase");
         std::string const confirm_passphrase = 
            read_passphrase("confirm new passphrase");
         if(new_passphrase != confirm_passphrase)
         {
            throw std::exception();
         }
         pv.change(old_passphrase, new_passphrase);
      }
      else if(std::string("-v") == argv[1])
      {
         std::cout << argv[0] << " "
                   << VERSION_STRING << std::endl;
      }
      else
      {
         return usage(std::string(argv[0]));
      }
   }
   else if(argc == 3)
   {
      std::string site(argv[2]);
      if(std::string("add") == argv[1])
      {
         std::string const passphrase = read_passphrase();
         pv.add(site, passphrase);
      }
      else if(std::string("get") == argv[1])
      {
         std::string const passphrase = read_passphrase();
         std::cout << pv.get(site, passphrase);
      }
      else
      {
         return usage(std::string(argv[0]));
      }
   }
   else
   {
      return usage(std::string(argv[0]));
   }

   return 0;
}
