#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PARTS 64

char* dec2bin(char *bin);


static char bin[1024];

int main() {

    return 0;
}

int *generateLargeNumber()
{

//    split the whole large number into parts in an array
//    here choose 256 as base
    int container[PARTS];


//    produce a random number
    time_t t;
    srand((unsigned) time(&t));

//    initialize the random number in each part
    int i;
    for(i = 0; i < PARTS; i++)
    {
        container[i] = rand() % 256;
    }
    return container;
}

char* dec2bin(char *bin)
{
    unsigned long long int inputNumber;
    int i;
    scanf("%ull", &inputNumber);
    for(i = 0; i < 1024; i++)
    {
        bin[i] = inputNumber % 2;
        inputNumber / 2;
    }
    printf("%s", bin);
    return bin;
}