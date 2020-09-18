#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FF 0

typedef enum _token {
    NUMBER, PLUS, STAR, LP, RP, END,
} TOKEN;

enum {
     EXPRESSION, TERM, FACTOR, ACC = 999,
};

enum { // shifts
    S1 = 1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11,
};

enum { // reduce
    R6 = -6, R5, R4, R3, R2, R1,
};

int action[12][6] = {
    {S5, FF, FF, S4, FF, FF},
    {FF, S6, FF, FF, FF, ACC},
    {FF, R2, S7, FF, R2, R2},
    {FF, R4, R4, FF, R4, R4},
    {S5, FF, FF, FF, FF, FF},
    {FF, R6, R6, FF, R6, R6},
    {S5, FF, FF, S4, FF, FF},
    {S5, FF, FF, S4, FF, FF},
    {FF, S6, FF, FF, S11,FF},
    {FF, R1, S7, FF, R1, R1},
    {FF, R3, R3, FF, R3, R3},
    {FF, R5, R5, FF, R5, R5},
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
    0,
    EXPRESSION,
    EXPRESSION,
    TERM,
    TERM,
    FACTOR,
    FACTOR,
};

int prod_length[7] = {
    0,
    3, // "E+T".length == 3
    1, // "T".length == 1
    3, // T*F
    1, // F
    3, // (E)
    1, // n
};

int stack[1000]; int top = -1; int sym;

int yylex();
void yyparse();
void push(int i);
void shift(int i);
void reduce(int i);
void lex_error(const char *msg);
void error(const char *msg);
int _getchar();

typedef struct {
    size_t counter;
    char msg[64];
} error_handler_t;
error_handler_t error_handler;

void error_handler_init(error_handler_t *this) {
    this->counter = 0;
    this->msg[0] = '\0';
}

void error_handler_count() {
    error_handler.counter ++;    
}

int main() {
    error_handler_init(&error_handler);
    yyparse();
}

void yyparse() {
    int i;
    stack[++top] = 0;
    sym = yylex();
    do {
        i = action[stack[top]][sym]; // get relation
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
    for (size_t i = 1; i < error_handler.counter; i++)
        fprintf(stderr, "%s", " ");
    fprintf(stderr, "^ ~~ %s\n", msg);
    exit(1);
}

int yylex() {
    static char ch = ' ';
    int i = 0;
    while (ch == ' ' || ch == '\t') ch = _getchar();
    
    if (isdigit(ch)) {
        do {
            ch = _getchar();
        } while (isdigit(ch));
        return NUMBER;
    }
    else if (ch == '+') { ch = _getchar(); return PLUS; }
    else if (ch == '*') { ch = _getchar(); return STAR; }
    else if (ch == '(') { ch = _getchar(); return LP; }
    else if (ch == ')') { ch = _getchar(); return RP; }
    else if (ch == EOF || ch == '\n') return END;
    sprintf(error_handler.msg, "lex error! failed to handle character: [%c]", ch);
    error(error_handler.msg);
    return -1;
}

int _getchar() {
    error_handler_count();
    return getchar();
}
