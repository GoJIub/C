#include "binaryTree/tree.h"
#include <stdio.h>
#include <float.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    tree t = createEmpty();
    int choice;
    double val;
    int level;

    while (1) {
        printf("\nOptions:\n");
        printf("  1. Add node\n");
        printf("  2. Remove node\n");
        printf("  3. Visualize tree\n");
        printf("  4. Get tree power\n");
        printf("  5. Exit\n");
        printf("Choose an action: ");

        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Invalid input. Please enter a number between 1 and 5: ");
            clearInputBuffer();
        }

        clearInputBuffer();
        printf("\n");

        switch (choice) {
            case 1: {
                printf("Enter value: ");
                while (scanf("%lf", &val) != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                }
                clearInputBuffer();

                int result = addNode(&t, val);

                if (result == 1) 
                    printf("Node %.2f was added.\n", val);
                else if (result == 0 && t != NULL)
                    printf("Node already exists.\n");
                else
                    printf("Failed to add node.\n");
                
                break;
            }

            case 2: {
                printf("Enter value to remove: ");
                while (scanf("%lf", &val) != 1) {
                    printf("Invalid input. Please enter a valid number: ");
                    clearInputBuffer();
                }
                clearInputBuffer();
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
                destroyTree(t);
                printf("Goodbye.\n");
                return 0;
            }
        }
    }
}