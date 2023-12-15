//
// Created by znwan on 2023/12/6.
//
//A18 行程码压缩与解压。行程码（Run-Length Encoding）是一种统计编码，适用于经常出现连续符号的数据压缩，编码规则为：
//（1）对2-8个连续出现的相同字符，用一个计数值和该字符来代替。例如aaa******dd表示为3a6*2d
//（2）超过8个相同字符时，每次截取8个进行编码，例如??????????? (11个)表示为8?3?
//（3）出现单独字符时，以计数值1开头，再列举连续的单独字符，在出现第一个连续相同字符之前以计数值1结尾，例如aaa!$$表示为3a1!12$，aaa!@#$$表示为3a1!@#12$
//（4）输出编码结果时，计数值减1后以3位二进制数表示，字符以ASCII表示。例如3a6*2d表示为010 0110 0001 101 0010 1010 001 0110 0100，下划线表示计数值。最后按8位二进制字节输出，即输出
//01001100, 00110100, 10101000, 10110010, 0
//要求：
//（1）实现文件压缩、解压缩功能。读入源文本文件，将压缩结果输出到二进制文件中；读入压缩文件，将解压结果输出到文本文件中。
//（2）源文件名也应保存在压缩文件中，在解压缩时以源文件名恢复。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 65536

char buffer[SIZE];
char output_buff[SIZE];
int position = 0;
//char *output_ptr = output_buff;
int main(void)
{
//    FILE *fp = NULL;
//    fp = fopen("D:/tmp/_test.txt", "w");
//    fputs("wssaiefefefefefe     aaaaaaaaaaaa?????\n", fp);
//    fseek(fp, 0, SEEK_END);
//    fclose(fp);
//
//    fp = fopen("D:/tmp/_test.txt", "r");

}

void code_split(char ch, int cnt)
{
    while (1){
        if (cnt %= 8){
            output_buff[position] = '8';
            output_buff[position + 1] = ch;
            position += 2;
        }else{
            output_buff[position] = (char )cnt;
            output_buff[position + 1] = ch;
            position += 2;
            break;
        }
    }
}

void code_one(int location, int cnt)
{
    if (cnt == 1)
        return;
    output_buff[position] = '1';
    memcpy(output_buff + position + 1, buffer + location, cnt);
    output_buff[position + cnt + 1] = '1';
    position += cnt + 2;
}

void coding_processor()
{
    int i;
    for (i = 0; i < SIZE - 1; ){
        int cnt_1 = 1, cnt_2 = 1;
        int copy_i = i;
        while (1) {
            if (buffer[i] != buffer[i + 1] && buffer[i + 1] != '\0') {
                cnt_1++;
                i++;
                continue;
            }
            code_one(copy_i, cnt_1);
            if (buffer[i] == buffer[i + 1] && buffer[i + 1] != '\0') {
                cnt_1 = 1;
                break;
            }
            cnt_1 = 1;
            break;
        }
        while (1){
            if (buffer[i] == buffer[i + 1] && buffer[i + 1] != '\0'){
                cnt_2++;
                i++;
                continue;
            }
            code_split(buffer[i], cnt_2);
            if (buffer[i] != buffer[i + 1] && buffer[i + 1] != '\0'){
                cnt_2 = 1;
                break;
            }
            cnt_2 = 1;
            break;
        }
    }
}
