#ifndef quick_sort_h_
#define quick_sort_h_

/* quick sort (recursive version) ------------------------------------------*/
void QuickSort_qSort(int *arr, int left, int right);
/* quick sort (recursive version) ------------------------------------------*/

/* quick sort (non-recursive version, with explicit stack) -----------------*/
void QuickSort_qSort_iterative(int *arr, int left, int right);
/* quick sort (non-recursive version, with explicit stack) -----------------*/

/* quick sort test ---------------------------------------------------------*/
void QuickSort_testHandler(void);
/* quick sort test ---------------------------------------------------------*/

#endif /* quick_sort_h_ */
