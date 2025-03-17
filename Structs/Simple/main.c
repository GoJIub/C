#include <stdio.h>
#include "mylib.h"

// Тест для стека (на основе массива)
void test_stack() {
    printf("\n=== Testing Stack (Array-based) ===\n\n");
    stack* s = create_stack(3);

    // Проверка пустоты
    printf("is_empty_stack: %d\n", is_empty_stack(s));

    // Добавление элементов
    push_back_stack(s, 1.0);
    push_back_stack(s, 2.0);
    push_back_stack(s, 3.0);

    // Проверка после добавления
    printf("is_empty_stack after pushing 3 elements: %d\n", is_empty_stack(s));

    // Извлечение элементов
    double val1 = pop_back_stack(s);
    double val2 = pop_back_stack(s);
    double val3 = pop_back_stack(s);

    printf("Popping values: %.1f, %.1f, %.1f\n", val1, val2, val3);

    // Проверка после извлечения всех элементов
    printf("is_empty_stack after popping all elements: %d\n", is_empty_stack(s));

    destroy_stack(s);
}

// Тест для очереди (на основе массива)
void test_queue() {
    printf("\n=== Testing Queue (Array-based) ===\n\n");
    queue* q = create_queue(3);

    // Проверка пустоты
    printf("is_empty_queue: %d\n", is_empty_queue(q));

    // Добавление элементов
    push_back_queue(q, 1.0);
    push_back_queue(q, 2.0);
    push_back_queue(q, 3.0);

    // Проверка после добавления
    printf("is_empty_queue after enqueuing 3 elements: %d\n", is_empty_queue(q));

    // Извлечение 2-ух элементов
    double val1 = pop_front_queue(q);
    double val2 = pop_front_queue(q);

    printf("Dequeuing values: %.1f, %.1f\n", val1, val2);

    // Добавление элементов
    push_back_queue(q, 4.0);
    push_back_queue(q, 5.0);
    
    // Извлечение элементов
    double val3 = pop_front_queue(q);
    double val4 = pop_front_queue(q);
    double val5 = pop_front_queue(q);

    printf("Dequeuing values: %.1f, %.1f, %.1f\n", val3, val4, val5);

    // Проверка после извлечения всех элементов
    printf("is_empty_queue after dequeuing all elements: %d\n", is_empty_queue(q));

    destroy_queue(q);
}

// Тест для дека (на основе массива)
void test_deque() {
    printf("\n=== Testing Deque (Array-based) ===\n\n");
    deque* d = create_deque(3);

    // Проверка пустоты
    printf("is_empty_deque: %d\n", is_empty_deque(d));

    printf("- Pushing front 3 elements\n");

    // Добавление элементов в начало
    push_front_deque(d, 1.0);
    push_front_deque(d, 2.0);
    push_front_deque(d, 3.0);

    // Проверка после добавления
    printf("is_empty_deque after pushing 3 elements: %d\n", is_empty_deque(d));

    // Извлечение элементов с конца
    double val1 = pop_back_deque(d);
    double val2 = pop_back_deque(d);
    double val3 = pop_back_deque(d);

    printf("Popping back: %.1f, %.1f, %.1f\n", val1, val2, val3);

    // Проверка после извлечения всех элементов
    printf("is_empty_deque after popping all elements: %d\n", is_empty_deque(d));

    printf("- Pushing back 3 elements\n");
    
    // Добавление элементов в конец
    push_back_deque(d, 1.0);
    push_back_deque(d, 2.0);
    push_back_deque(d, 3.0);

    // Проверка после добавления
    printf("is_empty_deque after pushing 3 elements: %d\n", is_empty_deque(d));

    // Извлечение элементов с начала
    val1 = pop_front_deque(d);
    val2 = pop_front_deque(d);
    val3 = pop_front_deque(d);

    printf("Popping front: %.1f, %.1f, %.1f\n", val1, val2, val3);

    destroy_deque(d);
}

// Тест для стека (на основе связанного списка)
void test_dstack() {
    printf("\n=== Testing DStack (Linked List) ===\n\n");
    dstack* s = create_dstack();

    // Проверка пустоты
    printf("is_empty_dstack: %d\n", is_empty_dstack(s));

    // Добавление элементов
    push_back_dstack(s, 1.0);
    push_back_dstack(s, 2.0);
    push_back_dstack(s, 3.0);

    // Проверка после добавления
    printf("is_empty_dstack after pushing 3 elements: %d\n", is_empty_dstack(s));

    // Извлечение элементов
    double val1 = pop_back_dstack(s);
    double val2 = pop_back_dstack(s);
    double val3 = pop_back_dstack(s);

    printf("Popping values: %.1f, %.1f, %.1f\n", val1, val2, val3);

    // Проверка после извлечения всех элементов
    printf("is_empty_dstack after popping all elements: %d\n", is_empty_dstack(s));

    destroy_dstack(s);
}

