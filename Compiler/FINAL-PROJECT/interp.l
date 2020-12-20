digit            [0-9]
letter            [a-zA-Z_]
delim            [ \t]
line            [\n]
ws            {delim}+

%{
#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;
#include "y.tab.h"

int line_no=1;

int search_opcode();
int is_inst2();
char *makeString();
%}

%%

{ws}        { }
{line}        { line_no++; return(NEW_LINE);};
"\.global_word"    { return(GLOBAL_WORD_SYM);}
"\.global_byte"    { return(GLOBAL_BYTE_SYM);}
"\.literal"    { return(LITERAL_SYM);}
"\:"        { return(COLON); }
"\,"        { return(COMMA); }


(\-)?{digit}+            { yylval=atoi(yytext); return(INTEGER);}
{digit}+\.{digit}+        { yylval=makeString(yytext); return(FLOAT);}
{letter}({letter}|{digit})*    { yylval=search_opcode(yytext); 
                  if (yylval==0) { 
                    yylval=makeString(yytext);
                    return(IDENTIFIER);}
                  else if (is_inst2(yylval)) return (INST2); 
                  else return(INST1);}
\"([^"\n]|\\["\n])*\"        { yylval=makeString(yytext); return(STRING);}
\'([^'\n]|\'\')\'        { yylval=*(yytext+1); return(CHAR);}

%%

char *makeString(char *s)
{
    char *t;
    t=malloc(strlen(s)+1);
    strcpy(t,s);
    return(t);


}


yywrap()
{
    return(1);
}
