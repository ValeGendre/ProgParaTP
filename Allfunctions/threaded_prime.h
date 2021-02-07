#include "miller-rabin-gmp.h"
#include <vector>
#include <pthread.h>

struct arg_struct{
    mpz_class *candidates;
    bool *truth_value;
    pthread_mutex_t *lmutex;
    bool *tested;
    int tab_size;
};

void thread_is_prime_one_number(mpz_class candidate, bool *truth_value, bool *tested, int id, pthread_mutex_t *lmutex);
void *thread_is_prime(void *arguments);