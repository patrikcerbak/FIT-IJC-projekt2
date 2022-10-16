/*
 * file:        htab_resize.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_resize(htab_t *t, size_t newn) {
    if(t == NULL || newn == 0) {
        return;
    }
    // allocate new array
    htab_item_t **resized_array = malloc(newn * sizeof(htab_item_t *));
    if(resized_array == NULL) {
        return;
    }
    for(size_t i = 0; i < newn; i++) {
        resized_array[i] = NULL;
    }
    for(size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->arr_ptr[i];
        while(item != NULL) {
            // "copy" the item from old array to new array (to the start of each list)
            htab_item_t *temp = item;
            size_t new_index = htab_hash_function(temp->pair->key) % newn;
            item = item->next;
            temp->next = resized_array[new_index];
            resized_array[new_index] = temp;
        }
    }

    // free the old array and set the new one
    free(t->arr_ptr);
    t->arr_ptr = resized_array;
    t->arr_size = newn;
}
