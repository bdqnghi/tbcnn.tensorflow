#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Q_DP_27_RodCutting.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	
	

	
	
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
		
		vector<int> maxRevenueHashTable(rodLength, -1);
		return getMaxRevenueRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength);
	}

	
	

	int getMaxRevenueRodCutting_DP_BottomUp(const vector<int>& price, const int rodLength)
	{
		vector<int> maxRevenueHashTable(rodLength + 1);
		
		maxRevenueHashTable[0] = 0; 
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

	

	MM_DECLARE_FLAG(Q_DP_27_RodCutting)

	MM_UNIT_TEST(Q_DP_27_RodCutting_test_1, Q_DP_27_RodCutting)
	{
		
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
