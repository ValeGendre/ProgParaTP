#include "threaded_prime.hpp"
#include "intervals.hpp"
#include <fstream>
#include <vector>
#include <pthread.h>
#include "math.h"
#include "Chrono.hpp"
#include "iostream"

pthread_mutex_t lMutex = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

int main(int argc, char * argv[])
{
    
    if (argc == 2 + 1)
    {
        Chrono chrono = new Chrono(false);
        int nb_thread = atoi(argv[1]); // get number of threads
        string filename = argv[2]; // get filename (ex : Exemples\ de\ fichiers/4_variÇ2.txt)
        dataNumbers data = getNumbersToTestInOrder(filename, chrono); // get the number of candidates and a tab of candidates

        mpz_class *candidates = data.tab; // get the tab of candidates 
        unsigned long long nb_int = data.nbNumbers; // get the number of candidates 


        unsigned long long size_of_part = (unsigned long long) ceil(((double) nb_int) / ((double) nb_thread)); // Get the nb of candidates each thread will test

        mpz_class *numbers[nb_thread]; // create a tab which will contain nb_thread tab of mpz_class of the size size_of_parts, the nb of candidates each thread wil test
        for (int i = 0; i < nb_thread; i++)
        {
          numbers[i] = new mpz_class[size_of_part];
        }

        unsigned long long *tabsizes = new unsigned long long[nb_thread]; // create a tab of unsigned long long of size number of threads 
        for (int i = 0; i < nb_thread; i++)
        {
            tabsizes[i] = 0;
        }

        // tabsizes will stock the number of candidates to test for each threads
        // numbers will stock for each thread all the candidates to test
        unsigned long long idx = 0;
        for (unsigned long long i = 0; i < nb_int;)
        {
            for (int j = 0; j < nb_thread; j++) 
            {
                numbers[j][idx] = candidates[i]; 
                tabsizes[j]++;

                i++; 
                if (i == nb_int) 
                {
                    break;
                }
            }
            idx++;
        }

        bool *prime[nb_thread];
        for (int i = 0; i < nb_thread; i++)
        {
          prime[i] = new bool[size_of_part];
        }
        for (int i = 0; i < nb_thread; i++)
        {
            for (unsigned long long j = 0; j<size_of_part; j++)
            {
                prime[i][j] = false;
            }
        }
        pthread_t threads[nb_thread];

        struct arg_struct args[nb_thread];
        

        for (int i = 0; i<nb_thread; i++)
        {
            args[i].candidates = numbers[i];
            args[i].truth_value = prime[i];
            args[i].tab_size = tabsizes[i];
            pthread_create(&threads[i], NULL, thread_is_prime, (void *) &args[i]);
        }

        for (int i = 0; i<nb_thread; i++)
        {
            pthread_join(threads[i], NULL);
        }
        chrono.pause();

        for (unsigned long long i = 0; i < size_of_part; i++)
        {
            for (int j = 0; j < nb_thread; j++)
            {
                if (prime[j][i])
                {
                    cout << numbers[j][i] << endl;
                }
            }
            
        }
        cerr << "Chrono : " << chrono.get() << endl;
    }
    return 0;
}

