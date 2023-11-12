//
// Created by znwang on 2023/11/5.
//

#include <stdio.h>
#define LENGTH 1024
#define MyLpha(c) (((c) >= 'a' && (c) <= 'z') ? 1 : (((c) >= 'A' && (c) <= 'Z') ? -1 : 0))

int main(void)
{
    char string[LENGTH];
    scanf("%s", string);
    int i;

    for(i = 0; string[i] != '\0'; i++)
    {
        if(!(MyLpha(string[i])))
            string[i] = ' ';
        else if(MyLpha(string[i]) == -1)
            string[i] += 32;
        else if(MyLpha(string[i]) == 1)
            string[i] -= 32;
    }

    for(i = 0; string[i] != '\0'; i++)
    {
        if(string[i] != ' ')
        printf("%c", string[i]);
    }

//    why getchar() is not applicable here?

//    int read;
//
//    while(read = getchar() != EOF)
//    {
//        if(!(MyLpha(read)))
//            continue;
//        else if(MyLpha(read) == -1)
//        {
//            read += 32;
//            printf("%d", read);
//        }
//        else if(MyLpha(read) == 1)
//        {
//            read -= 32;
//            printf("%d", read);
//        }
//    }

    return 0;
}