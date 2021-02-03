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
#define FILEINTERVAL "./intervalles.txt"

/*
 * Add to vect primeNumbers the list of the prime numbers in the interval [min, max]
 *
 */
static void pi(int min, int max, vector<int> &primeNumbers)
{
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
  cout << "\n" << endl;
  /*
   * Instead of honoring my own advice over at
   * http://csl.sublevel3.org/c++/#srand_time we'll just go ahead and use
   * the idiomatic form for initializing the seed. (It doesn't really matter
   * in this code).
   */
  srand(time(0));
  setrand(myrand, RAND_MAX);

  vector<int> intervalles; // Création d'un vect intervalles qui va contenir les intervalles

  // Lecture du fichier contenant les intervalles et ajout des intervalles dans le vect intervalles
  ifstream fichier(FILEINTERVAL);  //Ouverture du fichier du nom contenu dans la macro FILEINTERVAL 
  if(fichier)
  {
    int nombre;
    while(fichier >> nombre) 
    {
      intervalles.push_back(nombre); // ajoute au vect intervalles les nombres
    }
    fichier.close();
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }

  int nombreIntervalles = intervalles.size(); // taille du vect intervalles
  int min = 0;
  int max = 0;
  vector<int> primeNumbers; // vect qui va contenir la liste des nombres premiers 

  // on cherche les nombres premiers pour chaque intervalles
  for(int i = 0; i < (int)nombreIntervalles; i+= 2){
    min = intervalles[i];
    max = intervalles[i+1]; 
    pi(min, max, primeNumbers); 
  }
  
  // on affiche la liste des nombres premiers 
  for(int i = 0; i < (int)primeNumbers.size(); i++){
    cout << "Prime number : " << primeNumbers[i] << endl; 
  }

  cout << "\n" << endl;
  
  return 0;
}
