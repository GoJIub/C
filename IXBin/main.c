#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tools.h"

// Функция для выполнения теста
int run_test(const char *test_name, const char *keys_file, const char *table_file, const char *ref_file, key *keys, record *table, int *n, int silent) {
    if (!silent) {
        printf("\n=== Test: %s ===\n", test_name);
    }
    
    *n = read_keys(keys_file, keys, MAX_SIZE);
    if (*n == 0) {
        printf("Test %s: Failed due to empty key table\n", test_name);
        return 1;
    }
    int table_size = read_table(table_file, table, MAX_SIZE);
    if (table_size == 0) {
        printf("Test %s: Failed due to empty main table\n", test_name);
        return 1;
    }
    if (table_size != *n) {
        printf("Warning: Key table size (%d) differs from main table size (%d)\n", *n, table_size);
        *n = (*n < table_size) ? *n : table_size;
    }
    
    if (!silent) {
        printf("Initial state:\n");
        print_keys(keys, *n);
        print_table(table, *n);
    }
    
    odd_even_sort(keys, table, *n);
    
    if (!silent) {
        printf("\nAfter sorting:\n");
        print_keys(keys, *n);
        print_table(table, *n);
        
        printf("\nRestored poem:\n");
        for (int i = 0; i < *n; i++) {
            printf("%s\n", table[i].text);
        }
        
        printf("\nComparison with reference:\n");
    }
    
    int result = compare_poem(table, *n, ref_file);
    if (silent) {
        printf("Test %s: %s\n", test_name, result ? "Passed" : "Failed");
    }
    
    if (!result) {
        return 1;
    }
    
    if (!silent) {
        printf("\nEnter keys to search (w x y z, 0 0 0 0 to terminate):\n");
        quaternion target;
        while (scanf("%lf %lf %lf %lf", &target.w, &target.x, &target.y, &target.z) == 4) {
            if (target.w == 0 && target.x == 0 && target.y == 0 && target.z == 0) break;
            int idx = binary_search(keys, *n, &target);
            if (idx >= 0) {
                printf("Found: Index: %d, Text: %s\n", keys[idx].index, table[keys[idx].index].text);
            } else {
                printf("Not found\n");
            }
        }
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    int silent = 0;
    if (argc > 1 && strcmp(argv[1], "-s") == 0) {
        silent = 1;
    }

    key keys[MAX_SIZE];
    record table[MAX_SIZE];
    int n;

    // Преобразование текстовых файлов в бинарные
    if (!silent) {
        printf("=== Converting text files to binary ===\n");
    }
    const char *sets[] = {"sorted", "reverse", "shuffled"};
    const char *ref_txt = "data/table.txt";
    const char *ref_bin = "data/table.bin";
    
    // Преобразование эталонной таблицы
    FILE *ref_bin_file = fopen(ref_bin, "rb");
    if (!ref_bin_file) {
        n = read_table_text(ref_txt, table, MAX_SIZE);
        if (n == 0) {
            printf("Failed to read %s\n", ref_txt);
            return 1;
        }
        if (!save_table(ref_bin, table, n)) {
            printf("Failed to save %s\n", ref_bin);
            return 1;
        }
        printf("Converted %s to %s\n", ref_txt, ref_bin);
    } else {
        fclose(ref_bin_file);
        if (!silent) printf("%s already exists, skipping conversion\n", ref_bin);
    }

    // Преобразование файлов для каждого набора
    for (int set = 0; set < 3; set++) {
        char keys_txt[256], keys_bin[256], table_txt[256], table_bin[256];
        snprintf(keys_txt, sizeof(keys_txt), "data/%s/keys_%s.txt", sets[set], sets[set]);
        snprintf(keys_bin, sizeof(keys_bin), "data/%s/keys_%s.bin", sets[set], sets[set]);
        snprintf(table_txt, sizeof(table_txt), "data/%s/table_%s.txt", sets[set], sets[set]);
        snprintf(table_bin, sizeof(table_bin), "data/%s/table_%s.bin", sets[set], sets[set]);

        FILE *keys_bin_file = fopen(keys_bin, "rb");
        FILE *table_bin_file = fopen(table_bin, "rb");
        if (!keys_bin_file || !table_bin_file) {
            if (keys_bin_file) fclose(keys_bin_file);
            if (table_bin_file) fclose(table_bin_file);

            // Конвертация ключей
            n = read_keys_text(keys_txt, keys, MAX_SIZE);
            if (n == 0) {
                printf("Failed to read %s\n", keys_txt);
                return 1;
            }
            if (!save_keys(keys_bin, keys, n)) {
                printf("Failed to save %s\n", keys_bin);
                return 1;
            }
            if (!silent) printf("Converted %s to %s\n", keys_txt, keys_bin);

            // Конвертация таблицы
            int table_size = read_table_text(table_txt, table, MAX_SIZE);
            if (table_size == 0) {
                printf("Failed to read %s\n", table_txt);
                return 1;
            }
            if (!save_table(table_bin, table, table_size)) {
                printf("Failed to save %s\n", table_bin);
                return 1;
            }
            if (!silent) printf("Converted %s to %s\n", table_txt, table_bin);
        } else {
            fclose(keys_bin_file);
            fclose(table_bin_file);
            if (!silent) printf("%s and %s already exist, skipping conversion\n", keys_bin, table_bin);
        }
    }

    // Выполнение тестов
    if (run_test("Sorted Keys", "data/sorted/keys_sorted.bin", "data/sorted/table_sorted.bin", "data/table.bin", keys, table, &n, silent)) {
        return 1;
    }
    if (run_test("Reverse Keys", "data/reverse/keys_reverse.bin", "data/reverse/table_reverse.bin", "data/table.bin", keys, table, &n, silent)) {
        return 1;
    }
    if (run_test("Shuffled Indices", "data/shuffled/keys_shuffled.bin", "data/shuffled/table_shuffled.bin", "data/table.bin", keys, table, &n, silent)) {
        return 1;
    }

    return 0;
}