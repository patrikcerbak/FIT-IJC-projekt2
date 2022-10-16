/*
 * file:        htab_for_each.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    if(t == NULL || f == NULL) {
        return;
    }

    // go through the array and call the function on each pair it contains
    for(size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->arr_ptr[i];
        while(item != NULL) {
            f(item->pair);
            item = item->next;
        }
    }
}
