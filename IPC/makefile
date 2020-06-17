CC = gcc
FLAGS = -Wall -g

all: ipc

ipc: ipc.o
	$(CC) $(FLAGS) ipc.c -o ipc

.PHONY: clean all

clean:
	rm -f *.o *.a *.so ipc
