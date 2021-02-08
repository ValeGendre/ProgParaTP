#include "threaded_prime.h"
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
        int nb_thread = atoi(argv[1]);
        string filename = argv[2];
        dataNumbers data = getNumbersToTestInOrder(filename);

        mpz_class *candidates = data.tab;
        unsigned long long nb_int = data.nbNumbers;


        unsigned long long size_of_part = (unsigned long long) ceil(((double) nb_int) / ((double) nb_thread));

        mpz_class *numbers[nb_thread];
        for (int i = 0; i < nb_thread; i++)
        {
          numbers[i] = new mpz_class[size_of_part];
        }

        unsigned long long tabsizes[nb_thread];
        for (int i = 0; i < nb_thread; i++)
        {
            tabsizes[i] = 0;
        }

        cout << candidates;

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
        Chrono chrono = new Chrono;

        for (int i = 0; i<nb_thread; i++)
        {
            args[i].candidates = numbers[i];
            args[i].truth_value = prime[i];
            args[i].lmutex = &lMutex;
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
                    cout << numbers[j][i] << "\n";
                    idx++;
                }
            }
            
        }
        cerr << chrono.get();
    }
    return 0;
}

