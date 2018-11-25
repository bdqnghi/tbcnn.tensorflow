//============================================================================
// Name        : ReverseDigitsWithRecursion.cpp
// Author      : Jordan Betcher
// Date        : 11/3/2017
// Copyright   :
// Description : Takes positive numbers from input and reverses them
//============================================================================

#include <iostream>
using namespace std;

void reverseNumbers();
string reverseString(string stringToReverse);

int main()
{
	reverseNumbers();

	return 0;
}

//Takes a number from input and reverses it
inline void reverseNumbers()
{
	string numberToReverse;

	cout << "Enter a positive number to reverse: ";
	cin  >> numberToReverse;

	while(numberToReverse.find("-"))
	{
		cout << reverseString(numberToReverse) << endl;

		cout << "Enter a positive number to reverse: ";
		cin  >> numberToReverse;
	}
}

//Reverses a string using recursion
inline string reverseString(string stringToReverse)
{
	if (stringToReverse.size() <= 1)
	{
		return stringToReverse;
	}
	else
	{
		return reverseString(stringToReverse.substr(1, -1)) + stringToReverse[0];
	}
}
