#include <stdio.h>
#include "mathlib.h"

// int i_am_everywhere = 2; // Переменная определяется сразу в двух файлах

int main() {

    // int div(double a, double b); // Такая же функция в mathlib.h имеет другие сигнатуры

    int d = div(17, 5);
    printf("%d\n", d);

    int md = mod(17, 5);
    printf("%d\n", md);

    int mx = max(17, 5);
    printf("%d\n", mx);

    int mn = min(17, 5);
    printf("%d\n", mn);
    
}