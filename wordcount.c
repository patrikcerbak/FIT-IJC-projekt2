/*
 * file:        wordcount.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 2)
 * compiler:    gcc 11.2.1
 * date:        19.4.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "htab.h"
#include "io.h"

// limit for the length of a word
#define LIMIT 128

#ifdef HASHTEST
    // this function is edited "lose lose" hash function that appeared in K&R
    // source is here: http://www.cse.yorku.ca/~oz/hash.html
    size_t htab_hash_function(const char *str) {
	    uint32_t hash = 0;
	    int c;
	    while ((c = *str++) != '\0') {
            hash += c;
        }
	    return hash;
    }
#endif

// a function for printing the pair key and its value
void print_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    // i chose a prime number close to 1000, for a nice balance between performance and memory usage
    htab_t *t = htab_init(1009);
    if(t == NULL) {
        fprintf(stderr, "Error: initiation of the table failed!\n");
        return 1;
    }

    char key[LIMIT];
    int word_length = 0;
    int printed_error = 0;

    // load the words from stdin
    while((word_length = read_word(key, LIMIT, stdin)) != EOF) {
        if(word_length == LIMIT) {
            if(!printed_error) {
                fprintf(stderr, "Error: word is too long!\n");
                printed_error = 1;
            }
        }
        
        // add the word to the table (if it is not already there)
        htab_pair_t *pair = htab_lookup_add(t, key);
        if(pair == NULL) {
            fprintf(stderr, "Error: adding the word to the table failed!\n");
            return 1;
        }
        pair->value++;
    }

    htab_for_each(t, print_pair); // print all the pairs in the table

    // free the table
    htab_free(t);
    return 0;
}
