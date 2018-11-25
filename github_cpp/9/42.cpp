


#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

string reverseString(string s) 
{
	cout << "size of string = " << s.size() << endl;
	
	int i = 0, j = 0;
	char temp = NULL;
	for (i = 0, j = s.size() - 1; i < j;i++,j--)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}

	return s;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string revString = reverseString("Hello");
	cout << revString << endl;
	

	system("pause");
	return 0;
}

