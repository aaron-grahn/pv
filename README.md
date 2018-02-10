
# pv

pv is a password vault. It depends on mbedtls. Edit config.mk to point to where
mbedtls is installed, and then build with make. 

# How to get randomness

Reading from /dev/random is fast and probably secure enough. 

Shuffle 35 cards very thoroughly, and type them in in sequence. Take the MD5
hash of the result. 128 bits. 

Roll a D6 50 times. Type in the numbers that come up in sequence. Take the MD5
hash. 128 bits. 
