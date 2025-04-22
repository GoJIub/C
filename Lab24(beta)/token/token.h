#pragma once

typedef enum {
    TOK_VAR,     // Переменная (например, "x1")
    TOK_CONST,   // Числовая константа (например, "42")
    TOK_OP,      // Оператор ("+", "-", "*", и т.д.)
    TOK_UNARY_OP, // Унарный оператор ("~" для минуса)
    TOK_PAREN    // Скобки ("(", ")")
} TokenType;

typedef struct {
    char* value;    // Строковое значение
    TokenType type; // Тип токена
} Token;