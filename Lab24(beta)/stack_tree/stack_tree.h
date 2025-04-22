#pragma once

#include "../binaryTree/tree.h"

typedef struct {
    tree* buf;
    int max_len;
    int len;
} stack_tree;

stack_tree* stree_create(int max_len);
void stree_destroy(stack_tree* obj);
int stree_is_empty(stack_tree* obj);
int stree_push_back(stack_tree* obj, tree value);
tree stree_pop_back(stack_tree* obj);
tree stree_top(stack_tree* obj);