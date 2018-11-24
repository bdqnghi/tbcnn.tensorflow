//stack.cpp

#include<iostream>

struct Node {
	Node* next = NULL;
	int data;
};

class Stack {
	Node* top = NULL;

public:
	~Stack(){
		while (top!=NULL){
			pop();
		}
	};

	void push(int number){
		Node* temp = new Node;
		temp -> data = number;
		temp -> next = top;
		top = temp;
	}
	void pop(){
		if(top != NULL){
			Node* temp = top;
			top = top -> next;
			delete temp;
		} else {
			std::cout << "Cannot pop, stack is empty." << std::endl;
		}
	}
	void peek(){
		if (top != NULL){
			std::cout << top -> data << std::endl;
		} else {
			std::cout << "Empty Stack" << std::endl;
		}
	}
};

class stack
{
public:
	stack();
	~stack(){};

	/* data */
};
int main(int argc, char const *argv[])
{
	Stack myStack;
	myStack.peek();
	myStack.push(1);
	myStack.peek();
	myStack.push(2);
	myStack.peek();
	myStack.push(3);
	myStack.peek();
	myStack.pop();
	myStack.peek();
	myStack.pop();
	myStack.peek();
	myStack.pop();
	myStack.peek();
	myStack.pop();
	myStack.peek();
	return 0;
}