# Paths for gmpxx.h and libgmp*
GMPINC := /usr/local/Cellar/gmp/6.2.1/include
GMPLIB := /usr/local/Cellar/gmp/6.2.1/lib

CXXFLAGS := -W -Wall -O3 -march=native
TARGETS := miller-rabin.o test-pi

all: $(TARGETS)

check: test-pi
	time nice -9 ./test-pi

test-pi: miller-rabin.o

clean:
	rm -f $(TARGETS)

bigprimes: bigprimes.cpp miller-rabin-gmp.cpp 
	$(CXX) $(CXXFLAGS) -I$(GMPINC) -L$(GMPLIB) \
		-lgmp -lgmpxx -o$@ $^
