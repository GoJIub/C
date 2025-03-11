#include <stdio.h>
#include "mathlib.h"


int main() {

    // printf("%d\n", 17 / "5"); // Нельзя делить int на char

    int d = div(17, 5);
    printf("%d\n", d);

    int md = mod(17, 5);
    printf("%d\n", md);

    int mx = max(17, 5);
    printf("%d\n", mx);

    int mn = min(17, 5);
    printf("%d\n", mn);
    // printf("%d\n" mn); // Забыл запятую
}