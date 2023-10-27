#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b);
int main() {
    long long int a, b, c;
    long long int n;
    scanf("%lld", &n);
    while(n--)
    {
        scanf("%lld%lld%lld", &a,&b,&c);
        int temp;
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
        if (a <= 0 || b <= 0 || c <= 0)
        {
            printf("error\n");
        }
        else
        {
            if (a > c - b)
            {
                //
                long long divisor1, divisor2, commonDivisor;
                divisor1 = gcd(a, b);
                divisor2 = gcd(b, c);
                commonDivisor = gcd(divisor1, divisor2);
                a /=commonDivisor, b /= commonDivisor, c /=commonDivisor;


                long double l1, l2;

//                unsigned long long sub, sum;
//                sub = c - b, sum = c + b;
//                unsigned long long k1 = a / gcd(a, sub);
//                unsigned long long k2 = sub / gcd(a, sub);
//                unsigned long long k3 = a / gcd(a, sum);
//                unsigned long long k4 = sum / gcd(a, sum);

                l1 = (long double)a / (c - b), l2 = (long double)(c + b) / a;
                if (a == b && b == c)
                {
                    printf("dengbian\n");
                }
                /*else if ((a == b || b == c || c == a) && (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a))
                {
                    printf("dengyaozhijiao\n");
                }*/
//                k1 == k4 && k2 == k3
                else if (l1 - l2 > -1e-18 && l1 - l2 < 1e-18)
                {
                    printf("zhijiao\n");
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