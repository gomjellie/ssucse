CC = gcc
TAR = run
SRCS = chain_htable.c hash_table.c main.c
OPTS = -Wall -pedantic

all:
	$(CC) $(SRCS) -o $(TAR) $(OPTS)

run:
	./$(TAR)

test: all run

clean:
	rm $(TAR)
	
debug:
	$(CC) -g $(SRCS) -o $(TAR) $(OPTS)
