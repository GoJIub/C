#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

// === Stack by array ===

stack* create_stack(int max_len) {
    stack* res = malloc(sizeof(stack));
    if (res == NULL) return NULL;
    res -> max_len = max_len;
    res -> buf = malloc(sizeof(double) * max_len);
    if (res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> len = 0;
    return res;
}

void destroy_stack(stack* obj) {
    if (!obj) return;
    free(obj -> buf);
    free(obj);
}

int is_empty_stack(stack* obj) {
    return obj -> len == 0;
}

int push_back_stack(stack* obj, double value) {
    if (obj -> len == obj -> max_len) return 0;
    obj -> buf[obj -> len] = value;
    obj -> len++;
    return 1;
}

double pop_back_stack(stack* obj) {
    if (is_empty_stack(obj)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    double value = obj -> buf[obj -> len - 1];
    obj -> len--;
    return value;
}

// === Queue by array ===

queue* create_queue(int max_len) {
    queue* res = malloc(sizeof(queue));
    if (res == NULL) return NULL;
    res -> max_len = max_len;
    res -> buf = malloc(sizeof(double) * max_len);
    if (res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> len = 0;
    res -> start = 0;
    return res;
}

void destroy_queue(queue* obj) {
    if (!obj) return;
    free(obj -> buf);
    free(obj);
}

int is_empty_queue(queue* obj) {
    return obj -> len == 0;
}

int push_back_queue(queue* obj, double value) {
    if (obj -> len == obj -> max_len) return 0;
    obj -> buf[(obj -> len + obj -> start) % obj -> max_len] = value;
    obj -> len++;
    return 1;
}

double pop_front_queue(queue* obj) {
    if (is_empty_queue(obj)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    double value = obj -> buf[obj -> start];
    obj -> start = (obj -> start + 1) % obj -> max_len;
    obj -> len--;
    return value;
}

// === Deque by array ===

deque* create_deque(int max_len) {
    deque* res = malloc(sizeof(deque));
    if (res == NULL) return NULL;
    res -> max_len = max_len;
    res -> buf = malloc(sizeof(double) * max_len);
    if (res -> buf == NULL) {
        free(res);
        return NULL;
    }
    res -> len = 0;
    res -> start = 0;
    return res;
}

void destroy_deque(deque* obj) {
    if (!obj) return;
    free(obj -> buf);
    free(obj);
}

int is_empty_deque(deque* obj) {
    return obj -> len == 0;
}

int push_back_deque(deque* obj, double value) {
    if (obj -> len == obj -> max_len) return 0;
    obj -> buf[(obj -> len + obj -> start) % obj -> max_len] = value;
    obj -> len++;
    return 1;
}

int push_front_deque(deque* obj, double value) {
    if (obj -> len == obj -> max_len) return 0;
    obj -> start = (obj -> start + obj -> max_len - 1) % obj -> max_len;
    obj -> buf[obj -> start] = value;
    obj -> len++;
    return 1;
}

double pop_back_deque(deque* obj) {
    if (is_empty_deque(obj)) {
        fprintf(stderr, "Deque underflow\n");
        exit(EXIT_FAILURE);
    }
    double value = obj -> buf[(obj -> len + obj -> start - 1) % obj -> max_len];
    obj -> len--;
    return value;
}

double pop_front_deque(deque* obj) {
    if (is_empty_deque(obj)) {
        fprintf(stderr, "Deque underflow\n");
        exit(EXIT_FAILURE);
    }
    double value = obj -> buf[obj -> start];
    obj -> start = (obj -> start + 1) % obj -> max_len;
    obj -> len--;
    return value;
}

// === Stack by linked list ===

dstack* create_dstack() {
    dstack* res = malloc(sizeof(dstack));
    if (res == NULL) return NULL;
    res -> first = NULL;
    return res;
}

void destroy_dstack(dstack* obj) {
    elem* current = obj -> first;
    while (current != NULL) {
        elem* next = current -> next;
        free(current);
        current = next;
    }
    free(obj);
}

int is_empty_dstack(dstack* obj) {
    return obj -> first == NULL;
}

int push_back_dstack(dstack* obj, double value) {
    elem* e = malloc(sizeof(elem));
    if (e == NULL) return 0;
    e -> val = value;
    e -> next = obj -> first;
    obj -> first = e;
    return 1;
}

double pop_back_dstack(dstack* obj) {
    if (is_empty_dstack(obj)) {
        fprintf(stderr, "Dstack underflow\n");
        exit(EXIT_FAILURE);
    }
    double res = obj -> first -> val;
    elem* next = obj -> first -> next;
    free(obj -> first);
    obj -> first = next;
    return res;
}

// === Queue by linked list ===

dqueue* create_dqueue() {
    dqueue* res = malloc(sizeof(dqueue));
    if (res == NULL) return NULL;
    res -> first = NULL;
    res -> last = NULL;
    return res;
}

void destroy_dqueue(dqueue* obj) {
    elem* current = obj -> first;
    while (current != NULL) {
        elem* next = current -> next;
        free(current);
        current = next;
    }
    free(obj);
}

int is_empty_dqueue(dqueue* obj) {
    return obj -> first == NULL;
}

int push_back_dqueue(dqueue* obj, double value) {
    elem* e = malloc(sizeof(elem));
    if (e == NULL) return 0;
    e -> val = value;
    e -> next = NULL;
    if (obj -> last == NULL)
        obj -> first = obj -> last = e;
    else {
        obj -> last -> next = e;
        obj -> last = e;
    }
    return 1;
}

double pop_front_dqueue(dqueue* obj) {
    if (is_empty_dqueue(obj)) {
        fprintf(stderr, "Dqueue underflow\n");
        exit(EXIT_FAILURE);
    }
    double res = obj -> first -> val;
    elem* next = obj -> first -> next;
    free(obj -> first);
    obj -> first = next;
    if (obj -> first == NULL) obj -> last = NULL;
    return res;
}

// === Deque by linked list ===

ddeque* create_ddeque() {
    ddeque* res = malloc(sizeof(ddeque));
    if (res == NULL) return NULL;
    res -> first = NULL;
    res -> last = NULL;
    return res;
}

void destroy_ddeque(ddeque* obj) {
    elem* current = obj -> first;
    while (current != NULL) {
        elem* next = current -> next;
        free(current);
        current = next;
    }
    free(obj);
}

int is_empty_ddeque(ddeque* obj) {
    return obj -> first == NULL;
}

int push_back_ddeque(ddeque* obj, double value) {
    elem* e = malloc(sizeof(elem));
    if (e == NULL) return 0;
    e -> val = value;
    e -> next = NULL;
    e -> prev = obj -> last;
    if (is_empty_ddeque(obj))
        obj -> first = obj -> last = e;
    else {
        obj -> last -> next = e;
        obj -> last = e;
    }
    return 1;
}

int push_front_ddeque(ddeque* obj, double value) {
    elem* e = malloc(sizeof(elem));
    if (e == NULL) return 0;
    e -> val = value;
    e -> prev = NULL;
    e -> next = obj -> first;
    if (is_empty_ddeque(obj))
        obj -> first = obj -> last = e;
    else {
        obj -> first -> prev = e;
        obj -> first = e;
    }
    return 1;
}

double pop_back_ddeque(ddeque* obj) {
    if (is_empty_ddeque(obj)) {
        fprintf(stderr, "Ddeque underflow\n");
        exit(EXIT_FAILURE);
    }
    elem* last = obj -> last;
    double res = last -> val;
    obj -> last = last -> prev;
    free(last);
    if (obj -> last == NULL) obj -> first = NULL;
    else obj -> last -> next = NULL;
    return res;
}

double pop_front_ddeque(ddeque* obj) {
    if (is_empty_ddeque(obj)) {
        fprintf(stderr, "Ddeque underflow\n");
        exit(EXIT_FAILURE);
    }
    double res = obj -> first -> val;
    elem* next = obj -> first -> next;
    free(obj -> first);
    obj -> first = next;
    if (obj -> first == NULL) obj -> last = NULL;
    else obj -> first -> prev = NULL;
    return res;
}