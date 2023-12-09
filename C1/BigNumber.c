//
// Created by znwang on 2023/10/12.
//
#include "BigNumber.h"

//note: the whole number is seperated into 256 segments, and they are stored reversely in an array
//big_n a[0] represents 0 in base
typedef uint8_t big_n[Big_n_Size];//big_n here is the whole array representing _Big_Number_(1024bits)
big_n big_n_cache[Big_n_Base];//big_n_cache is

//b = a + b
void big_n_add_big_n(big_n a, big_n b)
{
    uint16_t sum = 0, i;
    for(i = 0; i < Big_n_Size; i++){
        sum += (uint16_t) (a[i] + b[i]);
        b[i] = sum % Big_n_Base;
        sum /= Big_n_Base;
    }
}

//b = b + int
void big_n_add_int(big_n b, uint16_t a)
{
//    TODO:this part is different
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        b[i] = (a + b[i]) % Big_n_Base;
        a /= Big_n_Base;
        if (a == 0)
            break;
    }
}

//b = b - a
void big_n_sub_big_n(big_n a, big_n b)
{
    uint16_t borrow = 0, i;
    for(i = 0; i < Big_n_Size; i++){
        if(b[i] - borrow < a[i]){
            b[i] = b[i] - a[i] + Big_n_Base - borrow;
            borrow = 1;
        }else{
            b[i] -= a[i] + borrow;
            borrow = 0;
        }
    }
}

//b = b - int
void big_n_sub_int(big_n b, uint16_t a)
{
//    TODO:check if a > base
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        if (b[i] < a){
            b[i] = a = b[i] + Big_n_Base - a;
            a = 1;
        }else{
            b[i] -= a;
            a = 0;
        }
    }
}

//p = b * a
void big_n_mul_big_n(big_n a, big_n b, big_n p)
{
    big_n tmp;
    clear_big_n(p);
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        memcpy(tmp, b, Big_n_Size);
        big_n_mul_int(tmp, a[i]);
        big_n_shl(tmp, i);
        big_n_add_big_n(tmp, p);
    }
}

//b = b * int
void big_n_mul_int(big_n b, uint16_t a)
{
    uint16_t add = 0;
    size_t i;
    for(i = 0 ; i < Big_n_Size; i++){
        add += (uint16_t)(b[i] * a);
        b[i] = add % Big_n_Base;
        add = (uint16_t)(add / Big_n_Base);
    }
}

//r = b % a
void big_n_mod_int(big_n b, size_t a, size_t *r)
{
    *r = 0;
    size_t i = 0;
    for(i = Big_n_Size; i > 0; i--){
        *r = (*r * Big_n_Base + b[i]) % a;
    }
}

//a = a >> 8*sh
void big_n_shr(big_n a, size_t sh)
{
    if(sh == 0)
        return;
    sh = Big_n_Size > sh ? sh : Big_n_Size;
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        a[i] = a[i + sh];
    }
    for (int i = 0; i < sh; i++) {
        a[Big_n_Size - 1 - i] = 0;
    }
}

//a = a << 8*sh
void big_n_shl(big_n a, size_t sh)
{
    if(sh == 0)
        return;
    sh = Big_n_Size > sh ? sh : Big_n_Size;
    size_t i;
    for(i = Big_n_Size - 1; i >= sh; i--){
        a[i] = a[i - sh];
    }
    for(i = 0; i < sh; i++){
        a[i] =0;
    }
}

//a>>sh
void big_n_shr_bit(big_n a, size_t sh)
{
    if(sh == 0) return;
    big_n_shr(a, sh / Len_Cache);
    sh %= Len_Cache;
    if (sh == 0) return;
    uint8_t tmp1 = 0, tmp2 = 0;
    uint8_t mask = (1 << sh) - 1;
    size_t i;
    for (i = Big_n_Size - 1; i > 0; i--){
        tmp1 = a[i] & mask;
        a[i] >>= sh;
        a[i] |= tmp2 << (Len_Cache - sh);
        tmp2 = tmp1;
    }
}

