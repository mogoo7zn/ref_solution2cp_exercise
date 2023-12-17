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

//#define DEBUG

#define MAX_CHARS_PER_LINE 2048
#define MAX_REPEATED_TIMES 8
#define SINGLE_SEQUENCE 1
#define REPEATED_SEQUENCE 2

#define DECODING_LENGTH 1
#define DECODING_CHARS 2

#define true (1 == 1)
#define false (!true)
typedef int bool;

// Read text file per line, encode and write to target file
int compress(char *, char *);

// Read compressed file per line, decode and write to file
int uncompress(char *);

// Functions: encoding, bit operations, decoding
int encoding(char *, char *);
void output_bits(char *, unsigned char *);
int decoding(unsigned char *, char *);

void print_string_binary(unsigned char *);
void print_usage(void);


int main(int argc, char **argv) {
    char src_filename[] = "D:/A18-SRC.TXT";
    char out_filename[] = "D:/A18-OUT.BIN";

    print_usage();

    switch (argc) {
        case 1:
            compress(src_filename, out_filename);
            uncompress(out_filename);
            break;

        case 3:
            uncompress(argv[1]);
            break;

        case 4:
            compress(argv[1], argv[2]);
            break;

        default:
            print_usage();
            break;
    }

    return 0;
}

int compress(char *src_filename, char *out_filename) {
    char input_buff[MAX_CHARS_PER_LINE];
    char encode_buff[MAX_CHARS_PER_LINE];
    unsigned char output_buff[MAX_CHARS_PER_LINE];
    char *input_cursor;
    int i;

    // Open source file for reading
    FILE *fp_src = fopen(src_filename, "r");
    if (NULL == fp_src) {
        printf("Fail to open source text file %s.\n", src_filename);
        exit(1);
    }

    // Open target file for writing
    FILE *fp_out = fopen(out_filename, "wb");
    if (NULL == fp_out) {
        printf("Fail to open binary output file %s.\n", out_filename);
        exit(1);
    }

    // While loop: fgets read a line from source to input buffer until EOF
    strcpy(input_buff, src_filename);
    strcat(input_buff, ".REC\n");

    // Write line break as '\0' instead as '\n' occurs in compressed output
    do {
        bool ends_with_rtn = false;
        // Remove ending '\n'
        if ('\n' == input_buff[strlen(input_buff) - 1]) {
            input_buff[strlen(input_buff) - 1] = '\0';
            ends_with_rtn = true;
        }

        // Empty line
        if (strlen(input_buff) == 0) {
            if (ends_with_rtn = true) {
                fwrite("\0", sizeof(unsigned char), 1, fp_out);
            }
            continue;
        }
#ifdef DEBUG
        // Print to screen for debug purpose
        printf("Input Text: %s\n", input_buff);
#endif
        // Clear encode_buff & output_buff
        memset(encode_buff, '\0', MAX_CHARS_PER_LINE);
        memset(output_buff, '\0', MAX_CHARS_PER_LINE);

        input_cursor = input_buff;
        while (input_cursor < input_buff + strlen(input_buff)) {
            input_cursor += encoding(input_cursor, encode_buff + strlen(encode_buff));
        }
        output_bits(encode_buff, output_buff);

#ifdef DEBUG
        // Print to screen for debug purpose
        printf("Encode HEX: ");
        for (i = 0; i < strlen(encode_buff); i++) {
            printf("%.2x ", encode_buff[i]);
        }
        printf("\n");

        printf("Output HEX: ");
        for (i = 0; i < strlen(output_buff); i++) {
            printf("%.2x ", output_buff[i]);
        }
        printf("\n");

        printf("Output Binary: ");
        print_string_binary(output_buff);
#endif
        // Write a line to target file
        fwrite(output_buff, sizeof(unsigned char), strlen(output_buff), fp_out);
        if (true == ends_with_rtn) {
            fwrite("\0", sizeof(unsigned char), 1, fp_out);
        }
    } while (fgets(input_buff, MAX_CHARS_PER_LINE, fp_src) != NULL);

    fclose(fp_src);
    fclose(fp_out);

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

int uncompress(char *out_filename) {
    unsigned char output_buff[MAX_CHARS_PER_LINE] = {0};
    char decode_buff[MAX_CHARS_PER_LINE] = {0};

    FILE *fp_out = fopen(out_filename, "rb");
    if (NULL == fp_out) {
        printf("Open compressed file %s failed.\n", out_filename);
        exit(1);
    }

    FILE *fp_rec = NULL;
    long outfile_offset = 0;
    while (true) {
        bool ends_with_rtn = false;
        bool is_eof = false;

        int i = 0;
        while (true) {
            int ch = fgetc(fp_out);
            if (0 == ch) {
                ends_with_rtn = true;
                break;
            }
            if (EOF == ch) {
                is_eof = true;
                break;
            }
            output_buff[i++] = ch;
        }

        // Empty line
        if (strlen(output_buff) == 0) {
            if (true == ends_with_rtn) {
                fputs("\n", fp_rec);
            }
            if (true == is_eof) {
                break;
            }
            memset(output_buff, '\0', MAX_CHARS_PER_LINE);
            continue;
        }

        decoding(output_buff, decode_buff);
        if (NULL == fp_rec) {
#ifdef DEBUG
            printf ("Got recovery file name %s\n", decode_buff);
#endif
            fp_rec = fopen(decode_buff, "w");
            if (NULL == fp_rec) {
                printf ("Fail to open recovery file %s\n", decode_buff);
                fclose(fp_out);
                exit(1);
            }
            memset(output_buff, '\0', MAX_CHARS_PER_LINE);
            memset(decode_buff, '\0', MAX_CHARS_PER_LINE);
            continue;
        }
        fputs(decode_buff, fp_rec);
        fputs("\n", fp_rec);
        memset(output_buff, '\0', MAX_CHARS_PER_LINE);
        memset(decode_buff, '\0', MAX_CHARS_PER_LINE);

        if (true == is_eof) {
            break;
        }
    }

    fclose(fp_out);
    if (fp_rec != NULL) {
        fclose(fp_rec);
    }

    return 0;
}

int decoding(unsigned char *output, char *decode) {
    unsigned char rec_char = 0;
    int rec_done_bits = 0;
    int out_done_bits = 0;
    int repeated_times = 0;
    int action = DECODING_LENGTH;
    int len = strlen(output);
    unsigned char *cursor = output;
    int i;

    while (cursor < (output + len)) {
        int ch = *cursor;
        if (DECODING_LENGTH == action) {
            if ((8 - out_done_bits) >= (3 - rec_done_bits)) {
                ch = (ch << out_done_bits) & 0XFF;
                ch >>= out_done_bits;
                ch >>= 8 - out_done_bits - (3 - rec_done_bits);
                ch = rec_char | (ch & 0XFF);
                ch++;

                if (1 == repeated_times) {
                    if (1 == ch) { // End of single sequence
                        repeated_times = 0;
                        out_done_bits += 3 - rec_done_bits;
                        rec_char = 0;
                        rec_done_bits = 0;
                    } else {
                        action = DECODING_CHARS;
                    }
                    continue;
                }

                repeated_times = ch;
                action = DECODING_CHARS;

                if ((8 - out_done_bits) == (3 - rec_done_bits)) {
                    cursor++;
                }

                out_done_bits += 3 - rec_done_bits;
                out_done_bits %= 8;
                rec_char = 0;
                rec_done_bits = 0;
            } else { //(8 - out_done_bits) < (3 - rec_done_bits)
                ch = (ch << out_done_bits) & 0XFF;
                ch >>= out_done_bits;
                ch <<= (3 - rec_done_bits) - (8 - out_done_bits);
                rec_char |= ch & 0XFF;
                rec_done_bits += 8 - out_done_bits;
                out_done_bits = 0;
                cursor++;
            }
        } else if (DECODING_CHARS == action) {
            if ((8 - out_done_bits) >= (8 - rec_done_bits)) {
                ch = (ch << out_done_bits) & 0XFF;
                ch >>= out_done_bits + rec_done_bits;
                rec_char |= ch & 0XFF;

                for (i = 0; i < repeated_times; i++) {
                    *decode++ = rec_char;
                }

                action = DECODING_LENGTH;
                if ((8 - out_done_bits) == (8 - rec_done_bits)) {
                    cursor++;
                }

                out_done_bits += 8 - rec_done_bits;
                out_done_bits %= 8;
                rec_char = 0;
                rec_done_bits = 0;
            } else { //(8 - out_done_bits) < (8 - rec_done_bits)
                ch = (ch << out_done_bits) & 0XFF;
                ch >>= out_done_bits;
                ch <<= (8 - rec_done_bits) - (8 - out_done_bits);
                rec_char |= ch & 0XFF;
                rec_done_bits += 8 - out_done_bits;
                out_done_bits = 0;
                cursor++;
            }
        }
    }

    // The remaining bits are zeros and lost in '\0 as line break
    if (repeated_times > 1 && rec_done_bits > 0 && rec_char != 0) {
        for (i = 0; i < repeated_times; i++) {
            *decode++ = rec_char;
        }
    }
    return 0;
}

void print_string_binary(unsigned char * buff) {
    int i, j;
    for (i = 0; i < strlen(buff); i++) {
        char str[8 + 1];
        itoa(buff[i], str, 2);
        for (j = 0; j < 8 - strlen(str); j++) {
            printf("%c", '0');
        }
        printf("%s ", str);
        if ((i + 1) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void print_usage() {
    printf("Usage:\n"
           "1. No parameters\n"
           "A18.exe\n"
           "2. Two parameters, source text filename & compressed filename\n"
           "A18.exe a.txt b.bin\n"
           "3. One parameter, compressed filename\n"
           "A18.exe b.bin\n");
}