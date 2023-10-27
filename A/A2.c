#include <stdio.h>

int main() {
    int year;
    scanf("%d", &year);
    if (year >= 1800 && year <= 2200)
    {
        //optimization
        char ans = (!(year % 4) && year % 100) || !(year % 400) ? 'Y': 'N';
        printf("%c", ans);

       /* if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        {
            printf("Y");
        }
        else
        {
            printf("N");
        }*/
    }else
    {
        printf("input error");
    }
    return 0;
}
