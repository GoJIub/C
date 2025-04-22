#include "binaryTree/tree.h"
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exitProgram(tree t) {
    destroyTree(t);
    printf("Exiting program.\n");
    exit(0);
}

int main() {
    tree t = createEmpty();
    int choice;
    double val;

    while (1) {
        printf("\nOptions:\n");
        printf("  1. Add node\n");
        printf("  2. Remove node\n");
        printf("  3. Visualize tree\n");
        printf("  4. Get tree power\n");
        printf("  5. Exit\n");
        printf("Choose an action: ");

        int scanResult = scanf("%d", &choice);
        if (scanResult == EOF || feof(stdin)) exitProgram(t);
        if (scanResult != 1 || choice < 1 || choice > 5) {
            printf("Invalid input. Please enter a number between 1 and 5: ");
            clearInputBuffer();
            continue;
        }
        int c = getchar();
        if (c != '\n') {
            printf("Invalid input. Please enter exactly one number: ");
            clearInputBuffer();
            continue;
        }

        printf("\n");

        switch (choice) {
            case 1: {
                printf("Enter value: ");
                scanResult = scanf("%lf", &val);
                if (scanResult == EOF || feof(stdin)) exitProgram(t);
                if (scanResult != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                    break;
                }
                c = getchar();
                if (c != '\n') {
                    printf("Invalid input. Please enter exactly one number: ");
                    clearInputBuffer();
                    break;
                }

                int result = addNode(&t, val);
                if (result == 1) printf("Node %.2f was added.\n", val);
                else if (result == 0 && t != NULL) printf("Node already exists.\n");
                else printf("Failed to add node.\n");
                break;
            }

            case 2: {
                printf("Enter value to remove: ");
                scanResult = scanf("%lf", &val);
                if (scanResult == EOF || feof(stdin)) exitProgram(t);
                if (scanResult != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                    break;
                }
                c = getchar();
                if (c != '\n') {
                    printf("Invalid input. Please enter exactly one number: ");
                    clearInputBuffer();
                    break;
                }

                t = removeNode(t, val);
                printf("Node %.2f was removed.\n", val);
                break;
            }

            case 3: {
                printf("Tree:\n");
                printTree(t, 0);
                break;
            }

            case 4: {
                int power = getPower(t);
                printf("Power: %d\n", power);
                break;
            }

            case 5: {
                exitProgram(t);
                break;
            }
        }
    }
}