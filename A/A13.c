//
// Created by znwan on 2023/11/11.
//

#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100001

int min_max(char *character_set, int left, int right);
void swap(char *a, char *b);
void bubbleSort(char *value, int left, int right);
void printArray(char *character_set);
int main(void)
{
    char character_set[MAXLENGTH];
//    record is the recorded summit of the array(character_set)
    int i, record, length ,position;
    scanf_s("%s", character_set);

//    how to find the length of my input?
//    for(i = 0; i < MAXLENGTH; i++)
//    {
//        if(character_set[i] == '\0')
//        {
//            length = i - 1;
//            break;
//        }
//    }

    length = strlen(character_set) - 1;

//    find the summit of character set, the summit is character_set[i]
    int flag = 0;
    while(--i)
    {
        if(character_set[i] > character_set[i - 1])
        {
            flag = 1;
            record = i;
            break;
        }
    }

//    judge whether the permutation is over
    if(flag == 0)
    {
        printf("over!");
        return 0;
    }

//    search for the minimum value's position of the numbers bigger than ..[i - 1]
    position = min_max(character_set, record, length);

//    swap the summit element with min_max after it(if there is a min_max)
    swap(character_set + position, character_set + record - 1);

//    sort the array after
    bubbleSort(character_set, record, length);
    printArray(character_set);

    return 0;
}

int min_max(char *character_set, int left, int right)
{
    int i, max, position = right;
    max = character_set[left];
    for(i = right; i > left; i--)
    {
        if(max > character_set[i] && character_set[i] > character_set[left - 1] && left > 0)
        {
            max = character_set[i];
            position = i;
        }
    }
    return position;
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
    for(i = left; i < (right - left); i++)
    {
        for(j = left; j < (right - left) - 1; j++)
        {
            if(value[j] > value[j + 1])
                swap(value + j, value + j + 1);
        }
    }
}

void printArray(char *character_set)
{
    int i;
    for(i = 0; character_set[i] != '\0'; i++)
    {
        printf_s("%c", character_set[i]);
    }
}