#include <string>
#include <gtest/gtest.h>

namespace projects_cpp {
namespace dynamic_programming {

/**
 * Problem: Given two text strings A of length n and B of length m, you want to
 * transform A into B with a minimum number of operations of the following
 * types: delete a character from A, insert a character into A, or change some
 * character in A into a new character. The minimal number of such operations
 * required to transform A into B is called the edit distance between A and B.
 */

/**
 * dp[i][j], minimal distance from a[0..i] to b[0..j]
 */
int EditDistance(const std::string& a, const std::string& b) {
  // Sanity check.
  if (a.empty() || b.empty()) {
    return std::max(a.size(), b.size());
  }

  const auto N = a.size(), M = b.size();
  int dp[N + 1][M + 1];
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= M; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = std::max(i, j); // Init to number of characters there.
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