#include <iostream>

using namespace std;

// Implement 3 stacks with an array

class Stack{
public:
	int array[60];
	int top;

	Stack(){
		top = -1;
	}

	int push(int value){
		if(top==59){
			cout << "Stack full" << endl;
			return -1;
		}
		array[++top] = value;
	}

	int pop(){
		return array[top--];
	}

	void print(){
		for(int i=0;i<=top;i++)
			cout << array[i] << endl;
		cout << "top: " << top+1 << endl;
	}
};

void movetop(Stack begin, Stack end){
	end.push(begin.pop());
	return;
}

void towerUtil(int n, Stack begin, Stack end, Stack buffer){

	if(n==0) return;

	towerUtil(n-1, begin, buffer, end);
	
	movetop(begin, end);
	
	towerUtil(n-1, buffer, end, begin);

}

int towerofhanoi(int n){
	Stack begin;
	for(int i=0;i<n;i++){
		begin.push(i);
	}

	Stack end;
	Stack buffer;

	begin.print();

	towerUtil(n, begin, end, buffer);

	end.print();
}

int main(){
	towerofhanoi(9);
	return 0;
}