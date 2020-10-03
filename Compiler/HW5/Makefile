YACC = yacc
LEX = lex

all: y.tab.c lex.yy.c
	# yacc -d ./kim.y
	# lex ./kim.l
	gcc lex.yy.c y.tab.c -o run

y.tab.c: kim.y
	$(YACC) -d kim.y

lex.yy.c : kim.l
	$(LEX) kim.l

