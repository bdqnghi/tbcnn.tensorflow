//Lab7Driver.cpp
//Dominic Rainbolt
//program to test the functions we were asked to create in lab 5
#include "Lab7MyStack.h"
#include <iostream>
using std::cout;
using std::endl;

//-----------------functions to test---------------

string stringReversal1(string input)
{
	stack<char> myStack;
	for (int i = 0; i < input.size(); i++)
	{
		myStack.push(input[i]);
	}
	string reverse = input;
	for (int i = 0; i < input.size(); i++)
	{
		reverse[i] = myStack.top();
		myStack.pop();

	}
	return reverse;
}

string stringReversal2(string input)
{
	vector<char> myVector;
	for (int i = 0; i < input.size(); i++)
	{
		myVector.push_back(input[i]);
	}
	string reverse = input;
	for (int i = 0; i < input.size(); i++)
	{
		reverse[i] = myVector.back();
		myVector.pop_back();
	}
	return reverse;
}
string stringReversal3(string input)
{
	list<char>  myList;
	for (int i = 0; i < input.size(); i++)
	{
		myList.push_back(input[i]);
	}
	string reverse = input;
	for (int i = 0; i < input.size(); i++)
	{
		reverse[i] = myList.back();
		myList.pop_back();
	}
	return reverse;
}
string stringReversal4(string input)
{
	MyStack  myList;
	for (int i = 0; i < input.size(); i++)
	{
		myList.push(input[i]);
	}
	string reverse = input;
	for (int i = 0; i < input.size(); i++)
	{
		reverse[i] = myList.pull();
	}
	return reverse;
}
//------------main program----------
int main() {
	cout << "the test string is hello: " << endl;
	cout << "Testing stringReverse 1" << endl;
	cout << "the reverse of the test string is: " << stringReversal1("hello") << endl;

	cout << "Testing stringReverse 2" << endl;
	cout << "the reverse of the test string is: " << stringReversal2("hello") << endl;

	cout << "Testing stringReverse 3" << endl;
	cout << "the reverse of the test string is: " << stringReversal3("hello") << endl;

	cout << "Testing stringReverse 4" << endl;
	cout << "the reverse of the test string is: " << stringReversal4("hello") << endl;

	system("pause");
	return 0;
}
