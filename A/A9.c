#include <stdio.h>
#include <math.h>
#define PRIME 1

int main() {
    long int givenNumber;
    scanf("%ld", &givenNumber);
        long int limit = givenNumber / 2 + 1;
        int primes[limit];
        long int i, j;
        //int judge = 0;
        for(i = 0; i < limit; i++)
        {
            primes[i] = PRIME;
        }
        primes[0] = 0;
        primes[1] = 0;

        //ascertain testing numbers
        for(i = 2; i < limit; i++)
        {
            if(primes[i])
            {
                for(j = 2 * i; j < limit; j += i)
                {
                    primes[j] = 0;
                }
            }
        }

        //repeatedly divided by i
        i = 2;
        //printf("%d=",givenNumber);
        for(; i < limit; i++)
        {
            while(primes[i])
            {
                if(givenNumber % i == 0)
                {
                    /*if(judge == 0)
                    {
                        printf("%d", i);
                        judge++;
                    }else
                    {
                        printf("*%d", i);
                    }*/
                    printf("%ld ", i);
                    givenNumber = givenNumber / i;
                }else
                {
                    break;
                }
            }
        }
    return 0;
}
