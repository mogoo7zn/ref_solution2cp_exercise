#include <stdio.h>
#include <string.h>

#define INTEGER_LEN 2048

int radix_conversion(unsigned char *target, const unsigned char *source, int source_radix, int target_radix);

int main() {
    unsigned char source[] = "141391046812018796882845828565364197183213832872558119623989034374349862711961811761756022149157863889079827088948943796770122882454819958822797275540616354581115703212297752621840530234557508806950394391188946374934017297995851398246623558276472465752581909770271848264357732979566326617319645868441609151211";
    unsigned char target[INTEGER_LEN] = {0};

    int len = radix_conversion(target, source, 10, 256);

    int i;
    for (i = len - 1; i >= 0; i--) {
        printf("%.2x", target[i]);
    }
    printf("\n");

    return 0;
}

// Radix conversion: source to target. Big-endian source integer and little-endian target integer.
// unsigned char *target, const unsigned char *source, int source_radix, int target_radix
int radix_conversion(unsigned char *target, const unsigned char *source, int source_radix, int target_radix) {
    size_t ti = 0;
    unsigned char sc[INTEGER_LEN] = {0};

    if (strlen(source) == 0) return 0;

    strcpy(sc, source);
    while (strlen(sc) > 0) {
        size_t k = 0, sci = 0, qi = 0, r = 0;
        unsigned char q[INTEGER_LEN] = {0};
        while (sc[sci] != 0) {
            k = r * source_radix + (sc[sci++] - '0');
            r = k % target_radix;
            if (k >= target_radix || qi > 0) {
                q[qi++] = k / target_radix + '0';
            }
        }
        target[ti++] = r;
        strcpy(sc, q);
    }

    return ti;
}