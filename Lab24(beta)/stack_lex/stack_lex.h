#pragma once

#include "../token/token.h"

typedef struct {
    Token* buf;     // Буфер для хранения токенов
    int max_len;    // Максимальный размер
    int len;        // Текущее количество элементов
} stack_lex;

stack_lex* slex_create(int max_len);
void slex_destroy(stack_lex* obj);
int slex_is_empty(stack_lex* obj);
int slex_push_back(stack_lex* obj, Token token);
Token slex_pop_back(stack_lex* obj);
Token slex_top(stack_lex* obj);