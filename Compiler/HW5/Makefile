
all:
	yacc -d ./c.y
	lex ./c.l
	gcc -m32 main.c syntax.c lex.yy.c y.tab.c -o run

