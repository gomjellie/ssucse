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

typedef struct number {
    NUMBER_TYPE type;
    int int_val;
    double float_val;
} number_t;

void number_record_push(number_record_t *this, char val) {
    this->body[this->len++] = val;
}

void number_record_clear(number_record_t *this) {
    this->len = 0;
    this->curr = 0;
    this->type = INTEGER;
    memset(this->body, 0, MAX_NUMBER_LEN);
}

number_t number_eval(const number_record_t *this) {
    if (this->type == FLOAT) {
        return (number_t) { .type = FLOAT, .int_val = 0, .float_val = atof(this->body) };
    }
    return (number_t) { .type = INTEGER, .int_val = atoi(this->body), .float_val = 0 };
}

number_t number_plus(number_t n1, number_t n2) {
    double double_sum = 0;
    int int_sum = 0;
    if (n1.type == FLOAT) double_sum += n1.float_val;
    if (n2.type == FLOAT) double_sum += n2.float_val;
    if (n1.type == INTEGER) int_sum += n1.int_val;
    if (n2.type == INTEGER) int_sum += n2.int_val;

    if (n1.type == FLOAT || n2.type == FLOAT)
        return (number_t) { .type = FLOAT, .float_val = double_sum + int_sum, .int_val = 0 };
    return (number_t) { .type = INTEGER, .float_val = 0, .int_val = int_sum };
}

number_t number_mul(number_t n1, number_t n2) {
    double double_mul = 0;
    int int_mul = 0;
    if (n1.type == FLOAT) {
        if (n2.type == FLOAT)
            return (number_t) {.type = FLOAT, .float_val = n1.float_val * n2.float_val, .int_val = 0 };
        return (number_t) {.type = FLOAT, .float_val = n1.float_val * n2.int_val, .int_val = 0 };
    }
    if (n2.type == FLOAT)
        return (number_t) {.type = FLOAT, .float_val = n1.int_val * n2.float_val, .int_val = 0 };
    return (number_t) {.type = INTEGER, .float_val = 0, .int_val = n1.int_val * n2.int_val };
}

void number_print(const number_t *this) {
    if (this->type == INTEGER) {
        printf("%d", this->int_val); return;
    }
    printf("%f", this->float_val);
}

TOKEN g_token;
number_record_t number_record;

number_t expr();
number_t term();
number_t factor();
number_t number();
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
        if (c >= '0' && c <= '9') {
            g_token = NUMBER;
            number_record.curr = c;
            break;
        }
        printf("c: %c", c);
        error("get_token() 에서 터짐");
    }
}

number_t expr() {
    number_t ret = term();
    while (g_token == PLUS) {
        get_token();
        ret = number_plus(ret, term());
    }
    return ret;
}

number_t term() {
    number_t ret = factor();
    while (g_token == STAR) {
        get_token();
        ret = number_mul(ret, factor());
    }
    return ret;
}

number_t factor() {
    number_t ret;
    if (g_token == NUMBER) {
        number_t evaluated_number = number();
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

number_t number() {
    do {
        number_record_push(&number_record, number_record.curr);
        get_token();
    } while (g_token == NUMBER || g_token == DOT);
    number_t ret = number_eval(&number_record);
    number_record_clear(&number_record);
    return ret;
}

int main() {
    number_record_clear(&number_record);
    get_token();
    number_t result = expr();
    number_print(&result);
}

void error(char *error_message) {
    fprintf(stderr, error_message);
    exit(1);
}
