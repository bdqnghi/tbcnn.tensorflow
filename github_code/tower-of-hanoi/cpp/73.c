//============================================================================
// Name        : TowerOfHanoi.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void TowerOfHanoi(int n, char frompeg, char topeg, char auxpeg)
{
	if(n == 1)
	{
		printf("Move disk 1 from peg %c to peg %c\n", frompeg, topeg);
		return;
	}

	/* Move top n-1 disks from A to B, using C as auxiliary */
	TowerOfHanoi(n-1, frompeg, auxpeg , topeg);

	printf("Move disk %d from peg %c to peg %c\n", n , frompeg, topeg);

	/* Move top n-1 disks from B to C, using A as auxiliary */
	TowerOfHanoi(n-1, auxpeg , topeg, frompeg);
}

int main() {
	TowerOfHanoi(5, 'A', 'B', 'C');
	return 0;
}
