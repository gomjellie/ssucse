
all:
	yacc -d ./kim.y
	lex ./kim.l
	gcc lex.yy.c y.tab.c -o run
