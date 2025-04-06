#include "deque_str.h"
#include <stdlib.h>
#include <string.h>

deque_str* dstr_create(int max_len) {
    deque_str* res = malloc(sizeof(deque_str));
    if (!res) return NULL;
    res -> max_len = max_len;
    res -> buf = malloc(sizeof(char*) * max_len);
    if (!res -> buf) {
        free(res);
        return NULL;
    }
    res -> len = 0;
    res -> start = 0;
    return res;
}

static int grow(deque_str* obj) {
    int new_max_len = obj -> max_len * 2;
    char** new_buf = malloc(sizeof(char*) * new_max_len);
    if (!new_buf) return 0;
    for (int i = 0; i < obj -> len; i++) {
        new_buf[i] = obj -> buf[(obj -> start + i) % obj -> max_len];
    }
    free(obj -> buf);
    obj -> buf = new_buf;
    obj -> max_len = new_max_len;
    obj -> start = 0;
    return 1;
}

static int shrink(deque_str* obj) {
    if (obj -> max_len <= 10 || obj -> len * 4 > obj -> max_len)
        return 1;
    int new_max_len = obj -> max_len / 2;
    char** new_buf = malloc(sizeof(char*) * new_max_len);
    if (!new_buf) return 0;
    for (int i = 0; i < obj -> len; i++) {
        new_buf[i] = obj -> buf[(obj -> start + i) % obj -> max_len];
    }
    free(obj -> buf);
    obj -> buf = new_buf;
    obj -> max_len = new_max_len;
    obj -> start = 0;
    return 1;
}

void dstr_destroy(deque_str* obj) {
    if (!obj) return;
    for (int i = 0; i < obj -> len; i++) {
        int idx = (obj -> start + i) % obj -> max_len;
        free(obj -> buf[idx]);
    }
    free(obj -> buf);
    free(obj);
}

int dstr_is_empty(deque_str* obj) {
    return obj -> len == 0;
}

int dstr_push_back(deque_str* obj, const char* value) {
    if (obj -> len == obj -> max_len)
        if (!grow(obj)) return 0;
    int idx = (obj -> start + obj -> len) % obj -> max_len;
    obj -> buf[idx] = strdup(value);
    if (!obj -> buf[idx])
        return 0;
    obj -> len++;
    return 1;
}

int dstr_push_front(deque_str* obj, const char* value) {
    if (obj -> len == obj -> max_len)
        if (!grow(obj)) return 0;
    obj -> start = (obj -> start + obj -> max_len - 1) % obj -> max_len;
    obj -> buf[obj -> start] = strdup(value);
    if (!obj -> buf[obj -> start])
        return 0;
    obj -> len++;
    return 1;
}

char* dstr_pop_front(deque_str* obj) {
    if (dstr_is_empty(obj))
        return NULL;
    char* value = obj -> buf[obj -> start];
    obj -> start = (obj -> start + 1) % obj -> max_len;
    obj -> len--;
    shrink(obj);
    return value;
}

char* dstr_pop_back(deque_str* obj) {
    if (dstr_is_empty(obj))
        return NULL;
    int idx = (obj -> start + obj -> len - 1) % obj -> max_len;
    char* value = obj -> buf[idx];
    obj -> len--;
    shrink(obj);
    return value;
}