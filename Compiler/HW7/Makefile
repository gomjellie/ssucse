YACC = yacc
LEX = lex

all: y.tab.c lex.yy.c
	gcc lex.yy.c y.tab.c print_sem.c print.c syntax.c semantic.c main.c -o run -m32 -w

y.tab.c: kim.y
	$(YACC) -d kim.y

lex.yy.c : kim.l
	$(LEX) kim.l

debug: y.tab.c lex.yy.c
	gcc -g lex.yy.c y.tab.c print_sem.c print.c syntax.c semantic.c main.c -o run -m32 -w

