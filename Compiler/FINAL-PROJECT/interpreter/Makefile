YACC = yacc
LEX = lex

all: y.tab.c lex.yy.c
	cc y.tab.c lex.yy.c interp.c lib.c -o interpreter -w

y.tab.c: interp.y
	$(YACC) -d interp.y

lex.yy.c : interp.l
	$(LEX) interp.l

