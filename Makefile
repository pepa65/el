# Makefile for el - Extension lookup

APP := el
SELF := Makefile
SOURCES := el.c el.h
OBJECTS := el.o
WARNING := -Wall -Wextra

.PHONY: all clean

all: $(APP)

clean:
	$(RM) $(OBJECTS)

$(OBJECTS): $(SOURCES) $(SELF)
	$(CC) $(WARNING) -c $< -o $@

$(APP): $(OBJECTS)
	$(CC) $(WARNING) $^ -o $@
