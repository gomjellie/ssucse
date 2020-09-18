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

typedef struct {
    size_t counter;
    char msg[64];
} error_handler_t;
error_handler_t error_handler;

void error_handler_init(error_handler_t *this);
void error_handler_count();

typedef enum number_type {
    FLOAT, INTEGER,
} NUMBER_TYPE;

typedef union real_number {
    int int_val;
    double float_val;
} real_number_t;

typedef struct number {
    NUMBER_TYPE type;
    real_number_t data;
} number_t;

number_t value[1000];
char yytext[32];
number_t yylval;
NUMBER_TYPE yytype;

number_t number_parse(const char *text);
number_t number_plus(number_t n1, number_t n2);
number_t number_mul(number_t n1, number_t n2);
void number_print(const number_t *this);

int yylex();
void yyparse();
void push(int i);
void shift(int i);
void reduce(int i);
void lex_error(const char *msg);
void error(const char *msg);
int _getchar();

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
        if (i == ACC) {
            puts("success !");
            printf("evaluated result: ");
            number_print(&value[1]);
            // printf("evaluated result: %d\n", value[1]);
        }
        else if (i > 0) shift(i);
        else if (i < 0) reduce(-i);
        else error("yyerror! got wrong syntax here");
    } while (i != ACC);
}

void push(int i) {
    stack[++top] = i;
}

void shift(int i) {
    push(i);
    value[top] = yylval;
    sym = yylex();
}

void reduce(int i) {
    int old_top;
    top -= prod_length[i];
    old_top = top;
    push(go_to[stack[old_top]][prod_left[i]]);
    switch (i) {
        case 1:
        value[top] = number_plus(value[old_top + 1], value[old_top + 3]); break;
        case 2:
        value[top] = value[old_top + 1]; break;
        case 3:
        value[top] = number_mul(value[old_top + 1], value[old_top + 3]); break;
        // value[top] = value[old_top + 1] * value[old_top + 3];
        case 4:
        value[top] = value[old_top + 1]; break;
        case 5:
        value[top] = value[old_top + 2]; break;
        case 6:
        value[top] = value[old_top + 1]; break;
        default:
        error("yyerror: parsing table error"); break;
    }
}

void error(const char *msg) {
    for (size_t i = 2; i < error_handler.counter; i++)
        fprintf(stderr, "%s", " ");
    fprintf(stderr, "^ ~~ %s\n", msg);
    exit(1);
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
        yylval = number_parse(yytext);
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

void error_handler_init(error_handler_t *this) {
    this->counter = 0;
    this->msg[0] = '\0';
}

void error_handler_count() {
    error_handler.counter ++;    
}

number_t number_parse(const char *text) {
    if (yytype == FLOAT) {
        return (number_t) { .type = FLOAT, .data.float_val = atof(yytext) };
    }
    return (number_t) { .type = INTEGER, .data.int_val = atoi(yytext) };
}

number_t number_plus(number_t n1, number_t n2) {
    double double_sum = 0;
    int int_sum = 0;
    if (n1.type == FLOAT) double_sum += n1.data.float_val;
    if (n2.type == FLOAT) double_sum += n2.data.float_val;
    if (n1.type == INTEGER) int_sum += n1.data.int_val;
    if (n2.type == INTEGER) int_sum += n2.data.int_val;

    if (n1.type == FLOAT || n2.type == FLOAT)
        return (number_t) { .type = FLOAT, .data.float_val = double_sum + int_sum };
    return (number_t) { .type = INTEGER, .data.int_val = int_sum };
}

number_t number_mul(number_t n1, number_t n2) {
    double double_mul = 0;
    int int_mul = 0;
    if (n1.type == FLOAT) {
        if (n2.type == FLOAT)
            return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val * n2.data.float_val };
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val * n2.data.int_val };
    }
    if (n2.type == FLOAT)
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.int_val * n2.data.float_val };
    return (number_t) {.type = INTEGER, .data.int_val = n1.data.int_val * n2.data.int_val };
}

void number_print(const number_t *this) {
    if (this->type == INTEGER) {
        printf("%d", this->data.int_val); return;
    }
    printf("%.2f", this->data.float_val);
}
