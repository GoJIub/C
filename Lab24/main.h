#pragma once

#include "queue_lex/queue_lex.h"
#include "stack_lex/stack_lex.h"
#include "stack_tree/stack_tree.h"
#include "binaryTree/tree.h"

typedef struct {
    int code;
    queue_lex* queue;
} read_result;

typedef struct {
    int code;
    queue_lex* queue;
} postfix_result;

typedef struct {
    int code;
    tree t;
} tree_result;