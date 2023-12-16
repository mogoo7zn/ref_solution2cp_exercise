/*
 * A18
 * 行程码压缩与解压。行程码（Run-Length Encoding）是一种统计编码，适用于经常出现连续符号的数据压缩，编码规则为：
 * （1）对2-8个连续出现的相同字符，用一个计数值和该字符来代替。例如aaa******dd表示为3a6*2d
 * （2）超过8个相同字符时，每次截取8个进行编码，例如??????????? (11个)表示为8?3?
 * （3）出现单独字符时，以计数值1开头，再列举连续的单独字符，在出现第一个连续相同字符之前以计数值1结尾，例如aaa!$$表示为3a1!12$，aaa!@#$$表示为3a1!@#12$
 * （4）输出编码结果时，计数值减1后以3位二进制数表示，字符以ASCII表示。
 * 例如3a6*2d表示为010 0110 0001 101 0010 1010 001 0110 0100，下划线表示计数值。
 * 最后按8位二进制字节输出，即输出01001100, 00110100, 10101000, 10110010, 0
 * 要求：
 * （1）实现文件压缩、解压缩功能。读入源文本文件，将压缩结果输出到二进制文件中；读入压缩文件，将解压结果输出到文本文件中。
 * （2）源文件名也应保存在压缩文件中，在解压缩时以源文件名恢复。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_PER_LINE 2048
#define MAX_REPEATED_TIMES 8
#define SINGLE_SEQUENCE 1
#define REPEATED_SEQUENCE 2

#define true (1 == 1)
#define false (!true)
typedef int bool;

// Read text file per line, encode and write to target file
int compress(void);

// Read compressed file per line, decode and write to file
int uncompress(void);

// Functions: encoding, bit operations, decoding
int encoding(char *, char *);
void output_bits(char *, unsigned char *);
int decoding(char *, char *);

char src_filename[] = "D:/A18-SRC.TXT";
char out_filename[] = "D:/A18-OUT.TXT";
char recover_filename[] = "D:/A18-REC.TXT\n";

int main() {

    compress();
    uncompress();

    return 0;
}

int compress(void) {
    char input_buff[MAX_CHARS_PER_LINE]; // "aaa******dd???????????aaa!$$aaa!@#$$"; // sample line for test
    char encode_buff[MAX_CHARS_PER_LINE]; // sample encode "3a6*2d8?3?3a1!12$3a1!@#12$"
    unsigned char output_buff[MAX_CHARS_PER_LINE]; // "010 0110 0001 101 0010 1010 001 0110 0100" for "3a6*2d"
    char *input_cursor;
    int i;

    // Open source file for reading
    FILE *fpSrc = fopen(src_filename, "r");

    // Open target file for writing
    FILE *fpOut = fopen(out_filename, "w");

    if (NULL == fpSrc || NULL == fpOut) {
        printf("Open source text or output file (D:/A18-SRC.TXT)failed.\n");
        exit(1);
    }

    // While loop: fgets read a line from source to input buffer until EOF
    strcpy(input_buff, recover_filename);
    do {
        bool ends_with_rtn = false;
        // Remove ending '\n'
        if ('\n' == input_buff[strlen(input_buff) - 1]) {
            input_buff[strlen(input_buff) - 1] = '\0';
            ends_with_rtn = true;
        }

        // Empty line
        if (strlen(input_buff) == 0) {
            fputs("\n", fpOut);
            continue;
        }

        // Print to screen for debug purpose
        printf("Input Text: %s\n", input_buff);

        // Clear encode_buff & output_buff
        memset(encode_buff, '\0', MAX_CHARS_PER_LINE);
        memset(output_buff, '\0', MAX_CHARS_PER_LINE);

        input_cursor = input_buff;
        while (input_cursor < input_buff + strlen(input_buff)) {
            input_cursor += encoding(input_cursor, encode_buff + strlen(encode_buff));
        }

        // Print to screen for debug purpose
        printf("Encode Text: %s\n", encode_buff);
        printf("Encode HEX: ");
        for (i = 0; i < strlen(encode_buff); i++) {
            char str[2 + 1];
            sprintf(str, "%.2x", encode_buff[i]);
            printf("%s ", str);
        }
        printf("\n");

        output_bits(encode_buff, output_buff);
        // Print to screen for debug purpose
        printf("Output Text: %s\n", output_buff);

        printf("Output HEX: ");
        for (i = 0; i < strlen(output_buff); i++) {
            char str[2 + 1];
            sprintf(str, "%.2x", output_buff[i]);
            printf("%s ", str);
        }
        printf("\n");

        printf("Output Binary: ");
        for (i = 0; i < strlen(output_buff); i++) {
            char str[8 + 1];
            int j;
            itoa(output_buff[i], str, 2);
            for (j = 0; j < 8 - strlen(str); j++) {
                printf("%c", '0');
            }
            printf("%s ", str);
            if ((i + 1) % 7 == 0) {
                printf("\n");
            }
        }
        printf("\n");

        // Write a line to target file
        fputs(output_buff, fpOut);
        if (true == ends_with_rtn) {
            fputs("\n", fpOut);
        }
    } while (fgets(input_buff, MAX_CHARS_PER_LINE, fpSrc) != NULL);

    fclose(fpSrc);
    fclose(fpOut);

    return 0;
}

int encoding(char *input, char *encode) {
    int i;
    int type = -1;
    int len = strlen(input);

    for (i = 0; i < len; i++) {
        if (*(input + i) == *(input + i + 1)) {
            if (0 == i) {
                type = REPEATED_SEQUENCE;
            }
            if (SINGLE_SEQUENCE == type) {
                *encode++ = 1;
                strncpy(encode, input, i);
                encode += i;
                *encode++ = 1;
                return i;
            }
            if (REPEATED_SEQUENCE == type && (MAX_REPEATED_TIMES - 2) == i) {
                *encode++ = MAX_REPEATED_TIMES;
                *encode++ = *input;
                return MAX_REPEATED_TIMES;
            }
        } else {
            if (0 == i) {
                type = SINGLE_SEQUENCE;
            }
            if (REPEATED_SEQUENCE == type) {
                *encode++ = i + 1;
                *encode++ = *input;
                return i + 1;
            }
        }
    }
    if (SINGLE_SEQUENCE == type) { // Single sequence until end of the line
        *encode++ = 1;
        strncpy(encode, input, i);
        encode += i;
        *encode++ = 1;
        return i;
    }
}

void output_bits(char *encode, unsigned char *output) {
    int i;
    int len = strlen(encode);

    unsigned char out_char = 0;
    int done_bits = 0;

    for (i = 0; i < len; i++) {
        int ch = encode[i]; // Why save char to int ?
        if (ch <= 8) { // Length
            ch--;
            if ((8 - done_bits) < 3) {
                int saved_ch = ch;
                ch >>= 3 - (8 - done_bits);
                out_char |= ch & 0XFF;
                *output++ = out_char;
                saved_ch <<= 8 - (3 - (8 - done_bits));
                out_char = saved_ch & 0XFF;
                done_bits = 3 - (8 - done_bits);
            } else if ((8 - done_bits) == 3) {
                out_char |= ch;
                *output++ = out_char;
                out_char = 0;
                done_bits = 0;
            } else {
                ch <<= 8 - done_bits - 3;
                out_char |= ch & 0XFF;
                done_bits += 3;
            }
        } else { // Characters
            if (0 == done_bits) {
                *output++ = ch;
                out_char = 0;
                done_bits = 0;
            } else {
                int saved_ch = ch;
                ch >>= done_bits;
                out_char |= ch & 0XFF;
                *output++ = out_char;
                saved_ch <<= 8 - done_bits;
                out_char = saved_ch & 0XFF;
            }
        }
    }
    if (done_bits != 0) {
        *output++ = out_char;
    }
}

int uncompress() {
    return 0;
}