/*
 * file:        tail.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * project:     IJC DU2, 1)
 * compiler:    gcc 11.2.1
 * date:        18.4.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 4095
#define DEFAULT_LINES 10

// loads the lines to a circular buffer and returns current position in the buffer
int load_lines(FILE *fp, char **lines, long num_of_lines) {

    int character = 0;
    int position = 0; // current position in circular buffer
    int i = 0; // current character index in array
    int end = 0; // end of while loop flag
    int printed_error = 0; // error flag

    while(!end) {
        character = getc(fp);
        if(character == EOF) {
            end = 1;
        } else {
            // check if the line is too long
            if(i == MAX_LENGTH && character != '\n') {
                // check if the error was already printed
                if(!printed_error) {
                    fprintf(stderr, "Error: the line is too long!\n");
                    printed_error = 1;
                }
                // skip the rest of the line
                while(character != '\n') {
                    character = getc(fp);
                }
                // load the '\n' and '\0' characters
                lines[position][i] = character;
                lines[position][i+1] = '\0';
                // reset the index
                i = 0;
                // increment the position
                if(++position == num_of_lines) {
                    position = 0;
                }
            } else {
                // if the line is not too long, check if the character is '\n'
                if(character == '\n') {
                    // load '\n' and '\0' characters, reset the index and increment the position
                    lines[position][i] = character;
                    lines[position][i+1] = '\0';
                    i = 0;
                    if(++position == num_of_lines) {
                        position = 0;
                    }
                // else load the character
                } else {
                    lines[position][i] = character;
                    i++;
                }
            }
        }
    }
    return position;
}

// a function for printing all the lines in a circular buffer
void print_lines(char **lines, long num_of_lines, int position) {
    int i = 0;
    while(i < num_of_lines) {
        printf("%s", lines[position]);
        if(++position == num_of_lines) {
            position = 0;
        }
        i++;
    }
}

int main(int argc, char **argv) {
    FILE *fp;

    // default values
    fp = stdin;
    long num_of_lines = DEFAULT_LINES;

    // parse arguments
    if(argc > 4) {
        fprintf(stderr, "Error: too many arguments!\n");
        return 1;
    }
    for(int i = 1; i < argc; i++) {
        // check if the argument is -n
        if(strcmp(argv[i], "-n") == 0) {
            if(i+1 < argc) {
                char *temp_ptr;
                // check if the argument after -n is a number
                num_of_lines = strtol(argv[++i], &temp_ptr, 10);
                // check if the number is valid
                if(temp_ptr[0] != '\0' || num_of_lines < 0) {
                    fprintf(stderr, "Error: invalid number of lines!\n");
                    return 1;
                } else if(num_of_lines == 0) {
                    // print zero lines
                    return 0;
                }
            } else {
                // missing the number after -n
                fprintf(stderr, "Error: missing number of lines!\n");
                return 1;
            }
        } else {
            // get the filename argument
            fp = fopen(argv[i], "r");
            // check if the file is valid
            if(fp == NULL) {
                fprintf(stderr, "Error: cannot open file!\n");
                return 1;
            }
        }
        
    }

    // allocate memory for the circular buffer of lines
    char **lines = (char**)malloc(num_of_lines * sizeof(char *));
    if(lines == NULL) {
        fprintf(stderr, "Error: memory allocation failed!\n");
        return 1;
    }
    for(int i = 0; i < num_of_lines; i++) {
        lines[i] = calloc((MAX_LENGTH + 1 + 1), sizeof(char)); // MAX_LENGTH + '\n' + '\0'
        if(lines[i] == NULL) {
            fprintf(stderr, "Error: memory allocation failed!\n");
            return 1;
        }
    }

    // load and print the lines
    int position = load_lines(fp, lines, num_of_lines);
    print_lines(lines, num_of_lines, position);

    // close the file and free memory
    fclose(fp);
    for(long i = 0; i < num_of_lines; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
