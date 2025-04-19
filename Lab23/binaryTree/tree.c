#include "tree.h"
#include "../vector/vector_int.h"
#include "../queue/queue_tree.h"
#include "../stack/stack_tree.h"
#include <stdlib.h>
#include <stdio.h>

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

double getValue(tree t) {
    return t -> val;
}

tree getLeft(tree t) {
    return t -> left;
}

tree getRight(tree t) {
    return t -> right;
}

tree build(double val, tree left, tree right) {
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

tree add(tree t, double val) {
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

int addNew(tree* t, double val) {
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

int addNode(tree *t, double val) { // Iteration
    tree* cur = t;
    while (!isEmpty(*cur)) {
        if (val < (*cur) -> val) cur = &(*cur) -> left;
        else if (val > (*cur) -> val) cur = &(*cur) -> right;
        else return 0;
    }
    *cur = malloc(sizeof(tree));
    if (isEmpty(*cur)) return 0;
    (*cur) -> val = val;
    (*cur) -> left = NULL;
    (*cur) -> right = NULL;
    return 1;
}

// tree removeNode(tree t, double val) {
//     if (isEmpty(t))
//         return t;
    
//     if (val < getValue(t)) {
//         tree left = removeNode(getLeft(t), val);
//         tree res = build(getValue(t), left, getRight(t));
        
//         destroy(t);
        
//         return res;
//     } 

//     else if (val > getValue(t)) {
//         tree right = removeNode(getRight(t), val);
//         tree res = build(getValue(t), getLeft(t), right);
        
//         destroy(t);
        
//         return res;
//     }
    
//     if (isEmpty(getLeft(t))) {
//         tree res = getRight(t);
//         destroy(t);
        
//         return res;
//     } 

//     else if (isEmpty(getRight(t))) {
//         tree res = getLeft(t);
//         destroy(t);
        
//         return res;
//     }
    
//     tree maxLeft = getLeft(t);

//     while (!isEmpty(getRight(maxLeft)))
//         maxLeft = getRight(maxLeft);
    
//     double maxLeftVal = getValue(maxLeft);
    
//     tree left = removeNode(getLeft(t), maxLeftVal);
//     tree res = build(maxLeftVal, left, getRight(t));
    
//     destroy(t);

//     return res;
// }

tree removeNode(tree t, double val) { // Iteration
    tree* cur = &t;
    while (*cur != NULL && (*cur) -> val != val) {
        if (val < (*cur) -> val) cur = &((*cur) -> left);
        else cur = &((*cur) -> right);
    }
    if (*cur == NULL) return t;
    tree nodeToDelete = *cur;
    if (nodeToDelete -> left == NULL) {
        *cur = nodeToDelete -> right;
        destroy(nodeToDelete);
    } else if (nodeToDelete -> right == NULL) {
        *cur = nodeToDelete -> left;
        destroy(nodeToDelete);
    } else {
        tree* maxLeft = &(nodeToDelete -> left);
        while ((*maxLeft) -> right != NULL) maxLeft = &((*maxLeft) -> right);
        nodeToDelete -> val = (*maxLeft) -> val;
        tree temp = *maxLeft;
        *maxLeft = (*maxLeft) -> left;
        destroy(temp);
    }
    return t;
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
    if (isEmpty(t)) {
        return;
    }
    printTreePretty(getRight(t), level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%.2f\n", getValue(t));
    printTreePretty(getLeft(t), level + 1);
}

void printTree(tree t, int level) { // Iteration - Ugly
    if (isEmpty(t)) return;

    typedef struct {
        tree node;
        int level;
    } StackNode;

    stack_tree* stack = stree_create(10);
    StackNode* root = malloc(sizeof(StackNode));
    root -> node = t;
    root -> level = 0;
    stree_push_back(stack, (tree)root);

    while (!stree_is_empty(stack)) {
        StackNode* cur = (StackNode*)stree_pop_back(stack);
        if (cur -> node == NULL) {
            free(cur);
            continue;
        }
        StackNode* right = malloc(sizeof(StackNode));
        right -> node = getRight(cur -> node);
        right -> level = cur -> level + 1;
        stree_push_back(stack, (tree)right);
        for (int i = 0; i < cur -> level; i++) printf("    ");
        printf("%.2f\n", getValue(cur -> node));
        StackNode* left = malloc(sizeof(StackNode));
        left -> node = getLeft(cur -> node);
        left -> level = cur -> level + 1;
        stree_push_back(stack, (tree)left);
        free(cur);
    }
    stree_destroy(stack);
}

int getPower(tree t) { // Iteration
    if (t == NULL) return 0;
    queue_tree* q1 = qtree_create(1);
    queue_tree* q2 = qtree_create(1);
    int res = 0;
    qtree_push_back(q1, t);
    while (!qtree_is_empty(q1)) {
        res = max(res, (getLeft(qtree_top(q1)) != NULL) + (getRight(qtree_top(q1)) != NULL));
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