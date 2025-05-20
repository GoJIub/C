#pragma once

#define MAX_SIZE 100
#define MAX_TEXT 256

typedef struct {
    double w, x, y, z;
} quaternion;

typedef struct {
    int index;
    quaternion q;
} key;

typedef struct {
    int index;
    char text[MAX_TEXT];
} record;

int compare_quaternion(const quaternion *a, const quaternion *b);
int read_keys(const char *filename, key *keys, int max_size);
int read_table(const char *filename, record *table, int max_size);
void print_keys(const key *keys, int n);
void print_table(const record *table, int n);
void odd_even_sort(key *keys, record *table, int n);
int binary_search(const key *keys, int n, const quaternion *target);
int compare_poem(const record *table, int n, const char *reference_file);