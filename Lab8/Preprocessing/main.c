#include <stdio.h>
#include "mathlib.h" // Внутри mathlib происходит вызов main.c, а то, что происходит дальше, можно увидеть там

// #include "doesn't_exist.h" // Такого файла просто не существует
// #Define abs(x) x > 0 ? x : -x // В названии ключевого слова допущена ошибка


int main() {

    int d = div(17, 5);
    printf("%d\n", d);

    int md = mod(17, 5);
    printf("%d\n", md);

    int mx = max(17, 5);
    printf("%d\n", mx);

    int mn = min(17, 5);
    printf("%d\n", mn);
    
}