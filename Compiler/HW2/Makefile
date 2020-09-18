all: build

build: lr_parser.c
	gcc lr_parser.c -o run

test:
	cat input.txt | ./run
