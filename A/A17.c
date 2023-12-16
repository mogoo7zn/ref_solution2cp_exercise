//
// Created by znwan on 2023/11/15.
//
//A17 分析一手5张牌的牌型，输出最好的牌型。牌有四种花色（Diamonds、Clubs、Hearts、Spades）和十三个等级（2、3、4、5、6、7、8、9、10、J、Q、K、A），
// A既可作为最大等级，也可作为最小等级。输入时，花色用首字母表示，等级用数字或字母表示（10用T表示）。若输入非法牌或重复牌则丢弃。若输入为0则结束程序。
//   牌型从大到小有：
//同花顺 straight flush（同花色且等级顺序相连）
//四张 four of a kind（4张牌等级相同）
//葫芦 full house（3张牌等级相同，另2张牌也等级相同）
//同花 flush（5张牌花色相同）
//顺子 straight（5张牌等级顺序相连）
//三张 three of a kind（3张牌等级相同）
//两对 two pairs（存在两个对子）
//对子 pair（2张牌等级相同）
//其他


#include <stdio.h>
#define MAX_LENGTH 1500
#define TypeLen 4
#define NumLen 13
//#define DIAMONDS D
//#define CLUBS C
//#define HEARTS H
//#define SPADES S

void clear(void);
int islegal(const char *cursor);
void sort_num(void);
int straight_flush();
int four_of_a_kind();
int full_house();
int flush();
int straight();
int three_of_a_kind();
int two_pairs();
int pair();
void swap(int *a, int *b);
void bubbleSort(int *value, int left, int right);

char buffer_all[MAX_LENGTH] = "DK HQ SJ DA ST 0";
char judge_type[TypeLen] = {'D', 'C', 'H', 'S'};
char judge_num[NumLen] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char type[5];
char num[5];
int int_num[5];
int main(void)
{
    char *cursor = buffer_all;
    int i;
    while(islegal(cursor) != -1){
        clear();
        i = 0;
        while(i < 5){
            if (islegal(cursor)){
                type[i] = *cursor;
                num[i] = *(cursor + 1);
                i++;
            }
            cursor += 3;
        }
        sort_num();
        if (straight_flush()){
            printf("straight flush\n");
        }else if(four_of_a_kind()){
            printf("four of a kind\n");
        }else if (full_house()) {
            printf("full house\n");
        }else if (flush()){
            printf("flush\n");
        }else if (straight()){
            printf("straight\n");
        }else if (three_of_a_kind()){
            printf("three of a kind\n");
        }else if (two_pairs()){
            printf("two pairs\n");
        }else if (pair()){
            printf("pair\n");
        }else
        printf("others\n");

    }

    return 0;
}

void clear(void)
{
    int i;
    for (i = 0; i < 5; i++){
        type[i] = '0';
        num[i] = '0';
    }
}
int islegal(const char *cursor)
{
    if (*cursor == '0'){
        return -1;
    }
    int i = 0, flag1 = 0, flag2 = 0;
    while(i < TypeLen){
        if (*cursor == judge_type[i]) {
            flag1 = 1;
            break;
        }
        i++;
    }
    i = 0;
    while(i < NumLen){
        if (*(cursor + 1) == judge_num[i]) {
            flag2 = 1;
            break;
        }
        i++;
    }
    i = 0;
    if (!(flag1 && flag2)){
        return 0;
    }
    while (i < 5){
        if (*cursor == type[i] && *(cursor + 1) == num[i])
            return 0;
        i++;
    }
    return 1;
}

int straight_flush()
{
    int i;
    for(i = 0; i < TypeLen - 1; i++){
        if(type[i] != type[i + 1]) return 0;
    }
    for(i = 0; i < 4; i++){
        if(int_num[i] == int_num[i + 1]) return 0;
    }
    if(int_num[4] == 14){
        int int_num_copy[5];
        int j;
        for (j = 0; j < 5; j++){
            int_num_copy[j] = int_num[j];
        }
        for (j = 4; j > 1; j--){
            int_num_copy[j] = int_num_copy[j - 1];
        }
        int_num_copy[0] = 1;j = 0;
        while (j < 4 && int_num_copy[j] + 1 == int_num_copy[j + 1]){
            j++;
        }
        if(j == 4)
            return 1;
    }else{
        for (i = 0; i < 4; i++){
            if(int_num[i] + 1 != int_num[i + 1])
                return 0;
        }
        return 1;
    }
    return 0;
}

