#include "stack_lex.h"
#include <stdlib.h>
#include <string.h>

stack_lex* slex_create(int max_len) {
    stack_lex* res = malloc(sizeof(stack_lex));
    if (res == NULL) return NULL;
    res->max_len = max_len;
    res->buf = malloc(sizeof(Token) * max_len); // Изменено char на Token
    if (res->buf == NULL) {
        free(res);
        return NULL;
    }
    res->len = 0;
    return res;
}

static int grow(stack_lex* obj) {
    int new_max_len = obj->max_len * 2;
    Token* new_buf = realloc(obj->buf, sizeof(Token) * new_max_len); // Изменено char на Token
    if (new_buf == NULL) return 0;
    obj->buf = new_buf;
    obj->max_len = new_max_len;
    return 1;
}

void slex_destroy(stack_lex* obj) {
    if (!obj) return;
    for (int i = 0; i < obj->len; i++) {
        free(obj->buf[i].value); // Освобождаем строки токенов
    }
    free(obj->buf);
    free(obj);
}

int slex_is_empty(stack_lex* obj) {
    return obj->len == 0;
}

int slex_push_back(stack_lex* obj, Token value) {
    if (obj->len == obj->max_len)
        if (!grow(obj)) return 0;
    obj->buf[obj->len] = value;
    obj->len++;
    return 1;
}

Token slex_pop_back(stack_lex* obj) {
    obj->len--;
    return obj->buf[obj->len];
}

Token slex_top(stack_lex* obj) {
    return obj->buf[obj->len - 1];
}