#ifndef linklist_h_
#define linklist_h_

typedef struct ListNode {

    void *val;

    struct ListNode *next;

} ListNode;

void LinkList_testHandler(void);

#endif  /* linklist_h_ */
