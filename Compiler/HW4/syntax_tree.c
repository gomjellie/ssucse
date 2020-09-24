#include "syntax_tree.h"

#include <stdlib.h>

node_t *node_new(NODE_NAME name, number_t v, node_t *p, node_t *q) {
    node_t *this = malloc(sizeof(node_t));
    this->name = name;
    this->val = v;
    this->llink = p;
    this->rlink = q;

    return this;
}

