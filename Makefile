
include config.mk

BUILDROOT = $(shell pwd)
PV_INCLUDE_FLAGS  = -I$(BUILDROOT)/include
PV_LIB_FLAGS  = -L$(BUILDROOT)/lib

CXXFLAGS += $(PV_INCLUDE_FLAGS) -std=c++11 -Wall -Wextra -O2
CXXFLAGS += -fPIC -DUSE_$(PORT) $(PORT_CXXFLAGS)
LDFLAGS += $(PV_LIB_FLAGS) -lpv $(PORT_LDFLAGS)

all: pv
	$(CXX) --version

pv: lib/libpv.a lib/libpv.so.0 main.o
	$(CXX) -o pv main.o $(LDFLAGS)
	
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

################################################################################
ifeq ($(PORT), MBED_TLS)
PORT_OBJECTS = crypto_mbedtls.o hash_mbedtls.o base64_mbedtls.o
endif

OBJECTS = key.o buffer.o block.o $(PORT_OBJECTS)

lib/libpv.a: $(OBJECTS)
	mkdir -p lib
	$(AR) rsU lib/libpv.a $(OBJECTS)

lib/libpv.so.0: $(OBJECTS)
	mkdir -p lib
	$(CXX) -o lib/libpv.so.0 $(OBJECTS) -shared

key.o: src/key.cpp
	$(CXX) $(CXXFLAGS) -c -o key.o src/key.cpp

block.o: src/block.cpp
	$(CXX) $(CXXFLAGS) -c -o block.o src/block.cpp

buffer.o: src/buffer.cpp
	$(CXX) $(CXXFLAGS) -c -o buffer.o src/buffer.cpp

crypto_mbedtls.o: src/crypto_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o crypto_mbedtls.o src/crypto_mbedtls.cpp

hash_mbedtls.o: src/hash_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o hash_mbedtls.o src/hash_mbedtls.cpp

base64_mbedtls.o: src/base64_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o base64_mbedtls.o src/base64_mbedtls.cpp

################################################################################
clean:
	rm -rvf *.o pv lib

install: pv
	install -D -m 0755 -t $(INSTALL_PREFIX)/bin pv
	install -D -m 0755 -t $(INSTALL_PREFIX)/lib lib/libpv.so.0
	ln -s -T $(INSTALL_PREFIX)/lib/libpv.so.0 $(INSTALL_PREFIX)/lib/libpv.so

# Run the clang static analyzer. 
scan:
	scan-build --use-c++=$(CXX) make
