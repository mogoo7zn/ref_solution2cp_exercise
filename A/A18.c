#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#define TIMES 3

double calPi(long long n);
int main() {
    long long seed;
    scanf("%lld", &seed);
    srand((unsigned int) seed);
    long long n = 10000;
    double pi;
    int i = TIMES;
    while(i--)
    {
        pi = calPi(n);
        printf("%lf\n", pi);
        n *= 10;
    }
    return 0;
}

double calPi(long long n)
{
//    time_t t;
//    srand((unsigned long) time(&t));
    long long cnt = 0, i;
    double x, y, pi;
    for(i = 0; i < n; i++)
    {
        x = rand() / (double)(RAND_MAX);
        y = rand() / (double)(RAND_MAX);
        if(pow(x, 2) + pow(y, 2) < 1)
        {
            cnt++;
        }
    }
    pi = 4 * cnt / (double)n;
    return pi;
}
