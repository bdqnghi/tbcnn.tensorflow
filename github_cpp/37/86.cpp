/**
 * Rod cutting CLRS 15.1
 * */

#include "rod_cutting.h"
#include <vector>
#include <algorithm>
#include <utility>

/**
 * OPT[n] = max_{1 <= k <= n} OPT[n-k] + p[k]
 * OPT[0] = 0
 * */
int rotCutting(int n, const std::vector<int>& prices) {
    if (n < 1) return 0; 
    int k = prices.size();
    std::vector<int> DP(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k && j < i; j++) {
            DP[i] = std::max(DP[i-1-j] + prices[j], DP[i]);
        }
    }
    return DP.back();
}

int rotCutting(int n, const std::vector<int>& prices, std::vector<int>& solution) {
    if (n < 1) return 0; 
    int k = prices.size(), ci = n;
    std::vector<std::pair<int, int>> DP(n + 1, std::make_pair(0, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k && j < i; j++) {
            if (DP[i].first < DP[i-1-j].first + prices[j]) {
                DP[i] = std::make_pair(DP[i-1-j].first + prices[j], i - 1 - j);
            }
        }
    }
    // reconstruct the result
    while (ci > 0) {
        solution.push_back(ci - DP[ci].second);
        ci = DP[ci].second;
    }
    return DP[n].first;
}
