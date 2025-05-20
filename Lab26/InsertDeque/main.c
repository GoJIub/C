#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque_str.h"
#include "sort.h"

char* read_line() {
    int capacity = 128;
    int len = 0;
    char* buffer = malloc(capacity);
    if (!buffer) return NULL;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[len++] = (char)c;
        if (len >= capacity - 1) {
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);
            if (!tmp) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
    }
    buffer[len] = '\0';
    if (c == EOF && len == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

int main(void) {

    deque_str* d = dstr_create(10);
    if (!d) {
        fprintf(stderr, "Error: Could not create deque\n");
        return 1;
    }
    
    printf("Enter lines (empty line to finish):\n");
    while (1) {
        char* line = read_line();
        if (!line) break;
        if (line[0] == '\0') {
            free(line);
            break;
        }
        if (!dstr_push_back(d, line)) {
            fprintf(stderr, "Error: Could not add line\n");
            free(line);
            dstr_destroy(d);
            return 0;
        }
        free(line);
    }
    
    insert_sort(d);
    
    printf("Sorted lines:\n");
    while (!dstr_is_empty(d)) {
        char* s = dstr_pop_front(d);
        printf("%s\n", s);
        free(s);
    }
    dstr_destroy(d);
}
