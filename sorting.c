#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

void printArr(long* arr, int size)
{
    printf("\n");
    for(int x = 0; x < size; x++)
    {
        printf("%ld, ", arr[x]);
    }
    printf("\n");
}

int partition(long* arr, int lb, int ub)
{

}

void quickSort(long* arr, int size)
{

}

void merge(long* src, long* dest, int lb, int mid, int ub)
{
    int ind1 = lb;
    int ind2 = mid + 1;
    int ind_dest = 0;
    long l_val;
    long u_val;
    if((ub <= lb) || (mid < lb) || (mid + 1 > ub))
    {
        return;
    }
    while(ind1 <= mid && ind2 <= ub)
    {
        l_val = src[ind1];
        u_val = src[ind2];
        (l_val < u_val) ? (dest[ind_dest] = l_val) : (dest[ind_dest] = u_val);
        ind_dest++;
        ind1 += l_val <= u_val;
        ind2 += u_val < l_val;
    }
    if(ind1 == mid + 1)
    {
        for(int x = ind2; x <= ub; x++)
        {
            dest[ind_dest] = src[x];
            ind_dest++;
        }
    }
    else
    {
        for(int x = ind1; x <= mid + 1; x++)
        {
            dest[ind_dest] = src[x];
            ind_dest++;
        }
    }
}

void mergeSort(long* src, int size)
{
    long * dest = malloc(sizeof(long) * size);
    if(size == 1)
    {
        free(dest);
        return;
    }
    mergeSort(src, size / 2);
    mergeSort(src + size / 2, size - size / 2);

    
    merge(src, dest, 0, size / 2 - 1, size - 1);
    for(int x = 0; x < size; x++)
    {
        src[x] = dest[x];
    }
    free(dest);
}
