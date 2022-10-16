/*
 * file:        htab_lookup_add.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    if(t == NULL || key == NULL) {
        return NULL;
    }
    // get the hash value
    size_t index = htab_hash_function(key) % t->arr_size;
    // if the index is not empty, try to find the key
    if(t->arr_ptr[index] != NULL) {
        htab_item_t *item = t->arr_ptr[index];
        while(item->next != NULL) {
            if(strcmp(item->pair->key, key) == 0) {
                return item->pair;
            }
            item = item->next;
        }
        // if the last item is the key, return it
        if(strcmp(item->pair->key, key) == 0) {
            return item->pair;
        // else add the new item to the list
        } else {
            // allocate memory for the new item
            htab_item_t *new_item = malloc(sizeof(htab_item_t));
            if(item == NULL) {
                return NULL;
            }
            new_item->pair = malloc(sizeof(htab_pair_t));
            if(item->pair == NULL) {
                free(new_item);
                return NULL;
            }
            char *pair_key = malloc(sizeof(char) * strlen(key) + 1);
            if(pair_key == NULL) {
                free(new_item->pair);
                free(new_item);
                return NULL;
            }
            // copy the key
            strcpy(pair_key, key);
            new_item->pair->key = pair_key;
            new_item->pair->value = 0;
            new_item->next = NULL;
            item->next = new_item;
            t->size++;
            // if the table is big enough, resize it
            if((t->size / t->arr_size) > AVG_LEN_MAX) {
                htab_resize(t, t->arr_size * 2);
            }

            return new_item->pair;
        }
    // the array at the index is empty, create the item
    } else {
        // allocate memory for the new item
        htab_item_t *new_item = malloc(sizeof(htab_item_t));
        if(new_item == NULL) {
            return NULL;
        }
        new_item->pair = malloc(sizeof(htab_pair_t));
        if(new_item->pair == NULL) {
            free(new_item);
            return NULL;
        }
        char *pair_key = malloc(sizeof(char) * strlen(key) + 1);
        if(pair_key == NULL) {
            free(new_item->pair);
            free(new_item);
            return NULL;
        }
        // copy the key
        strcpy(pair_key, key);
        new_item->pair->key = pair_key;
        new_item->pair->value = 0;
        new_item->next = NULL;
        t->arr_ptr[index] = new_item;
        t->size++;
        // resize the table if necessary
        if((t->size / t->arr_size) > AVG_LEN_MAX) {
            htab_resize(t, t->arr_size * 2);
        }

        return new_item->pair;
    }
}
