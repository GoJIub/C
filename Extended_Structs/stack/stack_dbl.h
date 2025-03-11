#pragma once

typedef struct {
    double* buf;
    int max_len;
    int len;
} stack_dbl;

stack_dbl* sdbl_create(int max_len);
void sdbl_destroy(stack_dbl* obj);
int sdbl_is_empty(stack_dbl* obj);
int sdbl_push_back(stack_dbl* obj, double value);
double sdbl_pop_back(stack_dbl* obj);