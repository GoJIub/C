#include "stack_dbl.h"
#include <stdlib.h>

stack_dbl* sdbl_create(int max_len) {
  stack_dbl* res = malloc(sizeof(stack_dbl));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(double) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  return res;
}

static int grow(stack_dbl* obj) {
  int new_max_len = obj -> max_len * 2;
  double* new_buf = realloc(obj -> buf, sizeof(double) * new_max_len);
  if (new_buf == NULL) return 0;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void sdbl_destroy(stack_dbl* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int sdbl_is_empty_stack(stack_dbl* obj) {
  return obj -> len == 0;
}

int sdbl_push_back(stack_dbl* obj, double value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[obj -> len] = value;
  obj -> len++;
  return 1;
}

double sdbl_pop_back_stack(stack_dbl* obj) {
  double value = obj -> buf[obj -> len - 1];
  obj -> len--;
  return value;
}