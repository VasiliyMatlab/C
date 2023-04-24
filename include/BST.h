/**
 * @file BST.h
 * @author Vasiliy
 * @brief Header file for Binary Search Tree (BST)
 * @version 0.1
 * @date 24-04-2023
 * @copyright Copyright (c) 2023
 */

#ifndef __BST_H__
#define __BST_H__


typedef struct BST {
    int val;
    struct BST *left;
    struct BST *right;
} BST_t;

BST_t *BST_init(const int val);
BST_t *BST_search(BST_t *ptr, const int val);
void BST_insert(BST_t *ptr, const int val);
BST_t *BST_getMin(BST_t *ptr);
BST_t *BST_getMax(BST_t *ptr);
void BST_print(const BST_t *ptr);
void BST_print_forward(const BST_t *ptr);
void BST_free(BST_t *ptr);


#endif /* __BST_H__*/
