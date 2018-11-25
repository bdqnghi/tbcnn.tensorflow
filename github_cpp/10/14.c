

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

class EditDistance {
public:
    int minDistance(string s1, string s2) {
        
        
        
        
        
        
        
        return solve_by_dp(s1, s2);
    }

    int solve_by_dp(string s1, string s2) {
        
        
        
        
        
        int m = s1.size() + 1;
        int n = s2.size() + 1;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + 1;
        }
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + 1;
            for (int j = 1; j < n; ++j) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    
                    dp[i][j] =
                        std::min(dp[i - 1][j - 1],
                                 std::min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
        }
        return dp[m - 1][n - 1];
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.edit_distance" ) {
    EditDistance sol;
    using TestCase = std::tuple< string, string, int >;
    std::vector<TestCase> test_cases {
        TestCase{ "a", "b", 1 },
        TestCase{ "sea", "eat", 2 },
        TestCase{ "delete", "leet", 3 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.minDistance(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
