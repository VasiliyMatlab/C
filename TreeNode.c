#include <stdio.h>
#include <stdlib.h>
#include "include/TreeNode.h"

/*
Структура дерева:
        0
      /   \
     1     2
    / \   / \
   3   4 5   6
*/

// Инициализация дерева
struct TreeNode *init(int value) {
    struct TreeNode *tree = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if (!tree)
        exit(STACK_OVERFLOW);
    tree->val = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

// Запись значения в дерево по индексу (см. рисунок выше)
void set(struct TreeNode **tree, unsigned index, int value) {

    // Если null, то узел не создаем
    if (!value)
        return;
    // Если индекс нулевой, то сразу записываем значение узла
    if (!index) {
        *tree = init(value);
        return;
    }

    // Ищем путь
    struct TreeNode *tmp = *tree;
    unsigned cur_val = 0; // Индекс текущего узла
    while (cur_val != index) {
        // Куда идти
        path way = where(cur_val,index);
        // Направо
        if (way) {
            cur_val = 2*cur_val + 2;
            // Если нет узла, то создаем и записываем
            if (!tmp->right) {
                tmp->right = init(value);
                return;
            }
            // иначе спускаемся
            else
                tmp = tmp->right;
        }
        // Налево
        else {
            cur_val = 2*cur_val + 1;
            // Если нет узла, то создаем и записываем
            if (!tmp->left) {
                tmp->left = init(value);
                return;
            }
            // иначе спускаемся
            else
                tmp = tmp->left;
        }
    }
    // Если текущий индекс равен искомому,
    // то производим запись
    tmp->val = value;
}

// Вернуть значение узла дерева по индексу
int get(struct TreeNode *tree, unsigned index) {

    // Если индекс нулевой, то сразу возвращаем значение
    if (!index)
        return tree->val;
    
    // Ищем путь до нужного узла
    unsigned cur_val = 0; // Индекс текущего узла
    while (cur_val != index) {
        // Куда идти
        path way = where(cur_val,index);
        // Направо
        if (way) {
            cur_val = 2*cur_val + 2;
            // Если нет узла, то ошибка
            if (!tree->right) {
                printf("\nError: there is no node by index %d\n",index);
                exit(STACK_UNDERFLOW);
            }
            // иначе спускаемся
            else
                tree = tree->right;
        }
        // Налево
        else {
            cur_val = 2*cur_val + 1;
            // Если нет узла, то ошибка
            if (!tree->left) {
                printf("\nError: there is no node by index %d\n",index);
                exit(STACK_UNDERFLOW);
            }
            // иначе спускаемся
            else
                tree = tree->left;
        }
    }
    return tree->val;
}

// Максимальная глубина дерева
unsigned getDepth(struct TreeNode *tree) {
    if (!tree)
        return 0;
    unsigned k1 = 0;
    unsigned k2 = 0;
    if (tree->left) {
        k1 = getDepth(tree->left);
        
    }
    if (tree->right) {
        k2 = getDepth(tree->right);
        
    }
    return (k1 > k2) ? k1+1 : k2+1;
}

// Удаление дерева
void freeTreeNode(struct TreeNode **tree) {
    if (*tree) {
        freeTreeNode(&((*tree)->left));
        freeTreeNode(&((*tree)->right));
        free(*tree);
    }
}

//////////////////////////////////////////////////////////////
/////// Функции, не связанные непосредственно с деревом //////
//////////////////////////////////////////////////////////////

path where(int val, int value) {

    if (value == (2*val + 1))
        return left;
    if (value == (2*val + 2))
        return right;

    // Нахождение крайних левых значений индексов дерева
    int MRLB = val; // Max Right in Left Branch (0,1,4,10,22)
    int buff_MRLB; // Previous value
    while (MRLB < value) {
        buff_MRLB = MRLB;
        if (MRLB == val)
            MRLB = 2*MRLB + 1;
        else
            MRLB = 2*MRLB + 2;
    }
    // Нахождение крайних правых значений индексов дерева
    int MRRB = val; // Max Right in Right Branch (0,2,6,14,30)
    int buff_MRRB; // Previous value
    while (MRRB < value) {
        buff_MRRB = MRRB;
        MRRB = 2*MRRB + 2;
    }

    // Левая граница возможных индексов
    int bordet_left = buff_MRLB + 1;
    // Разделение областей пополам
    int border_center;
    // Правая граница возможных индексов
    int border_right = MRLB;

    // Уточнение границ
    if (buff_MRRB < bordet_left)
        border_center = MRRB;
    else
        border_center = buff_MRRB;
    
    // Определение в какую область попали
    if ((value >= bordet_left) && (value <= border_center))
        return right;
    else
        return left;

}