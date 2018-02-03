OBJECTS = key.o buffer.o crypto_mbedtls.o

libpv.a: $(OBJECTS)
	$(AR) r libpv.a $(OBJECTS)

key.o: key.cpp
	$(CXX) $(CXXFLAGS) -c -o key.o key.cpp

buffer.o: buffer.cpp
	$(CXX) $(CXXFLAGS) -c -o buffer.o buffer.cpp

crypto_mbedtls.o: crypto_mbedtls.cpp
	$(CXX) $(CXXFLAGS) -c -o crypto_mbedtls.o crypto_mbedtls.cpp

clean:
	rm -vf *.o *.a
