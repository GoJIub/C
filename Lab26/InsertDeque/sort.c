#include "sort.h"
#include "deque_str.h"

int step_of_a_sort(deque_str* obj) {
    if (dstr_is_empty(obj)) return 0;
    char* s1 = dstr_pop_front(obj);
    if (dstr_is_empty(obj)) {
        dstr_push_back(obj, s1);
        return 0;
    }
    char* s2 = dstr_pop_front(obj);
    deque_str* storage = dstr_create(10);
    if (!storage) {
        dstr_push_front(obj, s1);
        dstr_push_front(obj, s2);
        return 0;
    }
    while (strcmp(s2, s1) >= 0) {
        dstr_push_back(storage, s1);
        s1 = s2;
        if (dstr_is_empty(obj)) {
            dstr_push_back(storage, s1);
            while (!dstr_is_empty(storage)) dstr_push_back(obj, dstr_pop_front(storage));
            dstr_destroy(storage);
            return 0;
        }
        s2 = dstr_pop_front(obj);
    }
    dstr_push_back(storage, s1);
    while (!dstr_is_empty(obj)) dstr_push_back(storage, dstr_pop_front(obj));
    int was_added = 0;
    while (!dstr_is_empty(storage)) {
        s1 = dstr_pop_front(storage);
        if (strcmp(s1, s2) <= 0) {
            dstr_push_back(obj, s1);
        } else if (!was_added) {
            dstr_push_back(obj, s2);
            was_added = 1;
            dstr_push_back(obj, s1);
        } else {
            dstr_push_back(obj, s1);
        }
    }
    if (!was_added) dstr_push_back(obj, s2);
    dstr_destroy(storage);
    return 1;
}

void insert_sort(deque_str* obj) {
    while (step_of_a_sort(obj));
}