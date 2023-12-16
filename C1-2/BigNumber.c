#include "BigNumber.h"

BigNumber bn_cache[BN_Base + 1];
bool bn_cache_empty = true;
BigNumber bn_lastnum;

// a == b
bool bn_equal(BigNumber a, BigNumber b) {
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// a < b
bool bn_less(BigNumber a, BigNumber b) {
    size_t i = 0;
    for (i = BN_Size - 1; ; i--) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
        if (i == 0) break;
    }
    return false;
}

// a <= b
bool bn_less_or_equal(BigNumber a, BigNumber b) {
    size_t i = 0;
    for (i = BN_Size - 1; ; i--) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
        if (i == 0) break;
    }
    return true;
}

// a == 0
bool bn_is_zero(BigNumber a) {
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        if (a[i] != 0) return false;
    }
    return true;
}

// a & 1 == 0
bool bn_is_even(BigNumber a) {
    return (a[0] & 1) == 0;
}

// a & 1 == 1
bool bn_is_odd(BigNumber a) {
    return (a[0] & 1) == 1;
}

// a = 0
void bn_set_zero(BigNumber a) {
    memset(a, 0, BN_Size);
}

// a = 1
void bn_set_one(BigNumber a) {
    bn_set_zero(a);
    a[0] = 1;
}

// a = value
void bn_set(BigNumber a, size_t value) {
    bn_set_zero(a);
    size_t i = 0;
    while (value > 0 && i < BN_Size) {
        a[i] = value % BN_Base;
        value /= BN_Base;
        i++;
    }
}

// a = b
void bn_set_bn(BigNumber a, BigNumber b) {
    memcpy(a, b, BN_Size);
}

//b = b + a
void bn_add_bn(BigNumber a, BigNumber b) {
    uint16_t x = 0;
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        x = (uint16_t) b[i] + a[i] + x;
        b[i] = x % BN_Base;
        x /= BN_Base;
    }
}

//b = b + a
void bn_add_int(uint8_t a, BigNumber b) {
    uint16_t x = a;
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        x = (uint16_t) b[i] + x;
        b[i] = x % BN_Base;
        x /= BN_Base;
        if (x == 0) break;
    }
}

//b = b - a
void bn_sub_bn(BigNumber a, BigNumber b) {
    uint16_t r = 0;
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        if (b[i] < a[i] + r) {
            b[i] = r = BN_Base + b[i] - a[i] - r;
            r = 1;
        } else {
            b[i] -= r + a[i];
            r = 0;
        }
    }
}

//b = b - a
void bn_sub_int(uint8_t a, BigNumber b) {
    uint16_t r = a;
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        if (b[i] < r) {
            b[i] = r = BN_Base + b[i] - r;
            r = 1;
        } else {
            b[i] -= r;
            r = 0;
        }
    }
}

//a = a << 8*sh (base 256)
void bn_shl(BigNumber a, size_t sh) {
    if (sh == 0) return;
    sh = min(BN_Size, sh);
    size_t i = 0;
    for (i = BN_Size - 1; i >= sh; i--) {
        a[i] = a[i - sh];
    }

    for (i = 0; i < sh; i++) {
        a[i] = 0;
    }
}

//a = a >> 8*sh (base 256)
void bn_shr(BigNumber a, size_t sh) {
    if (sh == 0) return;
    sh = min(BN_Size, sh);
    size_t i = 0;
    for (i = 0; i < BN_Size - sh; i++) {
        a[i] = a[i + sh];
    }

    for (i = 0; i < sh; i++) {
        a[BN_Size - 1 - i] = 0;
    }
}

//a = a << sh
void bn_shbl(BigNumber a, size_t sh) {
    if (sh == 0) return;
    bn_shl(a, sh / BN_Bits);
    sh = sh % BN_Bits;
    if (sh == 0) return;

    uint16_t mask = BN_Base - (1 << (BN_Bits - sh));
    uint8_t bits0 = 0, bits1 = 0;
    size_t i = 0;
    for (i = 0; i < BN_Size; ++i) {
        bits1 = a[i] & mask;
        a[i] <<= sh;
        a[i] |= bits0 >> (BN_Bits - sh);
        bits0 = bits1;
    }
}

