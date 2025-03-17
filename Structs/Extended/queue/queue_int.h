#pragma once

typedef struct {
    int* buf;
    int max_len;
    int len;
    int start;
} queue_int;

queue_int* qint_create(int max_len);
void qint_destroy(queue_int* obj);
int qint_is_empty(queue_int* obj);
int qint_push_back(queue_int* obj, int value);
int qint_pop_front(queue_int* obj);