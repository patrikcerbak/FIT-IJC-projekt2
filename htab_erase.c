/*
 * file:        htab_erase.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t * t, htab_key_t key) {
    if(t == NULL || key == NULL) {
        return false;
    }
    // calculate the index for the key
    size_t index = htab_hash_function(key) % t->arr_size;
    // if the array at the index is empty, return false
    if(t->arr_ptr[index] == NULL) {
        return false;
    } else {
        // if it is the first item in the linked list
        if(strcmp(t->arr_ptr[index]->pair->key, key) == 0) {
            htab_item_t *erase = t->arr_ptr[index];
            t->arr_ptr[index] = erase->next;
            free((char *)erase->pair->key); // have to cast to (char *) to free the key
            free(erase->pair);
            free(erase);
            t->size--;
            // if the average linked list size is smaller than AVG_LEN_MIN, resize the table
            if((t->size / t->arr_size) < AVG_LEN_MIN) {
                // just to make sure to not resize to 0
                if(t->arr_size / 2 > 0) {
                    htab_resize(t, t->arr_size / 2);
                } else {
                    htab_resize(t, 1);
                }
            }
            return true;
        } else {
            htab_item_t *item = t->arr_ptr[index];
            // go through the linked list at the array index
            while(item->next != NULL) {
                // if the key is found, erase it
                if(strcmp(item->next->pair->key, key) == 0) {
                    htab_item_t *erase = item->next;
                    item->next = erase->next;
                    free((char *)erase->pair->key);
                    free(erase->pair);
                    free(erase);
                    t->size--;
                    // if the average linked list size is smaller than AVG_LEN_MIN, resize
                    if((t->size / t->arr_size) < AVG_LEN_MIN) {
                        if(t->arr_size / 2 > 0) {
                            htab_resize(t, t->arr_size / 2);
                        } else {
                            htab_resize(t, 1);
                        }
                    }
                    return true;
                }
                item = item->next;
            }
            return false;
        }
    }
}
