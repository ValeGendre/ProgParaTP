#include "intervals.hpp"
using namespace std;

void readFiles(vector<mpz_class> &intervallesMin, vector<mpz_class> &intervallesMax, string filename){
  // Lecture du fichier contenant les intervalles et ajout des intervalles dans le vect intervalles
  ifstream fichier(filename);  //Ouverture du fichier du nom contenu dans la macro FILEINTERVAL
  if(fichier)
  {
    string min;
    string max;
    while(fichier >> min >> max)
    {
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

void triFusion(unsigned long long i, unsigned long long j, mpz_class tab[], mpz_class temp[]) {
    if(j <= i){ return;}
  
    unsigned long long m = (i + j) / 2;
    
    triFusion(i, m, tab, temp);     //trier la moitié gauche récursivement
    triFusion(m + 1, j, tab, temp); //trier la moitié droite récursivement

    unsigned long long pg = i;     //pg pointe au début du sous-tableau de gauche
    unsigned long long pd = m + 1; //pd pointe au début du sous-tableau de droite
    unsigned long long c;          //compteur

    // on boucle de i à j pour remplir chaque élément du tableau final fusionné
    for(c = i; c <= j; c++) {
        if(pg == m + 1) { //le pointeur du sous-tableau de gauche a atteint la limite
            temp[c] = tab[pd];
            pd++;
        }else if (pd == j + 1) { //le pointeur du sous-tableau de droite a atteint la limite
            temp[c] = tab[pg];
            pg++;
        }else if (tab[pg] < tab[pd]) { //le pointeur du sous-tableau de gauche pointe vers un élément plus petit  
            temp[c] = tab[pg];
            pg++;
        }else {  //le pointeur du sous-tableau de droite pointe vers un élément plus petit
            temp[c] = tab[pd];
            pd++;
        }
    }
    for(c = i; c <= j; c++) {  //copier les éléments de tmp[] à tab[]
      tab[c] = temp[c];
    }
}

void supprimeDoublons(mpz_class tab[], vector<mpz_class> &final, unsigned long long nbNumbers){
    final.push_back(tab[0]);
    for(unsigned long long index = 1; index < nbNumbers; index++){
      if(tab[index] != tab[index-1]){
        final.push_back(tab[index]);
      }
    }
}

dataNumbers getNumbersToTestInOrder(string filename, Chrono &chrono){
    dataNumbers x;

    vector<mpz_class> intervallesMin;
    vector<mpz_class> intervallesMax;

    readFiles(intervallesMin, intervallesMax, filename);

    chrono.resume();

    int nbIntervalles = (int)intervallesMin.size();
    mpz_class nMin[nbIntervalles];
    mpz_class nMax[nbIntervalles];

    for(int i = 0; i < nbIntervalles; i++){
    nMin[i] = intervallesMin[i];
    nMax[i] = intervallesMax[i];
    }

    vector<mpz_class> numberToTest;
    for(int i = 0; i < nbIntervalles; i++){
        for(mpz_class j = nMin[i]; j <= nMax[i]; j++){
            numberToTest.push_back(j);
        }
    }

    unsigned long long nbNumbers = (unsigned long long)numberToTest.size();
    mpz_class *numbersToTest_Tab = new mpz_class[nbNumbers];
    mpz_class *temp = new mpz_class[nbNumbers];
    vector<mpz_class> tempFinal;  


    for(unsigned long long i = 0; i < nbNumbers; i++){
        numbersToTest_Tab[i] = numberToTest[i];
    }

    triFusion(0, nbNumbers-1, numbersToTest_Tab, temp);
    supprimeDoublons(numbersToTest_Tab, tempFinal, nbNumbers);

    unsigned long long nbNumbersFinal = (unsigned long long)tempFinal.size();
    mpz_class *final = new mpz_class[nbNumbersFinal];

    for(unsigned long long i = 0; i < nbNumbersFinal; i++){
        final[i] = tempFinal[i];
    }

    x.tab = final;
    x.nbNumbers = nbNumbersFinal;

    return x;
}