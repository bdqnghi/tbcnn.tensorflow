#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> numbers = { 6, 2, 1, 3, 5, 9, 4, 8, 7 };
	int lastUnsorted = numbers.size() - 1;
	bool isSorted = false;
	int temp;

	while (!isSorted)
	{
		isSorted = true;

		for (int i = 0; i < lastUnsorted; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				temp = numbers[i];
				numbers[i] = numbers[i + 1];
				numbers[i + 1] = temp;
				
				isSorted = false;
			}
		}

		lastUnsorted--;
	}

	for (auto itr = numbers.begin(); itr != numbers.end(); itr++)
	{
		cout << *itr;
	}

	cin >> temp;

    return 0;
}
