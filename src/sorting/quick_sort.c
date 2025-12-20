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

    /* get pivot -----------------------------------------------------------*/
    /* get the middle of arr[left], arr[mid], arr[right] -------------------*/
    // int mid = left + (right - left) / 2;
    // if (arr[left] <= arr[mid]) {
    //     if (arr[mid] <= arr[right]) {
    //         /* left <= mid <= right */
    //         QuickSort_swap(&arr[mid], &arr[right]);
    //     }
    //     else if (arr[left] <= arr[right]) {
    //         /* left <= right < mid */
    //         /* no position replacement */
    //     }
    //     else {
    //         /* right < left <= mid */
    //         QuickSort_swap(&arr[left], &arr[right]);
    //     }
    // }
    // else {
    //     if (arr[left] <= arr[right]) {
    //         /* mid < left <= right */
    //         QuickSort_swap(&arr[left], &arr[right]);
    //     } else if (arr[mid] <= arr[right]) {
    //         /* mid <= right < left */
    //         /* no position replacement */
    //     } else {
    //         /* right < mid < left */
    //         QuickSort_swap(&arr[mid], &arr[right]);
    //     }
    // }
    /* get the middle of arr[left], arr[mid], arr[right] -------------------*/
    pivot = arr[right];
    /* get pivot -----------------------------------------------------------*/

    /* partition -----------------------------------------------------------*/
    int pivIdx = left;  /* idx of element lower than pivot of partition */
    for (int opIdx = left; opIdx <= right - 1; opIdx++) {
        /* comparing with pivot, ascending */
        if (arr[opIdx] <= pivot) {
            /* put ascending element one by one */
            QuickSort_swap(&arr[pivIdx], &arr[opIdx]);
            ++pivIdx;  /* index moving to the border */
        }
    }
    /* partition -----------------------------------------------------------*/

    /* put pivot to the border of divided part */
    QuickSort_swap(&arr[pivIdx], &arr[right]);

    /* loc of divided partition: ... ... pivIdx(placed pivot) ...... */
    return (pivIdx);
}
/* partition ---------------------------------------------------------------*/

/* quick sort --------------------------------------------------------------*/
/* quick sort (recursive version) ------------------------------------------*/
void QuickSort_qSort(int *arr, int left, int right) {
    if (left < right) {  /* >= 2 elements */
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
    int stack[2 * (right - left + 1)];
    int top = -1;

    /* push initial range */
    stack[++top] = left;
    stack[++top] = right;
    while (top >= 0) {
        int partRight = stack[top--];
        int partLeft  = stack[top--];

        /* partition */
        int pivIdx = QuickSort_partition(arr, partLeft, partRight);

        /* If there are elements on left side of pivot, push left side */
        if (pivIdx - 1 > partLeft) {
            stack[++top] = partLeft;
            stack[++top] = pivIdx - 1;
        }

        /* If there are elements on right side of pivot, push right side */
        if (pivIdx + 1 < partRight) {
            stack[++top] = pivIdx + 1;
            stack[++top] = partRight;
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
    int arr[] = {4, 3, 1, 2};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("QuickSort test --------------------------------------------\r\n");
    printf("Unsorted %2d-element array:", n); printArray(arr, n);
    QuickSort_qSort(arr, 0, n-1);
    // QuickSort_qSort_iterative(arr, 0, n-1);
    printf("Sorted %4d-element array:", n);   printArray(arr, n);

    return;
}
/* quick sort test ---------------------------------------------------------*/
