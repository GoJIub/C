#pragma once

#include "../token/token.h"

typedef struct {
    Token* buf;     // Буфер для хранения токенов
    int max_len;    // Максимальный размер
    int len;        // Текущее количество
    int start;      // Начальный индекс (для кольцевого буфера)
} queue_lex;

queue_lex* qlex_create(int max_len);
void qlex_destroy(queue_lex* obj);
int qlex_is_empty(queue_lex* obj);
int qlex_push_back(queue_lex* obj, Token token);
Token qlex_pop_front(queue_lex* obj);
Token qlex_top(queue_lex* obj);