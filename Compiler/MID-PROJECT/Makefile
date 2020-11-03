YACC = yacc
LEX = lex

all: y.tab.c lex.yy.c
	gcc lex.yy.c y.tab.c main.c print.c syntax.c -o run

y.tab.c: kim.y
	$(YACC) -d kim.y

lex.yy.c : kim.l
	$(LEX) kim.l

