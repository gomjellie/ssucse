#ifndef __NODE_H__
#define __NODE_H__

#include "number.h"

typedef enum {INT_VAL, ADD, MUL} NODE_NAME;

typedef struct node {
    NODE_NAME name;
    number_t val;
    struct node *llink, *rlink;
} node_t;

node_t *node_new(NODE_NAME name, number_t v, node_t *p, node_t *q);
void node_print(node_t *this);

#endif /* __NODE_H__ */
