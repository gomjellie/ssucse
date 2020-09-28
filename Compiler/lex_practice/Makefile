CC = gcc
TARGET = run
SRCS = lex.yy.c
OPT = -Wall -pedantic 
LIBS = -ll

all: lex.yy.c
	$(CC) $(SRCS) -o $(TARGET) $(OPT) $(LIBS)

run:
	./$(TARGET)

test: all run

clean:
	rm -f $(TARGET)

lex.yy.c:
	lex ./calculator.l

debug: calculator.l
	$(CC) -g $(SRCS) -o $(TARGET) $(OPT) $(LIBS)
