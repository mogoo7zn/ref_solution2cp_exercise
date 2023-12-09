//
// Created by znwan on 2023/10/14.
//
#include "Prime.h"

//Miller-Rabin primality test
bool is_prime(big_n n, size_t times)
{
    if(big_n_is_even(n))
        return FALSE;
    big_n judge, n_1;    //judge = (big_n)1
    big_n_one(judge);
    copy_big_n(n_1, n);
    big_n_sub_int(n_1, 1);  //n_1 = n - 1

    size_t k = 0;
    big_n n_1_copy;
    copy_big_n(n_1_copy, n_1);
    while (big_n_is_even(n_1_copy)){
        big_n_shr_bit(n_1_copy, 1);
        k++;
    }

    big_n q;
//    get q as what is shown in ppt
    {
        copy_big_n(n_1_copy, n_1);
        big_n tmp, r;
        set_big_n(tmp, 1);
        big_n_shl_bit(tmp, k);
        big_n_div_big_n(tmp, n_1_copy, q, r);
    }

    size_t i;
    for (i = 0; i < times; i++){
        big_n a;    //the same a in ppt
        {
            big_n sup;
            copy_big_n(sup, n);
            big_n_sub_int(sup, 2);
            big_n_rand_in_range(a, sup);
        }
        big_n r;
        big_n_pow_mod(a, q, n, r);  //a to the x mod n
        if (big_n_compare_equal(r, n_1) || big_n_compare_equal(r, judge))   //如果有一个余数是1或n - 1
            continue;
        size_t j;
        //the reason why here is k - 1 is that the former three lines do the job of checking the first case
        for (j = 0; j < k - 1; j++){
            big_n tmp, r_squared;
            big_n_mul_big_n(r, r, r_squared);
            big_n_mod_big_n(n, r_squared, tmp);
            copy_big_n(r, tmp);
            if (big_n_equal(r, judge))  //1 appears not in the first place
                return FALSE;
            if (big_n_equal(r, n_1))
                break;
        }
        if (big_n_equal(r, n_1))
            return FALSE;
    }
    return TRUE;
}

void generate_prime(int num_bits)
{
    uint16_t prime_table[Prime_Table_Cnt] = {2, 3, 5, 7, 11, 13, 17, 19,
                                23, 29, 31, 37, 41, 43, 47,
                                53, 59, 61, 67, 71};
/* inf is the left limit of generated big_n, while sup is the opposite case
 * judge is one expressed in big_n form and n is the big_n that need to be tested*/
    big_n inf, sup, judge, n;
    clear_big_n(n);
    big_n_one(inf), big_n_one(sup), big_n_one(judge);
    big_n_shl_bit(inf, num_bits - 1), big_n_shl_bit(sup, num_bits - 1);
    big_n_sub_int(sup, 1);
    size_t ncheck_n;    //number of checked n
    bool isPrime = TRUE;
    size_t mod_table[Mod_Table_Size];
    size_t i;
    bool _flag = 1;

    double used_time;
    time_t time;
    srand(time);
    clock_t start ,end;
    start = clock();

    while (_flag){
//        generate suitable n
        if (is_big_n_zero(n)){
            big_n_rand_in_range(n, sup);
            big_n_add_big_n(inf, n);
            if (big_n_is_even(n))
                big_n_add_int(n, 1);
            for (i = 0; i < Prime_Table_Cnt; i++){
                size_t r;
                big_n_mod_int(n, prime_table[i], &r);
                mod_table[i] = r;
            }
            while (TRUE){
//                use prime table to quick eliminate unwanted n
                for (i = 0; i < Prime_Table_Cnt; i++){
                    if (mod_table[i]){
                        isPrime = FALSE;
                        break;
                    }
                }
//                TODO:this part cannot operate correctly
                while (isPrime == FALSE){
                    short flag = 1;
                    big_n_add_int(n, 2);
                    for (i = 0; i < Prime_Table_Cnt; i++){
                        mod_table[i] += 2;
                        if (mod_table[i] >= prime_table[i])
                            mod_table[i] -= prime_table[i];
                        if (mod_table[i] == 0)
                            flag = 0;
                    }
                    if (flag == 1)
                        isPrime = TRUE;
                }
                if (is_prime(n, Test_Times)){
                    printf("find prime number:\t");
                    print_big_n(n);
                    printf("\n");
                    _flag = 0;
                    break;
                }else{
                    printf("*");
//                    TODO:here omit fflush
                }
            }
        }
    }
    end = clock();
    used_time = ((double )(end - start)) / CLOCKS_PER_SEC;
    printf("use %lf seconds\n", used_time);
}