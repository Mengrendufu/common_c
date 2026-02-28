//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include <stdlib.h>
#include "merge_sort.h"

//============================================================================
static void MergeSort_merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // copy.
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // compare & merge.
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) { // stable ascending.
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    // sorted paste.
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

//============================================================================
void MergeSort_mergeSortRecursive(int *arr, int left, int right) {
    if (left < right) {  // at least has two elements.
        int mid = left + (right - left) / 2;
        MergeSort_mergeSortRecursive(arr, left, mid);
        MergeSort_mergeSortRecursive(arr, mid + 1, right);
        MergeSort_merge(arr, left, mid, right);
    }
}

//............................................................................
void MergeSort_mergeSortIterative(int *arr, int n) {
    int mergeArrSize;
    int left, right, mid;
    for (mergeArrSize = 1; mergeArrSize < n; mergeArrSize *= 2) {
        // left = 0:
        //       for the whole array.
        // left < n - mergeArrSize:
        //       left + mergeArrSize <= n - 1,
        //       make sure that right merge part exists.
        // left += 2*mergeArrSize:
        //       jump to the next left merge part
        for (left = 0; left < n - mergeArrSize; left += 2*mergeArrSize) {
            mid = left + mergeArrSize - 1;
            right = left + 2*mergeArrSize - 1;
            if (right > n - 1) right = n - 1; // truncate.
            MergeSort_merge(arr, left, mid, right);
        }
    }
}
