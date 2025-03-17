#pragma once

typedef struct {
    int* buf;
    int max_len;
    int len;
} stack_int;

stack_int* sint_create(int max_len);
void sint_destroy(stack_int* obj);
int sint_is_empty(stack_int* obj);
int sint_push_back(stack_int* obj, int value);
int sint_pop_back(stack_int* obj);