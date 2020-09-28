%{
#include <stdio.h>
#include "y.tab.h"

extern char *var_name;
extern int yylex();
extern void yyerror(char *s);
double vbltable[333];
%}
/* %token NAME NUMBER */

%union  {
    double dval;
    int vblno;
}
%token    <vblno> NAME
%token    <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS
%type <dval> expression

%%
statement_list: statement '\n'
          |         statement_list statement '\n'
          ;
statement:        NAME '=' expression  { vbltable[$1] = $3; }
          |   expression               { printf("= %g\n", $1); }
          ;
expression: expression '+' expression  { $$ = $1 + $3;  }
          | expression '-' expression  { $$ = $1 - $3;  }
          | expression '*' expression  { $$ = $1 * $3;  }
          | expression '/' expression
                    {  if($3 == 0.0)
                             yyerror("divide by zero");
                       else   $$ = $1 /$3;
                    }
           |  '-' expression  %prec UMINUS   { $$ = -$2; }
           |  '(' expression ')'     { $$ = $2; }
           |       NUMBER     { $$ = $1; }
           |       NAME       { $$ = vbltable[$1]; }
           ;
%%

int main() {
    yyparse();
}
