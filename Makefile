
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
PORT_OBJECTS = crypto_mbedtls.o hash_mbedtls.o encoding_mbedtls.o
endif

OBJECTS = pv.o io.o key.o buffer.o random_buffer.o block.o $(PORT_OBJECTS)

lib/libpv.a: $(OBJECTS)
	mkdir -p lib
	$(AR) rsU lib/libpv.a $(OBJECTS)

lib/libpv.so.0: $(OBJECTS)
	mkdir -p lib
	$(CXX) -o lib/libpv.so.0 $(OBJECTS) -shared

pv.o: src/pv.cpp
	$(CXX) $(CXXFLAGS) -c -o pv.o src/pv.cpp

io.o: src/io.cpp
	$(CXX) $(CXXFLAGS) -c -o io.o src/io.cpp

key.o: src/key.cpp
	$(CXX) $(CXXFLAGS) -c -o key.o src/key.cpp

block.o: src/block.cpp
	$(CXX) $(CXXFLAGS) -c -o block.o src/block.cpp

buffer.o: src/buffer.cpp
	$(CXX) $(CXXFLAGS) -c -o buffer.o src/buffer.cpp

random_buffer.o: src/random_buffer.cpp
	$(CXX) $(CXXFLAGS) -c -o random_buffer.o src/random_buffer.cpp

crypto_mbedtls.o: src/crypto_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o crypto_mbedtls.o src/crypto_mbedtls.cpp

hash_mbedtls.o: src/hash_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o hash_mbedtls.o src/hash_mbedtls.cpp

encoding_mbedtls.o: src/encoding_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o encoding_mbedtls.o src/encoding_mbedtls.cpp

################################################################################
clean:
	rm -rvf *.o pv lib

install: pv
	install -D -m 0755 -t $(INSTALL_PREFIX)/bin pv
	install -D -m 0755 -t $(INSTALL_PREFIX)/lib lib/libpv.so.0
	install -D -m 0644 -t $(INSTALL_PREFIX)/lib lib/libpv.a
	install -D -m 0644 -t $(INSTALL_PREFIX)/include include/pv.h
	ln -f -s -T $(INSTALL_PREFIX)/lib/libpv.so.0 $(INSTALL_PREFIX)/lib/libpv.so

# Run the clang static analyzer. 
scan:
	scan-build --use-c++=$(CXX) make
