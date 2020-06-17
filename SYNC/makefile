CC = gcc
FLAGS = -Wall -g
LIB = -pthread

all: 2_1_1 2_1_2 2_2_1 2_2_2 2_3_1 2_3_2

2_1_1: 2_1_1.o
	$(CC) $(FLAGS) $(LIB) 2_1_1.c -o 2_1_1

2_1_2: 2_1_2.o
	$(CC) $(FLAGS) $(LIB) 2_1_2.c -o 2_1_2

2_2_1: 2_2_1.o
	$(CC) $(FLAGS) $(LIB) 2_2_1.c -o 2_2_1

2_2_2: 2_2_2.o
	$(CC) $(FLAGS) $(LIB) 2_2_2.c -o 2_2_2

2_3_1: 2_3_1.o
	$(CC) $(FLAGS) $(LIB) 2_3_1.c -o 2_3_1

2_3_2: 2_3_2.o
	$(CC) $(FLAGS) $(LIB) 2_3_2.c -o 2_3_2



.PHONY: clean all

clean:
	rm -f *.o *.a *.so 2_1_1 2_1_2 2_2_1 2_2_2 2_3_1 2_3_2

