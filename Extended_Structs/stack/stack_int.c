#include "stack_int.h"
#include <stdlib.h>

stack_int* sint_create(int max_len) {
  stack_int* res = malloc(sizeof(stack_int));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(int) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  return res;
}

static int grow(stack_int* obj) {
  int new_max_len = obj -> max_len * 2;
  int* new_buf = realloc(obj -> buf, sizeof(int) * new_max_len);
  if (new_buf == NULL) return 0;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void sint_destroy(stack_int* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int sint_is_empty_stack(stack_int* obj) {
  return obj -> len == 0;
}

int sint_push_back(stack_int* obj, int value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[obj -> len] = value;
  obj -> len++;
  return 1;
}

int sint_pop_back_stack(stack_int* obj) {
  int value = obj -> buf[obj -> len - 1];
  obj -> len--;
  return value;
}