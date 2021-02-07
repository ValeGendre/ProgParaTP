# Paths for gmpxx.h and libgmp*
GMPINC := /usr/local/include
GMPLIB := /usr/local/lib

CXXFLAGS := -W -Wall -O3 -march=native
TARGETS := main

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

main: main.cpp
	$(CXX) $(CXXFLAGS) -I$(GMPINC) -L$(GMPLIB) \
		-lgmp -lgmpxx -o$@ $^
