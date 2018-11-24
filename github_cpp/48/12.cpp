#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

int main(){

	queue<char> myQueue;
	stack<char> myStack;
	string palindrome;

	cout << "Enter a text in lowercase:" << endl;
	cin >> palindrome;

	for(int i = 0; i < palindrome.length(); i++){

		myQueue.push(palindrome[i]);
		myStack.push(palindrome[i]);

	}//end for

	while(!myQueue.empty() && !myStack.empty()){

		if(myQueue.front() == myStack.top()){
			myQueue.pop();
			myStack.pop();
		}else{
			cout << "Is not a palindrome" << endl;
			system("pause");
			return 0;
		}//end if

	}//end while

		cout << "Is a palindrome" << endl;

	system("pause");
	return 0;
}//end main
