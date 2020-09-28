
all:
	yacc ./calculator.y -d
	lex ./calculator.l
	gcc lex.yy.c y.tab.c -o run -ly -ll
