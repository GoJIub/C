#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tools.h"

int main() {
    key keys[MAX_SIZE];
    record table[MAX_SIZE];
    int n;

    // Тест 1: верный порядок
    printf("\n=== Test 1: Sorted Keys ===\n");
    n = read_keys("data/sorted/keys_sorted.txt", keys, MAX_SIZE);
    if (n == 0) {
        printf("Test 1 failed due to empty key table\n");
        return 1;
    }
    int table_size = read_table("data/sorted/table_sorted.txt", table, MAX_SIZE);
    if (table_size == 0) {
        printf("Test 1 failed due to empty main table\n");
        return 1;
    }
    if (table_size != n) {
        printf("Warning: Key table size (%d) differs from main table size (%d)\n", n, table_size);
        n = (n < table_size) ? n : table_size;
    }
    printf("Initial state:\n");
    print_keys(keys, n);
    print_table(table, n);
    odd_even_sort(keys, table, n);
    printf("\nAfter sorting:\n");
    print_keys(keys, n);
    print_table(table, n);
    printf("\nRestored poem:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", table[i].text);
    }
    printf("\nComparison with reference:\n");
    compare_poem(table, n, "data/table.txt");

    // Поиск
    printf("\nEnter keys to search (w x y z, 0 0 0 0 to terminate):\n");
    quaternion target;
    while (scanf("%lf %lf %lf %lf", &target.w, &target.x, &target.y, &target.z) == 4) {
        if (target.w == 0 && target.x == 0 && target.y == 0 && target.z == 0) break;
        int idx = binary_search(keys, n, &target);
        if (idx >= 0) {
            printf("Found: Index: %d, Text: %s\n", keys[idx].index, table[keys[idx].index].text);
        } else {
            printf("Not found\n");
        }
    }

    // Тест 2: обратный порядок
    printf("\n=== Test 2: Reverse Keys ===\n");
    n = read_keys("data/reverse/keys_reverse.txt", keys, MAX_SIZE);
    if (n == 0) {
        printf("Test 2 failed due to empty key table\n");
        return 1;
    }
    table_size = read_table("data/reverse/table_reverse.txt", table, MAX_SIZE);
    if (table_size == 0) {
        printf("Test 2 failed due to empty main table\n");
        return 1;
    }
    if (table_size != n) {
        printf("Warning: Key table size (%d) differs from main table size (%d)\n", n, table_size);
        n = (n < table_size) ? n : table_size;
    }
    printf("Initial state:\n");
    print_keys(keys, n);
    print_table(table, n);
    odd_even_sort(keys, table, n);
    printf("\nAfter sorting:\n");
    print_keys(keys, n);
    print_table(table, n);
    printf("\nRestored poem:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", table[i].text);
    }
    printf("\nComparison with reference:\n");
    compare_poem(table, n, "data/table.txt");

    // Поиск
    printf("\nEnter keys to search (w x y z, 0 0 0 0 to terminate):\n");
    while (scanf("%lf %lf %lf %lf", &target.w, &target.x, &target.y, &target.z) == 4) {
        if (target.w == 0 && target.x == 0 && target.y == 0 && target.z == 0) break;
        int idx = binary_search(keys, n, &target);
        if (idx >= 0) {
            printf("Found: Index: %d, Text: %s\n", keys[idx].index, table[keys[idx].index].text);
        } else {
            printf("Not found\n");
        }
    }

    // Тест 3: солянка
    printf("\n=== Test 3: Shuffled Indices ===\n");
    n = read_keys("data/shuffled/keys_shuffled.txt", keys, MAX_SIZE);
    if (n == 0) {
        printf("Test 3 failed due to empty key table\n");
        return 1;
    }
    table_size = read_table("data/shuffled/table_shuffled.txt", table, MAX_SIZE);
    if (table_size == 0) {
        printf("Test 3 failed due to empty main table\n");
        return 1;
    }
    if (table_size != n) {
        printf("Warning: Key table size (%d) differs from main table size (%d)\n", n, table_size);
        n = (n < table_size) ? n : table_size;
    }
    printf("Initial state:\n");
    print_keys(keys, n);
    print_table(table, n);
    odd_even_sort(keys, table, n);
    printf("\nAfter sorting:\n");
    print_keys(keys, n);
    print_table(table, n);
    printf("\nRestored poem:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", table[i].text);
    }
    printf("\nComparison with reference:\n");
    compare_poem(table, n, "data/table.txt");

    // Поиск
    printf("\nEnter keys to search (w x y z, 0 0 0 0 to terminate):\n");
    while (scanf("%lf %lf %lf %lf", &target.w, &target.x, &target.y, &target.z) == 4) {
        if (target.w == 0 && target.x == 0 && target.y == 0 && target.z == 0) break;
        int idx = binary_search(keys, n, &target);
        if (idx >= 0) {
            printf("Found: Index: %d, Text: %s\n", keys[idx].index, table[keys[idx].index].text);
        } else {
            printf("Not found\n");
        }
    }
}