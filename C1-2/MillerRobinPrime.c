#include "MillerRobinPrime.h"

/*
 * Miller-Robin primality test
 * return false: number n is composite
 * return true:  number n is very likely to be a prime
 */
bool is_prime(BigNumber n, size_t trials) {
    if (bn_is_even(n)) return false;

    BigNumber _1;
    bn_set_one(_1);
    BigNumber n_1;
    bn_set_bn(n_1, n);
    bn_sub_bn(_1, n_1);

    size_t k = 0;
    BigNumber m;
    bn_set_bn(m, n_1);
    while (bn_is_even(m)) {
        k++;
        bn_shbr(m, 1);
    }

    BigNumber q;
    {
        bn_set_bn(m, n_1);
        BigNumber t;
        bn_set_bn(t, _1);
        BigNumber r;
        bn_shbl(t, k);
        bn_div_bn(t, m, q, r);
    }

    size_t i;
    trials = max(trials, 3);
    for (i = 0; i < trials; i++) {
        BigNumber a;
        {
            BigNumber _max;
            bn_set_bn(_max, n);
            BigNumber _2;
            bn_set(_2, 2);
            BigNumber _4;
            bn_set(_4, 4);
            bn_sub_bn(_4, _max);

            bn_rand_range(a, _max);
            bn_add_bn(_2, a);
        }

        BigNumber x;
        bn_pow_mod(a, q, n, x);

        if (bn_equal(x, _1) || bn_equal(x, n_1)) continue;
        size_t j;
        for (j = 0; j < k - 1; j++) {
            BigNumber x2, g;
            bn_mul_bn(x, x, x2);
            bn_mod_bn(n, x2, g);
            bn_set_bn(x, g);

            if (bn_equal(x, _1)) return false;
            if (bn_equal(x, n_1)) break;
        }

        if (bn_equal(x, n_1) == false) return false;
    }
    return true;
}

void generate_prime_number(uint8_t number[], int nbits, size_t trials, size_t smallPrimesCnt) {
    size_t smallPrimes[MAX_SMALL_PRIMES] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                            31, 37, 41, 43, 47, 53, 59, 61,
                                            67, 71, 73, 79, 83, 89, 97, 101,
                                            103, 107, 109, 113, 127, 131, 137,
                                            139, 149, 151, 157, 163, 167, 173,
                                            179, 181, 191, 193, 197, 199, 211,
                                            223, 227, 229, 233, 239, 241, 251,
                                            257, 263, 269, 271, 277, 281, 283,
                                            293, 307, 311, 313, 317, 331, 337,
                                            347, 349, 353, 359, 367, 373, 379,
                                            383, 389, 397, 401, 409, 419, 421,
                                            431, 433, 439, 443, 449, 457, 461,
                                            463, 467, 479, 487, 491, 499, 503,
                                            509, 521, 523, 541};

    srand(time(0));

    BigNumber n_lo, n_hi, _1;
    bn_set_one(n_lo);
    bn_set_one(n_hi);
    bn_set_one(_1);
    bn_shbl(n_lo, nbits - 1);
    bn_shbl(n_hi, nbits);
    bn_sub_bn(n_lo, n_hi);

    BigNumber n;
    bn_set_zero(n);
    size_t pmod[MAX_SMALL_PRIMES];

    //printf("Searching for %d-bit prime ...\n", nbits);

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    size_t ncheck = 0;
    size_t i, p, r;
    while (true) {
        if (bn_is_zero(n)) {
            bn_rand_range(n, n_hi);
            bn_add_bn(n_lo, n);
            if (bn_is_even(n))
                bn_add_int(1, n);
            for (i = 0; i < smallPrimesCnt; i++) {
                p = smallPrimes[i];
                bn_mod_int(p, n, &r);
                pmod[i] = r;
            }
        }

        bool do_fast = true;
        while (true) {
            for (i = 0; i < smallPrimesCnt; ++i) {
                if (pmod[i] == 0) {
                    do_fast = false;
                    break;
                }
            }
            if (do_fast == false) {
                ncheck++;
                bn_add_int(2, n);
                for (i = 0; i < smallPrimesCnt; i++) {
                    p = smallPrimes[i];
                    pmod[i] += 2;
                    if (pmod[i] >= p) {
                        pmod[i] -= p;
                    }
                }
                do_fast = true;
                continue;
            } else {
                break;
            }
            if (do_fast == false) {
                break;
            }
        }

        if (is_prime(n, trials)) {
            //printf("\nFound prime p:\n");
            for (i = 0; i < 128; i++) {
                number[i] = n[127 - i];
            }
            break;
        } else {
            //printf(".");
            fflush(stdout);
        }

        ncheck++;
        bn_add_int(2, n);
        for (i = 0; i < smallPrimesCnt; i++) {
            p = smallPrimes[i];
            pmod[i] += 2;
            if (pmod[i] >= p) {
                pmod[i] -= p;
            }
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Number of small primes %3d\t Checked %4d numbers in %8d ms: %g num/sec\n", (int) smallPrimesCnt,
           (int) ncheck, (int) cpu_time_used, 1000.0 * ((double) (ncheck)) / cpu_time_used);
}
