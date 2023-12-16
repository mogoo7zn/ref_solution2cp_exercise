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

#define DEBUG

#define MAX_CHARS_PER_LINE 20480
#define MAX_REPEATED_TIMES 8
#define BITS_PER_CHAR 8
#define BITS_PER_REPEATED 3

#define UNKNOWN_SEQUENCE 0
#define SINGLE_SEQUENCE 1
#define REPEATED_SEQUENCE 2

#define MAX_BLOCK_SIZE 2048

#define DECODING_UNKNOWN 0
#define DECODING_LENGTH 1
#define DECODING_CHARS 2

#define true (1 == 1)
#define false (!true)
typedef int bool;

// Read text file per line, encode and write to target file
int compress(void);

// Read compressed file per line, decode and write to file
int uncompress(void);

// Functions: encoding, bit operations, decoding
int encoding(char *, char *, bool);

int output_bits(char *, unsigned char *, bool);

int decoding(unsigned char *, char *, int);

char src_filename[] = "D:/A18-SRC.TXT";
char out_filename[] = "D:/A18-OUT.BIN";
char recover_filename[] = "D:/A18-REC.TXT";

int main() {

    compress();
    uncompress();

    return 0;
}

int uncompress() {
    unsigned char block_buff[MAX_BLOCK_SIZE] = {0};
    char decode_buff[MAX_CHARS_PER_LINE] = {0};
    char *decode_cursor = decode_buff;

    FILE *fp_bin = fopen(out_filename, "rb");
    if (NULL == fp_bin) {
        printf("Open compressed file (D:/A18-OUT.BIN)failed.\n");
        exit(1);
    }

    FILE *fp_rec = NULL;
    while (true) {
        int block_len = fread(block_buff, sizeof(unsigned char), MAX_BLOCK_SIZE, fp_bin);
        if (0 == block_len) {
            break;
        }
        int done_bin_chars = decoding(block_buff, decode_cursor, block_len);
        if (done_bin_chars != -1) {
            if (NULL == fp_rec) {
                char *rtn = strchr(decode_buff, '\n');
                if (NULL == rtn) {
                    decode_cursor += done_bin_chars;
                } else {
                    *rtn++ = '\0';
#ifdef DEBUG
                    printf ("Got recovery file name %\n", decode_buff);
#endif
                    fp_rec = fopen(decode_buff, "w");
                    if (NULL == fp_rec) {
                        printf ("Fail to open recovery file %\n", decode_buff);
                        fclose(fp_bin);
                        exit(1);
                    }
                    fputs(rtn, fp_rec);
                    decode_cursor = decode_buff;
                }
            } else {
                fputs(decode_buff, fp_rec);
                decode_cursor = decode_buff;
            }
        }
    }

    fclose(fp_bin);
    if (fp_rec != NULL) {
        fclose(fp_rec);
    }

    return 0;
}

int decoding(unsigned char *block, char *decode, int block_len) {
    static unsigned char rec_char = 0;
    static int done_bits = 0;
    static int repeated_times = 0;
    static int action = DECODING_LENGTH;
    int i;

    for (i = 0; i < block_len; i++) {
        int ch = block[i];
        if (DECODING_LENGTH == action) {
            if (0 == done_bits) {
                repeated_times = ch >> (BITS_PER_CHAR - BITS_PER_REPEATED);
                repeated_times++;
                rec_char = (ch << BITS_PER_REPEATED) & 0XFF;
                action = DECODING_CHARS;
                done_bits = BITS_PER_CHAR - BITS_PER_REPEATED;
            } else if (done_bits < 3) {
                repeated_times = rec_char | (ch >> (BITS_PER_CHAR - (BITS_PER_REPEATED - done_bits)));
                repeated_times++;
                rec_char = (ch << (BITS_PER_REPEATED - done_bits)) & 0XFF;
                done_bits = BITS_PER_CHAR - (BITS_PER_REPEATED - done_bits);
            } else {
                printf ("Unexpected error! done_bits = %d\n", done_bits);
            }
        } else if (DECODING_CHARS == action) {

        }

    }

    return bin_chars_cnt;
}

