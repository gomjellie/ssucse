#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUMBER_LEN 128

typedef enum _token {
    EMPTY, PLUS, STAR, NUMBER, DOT, LP, RP, END
} TOKEN;

typedef enum number_type {
    FLOAT, INTEGER,
} NUMBER_TYPE;

typedef struct number_record {
    size_t len;
    char body[MAX_NUMBER_LEN];
    char curr; // current input char, get_token 에서만 값 세팅함.
    NUMBER_TYPE type;
} number_record_t;

void number_record_push(number_record_t *this, char val) {
    this->body[this->len++] = val;
}

void number_record_clear(number_record_t *this) {
    this->len = 0;
    this->curr = 0;
    this->type = INTEGER;
    memset(this->body, 0, MAX_NUMBER_LEN);
}

double number_eval(number_record_t *this) {
    double res = atof(this->body);
    return atof(this->body);
}

typedef struct number {
    NUMBER_TYPE type;
    int int_val;
    double float_val;
} number_t;

void print_number(number_t *this) {
    if (this->type == INTEGER) {
        printf("%d", this->int_val);
        return;
    }
    printf("%f", this->float_val);
}

TOKEN g_token;
number_record_t number_record;

int expr();
int term();
int factor();
double number();
void error(char *error_message);

void get_token() {
    char c = getchar();
    
    switch (c) {
        case '+': g_token = PLUS; break;
        case '*': g_token = STAR; break;
        case '(': g_token = LP; break;
        case ')': g_token = RP; break;
        case ' ': g_token = EMPTY; get_token(); break;
        case '.': g_token = DOT; number_record.curr = c; number_record.type = FLOAT; break;
        case '\n': g_token = END; break;
        case EOF: g_token = END; break;
        default:
        if (c >= '0' && c < '9') {
            g_token = NUMBER;
            number_record.curr = c;
            break;
        }
        printf("c: %c", c);
        error("get_token() 에서 터짐");
    }
}

int expr() {
    int ret = 0;
    ret = term();
    while (g_token == PLUS) {
        get_token();
        ret += term();
    }
    return ret;
}

int term() {
    int ret = 0;
    ret = factor();
    while (g_token == STAR) {
        get_token();
        ret *= factor();
    }
    return ret;
}

int factor() {
    int ret = 0;
    if (g_token == NUMBER) {
        double evaluated_number = number();
        return evaluated_number;
    }
    else if (g_token == LP) {
        get_token();
        ret = expr();
        if (g_token == RP) {
            get_token();
            return ret;
        }
        else {
            error("factor() line 72");
        }
    }
    else { error("factor() line 75"); }
}

double number() {
    int ret = 0;
    
    do {
        number_push(&number_record, number_record.curr);
        get_token();
    } while (g_token == NUMBER || g_token == DOT);
    double res = number_eval(&number_record);
    number_clear(&number_record);
    return res;
}

int main() {
    number_clear(&number_record);
    get_token();
    int res = expr();
    printf("result: %d \n", res);
}

void error(char *error_message) {
    fprintf(stderr, error_message);
    exit(1);
}
