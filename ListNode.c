#include <stdio.h>
#include <stdlib.h>
#include "include/ListNode.h"

// Инициализация списка
struct ListNode *init() {
    struct ListNode *head = (struct ListNode*) malloc(sizeof(struct ListNode));
    head->val = 0;
    head->next = NULL;
    return head;
}

// Создать новый узел и сделать его вершиной списка
void push(struct ListNode *head, int value) {
    struct ListNode *tmp = init();
    if (!tmp)
        exit(STACK_OVERFLOW);
    tmp->next = head->next;
    tmp->val = head->val;
    head->val = value;
    head->next = tmp;
}

// Вернуть значение текущей вершины и удалить её
int pop(struct ListNode **head) {
    if (!(*head))
        exit(STACK_UNDERFLOW);
    int value = (*head)->val;
    struct ListNode *tmp = (*head)->next;
    *head = tmp;
    return value;
}

// Вернуть значение последнего узла и удалить его
int getLast(struct ListNode **head) {
    if (!head)
        exit(STACK_UNDERFLOW);
    int value = 0;
    struct ListNode *tmp = *head;
    if (!tmp->next) {
        value = pop(&tmp);
        *head = tmp;
    }
    else {
        while (tmp->next->next) {
            tmp = tmp->next;
        }
        value = tmp->next->val;
        tmp->next = NULL;
    }
    return value;
}

// Вернуть длину списка
unsigned int getLength(struct ListNode *head) {
    if (!head)
        exit(STACK_UNDERFLOW);
    unsigned int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// Вернуть все значения списка в виде массива
int *getArray(struct ListNode *head) {
    if (!head)
        return NULL;
    int *array = NULL;
    int i = 1;
    while (head) {
        array = (int*) realloc(array, i*sizeof(int));
        array[i-1] = head->val;
        head = head->next;
        i++;
    }
    return array;
}

// Реверсировать список
struct ListNode *reverseList(struct ListNode *head) {
    if (!head)
        return head;
    int i = 0;
    int *array = NULL;
    while (head) {
        i++;
        array = (int*) realloc(array, i*sizeof(int));
        array[i-1] = pop(&head);
    }
    int len = i;
    struct ListNode *tmp = init();
    if (!tmp)
        exit(STACK_OVERFLOW);
    tmp->val = array[0];
    for (i = 1; i < len; i++) {
        push(tmp, array[i]);
    }
    return tmp;
}

// Сравнение двух cтеков
// 0 - стеки не равны
// 1 - стеки равны
unsigned char compareLists(struct ListNode *head_1, struct ListNode *head_2) {
    if (head_1 == head_2)
        return 1;
    if ((head_1 && !head_2) || (!head_1 && head_2))
        return 0;
    while (head_1 || head_2) {
        if (head_1->val != head_2->val)
            return 0;
        head_1 = head_1->next;
        head_2 = head_2->next;
    }
    return 1;
}

// Вывод списка на экран
void printList(struct ListNode *head) {
    if (head) {
        printf("%d ",head->val);
        printList(head->next);
    }
}

// Удаление всех вершины
void freeListNode(struct ListNode **head) {
    struct ListNode *tmp = NULL;
    while ((*head)->next) {
        tmp = (*head)->next;
        free(*head);
        (*head) = tmp;
    }
    free(*head);
}