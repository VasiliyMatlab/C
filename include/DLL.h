/**
 * @file DLL.h
 * @author Vasiliy
 * @brief Header file of Double Linked List (DLL)
 * @version 0.1
 * @date 23-04-2023
 * @copyright Copyright (c) 2023
 */

#ifndef __DLL_H__
#define __DLL_H__


typedef struct Node {
    int val;
    struct Node *prev;
    struct Node *next;
} Node_t;

typedef struct DLL {
    Node_t *head;
    Node_t *tail;
} DLL_t;

DLL_t *DLL_init(void);
void DLL_push(DLL_t *ptr, const int val);
int DLL_pop(DLL_t *ptr);
void DLL_print(const DLL_t *ptr);
void DLL_free(DLL_t *ptr);


#endif /* __DLL_H__ */
