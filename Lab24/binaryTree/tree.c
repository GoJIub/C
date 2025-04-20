#include "tree.h"
#include "../vector_int/vector_int.h"
#include "../queue_tree/queue_tree.h"
#include "../stack_tree/stack_tree.h"
#include <stdlib.h>
#include <stdio.h>

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

char getValue(tree t) {
    return t -> val;
}

tree getLeft(tree t) {
    return t -> left;
}

tree getRight(tree t) {
    return t -> right;
}

tree build(char val, tree left, tree right) {
    tree res = malloc(sizeof(treeNode));
    if (res == NULL) return NULL;
    res -> val = val;
    res -> left = left;
    res -> right = right;
    return res;
}

static void destroy(tree t) {
    if (!isEmpty(t)) free(t);
}

void destroyTree(tree t) { // Iteration
    if (t == NULL) return;
    queue_tree* q = qtree_create(1);
    qtree_push_back(q, t);
    while (!qtree_is_empty(q)) {
        tree cur = qtree_pop_front(q);
        if (getLeft(cur) != NULL) qtree_push_back(q, getLeft(cur));
        if (getRight(cur) != NULL) qtree_push_back(q, getRight(cur));
        destroy(cur);
    }
    qtree_destroy(q);
}

tree add(tree t, char val) {
    if (isEmpty(t)) return build(val, createEmpty(), createEmpty());
    if (val < getValue(t)) {
        tree left = add(getLeft(t), val);
        tree res = build(getValue(t), left, getRight(t));
        destroy(t);
        return res;
    } else if (val > getValue(t)) {
        tree right = add(getRight(t), val);
        tree res = build(getValue(t), getLeft(t), right);
        destroy(t);
        return res;
    } else return t;
}

int addNew(tree* t, char val) {
    if (isEmpty(*t)) {
        *t = malloc(sizeof(treeNode));
        (*t) -> val = val;
        (*t) -> left = NULL;
        (*t) -> right = NULL;
        return 1;
    }
    if (val < (*t) -> val) return addNew(&(*t) -> left, val);
    if (val > (*t) -> val) return addNew(&(*t) -> right, val);
    return 0;
}

tree removeNode(tree t, char val) {
    if (isEmpty(t))
        return t;
    
    if (val < getValue(t)) {
        tree left = removeNode(getLeft(t), val);
        tree res = build(getValue(t), left, getRight(t));
        
        destroy(t);
        
        return res;
    } 

    else if (val > getValue(t)) {
        tree right = removeNode(getRight(t), val);
        tree res = build(getValue(t), getLeft(t), right);
        
        destroy(t);
        
        return res;
    }
    
    if (isEmpty(getLeft(t))) {
        tree res = getRight(t);
        destroy(t);
        
        return res;
    } 

    else if (isEmpty(getRight(t))) {
        tree res = getLeft(t);
        destroy(t);
        
        return res;
    }
    
    tree maxLeft = getLeft(t);

    while (!isEmpty(getRight(maxLeft)))
        maxLeft = getRight(maxLeft);
    
    char maxLeftVal = getValue(maxLeft);
    
    tree left = removeNode(getLeft(t), maxLeftVal);
    tree res = build(maxLeftVal, left, getRight(t));
    
    destroy(t);

    return res;
}

static int max(int n, int m) {
    return n > m ? n : m;
}

int getDepth(tree t) {
    if (t == NULL) return 0;
    return 1 + max(getDepth(t -> left), getDepth(t -> right));
}

int levelWidth(tree t, int k) {
    if (k == 0) return t == NULL ? 0 : 1;
    return levelWidth(t -> left, k - 1) + levelWidth(t -> right, k - 1);
}

int getWidth(tree t) {
    int res = 0;
    int d = getDepth(t);
    for (int i = 0; i < d; ++i) res = max(res, levelWidth(t, i));
    return res;
}

static void widths(tree t, vector_int* v, int k) {
    if (t == NULL) return;
    if (vint_get_size(v) < k + 1) vint_set_size(v, k + 1);
    vint_set(v, k, vint_get(v, k) + 1);
    widths(t -> left, v, k + 1);
    widths(t -> right, v, k + 1);
}

int getWidthVector(tree t) {
    vector_int* v = vint_create(0);
    widths(t, v, 0);
    int res = 0;
    for (int i = 0; i < vint_get_size(v); ++i) res = max(res, vint_get(v, i));
    vint_destroy(v);
    return res;
}

int getWidthBFS(tree t) {
    if (t == NULL) return 0;
    queue_tree* q1 = qtree_create(1);
    queue_tree* q2 = qtree_create(1);
    int res = 0;
    qtree_push_back(q1, t);
    while (!qtree_is_empty(q1)) {
        res = max(res, qtree_get_size(q1));
        while (!qtree_is_empty(q1)) {
            tree cur = qtree_pop_front(q1);
            if (getLeft(cur) != NULL) qtree_push_back(q2, getLeft(cur));
            if (getRight(cur)!= NULL) qtree_push_back(q2, getRight(cur));
        }
        queue_tree* c = q2;
        q2 = q1;
        q1 = c;
    }
    qtree_destroy(q1);
    qtree_destroy(q2);
    return res;
}

void printTreePretty(tree t, int level) {
    if (isEmpty(t)) return;
    printTreePretty(getRight(t), level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("%c\n", getValue(t));
    printTreePretty(getLeft(t), level + 1);
}

void deleteUnitMultiply(tree* t) {
    if (isEmpty(*t)) return;

    deleteUnitMultiply(&(*t)->left);
    deleteUnitMultiply(&(*t)->right);

    if ((*t)->val == '*') {
        if ((*t)->left != NULL && (*t)->left->val == '1') {
            tree tmp = *t;
            *t = (*t)->right;
            destroy(tmp->left);
            destroy(tmp);
        } else if ((*t)->right != NULL && (*t)->right->val == '1') {
            tree tmp = *t;
            *t = (*t)->left;
            destroy(tmp->right);
            destroy(tmp);
        }
    }
}