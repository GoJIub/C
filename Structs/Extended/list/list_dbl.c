#include "list_dbl.h"
#include <stdlib.h>


list_dbl* ldbl_create() {
    list_dbl* obj = malloc(sizeof(list_dbl));
    obj -> first = NULL;
    obj -> last = NULL;
    return obj;
}

void ldbl_destroy(list_dbl* obj) {
    elem* e = obj -> first;
    while (e != NULL) {
        elem* next = e -> next;
        free(e);
        e = next;
    }
    free(obj);
}

iter ldbl_begin(list_dbl* obj) {
    return (iter){.l = obj, .prev = NULL};
}

iter ldbl_end(list_dbl* obj) {
    return (iter){.l = obj, .prev = obj -> last};
}

iter ldbl_iter_move_next(iter it) {
    it.prev = it.prev == NULL ? it.l -> first : it.prev -> next;
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

void ldbl_iter_insert(iter it, double val) {
    elem* new_elem = malloc(sizeof(elem));
    new_elem -> val = val;
    if (it.prev == NULL) {
        new_elem -> next = it.l -> first;
        it.l -> first = new_elem;
        if (it.l -> last == NULL) it.l -> last = new_elem;
    } else {
        new_elem -> next = it.prev -> next;
        it.prev -> next = new_elem;
        if (it.l -> last == it.prev) it.l -> last = new_elem;
    }
}

void ldbl_iter_remove(iter it) {
    if (it.prev == NULL) {
        elem* e = it.l -> first;
        it.l -> first = e -> next;
        if (it.l -> first == NULL) it.l -> last = NULL;
        free(e);
    } else {
        elem* e = it.prev -> next;
        it.prev -> next = e -> next;
        if (e -> next == NULL) it.l -> last = it.prev;
        free(e);
    }
}
