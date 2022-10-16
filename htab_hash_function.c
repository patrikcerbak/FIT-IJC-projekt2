/*
 * file:        htab_hash_function.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdint.h>
#include "htab.h"

// this function is taken from the asignment
// source of the function is: http://www.cse.yorku.ca/~oz/hash.html - sdbm variant
size_t htab_hash_function(const char *str) {
    uint32_t h=0;
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
