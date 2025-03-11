#include <stdio.h>

enum state {
    OUT_OF_COMMENT, // = 0
    MAYBE_COMMENT, // = 1
    OUT_OF_WORD, // = 2
    IN_WORD // = 3
};

int issep (char chr) {
    return chr == ' ' || chr == '\t' || chr == EOF;
}

// я пишу пример

int main () {

    enum state state = OUT_OF_COMMENT;
    int k = 0;
    int chr;

    do {
        chr = getchar();

        if (state == OUT_OF_COMMENT) {
            if (chr == '/')
                state = MAYBE_COMMENT;
        }
        else if (state == MAYBE_COMMENT) {
            if (chr == '/')
                state = OUT_OF_WORD;
            else
                state = OUT_OF_COMMENT;
        }
        else if (state == OUT_OF_WORD) {
            if (chr == '\n')
                state = OUT_OF_COMMENT;
            else if (!issep(chr))
                state = IN_WORD;
        }
        else if (state == IN_WORD) {
            if (chr == '\n') {
                state = OUT_OF_COMMENT;
                k++;    
            }
            else if (issep(chr)) {
                state = OUT_OF_WORD;
                k++;
            }
        }

    } while (chr != EOF);

    printf("%d\n", k);
}
// ещё пример