// Тест для очереди (на основе связанного списка)
void test_dqueue() {
    printf("\n=== Testing DQueue (Linked List) ===\n\n");
    dqueue* q = create_dqueue();

    // Проверка пустоты
    printf("is_empty_dqueue: %d\n", is_empty_dqueue(q));

    // Добавление элементов
    push_back_dqueue(q, 1.0);
    push_back_dqueue(q, 2.0);
    push_back_dqueue(q, 3.0);

    // Проверка после добавления
    printf("is_empty_dqueue after enqueuing 3 elements: %d\n", is_empty_dqueue(q));

    // Извлечение элементов
    double val1 = pop_front_dqueue(q);
    double val2 = pop_front_dqueue(q);
    double val3 = pop_front_dqueue(q);

    printf("Dequeuing values: %.1f, %.1f, %.1f\n", val1, val2, val3);

    // Проверка после извлечения всех элементов
    printf("is_empty_dqueue after dequeuing all elements: %d\n", is_empty_dqueue(q));

    destroy_dqueue(q);
}

// Тест для дека (на основе связанного списка)
void test_ddeque() {
    printf("\n=== Testing DDeque (Linked List) ===\n\n");
    ddeque* d = create_ddeque(5);

    // Проверка пустоты
    printf("is_empty_ddeque: %d\n", is_empty_ddeque(d));

    printf("- Pushing front 3 elements\n");

    // Добавление элементов в начало
    push_front_ddeque(d, 1.0);
    push_front_ddeque(d, 2.0);
    push_front_ddeque(d, 3.0);

    // Проверка после добавления
    printf("is_empty_ddeque after pushing 3 elements: %d\n", is_empty_ddeque(d));

    // Извлечение элементов с конца
    double val1 = pop_back_ddeque(d);
    double val2 = pop_back_ddeque(d);
    double val3 = pop_back_ddeque(d);

    printf("Popping back: %.1f, %.1f, %.1f\n", val1, val2, val3);

    // Проверка после извлечения всех элементов
    printf("is_empty_ddeque after popping all elements: %d\n", is_empty_ddeque(d));

    printf("- Pushing back 3 elements\n");

    // Добавление элементов в конец
    push_back_ddeque(d, 1.0);
    push_back_ddeque(d, 2.0);
    push_back_ddeque(d, 3.0);

    // Проверка после добавления
    printf("is_empty_ddeque after pushing 3 elements: %d\n", is_empty_ddeque(d));

    // Извлечение элементов с начала
    val1 = pop_front_ddeque(d);
    val2 = pop_front_ddeque(d);
    val3 = pop_front_ddeque(d);

    printf("Popping front: %.1f, %.1f, %.1f\n", val1, val2, val3);

    destroy_ddeque(d);
}

// Тест на переполнение
void test_overflow() {
    printf("\n=== Testing overflow for all structures ===\n\n");

    stack* s = create_stack(3);
    push_back_stack(s, 1.0);
    push_back_stack(s, 2.0);
    push_back_stack(s, 3.0);
    int overflow_stack = push_back_stack(s, 4.0);  // Ожидаем, что эта операция не выполнится
    printf("Overflow on stack: %d\n", overflow_stack); // Ожидаем 0

    queue* q = create_queue(3);
    push_back_queue(q, 1.0);
    push_back_queue(q, 2.0);
    push_back_queue(q, 3.0);
    int overflow_queue = push_back_queue(q, 4.0);  // Ожидаем, что эта операция не выполнится
    printf("Overflow on queue: %d\n", overflow_queue); // Ожидаем 0

    deque* d = create_deque(3);
    push_back_deque(d, 1.0);
    push_back_deque(d, 2.0);
    push_back_deque(d, 3.0);
    int overflow_deque = push_back_deque(d, 4.0);  // Ожидаем, что эта операция не выполнится
    printf("Overflow on deque: %d\n", overflow_deque); // Ожидаем 0

    destroy_stack(s);
    destroy_queue(q);
    destroy_deque(d);
}

int main() {
    // Вызов всех тестов
    test_stack();
    test_queue();
    test_deque();
    test_dstack();
    test_dqueue();
    test_ddeque();
    test_overflow();
    printf("\n");
}