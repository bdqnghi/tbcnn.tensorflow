#include <iostream>
using namespace std;

int main()
{
	//setup variables, get input
	string input, reverseInput;
	cout << "Enter string to reverse: ";
	cin >> input;

	//because you cannot have a dynamic allocated size of a string (such as getting size of string input and using it to set the size of reverseInput) this is needed to make sure both strings are the correct size.
	reverseInput = input;

	int j = 0; //second helper iterator

	//reverse the string
	for (int i = input.length() - 1; i >= 0; i--)
	{
		reverseInput[j] = input[i];
		j++;
	}

	cout << "The reverse of '" << input << "' is " << reverseInput << endl;
}