#include <stdio.h>

long long gcd(long long a, long long b);
int main() {
    unsigned long long int a, b, c;
    long long int n;
    scanf("%lld", &n);
    while(n--)
    {
        scanf("%llu%llu%llu", &a,&b,&c);
        int temp;

//        sort a, b, c
        if(a > b)
        {
            temp = a, a = b, b = temp;
        }
        if(b > c)
        {
            temp = b, b = c, c = temp;
        }
        if(a > b)
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
                long long divisor1, divisor2, commonDivisor;
                divisor1 = gcd(a, b);
                divisor2 = gcd(b, c);
                commonDivisor = gcd(divisor1, divisor2);
                a /=  commonDivisor, b /= commonDivisor, c /= commonDivisor;


//               compare divisors

                unsigned long long sub, sum;
                sub = c - b, sum = c + b;
                unsigned long long k1 = a / gcd(a, sub);
                unsigned long long k2 = sub / gcd(a, sub);
                unsigned long long k3 = a / gcd(a, sum);
                unsigned long long k4 = sum / gcd(a, sum);

//               (neglect it) l1 = (long double)a * (long double)a, l2 = (long double)b * (long double)b, l3 = (long double)c * (long double)c;
                if (a == b && b == c)
                {
                    printf("dengbian\n");
                }
                /*else if ((a == b || b == c || c == a) && (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a))
                {
                    printf("dengyaozhijiao\n");
                }*/
                else if (k1 == k4 && k2 == k3)
                {
                    printf("zhijao\n");
                }
                else if (a == b || b == c || c == a)
                {
                    printf("dengyao\n");
                }
                else
                {
                    printf("putong\n");
                }
            }
            else
            {
                printf("error\n");
            }
        }
    }
    return 0;
}

long long gcd(long long a, long long b)
{
    if(b == 0)
    {
        return a;
    }else
    {
        return gcd(b, a % b);
    }
}