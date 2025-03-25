#include "../../Structs/Extended/deque/deque_dbl.h"
 
 int step_of_a_sort(deque_dbl* obj) {
    if (ddbl_is_empty(obj)) return 0;
    double e1 = ddbl_pop_front(obj);
    if (ddbl_is_empty(obj)) {
        ddbl_push_back(obj, e1);
        return 0;
    }
    double e2 = ddbl_pop_front(obj);
    deque_dbl* storage = ddbl_create(10);
    while (e2 >= e1) {
        ddbl_push_back(storage, e1);
        e1 = e2;
        if (ddbl_is_empty(obj)) {
            ddbl_push_back(storage, e1);
            while (!ddbl_is_empty(storage)) ddbl_push_back(obj, ddbl_pop_front(storage));
            return 0;
        }
        e2 = ddbl_pop_front(obj);
    }
    ddbl_push_back(storage, e1);
    while (!ddbl_is_empty(obj)) ddbl_push_back(storage, ddbl_pop_front(obj));
    int was_added = 0;
    while (!ddbl_is_empty(storage)) {
        e1 = ddbl_pop_front(storage);
        if (e1 <= e2) ddbl_push_back(obj, e1);
        else if (!was_added) {
            ddbl_push_back(obj, e2);
            was_added = 1;
        }
    }
    if (!was_added) ddbl_push_back(obj, e2);
    return 1;
 }

 void insert_sort(deque_dbl* obj) {
    while (step_of_a_sort(obj));
 }