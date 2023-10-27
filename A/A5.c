#include <stdio.h>

int main() {
    int n, i;
    scanf("%d", &n);
    /*create upper layers*/
    for (i = 1; i < n + 1; i++)
    {
        int num = 0, j = 0;
        while(j < n - i)
        {
            printf(" ");
            j++;
        }
        for (; num < i; num++)
        {
            if(num - i)
            {
                printf("%d ", i);
            }else
            {
                printf("%d", i);
            }
        }
        printf("\n");
    }
    /*create lower layers*/
    for (i = 1; i < n; i++)
    {
        int num = 0, j = 0;
        while(j < i)
        {
            printf(" ");
            j++;
        }
        for (; num < n - i; num++)
        {
            if (num - n + i)
            {
                printf("%d ", n - i);
            }else
            {
                printf("%d", n - i);
            }
        }
        printf("\n");
    }
    return 0;
}
