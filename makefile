CC = gcc
CFLAGS = -Wall -g

all: graph

graph: main.o nodes.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o graph