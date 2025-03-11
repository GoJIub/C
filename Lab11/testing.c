#include <stdio.h>

enum state {
    OUT_OF_WORD,
    IN_WORD
};

char Caesar(char chr, int shift) {
    if (chr >= 'A' && chr <= 'Z') {
        chr = ((chr - 'A' + shift) % 26) + 'A';
    } else if (chr >= 'a' && chr <= 'z') {
        chr = ((chr - 'a' + shift) % 26) + 'a';
    }
    return chr;
}

int issep(char chr) {
    return chr == ' ' || chr == '\t' || chr == '\n';
}

int main() {
    int shift = 3;
    char chr;
    char res[1024] = "";
    int index = 0; 
    enum state state = OUT_OF_WORD;

    while ((chr = getchar()) != EOF) {

        if (state == OUT_OF_WORD) {
            if (!issep(chr)) {
                state = IN_WORD;
                chr = Caesar(chr, shift);
            }
        }
        else if (state == IN_WORD) {
            if (issep(chr)) {
                state = OUT_OF_WORD;
                shift = 3;
            } else {
                shift++;
                chr = Caesar(chr, shift);
            }
        }

        res[index++] = chr; 
    }

    printf("%s\n", res);
}