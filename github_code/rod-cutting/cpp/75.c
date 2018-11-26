// CoinChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int prices[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20 };
int N = sizeof(prices) / sizeof(prices[0]) - 1;

#define MINF -987654321
#define MAX(a,b) ((a)>(b)?(a):(b))

int cache[100 + 1];
void initCache() {
	for (int i = 0; i < 101; i++)
		cache[i] = -1;
}

int rodCutting(int length) {
	if (length <= 0)
		return 0;

	if (cache[length] != -1)
		return cache[length];

	int Ans = MINF;
	for (int i = 1; i <= length; i++) {
		int option = prices[i] + rodCutting(length - i);
		Ans = MAX(Ans, option);
	}

	return cache[length] = Ans;
}
int _tmain(int argc, _TCHAR* argv[])
{
	initCache();
	cout << rodCutting(N);
	return 0;
}

