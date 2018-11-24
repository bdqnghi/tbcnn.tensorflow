// Taken from the book Introduction to Algorithms, Third Ed. (CLRS)
// Section 15.1 Rod cutting

#include <iostream>
#include <vector>

using namespace std;

int rodcutting(int length, const vector<int> &prices) {
    vector<int> dp(length + 1, 0);

    for(int i = 1; i <= length; i++) {
        int maxprofit = 0;
        for(int j = 1; j <= i && j <= prices.size(); j++) {
            maxprofit = max(maxprofit, prices[j - 1] + dp[i - j]);
        }
        dp[i] = maxprofit;
    }

    return dp[length];
}

int main() {
    int length = 4;
    vector<int> prices {1, 5, 8, 9};

    cout << "Maximum profit: " << rodcutting(length, prices) << endl;

    return 0;
}