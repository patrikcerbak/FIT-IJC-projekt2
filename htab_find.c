/*
 * file:        htab_find.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <string.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    if(t == NULL || key == NULL) {
        return NULL;
    }

    size_t index = htab_hash_function(key) % t->arr_size;
    // check if the index is empty
    if(t->arr_ptr[index] == NULL) {
        return NULL;
    }

    // go through the linked list and try to find the key
    htab_item_t *item = t->arr_ptr[index];
    while(item != NULL) {
        if(strcmp(item->pair->key, key) == 0) {
            return item->pair;
        }
        item = item->next;
    }
    return NULL;
}
