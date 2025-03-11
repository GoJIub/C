#pragma once

typedef struct {
    double* buf;
    int size;
    int start;
    int max_size;
} absolute_dbl;

absolute_dbl* adbl_create(int size);
void adbl_destroy(absolute_dbl* obj);
int adbl_get_size(absolute_dbl* obj);
int adbl_set_size(absolute_dbl* obj, int size);
double adbl_get(absolute_dbl* obj, int i);
void adbl_set(absolute_dbl* obj, int i, double val);
int adbl_is_empty(absolute_dbl* obj);
int adbl_push_back(absolute_dbl* obj, double value);
int adbl_push_front(absolute_dbl* obj, double value);
double adbl_pop_back(absolute_dbl* obj);
double adbl_pop_front(absolute_dbl* obj);