#include "mathlib.h"

int div(int a ,int b) {
    if (a >= 0) {
        if (b > 0)
            return a / b;
        if (a % b != 0)
            return a / b - 1;
        return a / b;
    }
    if (b < 0)
        return a / b;
    if (a % b != 0)
        return a / b - 1;
    return a / b;
}

int mod(int a ,int b) {
    return a - div(a, b) * b;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int in_triangle(int a, int b) {
    if (a <= 0 && a >= -10) {
        if (b <= 20 && b >= 0) {
            if (b > 10) {
                if (b <= -a + 10)
                    return 1;
            }
            else {
                if (b >= a + 10)
                    return 1;
            }
        }
    }
    return 0;
}