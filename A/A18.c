//
// Created by znwan on 2023/12/6.
//
#include <stdio.h>

char *output_buff;
int main(void)
{
    FILE *fp = NULL;
    fp = fopen("D:/tmp/_test.txt", "w");
    fputs("wssaiefefefefefe     aaaaaaaaaaaa?????\n", fp);
    fseek(fp, 0, SEEK_END);
    fclose(fp);

    fp = fopen("D:/tmp/_test.txt", "r");


}