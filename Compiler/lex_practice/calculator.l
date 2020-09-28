%{
#include  "y.tab.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern double vbltable[333];
%}

%%
([0-9]+|([0-9]*\.[0-9]+))  { yylval.dval = atof(yytext); return NUMBER; }
[ \t]   ;
[a-z]    {      yylval.vblno = yytext[0] - 'a'; return NAME; }
"$"      { return 0; }
\n |
. return  yytext[0];
%%

void yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}
