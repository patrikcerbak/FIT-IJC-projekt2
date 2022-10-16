#
# file:        Makefile
# autor:       Patrik Čerbák - xcerba00, FIT
# project:     IJC DU2, 2)
# compiler:    gcc 11.2.1
# date:        20.4.2022
#

CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2
PROGRAMS = tail libhtab.a libhtab.so wordcount wordcount-dynamic
HTAB_LIB = htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_resize.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
#CFLAGS += -DHASHTEST

all: $(PROGRAMS)

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o io.o -o wordcount-dynamic -L. -lhtab

wordcount: wordcount.o io.o libhtab.a
	$(CC) -static wordcount.o io.o -o wordcount -L. -lhtab

# static library
libhtab.a: $(HTAB_LIB)
	ar crs libhtab.a $^

# shared library
libhtab.so: $(HTAB_LIB)
	$(CC) -shared -fPIC $^ -o libhtab.so

# compile object files
%.o: %.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC $^

clean:
	rm -f *.o *.gch $(PROGRAMS)

zip:
	zip xcerba00.zip *.c *.h Makefile
