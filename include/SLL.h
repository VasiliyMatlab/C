/**
 * @file SLL.h
 * @author Vasiliy
 * @brief Header file of Single Linked List (SLL)
 * @version 0.1
 * @date 23-04-2023
 * @copyright Copyright (c) 2023
 */

#ifndef __SLL_H__
#define __SLL_H__


typedef struct Node {
    int val;
    struct Node *next;
} Node_t;

typedef struct SLL {
    Node_t *head;
    Node_t *tail;
} SLL_t;

SLL_t *SLL_init(void);
void SLL_push(SLL_t *ptr, const int val);
void SLL_push_forward(SLL_t *ptr, const int val);
int SLL_pop(SLL_t *ptr);
int SLL_pop_forward(SLL_t *ptr);
void SLL_print(const SLL_t *ptr);
void SLL_free(SLL_t *ptr);


#endif /* __SSL_H__ */