#include "stdafx.h"
#include <stdint.h>
#include <functional>

#include "RodCutting.h"

namespace DynamicProgramming
{
	int RodCutting::Brute_Rod_Cutting(int * priceList, int length)
	{
		if (length < 0 || priceList == nullptr)
		{
			return INT_MIN;
		}

		if (length == 0) return 0;

		int maxPrice = INT_MIN;
		for (int i = 0; i <= length; ++i)
		{
			int cuttingPrice = Brute_Rod_Cutting(priceList, length - i) + priceList[i];
			maxPrice = (maxPrice > cuttingPrice) ? maxPrice : cuttingPrice ;
		}

		return maxPrice;
	}

	int RodCutting::Memoization_Rod_Cutting(int * priceList, int length)
	{
		if (priceList == nullptr || length < 0)
		{
			return INT_MIN;
		}

		if (length == 0) return 0;

		auto maxPriceMemo = new int[length + 1];
		for (auto i = 0; i <= length; ++i)
		{
			maxPriceMemo[i] = { 0 };
		}

		std::function<int(int*, int, int*)> recursiveProgress = [&](int * priceList, int length, int * maxPriceMemo) 
		{
			if (maxPriceMemo[length] != 0) return maxPriceMemo[length];

			int maxPrice = INT_MIN;

			for (auto i = 1; i < length; ++i)
			{
				int cuttingPrice = recursiveProgress(priceList, length - i, maxPriceMemo) + priceList[i];

				maxPrice = (maxPrice > cuttingPrice) ? maxPrice : cuttingPrice;
			}

			maxPriceMemo[length] = maxPrice;

			return maxPrice;
		};

		auto wholeRodPrice = recursiveProgress(priceList, length, maxPriceMemo);

		delete[] maxPriceMemo;

		return wholeRodPrice;
	}

	int RodCutting::Bottom_Up_Rod_Cutting(int * priceList, int length)
	{
		if (priceList == nullptr || length < 0)
		{
			return INT_MIN;
		}

		if (length == 0) return 0;


		return 0;
	}
}