
all:
	yacc -d ./kim.y
	lex ./kim.l
	gcc syntax.c lex.yy.c y.tab.c -o run
