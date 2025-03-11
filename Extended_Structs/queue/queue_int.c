#include "queue_int.h"
#include <stdlib.h>

queue_int* qint_create(int max_len) {
  queue_int* res = malloc(sizeof(queue_int));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(int) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  res -> start = 0;
  return res;
}

static int grow(queue_int* obj) {
  int new_max_len = obj -> max_len * 2;
  int* new_buf = realloc(obj -> buf, sizeof(int) * new_max_len);
  if (new_buf == NULL) return 0;
  for (int i = obj -> max_len - 1; i >= obj -> start; i--)
    new_buf[new_max_len - obj -> len + i] = new_buf[i];
  obj -> start += new_max_len - obj -> max_len;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void qint_destroy(queue_int* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int qint_is_empty(queue_int* obj) {
  return obj -> len == 0;
}

int qint_push_back(queue_int* obj, int value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[(obj -> len + obj -> start) % obj -> max_len] = value;
  obj -> len++;
  return 1;
}

int qint_pop_front(queue_int* obj) {
  int value = obj -> buf[obj -> start];
  obj -> start = (obj -> start + 1) % obj -> max_len;
  obj -> len--;
  return value;
}