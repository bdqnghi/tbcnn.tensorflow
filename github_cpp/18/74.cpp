#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Q_DP_28_MaxProductRodCutting.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	
	

	
	
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
		
		vector<int> maxRevenueHashTable(rodLength, -1);
		return getMaxRevenueMaxProductRodCutting_DP_TopDown(maxRevenueHashTable, price, rodLength);
	}

	
	

	int getMaxRevenueMaxProductRodCutting_DP_BottomUp(const vector<int>& price, const int rodLength)
	{
		vector<int> maxRevenueHashTable(rodLength + 1);
		
		maxRevenueHashTable[0] = 1; 
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

	

	MM_DECLARE_FLAG(Q_DP_28_MaxProductRodCutting)

	MM_UNIT_TEST(Q_DP_28_MaxProductRodCutting_test_1, Q_DP_28_MaxProductRodCutting)
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
