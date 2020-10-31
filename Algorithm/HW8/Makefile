CC = gcc
TAR = run
SRCS = main.c 1.c 2.c 3.c
OPTS = --std=c11 -Wall -pedantic

all:
	$(CC) $(SRCS) -o $(TAR) $(OPTS)

test:
	cat input.txt | ./$(TAR)

test: all run

clean:
	rm $(TAR)
	
debug:
	$(CC) -g $(SRCS) -o $(TAR) $(OPTS)
