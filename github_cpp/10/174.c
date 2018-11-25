#include <string>
#include <gtest/gtest.h>

namespace projects_cpp {
namespace dynamic_programming {




int EditDistance(const std::string& a, const std::string& b) {
  
  if (a.empty() || b.empty()) {
    return std::max(a.size(), b.size());
  }

  const auto N = a.size(), M = b.size();
  int dp[N + 1][M + 1];
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= M; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = std::max(i, j); 
      } else {
        dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]) + 1,
                            dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1));
      }
    }
  }

  return dp[N][M];
}

namespace {

TEST(EditDistance, SimpleCase) {
  EXPECT_EQ(0, EditDistance("", ""));
  EXPECT_EQ(1, EditDistance("a", ""));
  EXPECT_EQ(1, EditDistance("", "a"));
  EXPECT_EQ(1, EditDistance("a", "b"));
  EXPECT_EQ(0, EditDistance("ab", "ab"));
  EXPECT_EQ(1, EditDistance("ab", "ac"));
  EXPECT_EQ(2, EditDistance("abcdefg", "labcdefgj"));
}

}
}
}