#include "vector_int.h"
#include <stdlib.h>

vector_int* vint_create(int size) {
    vector_int* res = malloc(sizeof(vector_int));
    if (res == NULL) return NULL;
    res -> buf = malloc(sizeof(int) * size);
    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> size = size;
    return res;
}

void vint_destroy(vector_int* obj) {
    free(obj -> buf);
    free(obj);
}

int vint_get_size(vector_int* obj) {
    return obj -> size;
}

int vint_set_size(vector_int* obj, int size) {
    int* new_buf = realloc(obj -> buf, sizeof(int) * size);
    if (size && new_buf == NULL) return 0;
    obj -> buf = new_buf;
    for (int i = obj -> size; i < size; i++) obj -> buf[i] = 0;
    obj -> size = size;
    return 1;
}

int vint_get(vector_int* obj, int i) {
    return obj -> buf[i];
}

void vint_set(vector_int* obj, int i, int val) {
    obj -> buf[i] = val;
}

int vint_push_back(vector_int* obj, int val) {
    if (!vint_set_size(obj, vint_get_size(obj) + 1)) return 0;
    vint_set(obj, vint_get_size(obj) - 1, val);
    return 1;
}

int vint_pop_back(vector_int* obj) {
    int val = vint_get(obj, vint_get_size(obj) - 1);
    vint_set_size(obj, vint_get_size(obj) - 1);
    return val;
}