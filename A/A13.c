//
// Created by znwan on 2023/11/11.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
//#define MAXLENGTH 100001

int min_max(char *character_set, int left, int right);
void swap(char *a, char *b);
void bubbleSort(char *value, int left, int right);
//void printArray(char *character_set);
int main(void)
{
    char *character_set = NULL;
    character_set = malloc(1000001);
//    record is the recorded summit of the array(character_set)
    int i, record, length ,position;
    scanf_s("%s", character_set);

    length = strlen(character_set);
    i = length;

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
    position = min_max(character_set, record, length - 1);

//    swap the summit element with min_max after it(if there is a min_max)
    swap(character_set + position, character_set + record - 1);

//    sort the array after
    bubbleSort(character_set, record, length);

    printf_s("%s", character_set);
//    printArray(character_set);

    free(character_set);
    return 0;
}

int min_max(char *character_set, int left, int right)
{
    int i, max, position = right, flag = 0;
    max = character_set[left];
    for(i = right; i > left; i--)
    {
        if(left > 0 && max > character_set[i] && character_set[i] > character_set[left - 1])
        {

            flag = 1;
            max = character_set[i];
            position = i;
        }
    }
    if(flag == 0)
    {
        position = left;
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
    for(i = left; i < right; i++)
    {
        for(j = left; j < right - 1; j++)
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