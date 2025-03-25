#include "../../Structs/Extended/stack/stack_dbl.h"

void mege(stack_dbl* obj1, stack_dbl* obj2, stack_dbl* res) {
    if (sdbl_is_empty(obj1) || sdbl_is_empty(obj2)) return;
    double e1 = sdbl_top(obj1), e2 = sdbl_top(obj2);
    while (!sdbl_is_empty(obj1) && !sdbl_is_empty(obj2)) {
        if (e1 >= e2) {
            sdbl_push_back(res, sdbl_pop_back(obj1));
            e1 = top_back(obj1);
        } else {
            sdbl_push_back(res, sdbl_pop_back(obj2));
            e2 = top_back(obj2);
        }
    }
    while (!sdbl_is_empty(obj1)) sdbl_push_back(res, sdbl_pop_back(obj1));
    while (!sdbl_is_empty(obj2)) sdbl_push_back(res, sdbl_pop_back(obj2));
}