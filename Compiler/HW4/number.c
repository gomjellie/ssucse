#include "number.h"

#include "error_handler.h"
extern error_handler_t *error_handler;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

number_t number_parse(const char *text, NUMBER_TYPE yytype) {
    if (yytype == FLOAT) {
        return (number_t) { .type = FLOAT, .data.float_val = atof(text) };
    }
    return (number_t) { .type = INTEGER, .data.int_val = atoi(text) };
}

number_t number_plus(number_t n1, number_t n2) {
    char buf[128];
    if (n1.type == FLOAT) {
        if (n2.type == FLOAT)
            return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val + n2.data.float_val };
        sprintf(buf, "%.2lf(실수) 와 %d(정수)의 연산은 허용되지 않습니다.", n1.data.float_val, n2.data.int_val);
        error(error_handler, buf);
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val + n2.data.int_val };
    }
    if (n2.type == FLOAT) {
        sprintf(buf, "%d(정수) 와 %.2lf(실수)의 연산은 허용되지 않습니다.", n1.data.int_val, n2.data.float_val);
        error(error_handler, buf);
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.int_val + n2.data.float_val };
    }
    return (number_t) {.type = INTEGER, .data.int_val = n1.data.int_val + n2.data.int_val };
}

number_t number_mul(number_t n1, number_t n2) {
    char buf[128];
    if (n1.type == FLOAT) {
        if (n2.type == FLOAT)
            return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val * n2.data.float_val };
        sprintf(buf, "(실수)%.2lf 와 (정수)%d의 연산은 허용되지 않습니다.", n1.data.float_val, n2.data.int_val);
        error(error_handler, buf);
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.float_val * n2.data.int_val };
    }
    if (n2.type == FLOAT) {
        sprintf(buf, "%d(정수) 와 %.2lf(실수)의 연산은 허용되지 않습니다.", n1.data.int_val, n2.data.float_val);
        error(error_handler, buf);
        return (number_t) {.type = FLOAT, .data.float_val = n1.data.int_val * n2.data.float_val };
    }
    return (number_t) {.type = INTEGER, .data.int_val = n1.data.int_val * n2.data.int_val };
}

void number_print(const number_t *this) {
    if (this->type == INTEGER) {
        printf("%d", this->data.int_val); return;
    }
    printf("%.2f", this->data.float_val);
}
