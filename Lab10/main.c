#include <stdio.h>

int my_pow(int base, int power);
void print(int l, int r);
void print_even(int l, int r);
void print_not_even(int l, int r);


// Прямая рекурсия
int my_pow(int base, int power) {
    if (power == 0)
        return 1;
    return base * my_pow(base, power - 1);
}

// Косвеннаяа рекурсия
void print(int l, int r) {
    if (l % 2 == 0)
        print_even(l, r);
    else
        print_not_even(l, r);
}

void print_even(int l, int r) {
    if (l > r){
        printf("\n");
        return;    
    }
    printf("%d - even, ", l);
    print_not_even(l + 1, r);
}

void print_not_even(int l, int r) {
    if (l > r){
        printf("\n");
        return;    
    }
    printf("%d - not even, ", l);
    print_even(l + 1, r);
}

// Тело
int main() {

    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", my_pow(a, b));
    print(a, b);
}