#include "threaded_prime.h"
#include <fstream>
#include <vector>
#include <pthread.h>
#include "math.h"
#include "Chrono.hpp"
#include "iostream"

pthread_mutex_t lMutex = PTHREAD_MUTEX_INITIALIZER;

using namespace std;
static void readFiles(vector<mpz_class> &intervalles, char* filename)
{
    // Lecture du fichier contenant les intervalles et ajout des intervalles dans le vect intervalles
    ifstream fichier(filename); //Ouverture du fichier du nom contenu dans la macro FILEINTERVAL 
    if(fichier)
    {
        mpz_class nombre;
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
}

int main(int argc, char * argv[])
{
    vector<mpz_class> intervalles; // Création d'un vect intervalles qui va contenir les intervalles
    if (argc == 2 + 1)
    {
        int nb_thread = atoi(argv[1]);
        // Lit les intervalles dans un fichier intervalles.txt et les mets dans le vecteur intervalle
        //readFiles(intervalles, argv[2]);
        for (int i = 2; i<1000; i++)
        {
            intervalles.push_back(i);
        }
        
        int nb_int = intervalles.size();
        int size_of_part = (int) ceil(((float) nb_int) / ((float) nb_thread));

        mpz_class numbers[nb_thread][size_of_part];
        int tabsizes[nb_thread];
        for (int i = 0; i < nb_thread; i++)
        {
            tabsizes[i] = 0;
        }

        int idx = 0;
        for (auto i = intervalles.begin(); i != intervalles.end();)
        {
            for (int j = 0; j < nb_thread; j++)
            {
                numbers[j][idx] = *i;
                tabsizes[j]++;

                i++;
                if (i == intervalles.end())
                {
                    break;
                }
            }
            idx++;
        }


        bool prime[nb_thread][size_of_part];
        bool hasbeentested[nb_thread][size_of_part];
        for (int i = 0; i < nb_thread; i++)
        {
            for (int j = 0; j<size_of_part; j++)
            {
                prime[i][j] = false;
                hasbeentested[i][j] = false;
            }
        }
        pthread_t threads[nb_thread];

        struct arg_struct args[nb_thread];
        Chrono chrono = new Chrono;

        for (int i = 0; i<nb_thread; i++)
        {
            args[i].candidates = numbers[i];
            args[i].truth_value = prime[i];
            args[i].lmutex = &lMutex;
            args[i].tested = hasbeentested[i];
            args[i].tab_size = tabsizes[i];
            pthread_create(&threads[i], NULL, thread_is_prime, (void *) &args[i]);
        }

        for (int i = 0; i<nb_thread; i++)
        {
            pthread_join(threads[i], NULL);
        }
        chrono.pause();

        for (int i = 0; i < size_of_part; i++)
        {
            for (int j = 0; j < nb_thread; j++)
            {
                if (prime[j][i])
                {
                    cout << numbers[j][i] << "\n";
                    idx++;
                }
            }
            
        }
        cerr << chrono.get();
    }
    return 0;
}

