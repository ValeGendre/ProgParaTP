all: test.cpp threaded_prime.cpp miller-rabin-gmp.cpp
	g++ -I /usr/local/include -L /usr/local/lib -o $@ $^ -lgmp -lgmpxx -lpthread
