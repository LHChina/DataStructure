#ifndef QUEUE_H_INLCUDE
#define QUEUE_H_INLCUDE

#include "List.h"

typedef List Queue;
#define queue_init list_init
#define queue_destroy list_destroy

int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);

#define queue_peek(queue) (NULL == (queue)->head ? NULL : (queue)->head->data)
#define queue_size list_size

#endif

