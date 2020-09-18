#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum _token {
    NUMBER = 256, PLUS, STAR, LP, RP, END,
} TOKEN;

enum {
     EXPRESSION, TERM, FACTOR, ACC = 999,
};

int action[12][6] = {
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 0, ACC},
    {0, -2, 7, 0, -2, -2},
    {0, -4, -4, 0, -4, -4},
    {5, 0, 0, 4, 0, 0},
    {0, -6, -6, 0, -6, -6},
    {5, 0, 0, 4, 0, 0},
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 11, 0},
    {0, -1, 7, 0, -1, -1},
    {0, -3, -3, 0, -3, -3},
    {0, -5, -5, 0, -5, -5},
};

int go_to[12][3] = {
    {1, 2, 3},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {8, 2, 3},
    {0, 0, 0},
    {0, 9, 3},
    {0, 0, 10},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

int prod_left[7] = {
    0, EXPRESSION, EXPRESSION, TERM, TERM, FACTOR, FACTOR,
};
int prod_length[7] = {
    0, 3, 1, 3, 1, 3, 1,
};

int stack[1000]; int top = -1; int sym;

int yylex();
void yyparse();
void push(int i);
void shift(int i);
void reduce(int i);
void lex_error(const char *msg);
void error(const char *msg);

int main() {
    yyparse();
}

void yyparse() {
    int i;
    stack[++top] = 0;
    sym = yylex();
    do {
        i = action[stack[top]][sym-256]; // get relation
        if (i == ACC)
            puts("success !");
        else if (i > 0) shift(i);
        else if (i < 0) reduce(-i);
        else error("yyerror!");
    } while (i != ACC);
}

void push(int i) {
    stack[++top] = i;
}

void shift(int i) {
    push(i);
    sym = yylex();
}

void reduce(int i) {
    int old_top;
    top -= prod_length[i];
    old_top = top;
    push(go_to[stack[old_top]][prod_left[i]]);
}

void error(const char *msg) {
    fprintf(stderr, "%s", msg);
    exit(1);
}

int yylex() {
    static char ch = ' ';
    int i = 0;
    while (ch == ' ' || ch == '\t') ch = getchar();
    
    if (isdigit(ch)) {
        do {
            ch = getchar();
        } while (isdigit(ch));
        return NUMBER;
    }
    else if (ch == '+') { ch = getchar(); return PLUS; }
    else if (ch == '*') { ch = getchar(); return STAR; }
    else if (ch == '(') { ch = getchar(); return LP; }
    else if (ch == ')') { ch = getchar(); return RP; }
    else if (ch == EOF || ch == '\n') return END;
    error("lex error");
    return -1;
}
