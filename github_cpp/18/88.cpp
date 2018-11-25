#include "RodCutting.h"

int RodCutting::TopDown(int* priceTable, int wholeLength)
{
	if (wholeLength == 0)
		return 0;

	int maxPrice = priceTable[wholeLength];
	
	for (int cutLength = 1; cutLength <= wholeLength / 2; cutLength++)
	{
		int cutPrice = priceTable[cutLength] + TopDown(priceTable, wholeLength - cutLength);
		maxPrice = max(maxPrice, cutPrice);
	}

	return maxPrice;
}

int RodCutting::Memo(int* priceTable, int rodLength)
{
	if (priceTable == nullptr || rodLength <= 0)
		return 0;

	int* memo = new int[rodLength + 1];
	
	memo[0] = 0;
	for (int i = 1; i <= rodLength; i++)
	{
		memo[i] = NOT_CALCULATED;
	}

	int res = _Memo(priceTable, memo, rodLength);

	delete[] memo;

	return res;
}

int RodCutting::_Memo(int* priceTable, int* memo, int rodLength)
{
	if (rodLength == 0)
		return 0;

	if (memo[rodLength] != NOT_CALCULATED)
		return memo[rodLength];

	int maxPrice = priceTable[rodLength];

	for (int cutLength = 1; cutLength <= rodLength/2; cutLength++)
	{
		int cutPrice = priceTable[cutLength] + _Memo(priceTable, memo, rodLength - cutLength);
		maxPrice = max(maxPrice, cutPrice);
	}

	memo[rodLength] = maxPrice;

	return maxPrice;
}

int RodCutting::BottomUp(int* priceTable, int rodLength)
{
	int* maxPriceTable = new int[rodLength + 1];
	
	maxPriceTable[0] = 0;
	
	for (int currentLength = 1; currentLength <= rodLength; currentLength++)
	{
		int maxPrice = 0;

		for (int cutLength = 0; cutLength <= currentLength; cutLength++)
		{
			int cutPrice = priceTable[cutLength] + maxPriceTable[currentLength - cutLength];
			maxPrice = max(maxPrice, cutPrice);
		}

		maxPriceTable[currentLength] = maxPrice;
	}

	int res = maxPriceTable[rodLength];

	delete[] maxPriceTable;

	return res;
}