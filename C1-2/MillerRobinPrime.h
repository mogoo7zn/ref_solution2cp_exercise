#ifndef __MillerRobinPrime__
#define __MillerRobinPrime__

#include "BigNumber.h"

#define MAX_SMALL_PRIMES 100

bool is_prime(BigNumber n, size_t trials);

void generate_prime_number(uint8_t number[], int nbits, size_t trials, size_t smallPrimesCnt);


#endif
