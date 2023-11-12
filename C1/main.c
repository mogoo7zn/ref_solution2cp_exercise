#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PARTS 8

int main() {

    return 0;
}

int *generateLargeNumber()
{
//    split the whole large number into parts in an array
    int container[PARTS];
    int i;

//    produce a random number
    time_t t;
    srand((unsigned) time(&t));

//    initialize the random number in each part
    for(i = 0; i < PARTS; i++)
    {
        container[i] = (rand() * 2) % (RAND_MAX * 2);
    }
    return container;
}