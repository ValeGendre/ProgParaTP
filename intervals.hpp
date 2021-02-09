#ifndef INTERVALS_H
#define INTERVALS_H

    #include <iostream>
    #include <vector>
    #include <iostream>
    #include <vector>
    #include <stdint.h>
    #include <fstream>
    #include <gmpxx.h>
    #include <gmp.h>
    #include <stdio.h>
    #include <string>
    #include "Chrono.hpp"
    using namespace std;

    struct dataNumbers{
    mpz_class *tab;
    unsigned long long nbNumbers;
    };

    void readFiles(vector<mpz_class> &intervallesMin, vector<mpz_class> &intervallesMax);
    void triFusion(unsigned long long i, unsigned long long j, mpz_class *tabMin, mpz_class *tempMin);
    void supprimeDoublons(mpz_class tab[], vector<mpz_class> &final, unsigned long long nbNumbers);
    dataNumbers getNumbersToTestInOrder(string filename, Chrono &chrono);

#endif 