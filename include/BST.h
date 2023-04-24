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

BST_t *BST_init(int val);
void BST_insert(BST_t *ptr, const int val);
void BST_free(BST_t *ptr);


#endif /* __BST_H__*/
