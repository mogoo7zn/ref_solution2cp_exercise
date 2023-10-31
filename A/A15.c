#include <stdio.h>

void mergeSort(int *array, int l, int r, int opt);
void printArray(int *array, int size);
int main() {
    int n, opt;
    scanf("%d%d", &n, &opt);
    int arr[n];
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    mergeSort(arr, 0, n - 1, opt);
    printArray(arr, n);
    return 0;
}

void merge(int *array, int l, int m, int r, int opt)
{
    // First subarray is L(left)[l..m]
    // Second subarray is R(right)[m+1..r]
    int L[m - l + 1], R[r - m];
    int i = l, j = 0, k = l;

    for(; i < m + 1; i++)
    {
        L[j] = array[i];
        j++;
    }
    j = 0;
    for(; j < r - m; i++)
    {
        R[j] = array[i];
        j++;
    }

    if(!opt)
    {
        for(i = 0, j = 0; i < m - l + 1 && j < r - m;)
        {
            if(L[i] <= R[j])
            {
                array[k] = L[i];
                i++;
            }else
            {
                array[k] = R[j];
                j++;
            }
            k++;
        }
    }else
    {
        for(i = 0, j = 0; i < m - l + 1 && j < r - m;)
        {
            if(L[i] >= R[j])
            {
                array[k] = L[i];
                i++;
            }else
            {
                array[k] = R[j];
                j++;
            }
            k++;
        }
    }

    //deal with remain elements in either array
    while(i < m - l + 1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    while(j < r - m)
    {
        array[k] =  R[j];
        j++;
        k++;
    }
}

void mergeSort(int *array, int l, int r, int opt)
{
    /*recursion: repeatedly use l and r to halve the length of array
	and ultimately cut it size down to 2. After that, func recurses
	level by level, back to its original length*/
    int m;
    if(l < r)
    {
        m = (l + r -1) / 2;
        mergeSort(array, l, m, opt);
        mergeSort(array, m + 1, r, opt);
        merge(array, l, m, r, opt);
    }
    //int *array, int l, int m, int r, int opt
}


void printArray(int *array, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}