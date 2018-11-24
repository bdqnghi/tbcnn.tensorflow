#include <stdlib.h>
#include <string.h>

#include "auxiliary/Queue.h"

Queue auxQueueCreate() {
  Queue q;
  q.pos = q.size = 0;
  q.cap = 4;
  q.array = (AuxValue*)malloc(sizeof(AuxValue) * q.cap);
  return q;
}

void auxQueueDestroy(Queue* q) {
  free(q->array);
  memset(q, 0, sizeof(Queue));
}

bool auxQueueEmpty(Queue* q) {
  return q->size == 0;
}

u4 auxQueueSize(Queue* q) {
  return q->size;
}

void auxQueuePush(Queue* q, AuxValue val) {
  if(q->size == q->cap) {
    /* Whoops we hit capacity.  Reallocate and copy up to the head onto the back
     * of the queue. */
    q->cap = q->cap << 1;
    q->array = (AuxValue*)realloc(q->array, sizeof(AuxValue) * q->cap);
    memcpy(q->array + (q->cap >> 1), q->array, sizeof(AuxValue) * q->pos);
  }

  /* Fill in the next open slot with the pushed value. */
  q->array[(q->pos + q->size++) & (q->cap - 1)] = val;
}

AuxValue auxQueuePop(Queue* q) {
  /* Find the next element on the queue. */
  AuxValue ret = q->array[q->pos++];
  q->pos &= q->cap - 1;
  q->size--;

  /* Look for an opportunity to shrink the queue. */
  while(4 < q->cap &&
        (q->size << 2) <= q->cap &&
        q->pos + q->size <= q->cap >> 1) {
    q->cap = q->cap >> 1;
    q->array = (AuxValue*)realloc(q->array, sizeof(AuxValue) * q->cap);
  }

  return ret;
}

AuxValue auxQueuePeek(Queue* q) {
  return q->array[q->pos];
}

AuxValue auxQueuePeekBack(Queue* q) {
  return q->array[(q->pos + q->size - 1) & (q->cap - 1)];
}
