
# Where to install pv.
INSTALL_PREFIX = /opt/pv-0.1.0

# Uncomment this for a fully static build
#LDFLAGS = -static -static-libstdc++

################################################################################
# Select the port.
################################################################################
# Which port to use. This is used to make a -D compiler flag, and to pick
# dependencies in the Makefile.
PORT = MBED_TLS

# Specify the prefix under which the port dependency library is installed. This
# is not used outside of this file, but may be convenient.
PORT_PREFIX = /opt/mbedtls-2.6.0

# Configure to compile and link against the port dependencies.
PORT_CXXFLAGS = -I$(PORT_PREFIX)/include
PORT_LDFLAGS = -L$(PORT_PREFIX)/lib -lmbedcrypto

