#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Queue
{
  int front,rear,size;
  unsigned capacity;
  int* arr;
};

struct Queue* createQueue(unsigned capacity)
{
  struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
  queue->capacity=capacity;
  queue->front=queue->size=0;
  queue->rear=capacity-1;
  queue->arr=(int*) malloc(queue->capacity*sizeof(int));
  return queue;
}

int isFull(struct Queue* queue)
{
  return (queue->size==queue->capacity-1);
}

int isEmpty(struct Queue* queue)
{
  return (queue->size==0);
}

void enqueue(struct Queue* queue, int item) {
  /* code */
  if (isFull(queue))
    return;
  queue->rear=(queue->rear+1);
}
