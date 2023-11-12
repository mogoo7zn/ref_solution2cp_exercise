#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b);
int main(void) {
    unsigned long long int a, b, c;
    long n;
    scanf("%ld", &n);
    while(n--)
    {
        scanf("%llu%llu%llu", &a,&b,&c);
        int temp;

//        sort a, b, c
        if(a >= b)
        {
            temp = a, a = b, b = temp;
        }
        if(b >= c)
        {
            temp = b, b = c, c = temp;
        }
        if(a >= b)
        {
            temp = a, a = b, b = temp;
        }

//        judge whether the inputs are legal
        if (a <= 0 || b <= 0 || c <= 0)
        {
            printf("error\n");
        }
        else
        {
            if (a > c - b)
            {
//                 divide the greatest common divisor
                unsigned long long divisor1, divisor2, commonDivisor;
                divisor1 = gcd(a, b);
                divisor2 = gcd(b, c);
                commonDivisor = gcd(divisor1, divisor2);
                a = a / commonDivisor, b = b / commonDivisor, c = c / commonDivisor;

                if (a == b && b == c)
                {
                    printf("dengbian\n");
                }
                    /*else if ((a == b || b == c || c == a) && (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a))
                    {
                        printf("dengyaozhijiao\n");
                    }*/
                else if (a == b || b == c || c == a)
                {
                    printf("dengyao\n");
                }
                else if(a != b && b != c && c != a) {
                    //compare divisors
                    unsigned long long sub, sum;
                    sub = c - b, sum = c + b;
                    unsigned long long k1 = (unsigned long long) (a / gcd(a, sub));
                    unsigned long long k2 = (unsigned long long) (sub / gcd(a, sub));
                    unsigned long long k3 = (unsigned long long) (a / gcd(a, sum));
                    unsigned long long k4 = (unsigned long long) (sum / gcd(a, sum));

                    if (k1 == k4 && k2 == k3) {
                        printf("zhijao\n");
                    } else {
                        printf("putong\n");
                    }
                }
            }else
            {
                printf("error");
            }
        }
    }
    return 0;
}

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    if(b == 0)
    {
        return a;
    }else
    {
        return gcd(b, a % b);
    }
}