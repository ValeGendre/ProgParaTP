#include "threaded_prime.h"
#include <iostream>


void thread_is_prime_one_number(mpz_class candidate, bool *truth_value, int id, pthread_mutex_t *lmutex)
{
    if ( prob_prime(candidate, 10) )
    {
        if (prob_prime(candidate, 40))
        {
            pthread_mutex_lock(lmutex);
            truth_value[id] = true;
            pthread_mutex_unlock(lmutex);
        }
    }
}

void *thread_is_prime(void *arguments)
{
    struct arg_struct *args = (struct arg_struct *)arguments;
    mpz_class *candidates = args -> candidates;
    mpz_class candidate;
    bool *truth_value = args -> truth_value;
    pthread_mutex_t *lmutex = args -> lmutex;
    unsigned long long tab_size = args -> tab_size;

    for (unsigned long long i = 0; i < tab_size; i++)
    {
        candidate = candidates[i];
        thread_is_prime_one_number(candidate, truth_value, i, lmutex);
    }
    pthread_exit(NULL);
}