// a = a >> sh
void bn_shbr(BigNumber a, size_t sh) {
    if (sh == 0) return;
    bn_shr(a, sh / BN_Bits);
    sh = sh % BN_Bits;
    if (sh == 0) return;

    uint16_t mask = (1 << sh) - 1;
    uint8_t bits0 = 0, bits1 = 0;
    size_t i = 0;
    for (i = BN_Size - 1; ; i--) {
        bits1 = a[i] & mask;
        a[i] >>= sh;
        a[i] |= bits0 << (BN_Bits - sh);
        bits0 = bits1;
        if (i == 0) break;
    }
}

// b = b * a
void bn_mul_int(uint8_t a, BigNumber b) {
    uint16_t r = 0;
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        r += (uint16_t) a * b[i];
        b[i] = r % BN_Base;
        r /= BN_Base;
    }
}

// p = a * b
void bn_mul_bn(BigNumber a, BigNumber b, BigNumber p) {
    BigNumber t;
    bn_set_zero(p);
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        memcpy(t, b, BN_Size);
        bn_mul_int(a[i], t);
        bn_shl(t, i);
        bn_add_bn(t, p);
    }
}

// b / a = q, b % a = r
void bn_div_bn(BigNumber a, BigNumber b, BigNumber q, BigNumber r) {
    bn_set_zero(q);
    bn_set_zero(r);
    BigNumber t;
    bn_set_zero(t);
    size_t i = 0;
    for (i = BN_Size - 1; ; i--) {
        bn_shl(r, 1);
        bn_add_int(b[i], r);
        if (bn_less_or_equal(a, r)) {
            bn_set_zero(t);
            uint8_t k = 0;
            do {
                k++;
                bn_add_bn(a, t);
            } while (bn_less_or_equal(t, r));
            q[i] = k - 1;
            bn_sub_bn(a, t);
            bn_sub_bn(t, r);
        } else {
            q[i] = 0;
        }
        if (i == 0) break;
    }
}

// b % a = r
void bn_mod_bn2(BigNumber a, BigNumber b, BigNumber r) {
    BigNumber q;
    bn_div_bn(a, b, q, r);
}

// b % a = r
void bn_mod_bn(BigNumber a, BigNumber b, BigNumber r) {
    if (bn_less(b, a)) {
        bn_set_bn(r, b);
        return;
    }

    bn_set_zero(r);
    BigNumber t;

    bn_set_bn(bn_lastnum, a);
    if (bn_cache_empty || bn_equal(a, bn_lastnum) == false) {
        bn_set_zero(t);
        size_t k;
        for (k = 0; k <= BN_Base; k++) {
            bn_set_bn(bn_cache[k], t);
            bn_add_bn(a, t);
        }
        bn_set_bn(bn_lastnum, a);
    }

    size_t i;
    for (i = BN_Size - 1; ; i--) {
        bn_shl(r, 1);
        bn_add_int(b[i], r);

        if (bn_less_or_equal(a, r)) {
            if (bn_less_or_equal(bn_cache[BN_Base - 1], r)) {
                bn_sub_bn(bn_cache[BN_Base - 1], r);
            } else {
                int k0 = 0;
                int k1 = BN_Base;
                while (k1 != (k0 + 1)) {
                    int m = (k0 + k1) / 2;
                    if (bn_less_or_equal(bn_cache[m], r)) {
                        k0 = m;
                    } else {
                        k1 = m;
                    }
                }
                bn_sub_bn(bn_cache[k0], r);
            }
        }
        if (i == 0) break;
    }
}

// b % a = r
void bn_mod_int(size_t a, BigNumber b, size_t *r) {
    *r = 0;
    size_t i = 0;
    for (i = BN_Size - 1; ; i--) {
        *r = (*r * BN_Base + b[i]) % a;
        if (i == 0) break;
    }
}

// generate random number a
void bn_rand(BigNumber a) {
    srand(time(0));
    size_t i = 0;
    for (i = 0; i < BN_Size; i++) {
        a[i] = rand() % BN_Base;
    }
}

// generate random number a < b
void bn_rand_range(BigNumber a, BigNumber b) {
    bn_rand(a);
    BigNumber t;
    bn_set_bn(t, a);

    BigNumber q;
    bn_div_bn(b, t, q, a);
}

// r = a^x mod n
void bn_pow_mod(BigNumber a, BigNumber x, BigNumber n, BigNumber r) {
    BigNumber t;
    bn_set_one(r);
    bn_set_zero(t);

    while (bn_is_zero(x) == false) {
        if (bn_is_odd(x)) {
            bn_mul_bn(a, r, t);
            bn_mod_bn(n, t, r);
        }
        bn_shbr(x, 1);
        bn_mul_bn(a, a, t);
        bn_mod_bn(n, t, a);
    }
}
