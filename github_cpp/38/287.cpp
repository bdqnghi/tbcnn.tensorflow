//queue.cpp

#include<iostream>

struct Node{
	Node* next = NULL;
	int data;
};

class Queue {
	Node* first = NULL;
	Node* last  = NULL;

	public:
		void enqueue(int number){
			if(first == NULL){
				last = new Node;
				last -> data = number;
				first = last;
			} else {
				last -> next = new Node;
				last -> next -> data = number;
				last = last -> next;
			}
		}
		void dequeue(){
			if(first != NULL){
				std::cout << first -> data << std::endl;
				Node* temp = first;
				first = first -> next;
				delete temp;
			}
			if (first == NULL){
				last = NULL;
				std::cout << "Empty queue" << std::endl;
			}
		}
};

int main(int argc, char const *argv[])
{
	Queue myQueue;
	myQueue.dequeue();
	myQueue.enqueue(1);
	myQueue.enqueue(2);
	myQueue.enqueue(3);
	myQueue.dequeue();
	myQueue.dequeue();
	myQueue.dequeue();
	myQueue.dequeue();

	return 0;
}