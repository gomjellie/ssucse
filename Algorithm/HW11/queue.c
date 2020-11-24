#include "queue.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void queue_destructor(queue *this) {
    free(this);
}

void *queue_new(size_t sz) {
    queue *this = malloc(sizeof(queue));
    this->sz = sz;
    this->front = 0;
    this->rear = 0;
    this->capacity = 128;
    this->body = malloc(sz * 128);

    return this;
}

void *queue_front(queue *this) {
    size_t idx = (this->front + 1) % this->capacity;

    return &this->body[idx * this->sz];
}

void *queue_back(queue *this) {
    return &this->body[this->rear * this->sz];
}

bool queue_push(queue *this, void *element) {
    if ((this->rear + 1) % this->capacity == this->front) {
        // realloc(this->body, this->sz * this->capacity * 2);
        // this->capacity = this->capacity * 2;
        return false;
    }
    
    this->rear = (this->rear + 1) % this->capacity;
    memcpy(&this->body[this->rear * this->sz], element, this->sz);
    // free(element);
    return true;
}

bool queue_pop(queue *this) {
    if (queue_empty(this)) return false;

    this->front = (this->front + 1) % this->capacity;
    return true;
}

size_t queue_size(queue *this) {
    return (this->rear - this->front) % this->capacity;
}

bool queue_empty(queue *this) {
    return this->front == this->rear;
}
