/*
 * file:        htab_size.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include "htab.h"
#include "htab_private.h"

size_t htab_size(const htab_t * t) {
    if(t == NULL) {
        return 0;
    }
    // return total number of items in the table
    return t->size;
}
