/* dependencies ------------------------------------------------------------*/
#include <stdio.h>

#include "insert_sort.h"
/* dependencies ------------------------------------------------------------*/

void InsertSort_insertSort(int arr[], int n) {
    int insElemIdx, insElem, sortedIdx;
    for (insElemIdx = 1; insElemIdx < n; ++insElemIdx) {
        insElem = arr[insElemIdx];
        sortedIdx = insElemIdx - 1;
        while ((sortedIdx >= 0) && (arr[sortedIdx] > insElem)) {
            arr[sortedIdx + 1] = arr[sortedIdx];  /* move right */
            --sortedIdx;  /* left search */
        }
        arr[sortedIdx + 1] = insElem;  /* insert */
    }

    return;
}

static void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\r\n");

    return;
}
void InsertSort_testHandler(void) {
    int arr[] = {9, 8, 5, 3, 2, 5, 0, 0, 0};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("InsertSort test -------------------------------------------\r\n");
    printf("Unsorted %2d-element array:", n); printArray(arr, n);
    InsertSort_insertSort(arr, n);
    printf("Sorted %4d-element array:", n);   printArray(arr, n);

    return;
}
