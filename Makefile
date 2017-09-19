TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -Wall -Llib -lid3v2

.PHONY: default all clean

default: $(TARGET)

all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

run:
	./prog

clean:
	-rm -f *.o
	-rm -f $(TARGET)