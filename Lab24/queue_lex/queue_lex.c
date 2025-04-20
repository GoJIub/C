#include "queue_lex.h"
#include <stdlib.h>

queue_lex* qlex_create(int max_len) {
  queue_lex* res = malloc(sizeof(queue_lex));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(char) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  res -> start = 0;
  return res;
}

static int grow(queue_lex* obj) {
  int new_max_len = obj -> max_len * 2;
  char* new_buf = realloc(obj -> buf, sizeof(char) * new_max_len);
  if (new_buf == NULL) return 0;
  for (int i = obj -> max_len - 1; i >= obj -> start; i--)
    new_buf[new_max_len - obj -> len + i] = new_buf[i];
  obj -> start += new_max_len - obj -> max_len;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void qlex_destroy(queue_lex* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int qlex_is_empty(queue_lex* obj) {
  return obj -> len == 0;
}

int qlex_push_back(queue_lex* obj, char value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[(obj -> len + obj -> start) % obj -> max_len] = value;
  obj -> len++;
  return 1;
}

char qlex_pop_front(queue_lex* obj) {
  char value = obj -> buf[obj -> start];
  obj -> start = (obj -> start + 1) % obj -> max_len;
  obj -> len--;
  return value;
}

char qlex_top(queue_lex* obj) {
  return obj -> buf[obj -> start];
}