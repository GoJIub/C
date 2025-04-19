#pragma once

typedef struct {
    int* buf;
    int size;
} vector_int;

vector_int* vint_create(int size);
void vint_destroy(vector_int* obj);
int vint_get_size(vector_int* obj);
int vint_set_size(vector_int* obj, int size);
int vint_get(vector_int* obj, int i);
void vint_set(vector_int* obj, int i, int val);

int vint_push_back(vector_int* obj, int val);
int vint_pop_back(vector_int* obj);