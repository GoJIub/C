#pragma once

typedef struct {
    int max_len;
    int len;
    int start;
    char** buf;
} deque_str;

deque_str* dstr_create(int max_len);
void dstr_destroy(deque_str* obj);
int dstr_is_empty(deque_str* obj);
int dstr_push_back(deque_str* obj, const char* value);
int dstr_push_front(deque_str* obj, const char* value);
char* dstr_pop_back(deque_str* obj);
char* dstr_pop_front(deque_str* obj);