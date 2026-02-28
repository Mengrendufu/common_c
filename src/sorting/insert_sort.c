//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "insert_sort.h"

//============================================================================
void InsertSort_insertSort(int *arr, int n) {
    int insElemIdx, insElem, sortedIdx;
    for (insElemIdx = 1; insElemIdx < n; ++insElemIdx) {
        insElem = arr[insElemIdx];
        sortedIdx = insElemIdx - 1;
        while ((sortedIdx >= 0) && (arr[sortedIdx] > insElem)) { // asend.
            arr[sortedIdx + 1] = arr[sortedIdx];  // move right.
            --sortedIdx;  // left search.
        }
        arr[sortedIdx + 1] = insElem;  // insert.
    }
}
