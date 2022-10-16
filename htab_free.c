/*
 * file:        htab_free.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t * t) {
    if(t == NULL) {
        return;
    }
    // free the table
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}
