#include <stdio.h>
#include "../../mathlib.h"

int main () {

    int a, b;
    scanf("%d %d", &a, &b);
    if (b == 0)
        printf("Division by zero\n");
    else
        printf("%d\n", div(a, b));
    
}