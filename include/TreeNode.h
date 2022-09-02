#ifndef _TREE_NODE_H
#define _TREE_NODE_H

#define STACK_OVERFLOW  3
#define STACK_UNDERFLOW 4

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef enum {
    left,
    right
} path;

struct TreeNode *init(int);
void set(struct TreeNode **, unsigned, int);
int get(struct TreeNode *, unsigned);
unsigned getDepth(struct TreeNode *);
void freeTreeNode(struct TreeNode **);

// Сторонние функции
path where(int, int);

#endif