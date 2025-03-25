#include "../Structs/Extended/stack/stack_dbl.h"

double remove_max(stack_dbl* obj) {
    stack_dbl* storage = create();
    double cur_max = sdbl_pop_back(obj);
    sdbl_push_back(storage, cur_max);
    while (!sdbl_is_empty(obj)) {
        double cur = sdbl_pop_back(obj);
        if (cur > cur_max) cur_max = cur;
        sdbl_push_back(storage, cur);
    }
    int was_removed = 0;
    while (!sdbl_is_empty(storage)) {
        double cur = sdbl_pop_back(storage);
        if (cur != cur_max || was_removed) {
            sdbl_push_back(obj, cur);
            continue;
        }
        was_removed = 1;
    }
    sdbl_destroy(storage);
    return cur_max;
}

void select_sort(stack_dbl* obj) {
    stack_dbl* sorted = create();
    while (!sdbl_is_empty(obj)) sdbl_push_back(sorted, remove_max(obj));
    while (!sdbl_is_empty(sorted)) sdbl_push_back(obj, sdbl_pop(back(sorted)));
    sdbl_destroy(sorted);
}