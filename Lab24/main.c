#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

static int is_op(char c) {
    char *operators = "~+-*^/!";
    return strchr(operators, c) != NULL;
}

static int is_const(char c) {
    if (isdigit(c)) return 1;
    return 0;
}

static int is_var(char c) {
    if (isalpha(c) && !is_op(c)) return 1;
    return 0;
}

static int is_p_left(char c) {
    if (c == '(') return 1;
    return 0;
}

static int is_p_right(char c) {
    if (c == ')') return 1;
    return 0;
}

static int is_right_assoc(char c) {
    return c == '^' || c == '~';
}

static int op_priority(char op) {
    switch (op) {
        case '!':
        case '~':
            return 4;
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }
}

static int should_displace(char lex, char target) {
    if (is_p_left(target)) return 0;
    int lex_prio = op_priority(lex);
    int target_prio = op_priority(target);
    
    if (is_right_assoc(lex))
        return target_prio > lex_prio;
    else
        return target_prio >= lex_prio;
}

read_result readline(queue_lex* out) {
    read_result result = {out, {RESULT_OK, "Success", -1}};
    int prev = 0;
    int pos = 0;
    int cur = getchar();

    if (out == NULL) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Output queue is NULL", -1};
        return result;
    }

    while (cur != EOF && cur != '\n') {
        if (is_const(cur) || is_var(cur)) {
            if (!qlex_push_back(out, cur)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
        } 
        else if (is_op(cur)) {
            char op = cur;
            if (cur == '-') {
                op = (prev == 0 || is_op(prev) || is_p_left(prev)) ? '~' : '-';
            }
            
            if (!qlex_push_back(out, op)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
        } 
        else if (is_p_left(cur) || is_p_right(cur)) {
            if (!qlex_push_back(out, cur)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
        } 
        else if (!isspace(cur)) {
            result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid character in input", pos};
            return result;
        }
        
        prev = cur;
        pos++;
        cur = getchar();
    }

    if (pos > 0 && is_op(prev) && prev != '!' && prev != '~') {
        result.error = (ErrorInfo){
            ERROR_INVALID_EXPRESSION, 
            "Expression cannot end with an operator", 
            pos-1
        };
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
        char lex = qlex_pop_front(q);
        
        if (is_const(lex) || is_var(lex)) {
            if (!qlex_push_back(out, lex)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                slex_destroy(s);
                return result;
            }
        } 
        else if (is_p_left(lex)) {
            if (!slex_push_back(s, lex)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        } 
        else if (is_p_right(lex)) {
            while (!slex_is_empty(s) && !is_p_left(slex_top(s))) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    return result;
                }
            }
            
            if (slex_is_empty(s)) {
                result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
                slex_destroy(s);
                return result;
            }
            
            slex_pop_back(s);
        } 
        else if (is_op(lex)) {
            while (!slex_is_empty(s) && 
                  !is_p_left(slex_top(s)) && 
                  should_displace(lex, slex_top(s))) {
                if (!qlex_push_back(out, slex_pop_back(s))) {
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    return result;
                }
            }
            
            if (!slex_push_back(s, lex)) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        }
        pos++;
    }

    while (!slex_is_empty(s)) {
        char op = slex_pop_back(s);
        if (is_p_left(op)) {
            result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
            slex_destroy(s);
            return result;
        }
        
        if (!qlex_push_back(out, op)) {
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
        char token = qlex_pop_front(q);
        tree node = build(token, NULL, NULL);
        
        if (!node) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create tree node", pos};
            stree_destroy(stack);
            return result;
        }

        if (is_op(token)) {
            if (token == '~') {
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
            } else if (token == '!') {
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
    
    queue_lex* temp = qlex_create(1);
    if (temp == NULL) {
        fprintf(stderr, "Warning: Failed to create temp queue for printing\n");
        return;
    }

    while (!qlex_is_empty(q)) {
        char c = qlex_pop_front(q);
        printf("%c ", c);
        qlex_push_back(temp, c);
    }

    while (!qlex_is_empty(temp)) {
        qlex_push_back(q, qlex_pop_front(temp));
    }

    qlex_destroy(temp);
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