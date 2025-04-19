#include "queue_tree.h"
#include "../binaryTree/tree.h"
#include <stdlib.h>

queue_tree* qtree_create(int max_len) {
  queue_tree* res = malloc(sizeof(queue_tree));
  if (res == NULL) return NULL;
  res -> max_len = max_len;
  res -> buf = malloc(sizeof(tree) * max_len);
  if (res -> buf == NULL) {
      free(res);
      return NULL;
  }
  res -> len = 0;
  res -> start = 0;
  return res;
}

static int grow(queue_tree* obj) {
  int new_max_len = obj -> max_len * 2;
  tree* new_buf = realloc(obj -> buf, sizeof(tree) * new_max_len);
  if (new_buf == NULL) return 0;
  for (int i = obj -> max_len - 1; i >= obj -> start; i--)
    new_buf[new_max_len - obj -> len + i] = new_buf[i];
  obj -> start += new_max_len - obj -> max_len;
  obj -> buf = new_buf;
  obj -> max_len = new_max_len;
  return 1;
}

void qtree_destroy(queue_tree* obj) {
  if (!obj) return;
  free(obj -> buf);
  free(obj);
}

int qtree_is_empty(queue_tree* obj) {
  return obj -> len == 0;
}

int qtree_get_size(queue_tree* obj) {
    return obj -> len;
}

int qtree_push_back(queue_tree* obj, tree value) {
  if (obj -> len == obj -> max_len)
    if (!grow(obj)) return 0;
  obj -> buf[(obj -> len + obj -> start) % obj -> max_len] = value;
  obj -> len++;
  return 1;
}

tree qtree_pop_front(queue_tree* obj) {
  tree value = obj -> buf[obj -> start];
  obj -> start = (obj -> start + 1) % obj -> max_len;
  obj -> len--;
  return value;
}

tree qtree_top(queue_tree* obj) {
  return obj -> buf[obj -> start];
}