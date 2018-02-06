
include config.mk

MBED_TLS_INCLUDE = $(MBED_TLS_PATH)/include
MBED_TLS_LIB = $(MBED_TLS_PATH)/lib

BUILDROOT = $(shell pwd)
INCLUDE_FLAGS  = -I$(BUILDROOT)/include
INCLUDE_FLAGS += -I$(MBED_TLS_INCLUDE)
LIB_FLAGS  = -L$(BUILDROOT)/src
LIB_FLAGS += -L$(MBED_TLS_LIB)

CXXFLAGS += $(INCLUDE_FLAGS) -std=c++11 -Wall -Wextra
LDFLAGS += $(LIB_FLAGS) -lpv -lmbedcrypto

all: pv
	$(CXX) --version

pv: src/libpv.a main.o
	$(CXX) -o pv main.o $(LDFLAGS)
	
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

src/libpv.a:
	CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" make -C src libpv.a

clean:
	make -C src clean
	rm -vf *.o pv

install: pv
	install -m 0755 -t $(INSTALL_PREFIX)/bin pv

# Run the clang static analyzer. 
scan:
	scan-build --use-c++=$(CXX) make
