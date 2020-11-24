#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <stddef.h>
#include <stdbool.h>

typedef int (*cmp_f)(const void *a, const void *b);

typedef struct _priority_queue {
    void *body;
    size_t capacity;
    size_t length;
    size_t sz; // sizeof(type)
    cmp_f cmp;
} priority_queue;

priority_queue *pq_new(size_t capacity, size_t sz, cmp_f cmp);

bool pq_empty(priority_queue *this);

void pq_destroy(priority_queue *this);

void *pq_top(priority_queue *this);

void pq_push(priority_queue *this, void* elem);

void pq_pop(priority_queue *this);

#endif /* _PRIORITY_QUEUE_H_ */

