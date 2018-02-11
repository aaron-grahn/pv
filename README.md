# pv

pv is a password vault. 

## Building

Edit config.mk to conform to your installation, and then build with `make`, and
install with `make install`.

# How to get randomness

Reading from /dev/random is fast and probably secure enough. 

Shuffle 35 cards very thoroughly, and type them in in sequence. Take the MD5
hash of the result. 128 bits. 

Roll a D6 50 times. Type in the numbers that come up in sequence. Take the MD5
hash. 128 bits. 

# Algorithms

pv makes use of a cipher E\_k(M), D\_k(M), and a hash H(M).

A master key m and a salt string s are generated at initialization. 

## User password

A user key u is derived from a passphrase p. This derivation is 

    H(p + s)

## Master Key

The master key m is stored in encrypted form m' as 

    m' = E\_u(m)

When it is needed, it is decrypted as

    m = D\_u(m') 

## Site password

Each site has a random password r. This is stored in encrypted form r' as

    r' = E\_m(r)

When it is needed, it is decrypted as 

    r = D\_m(r')

## Site password filename

The site password r for a site n is stored in encrypted form r' in a file whose
name is

    H(n + s)

# Porting

A port provides implementations of E\_k(M), D\_k(M), and H(M). It also provides
Base64 encoding. Ports are not obligated to use the same cryptographic
primitives as one another. 
