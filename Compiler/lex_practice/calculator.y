%{
#include <stdio.h>
#include "y.tab.h"

extern int yylex();
extern void yyerror(char *s);
%}
%token NAME NUMBER
%%
statement:    NAME '=' expression
            | expression  { printf("= %d\n", $1); }
            ;
expression:   expression '+' NUMBER { $$ = $1 + $3; }
            |   expression '-' NUMBER { $$ = $1 - $3; }
            |   NUMBER  { $$ = $1; }
            ;

