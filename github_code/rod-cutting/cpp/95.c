#include "RodCutting.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

int main()
{
	//Init datas for test
	const int MAX_ROD_LEN = 10;

	srand((unsigned int)time(NULL));

	int priceTable[MAX_ROD_LEN + 1] = { 0, };
	
	for (int i = 1; i <= MAX_ROD_LEN; i++)
	{
		priceTable[i] = (rand() % 10) + 1;
		cout << "Length: " << i << " Price: " << priceTable[i] << endl;
 	}
	cout << endl;

	int rodLength = MAX_ROD_LEN;

	//RodCutting Algorithm test
	RodCutting rodCutting;

	int topDown = rodCutting.TopDown(priceTable, rodLength);

	cout << "[TopDown] : " << topDown << endl;

	int memo = rodCutting.Memo(priceTable, rodLength);

	cout << "[Memo] : " << memo << endl;

	int bottomUp = rodCutting.BottomUp(priceTable, rodLength);

	cout << "[BottomUp] : " << bottomUp << endl;

	return 0;
}