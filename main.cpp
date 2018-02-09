#include <cassert>
#include <iostream>
#include <string>
#include <string.h>
#include "pv.h"
#include "key.h"
#include "block.h"
#include "buffer.h"
#include "crypto_port.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{

////////////////////////////////////////////////////////////////////////////////
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
   assert(false);
}

////////////////////////////////////////////////////////////////////////////////
int usage(std::string const &name)
{
   std::cout << "Usage: "
             << name << " "
             << "{init | [add | get] <site>}"
             << std::endl;
   return 1;
}

} //namespace

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv, char **env)
{
   std::string const HOME = findhome(env);
   std::string const STORE = HOME + "/.pv";
   std::cout << STORE << std::endl;
   Pv pv(STORE);

   // Parse the arguments. 
   if(argc == 2)
   {
      if(std::string("init") == argv[1])
      {
         pv.initialize();
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
         pv.add(site);
      }
      else if(std::string("get") == argv[1])
      {
         pv.get(site);
      }
      else
      {
         return usage(std::string(argv[0]));
      }
      std::cout << site << std::endl;
   }
   else
   {
      return usage(std::string(argv[0]));
   }

   Key<128> k1;
   Key<256> k2;
   std::cout << k1.buffer() << std::endl;
   std::cout << k2.buffer() << std::endl;

   Port::Hash h;
   h << "fish" << "swish";
   Buffer hash(32);
   h >> hash;
   std::cout << hash << std::endl;

   Block b(k1.buffer());
   std::cout << b.buffer() << std::endl;
   Port::Encryptor encrypt(k1);
   Port::Decryptor decrypt(k1);
   Block ct(encrypt(b));
   std::cout << ct.buffer() << std::endl;
   Block pt(decrypt(ct));
   std::cout << pt.buffer() << std::endl;

   return 0;
}

