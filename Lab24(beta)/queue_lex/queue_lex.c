#include "queue_lex.h"
#include <stdlib.h>
#include <string.h>

queue_lex* qlex_create(int max_len) {
    queue_lex* res = malloc(sizeof(queue_lex));
    if (!res) return NULL;
    
    res->buf = malloc(sizeof(Token) * max_len);
    if (!res->buf) {
        free(res);
        return NULL;
    }
    
    res->max_len = max_len;
    res->len = 0;
    res->start = 0;
    return res;
}

void qlex_destroy(queue_lex* obj) {
    if (!obj) return;
    
    for (int i = 0; i < obj->len; i++) {
        int idx = (obj->start + i) % obj->max_len;
        free(obj->buf[idx].value);
    }
    
    free(obj->buf);
    free(obj);
}

int qlex_is_empty(queue_lex* obj) {
    return obj->len == 0;
}

static int grow(queue_lex* obj) {
    int new_max_len = obj -> max_len * 2;
    Token* new_buf = realloc(obj -> buf, sizeof(Token) * new_max_len);
    if (new_buf == NULL) return 0;
    for (int i = obj -> max_len - 1; i >= obj -> start; i--)
      new_buf[new_max_len - obj -> len + i] = new_buf[i];
    obj -> start += new_max_len - obj -> max_len;
    obj -> buf = new_buf;
    obj -> max_len = new_max_len;
    return 1;
}

int qlex_push_back(queue_lex* obj, Token token) {
    if (obj->len == obj->max_len) {
        if (!grow(obj))
            return 0;
    }
    
    int pos = (obj->start + obj->len) % obj->max_len;
    obj->buf[pos] = token;
    obj->len++;
    return 1;
}

Token qlex_pop_front(queue_lex* obj) {
    Token res = obj->buf[obj->start];
    obj->start = (obj->start + 1) % obj->max_len;
    obj->len--;
    return res;
}

Token qlex_top(queue_lex* obj) {
    return obj->buf[obj->start];
}