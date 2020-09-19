CC = gcc

all:
	$(CC) sort.c -o sort -Wall -pedantic

run:
	./sort

test: all run

clean:
	rm sort;
	
debug:
	$(CC) -g sort.c -o sort -Wall -pedantic
