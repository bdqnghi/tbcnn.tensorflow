// HW-4-4-12 Reverse Phrase - Patrick Kubiak - 6/3/2015
// Iterative and Recursive algorithms to reverse a string.

#include <iostream>
#include <string>
using namespace std;

string reverse(string str);
string reverse(string str, string strRev);

int main()
{
	string strPhrase, strReversePhrase;
	
	// welcome
	cout << "Reverse" << endl;
	cout << "Phrase to reverse: ";
	getline(cin, strPhrase);

	// iteratively reverse the phrase
	for (int i = strPhrase.length(); i >= 0; i--)
	{
		strReversePhrase += strPhrase.substr(i, 1);
	}
	cout << "Phrase in reverse (using iteration): " << strReversePhrase << endl;

	// recursively reverse the phrase
	strReversePhrase = reverse(strPhrase);
	cout << "Phrase in reverse (using recursion): " << strReversePhrase << endl;

	system("pause");
	return 0;
}

// reverse a string recursively - helper method
string reverse(string str)
{
	return reverse(str, "");
}

// reverse a string recursively
// str - string to reverse
// strRev - temporary storage of reversed string
string reverse(string str, string strRev)
{
	if (str.length() == 0)
	{
		return strRev;								// base case str is empty
	}
	else
	{
		strRev += str.substr(str.length() - 1, 1);	// add last letter in str to strRev
		str = str.substr(0, str.length() - 1);	    // remove last letter from str
		return reverse(str, strRev);				// call method recursively on smaller part of string
	}
}
