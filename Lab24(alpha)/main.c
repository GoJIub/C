#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "token/token.h"

static int is_op_char(char c) {
    return strchr("+-*/^!~", c) != NULL;
}

static int is_right_assoc(Token token) {
    return token.value[0] == '^' || token.value[0] == '~' || token.value[0] == '!';
}

static int op_priority(Token token) {
    switch (token.value[0]) {
        case '!':
        case '~': return 4;
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

static int should_displace(Token lex, Token target) {
    if (target.type == TOK_PAREN && target.value[0] == '(') return 0;
    int lex_prio = op_priority(lex);
    int target_prio = op_priority(target);
    return is_right_assoc(lex) ? target_prio > lex_prio : target_prio >= lex_prio;
}

read_result readline(queue_lex* out) {
    read_result result = {out, {RESULT_OK, "Success", -1}};
    char buffer[256]; // Буфер для сборки токенов
    int buffer_pos = 0;
    int pos = 0;
    int prev_type = -1; // Для отслеживания унарных операторов
    int c = getchar();

    if (out == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Output queue is NULL", -1};
        return result;
    }

    while (c != EOF && c != '\n') {
        if (isspace(c)) {
            c = getchar();
            pos++;
            continue;
        }

        buffer_pos = 0;

        // Числовые константы
        if (isdigit(c)) {
            while (isdigit(c) || c == '.') {
                buffer[buffer_pos++] = c;
                c = getchar();
            }
            buffer[buffer_pos] = '\0';
            Token token = {strdup(buffer), TOK_CONST};
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
            prev_type = TOK_CONST;
            pos += buffer_pos;
            continue;
        }

        // Переменные
        if (isalpha(c)) {
            while (isalnum(c)) {
                buffer[buffer_pos++] = c;
                c = getchar();
            }
            buffer[buffer_pos] = '\0';
            Token token = {strdup(buffer), TOK_VAR};
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
            prev_type = TOK_VAR;
            pos += buffer_pos;
            continue;
        }

        // Операторы и скобки
        if (is_op_char(c) || c == '(' || c == ')') {
            buffer[0] = c;
            buffer[1] = '\0';
            Token token;
            if (c == '(' || c == ')') {
                token = (Token){strdup(buffer), TOK_PAREN};
            } else if (c == '-' && (prev_type == -1 || prev_type == TOK_OP || prev_type == TOK_UNARY_OP || prev_type == TOK_PAREN)) {
                token = (Token){strdup("~"), TOK_UNARY_OP};
            } else {
                token = (Token){strdup(buffer), is_op_char(c) ? TOK_OP : TOK_UNARY_OP};
            }
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
            prev_type = token.type;
            c = getchar();
            pos++;
            continue;
        }

        result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid character in input", pos};
        return result;
    }

    if (pos > 0 && (prev_type == TOK_OP && strcmp(qlex_top(out).value, "!") != 0 && strcmp(qlex_top(out).value, "~") != 0)) {
        result.error = (ErrorInfo){ERROR_INVALID_EXPRESSION, "Expression cannot end with an operator", pos-1};
        return result;
    }

    if (pos == 0) {
        result.error = (ErrorInfo){ERROR_EMPTY_INPUT, "Empty input line", -1};
    }

    return result;
}

postfix_result convertToPostfix(queue_lex* q, queue_lex* out) {
    postfix_result result = {out, {RESULT_OK, "Success", -1}};
    
    if (q == NULL || out == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Input or output queue is NULL", -1};
        return result;
    }

    stack_lex* s = slex_create(10);
    if (s == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create stack", -1};
        return result;
    }

    int pos = 0;
    while (!qlex_is_empty(q)) {
        Token lex = qlex_pop_front(q);
        
        if (lex.type == TOK_CONST || lex.type == TOK_VAR) {
            if (!qlex_push_back(out, lex)) {
                free(lex.value); // Освобождаем строку токена
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                slex_destroy(s);
                return result;
            }
        } else if (lex.type == TOK_PAREN && strcmp(lex.value, "(") == 0) {
            if (!slex_push_back(s, lex)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        } else if (lex.type == TOK_PAREN && strcmp(lex.value, ")") == 0) {
            while (!slex_is_empty(s) && strcmp(slex_top(s).value, "(") != 0) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    return result;
                }
            }
            if (slex_is_empty(s)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
                slex_destroy(s);
                return result;
            }
            Token open_paren = slex_pop_back(s); // Удаляем '('
            free(open_paren.value); // Освобождаем строку
            free(lex.value);
        } else if (lex.type == TOK_OP || lex.type == TOK_UNARY_OP) {
            while (!slex_is_empty(s) && strcmp(slex_top(s).value, "(") != 0 && should_displace(lex, slex_top(s))) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    free(lex.value);
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    return result;
                }
            }
            if (!slex_push_back(s, lex)) {
                free(lex.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        } else {
            free(lex.value);
            result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid token type", pos};
            slex_destroy(s);
            return result;
        }
        pos++;
    }

    while (!slex_is_empty(s)) {
        Token op = slex_pop_back(s);
        if (strcmp(op.value, "(") == 0) {
            free(op.value);
            result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
            slex_destroy(s);
            return result;
        }
        if (!qlex_push_back(out, op)) {
            free(op.value);
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
            slex_destroy(s);
            return result;
        }
    }

    slex_destroy(s);
    return result;
}

tree_result convertToTree(queue_lex* q) {
    tree_result result = {NULL, {RESULT_OK, "Success", -1}};
    
    if (qlex_is_empty(q)) {
        result.error = (ErrorInfo){ERROR_EMPTY_INPUT, "Empty input queue", -1};
        return result;
    }

    stack_tree* stack = stree_create(10);
    if (!stack) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create stack", -1};
        return result;
    }

    int pos = 0;
    while (!qlex_is_empty(q)) {
        Token token = qlex_pop_front(q);
        tree node = build(token, NULL, NULL);
        
        if (!node) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create tree node", pos};
            stree_destroy(stack);
            return result;
        }

        if (token.type == TOK_OP || token.type == TOK_UNARY_OP) {
            if (token.value[0] == '~') {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){
                        ERROR_STACK_UNDERFLOW, 
                        "Missing operand for ~", 
                        pos
                    };
                    destroyTree(node);
                    stree_destroy(stack);
                    return result;
                }
                node = build(getValue(node), getLeft(node), stree_pop_back(stack));
            } else if (token.value[0] == '!') {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){
                        ERROR_STACK_UNDERFLOW, 
                        "Missing operand for !", 
                        pos
                    };
                    destroyTree(node);
                    stree_destroy(stack);
                    return result;
                }
                node = build(getValue(node), stree_pop_back(stack), getRight(node));
            } else {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing right operand", pos};
                    destroyTree(node);
                    stree_destroy(stack);
                    return result;
                }
                node = build(getValue(node), getLeft(node), stree_pop_back(stack));
                
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing left operand", pos};
                    destroyTree(node->right);
                    destroyTree(node);
                    stree_destroy(stack);
                    return result;
                }
                node = build(getValue(node), stree_pop_back(stack), getRight(node));
            }
        }

        if (!stree_push_back(stack, node)) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
            destroyTree(node);
            stree_destroy(stack);
            return result;
        }
        pos++;
    }

    result.root = stree_pop_back(stack);
    
    if (!stree_is_empty(stack)) {
        result.error = (ErrorInfo){ERROR_STACK_REMAINING, "Extra nodes in stack after processing", pos};
        destroyTree(result.root);
        result.root = NULL;
    }

    stree_destroy(stack);
    return result;
}

