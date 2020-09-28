%{
#include <stdio.h>
#include "y.tab.h"

extern char *var_name;
extern int yylex();
extern void yyerror(char *s);
%}
%token NAME NUMBER
%%
statement:    NAME '=' expression { printf("%s = %d\n", var_name, $3); }
            | expression  { printf("_ = %d\n", $1); }
            ;
expression:   expression '+' NUMBER { $$ = $1 + $3; }
            |   expression '-' NUMBER { $$ = $1 - $3; }
            |   NUMBER  { $$ = $1; }
            ;

