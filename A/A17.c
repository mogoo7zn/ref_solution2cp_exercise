//
// Created by znwan on 2023/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#define NUMBER 5
#define T 10
#define LENGTH 15
#define MAX_LENGTH 1500
//#define DIAMONDS D
//#define CLUBS C
//#define HEARTS H
//#define SPADES S

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


char input_cards_all[MAX_LENGTH];
int main(void)
{
    int i = 100;
    gets(input_cards_all);
    char *array_ptr = input_cards_all;
    while(i--) {
        char input_cards[LENGTH];
        int cnt;
        for(cnt = 0; cnt < LENGTH; cnt++){
            input_cards[cnt] = *array_ptr;
            array_ptr++;
        }

        //store input card types
//        gets_s(input_cards, 15);
        if (*input_cards == '0') {
            return 1;
        }else if (straight_flush(input_cards)) {
            printf("straight flush\n");
            continue;
        }
    }
//    printf("%s", input_cards);
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

//think: use a struct or two arrays to store the information?

//    typedef struct card{
//            char type;
//            int size;
//    }CARD;
//    CARD *hand;
//    hand = malloc(NUMBER * sizeof(CARD));