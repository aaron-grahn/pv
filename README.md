# pv

pv is a password vault. 

## Building

Edit config.mk and config.cpp to conform to your installation, and then build
with `make`, and install with `make install`.

# Usage

## pv -v

Displays the version of pv. 

## pv init

Initializes the store, by generating a random master key and a random salt
value, and encrypting the master key with a key derived from the user
passphrase.

The user passphrase is never stored, even in an encrypted form.

## pv change

Changes the user passphrase by decrypting the master key using the old
passphrase, and encrypting it using the new passphrase. The master key,
encrypted under the old passphrase, is stored in a backup file. 

## pv add {site}

Generates a random block from which to derive the password for the provided
site. This block is encrypted under the master key for storage. The file in
which it is stored is named by hashing the provided site together with the
random salt value, and encoding this hash.

## pv get {site}

Retrieves, decrypts, encodes, and outputs the password for the provided site. 

# Algorithms

pv makes use of a cipher M' = E\_k(M), M = D\_k(M'); and a hash H(M).

A master key m and a salt string s are generated at initialization. 

## User password

A user key u is derived from a passphrase p. This derivation is 

    u = H(p + s)

## Master Key

The master key m is stored in encrypted form m' as 

    m' = E_u(m)

When it is needed, it is decrypted as

    m = D_u(m') 

## Site password

Each site has a random password r. This is stored in encrypted form r' as

    r' = E_m(r)

When it is needed, it is decrypted as 

    r = D_m(r')

## Site password filename

The site password r for a site n is stored in encrypted form r' in a file whose
filename f is

    f = H(n + s)

## Attacks

The passphrase is used to derive a key, and that key is used to decrypt the
master key. The master key, decrypted correctly, looks exactly like the master
key, decrypted incorrectly, and works just as well to decrypt the site
passwords, which also look the same whether correctly or incorrectly decrypted.
An attacker would have to test the decrypted password against the site. 

An attacker who knows the password for some site can perform an offline attack
against the user passphrase, however, and could therefore learn all the other
passwords. 

An attacker can easily enough determine, offline, whether a password for some
site exists, by hashing the site name together with the salt, and checking if
such a file exists in the store.

### A design that is (nearly) immune to offline attacks

A random 128 bit value is generated and stored. To retrieve the password for a
given site, hash together the site name, the user passphrase, and an
installation specific salt. Encrypt the random 128 bit value, using this hash as
the key. The result is the site password. 

In this way, every combination of site and passphrase can be used to derive a
password, and each one looks as valid as any other until tested against the
site. 

Even with this design, however, an attacker who knows a site password could
perform an offline attack against the user passphrase. 

# Porting

A port provides implementations of E\_k(M), D\_k(M), and H(M). It also provides
an ascii encoding algorithm, such as base64. Ports are not obligated to use the
same cryptographic primitives as one another. 

It is necessary that the H(M) output a hash of a size that can be used as a key
by the functions E and D. It is also necessary that the block size of the
functions E and D is the same as a valid key size.

# Versioning

The major version is to be incremented when changes break compatibility with
existing password stores. The minor version is to be incremented when new
features are added that do not break compatibility. Releases that do not add new
features only increment the build version. Prior to version 1.0.0, everything is
potentially in flux. 

# How to get randomness

Reading from /dev/random is fast and probably secure enough. 

Shuffle 35 cards very thoroughly, and type them in in sequence. Take the MD5
hash of the result. 128 bits. 

Roll a D6 50 times. Type in the numbers that come up in sequence. Take the MD5
hash. 128 bits. 

