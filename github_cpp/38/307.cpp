//
//  Queue.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-18.
//
//
#include "cocos2d.h"
#include "Queue.h"

USING_NS_CC;

int Queue::getHead()
{
    return head;
}

int Queue::getTail()
{
    return tail < head ? tail + MAX_CELL : tail;
}

pathCell Queue::dequeue()
{
    head = head % MAX_CELL;
    return queue[head++];
}

void Queue::enqueue(pathCell pc)
{
    tail = tail % MAX_CELL;
    queue[tail++] = pc;
}

bool Queue::isEmpty()
{
    return size() == 0;
}

pathCell Queue::getByIndex(const unsigned int index)
{
    return queue[index % MAX_CELL];
}

void Queue::print()
{
    for (int i = head; i < tail; i++)
    {
        log("queue[i] col %d row %d\n", queue[i].col, queue[i].row);
    }
}

int Queue::size()
{
    return tail - head;
}