//
// Created by znwan on 2023/10/12.
//

#ifndef C1_BIGNUMBER_H
#define C1_BIGNUMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define bool int
#define Big_n_Size 256
#define Big_n_Base 256
#define Len_Cache 8
#define TRUE (1 == 1)
#define FALSE !TRUE

#endif //C1_BIGNUMBER_H

typedef uint8_t big_n[Big_n_Size];//big_n here is the whole array representing _Big_Number_(1024bits)
big_n big_n_segment[Big_n_Base];//big_n_cache is each segment of the entire _Big_Number_

void big_n_add_big_n(big_n a, big_n b);
void big_n_add_int(big_n b, uint16_t a);
void big_n_sub_big_n(big_n a, big_n b);
void big_n_sub_int(big_n b, uint16_t a);
void big_n_mul_big_n(big_n a, big_n b, big_n p);
void big_n_mul_int(big_n b, uint16_t a);
void big_n_mod_int(big_n b, size_t a, size_t *r);
void big_n_shr(big_n a, size_t sh);
void big_n_shl(big_n a, size_t sh);
void big_n_shr_bit(big_n a, size_t sh);
void big_n_shl_bit(big_n a, size_t sh);
void big_n_mod_big_n(big_n a, big_n b, big_n r);
void big_n_div_big_n(big_n a, big_n b, big_n n, big_n r);
void big_n_pow_mod(big_n a, big_n k, big_n n, big_n r);

bool big_n_equal(big_n a, big_n b);
bool big_n_is_even(big_n a);
bool big_n_is_odd(big_n a);
bool big_n_compare(big_n a, big_n b);
bool big_n_compare_equal(big_n a, big_n b);
bool is_big_n_zero(big_n a);


void big_n_rand(big_n a);
void big_n_rand_in_range(big_n a, big_n b);
void set_big_n(big_n a, size_t set_value);
void big_n_one(big_n a);
void clear_big_n(big_n a);
void copy_big_n(big_n a, big_n b);
void print_big_n(const big_n n);
