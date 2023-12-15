#include <stdio.h>

int main() {
    int factorial(int);
    int i, n;
    long long sum = 0, max;
    scanf("%d", &n);
    scanf("%lld", &max);
    for (i = 1; i < n + 1; i++)
    {
        sum += factorial(i);
    }
    if (sum < max)
    {
        printf("%lld", sum);
    }
    else
    {
        printf("overflow");
    }
    return 0;
}

int factorial(int n)
{
    if(n == 1 || n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}





//#include <stdio.h>
//
//int main() {
//    int factorial(int);
//    int i, n, sum, max;
//    scanf("%d", &n);
//    scanf("%d", &max);
//    for (i = 1; i < n + 1; i++)
//    {
//        sum += factorial(i);
//    }
//    if (sum < max)
//    {
//        printf("%d", sum);
//    }
//    else
//    {
//        printf("overflow");
//    }
//    return 0;
//}
//
//int factorial(int n)
//{
//    int i, product = 1;
//    for (i = 1; i < n + 1; i++)
//    {
//        product *= i;
//    }
//    return product;
//}

