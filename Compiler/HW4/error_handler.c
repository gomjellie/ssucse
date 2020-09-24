#include "error_handler.h"

#include <stdio.h>
#include <stdlib.h>

error_handler_t *error_handler_new() {
    error_handler_t *this = malloc(sizeof(error_handler_t));
    this->counter = 0;
    return this;
}

void error_handler_count(error_handler_t *this) {
    this->counter ++;    
}

void error(const error_handler_t *this, const char *msg) {
    for (size_t i = 2; i < this->counter; i++)
        fprintf(stderr, "%s", " ");
    fprintf(stderr, "^ ~~ %s\n", msg);
    exit(1);
}

void error_handler_del(error_handler_t *this) {
    free(this);
}
