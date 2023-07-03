//preprocessor directives
#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

//helper function declarations
void swap(long * arr, int i, int j);

/* swaps two elements in array arr*/
void swap(long * arr, int i, int j)
{
    long temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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

/*  partition usgin Hoare's partition scheme
    
    inputs: long * arr, int lb int ub
    
    arr: array to be partitioned
    lb: lower bound of array
    ub: upper bound of array
    
    instance variables: long pivot_el, int i, int j, int n
    
    pivot_el: stores last element chosen as pivot element
    i: index of left most element greater than or equal to pivot_el
    j: index of right most element less than or equal to pivot_el
    n: loop control variable
    
    functionality:
    
    loop until the indices of i and j meet
    loop i from last i to next index greater than or equal to pivot el
    loop j from last j to next index less than or equal to pivot el
    check if i and j met
    swap i and j
    results in all elements less than pivot_el on the left of pivot_el, and all elements greater than pivot_el on the right of pivot_el
*/
int partition(long* arr, int lb, int ub)
{
    long pivot_el = arr[lb];
    int i = lb - 1;
    int j = ub + 1;
    int n = 0;
    while(n == 0)
    {
        do
        {
            i += 1;
        }while(arr[i] < pivot_el);

        do
        {
            j -= 1;
        }while(arr[j] > pivot_el);

        if(i >= j)
        {
            printf("\npivot_idx: %d", j);
            printArr(arr, ub + 1);
            return j;  
        }
        swap(arr, i, j);
    }
    
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
    int pivot_idx;

    while(size > 1)
    {    
        pivot_idx = partition(arr, 0, size - 1);
        quickSort(arr + pivot_idx + 1, size - pivot_idx - 1);
        size = pivot_idx + 1;
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
    while(ind1 <= mid)
    {
        dest[ind_dest] = src[ind1];
        ind_dest++;
        ind1++;
    }
    while(ind2 <= ub)
    {
        dest[ind_dest] = src[ind2];
        ind_dest++;
        ind2++;
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
    for(int x = 0; x < size; x++)
    {
        src[x] = dest[x];
    }
    free(dest);
}
