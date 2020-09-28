%{
#include  "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
extern int  yylval;
char *var_name;
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%
{DIGIT}+ { yylval = atoi(yytext); return NUMBER;  }
{ID} { var_name = strdup(yytext); return NAME; }
[\t ]+ ;
\n return 0;
. return  yytext[0];
%%

void yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}
