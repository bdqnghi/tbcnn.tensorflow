#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

int editDistance(std::string, std::string);

int main() {
	std::cout << editDistance("sitting", "kitten") << std::endl;
	return 0;
}

int editDistance(std::string s1, std::string s2) {
	int m = s1.size();
	int n = s2.size();

	int dp[m+1][n+1];
	memset(dp, 0, sizeof(dp));

	for(int i = 0; i <= m; i++) {
		dp[0][i] = i;
	}

	for(int i = 0; i <= n; i++) {
		dp[i][0] = i;
	}

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			if(s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j -1];
			} else {
				dp[i][j] = 1 + std::min(dp[i - 1][j - 1],
					std::min(dp[i][j - 1], dp[i - 1][j]));
			}

		}
	}
	return dp[m][n];
}