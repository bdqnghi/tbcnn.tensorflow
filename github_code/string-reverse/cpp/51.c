/***************StringReverse.cpp****************/
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/10/10
//Compiled with g++
//Written on vim
//Purpose: To reverse a string without
// allocating memory.
/***************************************/

#include <iostream>
#include <string>
using namespace std;

//Purpose: To reverse a string within itself.
//User information: Input a string
//Algorithm: Uses a for loop to swap end characters
//Input:  User string
//Output: Reversed user string
int main()
{
	string reverseThis;	//holds string to be reversed
	int check = 1;		//loop check
	char left, right;	//holding vars for swap

	while(check == 1)
	{
		cout << "\nPlease enter a string to be reversed:\n";
		getline(cin, reverseThis);		//get string

		//error checking needed?

		cout << "Your string is:\n" << reverseThis << endl;

		int start = 0;				//start of string
		int end = reverseThis.length() - 1;	//end of string

		for(int count = 0; count < (reverseThis.length() / 2); count++)
		{
			left = reverseThis[start];	//start from beginning
			right = reverseThis[end];	//start from end

			//swap characters
			reverseThis[start] = right;
			reverseThis[end] = left;

			start++;	//move swap up
			end--;		//move swap down
		}

		cout << "Your string has been reversed:\n" << reverseThis << endl << endl;

		//continue to reverse strings
		cout << "If you want to continue please enter 1: ";
		cin >> check;
	}
	return 0;
}
