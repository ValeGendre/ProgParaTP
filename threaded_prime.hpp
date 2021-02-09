#include <gmpxx.h>
#include <stdint.h>
#include <vector>
#include <pthread.h>

struct arg_struct{
    mpz_class *candidates;
    bool *truth_value;
    unsigned long long tab_size;
};

void thread_is_prime_one_number(mpz_class candidate, bool *truth_value, bool *tested, unsigned long long id);
void *thread_is_prime(void *arguments);