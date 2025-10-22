/* dependencies ------------------------------------------------------------*/
#include <stdio.h>

#include "quick_sort.h"
/* dependencies ------------------------------------------------------------*/

/* quick sort swap ---------------------------------------------------------*/
static void QuickSort_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}
/* quick sort swap ---------------------------------------------------------*/

/* partition ---------------------------------------------------------------*/
static int QuickSort_partition(int *arr, int left, int right) {
    int pivot;  /* pivot of partition */

    /* get the middle of arr[left], arr[mid], arr[right] -------------------*/
    int mid = left + (right - left) / 2;
    if (arr[left] <= arr[mid]) {
        if (arr[mid] <= arr[right]) {
            /* left <= mid <= right */
            pivot = arr[mid];
            QuickSort_swap(&arr[mid], &arr[right]);
        }
        else if (arr[left] <= arr[right]) {
            /* left <= right < mid */
            pivot = arr[right];
            /* no position replacement */
        }
        else {
            /* right < left <= mid */
            pivot = arr[left];
            QuickSort_swap(&arr[left], &arr[right]);
        }
    }
    else {
        if (arr[left] <= arr[right]) {
            /* mid < left <= right */
            pivot = arr[left];
            QuickSort_swap(&arr[left], &arr[right]);
        } else if (arr[mid] <= arr[right]) {
            /* mid <= right < left */
            pivot = arr[right];
            /* no position replacement */
        } else {
            /* right < mid < left */
            pivot = arr[mid];
            QuickSort_swap(&arr[mid], &arr[right]);
        }
    }
    /* get the middle of arr[left], arr[mid], arr[right] -------------------*/

    int pivIdx = left;  /* idx of element lower than pivot of partition */

    for (int opIdx = left; opIdx <= right - 1; opIdx++) {
        /* comparing with pivot, ascending */
        if (arr[opIdx] <= pivot) {
            /* put ascending element one by one */
            QuickSort_swap(&arr[pivIdx], &arr[opIdx]);
            ++pivIdx;  /* index moving to the border */
        }
    }
    /* put pivot to the border of divided part */
    QuickSort_swap(&arr[pivIdx], &arr[right]);

    /* loc of divided partition: ... ... pivIdx(placed pivot) ...... */
    return (pivIdx);
}
/* partition ---------------------------------------------------------------*/

/* quick sort --------------------------------------------------------------*/
/* quick sort (recursive version) ------------------------------------------*/
void QuickSort_qSort(int *arr, int left, int right) {
    if (left < right) {
        /* base */
        int pivIdx = QuickSort_partition(arr, left, right);

        /* recursive left and right partition */
        QuickSort_qSort(arr, left, pivIdx-1);
        QuickSort_qSort(arr, pivIdx+1, right);
    }

    return;
}
/* quick sort (recursive version) ------------------------------------------*/

/* quick sort (iterative version, plain loop -------------------------------*/
void QuickSort_qSort_iterative(int *arr, int left, int right) {
    if (right - left < 1) {  /* only 1 element */
        return;
    }

    /* stack will hold pairs of indices: low, high */
    int stack[right - left + 1];
    int top = -1;

    /* push initial range */
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        int pivRight = stack[top--];
        int pivLeft  = stack[top--];

        /* partition */
        int pivIdx = QuickSort_partition(arr, pivLeft, pivRight);

        /* If there are elements on left side of pivot, push left side */
        if (pivIdx - 1 > pivLeft) {
            stack[++top] = pivLeft;
            stack[++top] = pivIdx - 1;
        }

        /* If there are elements on right side of pivot, push right side */
        if (pivIdx + 1 < pivRight) {
            stack[++top] = pivIdx + 1;
            stack[++top] = pivRight;
        }
    }

    return;
}
/* quick sort (iterative version, plain loop -------------------------------*/
/* quick sort --------------------------------------------------------------*/

/* quick sort test ---------------------------------------------------------*/
static void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\r\n");

    return;
}
void QuickSort_testHandler(void) {
    int arr[] = {9, 8, 5, 3, 2, 5, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Unsorted array:"); printArray(arr, n);
    // QuickSort_qSort(arr, 0, n-1);
    QuickSort_qSort_iterative(arr, 0, n-1);
    printf("Sorted array  :");   printArray(arr, n);

    return;
}
/* quick sort test ---------------------------------------------------------*/
