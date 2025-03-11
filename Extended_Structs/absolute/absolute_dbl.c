#include "absolute_dbl.h"
#include <stdlib.h>

absolute_dbl* adbl_create(int size) {
    absolute_dbl* res = malloc(sizeof(absolute_dbl));
    if (res == NULL) return NULL;
    res -> buf = malloc(sizeof(double) * size);
    if (size && res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> max_size = size;
    res -> size = size;
    res -> start = 0;
    return res;
}

static int grow(absolute_dbl* obj) {
  int new_max_size = obj -> max_size * 2;
  double* new_buf = realloc(obj -> buf, sizeof(double) * new_max_size);
  if (new_buf == NULL) return 0;
  for (int i = obj -> max_size - 1; i >= obj -> start; i--)
    new_buf[new_max_size - obj -> size + i] = new_buf[i];
  obj -> start += new_max_size - obj -> max_size;
  obj -> buf = new_buf;
  obj -> max_size = new_max_size;
  return 1;
}

void adbl_destroy(absolute_dbl* obj) {
    free(obj -> buf);
    free(obj);
}

int adbl_get_size(absolute_dbl* obj) {
    return obj -> size;
}

int adbl_set_size(absolute_dbl* obj, int size) {
    if (size <= obj -> max_size) {
        for (int i = obj -> size; i < size; i++)
            obj -> buf[(i + obj -> start) % obj -> max_size] = 0;
        obj -> size = size;
        return 1;
    }
    double* new_buf = malloc(sizeof(double) * size);
    if (size && new_buf == NULL) return 0;
    for (int i = 0; i < obj -> size; i++) new_buf[i] = obj -> buf[(i + obj -> size) % obj -> max_size];
    free(obj -> buf);
    obj -> buf = new_buf;
    obj -> start = 0;
    obj -> size = size;
    obj -> max_size = size;
    return 1;
}

double adbl_get(absolute_dbl* obj, int i) {
    return obj -> buf[i];
}

void adbl_set(absolute_dbl* obj, int i, double val) {
    obj -> buf[i] = val;
}

void adbl_destroy(absolute_dbl* obj) {
  free(obj -> buf);
  free(obj);
}

int adbl_is_empty(absolute_dbl* obj) {
  return obj -> size == 0;
}

int adbl_push_back(absolute_dbl* obj, double value) {
  if (obj -> size == obj -> max_size)
    if (!grow(obj)) return 0;
  obj -> buf[(obj -> size + obj -> start) % obj -> max_size] = value;
  obj -> size++;
  return 1;
}

int adbl_push_front(absolute_dbl* obj, double value) {
  if (obj -> size == obj -> max_size)
    if (!grow(obj)) return 0;
  obj -> start = (obj -> start + obj -> max_size - 1) % obj -> max_size;
  obj -> buf[obj -> start] = value;
  obj -> size++;
  return 1;
}

double adbl_pop_back(absolute_dbl* obj) {
  double value = obj -> buf[(obj -> size + obj -> start - 1) % obj -> max_size];
  obj -> size--;
  return value;
}

double adbl_pop_front(absolute_dbl* obj) {
  double value = obj -> buf[obj -> start];
  obj -> start = (obj -> start + 1) % obj -> max_size;
  obj -> size--;
  return value;
}