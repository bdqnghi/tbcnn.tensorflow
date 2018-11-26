#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Q_DP_27_RodCutting.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	// ============================= Problem Statement =============================
	/*
		Given a rod of length n and list of prices of rod of length i where 1 <= i <= n, Find 
		the optimal way to cut rod into smaller rods in order to maximize prot
	*/

	// ============================= Top-down (Recursive) =============================
	/*
	Complexity: O(n^n)
	Auxiliary space: O(1)

	This can be converted into general (not 1-0) knapsack problem, 
	to pick the rod pieces of different length (we can pick multiple pieces of same length),
	so that total length is less than or equal to given max rod length and total price is maximum
	*/
	int getMaxRevenueRodCutting_recursive(const vector<int>& price, const int rodLength)
	{
		if (rodLength == 0)
			return 0;

		int maxRevenue = 0;
		for (int rodLen = 1; rodLen <= rodLength; ++rodLen)
		{
			int currentRevenue = price[rodLen - 1] + getMaxRevenueRodCutting_recursive(price, rodLength - rodLen);
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
	int getMaxRevenueRodCutting_DP_TopDown(vector<int>& maxRevenueHashTable, const vector<int>& price, const int rodLength)
	{
		if (rodLength == 0)
			return 0;

		int maxRevenue = 0;
		for (int rodLen = 1; rodLen <= rodLength; ++rodLen)
		{
			if(maxRevenueHashTable[rodLength - rodLen] == -1)
				maxRevenueHashTable[rodLength - rodLen] = getMaxRevenueRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength - rodLen);

			int currentRevenue = price[rodLen - 1] + maxRevenueHashTable[rodLength - rodLen];
			if (maxRevenue < currentRevenue)
				maxRevenue = currentRevenue;
		}

		return maxRevenue;
	}

	int getMaxRevenueRodCutting_DP_TopDown(const vector<int>& price, const int rodLength)
	{
		// Create a hash table to store results of subproblems
		vector<int> maxRevenueHashTable(rodLength, -1);
		return getMaxRevenueRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength);
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

	int getMaxRevenueRodCutting_DP_BottomUp(const vector<int>& price, const int rodLength)
	{
		vector<int> maxRevenueHashTable(rodLength + 1);
		// initial condition:
		maxRevenueHashTable[0] = 0; // Rod of length 0 will earn 0 revenue
		for (int totalRodLen = 1; totalRodLen <= rodLength; ++totalRodLen)
		{
			for (int rodLen = 1; rodLen <= totalRodLen; ++rodLen)
			{
				int currentRevenue = price[rodLen - 1] + maxRevenueHashTable[totalRodLen - rodLen];
				if (maxRevenueHashTable[totalRodLen] < currentRevenue)
					maxRevenueHashTable[totalRodLen] = currentRevenue;
			}
			
		}

		return maxRevenueHashTable[rodLength];
	}

	// ============================= Unit Tests =============================

	MM_DECLARE_FLAG(Q_DP_27_RodCutting)

	MM_UNIT_TEST(Q_DP_27_RodCutting_test_1, Q_DP_27_RodCutting)
	{
		//const vector<int> length = { 1, 2, 3, 4, 5, 6, 7, 8 }; // Just to map lengths to prices
		const vector<int> price = { 1, 5, 8, 9, 10, 17, 17, 20 };
		int maxRevenue = 0;

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_recursive(price, 4)) == 10, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_DP_TopDown(price, 4)) == 10, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_DP_BottomUp(price, 4)) == 10, maxRevenue);

		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_recursive(price, 7)) == 18, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_DP_TopDown(price, 7)) == 18, maxRevenue);
		MM_EXPECT_TRUE((maxRevenue = getMaxRevenueRodCutting_DP_BottomUp(price, 7)) == 18, maxRevenue);
	}
	
}
