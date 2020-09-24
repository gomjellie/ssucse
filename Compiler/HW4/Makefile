CC = gcc
CC = gcc
TARGET = run
SRCS = lr_parser.c error_handler.c number.c node.c
OPT = -Wall -pedantic 

all:
	$(CC) $(SRCS) -o $(TARGET) $(OPT)

run:
	./ttop

test: all run

clean:
	rm -f $(TARGET)
	
debug:
	$(CC) -g $(SRCS) -o $(TARGET) $(OPT)
