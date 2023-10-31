#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 6554
#define GIVEN_CACHE_SIZE 1

unsigned int cache[MAX_LENGTH] = {2};

void generatePrimerTable(unsigned int number);
int main() {
    unsigned int givenNumber;
    scanf("%ud", &givenNumber);
    generatePrimerTable(givenNumber);
    int i;
    for(i = 0; i < MAX_LENGTH; i++)
    {
        while(givenNumber % cache[i] == 0)
        {
            printf("%ud", cache[i]);
        }
    }
    return 0;
}

void generatePrimerTable(unsigned int number)
{
    unsigned int limit = (unsigned int)(sqrt(number) + 2);
    int i = GIVEN_CACHE_SIZE, j;
    int m = 3;
    while(m < limit)
    {
        int flag = 0;
        for(j = 0; j < i; j++)
        {
            if(m % cache[j] == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            i++;
            cache[i] = m;
        }
        m += 2;
    }
}

//int isPrime(unsigned int number)
//{
//    int limit = (int)(sqrt(number) + 1);
//    int m = 20, i;
//    while(m < limit)
//    {
//        for(i = 0;;i++)
//        {
//            if()
//        }
//        m++;
//    }
//}