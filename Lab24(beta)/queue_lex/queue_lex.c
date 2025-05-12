#include "queue_lex.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

queue_lex* qlex_create(int max_len) {
    queue_lex* res = malloc(sizeof(queue_lex));
    if (res == NULL) return NULL;
    res->max_len = max_len;
    res->buf = malloc(sizeof(Token) * max_len);
    if (res->buf == NULL) {
        free(res);
        return NULL;
    }
    res->len = 0;
    res->start = 0;
    return res;
}

static int grow(queue_lex* obj) {
    int new_max_len = obj->max_len * 2;
    Token* new_buf = realloc(obj->buf, sizeof(Token) * new_max_len);
    if (new_buf == NULL) return 0;
    for (int i = obj->max_len - 1; i >= obj->start; i--)
        new_buf[new_max_len - obj->len + i] = new_buf[i];
    obj->start += new_max_len - obj->max_len;
    obj->buf = new_buf;
    obj->max_len = new_max_len;
    return 1;
}

void qlex_destroy(queue_lex* obj) {
    if (!obj) return;
    for (int i = 0; i < obj->len; i++) {
        free(obj->buf[(obj->start + i) % obj->max_len].value);
    }
    free(obj->buf);
    free(obj);
}

int qlex_is_empty(queue_lex* obj) {
    return obj->len == 0;
}

int qlex_push_back(queue_lex* obj, Token value) {
    if (obj->len == obj->max_len)
        if (!grow(obj)) return 0;
    obj->buf[(obj->len + obj->start) % obj->max_len] = value;
    obj->len++;
    return 1;
}

Token qlex_pop_front(queue_lex* obj) {
    Token value = obj->buf[obj->start];
    obj->start = (obj->start + 1) % obj->max_len;
    obj->len--;
    return value;
}

Token qlex_top(queue_lex* obj) {
    return obj->buf[obj->start];
}

void print_queue(queue_lex* q) {
    if (q == NULL) return;
    int i = q->start;
    int count = 0;
    while (count < q->len) {
        printf("%s ", q->buf[i].value);
        i = (i + 1) % q->max_len;
        count++;
    }
}