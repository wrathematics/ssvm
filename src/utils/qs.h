#ifndef __SORTED_QUICKSORT_H__
#define __SORTED_QUICKSORT_H__


typedef len_t SortData_t;

static inline void __sorted_swap(SortData_t *const restrict a, SortData_t *const restrict b)
{
  SortData_t tmp = *a;
  *a = *b;
  *b = tmp;
}



/* References:
  * https://en.wikipedia.org/wiki/Quicksort
*/

static inline int __sorted_qs_partition(int low, int high, SortData_t *const x)
{
  int pivot;
  int i, j;
  
  pivot = x[low];
  
  i = low - 1;
  j = high + 1;
  
  while (1)
  {
    do i++; while (x[i] < pivot);
    
    do j--; while (x[j] > pivot);
    
    if (i >= j)
      return j;
    
    __sorted_swap(x+i, x+j);
  }
}

static inline void __sorted_qs_recursive(int low, int high, SortData_t *const x)
{
  int pivot;
  
  if (low < high)
  {
    pivot = __sorted_qs_partition(low, high, x);
    __sorted_qs_recursive(low, pivot, x);
    __sorted_qs_recursive(pivot+1, high, x);
  }
}

/* quick sort */
static inline void sorted_qs(int len, SortData_t *const x)
{
  if (len <= 1)
    return;
  
  __sorted_qs_recursive(0, len-1, x);
}


#endif
