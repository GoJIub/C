#pragma once

typedef struct elem elem;
struct elem {
    double val;
    elem* next;
};

typedef struct {
    elem* first;
    elem* last;
} list_dbl;

typedef struct {
    list_dbl* l;
    elem* prev;
} iter;

iter ldbl_begin(list_dbl* l);
iter ldbl_end(list_dbl* l);
iter ldbl_iter_move_next(iter it);
int ldbl_iter_equal(iter it1, iter it2);
double ldbl_iter_get(iter it);
void ldbl_iter_set(iter it, double val);
void ldbl_iter_insert(iter it, double val);
void ldbl_iter_remove(iter it);