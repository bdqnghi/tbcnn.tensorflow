#include <iostream>
#include <string>
#include "media.h"
using namespace std;
#define MAX_SIZE 20



class Queue{

    private:
     	media** A;
	    int front, rear;
	    int total;

	public:
		Queue(){


			A = new media*[MAX_SIZE];

			front = -1;
			rear = -1;
		}

		bool IsEmpty(){
			return (front == -1 && rear == -1);
		}

		bool IsFull(){
			return (rear+1)%MAX_SIZE == front ? true : false;
		}

		void Enqueue(media* x){
			if (IsFull()){
				cout << "Queue is full. Error Error\n";
				return;
			}
			if (IsEmpty()){
				front = rear = 0;
			}else{
				rear = (rear+1)%MAX_SIZE;
			}

			A[rear] = x;


		}

		void Dequeue(){
			if (IsEmpty()){
				cout << "Error Error. No elements to dequeue\n";

			}
			else if (front == rear){
				rear = front = -1;
			}

			else{
				front = (front+1)%MAX_SIZE;
			}
		}

		media* Front(){
			if (front == 1){
				cout << "Empty queue\n";
				return A[0];
			}else{
			return A[front];
		    }
		}

		void print(){
			int count = (rear + MAX_SIZE - front) % MAX_SIZE + 1;
			int total = 0;
			int minutes, hours, sec;
			for (int i = 0; i <count; i++){
				int index = (front+i) % MAX_SIZE;
				//A[index]check();
				A[index]->display();
				total += A[index]->getLength()->seconds;

				minutes = total /60;
				hours = minutes / 60;

				minutes = minutes % 60;
				sec = total % 60;




			}
			cout << "total length is " << hours << ":" << minutes << ":" << sec << endl;
			cout << " \n \n";
		}
	
};