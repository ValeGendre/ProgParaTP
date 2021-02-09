#include "threaded_prime.hpp"
#include <iostream>


void thread_is_prime_one_number(mpz_class candidate, bool *truth_value, int id)
{
    if ( mpz_probab_prime_p(candidate.get_mpz_t(), 10))
    {
        if (mpz_probab_prime_p(candidate.get_mpz_t(), 40))
        {
            //pthread_mutex_lock(lmutex);
            truth_value[id] = true;
            //pthread_mutex_unlock(lmutex);
        }
    }
}

void *thread_is_prime(void *arguments)
{
    struct arg_struct *args = (struct arg_struct *)arguments;
    mpz_class *candidates = args -> candidates;
    mpz_class candidate;
    bool *truth_value = args -> truth_value;
    unsigned long long tab_size = args -> tab_size;

    for (unsigned long long i = 0; i < tab_size; i++)
    {
        candidate = candidates[i];
        thread_is_prime_one_number(candidate, truth_value, i);
    }
    pthread_exit(NULL);
}