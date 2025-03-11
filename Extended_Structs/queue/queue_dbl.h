#pragma once

typedef struct {
    double* buf;
    int max_len;
    int len;
    int start;
} queue_dbl;

queue_dbl* qdbl_create(int max_len);
void qdbl_destroy(queue_dbl* obj);
int qdbl_is_empty(queue_dbl* obj);
int qdbl_push_back(queue_dbl* obj, double value);
double qdbl_pop_front(queue_dbl* obj);