int compress(void) {
    char input_buff[MAX_CHARS_PER_LINE] = {0};
    char encode_buff[MAX_CHARS_PER_LINE] = {0};
    unsigned char output_buff[MAX_CHARS_PER_LINE] = {0};
    char tmp_buff[MAX_CHARS_PER_LINE];
    char *input_cursor = input_buff;
    bool is_eof = false;

    // Open source text file for reading
    FILE *fp_src = fopen(src_filename, "r");
    if (NULL == fp_src) {
        printf("Fail to open source text file (D:/A18-SRC.TXT)\n");
        exit(1);
    }
    // Open target binary file for writing
    FILE *fp_out = fopen(out_filename, "wb");
    if (NULL == fp_out) {
        printf("Fail to open output binary file (D:/A18-OUT.BIN)\n");
        fclose(fp_src);
        exit(1);
    }

    // While loop: fgets read a line from source to input buffer until EOF
    strcpy(input_buff, recover_filename);
    strcat(input_buff, "\n");

    do {
        // Print to screen for debug purpose
        printf("Input Text: %s\n", input_buff);

        int i;
        int done_input_chars;
        while (input_cursor < input_buff + strlen(input_buff)) {
            done_input_chars = encoding(input_cursor, encode_buff + strlen(encode_buff), is_eof);
            if (-1 == done_input_chars) {
                break;
            }
            input_cursor += done_input_chars;
        }

#ifdef DEBUG
        // Print to screen for debug purpose
        printf("Encode HEX: ");
        for (i = 0; i < strlen(encode_buff); i++) {
            printf("%.2x ", encode_buff[i]);
        }
        printf("\n");
#endif

        int out_chars_cnt;
        out_chars_cnt = output_bits(encode_buff, output_buff, is_eof);
        memset(encode_buff, '\0', MAX_CHARS_PER_LINE);

#ifdef DEBUG
        // Print to screen for debug purpose
        printf("Output HEX: ");
        for (i = 0; i < out_chars_cnt; i++) {
            printf("%.2x ", output_buff[i]);
        }
        printf("\n");
#endif

        // Write to target file
        fwrite(output_buff, sizeof(unsigned char), out_chars_cnt, fp_out);
        memset(output_buff, '\0', MAX_CHARS_PER_LINE);

        // Read a new line
        if (true == is_eof) {
            break;
        } else {
            strcpy(tmp_buff, input_cursor);
            strcpy(input_buff, tmp_buff);
            input_cursor = input_buff;
            if (fgets(tmp_buff, MAX_CHARS_PER_LINE, fp_src) == NULL) {
                is_eof = true;
            } else {
                strcat(input_buff, tmp_buff);
            }
        }
    } while (true);

    fclose(fp_src);
    fclose(fp_out);

    return 0;
}

int encoding(char *input, char *encode, bool is_eof) {
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
            if ((REPEATED_SEQUENCE == type && *(input + i + 1) != '\0') ||
                (REPEATED_SEQUENCE == type && *(input + i + 1) == '\0' && true == is_eof)) {
                *encode++ = i + 1;
                *encode++ = *input;
                return i + 1;
            }
        }
    }
    if (SINGLE_SEQUENCE == type && true == is_eof) {
        *encode++ = 1;
        strncpy(encode, input, i);
        encode += i;
        *encode++ = 1;
        return i;
    } else {
        return -1;
    }
}

int output_bits(char *encode, unsigned char *output, bool is_eof) {
    int i;
    int len = strlen(encode);
    int out_chars_cnt = 0;
    static unsigned char out_char = 0;
    static int done_bits = 0;

    for (i = 0; i < len; i++) {
        int ch = encode[i];
        if (ch <= MAX_REPEATED_TIMES) {
            ch--;
            if ((BITS_PER_CHAR - done_bits) < BITS_PER_REPEATED) {
                int saved_ch = ch;
                ch >>= BITS_PER_REPEATED - (BITS_PER_CHAR - done_bits);
                out_char |= ch & 0XFF;
                *output++ = out_char & 0XFF;
                out_chars_cnt++;
                saved_ch <<= BITS_PER_CHAR - (BITS_PER_REPEATED - (BITS_PER_CHAR - done_bits));
                out_char = saved_ch & 0XFF;
                done_bits = BITS_PER_REPEATED - (BITS_PER_CHAR - done_bits);
            } else if ((BITS_PER_CHAR - done_bits) == BITS_PER_REPEATED) {
                out_char |= ch;
                *output++ = out_char;
                out_chars_cnt++;
                out_char = 0;
                done_bits = 0;
            } else {
                ch <<= BITS_PER_CHAR - done_bits - BITS_PER_REPEATED;
                out_char |= ch & 0XFF;
                done_bits += BITS_PER_REPEATED;
            }
        } else { // Characters
            if (0 == done_bits) {
                *output++ = ch;
                out_chars_cnt++;
                out_char = 0;
                done_bits = 0;
            } else {
                int saved_ch = ch;
                ch >>= done_bits;
                out_char |= ch & 0XFF;
                *output++ = out_char;
                out_chars_cnt++;
                saved_ch <<= BITS_PER_CHAR - done_bits;
                out_char = saved_ch & 0XFF;
            }
        }
    }

    if (done_bits != 0 && true == is_eof) {
        *output++ = out_char;
        out_chars_cnt++;
    }

    return out_chars_cnt;
}
