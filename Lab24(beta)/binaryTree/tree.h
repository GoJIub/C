#pragma once
#include "../token/token.h"

typedef struct treeNode treeNode;
struct treeNode {
    Token token;    // Токен вместо char
    treeNode *left;
    treeNode *right;
};

typedef treeNode *tree;

tree createEmpty();
tree build(Token token, tree left, tree right);
int isEmpty(tree t);
Token getValue(tree t);
tree getLeft(tree t);
tree getRight(tree t);
void destroyTree(tree t);

// Остальные функции остаются, но обновляются для работы с Token
void printTreePretty(tree t, int level);
void deleteUnitMultiply(tree* t);