#pragma once

typedef struct {
    double* buf;
    int max_len;
    int len;
    int start;
} deque_dbl;

deque_dbl* ddbl_create(int max_len);
void ddbl_destroy(deque_dbl* obj);
int ddbl_is_empty(deque_dbl* obj);
int ddbl_push_back(deque_dbl* obj, double value);
int ddbl_push_front(deque_dbl* obj, double value);
double ddbl_pop_back(deque_dbl* obj);
double ddbl_pop_front(deque_dbl* obj);