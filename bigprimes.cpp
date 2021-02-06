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


using namespace std;
//mpz_class primes[500000];
//mpz_class tempPrimes[500000];


static void readFiles(vector<mpz_class> &intervallesMin, vector<mpz_class> &intervallesMax);
void triFusion(unsigned long long i, unsigned long long j, mpz_class *tabMin, mpz_class *tempMin);
//static mpz_class find_prime(const size_t bits, const size_t rounds);

int main(int argc, const char * argv[]) {
    vector<mpz_class> intervallesMin;
    vector<mpz_class> intervallesMax;
    
    readFiles(intervallesMin, intervallesMax);
    
    int nbIntervalles = (int)intervallesMin.size();
    
    mpz_class nMin[nbIntervalles];
    mpz_class nMax[nbIntervalles];
    
    for(int i = 0; i < nbIntervalles; i++){
      nMin[i] = intervallesMin[i];
      nMax[i] = intervallesMax[i];
    }

    vector<mpz_class> primeNumbers;
    
    mpz_t prime;
    mpz_init(prime);
    for(int i = 0; i < nbIntervalles; i++){
      mpz_class index = nMin[i] - 1;
      while(index <= nMax[i]){
        mpz_nextprime(prime, index.get_mpz_t());
        index = mpz_class(prime);

        if(index <= nMax[i]){
          primeNumbers.push_back(index);
        }
      }
    }

    const unsigned long long nbPrimes = (unsigned long long)primeNumbers.size();
    mpz_class *primes = new mpz_class[nbPrimes];
    mpz_class *tempPrimes = new mpz_class[nbPrimes];


    for(unsigned long long i = 0; i < nbPrimes; i++){
      primes[i] = primeNumbers[i];
    }

    triFusion(0, nbPrimes-1, primes, tempPrimes);

    for(unsigned long long i = 0; i < nbPrimes; i++){
      cout << primes[i] << endl;
    }
    
    return 0;
}


static void readFiles(vector<mpz_class> &intervallesMin, vector<mpz_class> &intervallesMax){
  // Lecture du fichier contenant les intervalles et ajout des intervalles dans le vect intervalles
  ifstream fichier("/Users/adrienx/Desktop/UL/Progra/ProgParaTP/Exemples de fichiers/3_variÇ1.txt");  //Ouverture du fichier du nom contenu dans la macro FILEINTERVAL
  if(fichier)
  {
    string min;
    string max;
    while(fichier >> min >> max)
    {
      /*
      const char * charMin = min.c_str();
      const char * charMax = max.c_str();
      mpz_t _min, _max;
      mpz_init_set_str(_min,charMin,10);
      mpz_init_set_str(_max,charMax,10);

      */
      
      mpz_class _min, _max;
      _min = min;
      _max = max;
      
      intervallesMin.push_back(_min); // ajoute au vect intervalles les nombres
      intervallesMax.push_back(_max);

    }
    fichier.close();
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }
}

void triFusion(unsigned long long i, unsigned long long j, mpz_class tabMin[], mpz_class tempMin[]) {
    if(j <= i){ return;}
  
    unsigned long long m = (i + j) / 2;
    
    triFusion(i, m, tabMin, tempMin);     //trier la moitié gauche récursivement
    triFusion(m + 1, j, tabMin, tempMin); //trier la moitié droite récursivement
    unsigned long long pg = i;     //pg pointe au début du sous-tableau de gauche
    unsigned long long pd = m + 1; //pd pointe au début du sous-tableau de droite
    unsigned long long c;          //compteur
    // on boucle de i à j pour remplir chaque élément du tableau final fusionné
    for(c = i; c <= j; c++) {
        if(pg == m + 1) { //le pointeur du sous-tableau de gauche a atteint la limite
            tempMin[c] = tabMin[pd];
            //tempMax[c] = tabMax[pd];
            pd++;
        }else if (pd == j + 1) { //le pointeur du sous-tableau de droite a atteint la limite
            tempMin[c] = tabMin[pg];
            //tempMax[c] = tabMax[pg];
            pg++;
        }else if (tabMin[pg] < tabMin[pd]) { //le pointeur du sous-tableau de gauche pointe vers un élément plus petit  
            tempMin[c] = tabMin[pg];
            //tempMax[c] = tabMax[pg];
            pg++;
        }else {  //le pointeur du sous-tableau de droite pointe vers un élément plus petit
            tempMin[c] = tabMin[pd];
            //tempMax[c] = tabMax[pd];
            pd++;
        }
    }
    for(c = i; c <= j; c++) {  //copier les éléments de tmp[] à tab[]
      tabMin[c] = tempMin[c];
      //tabMax[c] = tempMax[c];
    }
}

