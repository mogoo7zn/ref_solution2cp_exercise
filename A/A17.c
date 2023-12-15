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
//三张 three of a kind（ 3张牌等级相同）
//两对 two pairs（存在两个对子）
//对子 pair（2张牌等级相同）
//其他


#include <stdio.h>
#include <stdlib.h>
#define NUMBER 5
#define T 10
#define LENGTH 15
#define MAX_LENGTH 1500
#define TypeLen 4
#define NumLen 10
//#define DIAMONDS D
//#define CLUBS C
//#define HEARTS H
//#define SPADES S

int islegal(char *cursor);
int straight_flush(char *input_cards);
int four_of_a_kind(char *input_cards);
int full_house(char *input_cards);
int flush(char *input_cards);
int straight(char *input_cards);
int three_of_a_kind(char *input_cards);
int two_pairs(char *input_cards);
int pair(char *input_cards);
void bubbleSort(char *value, int left, int right);
void swap(char *a, char *b);


char buffer_all[MAX_LENGTH] = "D2 24 HA SJ CK SJ 0";
char judge_type[4] = {'D', 'C', 'H', 'S'};
char judge_num[10] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T'};
char type[5];
char num[5];
int main(void)
{
    char *cursor = buffer_all, *current = buffer_all;
    int i = 0;
    while(islegal(cursor) != -1){
        while(1){
            if (i == 4)
                break;
            if (islegal(cursor)){
                type[i] = *cursor;
                num[i] = *(cursor + 1);
                i++;
            }
            cursor += 3;
        }
    }

    return 0;
}

int islegal(char *cursor)
{
    if (*cursor == '0'){
        return -1;
    }
    int i = 0, flag1 = 0, flag2 = 0;
    while(i < TypeLen){
        i++;
        if (*cursor == judge_type[i]) {
            flag1 = 1;
            break;
        }
    }
    i = 0;
    while(i < NumLen){
        i++;
        if (*(cursor + 1) == judge_num[i]) {
            flag2 = 1;
            break;
        }
    }
    i = 0;
    if (!(flag1 && flag2)){
        return 0;
    }
    while (i < 5){
        i++;
        if (*cursor == type[i] && *(cursor + 1) == num[i])
            return 0;
    }
    return 1;
}
//initialize input_cards in incremental sequence
void init_cards(char *input_cards, char *ch, char *number)
{
    int i, j;
    for(i = 0, j = 0; i < LENGTH; i += 3, j++)
    {
        ch[j] = input_cards[i];
    }
    for(i = 1, j = 0; i < LENGTH; i += 3, j++)
    {
        number[j] = input_cards[i];
    }
    bubbleSort(ch, 0, 4);
    bubbleSort(number, 0, 4);
}

int straight_flush(char *input_cards)
{
    int judge = 0, i, j;
    char ch[5], number[5];
    init_cards(input_cards, ch, number);

    for(i = 4; i > 0; i--){
        if(ch[i] > ch[i - 1]) return judge;
    }
    for(i = 4; i > 0; i--){
        if(number[i] != number[i - 1] + 1) return judge;
    }
    return judge = 1;
}

int four_of_a_kind(char *input_cards)
{
    int judge = 0;
    int i;
    for(i = 0; i < LENGTH - 3; i += 3){
        if(input_cards[i] != input_cards[i + 3]) return judge;
    }
    return judge = 1;
}

int full_house(char *input_cards)
{
    int judge = 0;

    return judge;
}

int flush(char *input_cards)
{
    int judge = 0;

    return judge;
}

int straight(char *input_cards)
{
    int judge = 0;

    return judge;
}

int three_of_a_kind(char *input_cards)
{
    int judge = 0;

    return judge;
}

int two_pairs(char *input_cards)
{
    int judge = 0;

    return judge;
}

int pair(char *input_cards)
{
    int judge = 0;

    return judge;
}

void swap(char *a, char *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(char *value, int left, int right)
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