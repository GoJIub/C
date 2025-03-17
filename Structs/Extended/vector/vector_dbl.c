#include "vector_dbl.h"
#include <stdlib.h>

vector_dbl* vdbl_create(int size) {
    vector_dbl* res = malloc(sizeof(vector_dbl));
    if (res == NULL) return NULL;
    res -> buf = malloc(sizeof(double) * size);
    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> size = size;
    return res;
}

void vdbl_destroy(vector_dbl* obj) {
    free(obj -> buf);
    free(obj);
}

int vdbl_get_size(vector_dbl* obj) {
    return obj -> size;
}

int vdbl_set_size(vector_dbl* obj, int size) {
    double* new_buf = realloc(obj -> buf, sizeof(double) * size);
    if (size && new_buf == NULL) return 0;
    obj -> buf = new_buf;
    for (int i = obj -> size; i < size; i++) obj -> buf[i] = 0;
    obj -> size = size;
    return 1;
}

double vdbl_get(vector_dbl* obj, int i) {
    return obj -> buf[i];
}

void vdbl_set(vector_dbl* obj, int i, double val) {
    obj -> buf[i] = val;
}