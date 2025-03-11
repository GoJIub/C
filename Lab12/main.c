#include <stdio.h>

int pow_10(int n) {

    if (n <= 0)
        return 1;
    return 10 * pow_10(n - 1);
}

int length(int n) {

    int c = 1;

    while (n < -10 || n > 10) {
        c++;
        n /= 10;
    }
    return c;
}

int find_first_null(int n, int c) {

    while (n) {
        if (n % 10 == 0)
            return c;
        n /= 10;
        c++;
    }

    return -1;
}

int find_last_null(int n, int c) {

    n = n / pow_10(c);

    while (n) {
        if (n % 10 != 0)
            return c - 1;
        n /= 10;
        c++;
    }
}

int main() {

    int number;

    while (scanf("%d", &number) != EOF) {

        int len = length(number);
        int first_null = find_first_null(number, 0);
        
        if (first_null == -1) {
            printf("%d\n",number);
            continue;
        }

        int last_null = find_last_null(number, first_null);
        int nulls = last_null - first_null + 1;
        int center = len / 2 + len % 2 - 1;

        if (center > last_null)
            number = number / pow_10(center + 1) * pow_10(center + 1) + number % pow_10(center + 1) / pow_10(last_null + 1) * pow_10(first_null) + number % pow_10(first_null + 1);

        else
            number = number / pow_10(last_null + 1) * pow_10(last_null + 1) + number % pow_10(first_null) / pow_10(first_null - last_null + center) * pow_10(center + 1) + number % pow_10(first_null - last_null + center);
        
        printf("%d\n",number);
    }
}