//a<<sh
void big_n_shl_bit(big_n a, size_t sh)
{
    if(sh == 0) return;
    big_n_shl(a, sh / Len_Cache);
    sh %= Len_Cache;
    if(sh == 0) return;
    uint8_t tmp1 = 0, tmp2 = 0;
    uint8_t mask = Big_n_Base - (1 << (Len_Cache - sh));
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        tmp1 = mask & a[i];
        a[i] << sh;
        a[i] |= tmp2 >> (Len_Cache - sh);
        tmp2 = tmp1;
    }
}

//b % a = r
void big_n_mod_big_n(big_n a, big_n b, big_n r)
{
    //TODO:not finished
}

//b / a = n, b % a = r
void big_n_div_big_n(big_n a, big_n b, big_n n, big_n r)
{
    big_n tmp;
    clear_big_n(tmp), clear_big_n(r), clear_big_n(n);
    size_t i;
    for(i = Big_n_Size - 1; i > 0; i--){
        big_n_shl(r, 1);
        big_n_add_int(r, b[i]);
        if(big_n_compare_equal(a, r)){
            uint16_t j = 0;
            while(big_n_compare(a, r)){
                big_n_add_big_n(a,tmp);
                j++;
            }
            *(n + 1) = j - 1;
            big_n_sub_big_n(a,tmp);//roll back once and subtract it from tmp to fetch the rest
            big_n_sub_big_n(tmp, r);
        }else{
            *(n + 1) = 0;
        }
    }
}

//r = pow(a, k) mod n
void big_n_pow_mod(big_n a, big_n k, big_n n, big_n r)
{
    big_n tmp;
    clear_big_n(tmp);
    big_n_one(r);
    while (is_big_n_zero(k) == FALSE){
        if (big_n_is_odd(k)){   //如果是奇数，那么手动模一个，变成偶数了就丢给后面移位处理
            big_n_mul_big_n(r, a, tmp);
            big_n_mod_big_n(n, tmp, r);
        }
        big_n_shr_bit(k, 1);
        big_n_mul_big_n(a, a, tmp);
        big_n_mod_big_n(n, tmp, r);
    }
}

//judge whether two big numbers are equal
bool big_n_equal(big_n a, big_n b)
{
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        if(a[i] != b[i])
            return FALSE;
    }
    return TRUE;
}

//judge whether the number is an even number
bool big_n_is_even(big_n a)
{
    return (a[0] & 1) == 0;
}

//judge whether the number is an odd number
bool big_n_is_odd(big_n a)
{
    return (a[0] & 1) != 0;
}

//compare b > a
bool big_n_compare(big_n a, big_n b)
{
    size_t i;
    for(i = Big_n_Size - 1; i > 0; i++){
        if(b[i] > a[i]) return TRUE;
        if(b[i] < a[i]) return FALSE;
    }
    return FALSE;
}

//compare b>=a
bool big_n_compare_equal(big_n a, big_n b)
{
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        if(b[i] > a[i]) return TRUE;
        if(b[i] < a[i]) return FALSE;
    }
    return TRUE;
}

//a ?= 0
bool is_big_n_zero(big_n a)
{
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        if(a[i] != 0) return FALSE;
        return TRUE;
    }
}

//generate random number big number
void big_n_rand(big_n a)
{
    time_t time;
    srand(time);
    size_t i;
    for(i = 0; i < Big_n_Size; i++){
        a[i] = rand() % Big_n_Base;
    }
}

//generate random big_n in required range b
void big_n_rand_in_range(big_n a, big_n b)
{
    big_n tmp, n;
    big_n_rand(a);
    copy_big_n(tmp, a);
    big_n_div_big_n(b, tmp, n, a);
}

//a = set_value
void set_big_n(big_n a, size_t set_value)
{
    clear_big_n(a);
    size_t i;
    for(i = 0; set_value > 0 && i < Big_n_Size; i++){
        a[i] = set_value % Big_n_Base;
        set_value /= Big_n_Base;
    }
}

//a = 1
void big_n_one(big_n a)
{
    clear_big_n(a);
    a[0] = 1;
}

//clear array
void clear_big_n(big_n a)
{
    memset(a, 0, Big_n_Size);
}

//copy a = b
void copy_big_n(big_n a, big_n b)
{
    memcpy(a, b, Big_n_Size);
}

//print n
void print_big_n(const big_n n) //TODO:this part is different
{
    size_t i;
    for (i = Big_n_Size / 2 - 1; i > 0; i--){
        printf("%x", n[i]);
    }
}



