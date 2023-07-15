//preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

//helper function declarations
void swap(long * arr, int i, int j);
void copy(long * arr, long * dest, int lb, int ub);
void quickSort_notail(long * arr, int lb, int ub);

/* swaps two elements in array arr*/
void swap(long * arr, int i, int j)
{
    long temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*  copy elements from arr to dest*/
void copy(long * arr, long * dest, int lb, int ub)
{
    memcpy(dest, arr, sizeof(long) * (ub - lb + 1));

}

/*  array print function

    prints array of length = size
*/
void printArr(long* arr, int size)
{
    printf("\n");
    for(int x = 0; x < size; x++)
    {
        printf("%ld, ", arr[x]);
    }
    printf("\n");
}

/*  partition using Lomuto's partition scheme
    
    inputs: long * arr, int lb int ub
    
    arr: array to be partitioned
    lb: lower bound of array
    ub: upper bound of array
    
    instance variables: long pivot_el, int pivot_idx
    
    pivot_el: stores last element chosen as pivot element
    pivot_idx: variable to hold pivot index

    functionality:
    
    loop from lb to ub - 1
    check if element at index i is less than the pivot element
    if true, itterate the pivot index and swap the current element
    with the element at the new pivot index
    exit loop
    itterate pivot index once more
    and do one final swap
    result sin all elements less than pivot_el on the left of pivot_el, and vise versa
    return the pivot index
*/
int partition(long* arr, int lb, int ub)
{
    if(ub < lb)
        return -1;
    long pivot_el = arr[ub];
    int pivot_idx = lb - 1;
    for(int i = lb; i < ub; i++)
    {
        if(arr[i] <= pivot_el)
        {
            pivot_idx += 1;
            swap(arr, i, pivot_idx);
        }
    }
    pivot_idx += 1;
    swap(arr, ub, pivot_idx);
    return pivot_idx;
}

/*  quickSort

    inputs: long * arr, int size
    
    arr: array to be sorted
    size: size of arr
    
    instance variables: int pivot_idx
    
    pivot_idx: index in array to be used as pivot for qsort
    
    functionality: 
    
    recursively calls quickSort on the right sub array
    uses itterative approach to eliminate tail recursion when sorting left sub array
*/
void quickSort(long* arr, int size)
{
    quickSort_notail(arr, 0, size - 1);
}

/*  recursive quicksort function with 
    tail recursion eliminated
*/
void quickSort_notail(long * arr, int lb, int ub)
{
    int pivot_idx;
    while(lb < ub)
    {
        pivot_idx = partition(arr, lb, ub);
        
        if(pivot_idx < (lb + ub) / 2)
        {
            quickSort_notail(arr, lb, pivot_idx - 1);
            lb = pivot_idx + 1;
        }
        else
        {
            quickSort_notail(arr, pivot_idx + 1, ub);
            ub = pivot_idx - 1;
        }
    }
}

/*  merge
    
    inputs: long * src, long * dest, int lb, int mid, int ub
    
    src: source array
    dest: destination for sorted array
    lb: lower bound of src
    mid: middle index of src
    ub: upper bound of src
    
    instance variables: int ind1, int ind, int ind_dest, long l_val, long u_val
    
    ind1: current index of left sub array
    ind2: current index of right sub array
    ind_dest: current index of destination array
    l_val: value at current lower array index
    u_val: value at current upper array index

    functionality:

    initializes ind1 to lb, and ind 2 to mid + 1, splitting src into sub arrays of ~= size
    tests if upper bound is less than or equal to lower bound, if mid is less than lower bound, or if mid + 1 is greater than ub
    if any are true, return nothing, and keep input arrays as they were on function call
    while both ind1 and ind2 are in bounds for their respective sub arrays, place the lesser value of the two indices in dest, and 
    itterate the respective index by 1
    fill dest with the remaining elements in the left sub array, if any, using a while loop
    fill dest with the remaining elements in the right sub array, if any, using a while loop
*/
void merge(long* src, long* dest, int lb, int mid, int ub)
{
    int i = lb, j = mid + 1;
    for (int k = lb; k <= ub; k++)
    {
        if(i > mid)
            dest[k] = src[j++];
        else if(j > ub)
            dest[k] = src[i++];
        else if(src[j] < src[i])
            dest[k] = src[j++];
        else
            dest[k] = src[i++];
    }
}

/*  mergeSort
    
    inputs: long * src, int size
    
    src: source array to be sorted
    size: size of src
    
    instance variables: long * dest
    
    dest: array to hold sorted contents of src temporarily
    
    functionality:
    
    allocate sufficient memory for dest
    exit condition: size of src is 1
    call mergeSort for left sub array, and then right sub array recursively
    copy contents of dest into src
    */
void mergeSort(long* src, int size)
{
    long * dest = malloc(sizeof(long) * size);
    if(size <= 1)
    {
        free(dest);
        return;
    }
    mergeSort(src, size / 2);
    mergeSort(src + size / 2, size - size / 2);

    
    merge(src, dest, 0, size / 2 - 1, size - 1);
    copy(dest, src, 0, size - 1);
    free(dest);
}
