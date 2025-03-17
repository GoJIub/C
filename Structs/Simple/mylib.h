#pragma once

typedef struct {
    double* buf;
    int max_len;
    int len;
} stack;

typedef struct {
    double* buf;
    int max_len;
    int len;
    int start;
} queue;

typedef struct {
    double* buf;
    int max_len;
    int len;
    int start;
} deque;

typedef struct elem elem;
struct elem {
    double val;
    elem* next;
    elem* prev;
};

typedef struct {
    elem* first;
} dstack;

typedef struct {
    elem* first;
    elem* last;
} dqueue;

typedef struct {
    elem* first;
    elem* last;
} ddeque;

stack* create_stack(int max_len);
void destroy_stack(stack* obj);
int is_empty_stack(stack* obj);
int push_back_stack(stack* obj, double value);
double pop_back_stack(stack* obj);

queue* create_queue(int max_len);
void destroy_queue(queue* obj);
int is_empty_queue(queue* obj);
int push_back_queue(queue* obj, double value);
double pop_front_queue(queue* obj);

deque* create_deque(int max_len);
void destroy_deque(deque* obj);
int is_empty_deque(deque* obj);
int push_back_deque(deque* obj, double value);
int push_front_deque(deque* obj, double value);
double pop_back_deque(deque* obj);
double pop_front_deque(deque* obj);

dstack* create_dstack();
void destroy_dstack(dstack* obj);
int is_empty_dstack(dstack* obj);
int push_back_dstack(dstack* obj, double value);
double pop_back_dstack(dstack* obj);

dqueue* create_dqueue();
void destroy_dqueue(dqueue* obj);
int is_empty_dqueue(dqueue* obj);
int push_back_dqueue(dqueue* obj, double value);
double pop_front_dqueue(dqueue* obj);

ddeque* create_ddeque();
void destroy_ddeque(ddeque* obj);
int is_empty_ddeque(ddeque* obj);
int push_back_ddeque(ddeque* obj, double value);
int push_front_ddeque(ddeque* obj, double value);
double pop_back_ddeque(ddeque* obj);
double pop_front_ddeque(ddeque* obj);