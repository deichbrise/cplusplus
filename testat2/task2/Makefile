#
# Einfuehrung in die Programmiersprache C++
#
# Makefile fuer Aufgabe 4

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes  -std=c99 -pedantic

triangle_game: triangle_game.o triangle_routines.o
	$(CC) triangle_game.o triangle_routines.o -o triangle_game

triangle_example: triangle_example.o triangle_routines.o
	$(CC) triangle_example.o triangle_routines.o -o triangle_example

triangle_routines.o: triangle_routines.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_routines.c

triangle_example.o: triangle_example.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_example.c

triangle_game.o: triangle_game.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_game.c

test:
	./triangle_game < test_input

clean:
	rm -f *.o triangle_example triangle_game



