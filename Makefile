# Makefile for el - Extension lookup

SOURCES := el.c el.h
OBJECTS := el.o
WARNING := -Wall -Wextra

.PHONY: all clean

all: el

clean:
	rm el.o

el.o: el.c el.h Makefile
	$(CC) $(WARNING) -c $< -o $@

el: el.o
	$(CC) $(WARNING) $^ -o $@
