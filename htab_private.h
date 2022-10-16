/*
 * file:        htab_private.h
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

// this is a private header file for the library

#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include "htab.h"

// these values are used for determining whether to resize the table or not
#define AVG_LEN_MIN 2
#define AVG_LEN_MAX 20

// item strucure
typedef struct htab_item {
    struct htab_pair *pair;
    struct htab_item *next;
} htab_item_t;

// hash table structure
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

#endif
