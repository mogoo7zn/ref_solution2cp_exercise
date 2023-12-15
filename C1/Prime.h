//
// Created by znwan on 2023/10/14.
//

#ifndef C1_PRIME_H
#define C1_PRIME_H
#define Prime_Table_Cnt 50
#define Mod_Table_Size 100
#define Test_Times 10

#include "BigNumber.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>

bool is_prime(big_n n, size_t times);
void generate_prime(int num_bits);
#endif //C1_PRIME_H