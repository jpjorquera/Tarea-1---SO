TARGET = prog
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean

default: $(TARGET)

all: default

OBJECTS = src/organize.c src/id.c src/dir.c src/estructuras.c
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

run:
	./$(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)