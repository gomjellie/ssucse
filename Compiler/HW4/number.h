#ifndef __NUMBER_H__
#define __NUMBER_H__

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

number_t number_parse(const char *text, NUMBER_TYPE yytype);
number_t number_plus(number_t n1, number_t n2);
number_t number_mul(number_t n1, number_t n2);
void number_print(const number_t *this);

#endif /* __NUMBER_H__ */
