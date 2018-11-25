#include<iostream>

using namespace std;

char inputString[1000];
int inputReverse[1000];
int tmpReverse[1000];
int charPointer;

void Reverse()
{
	int first, second, third, fourth;
	cin >> inputString[charPointer];
	inputReverse[charPointer] = charPointer;
	first = charPointer;
	charPointer++;
	if (inputString[charPointer-1] == 'x')
	{
		Reverse();
	}
	cin >> inputString[charPointer];
	inputReverse[charPointer] = charPointer;
	second = charPointer;
	charPointer++;
	if (inputString[charPointer-1] == 'x')
	{
		Reverse();
	}
	cin >> inputString[charPointer];
	inputReverse[charPointer] = charPointer;
	third = charPointer;
	charPointer++;
	if (inputString[charPointer-1] == 'x')
	{
		Reverse();
	}
	cin >> inputString[charPointer];
	inputReverse[charPointer] = charPointer;
	fourth = charPointer;
	charPointer++;
	if (inputString[charPointer-1] == 'x')
	{
		Reverse();
	}

	for (int i = first; i < charPointer; i++)
	{
		tmpReverse[i] = inputReverse[i];
	}

	int thirdNum = fourth - third;
	int fourthNum = charPointer - fourth;
	int firstNum = second - first;
	int secondNum = third - second;

	int i = first;
	for (int j = 0; j < thirdNum; j++, i++)
	{
		inputReverse[i] = tmpReverse[third + j];
	}
	for (int j = 0; j < fourthNum; j++, i++)
	{
		inputReverse[i] = tmpReverse[fourth + j];
	}
	for (int j = 0; j < firstNum; j++, i++)
	{
		inputReverse[i] = tmpReverse[first + j];
	}
	for (int j = 0; j < secondNum; j++, i++)
	{
		inputReverse[i] = tmpReverse[second + j];
	}
}

void printReverse()
{
	for (int i = 0; i < charPointer; i++)
	{
		cout << inputString[inputReverse[i]];
	}
}

int main()
{
	int testCase;

	cin >> testCase;
	for (int test = 0; test < testCase; test++)
	{
		for (int i = 0; i < 1000; i++)
		{
			inputString[i] = 0;
			inputReverse[i] = 0;
		}
		charPointer = 0;
		cin >> inputString[charPointer];
		charPointer++;
		if (inputString[charPointer-1] == 'x')
		{
			Reverse();
		}
		printReverse();
		cout << endl;
	}

	return 0;
}