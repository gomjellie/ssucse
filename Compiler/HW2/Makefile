all: build

build: lr_parser.c
	gcc lr_parser.c -o run

debug: lr_parser.c
	gcc -g lr_parser.c -o lr_parser

test:
	cat input.txt | ./run
