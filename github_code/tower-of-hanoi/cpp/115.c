// Tower of Hanoi.cpp : Defines the entry point for the console application.
// algorithm:
/*
1. move top n-1 (largest) disks from source to auxillary tower
2. move nth disk from source to auxillary tower
3. move n-1 (smallest) disks form source to auxillary tower
4. repeat from step one using recursion

*/

#include "stdafx.h"
#include <iostream>

// n is number of disks
void Hanoi(int n, char frompeg, char topeg, char auxpeg)
{
	// base case if there's only 1 disk
	if (n == 1) {
		cout << "move disk 1 from " << frompeg << " to " <<  topeg;
		return;
	}

	// move top disks from A-B using C as auxillary
	Hanoi(n - 1, frompeg, topeg, auxpeg);

	// move 
	Hanoi(n, frompeg, topeg, auxpeg);

	Hanoi(n + 1, frompeg, topeg, auxpeg);
}

using namespace std;


int main()
{
    return 0;
}

