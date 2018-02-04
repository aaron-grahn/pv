
# Where to install pv.
INSTALL_PREFIX = /usr/local

# Uncomment this for a fully static build
LDFLAGS = -static -static-libstdc++

# Where to find mbedtls. This assumes it to have been installed under the build
# directory.
MBED_TLS_PATH = $(shell pwd)/usr
