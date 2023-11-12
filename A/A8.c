//
// Created by znwang on 2023/11/7.
//

#include <stdio.h>
#include <math.h>

int main(void)
{
    long long int n;
    long long nums_in_list, N, temp_storage, init;
    scanf("%lld", &n);
    N = n * n * n;
    temp_storage = (long long) sqrt((double)N);
    printf("%lld^3=%lld=", n, N);

    for(nums_in_list = temp_storage; nums_in_list > 0; nums_in_list--)
    {
        init = N / nums_in_list - nums_in_list + 1;
        if(init > 0 && N % nums_in_list == 0 && (init % 2) == 1)
        {
            nums_in_list--;
            while(nums_in_list--)
            {
                printf("%lld+", init);
                init += 2;
            }
            printf("%lld", init);
            return 0;
        }
    }
}


//ed3

//#include <stdio.h>
//
//int main(void) {
//    //n is the input
//    int n;
//    long long N, number, init;
//    long long max_number;   //maximum number of odd numbers
//    scanf("%d", &n);
//
////    N is n^3
//    N = (long long)n * n * n;
//    max_number = n;
//
//    if(!(n > 1 && n < 2000))
//        return -1;
//    else {
//        //    deal with odd numbers
//        if (n % 2 == 1 && n != 1) {
////        an algorithm which represents: n ^ 3 / k - (k-1) >= 1
//            for (number = n; number <= (N + 1) / 2; number += n) {
//                if (N % number == 0 && N / number >= number) {
//                    max_number = number;
//                }
//            }
//            init = N / max_number - max_number + 1;
//            printf("%d^3=%lld=", n, N);
//        }
//
////    deal with even numbers
//        else if (n % 2 == 0) {
//            number = n;
//            for (; number <= N / number; number += n) {
//                if (N % number == 0 && ((N / number - number + 1) % 2)) {
//                    max_number = number;
//                }
//            }
//            init = N / max_number - max_number + 1;
//            printf("%d^3=%lld=", n, N);
//        } else {
//            return -1;
//        }
//
////    print result
//        while (max_number--) {
//            if (max_number > 0) {
//                printf("%lld+", init);
//                init += 2;
//            } else {
//                printf("%lld", init);
//                init += 2;
//            }
//        }
//        return 0;
//    }
//}








//ed2

//#pragma GCC optimize(3)
//#include <stdio.h>
//#include <math.h>
//
//int main(void) {
//    //n is the input
//    int n;
//    long long N, number, init;
//    long long max_number;   //maximum number of odd numbers
//    scanf("%d", &n);
//
////    N is n^3
//    N = (long long)pow(n, 3);
//    max_number = n;
////    deal with odd numbers
//    if(n % 2 == 1 && n != 1)
//    {
////        an algorithm which represents: n ^ 3 / k - (k-1) >= 1
//        for(number = n; number <= (N + 1) / 2; number += n)
//        {
//            if(N % number == 0 && N / number >= number)
//            {
//                max_number = number;
//            }
//        }
//        init = N / max_number - max_number + 1;
//        printf("%d^3=%lld=", n, N);
//        while(max_number--)
//        {
//            if(max_number > 0)
//            {
//                printf("%lld+", init);
//                init += 2;
//            }else
//            {
//                printf("%lld", init);
//                init += 2;
//            }
//        }
//    }
//
////    deal with even numbers
//    else if(n % 2 == 0)
//    {
//        number = n;
//        for (; number <= N / number; number += n)
//        {
//            if (N % number == 0 && ((N / number - number + 1) % 2))
//            {
//                max_number = number;
//            }
//        }
//        init = N / max_number - max_number + 1;
//        printf("%d^3=%lld=", n, N);
//        while(max_number--)
//        {
//            if(max_number > 0)
//            {
//                printf("%lld+", init);
//                init += 2;
//            }else
//            {
//                printf("%lld", init);
//                init += 2;
//            }
//        }
//    }
//
//    return 0;
//}
//













//ed1

//#pragma GCC optimize(2)
//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//
//int main(void) {
//    //n is the input
//    int test;
//    scanf("%d", &test);
//
//    int n;
//    long long N;
//    long long int number, max, init;
//    scanf("%d", &n);
//
//    clock_t start_t, end_t;
//    start_t = clock();
//    while(test--)
//    {
////    N is n^3
//        N = (long long)pow(n, 3);
//        max = n;
//
//        if(n == 1)
//        {
//            return -1;
//        }
////    deal with odd numbers
//        else if(n % 2 == 1)
//        {
////        an algorithm which represents: n ^ 3 / k - (k-1) >= 1
//            for(number = n; number <= (N + 1) / 2; number += n)
//            {
//                if(N % number == 0 && N / number >= number)
//                {
//                    max = number;
//                }
//            }
//            init = N / max - max + 1;
//            printf("%d^3=%lld=", n, N);
//            while(max--)
//            {
//                if(max > 0)
//                {
//                    printf("%lld+", init);
//                    init += 2;
//                }else
//                {
//                    printf("%lld", init);
//                    init += 2;
//                }
//            }
//        }
//
////    deal with even numbers
//        else if(n % 2 == 0) {
//            for (number = n; number <= N / 2; number += n) {
//                if (N % number == 0 && N / number >= number && N % number) {
//                    max = number;
//                }
//            }
//            init = N / max - max + 1;
//            printf("%d^3=%lld=", n, N);
//            while(max--)
//            {
//                if(max > 0)
//                {
//                    printf("%lld+", init);
//                    init += 2;
//                }else
//                {
//                    printf("%lld", init);
//                    init += 2;
//                }
//            }
//        }
//        end_t = clock();
//        printf("\ntime = %d", (end_t - start_t) / CLOCKS_PER_SEC);
//    }
//
//    return 0;
//}
//
