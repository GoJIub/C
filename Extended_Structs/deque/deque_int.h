#pragma once

typedef struct {
    int* buf;
    int max_len;
    int len;
    int start;
} deque_int;

deque_int* dint_create(int max_len);
void dint_destroy(deque_int* obj);
int dint_is_empty(deque_int* obj);
int dint_push_back(deque_int* obj, int value);
int dint_push_front(deque_int* obj, int value);
int dint_pop_back(deque_int* obj);
int dint_pop_front(deque_int* obj);