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
#include "intervals.cpp"

using namespace std;
//mpz_class primes[500000];
//mpz_class tempPrimes[500000];



int main(int argc, const char * argv[]) {
  int nb_thread = atoi(argv[1]);
  string filename = argv[2];
  dataNumbers data = getNumbersToTestInOrder(filename); // A FAIRE : passer en argument de la fonction le nom du fichier d'intervalle
  
  return 0;
}

