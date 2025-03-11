#include <stdio.h>
#include "mathlib.h"


int main() {

    char x = 'x';
    char y;

    __asm__ (
        "movb %1, %0\n"
        // "addb %%eax, %0" // Неизвестный регистр %%eax
        : "=r"(y)
        : "r"(x)
    );

    printf("y = %c\n", y);

    int d = div(17, 5);
    printf("%d\n", d);

    int md = mod(17, 5);
    printf("%d\n", md);

    int mx = max(17, 5);
    printf("%d\n", mx);

    int mn = min(17, 5);
    printf("%d\n", mn);
    
}