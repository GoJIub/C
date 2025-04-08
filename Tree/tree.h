#pragma once

typedef struct treeNode treeNode;
struct treeNode {
    treeNode* son;
    treeNode* bro;
    double val;
};
typedef treeNode *tree;

// ...
int add(tree* t, double val, char* path);