void print_error(const ErrorInfo* error) {
    const char* error_type = "";
    switch (error->code) {
        case ERROR_EMPTY_INPUT:       error_type = "Empty input"; break;
        case ERROR_INVALID_SYMBOL:    error_type = "Invalid symbol"; break;
        case ERROR_UNBALANCED_PARENS: error_type = "Unbalanced parentheses"; break;
        case ERROR_STACK_UNDERFLOW:   error_type = "Stack underflow"; break;
        case ERROR_STACK_REMAINING:   error_type = "Remaining elements in stack"; break;
        case ERROR_MEMORY_ALLOC:      error_type = "Memory allocation failed"; break;
        case ERROR_INVALID_EXPRESSION:error_type = "Invalid expression"; break;
        default:                      error_type = "Unknown error"; break;
    }
    
    if (error->position >= 0) {
        fprintf(stderr, "Error [%s] at position %d: %s\n", 
                error_type, error->position, error->message);
    } else {
        fprintf(stderr, "Error [%s]: %s\n", error_type, error->message);
    }
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

int main() {
    queue_lex* input_queue = qlex_create(1);
    if (input_queue == NULL) {
        fprintf(stderr, "Error: Failed to create input queue\n");
        return EXIT_FAILURE;
    }

    printf("Enter expression: ");
    read_result read_res = readline(input_queue);
    if (read_res.error.code != RESULT_OK) {
        print_error(&read_res.error);
        qlex_destroy(input_queue);
        return EXIT_FAILURE;
    }

    printf("Input expression: ");
    print_queue(input_queue);
    printf("\n");

    queue_lex* postfix_queue = qlex_create(1);
    if (postfix_queue == NULL) {
        fprintf(stderr, "Error: Failed to create postfix queue\n");
        qlex_destroy(input_queue);
        return EXIT_FAILURE;
    }

    postfix_result postfix_res = convertToPostfix(input_queue, postfix_queue);
    if (postfix_res.error.code != RESULT_OK) {
        print_error(&postfix_res.error);
        qlex_destroy(input_queue);
        qlex_destroy(postfix_queue);
        return EXIT_FAILURE;
    }

    printf("Postfix notation: ");
    print_queue(postfix_queue);
    printf("\n");

    tree_result tree_res = convertToTree(postfix_queue);
    if (tree_res.error.code != RESULT_OK) {
        print_error(&tree_res.error);
        qlex_destroy(input_queue);
        qlex_destroy(postfix_queue);
        return EXIT_FAILURE;
    }

    printf("Expression tree:\n");
    printTreePretty(tree_res.root, 0);
    printf("\n");

    deleteUnitMultiply(&tree_res.root);
    printf("Simplified tree:\n");
    printTreePretty(tree_res.root, 0);

    qlex_destroy(input_queue);
    qlex_destroy(postfix_queue);
    destroyTree(tree_res.root);

    return EXIT_SUCCESS;
}