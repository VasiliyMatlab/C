#include <stdio.h>
#include <stdlib.h>
#include "include/SLL.h"

/**
 * @brief Функция инициализации узла односвязанного списка
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
    node->next = NULL;
    free(node);
    node = NULL;
}

/**
 * @brief Функция инициализации односвязанного списка
 * 
 * @return Указатель на односвязанный список
 */
SLL_t *SLL_init(void) {
    SLL_t *ret = (SLL_t *) malloc(sizeof(SLL_t));
    if (ret == NULL) {
        fprintf(stderr, "Cannot allocate memory for list\n");
        return ret;
    }
    ret->head  = NULL;
    ret->tail  = NULL;
    return ret;
}

/**
 * @brief Функция помещения значения в односвязанный список
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 * @param[in] val Значение
 */
void SLL_push(SLL_t *ptr, const int val) {
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
        ptr->tail = tmp;
    }
}

/**
 * @brief Функция помещения значения в начало односвязанного списка
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 * @param[in] val Значение
 */
void SLL_push_forward(SLL_t *ptr, const int val) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    Node_t *tmp = Node_init(val);
    if (ptr->head == NULL) {
        ptr->head = tmp;
        ptr->tail = tmp;
    } else {
        tmp->next = ptr->head;
        ptr->head = tmp;
    }
}

/**
 * @brief Функция помещения значения в определенный индекс односвязанного списка
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 * @param[in] val Значение
 * @param[in] idx Индекс
 */
void SLL_insert(SLL_t *ptr, const int val, const int idx) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    if (idx == 0) {
        SLL_push_forward(ptr, val);
        return;
    }
    int i = 1;
    Node_t *tmp = ptr->head;
    while (tmp != NULL) {
        if (i == idx) {
            Node_t *ins = Node_init(val);
            ins->next = tmp->next;
            tmp->next = ins;
            return;
        }
        tmp = tmp->next;
        i++;
    }
    fprintf(stderr, "Invalid index %d\n", idx);
}

/**
 * @brief Функция получения значения с вершины односвязанного списка
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 * @return Значение с вершины списка
 */
int SLL_pop(SLL_t *ptr) {
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
        Node_t *tmp = ptr->head;
        while (tmp->next != ptr->tail)
            tmp = tmp->next;
        Node_free(ptr->tail);
        ptr->tail = tmp;
        ptr->tail->next = NULL;
    }
    return ret;
}

/**
 * @brief Функция получения значения с начала односвязанного списка
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 * @return Значение с начала списка
 */
int SLL_pop_forward(SLL_t *ptr) {
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
        ret = ptr->head->val;
        Node_t *tmp = ptr->head->next;
        Node_free(ptr->head);
        ptr->head = tmp;
    }
    return ret;
}

/**
 * @brief Функция вывода на экран односвязанного списка
 * 
 * @param[in] ptr Указатель на односвязанный список
 */
void SLL_print(const SLL_t *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Uninitialized list\n");
        return;
    }
    Node_t *tmp = ptr->head;
    fprintf(stdout, "SLL: ");
    while (tmp) {
        fprintf(stdout, "%d -> ", tmp->val);
        tmp = tmp->next;
    }
    fprintf(stdout, "\b\b\b  \n");
}

/**
 * @brief Функция освобождения пространства, занятым односвязанным списком
 * 
 * @param[in,out] ptr Указатель на односвязанный список
 */
void SLL_free(SLL_t *ptr) {
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
