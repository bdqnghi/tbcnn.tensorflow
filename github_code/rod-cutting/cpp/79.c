#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "DynamicProgramming/DP_MaxProductRodCutting.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	// ============================= Problem Statement =============================
	/*
		Given a rod of length n, Find the
optimal way to cut rod into smaller
rods in order to maximize product of
price of each of the smaller rod.
Assume each rod of length i has price i.
	*/

	// ============================= Top-down (Recursive) =============================
	/*
	Complexity: O(n^n)
	Auxiliary space: O(1)

	This can be converted into general (not 1-0) knapsack problem, 
	to pick the rod pieces of different length (we can pick multiple pieces of same length),
	so that total length is less than or equal to given max rod length and product of prices is maximum
	*/
	int getMaxRevenueMaxProductRodCutting_recursive(const vector<int>& price, const int rodLength)
	{
		if (rodLength == 0)
			return 1;

		int maxRevenue = 0;
		for (int rodLen = 1; rodLen <= rodLength; ++rodLen)
		{
			int currentRevenue = price[rodLen - 1] * getMaxRevenueMaxProductRodCutting_recursive(price, rodLength - rodLen);
			if (maxRevenue < currentRevenue)
				maxRevenue = currentRevenue;
		}

		return maxRevenue;
	}

	// ============================= Top-down dynamic programming =============================
	/*
	Complexity: O(n*n)
	Auxiliary space: O(n + 1)
	Recurrence relation:
		maxRevenue(n) = max( price(1) + maxRevenue(n - 1),
							 price(2) + maxRevenue(n - 2),
							 ...
							 price(n))
	*/
	int getMaxRevenueMaxProductRodCutting_DP_TopDown(vector<int>& maxRevenueHashTable, const vector<int>& price, const int rodLength)
	{
		if (rodLength == 0)
			return 1;

		int maxRevenue = 0;
		for (int rodLen = 1; rodLen <= rodLength; ++rodLen)
		{
			if(maxRevenueHashTable[rodLength - rodLen] == -1)
				maxRevenueHashTable[rodLength - rodLen] = getMaxRevenueMaxProductRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength - rodLen);

			int currentRevenue = price[rodLen - 1] * maxRevenueHashTable[rodLength - rodLen];
			if (maxRevenue < currentRevenue)
				maxRevenue = currentRevenue;
		}

		return maxRevenue;
	}

	int getMaxRevenueMaxProductRodCutting_DP_TopDown(const vector<int>& price, const int rodLength)
	{
		// Create a hash table to store results of subproblems
		vector<int> maxRevenueHashTable(rodLength, -1);
		return getMaxRevenueMaxProductRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength);
	}

	// ============================= bottom-up dynamic programming =============================
	/*
	Complexity: O(n*n)
	Auxiliary space: O(n + 1)
	Recurrence relation:
		maxRevenue(n) = max( price(1) + maxRevenue(n - 1),
							 price(2) + maxRevenue(n - 2),
							 ...
							 price(n))
	*/

	int getMaxRevenueMaxProductRodCutting_DP_BottomUp(const vector<int>& price, const int rodLength)
	{
		vector<int> maxRevenueHashTable(rodLength + 1);
		// initial condition:
		maxRevenueHashTable[0] = 1; // Rod of length 0 will earn revenue 1 so that product can not be zero
		for (int totalRodLen = 1; totalRodLen <= rodLength; ++totalRodLen)
		{
			for (int rodLen = 1; rodLen <= totalRodLen; ++rodLen)
			{
				int currentRevenue = price[rodLen - 1] * maxRevenueHashTable[totalRodLen - rodLen];
				if (maxRevenueHashTable[totalRodLen] < currentRevenue)
					maxRevenueHashTable[totalRodLen] = currentRevenue;
			}
			
		}

		return maxRevenueHashTable[rodLength];
	}

	// ============================= Unit Tests =============================

	MM_DECLARE_FLAG(DP_MaxProductRodCutting)

	MM_UNIT_TEST(DP_MaxProductRodCutting_test_1, DP_MaxProductRodCutting)
	{
		const vector<int> price = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		int rodLength = 4;
		int maxRevenue = 0;

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_recursive(price, 4)) == 4, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_TopDown(price, 4)) == 4, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_BottomUp(price, 4)) == 4, maxRevenue);

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_recursive(price, 6)) == 9, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_TopDown(price, 6)) == 9, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_BottomUp(price, 6)) == 9, maxRevenue);

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_recursive(price, 8)) == 18, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_TopDown(price, 8)) == 18, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_BottomUp(price, 8)) == 18, maxRevenue);

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_recursive(price, 15)) == 243, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_TopDown(price, 15)) == 243, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueMaxProductRodCutting_DP_BottomUp(price, 15)) == 243, maxRevenue);
	}
	
}
