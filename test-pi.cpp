/*
 * The Miller-Rabin primality test
 *
 * Written by Christian Stigen Larsen, 2012-01-10
 * http://csl.sublevel3.org
 *
 * Distributed under the modified BSD license
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "miller-rabin.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


#define MAXTAB 10000

/*
 * Return the number of primes less than or equal to n, by virtue of brute
 * force.  There are much faster ways of computing this number, but we'll
 * use it to test the primality function.
 *
 */
static void pi(int min, int max, vector<int> primeNumbers)
{
  int r=0; // compteur de nombre premiers

  while (min <= max){
    if(isprime(min)){
      primeNumbers.push_back(min);
    }
    min++;
  }
}

/*
 * Demonstration on how to use other PRNG functions than rand().
 */
static uint64_t randcalls = 0;
int myrand()
{
  ++randcalls;
  return rand();
}

int main()
{
  /*
   * Instead of honoring my own advice over at
   * http://csl.sublevel3.org/c++/#srand_time we'll just go ahead and use
   * the idiomatic form for initializing the seed. (It doesn't really matter
   * in this code).
   */
  srand(time(0));
  setrand(myrand, RAND_MAX);

  ifstream fichier("./intervalles.txt");  //Ouverture d'un fichier en lecture
  vector<int> intervalles;

  if(fichier)
  {
    int nombre;
    while(fichier >> nombre)  // tant que l'on peut mettre la ligne dans "contenu"
    {
      intervalles.push_back(nombre);
    }
    fichier.close();
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }

  // placer ces intervalles dans 2 tableaux intervalleMin intervalleMax et on parcours les 2 ou un seul tableau a voir
  int nombreIntervalles = intervalles.size()/2;
  int min = 0;
  int max = 0;
  vector<int> primeNumbers;

  for(int i = 0; i < nombreIntervalles; i+= 2){
    min = intervalles[i];
    max = intervalles[i+1];
    pi(min, max, primeNumbers);
    }
  
  cout << primeNumbers.size() << endl;

  for(int i = 0; i < primeNumbers.size(); i++){
    cout << "Prime number : " << primeNumbers[i] << endl;
  }

  //cout << "There is " << primes << " prime numbers in [" << min << ", " << max << "]" << endl;
  //cout << "The randomization function was called " << randcalls << " times\n" << endl;
  return 0;
}
