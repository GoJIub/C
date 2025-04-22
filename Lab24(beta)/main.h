#pragma once

#include "queue_lex/queue_lex.h"
#include "stack_lex/stack_lex.h"
#include "stack_tree/stack_tree.h"
#include "binaryTree/tree.h"

typedef enum {
    RESULT_OK = 0,            // Успешное выполнение
    ERROR_EMPTY_INPUT,        // Пустой ввод
    ERROR_INVALID_SYMBOL,     // Недопустимый символ
    ERROR_UNBALANCED_PARENS,  // Несбалансированные скобки
    ERROR_STACK_UNDERFLOW,    // Недостаточно операндов
    ERROR_STACK_REMAINING,    // Остались элементы в стеке
    ERROR_MEMORY_ALLOC,       // Ошибка выделения памяти
    ERROR_INVALID_EXPRESSION  // Неверная структура выражения
} ErrorCode;

typedef struct {
    ErrorCode code;
    const char* message;
    int position;
} ErrorInfo;

typedef struct {
    queue_lex* queue;
    ErrorInfo error;
} read_result;

typedef struct {
    queue_lex* queue;
    ErrorInfo error;
} postfix_result;

typedef struct {
    tree root;
    ErrorInfo error;
} tree_result;