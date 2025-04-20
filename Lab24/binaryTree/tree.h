#pragma once

typedef struct treeNode treeNode;
struct treeNode {
    char val;
    treeNode *left;
    treeNode *right;
};

typedef treeNode *tree;

tree createEmpty();
tree build(char val, tree left, tree right);
int isEmpty(tree t);
char getValue(tree t);
tree getLeft(tree t);
tree getRight(tree t);
void destroyTree(tree t);

tree add(tree t, char val);
int addNew(tree* t, char val);
tree removeNode(tree t, char val);

int getDepth(tree t);
int levelWidth(tree t, int target);
int getWidth(tree t);
int getWidthVector(tree t);
int getWidthBFS(tree t);

void printTreePretty(tree t, int level);

void deleteUnitMultiply(tree* t);