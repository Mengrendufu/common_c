//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "heap_sort.h"

//============================================================================
static void SM_swap(void *a, void *b, uint16_t size) {
    uint8_t *a_ = (uint8_t *)a;
    uint8_t *b_ = (uint8_t *)b;
    uint8_t tmp;
    while (size--) {
        tmp = *a_; *a_++ = *b_; *b_++ = tmp;
    }
}

//============================================================================
static void HeapSort_heapifyRecursive(void *arr, uint8_t size,
                                      uint16_t heapRange, uint16_t parent,
                                      HeapSortCmp cmpCb)
{
    uint16_t largest = parent;          // default.
    uint16_t lchild  = 2 * parent + 1;  // lchild.
    uint16_t rchild  = 2 * parent + 2;  // rchild.

    // lchild exists and bigger than current parent.
    if (
        (lchild < heapRange) && cmpCb(arr + lchild*size, arr + largest*size)
    ) {
        largest = lchild;
    }
    // rchild exists and bigger than current parent.
    if (
        (rchild < heapRange) && cmpCb(arr + rchild*size, arr + largest*size)
    ) {
        largest = rchild;
    }

    // make sure the parent is the largest.
    if (largest != parent) {
        SM_swap(arr + parent*size, arr + largest*size, size);
        // recursive heapify.
        HeapSort_heapifyRecursive(arr, size,
                                  heapRange, largest,
                                  cmpCb);
    }
}

//............................................................................
void HeapSort_heapSortRecursive(void *arr, uint16_t n,
                                uint8_t size,
                                HeapSortCmp cmpCb)
{
    // max heap built for each parent node.
    for (int parent = n / 2 - 1; parent >= 0; --parent) {
        HeapSort_heapifyRecursive(arr, size,
                                  n, parent,
                                  cmpCb);
    }

    // swap & sort.
    for (int heapRange = n - 1; heapRange > 0; --heapRange) {
        SM_swap(arr + 0*size, arr + heapRange*size, size);
        HeapSort_heapifyRecursive(arr, size,
                                  heapRange, 0,
                                  cmpCb);
    }
}

//============================================================================
static void HeapSort_heapifyIterative(void *arr, uint8_t size,
                                      uint16_t heapRange, uint16_t parent,
                                      HeapSortCmp cmpCb)
{
    while (parent < heapRange) {
        uint16_t largest = parent;
        uint16_t lchild  = 2 * parent + 1;
        uint16_t rchild  = 2 * parent + 2;
        // lchild exists and bigger than current parent.
        if (
            (lchild < heapRange)
            && cmpCb(arr + lchild*size, arr + largest*size)
        ) {
            largest = lchild;
        }
        // rchild exists and bigger than current parent.
        if (
            (rchild < heapRange)
            && cmpCb(arr + rchild*size, arr + largest*size)
        ) {
            largest = rchild;
        }
        // make sure the parent is the largest.
        if (largest != parent) {
            SM_swap(arr + parent*size, arr + largest*size, size);
            parent = largest;
        } else {
            break; // done.
        }
    }
}

//............................................................................
void HeapSort_heapSortIterative(void *arr, uint16_t n,
                                uint8_t size,
                                HeapSortCmp cmpCb)
{
    // max heap built for each parent node.
    for (int parent = n / 2 - 1; parent >= 0; --parent) {
        HeapSort_heapifyIterative(arr, size,
                                  n, parent,
                                  cmpCb);
    }
    // swap & sort.
    for (int heapRange = n - 1; heapRange > 0; --heapRange) {
        SM_swap(arr + 0*size, arr + heapRange*size, size);
        HeapSort_heapifyIterative(arr, size,
                                  heapRange, 0,
                                  cmpCb);
    }
}