int four_of_a_kind()
{
    if ((int_num[0] == int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    return 0;
}

int full_house()
{
    if ((int_num[0] == int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    if ((int_num[0] == int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    return 0;
}

int flush()
{
    int i;
    for (i = 0; i < 4; i++){
        if(type[i] != type[i + 1])
            return 0;
    }
    return 1;
}

int straight()
{
    int i;
    for(i = 0; i < 4; i++){
        if(int_num[i] == int_num[i + 1]) return 0;
    }
    if(int_num[4] == 14){
        int int_num_copy[5];
        int j;
        for (j = 0; j < 5; j++){
            int_num_copy[j] = int_num[j];
        }
        for (j = 4; j > 0; j--){
            int_num_copy[j] = int_num_copy[j - 1];
        }
        int_num_copy[0] = 1;j = 0;
        while (j < 4 && int_num_copy[j] + 1 == int_num_copy[j + 1]){
            j++;
        }
        if (j == 4) {
            return 1;
        }
    }
    for (i = 0; i < 4; i++){
        if(int_num[i] + 1 != int_num[i + 1])
            return 0;
    }
    return 1;
}

int three_of_a_kind()
{
    if ((int_num[0] == int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    return 0;
}


int two_pairs()
{
    if ((int_num[0] == int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] == int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    return 0;
}

int pair()
{
    if ((int_num[0] == int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] == int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] == int_num[3]) && (int_num[3] != int_num[4]))
        return 1;
    if ((int_num[0] != int_num[1]) && (int_num[1] != int_num[2]) && (int_num[2] != int_num[3]) && (int_num[3] == int_num[4]))
        return 1;
    return 0;
}

void sort_num(void)
{
    int i;
    for (i = 0; i < 5; ++i) {
        switch (num[i]) {
            case '2':
                int_num[i] = 2;
                break;
            case '3':
                int_num[i] = 3;
                break;
            case '4':
                int_num[i] = 4;
                break;
            case '5':
                int_num[i] = 5;
                break;
            case '6':
                int_num[i] = 6;
                break;
            case '7':
                int_num[i] = 7;
                break;
            case '8':
                int_num[i] = 8;
                break;
            case '9':
                int_num[i] = 9;
                break;
            case 'T':
                int_num[i] = 10;
                break;
            case 'J':
                int_num[i] = 11;
                break;
            case 'Q':
                int_num[i] = 12;
                break;
            case 'K':
                int_num[i] = 13;
                break;
            case 'A':
                int_num[i] = 14;
                break;
        }
    }
    bubbleSort(int_num, 0, 5);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *value, int left, int right)
{
    int i, j;
    for(i = left; i < right; i++)
    {
        for(j = left; j < right - 1; j++)
        {
            if(value[j] > value[j + 1])
                swap(value + j, value + j + 1);
        }
    }
}


//    int i, j;
//    for(i = 0, j = 0; i < LENGTH; i += 3, j++)
//    {
//        ch[j] = input_cards[i];
//    }
//    for(i = 1, j = 0; i < LENGTH; i += 3, j++)
//    {
//        number[j] = input_cards[i];
//    }

//store input card types
//        gets_s(input_cards, 15);
//        if (*input_cards == '0') {
//            return 1;
//        }else if (straight_flush(input_cards)) {
//            printf("straight flush\n");
//            continue;
//        }
//    }
//    printf("%s", input_cards);
//int i = 100;
//    gets(input_cards_all);
//    char *array_ptr = input_cards_all;
//    while(i--) {
//        char input_cards[LENGTH];
//        int cnt;
//        for(cnt = 0; cnt < LENGTH; cnt++){
//            input_cards[cnt] = *array_ptr;
//            array_ptr++;
//        }
//think: use a struct or two arrays to store the information?

//    typedef struct card{
//            char type;
//            int size;
//    }CARD;
//    CARD *hand;
//    hand = malloc(NUMBER * sizeof(CARD));