#include <stdio.h>
#define SORTS 6 

int main() {
    int a, b, c, d, e, f ,x;
    scanf("%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &x);
    int number[SORTS] = {a, b, c, d, e, f};
    int value[SORTS] = {100, 50, 20, 10, 5, 1};
    int cnt[SORTS];
    int i, j, tempx = x;

    //judge whether the input is legal
    for(i = 0; i < SORTS; i++)
    {
        tempx -= number[i] * value[i];
    }
    if(tempx > 0 || x <= 0)
    {
        return 1;
    }
    else
    {
        //initialize cnt
        for(i = 0; i < SORTS; i++)
        {
            cnt[i] = 0;
        }

        //excessive greedy algorithm
        for(i = 0; i < SORTS; i++)
        {
            j = number[i];
            while(j > 0 && x > 0)
            {
                if(x < value[i])
                    break;
                x -= value[i];
                j--;
                cnt[i]++;
            }
        }

        //repent and withdraw those smaller notes
        if(x == 0)
        {
            for(i = 0; i < SORTS; i++)
            {
                if(cnt[i] != 0)
                printf("%d:%d\n", value[i], cnt[i]);
            }
            return 0;
        }
        else
        {
            for(i = SORTS - 1; i > 0;i--)
            {
                x += cnt[i] * value[i];
                cnt[i] = 0;
                while(x - cnt[i - 1] > 0 && cnt[i - 1] < number[i - 1])
                {
                    cnt[i - 1]++;
                    x -= value[i - 1];
                }
                if(x - cnt[i - 1] < 0)
                    break;
            }
        }

        //print the result
        for(i = 0; i < SORTS; i++)
        {
            if(cnt[i] != 0)
            printf("%d:%d\n", value[i], cnt[i]);
        }

    }

    return 0;
}
