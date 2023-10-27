#include <stdio.h>
#include <math.h>
#define PRIME 1

int main() {
    int givenEven;
    scanf("%d", &givenEven);
    //certify the input
    //if(!givenEven % 2)
    //{
        /*create an array to represent a large seive, which is initially all set as PRIME
         * however, every multiple of a small integer will be erased as 0, and therefore
         * they are abandoned from the seive*/
        int maxlength = givenEven;
        int primes[maxlength];
        int i, j;
        for(i = 0; i < maxlength; i++)
        {
            primes[i] = PRIME;
        }

        //ascertain testing numbers
        int limit = sqrt(givenEven) + 1;
        for(i = 2; i < limit; i++)
        {
            if(primes[i - 1])
            {
                for(j = 2 * i; j < maxlength; j += i)
                {
                    primes[j - 1] = 0;
                }
            }
        }

        //pick out wanted numbers
        for(i = 3; i <= maxlength / 2; i++)
        {
            if(primes[i-1])
            {
                if(primes[maxlength - i - 1])
                {
                    printf("%d = %d + %d\n", givenEven, i, givenEven - i);
                }
            }
        }
    //}
    return 0;
}
