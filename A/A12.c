//
// Created by znwang on 2023/11/2.
//
#include <stdio.h>
#define MAXLENGTH 65536

int main()
{
//    initialize two containers
    char origin[MAXLENGTH] = {0};
    char compare[MAXLENGTH] = {0};
    int ch, i, lenOrigin = 0, lenCompare = 0;

//    input of letters, count the length of array input
    for(i = 0; i < MAXLENGTH; i++)
    {
        if((ch = getchar()) != ' ')
        {
            origin[i] = ch;
            lenOrigin += 1;
        }else
            break;
    }
    for(i = 0; i < MAXLENGTH; i++)
    {
        if((ch = getchar()) != EOF)
        {
            compare[i] = ch;
            lenCompare += 1;
        }else
            break;
    }

    int lenOrigin_copy2 = lenOrigin;

//    judge whether the comparison is reasonable
    if(lenOrigin > lenCompare)
    {
//    compare two strings from right hand side
        int cntOrigin, cntCompare, lenOrigin_copy = lenOrigin, flag = 0;
        for(; lenOrigin > 0 && lenCompare > 0; lenOrigin--)
        {
            if(flag == 1)
                break;
            cntOrigin = lenOrigin - 1, cntCompare = lenCompare - 1;
            for(i = 0; i < lenCompare; i++)
            {
                if(origin[cntOrigin] == compare[cntCompare] && cntOrigin >= 0 && cntCompare >= 0)
                {
                    cntCompare--,cntOrigin--;
                    flag = 1;
                }else
                {
                    flag = 0;
                    break;
                }
            }
        }

//    output the remaining string letters
        if(flag == 1)
        {
            for(i = 0; i < lenOrigin - lenCompare + 1; i++)
            {
                printf("%c", origin[i]);
            }
            for(i = lenOrigin + 1; i < lenOrigin_copy; i++)
            {
                printf("%c", origin[i]);
            }
        }
        else
        {
            for(i = 0; i < lenOrigin_copy2; i++)
            {
                printf("%c", origin[i]);
            }
        }
    }else
    {
        for(i = 0; i < lenOrigin_copy2; i++)
        {
            printf("%c", origin[i]);
        }
    }
    return 0;
}