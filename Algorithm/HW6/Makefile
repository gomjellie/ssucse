CC = gcc
TAR = run
SRCS = main.c
OPTS = -Wall -pedantic

all:
	$(CC) $(SRCS) -o $(TAR) $(OPTS)

test:
	cat input.txt | ./$(TAR)

test: all run

clean:
	rm $(TAR)
	
debug:
	$(CC) -g $(SRCS) -o $(TAR) $(OPTS)
