#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tools.h"

// Сравнение кватернионов
int compare_quaternion(const quaternion *a, const quaternion *b) {
    if (a->w != b->w) return a->w < b->w ? -1 : 1;
    if (a->x != b->x) return a->x < b->x ? -1 : 1;
    if (a->y != b->y) return a->y < b->y ? -1 : 1;
    if (a->z != b->z) return a->z < b->z ? -1 : 1;
    return 0;
}

// Чтение ключей из текстового файла
int read_keys_text(const char *filename, key *keys, int max_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    int n = 0;
    while (n < max_size && fscanf(file, "%lf %lf %lf %lf",
        &keys[n].q.w, &keys[n].q.x, &keys[n].q.y, &keys[n].q.z) == 4) {
        keys[n].index = n;
        n++;
    }
    if (n == 0) {
        printf("Error: No valid data read from %s\n", filename);
    }
    fclose(file);
    return n;
}

// Чтение таблицы из текстового файла
int read_table_text(const char *filename, record *table, int max_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    int n = 0;
    char buffer[MAX_TEXT];
    while (n < max_size && fgets(buffer, MAX_TEXT, file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        table[n].index = n;
        strncpy(table[n].text, buffer, MAX_TEXT - 1);
        table[n].text[MAX_TEXT - 1] = '\0';
        n++;
    }
    if (n == 0) {
        printf("Error: No valid data read from %s\n", filename);
    }
    fclose(file);
    return n;
}

// Сохранение ключей в бинарный файл
int save_keys(const char *filename, const key *keys, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return 0;
    }
    size_t written = fwrite(keys, sizeof(key), size, file);
    fclose(file);
    if (written != size) {
        printf("Error: Failed to write %zu keys to %s\n", size, filename);
        return 0;
    }
    return 1;
}

// Сохранение таблицы в бинарный файл
int save_table(const char *filename, const record *table, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return 0;
    }
    size_t written = fwrite(table, sizeof(record), size, file);
    fclose(file);
    if (written != size) {
        printf("Error: Failed to write %zu records to %s\n", size, filename);
        return 0;
    }
    return 1;
}

// Чтение ключей из бинарного файла
int read_keys(const char *filename, key *keys, int max_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    int n = 0;
    while (n < max_size && fread(&keys[n], sizeof(key), 1, file) == 1) {
        n++;
    }
    fclose(file);
    if (n == 0) {
        printf("Error: No valid data read from %s\n", filename);
    }
    return n;
}

// Чтение таблицы из бинарного файла
int read_table(const char *filename, record *table, int max_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    int n = 0;
    while (n < max_size && fread(&table[n], sizeof(record), 1, file) == 1) {
        n++;
    }
    fclose(file);
    if (n == 0) {
        printf("Error: No valid data read from %s\n", filename);
    }
    return n;
}

// Печать таблицы ключей
void print_keys(const key *keys, int n) {
    printf("Key table:\n");
    if (n == 0) {
        printf("  (Empty table)\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("Index: %d, Key: (%.2f, %.2f, %.2f, %.2f)\n",
               keys[i].index, keys[i].q.w, keys[i].q.x, keys[i].q.y, keys[i].q.z);
    }
}

// Печать основной таблицы
void print_table(const record *table, int n) {
    printf("Main table:\n");
    if (n == 0) {
        printf("  (Empty table)\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("Index: %d, Text: %s\n", table[i].index, table[i].text);
    }
}

// Четно-нечетная сортировка транспозицией
void odd_even_sort(key *keys, record *table, int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        // Четная фаза
        for (int i = 0; i < n - 1; i += 2) {
            if (compare_quaternion(&keys[i].q, &keys[i + 1].q) > 0) {
                // Обмен ключей
                key temp_key = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = temp_key;
                // Обмен записей в таблице
                record temp_record = table[i];
                table[i] = table[i + 1];
                table[i + 1] = temp_record;
                sorted = 0;
            }
        }
        // Нечетная фаза
        for (int i = 1; i < n - 1; i += 2) {
            if (compare_quaternion(&keys[i].q, &keys[i + 1].q) > 0) {
                // Обмен ключей
                key temp_key = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = temp_key;
                // Обмен записей в таблице
                record temp_record = table[i];
                table[i] = table[i + 1];
                table[i + 1] = temp_record;
                sorted = 0;
            }
        }
    }
    // Обновление индексов
    for (int i = 0; i < n; i++) {
        keys[i].index = i;
        table[i].index = i;
    }
}

// Бинарный поиск
int binary_search(const key *keys, int n, const quaternion *target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_quaternion(&keys[mid].q, target);

        if (cmp == 0) {
            result = mid; // Найдено совпадение, продолжаем поиск влево
            right = mid - 1;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Сравнение восстановленного стихотворения с эталонным
int compare_poem(const record *table, int n, const char *reference_file) {
    record reference[MAX_SIZE];
    int ref_size = read_table(reference_file, reference, MAX_SIZE);
    if (ref_size != n) {
        printf("Comparison failed: Reference table size (%d) differs from restored table size (%d)\n", ref_size, n);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (strcmp(table[i].text, reference[i].text) != 0) {
            printf("Mismatch at index %d:\n", i);
            printf("  Restored: %s\n", table[i].text);
            printf("  Reference: %s\n", reference[i].text);
            return 0;
        }
    }
    printf("Poem restored correctly!\n");
    return 1;
}