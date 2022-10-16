/*
 * file:        htab_clear.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t * t) {
    if(t == NULL) {
        return;
    }

    // go through the array and free every key, pair and item
    for(size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->arr_ptr[i];
        // go through the linked list at each array index
        while(item != NULL) {
            htab_item_t *erase = item;
            item = item->next;
            free((char *)erase->pair->key); // have to cast to (char *) to free the key
            free(erase->pair);
            free(erase);
            t->size--;
        }
    }
}
