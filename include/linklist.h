//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef LINKLIST_H_
#define LINKLIST_H_

//============================================================================
#include "linklist_port.h"

//============================================================================
typedef struct ListNode {
    struct ListNode *next;
} ListNode;

//============================================================================
typedef bool (*MergeSortCmp)(void *, void *);

//============================================================================
ListNode *LinkList_reverse(ListNode *lt);

ListNode *LinkList_mergeSort(ListNode *lt, MergeSortCmp cmpCb);

#endif // LINKLIST_H_
