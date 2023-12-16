#include "MillerRobinPrime.h"

#define MILLER_ROBIN_TRIALS 10
#define PRIME_NUMBER_BITS 1024
#define USING_SMALL_PRIMES 60

int main() {
    uint8_t prime[128];
    char filename[] = "D:/C1.txt";
    char str[2 + 1] = "", str_big_number[256 + 1] = "";
    size_t i;

    generate_prime_number(prime, PRIME_NUMBER_BITS, MILLER_ROBIN_TRIALS,
                          USING_SMALL_PRIMES);

    // Print big prime to screen
    for (i = 0; i < 128; i++) {
        printf("%.2x", prime[i]);
    }
    printf("\n");

    // Save big prime to text file
    for (i = 0; i < 128; i++) {
        itoa(prime[i], str, 16);
        str_big_number[i * 2] = str[0];
        str_big_number[i * 2 + 1] = (str[1] == '\0' ? '0':str[1]);
        //sprintf(str, "%.2x", prime[i]);
        //strcat(str_big_number, str);
    }
    FILE *fp = fopen(filename, "a");
    if (NULL == fp) return 1;
    fputs(str_big_number, fp);
    fputs("\n", fp);
    fclose(fp);

    return 0;
}
