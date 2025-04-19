#include <stdlib.h>
#include <stdio.h>
#include "main.h"

static int is_op(char c) {

}

static int is_const(char c) {

}

static int is_var(char c) {

}

static int is_p_left(char c) {

}

static int is_p_right(char c) {

}

static int is_right_assoc(char c) { // *, -, ^

}

static int op_priority(char op) {

}

static int should_displace(char lex, char target) {
    if (is_p_left(target)) return 0;
    if (is_right_assoc(lex)) return op_priority(target) > op_priority(lex);
    return op_priority(target) <= op_priority(lex);
}

read_result readline(queue_lex* out) {
    int prev = 0;
    int cur = getchar();
    while (cur != EOF && cur != '\n') {
        if (is_const(cur) || is_var(cur)) {
            qlex_push_back(out, cur);
        } else if (is_op(cur)) {
            if (cur == '-') {
                if (prev == 0 || is_op(prev) || is_p_left(prev))
                    qlex_push_back(out, '~');
                else
                    qlex_push_back(out, cur);
            } else qlex_push_back(out, cur);
        } else return; // error;
        prev = cur;
    }
    return; // success
}

postfix_result postfix(queue_lex* q, queue_lex* out) {
    stack_lex* s = slex_create(2);
    char lex;
    while (!qlex_is_empty(q)) {
        lex = qlex_pop_front(q);
        if (is_const(lex) || is_var(lex)) {
            qlex_push_back(out, lex);
        } else if (is_p_left(lex)) {
            slex_push_back(s, lex);
        } else if (is_p_right(lex)) {
            lex = slex_pop_back(s);
            while (!slex_is_empty(s) && !is_p_left(lex)) {
                qlex_push_back(out, lex);
                lex = slex_pop_back(s);
            }
            if (!is_p_left(lex)) return; // missing
        } else if (is_op(lex)) {
            while (!slex_is_empty(s) && should_displace(lex, qlex_top(q))) {
                qlex_push_back(out, slex_pop_back(s));
            }
            slex_push_back(s, lex);
        }
    }
    while (!slex_is_empty(s) && (lex = slex_pop_back(s)) != '(') {
        qlex_push_back(out, lex);
    }
    if (is_p_left(lex)) return; // missing_rp
    slex_destroy(s);
    return; // success

}