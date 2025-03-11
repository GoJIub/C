#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 1000

typedef struct {
    unsigned int set;
} set;

void set_add(set *s, char c) {
    s->set |= (1u << (c - 'a'));
}

int set_contains(set *s, char c) {
    return s->set & (1u << (c - 'a'));
}

int is_consonant(char c) {
    const char consonants[] = "bcdfghjklmnpqrstvwxyz";
    return strchr(consonants, c) != NULL;
}

int is_whistling_consonant(char c) {
    const char consonants[] = "szxc";
    return strchr(consonants, c) != NULL;
}

int check_consonants(const char *word) {

    for (int i = 0; word[i] != '\0'; ++i) {
        char c = word[i];
        c = tolower(c);

        if (is_consonant(c)) {
            if (!is_whistling_consonant(c)) {
                return 0;
            }
        }
    }

    return 1;
}

void process_line(const char *line) {
    char word[MAX_WORD_LENGTH];
    int i = 0, word_len = 0;

    for (int j = 0; line[j] != '\0'; ++j) {
        char c = line[j];

        if (isspace(c) || c == ',' || c == '\t' || c == '\n') {
            if (word_len > 0) {
                word[word_len] = '\0';
                if (check_consonants(word)) {
                    printf("Слово '%s' состоит только из свистящих согласных.\n", word);
                } else {
                    printf("Слово '%s' состоит не только из свистящих согласных.\n", word);
                }
                word_len = 0;
            }
        } else {
            word[word_len++] = c;
        }
    }
}

int main() {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), stdin)) {
        process_line(line);
    }

    return 0;
}