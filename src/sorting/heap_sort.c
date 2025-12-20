/* dependencies ------------------------------------------------------------*/
#include <stdio.h>

#include "heap_sort.h"
/* dependencies ------------------------------------------------------------*/

/* swap */
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

/* max heap built recursive */
static void heapifyRecursive(int arr[], int heapRange, int parent) {
    int largest = parent;          /* parent */
    int lchild  = 2 * parent + 1;  /* lchild */
    int rchild  = 2 * parent + 2;  /* rchild */

    /* lchild exists and bigger than current parent */
    if ((lchild < heapRange) && (arr[lchild] > arr[largest])) {
        largest = lchild;
    }

    /* rchild exists and bigger than current parent */
    if ((rchild < heapRange) && (arr[rchild] > arr[largest])) {
        largest = rchild;
    }

    /* make sure the parent is the largest */
    if (largest != parent) {
        swap(&arr[parent], &arr[largest]);  /* largest pop to the parent */
        heapifyRecursive(arr, heapRange, largest); /* recursive heapify */
    }

    return;
}
/* iterative heap building & sorting */
void HeapSort_heapSort_recursive(int arr[], int heapNum) {
    /* max heap built for each parent node */
    for (int parent = heapNum / 2 - 1; parent >= 0; --parent) {
        heapifyRecursive(arr, heapNum, parent);
    }

    /* swap & sort */
    for (int heapRange = heapNum - 1; heapRange > 0; --heapRange) {
        swap(&arr[0], &arr[heapRange]);  /* current largest to the rear */
        heapifyRecursive(arr, heapRange, 0);  /* rebuild the parent node */
    }

    return;
}

/* max heap built iterative */
static void heapifyIterative(int arr[], int heapRange, int parent) {
    while (parent < heapRange) {
        int largest = parent;
        int lchid   = 2 * parent + 1;
        int rchild   = 2 * parent + 2;
        /* lchild exists and bigger than current parent */
        if ((lchid < heapRange) && (arr[lchid] > arr[largest])) {
            largest = lchid;
        }
        /* rchild exists and bigger than current parent */
        if ((rchild < heapRange) && (arr[rchild] > arr[largest])) {
            largest = rchild;
        }
        /* make sure the parent is the largest */
        if (largest != parent) {
            swap(&arr[parent], &arr[largest]);
            parent = largest;  /* continue building the max heap */
        }
        else {
            break; /* current max heap is built done */
        }
    }
    return;
}
/* iterative heap building & sorting */
void HeapSort_heapSort_iterative(int arr[], int heapNum) {
    /* max heap built for each parent node */
    for (int parent = heapNum / 2 - 1; parent >= 0; --parent) {
        heapifyIterative(arr, heapNum, parent);
    }

    /* swap & sort */
    for (int heapRange = heapNum - 1; heapRange > 0; --heapRange) {
        swap(&arr[0], &arr[heapRange]);  /* current largest to the rear */
        heapifyIterative(arr, heapRange, 0);  /* rebuild the parent node */
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
void HeapSort_testHandler(void) {
    int arr[] = {9, 8, 5, 3, 2, 5, 0, 0, 0};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("HeapSort test ---------------------------------------------\r\n");
    printf("Unsorted %2d-element array:", n); printArray(arr, n);
    HeapSort_heapSort_recursive(arr, n);
    // HeapSort_heapSort_iterative(arr, n);
    printf("Sorted %4d-element array:", n);   printArray(arr, n);

    return;
}
