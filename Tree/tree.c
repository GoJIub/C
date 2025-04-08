#include "tree.h"
#include <stdlib.h>

//...

int add(tree* t, double val, char* path) {
    if (*path == '\0') {
        tree new = malloc(sizeof(treeNode));
        new -> val = val;
        new -> son = NULL;
        new -> bro = *t;
        *t = new;
        return 1;
    }
    if (*t == NULL) return 0;
    if (*path == 's') return add(&(*t) -> son, val, path + 1);
    if (*path == 'b') return add(&(*t) -> bro, val, path + 1);
    return 0;
}