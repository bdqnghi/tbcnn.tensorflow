#include "stdafx.h"
#include "RodCutting.h"

void RodCutting::MakeUnitPrices()
{
	UnitPrices[0] = 0;
	UnitPrices[1] = 1;
	UnitPrices[2] = 5;
	UnitPrices[3] = 8;
	UnitPrices[4] = 9;
	UnitPrices[5] = 10;
	UnitPrices[6] = 17;
	UnitPrices[7] = 17;
	UnitPrices[8] = 20;
	UnitPrices[9] = 24;
	UnitPrices[10] = 30;
}

void RodCutting::RodCuttingTest()
{
	MakeUnitPrices();

	unsigned int cuttingSize = rand() % 10;
	unsigned int price = RodCuttingRecursive(cuttingSize);

	printf("RodCuttingRecursive : input %u, price %u\n", cuttingSize, price);
	CheckBestCuttingWay(cuttingSize);

	price = RodCuttingDynamic(cuttingSize);
	
	printf("RodCuttingDynamic : input %u, price %u\n", cuttingSize, price);
	CheckBestCuttingWay(cuttingSize);

	price = RodCuttingBottomUp(cuttingSize);

	printf("RodCuttingDynamic : input %u, price %u\n", cuttingSize, price);
	CheckBestCuttingWay(cuttingSize);

}

unsigned int RodCutting::RodCuttingRecursive(unsigned int size)
{

	if(size  < 2 )
	{
		return UnitPrices[size];
	}
	else
	{
		unsigned int maxPrice = 0;
		for(unsigned int i = 1; i < size + 1; ++i)
		{
			unsigned int curPrice = 
				UnitPrices[i] + RodCuttingRecursive(size - i);

			if(curPrice > maxPrice)
			{
				maxPrice = curPrice;
				FirstCuttingSize[size] = i;
			}
		}
		return maxPrice;
	}

}

unsigned int RodCutting::RodCuttingDynamic(unsigned int size)
{
	if(RodCutting::MaxPrices.find(size) != MaxPrices.end())
		return MaxPrices[size];

	if(size < 2)
	{
		MaxPrices[size] = UnitPrices[size];
	}
	else
	{
		MaxPrices[size] = 0;
		for(unsigned i = 1; i < size + 1; ++i)
		{
			unsigned int currPrice =
				UnitPrices[i] + RodCuttingDynamic(size - i);

			if(currPrice > MaxPrices[size])
			{
				MaxPrices[size] = currPrice;
				FirstCuttingSize[size] = i;
			}
		}
	}

	return MaxPrices[size];
}

unsigned int RodCutting::RodCuttingBottomUp(unsigned int size)
{

	for(unsigned checkIdx = 0; checkIdx <= size; ++checkIdx)
	{
		MaxPrices[checkIdx] = UnitPrices[checkIdx];
		for(unsigned i = 1; i < checkIdx; ++i)
		{
			unsigned int currPrice =
				UnitPrices[i] + MaxPrices[checkIdx - i];

			if(currPrice > MaxPrices[checkIdx])
			{
				FirstCuttingSize[checkIdx] = i;
				MaxPrices[checkIdx] = currPrice;
			}
		}
	}

	return MaxPrices[size];
}

void RodCutting::CheckBestCuttingWay(unsigned int size)
{	
	printf("Find Most Optimized CuttingWay of size %u :", size);
	while(true)
	{
		printf("%d", FirstCuttingSize[size]);
		size -= FirstCuttingSize[size];
		if(FirstCuttingSize[size] == 0)
			break;
		printf("/");
	}
	printf("\n");
}
