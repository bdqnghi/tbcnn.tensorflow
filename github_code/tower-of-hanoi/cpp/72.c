// TowerOfHanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int steps = 0;

void ToH(int disks, char from, char to, char aux) {
	if (disks == 1) {
		cout << steps << endl;
		steps++;
		return;
	}
	ToH(disks - 1, from, aux, to);
	cout << steps << endl;
	steps++;
	ToH(disks - 1, aux, to, from);
}

int main()
{
	int disks;
	cout << "Enter the number of disks: ";
	cin >> disks;
	ToH(disks, 'A', 'C', 'B');
	cout << "The total steps are: " << steps;

	
	return 0;
}

