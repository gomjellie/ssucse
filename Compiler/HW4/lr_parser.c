#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error_handler.h"
#include "number.h"
#include "node.h"

extern error_handler_t *error_handler;

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

node_t *value[1000];
char yytext[32];
number_t yylval;
NUMBER_TYPE yytype;

int yylex();
void yyparse();
void push(int i);
void shift(int i);
void reduce(int i);
void lex_error(const char *msg);
int _getchar();
void render_postfix(node_t *node);

int main() {
    error_handler = error_handler_new();
    yyparse();
    error_handler_del(error_handler);
}

void yyparse() {
    int i;
    stack[++top] = 0;
    sym = yylex();
    do {
        i = action[stack[top]][sym]; // get relation
        if (i == ACC) {
            printf("postfix: ");
            render_postfix(value[1]);
            puts("");
        }
        else if (i > 0) shift(i);
        else if (i < 0) reduce(-i);
        else error(error_handler, "yyerror! got wrong syntax here");
    } while (i != ACC);
}

void push(int i) {
    stack[++top] = i;
}

void shift(int i) {
    push(i);
    // value[top]->val = yylval;
    value[top] = node_new(INT_VAL, yylval, NULL, NULL);
    sym = yylex();
}

void reduce(int i) {
    int old_top;
    number_t int_zero = {
        .type = INTEGER,
        .data.int_val = 0,
    };
    top -= prod_length[i];
    old_top = top;
    push(go_to[stack[old_top]][prod_left[i]]);
    switch (i) {
        case 1:
        value[top] = node_new(ADD, int_zero, value[old_top + 1], value[old_top + 3]); break;
        // value[top] = number_plus(value[old_top + 1], value[old_top + 3]); break;
        case 2:
        value[top] = value[old_top + 1]; break;
        case 3:
        value[top] = node_new(MUL, int_zero, value[old_top + 1], value[old_top + 3]); break;
        // value[top] = number_mul(value[old_top + 1], value[old_top + 3]); break;
        case 4:
        value[top] = value[old_top + 1]; break;
        case 5:
        value[top] = value[old_top + 2]; break;
        case 6:
        value[top] = node_new(INT_VAL, value[old_top + 1]->val, NULL, NULL); break;
        // value[top] = value[old_top + 1]; break;
        default:
        error(error_handler, "yyerror: parsing table error"); break;
    }
}

int yylex() {
    static char ch = ' ';
    int i = 0;
    while (ch == ' ' || ch == '\t') ch = _getchar();
    yytype = INTEGER;

    if (isdigit(ch)) {
        do {
            yytext[i++] = ch;
            ch = _getchar();
            if (ch == '.') yytype = FLOAT;
        } while (isdigit(ch) || ch == '.');
        yytext[i] = 0;
        yylval = number_parse(yytext, yytype);
        return NUMBER;
    }
    else if (ch == '+') { ch = _getchar(); return PLUS; }
    else if (ch == '*') { ch = _getchar(); return STAR; }
    else if (ch == '(') { ch = _getchar(); return LP; }
    else if (ch == ')') { ch = _getchar(); return RP; }
    else if (ch == EOF || ch == '\n') return END;

    char buf[128];
    sprintf(buf, "lex error! failed to handle character: [%c]", ch);
    error(error_handler, buf);
    return -1;
}

int _getchar() {
    error_handler_count(error_handler);
    return getchar();
}

void render_postfix(node_t *node) {
    if (node == NULL) return;

    render_postfix(node->llink);
    render_postfix(node->rlink);
    node_print(node);
}
