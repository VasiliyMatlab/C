#include <stdio.h>
#include <stdlib.h>
#include "include/DLL.h"

/**
 * @brief Функция инициализации узла двусвязанного списка
 * 
 * @param[in] val Значение
 * @return Указатель на созданный узел
 */
static Node_t *Node_init(const int val) {
    Node_t *ret = (Node_t *) malloc(sizeof(Node_t));
    if (ret == NULL) {
        fprintf(stderr, "Cannot allocate memory for node\n");
        return ret;
    }
    ret->val  = val;
    ret->prev = NULL;
    ret->next = NULL;
    return ret;
}

/**
 * @brief Функция освобождения пространства узла
 * 
 * @param[in,out] node Указатель на узел для освобождения
 */
static void Node_free(Node_t *node) {
    if (node == NULL) {
        fprintf(stderr, "Uninitialized node\n");
        return;
    }
    node->val  = 0;
    node->prev = NULL;
    node->next = NULL;
    free(node);
    node = NULL;
}

/**
 * @brief Функция инициализации двусвязанного списка
 * 
 * @return Указатель на двусвязанный список
 */
DLL_t *DLL_init(void) {
    DLL_t *ret = (DLL_t *) malloc(sizeof(DLL_t));
    if (ret == NULL) {
        fprintf(stderr, "Cannot allocate memory for list\n");
        return ret;
    }
    ret->head  = NULL;
    ret->tail  = NULL;
    return ret;
}

/**
 * @brief Функция помещения значения в двусвязанный список
 * 
 * @param[in,out] ptr Указатель на двусвязанный список
 * @param[in] val Значение
 */
void DLL_push(DLL_t *ptr, const int val) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    Node_t *tmp = Node_init(val);
    if (ptr->head == NULL) {
        ptr->head = tmp;
        ptr->tail = tmp;
    } else {
        ptr->tail->next = tmp;
        tmp->prev = ptr->tail;
        ptr->tail = tmp;
    }
}

/**
 * @brief Функция получения значения с вершины двусвязанного списка
 * 
 * @param[in,out] ptr Указатель на двусвязанный список
 * @return Значение с вершины списка
 */
int DLL_pop(DLL_t *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return -1;
    }
    if (ptr->head == NULL) {
        fprintf(stderr, "Empty list\n");
        return -2;
    }
    int ret;
    if (ptr->head == ptr->tail) {
        ret = ptr->head->val;
        Node_free(ptr->head);
        ptr->head = NULL;
        ptr->tail = NULL;
    } else {
        ret = ptr->tail->val;
        Node_t *tmp = ptr->tail->prev;
        Node_free(ptr->tail);
        tmp->next = NULL;
        ptr->tail = tmp;
    }
    return ret;
}

/**
 * @brief Функция вывода на экран двусвязанного списка
 * 
 * @param[in] ptr Указатель на двусвязанный список
 */
void DLL_print(const DLL_t *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    Node_t *tmp = ptr->head;
    fprintf(stdout, "SLL: ");
    while (tmp) {
        fprintf(stdout, "%d <-> ", tmp->val);
        tmp = tmp->next;
    }
    fprintf(stdout, "\b\b\b\b   \n");
}

/**
 * @brief Функция освобождения пространства, занятым двусвязанным списком
 * 
 * @param[in,out] ptr Указатель на двусвязанный список
 */
void DLL_free(DLL_t *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    if (ptr->head != NULL) {
        Node_t *tmp = NULL;
        while (ptr->head != ptr->tail) {
            tmp = ptr->head->next;
            Node_free(ptr->head);
            ptr->head = tmp;
        }
        Node_free(ptr->head);
        ptr->head = NULL;
        ptr->tail = NULL;
    }
    free(ptr);
    ptr = NULL;
}

