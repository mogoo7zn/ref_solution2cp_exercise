#ifndef __BigNumber__
#define __BigNumber__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define BN_Size 256
#define BN_Bits 8
#define BN_Base 256

#define min(a, b) (a<b)?a:b
#define max(a, b) (a>b)?a:b

#define true (1 == 1)
#define false (!true)

typedef int bool;
typedef uint8_t BigNumber[BN_Size];


// a == b
bool bn_equal(BigNumber a, BigNumber b);

// a < b
bool bn_less(BigNumber a, BigNumber b);

// a <= b
bool bn_less_or_equal(BigNumber a, BigNumber b);

// a == 0
bool bn_is_zero(BigNumber a);

// a & 1 == 0
bool bn_is_even(BigNumber a);

// a & 1 == 1
bool bn_is_odd(BigNumber a);

// a = 0
void bn_set_zero(BigNumber a);

// a = 1
void bn_set_one(BigNumber a);

// a = value
void bn_set(BigNumber a, size_t value);

// a = b
void bn_set_bn(BigNumber a, BigNumber b);

//b = b + a
void bn_add_bn(BigNumber a, BigNumber b);

//b = b + a
void bn_add_int(uint8_t a, BigNumber b);

//b = b - a
void bn_sub_bn(BigNumber a, BigNumber b);

//b = b - a
void bn_sub_int(uint8_t a, BigNumber b);

//a = a << 8*sh (base 256)
void bn_shl(BigNumber a, size_t sh);

//a = a >> 8*sh (base 256)
void bn_shr(BigNumber a, size_t sh);

//a = a << sh
void bn_shbl(BigNumber a, size_t sh);

// a = a >> sh
void bn_shbr(BigNumber a, size_t sh);

// b = b * a
void bn_mul_int(uint8_t a, BigNumber b);

// p = a * b
void bn_mul_bn(BigNumber a, BigNumber b, BigNumber p);

// b / a = q, b % a = r
void bn_div_bn(BigNumber a, BigNumber b, BigNumber q, BigNumber r);

// b % a = r
void bn_mod_bn2(BigNumber a, BigNumber b, BigNumber r);

// b % a = r
void bn_mod_bn(BigNumber a, BigNumber b, BigNumber r);

// b % a = r
void bn_mod_int(size_t a, BigNumber b, size_t *r);

// generate random number a
void bn_rand(BigNumber a);

// generate random number a < b
void bn_rand_range(BigNumber a, BigNumber b);

// r = a^x mod n
void bn_pow_mod(BigNumber a, BigNumber x, BigNumber n, BigNumber r);

#endif
