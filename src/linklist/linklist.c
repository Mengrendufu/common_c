#include <stdio.h>

#include <stdint.h>

#include "stdlib.h"

#include "void_ops.h"

#include "linklist.h"

static void linkListPrinter(struct ListNode *lt);

ListNode *linkListReverse(ListNode *lt) {

    ListNode *head = lt;

    ListNode *subHead = head;

    ListNode *subTail = NULL;

    while (subHead) {

        if (!subTail) {

            subHead = head->next;

            head->next = NULL;

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

ListNode *linkListGenerater(void *arr, int arrSize) {

    ListNode *head;

    ListNode *insNode;

    head = NULL;

    for (int i = 0; i < arrSize; ++i) {

        insNode = malloc(sizeof(struct ListNode));

        if (!head) {  /* init */

            head = insNode;

            head->val = VOID_CAST(ALIGN_PTR_LEN(((int *)(arr))[i]));

            head->next = NULL;

        } else {  /* iterate */

            insNode->val = VOID_CAST(ALIGN_PTR_LEN(((int *)(arr))[i]));

            insNode->next = head;

            head = insNode;

        }
    }

    head = linkListReverse(head);

    return head;

}

void linkListFree(ListNode *lt) {

    ListNode *tmp;

    while (lt) {

        tmp = lt;

        free(tmp);

        lt = lt->next;

    }

    return;

}

/* middle node */
ListNode *linkListMidNode(ListNode *lt) {

    ListNode *slow = lt;

    ListNode *fast = lt;

    ListNode *upperMid = slow;

    while (fast && fast->next) {

        upperMid = slow;

        slow = slow->next;

        fast = fast->next->next;

    }

    upperMid->next = NULL;

    return slow;

}

typedef int (*SortCmp)(void *, void *);

int sortCmpAsscending_int(void * intNum1, void * intNum2) {

    if (((int)(ALIGN_PTR_LEN(intNum1))) <= ((int)(ALIGN_PTR_LEN(intNum2)))) {

        return 1;

    } else {

        return 0;

    }

}

ListNode *linkListMergeSort_merge(

    ListNode *ltLeft,

    ListNode *ltRight,

    SortCmp cmp)

{

    ListNode *mergedLt = NULL;

    ListNode *nodeIter;

    while (ltLeft && ltRight) {

        if (!mergedLt) {  /* init */

            if (cmp(ltLeft->val, ltRight->val)) {

                mergedLt = ltLeft;

                ltLeft = ltLeft->next;

                mergedLt->next = NULL;

            } else {

                mergedLt = ltRight;

                ltRight = ltRight->next;

                mergedLt->next = NULL;

            }

            nodeIter = mergedLt;

        } else {  /* iter */

            if (cmp(ltLeft->val, ltRight->val)) {

                nodeIter->next = ltLeft;

                nodeIter = nodeIter->next;;

                ltLeft = ltLeft->next;

            } else {

                nodeIter->next = ltRight;

                nodeIter = nodeIter->next;

                ltRight = ltRight->next;

            }

        }

    }

    if (ltLeft) {

        nodeIter->next = ltLeft;

    }

    if (ltRight) {

        nodeIter->next = ltRight;

    }

    return mergedLt;

}

ListNode *linkListMergeSort(ListNode *lt, SortCmp cmp) {

    ListNode *left  = lt;

    ListNode *right = linkListMidNode(lt);

    if (left == right) {

        return left;

    }

    left  = linkListMergeSort(left, cmp);

    right = linkListMergeSort(right, cmp);

    lt = linkListMergeSort_merge(left, right, cmp);

    return lt;

}

static void linkListPrinter(struct ListNode *lt) {

    struct ListNode *prtNode = lt;

    while (prtNode) {

        printf("%lld", ALIGN_PTR_LEN(prtNode->val));

        if (prtNode->next) {

            printf(" --> ");

        }

        prtNode = prtNode->next;

    }

    printf(" --> NULL\r\n");

    return;

}

void LinkList_testHandler(void) {

    printf("LinkList_mergeSort test -----------------------------------\r\n");

    int arrLinkList_1[] = {

        2,6,4,0,5,0,2,7,6,8

    };

    int arrLinkList_2[] = {3};

    ListNode *lt_1 = linkListGenerater(

                        arrLinkList_1,

                        sizeof(arrLinkList_1)/sizeof(arrLinkList_1[0]));

    ListNode *lt_2 = linkListGenerater(

                        arrLinkList_2,

                        sizeof(arrLinkList_2)/sizeof(arrLinkList_2[0]));

    printf("lt1: ");

    linkListPrinter(lt_1);

    printf("lt2: ");

    linkListPrinter(lt_2);

    ListNode *lt = linkListMergeSort(lt_1, sortCmpAsscending_int);

    printf("MergeSorted lt_1: ");

    linkListPrinter(lt);

    return;

}
