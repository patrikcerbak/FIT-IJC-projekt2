/*
 * file:        io.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdio.h>
#include <ctype.h>
#include "io.h"

int read_word(char *s, int max, FILE *f) {
    if(s == NULL || max < 1 || f == NULL) {
        return -1;
    }
    int character = 0;
    int i = 0;
    // read whitespace characters
    while ((character = getc(f)) != EOF && isspace(character)) {
        continue;
    }
    // check if the end of file was reached
    if(character == EOF) {
        return EOF;
    }
    // if not, load the character
    s[i++] = character;
    // read the rest of the word
    while ((character = getc(f)) != EOF && !isspace(character) && i < max) {
        s[i++] = character;
    }
    // end character
    s[i] = '\0';
    return i;
}
