#include "syntax_tree.h"

#include <stdlib.h>
#include <stdio.h>

node_t *node_new(NODE_NAME name, number_t v, node_t *p, node_t *q) {
    node_t *this = malloc(sizeof(node_t));
    this->name = name;
    this->val = v;
    this->llink = p;
    this->rlink = q;

    return this;
}

void node_print(node_t *this) {
    if (this == NULL) return;
    char *names[3] = {
        "INT_VAL",
        "ADD",
        "MUL",
    };
    
    if (this->name == INT_VAL) {
        printf("%s(%d)  ", names[this->name], this->val.data.int_val);
        return;
    }
    printf("%s  ", names[this->name]);
}
