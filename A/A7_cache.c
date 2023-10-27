#include <stdio.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

int isPrime(long long int x);
int main() {
    long long int givenEvenNum;
    scanf("%llu", &givenEvenNum);
    //judge whether is the input is legal
    if(givenEvenNum % 2 != 0)
        return 1;
    else
    {
        int init = 3;
        while(init < givenEvenNum - init)
        {
            if(isPrime(init)) {
                if (isPrime(givenEvenNum - init)) {
                    printf("%lld = %lld + %lld\n", givenEvenNum, init, givenEvenNum - init);
                }
            }
            init += 2;
        }
    }
    return 0;
}

int isPrime(long long int x)
{
    //even number is omitted here
    long long int num = 3;
    while(num < x)
    {
        if(x % num == 0)
        {
            return FALSE;
        }
        num += 2;
    }
    return TRUE;
}
