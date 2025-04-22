#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

// Проверка типа токена
static int is_op(const Token* token) {
    return token->type == TOK_OP || token->type == TOK_UNARY_OP;
}

static int is_const(const Token* token) {
    return token->type == TOK_CONST;
}

static int is_var(const Token* token) {
    return token->type == TOK_VAR;
}

static int is_p_left(const Token* token) {
    return token->type == TOK_PAREN && token->value[0] == '(';
}

static int is_p_right(const Token* token) {
    return token->type == TOK_PAREN && token->value[0] == ')';
}

static int is_right_assoc(const Token* op) {
    return op->value[0] == '^' || op->value[0] == '~' || op->value[0] == '!';
}

static int op_priority(const Token* op) {
    switch (op->value[0]) {
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

static int should_displace(const Token* lex, const Token* target) {
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
    int pos = 0;
    int cur = getchar();

    while (cur != EOF && cur != '\n') {
        Token token = {0};
        
        if (isalpha(cur)) {
            char buffer[256];
            int i = 0;
            while (isalnum(cur) && i < 255) {
                buffer[i++] = cur;
                cur = getchar();
                pos++;
            }
            buffer[i] = '\0';
            
            if (!(token.value = strdup(buffer))) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to allocate token", pos};
                return result;
            }
            token.type = TOK_VAR;
        }
        else if (isdigit(cur)) {
            char buffer[256];
            int i = 0;
            while (isdigit(cur) && i < 255) {
                buffer[i++] = cur;
                cur = getchar();
                pos++;
            }
            buffer[i] = '\0';
            
            if (!(token.value = strdup(buffer))) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to allocate token", pos};
                return result;
            }
            token.type = TOK_CONST;
        }
        else if (strchr("+-*/^!()", cur)) {
            token.value = malloc(2);
            if (!token.value) {
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to allocate operator", pos};
                return result;
            }
            token.value[0] = cur;
            token.value[1] = '\0';
            
            if (cur == '-') {
                int prev = pos > 0 ? out->buf[(out->start + out->len - 1) % out->max_len].value[0] : 0;
                if (pos == 0 || strchr("(+-*/^", prev)) {
                    token.type = TOK_UNARY_OP;
                    token.value[0] = '~';
                } else {
                    token.type = TOK_OP;
                }
            } else if (cur == '!') {
                token.type = TOK_UNARY_OP;
            } else if (cur == '(' || cur == ')') {
                token.type = TOK_PAREN;
            } else {
                token.type = TOK_OP;
            }
            
            cur = getchar();
            pos++;
        }
        else if (!isspace(cur)) {
            result.error = (ErrorInfo){ERROR_INVALID_SYMBOL, "Invalid character in input", pos};
            return result;
        }
        
        if (token.value) {
            if (!qlex_push_back(out, token)) {
                free(token.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                return result;
            }
        }
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
        
        if (is_const(&lex) || is_var(&lex)) {
            Token copy = {strdup(lex.value), lex.type};
            if (!copy.value || !qlex_push_back(out, copy)) {
                free(copy.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                slex_destroy(s);
                return result;
            }
        } 
        else if (is_p_left(&lex)) {
            Token copy = {strdup(lex.value), lex.type};
            if (!copy.value || !slex_push_back(s, copy)) {
                free(copy.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        } 
        else if (is_p_right(&lex)) {
            Token top = slex_top(s);
            while (!slex_is_empty(s) && !is_p_left(&top)) {
                Token op = slex_pop_back(s);
                if (!qlex_push_back(out, op)) {
                    free(op.value);
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
            
            free(slex_pop_back(s).value);
        } 
        else if (is_op(&lex)) {
            Token top = slex_top(s);
            while (!slex_is_empty(s) && !is_p_left(&top) && should_displace(&lex, &top)) {
                Token op = slex_pop_back(s);
                if (!qlex_push_back(out, op)) {
                    free(op.value);
                    result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Queue push failed", pos};
                    slex_destroy(s);
                    return result;
                }
            }
            Token copy = {strdup(lex.value), lex.type};
            if (!copy.value || !slex_push_back(s, copy)) {
                free(copy.value);
                result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
                slex_destroy(s);
                return result;
            }
        }
        free(lex.value);
        pos++;
    }

    while (!slex_is_empty(s)) {
        Token op = slex_pop_back(s);
        if (is_p_left(&op)) {
            result.error = (ErrorInfo){ERROR_UNBALANCED_PARENS, "Unbalanced parentheses", pos};
            free(op.value);
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

    stack_tree* stack = stree_create(16);
    if (!stack) {
        result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create stack", -1};
        return result;
    }

    int pos = 0;
    while (!qlex_is_empty(q)) {
        Token token = qlex_pop_front(q);
        tree node = build(strdup(token.value), NULL, NULL);
        
        if (!node) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Failed to create tree node", pos};
            free(token.value);
            stree_destroy(stack);
            return result;
        }

        if (is_op(&token)) {
            if (token.type == TOK_UNARY_OP) {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){
                        ERROR_STACK_UNDERFLOW, 
                        "Missing operand for unary operator", 
                        pos
                    };
                    destroyTree(node);
                    free(token.value);
                    stree_destroy(stack);
                    return result;
                }
                node->right = stree_pop_back(stack);
            } 
            // Обработка бинарных операторов
            else {
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing right operand", pos};
                    destroyTree(node);
                    free(token.value);
                    stree_destroy(stack);
                    return result;
                }
                node->right = stree_pop_back(stack);
                
                if (stree_is_empty(stack)) {
                    result.error = (ErrorInfo){ERROR_STACK_UNDERFLOW, "Missing left operand", pos};
                    destroyTree(node->right);
                    destroyTree(node);
                    free(token.value);
                    stree_destroy(stack);
                    return result;
                }
                node->left = stree_pop_back(stack);
            }
        }

        if (!stree_push_back(stack, node)) {
            result.error = (ErrorInfo){ERROR_MEMORY_ALLOC, "Stack push failed", pos};
            destroyTree(node);
            free(token.value);
            stree_destroy(stack);
            return result;
        }
        free(token.value);
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
        Token token = qlex_pop_front(q);
        printf("%s ", token.value);
        qlex_push_back(temp, token);
    }
    printf("\n");

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

    tree_result tree_res = convertToTree(postfix_queue);
    if (tree_res.error.code != RESULT_OK) {
        print_error(&tree_res.error);
        qlex_destroy(input_queue);
        qlex_destroy(postfix_queue);
        return EXIT_FAILURE;
    }

    printf("Expression tree:\n");
    printTreePretty(tree_res.root, 0);

    deleteUnitMultiply(&tree_res.root);
    printf("Simplified tree:\n");
    printTreePretty(tree_res.root, 0);

    qlex_destroy(input_queue);
    qlex_destroy(postfix_queue);
    destroyTree(tree_res.root);

    return EXIT_SUCCESS;
}