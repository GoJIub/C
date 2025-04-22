#pragma once

typedef struct treeNode treeNode;
struct treeNode {
    double val;
    treeNode *left;
    treeNode *right;
};

typedef treeNode *tree;

tree createEmpty();
tree build(double val, tree left, tree right);
int isEmpty(tree t);
double getValue(tree t);
tree getLeft(tree t);
tree getRight(tree t);
void destroyTree(tree t);

// tree add(tree t, double val);
// int addNew(tree* t, double val);
int addNode(tree *t, double val);
tree removeNode(tree t, double val);

// int getDepth(tree t);
// int levelWidth(tree t, int target);
// int getWidth(tree t);
// int getWidthVector(tree t);
// int getWidthBFS(tree t);

void printTree(tree t, int level);
void printTreePretty(tree t, int level);

int getPower(tree t);