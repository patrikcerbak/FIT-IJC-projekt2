/*
 * file:        htab_init.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) {
    if(n == 0) {
        return NULL;
    }
    // allocate memory for the table
    htab_t *h_table = malloc(sizeof(htab_t));
    if(h_table == NULL) {
        return NULL;
    }
    // allocate memory for the array
    h_table->arr_ptr = malloc(n * sizeof(htab_item_t *));
    if(h_table->arr_ptr == NULL) {
        free(h_table);
        return NULL;
    }

    h_table->arr_size = n;
    h_table->size = 0;

    // fill the array with NULL
    for(size_t i = 0; i < n; i++) {
        h_table->arr_ptr[i] = NULL;
    }

    return h_table;
}
