#include "queue.h"
#include "stdexcept"
#include "iostream"
using std::cout;
using std::endl;
using std::cin;
using std::overflow_error;
struct queue{
    int capacity;
    int size;
    int front;
    int rear;
    int* array;
};

PtrToQueue createQueue(int maxsize){
    PtrToQueue P=PtrToQueue(malloc(sizeof(struct queue)));
    P->capacity=maxsize;
    P->size= 0;
    P->front=0;
    P->rear=-1;
    P->array=(int*)(malloc(sizeof(int)*maxsize));

}

bool isFull(PtrToQueue P){
    return P->size>=P->capacity;
}

void destroyQueue(PtrToQueue P){
    free(P->array);
    free(P);
}

bool isEmpty(PtrToQueue P){
return P->size==0;
};

void enQueue(int x, PtrToQueue P){
    if(isFull(P))
        overflow_error("out of space");
    if(P->rear==P->capacity-1)
        P->rear=0;
    else
        ++P->rear;
    P->array[P->rear]=x;
    ++P->size;

}

int dequeue(PtrToQueue P){
    if(isEmpty(P))
        overflow_error("The queue is empty!!!");
    int temp=P->front;
    --P->size;
    if(temp==P->capacity-1)
        P->front=0;
    else
        ++P->front;

    cout<<P->array[temp]<<endl;
    return P->array[temp];
}

