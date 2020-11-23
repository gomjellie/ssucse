#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

typedef struct _queue {
    void *body;

    size_t sz;
    int front;
    int rear;
} queue;

void queue_destructor(queue *this);

void *queue_front(queue *this);
void *queue_back(queue *this);
bool queue_push(queue *this, void *element);
bool queue_pop(queue *this);
size_t queue_size(queue *this);
bool queue_empty(queue *this);

#endif /* _QUEUE_H_ */
