#pragma once

typedef struct {
    char* buf;
    int max_len;
    int len;
} stack_lex;

stack_lex* slex_create(int max_len);
void slex_destroy(stack_lex* obj);
int slex_is_empty(stack_lex* obj);
int slex_push_back(stack_lex* obj, char value);
char slex_pop_back(stack_lex* obj);
char slex_top(stack_lex* obj);