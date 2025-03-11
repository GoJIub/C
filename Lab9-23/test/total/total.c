#include <stdio.h>
#include <stdbool.h>
#include "../../mathlib.h"

int main() {

    bool check = false;
    int i0, j0, l0;
    scanf("%d %d %d", &i0, &j0, &l0);
    int i, j, l;
    int K;

    for (int k = 0; k <= 50; k++) {
        if (in_triangle(i0, j0)) {
            check = true;
            K = k;
            break;
        }

        i = mod(min(max(min(i0 - j0, i0 - l0), j0 - l0), i0 - k), 30);
        j = mod(max(min(max(i0 - j0, i0 - l0), j0 - l0), i0 - k), 30);
        l = mod(i0, 30) - mod(j0, 30) + mod(l0, 30) - mod(k, 30);

        i0 = i;
        j0 = j;
        l0 = l;

        printf("k = %d, i = %d, j = %d, l = %d\n", k, i, j ,l);
    }

    if (check)
        printf("Hit. k = %d, i = %d, j = %d, l = %d\n", K, i0, j0, l0);
    else
        printf("Miss. i = %d, j = %d, l = %d\n", i0, j0, l0);
}