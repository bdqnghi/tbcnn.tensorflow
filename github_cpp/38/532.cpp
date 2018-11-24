#include "Queue.h"

using namespace std;

/*Class Function definitions listed below */
void Queue :: push(const int& x) {
    /*Check if the queue is full , i.e no elements can be pushed */
    if((front == 0) && (rear == qsize-1)) {
    throw overflow_error("Queue Full ! Unable to push");
    }

    /*If not full,push must be implemented */
    else {
        /*Check if the queue is empty */
        if(empty()){
            front = rear = 0;       //Front and rear point to the same element
            data[rear]=x;
        }
        /*Queue is not empty , hence elements can be pushed */
        else {
            rear = ((rear==qsize-1) ? 0 : rear+1);
            data[rear] = x;
        }
        qsize++;
    }/*Queue is not full */
}

void Queue :: pop() {
    /*Check if the queue is empty
     *if empty , throw an underflow_error
     */
    if(empty()) {
        throw underflow_error("Queue Empty ! Nothing to pop ");
    }
    /* if the queue is not empty*/
    else {
        /*if only one element is present in the queue */
        if(qsize==1) {
            data[front]=0;
            front=rear=-1;
        }
        /*If more than one element is present */
        else {
            data[front]=0;
            front = ((front==qsize-1)?0:front+1);
        }
        qsize--;
    }
}

void Queue :: print() {
    for(int i=front;i<rear;i++)
        cout<<data[i]<<endl;
}
