#include "list_dbl.h"
#include <stdlib.h>

iter ldbl_begin(list_dbl* l) {
    return (iter){.l = l, .prev = NULL};
}

iter ldbl_end(list_dbl* l) {
    return (iter){.l = l, .prev = l -> last};
}

iter ldbl_iter_move_next(iter it) {
    it.prev =it.prev == NULL ? it.l -> first : it.prev -> next;
    return it;
}

int ldbl_iter_equal(iter it1, iter it2) {
    return it1.l == it2.l && it1.prev == it2.prev;
}

double ldbl_iter_get(iter it) {
    return it.prev == NULL ? it.l -> first -> val : it.prev -> next -> val;
}
void ldbl_iter_set(iter it, double val) {
    if (it.prev == NULL) it.l -> first -> val = val;
    else it.prev -> next -> val = val;
}
void ldbl_iter_insert(iter it, double val);
void ldbl_iter_remove(iter it);