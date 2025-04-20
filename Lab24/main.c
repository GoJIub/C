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
    return c == '^' || c == '~' || c == '!';
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

read_result* readline(queue_lex* out) {
    read_result* res = malloc(sizeof(read_result));
    res->queue = out;
    int prev = 0;
    int cur = getchar();

    while (cur != EOF && cur != '\n') {
        if (is_const(cur) || is_var(cur)) {
            qlex_push_back(out, cur);
        } else if (is_op(cur)) {
            if (cur == '-') {
                if (prev == 0 || is_op(prev) || is_p_left(prev))
                    qlex_push_back(out, '~');
                else
                    qlex_push_back(out, cur);
            } else {
                qlex_push_back(out, cur);
            }
        } else if (is_p_left(cur) || is_p_right(cur)) {
            qlex_push_back(out, cur);
        } else if (!isspace(cur)) {
            res->code = 1;
            return res;
        }
        prev = cur;
        cur = getchar();
    }
    res->code = 0;
    return res;
}

postfix_result* convertToPostfix(queue_lex* q, queue_lex* out) {
    postfix_result* res = malloc(sizeof(postfix_result));
    res->queue = out;
    stack_lex* s = slex_create(2);
    char lex;
    
    while (!qlex_is_empty(q)) {
        lex = qlex_pop_front(q);
        
        if (is_const(lex) || is_var(lex)) {
            qlex_push_back(out, lex);
        }
        else if (is_p_left(lex)) {
            slex_push_back(s, lex);
        }
        else if (is_p_right(lex)) {
            while (!slex_is_empty(s) && !is_p_left(slex_top(s))) {
                qlex_push_back(out, slex_pop_back(s));
            }
            if (slex_is_empty(s)) {
                res->code = 1;
                return res;
            }
            slex_pop_back(s);
        }
        else if (is_op(lex)) {
            while (!slex_is_empty(s) && 
                   !is_p_left(slex_top(s)) && 
                   should_displace(lex, slex_top(s))) {
                qlex_push_back(out, slex_pop_back(s));
            }
            slex_push_back(s, lex);
        }
    }
    while (!slex_is_empty(s)) {
        lex = slex_pop_back(s);
        if (is_p_left(lex)) {
            res->code = 2;
            return res;
        }
        qlex_push_back(out, lex);
    }
    
    slex_destroy(s);
    res->code = 0;
    return res;
}

tree convertToTree(queue_lex* q) {
    stack_tree* stack = stree_create(10);
    
    while (!qlex_is_empty(q)) {
        char token = qlex_pop_front(q);
        tree node = build(token, NULL, NULL);
        
        if (is_op(token)) { // Проверяем, является ли токен оператором
            if (token == '~' || token == '!') { // Унарные операторы
                node->right = stree_pop_back(stack);
            } else { // Бинарные операторы
                node->right = stree_pop_back(stack);
                node->left = stree_pop_back(stack);
            }
        }
        stree_push_back(stack, node);
    }
    
    tree root = stree_pop_back(stack);
    stree_destroy(stack);
    return root;
}

int main() {
    queue_lex* input = qlex_create(1);
    read_result* read = readline(input);

    if (read->code != 0) {
        printf("Expression isn\'t correct\n");
        free(read);
        qlex_destroy(input);
        return 0;
    }

    // Создаем временную очередь для печати исходного выражения
    queue_lex* temp_print = qlex_create(1);
    printf("Input: ");
    while (!qlex_is_empty(input)) {
        char c = qlex_pop_front(input);
        printf("%c ", c);
        qlex_push_back(temp_print, c);
    }
    printf("\n");

    // Восстанавливаем исходную очередь
    while (!qlex_is_empty(temp_print)) {
        qlex_push_back(input, qlex_pop_front(temp_print));
    }
    qlex_destroy(temp_print);

    // Преобразуем в постфиксную запись
    queue_lex* postfix = qlex_create(1);
    postfix_result* conversion = convertToPostfix(input, postfix);

    if (conversion->code != 0) {
        printf("Error: Postfix conversion failed\n");
        free(conversion);
        qlex_destroy(input);
        qlex_destroy(postfix);
        return 0;
    }

    // Создаем копию postfix для печати
    queue_lex* postfix_copy = qlex_create(1);
    printf("Postfix: ");
    while (!qlex_is_empty(postfix)) {
        char c = qlex_pop_front(postfix);
        printf("%c ", c);
        qlex_push_back(postfix_copy, c);
    }
    printf("\n");

    // Строим дерево из копии postfix
    tree Tree = convertToTree(postfix_copy);
    printf("Tree:\n");
    printTreePretty(Tree, 0);
    printf("\n");

    free(read);
    free(conversion);
    qlex_destroy(input);
    qlex_destroy(postfix);
    qlex_destroy(postfix_copy);
    destroyTree(Tree);

    return 0;
}