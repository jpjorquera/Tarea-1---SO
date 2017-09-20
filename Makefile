TARGET = prog
CC = gcc
CFLAGS = -Wall -Llib -lid3v2

.PHONY: default all clean

default: $(TARGET)

all: default

OBJECTS = test2.c src/id.c
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