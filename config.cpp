
#include <string>

// The version of pv.
extern std::string const VERSION_STRING = "0.2.0";

// This is the path to a directory, relative to the user's home directory.
extern std::string const STORE = "/.pv/";

// These are filenames in the STORE directory.
extern std::string const BACKUP_FILE_EXTENSION = ".bak";
extern std::string const MASTER_KEY_FILE = "master.key";
extern std::string const MASTER_KEY_BACKUP_FILE = 
   "master.key" + BACKUP_FILE_EXTENSION;
extern std::string const SALT_FILE = "salt";

// Whence to get randomness
extern std::string const RANDOM_SOURCE = "/dev/random";
