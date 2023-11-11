//
// Created by znwan on 2023/11/11.
//

#include <stdio.h>
#define MAXLENGTH 1000000

int min_max(char *character_set, int left, int right);
void swap(char *a, char *b);
void bubbleSort(char *value, int left, int right);
void printArray(char *character_set);
int main(void)
{
    char character_set[MAXLENGTH];
//    record is the recorded summit of the array(character_set)
    int i, record, copy_i ,position;
    scanf_s("%s", character_set);

//    how to find the length of my input?
    for(i = 0; i < MAXLENGTH; i++)
    {
        if(character_set[i] == '\0')
        {
            copy_i = i - 1;
            break;
        }
    }

    while(i--)
    {
        if(character_set[i] > character_set[i - 1])
        {
            record = i;
            break;
        }
    }
//    search for the minimum value's position of the numbers bigger than ..[i - 1]
    position = min_max(character_set, record, copy_i);
    swap(character_set + position, character_set + record - 1);

//    sort the array after
    bubbleSort(character_set, record, copy_i);
    printArray(character_set);

    return 0;
}

int min_max(char *character_set, int left, int right)
{
    int i = left, max, position;
    max = character_set[left];
    for(i = left; i < right; i++)
    {
        if(max > character_set[i] && character_set[i] > character_set[left - 1])
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