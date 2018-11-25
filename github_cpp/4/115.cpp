



#include "stdafx.h"
#include <iostream>


void Hanoi(int n, char frompeg, char topeg, char auxpeg)
{
	
	if (n == 1) {
		cout << "move disk 1 from " << frompeg << " to " <<  topeg;
		return;
	}

	
	Hanoi(n - 1, frompeg, topeg, auxpeg);

	
	Hanoi(n, frompeg, topeg, auxpeg);

	Hanoi(n + 1, frompeg, topeg, auxpeg);
}

using namespace std;


int main()
{
    return 0;
}

