#include <stdio.h>

int main() {
    char chr[11] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й"};
    for (int i = 0; i < 11; i++)
        printf("%d\n", chr[i]);
}