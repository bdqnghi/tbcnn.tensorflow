#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

string process(vector<pair<int,int>>& input) {
	int n = input.size();
	if (n == 1) {
		return "A1";
	}
	vector<vector<pair<int,string>>> dp;
	for (int i=0; i<n; i++)
		dp.emplace_back(n);
	for (int i=0; i<n; i++) {
		dp[i][i] = make_pair(0, "A" + to_string(i+1));
	}
	for (int i=0; i<n-1; i++) {
		dp[i][i+1] = make_pair(input[i].first * input[i].second * input[i+1].second, 
								"(A" + to_string(i+1) + " x A" + to_string(i+2) + ")");
	}
	for (int len=3; len<=n; len++) {
		for (int i=0; i+len<=n; i++) {
			dp[i][i+len-1] = make_pair(dp[i+1][i+len-1].first + input[i].first * input[i].second * input[i+len-1].second, 
										"(" + dp[i][i].second + " x " + dp[i+1][i+len-1].second + ")");
			for (int k=i+1; k<i+len-1; k++) {
				int m = input[i].first * input[k].second * input[i+len-1].second + dp[i][k].first + dp[k+1][i+len-1].first;
				if (m <= dp[i][i+len-1].first) {
					dp[i][i+len-1] = make_pair(m, "("+dp[i][k].second+" x "+dp[k+1][i+len-1].second+")");
				}
			}
		}
	}
	return dp[0][n-1].second;
}

int main() {

	int n, c = 0;
	while (scanf("%d\n", &n), n) {
		vector<pair<int,int>> input;
		for (int i=0; i<n; i++) {
			int a,b;
			scanf("%d %d\n", &a, &b);
			input.push_back(make_pair(a,b));
		}
		string s = process(input);
		cout << "Case " << ++c << ": ";
		cout << s << endl;
	}

}