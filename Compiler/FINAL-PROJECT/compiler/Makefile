YACC = yacc
LEX = lex

all: y.tab.c lex.yy.c
	gcc gen.c lex.yy.c main.c print_ast.c print_sem.c semantic.c syntax.c y.tab.c -o compiler -m32 -w

y.tab.c: parse.y
	$(YACC) -d parse.y

lex.yy.c : scan.l
	$(LEX) scan.l

