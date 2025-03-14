#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ui unsigned int

#define cyr_l_a 1072
#define cyr_l_ye 1077
#define cyr_l_yo 1105
#define cyr_l_i 1080
#define cyr_l_o 1086
#define cyr_l_u 1091
#define cyr_l_yi 1099
#define cyr_l_e 1101
#define cyr_l_yu 1102
#define cyr_l_ya 1103

#define cyr_u_a 1040
#define cyr_u_ye 1045
#define cyr_u_yo 1025
#define cyr_u_i 1048
#define cyr_u_o 1054
#define cyr_u_u 1059
#define cyr_u_yi 1067
#define cyr_u_e 1069
#define cyr_u_yu 1070
#define cyr_u_ya 1071

int unicode(int chr) {

    if (chr != EOF && chr < 128)
        return chr;
    return (chr & 0b00011111) << 6 | (getchar() & 0b00111111);

}



int code(int chr) {

    if (cyr_l_a <= chr && chr <= cyr_l_ya)
        return chr - cyr_l_a > 6 ? chr - cyr_l_a + 1 : (chr - cyr_l_a); 

    if (cyr_u_a <= chr && chr <= cyr_u_ya)
        return chr - cyr_u_a > 6 ? chr - cyr_u_a + 1: (chr - cyr_u_a); 
    
    if (chr == cyr_l_yo || chr == cyr_u_yo)
        return 6;
    
    return -1;

}

ui lat_mask() {

    ui set = 0;

    set |= 'a' - 'a';
    set |= 'e' - 'a';
    set |= 'i' - 'a';
    set |= 'o' - 'a';
    set |= 'u' - 'a';
    set |= 'y' - 'a';

    return set;

}

ui cyr_mask() {

    ui set = 0;

    set |= code(cyr_u_a);
    set |= code(cyr_u_ye);
    set |= code(cyr_u_yo);
    set |= code(cyr_u_i);
    set |= code(cyr_u_o);
    set |= code(cyr_u_u);
    set |= code(cyr_u_yi);
    set |= code(cyr_u_e);
    set |= code(cyr_u_yu);
    set |= code(cyr_u_ya);

    return set;

}

int issep(int chr) {
    return chr == ' ' || chr == ',' || chr == '\t' || chr == '\n' || chr == EOF;
}


int main() {
    
    bool isvowel = true;
    bool alphabet = false;

    ui lat_vowels = lat_mask();
    ui cyr_vowels = cyr_mask();

    ui lat_vowels_in_word = 0;
    ui cyr_vowels_in_word = 0;

    int chr = unicode(getchar());

    do {
        
        if (!issep(chr)) {

            if ((code(chr) & lat_vowels) == code(chr))
                lat_vowels_in_word |= code(chr);
            
            else if ((code(chr) & cyr_vowels) == code(chr))
                cyr_vowels_in_word |= code(chr);
        
        }

        else {

            if ((lat_vowels_in_word & lat_vowels) == lat_vowels)
                alphabet = true;
            
            else if ((cyr_vowels_in_word & cyr_vowels) == cyr_vowels)
                alphabet = true;

            lat_vowels_in_word = 0;
            cyr_vowels_in_word = 0;

        }
    } while ((chr = unicode(getchar())) != EOF);

    if (alphabet)
        printf("There is a word that contains all vowels\n");
    else
        printf("There is no word that contains all vowels\n");
}