#include <stdio.h>
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
 * @brief Функция поиска узла дерева по значению
 * 
 * @param[in] ptr Указатель на дерево
 * @param[in] val Значение узла
 * @return Указатель на разыскиваемый узел
 */
BST_t *BST_search(BST_t *ptr, const int val) {
    if (ptr == NULL)
        return NULL;
    if (ptr->val == val)
        return ptr;
    return (val < ptr->val) ? BST_search(ptr->left, val) : BST_search(ptr->right, val);
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
 * @brief Функция поиска узла с минимальным значением
 * 
 * @param[in] ptr Указатель на дерево
 * @return Указатель на узел с минимальным значением
 */
BST_t *BST_getMin(BST_t *ptr) {
    if (ptr == NULL)
        return NULL;
    if (ptr->left == NULL)
        return ptr;
    return BST_getMin(ptr->left);
}

/**
 * @brief Функция поиска узла с максимальным значением
 * 
 * @param[in] ptr Указатель на дерево
 * @return Указатель на узел с максимальным значением
 */
BST_t *BST_getMax(BST_t *ptr) {
    if (ptr == NULL)
        return NULL;
    if (ptr->right == NULL)
        return ptr;
    return BST_getMax(ptr->right);
}

/**
 * @brief Функция вывода на экран значений узлов дерева
 * при симметричном обходе
 * 
 * @param[in] ptr Указатель на дерево
 */
void BST_print(const BST_t *ptr) {
    if (ptr == NULL)
        return;
    BST_print(ptr->left);
    fprintf(stdout, "%d ", ptr->val);
    BST_print(ptr->right);
}

/**
 * @brief Функция вывода на экран значений узлов дерева
 * при прямом обходе
 * 
 * @param[in] ptr Указатель на дерево
 */
void BST_print_forward(const BST_t *ptr) {
    if (ptr == NULL)
        return;
    BST_print_forward(ptr->left);
    BST_print_forward(ptr->right);
    fprintf(stdout, "%d ", ptr->val);
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
