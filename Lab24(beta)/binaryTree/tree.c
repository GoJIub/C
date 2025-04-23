#include "tree.h"
#include "../vector_int/vector_int.h"
#include "../queue_tree/queue_tree.h"
#include "../stack_tree/stack_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tree createEmpty() {
    return NULL;
}

int isEmpty(tree t) {
    return t == NULL;
}

Token getValue(tree t) {
    return t->token;
}

tree getLeft(tree t) {
    return t -> left;
}

tree getRight(tree t) {
    return t -> right;
}

tree build(Token token, tree left, tree right) {
    tree res = malloc(sizeof(treeNode));
    if (res == NULL) return NULL;
    res->token = token; // Копируем токен
    res->left = left;
    res->right = right;
    return res;
}

static void destroy(tree t) {
    if (!isEmpty(t)) free(t);
}

void destroyTree(tree t) {
    if (t == NULL) return;
    queue_tree* q = qtree_create(1);
    qtree_push_back(q, t);
    while (!qtree_is_empty(q)) {
        tree cur = qtree_pop_front(q);
        if (getLeft(cur) != NULL) qtree_push_back(q, getLeft(cur));
        if (getRight(cur) != NULL) qtree_push_back(q, getRight(cur));
        free(cur->token.value); // Освобождаем строку токена
        free(cur);
    }
    qtree_destroy(q);
}

void printTreePretty(tree t, int level) {
    if (isEmpty(t)) return;
    printTreePretty(getRight(t), level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("%s\n", getValue(t).value); // Печатаем строковое значение
    printTreePretty(getLeft(t), level + 1);
}

void deleteUnitMultiply(tree* t) {
    if (isEmpty(*t)) return;

    deleteUnitMultiply(&(*t)->left);
    deleteUnitMultiply(&(*t)->right);

    if ((*t)->token.type == TOK_OP && strcmp((*t)->token.value, "*") == 0) {
        if ((*t)->left != NULL && (*t)->left->token.type == TOK_CONST && strcmp((*t)->left->token.value, "1") == 0) {
            tree tmp = *t;
            *t = (*t)->right;
            destroyTree(tmp->left);
            free(tmp->token.value);
            free(tmp);
        } else if ((*t)->right != NULL && (*t)->right->token.type == TOK_CONST && strcmp((*t)->right->token.value, "1") == 0) {
            tree tmp = *t;
            *t = (*t)->left;
            destroyTree(tmp->right);
            free(tmp->token.value);
            free(tmp);
        }
    }
}