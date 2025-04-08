#include "tree.h"
#include <stdio.h>

void printTree(tree t) {
    if (isEmpty(t)) {
        return;
    }
    printTree(getLeft(t));
    printf("%.2f ", getValue(t));
    printTree(getRight(t));
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

int main() {
    printf("Creating empty tree...\n");
    tree myTree = createEmpty();
    
    printf("\nChecking if tree is empty: %s\n", 
           isEmpty(myTree) ? "Yes" : "No");
    
    printf("\nAdding elements: 5, 3, 7, 2, 4, 7, 6\n");
    myTree = add(myTree, 5);
    myTree = add(myTree, 3);
    myTree = add(myTree, 7);
    myTree = add(myTree, 2);
    myTree = add(myTree, 4);
    myTree = add(myTree, 7);
    myTree = add(myTree, 6);
    
    printf("\nDepth: ");
    printf("%d", getDepth(myTree));
    printf("\n");
    
    printf("\nWidth: ");
    printf("%d", getWidth(myTree));
    printf("\n");

    printf("\nWidth with vector: ");
    printf("%d", getWidthVector(myTree));
    printf("\n");
    
    printf("\nWidth with BFS: ");
    printf("%d", getWidthBFS(myTree));
    printf("\n");
    
    printf("\nTree in-order (sorted): ");
    printTree(myTree);
    printf("\n");
    
    printf("\nTree structure:\n");
    printTreePretty(myTree, 0);
    
    printf("\nChecking if tree is empty: %s\n", 
           isEmpty(myTree) ? "Yes" : "No");
    
    printf("\nTrying to remove non-existent element (1):\n");
    myTree = removeNode(myTree, 1);
    printf("Tree after removal attempt: ");
    printTree(myTree);
    printf("\n");
    
    printf("\nRemoving leaf node (2):\n");
    myTree = removeNode(myTree, 2);
    printf("Tree after removal: ");
    printTree(myTree);
    printf("\n");
    printTreePretty(myTree, 0);
    
    printf("\nRemoving node with one child (7):\n");
    myTree = removeNode(myTree, 7);
    printf("Tree after removal: ");
    printTree(myTree);
    printf("\n");
    printTreePretty(myTree, 0);
    
    printf("\nRemoving root node (5):\n");
    myTree = removeNode(myTree, 5);
    printf("Tree after removal: ");
    printTree(myTree);
    printf("\n");
    printTreePretty(myTree, 0);
    
    printf("\nRemoving all remaining elements:\n");
    myTree = removeNode(myTree, 3);
    myTree = removeNode(myTree, 4);
    myTree = removeNode(myTree, 6);
    
    printf("Tree after all removals: ");
    printTree(myTree);
    printf("\n");
    
    printf("\nChecking if tree is empty: %s\n", 
           isEmpty(myTree) ? "Yes" : "No");
    
    printf("\nAdding elements to empty tree:\n");
    myTree = add(myTree, 10);
    myTree = add(myTree, 8);
    myTree = add(myTree, 12);
    
    printf("Tree after additions: ");
    printTree(myTree);
    printf("\n");
    printTreePretty(myTree, 0);
    
    printf("\nCleaning up memory...\n");
    destroyRecursive(myTree);
    
    printf("Testing completed!\n");
}