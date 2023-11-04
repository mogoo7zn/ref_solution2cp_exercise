#pragma GCC optimize(3)
#include <stdio.h>
#include <math.h>

int main() {
    //n is the input
    long long int n, N;
    long long int number, max, init;
    scanf("%lld", &n);
    N = (long long int)pow(n, 3);
    max = n;
    if(n == 1)
    {
        return -1;
    }else if(n % 2 == 1)
    {
        for(number = 1; number <= (N + 1) / 2; number += 2)
        {
            if(N % number == 0 && N / number >= number)
            {
                max = number;
            }
        }
        init = N / max - max + 1;
        printf("%lld^3=%lld=", n, N);
        while(max--)
        {
            if(max > 0)
            {
                printf("%lld+", init);
                init += 2;
            }else
            {
                printf("%lld", init);
                init += 2;
            }
        }
    }else if(n % 2 == 0) {
        for (number = 2; number <= N / 2; number += 2) {
            if (N % number == 0 && N / number >= number) {
                max = number;
            }
        }
        init = N / max - max + 1;
        printf("%lld^3=%lld=", n, N);
        while(max--)
        {
            if(max > 0)
            {
                printf("%lld+", init);
                init += 2;
            }else
            {
                printf("%lld", init);
                init += 2;
            }
        }
    }else
    {}
    return 0;
}

