#include "stack_tree.h"
#include <stdlib.h>

stack_tree* stree_create(int max_len) {
  stack_tree* res = malloc(sizeof(stack_tree));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(tree) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  return res;
}

static int grow(stack_tree* obj) {
  int new_max_len = obj -> max_len * 2;
  tree* new_buf = realloc(obj -> buf, sizeof(tree) * new_max_len);
  if (new_buf == NULL) return 0;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void stree_destroy(stack_tree* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int stree_is_empty(stack_tree* obj) {
  return obj -> len == 0;
}

int stree_push_back(stack_tree* obj, tree value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[obj -> len] = value;
  obj -> len++;
  return 1;
}

tree stree_pop_back(stack_tree* obj) {
  tree value = obj -> buf[obj -> len - 1];
  obj -> len--;
  return value;
}

tree stree_top(stack_tree* obj) {
  return obj -> buf[0];
}