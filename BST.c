#include <stdlib.h>
#include "include/BST.h"

/**
 * @brief Функция инициализации узла дерева
 * 
 * @param[in] val Значение для инициализации
 * @return Указатель на дерево
 */
BST_t *BST_init(const int val) {
    BST_t *ret = (BST_t *) malloc(sizeof(BST_t));
    ret->val   = val;
    ret->left  = NULL;
    ret->right = NULL;
    return ret;
}

/**
 * @brief Функция помещения значения в дерево
 * 
 * @param[in,out] ptr Указатель на дерево
 * @param[in] val Значение для размещения
 */
void BST_insert(BST_t *ptr, const int val) {
    if (ptr == NULL) {
        ptr = BST_init(val);
        return;
    }
    if (val < ptr->val) {
        if (ptr->left == NULL)
            ptr->left = BST_init(val);
        else
            BST_insert(ptr->left, val);
    } else {
        if (ptr->right == NULL)
            ptr->right = BST_init(val);
        else
            BST_insert(ptr->right, val);
    }
}

/**
 * @brief Функция освобождения памяти, используемой деревом
 * 
 * @param[in,out] ptr Указатель на дерево
 */
void BST_free(BST_t *ptr) {
    if (ptr->left != NULL) {
        BST_free(ptr->left);
        ptr->left = NULL;
    }
    if (ptr->right != NULL) {
        BST_free(ptr->right);
        ptr->right = NULL;
    }
    free(ptr);
    ptr = NULL;
}
