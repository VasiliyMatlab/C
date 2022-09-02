#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#define STACK_OVERFLOW  3
#define STACK_UNDERFLOW 4

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *init();
void push(struct ListNode *, int);
int pop(struct ListNode **);
int getLast(struct ListNode **);
unsigned int getLength(struct ListNode *);
int *getArray(struct ListNode *);
struct ListNode *reverseList(struct ListNode *);
unsigned char compareLists(struct ListNode *, struct ListNode *);
void printList(struct ListNode *);
void freeListNode(struct ListNode **);

#endif