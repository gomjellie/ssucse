#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

#include <ctype.h>

typedef struct {
    size_t counter;
} error_handler_t;

error_handler_t *error_handler_new();
void error_handler_count(error_handler_t *this);
void error(const error_handler_t *this, const char *msg);
void error_handler_del(error_handler_t *this);

error_handler_t *error_handler;

#endif /* __ERROR_HANDLER_H__ */
