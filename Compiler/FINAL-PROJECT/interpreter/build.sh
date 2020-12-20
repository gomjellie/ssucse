
yacc -d interp.y
lex interp.l
cc y.tab.c lex.yy.c interp.c lib.c -o interpreter
