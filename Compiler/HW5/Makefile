
all:
	yacc -d ./kim.y
	lex ./kim.l
	gcc -m32 syntax.c lex.yy.c y.tab.c -o run

