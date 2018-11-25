#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

int process(string str1, string str2, deque<char>& ret_str1, deque<char>& ret_str2)
{
	vector<vector<int>> dp = vector<vector<int>>(str1.size() + 1, vector<int>(str2.size() + 1, 0));

	for (int i = 1; i <= str1.size(); i++) dp[i][0] = i;
	for (int j = 1; j <= str2.size(); j++) dp[0][j] = j;

	for (int i = 1; i <= str1.size(); i++)
	{
		for (int j = 1; j <= str2.size(); j++)
		{
			if (str1[i - 1] == str2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
		}
	}

	int i = str1.size();
	int j = str2.size();
	while (i > 0 && j > 0)
	{
		int prev = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
		if (prev == dp[i][j])
		{
			ret_str1.push_front(str1[i - 1]);
			ret_str2.push_front(str2[j - 1]);

			i--;
			j--;
		}
		else if (prev == dp[i - 1][j - 1])
		{
			ret_str1.push_front(']');
			ret_str1.push_front(str1[i - 1]);
			ret_str1.push_front('[');

			ret_str2.push_front(']');
			ret_str2.push_front(str2[j - 1]);
			ret_str2.push_front('[');

			i--;
			j--;
		}
		else if (prev == dp[i - 1][j])
		{
			ret_str1.push_front(str1[i - 1]);
			ret_str2.push_front('_');
			i--;
		}
		else if (prev == dp[i][j - 1])
		{
			ret_str1.push_front('_');
			ret_str2.push_front(str2[j - 1]);
			j--;
		}
	}

	while (i > 0)
	{
		ret_str1.push_front(str1[i - 1]);
		i--;
	}

	while (j > 0)
	{
		ret_str2.push_front(str2[j - 1]);
		j--;
	}

	return dp[str1.size()][str2.size()];
}

