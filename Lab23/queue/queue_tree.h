#pragma once

#include "../binaryTree/tree.h"

typedef struct {
    tree* buf;
    int max_len;
    int len;
    int start;
} queue_tree;

queue_tree* qtree_create(int max_len);
void qtree_destroy(queue_tree* obj);
int qtree_is_empty(queue_tree* obj);
int qtree_get_size(queue_tree* obj);
int qtree_push_back(queue_tree* obj, tree value);
tree qtree_top(queue_tree* obj);
tree qtree_pop_front(queue_tree* obj);