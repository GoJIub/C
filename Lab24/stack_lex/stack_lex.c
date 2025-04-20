#include "stack_lex.h"
#include <stdlib.h>

stack_lex* slex_create(int max_len) {
  stack_lex* res = malloc(sizeof(stack_lex));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(char) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  return res;
}

static int grow(stack_lex* obj) {
  int new_max_len = obj -> max_len * 2;
  char* new_buf = realloc(obj -> buf, sizeof(char) * new_max_len);
  if (new_buf == NULL) return 0;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void slex_destroy(stack_lex* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int slex_is_empty(stack_lex* obj) {
  return obj -> len == 0;
}

int slex_push_back(stack_lex* obj, char value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[obj -> len] = value;
  obj -> len++;
  return 1;
}

char slex_pop_back(stack_lex* obj) {
  char value = obj -> buf[obj -> len - 1];
  obj -> len--;
  return value;
}

char slex_top(stack_lex* obj) {
  return obj -> buf[obj -> len - 1];
}