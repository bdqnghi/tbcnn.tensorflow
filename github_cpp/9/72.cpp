// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "string"
#include <iostream>

using namespace std;

void stringReverse(string, int);

int main()
{
	string greeting = "How Are You Doing Today";

	int lastPos = greeting.size() - 1;

	stringReverse(greeting, lastPos);
	cout << endl;

	return 0;
}

void stringReverse(string x, int initialPos) {

	int n = initialPos;

	cout << x[n];

	if (initialPos > 0) {

		stringReverse(x, n-1);

	}

}
