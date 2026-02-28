//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include <stdio.h>
#include "quick_sort.h"

//============================================================================
static void QuickSort_swap(int* a, int* b) {
    int temp = *a; *a = *b; *b = temp;
}

//............................................................................
static int QuickSort_partition(int *arr, int left, int right) {
    int pivot;  // pivot of partition.
    //! Get the middle of left, mid and right and put it to the [right]...
    int mid = left + (right - left) / 2;
    if (arr[left] <= arr[mid]) {
        if (arr[mid] <= arr[right]) {
            // left <= mid <= right.
            QuickSort_swap(&arr[mid], &arr[right]);
        } else if (arr[left] <= arr[right]) {
            // left <= right < mid.
            // no position replacement.
        } else {
            // right < left <= mid.
            QuickSort_swap(&arr[left], &arr[right]);
        }
    }
    else {
        if (arr[left] <= arr[right]) {
            // mid < left <= right.
            QuickSort_swap(&arr[left], &arr[right]);
        } else if (arr[mid] <= arr[right]) {
            // mid <= right < left.
            // no position replacement.
        } else {
            // right < mid < left.
            QuickSort_swap(&arr[mid], &arr[right]);
        }
    }
    pivot = arr[right];

    // partition...
    int pivIdx = left;  // idx of element lower than pivot of partition.
    for (int opIdx = left; opIdx <= right - 1; opIdx++) {
        // comparing with pivot, ascending.
        if (arr[opIdx] <= pivot) {
            // put ascending element one by one.
            QuickSort_swap(&arr[pivIdx], &arr[opIdx]);
            ++pivIdx;  // index moving to the border.
        }
    }

    // put pivot to the border of divided part.
    QuickSort_swap(&arr[pivIdx], &arr[right]);

    // loc of divided partition: ... ... pivIdx(placed pivot) .......
    return (pivIdx);
}

//============================================================================
void QuickSort_recursive(int *arr, int left, int right) {
    if (left < right) {  // >= 2 elements.
        // base.
        int pivIdx = QuickSort_partition(arr, left, right);
        // recursive left and right partition.
        QuickSort_recursive(arr, left, pivIdx-1);
        QuickSort_recursive(arr, pivIdx+1, right);
    }
}

//............................................................................
void QuickSort_iterative(int *arr, int left, int right) {
    if (right - left < 1)  return;
    // stack will hold pairs of indices: low, high.
    int stack[2 * (right - left + 1)];
    int top = -1;

    // push initial range.
    stack[++top] = left;
    stack[++top] = right;
    while (top >= 0) {
        int partRight = stack[top--];
        int partLeft  = stack[top--];

        // partition.
        int pivIdx = QuickSort_partition(arr,
                                         partLeft,
                                         partRight);

        // If there are elements on left side of pivot, push left side.
        if (pivIdx - 1 > partLeft) {
            stack[++top] = partLeft;
            stack[++top] = pivIdx - 1;
        }

        // If there are elements on right side of pivot, push right side.
        if (pivIdx + 1 < partRight) {
            stack[++top] = pivIdx + 1;
            stack[++top] = partRight;
        }
    }
}
