//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "linklist.h"

//============================================================================
ListNode *LinkList_reverse(ListNode *lt) {
    ListNode *head = lt;
    ListNode *subHead = head;
    ListNode *subTail = (ListNode *)0;
    while (subHead) {
        if (!subTail) {
            subHead = head->next;
            head->next = (ListNode *)0;
            subTail = subHead;
        } else {
            subTail = subHead->next;
            subHead->next = head;
            head = subHead;
            subHead = subTail;
        }
    }
    return head;
}

//============================================================================
//! @brief Up mid.
//         Node --> Node --> Node --> Node --> (ListNode *)0
//                   ^
//                   |
//                   |
//                 slow
//! @private @memberof ListNode
static ListNode *LinkList_upMid(ListNode *lt) {
    ListNode *slow = lt;
    ListNode *fast = lt;
    while (fast && fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//............................................................................
//! @brief Down mid.
//         Node --> Node --> Node --> Node --> (ListNode *)0
//                            ^
//                            |
//                            |
//                          slow
//! @private @memberof ListNode
static ListNode *LinkList_downMid(ListNode *lt) {
    ListNode *slow = lt;
    ListNode *fast = lt;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//============================================================================
static ListNode *LinkList_mergeSort_merge(ListNode *ltLeft, ListNode *ltRight,
                                          MergeSortCmp cmpCb)
{
    ListNode *mergedLt = (ListNode *)0;
    ListNode *nodeIter = (ListNode *)0;
    while (ltLeft && ltRight) {
        if (!mergedLt) { // Init...
            if (cmpCb(ltLeft, ltRight)) {
                mergedLt = ltLeft;
                ltLeft = ltLeft->next;
            } else {
                mergedLt = ltRight;
                ltRight = ltRight->next;
            }
            mergedLt->next = (ListNode *)0;
            nodeIter = mergedLt;
        } else { // Iter...
            if (cmpCb(ltLeft, ltRight)) {
                nodeIter->next = ltLeft;
                ltLeft = ltLeft->next;
            } else {
                nodeIter->next = ltRight;
                ltRight = ltRight->next;
            }
            nodeIter = nodeIter->next;
        }
    }
    if (ltLeft)  nodeIter->next = ltLeft;
    if (ltRight) nodeIter->next = ltRight;

    return mergedLt;
}

//............................................................................
static ListNode *LinkList_mergeSort_mid(ListNode *lt) {
    ListNode *upMid;
    ListNode *downMid;
    upMid = LinkList_upMid(lt);
    downMid = upMid->next;
    upMid->next = (ListNode *)0; // Cut it off.
    if (downMid) return downMid; // Use down mid node.
    else         return upMid;   // Only one node.
}

//............................................................................
ListNode *LinkList_mergeSort(ListNode *lt, MergeSortCmp cmpCb) {
    ListNode *left  = lt;
    ListNode *right = LinkList_mergeSort_mid(lt);
    if (left == right) return left;
    left  = LinkList_mergeSort(left, cmpCb);
    right = LinkList_mergeSort(right, cmpCb);
    lt    = LinkList_mergeSort_merge(left, right, cmpCb);
    return lt;
}
