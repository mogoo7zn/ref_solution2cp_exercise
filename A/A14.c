#include <stdio.h>
#include <string.h>
#define TRUE (1 == 1)
#define FALSE !TRUE

int isPlalindrome(char *string);
int main() {
    char str[1000];
    int judge;
    scanf("%s",str);
    judge = isPlalindrome(str);
    if(judge == TRUE)
    {
        printf("yes");
    }else
    {
        printf("no");
    }
    return 0;
}

int isPlalindrome(char *string)
{
    char *ptr, *rev;
    rev = string;
    int len = strlen(string);

    /*ptr first runs to the end of the string, and it runs conversely against rev
     * if these two aren't the same at any position: fail*/
    ptr = &string[len-1];
    while(ptr >= rev)
    {
        if(*ptr == *rev)
        {
            ptr--;
            rev++;
        }else
        {
            break;
        }
    }
    if(*ptr == *rev)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }
}
