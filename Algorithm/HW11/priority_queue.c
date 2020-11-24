#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>

priority_queue *pq_new(size_t capacity, size_t sz, cmp_f cmp) {
    priority_queue *this = malloc(sizeof(priority_queue));
    this->body = malloc(sz * capacity);
    this->capacity = capacity;
    this->sz = sz;
    this->cmp = cmp;
    this->length = 0;

    return this;
}

bool pq_empty(priority_queue *this) {
    return this->length == 0;
}

void pq_destroy(priority_queue *this) {
    free(this->body);
    free(this);
}

void *pq_top(priority_queue *this) {
    if (pq_empty(this)) NULL;
    
    return (char *)this->body + this->sz;
}

void pq_push(priority_queue *this, void* elem) {
    size_t sz = this->sz;
    size_t cur = ++this->length;
    
    while (cur != 1 && this->cmp(elem, (char *)this->body + (cur / 2) * sz) != 1) {
        memcpy((char *)this->body + cur * sz, (char *)this->body + (cur / 2) * sz, sz);
        cur /= 2;
    }
    memcpy((char *)this->body + cur * sz, elem, sz);
}

void pq_pop(priority_queue *this) {
    size_t sz = this->sz;
    if (pq_empty(this)) return;

    void *last_elem = malloc(sz);
    memcpy(last_elem, (char *)this->body + (this->length--) * sz, sz);

    size_t cur = 1;
    size_t child = 2;

    while (child <= this->length) {
        if (child < this->length && this->cmp((char *)this->body + (child + 1) * sz, (char *)this->body + child * sz) != 1)
            child++;
        if (this->cmp(last_elem, (char *)this->body + child * sz) != 1) break;

        memcpy((char *)this->body + cur * sz, (char *)this->body + child * sz, sz);
        cur = child; child *= 2;
    }
    memcpy((char *)this->body + cur * sz, last_elem, sz);

    free(last_elem);
}
