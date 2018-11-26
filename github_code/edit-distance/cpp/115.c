size_t distance(const std::string &s, const std::string &t) {
  // levenshtein distance between s and t
  auto dp=std::vector<std::vector<size_t>>(
      s.length()+1,
      std::vector<size_t>(t.length()+1, inf<size_t>));

  dp[0][0] = 0;
  for (size_t i=0; i<=s.length(); ++i)
    dp[i][0] = i;
  for (size_t j=0; j<=t.length(); ++j)
    dp[0][j] = j;

  for (size_t i=1; i<=s.length(); ++i) {
    for (size_t j=1; j<=t.length(); ++j) {
      dp[i][j] = std::min(
          {dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+(s[i-1]!=t[j-1])}
      );
    }
  }

  return dp[s.length()][t.length()];
}

size_t distance_star(const std::string &s, const std::string &t) {
  // min(levenshtein distance between s and t^i) for any integer i
  size_t slen=s.length(), tlen=t.length();
  auto dp=std::vector<std::vector<size_t>>(
      tlen, std::vector<size_t>(slen+1, inf<size_t>));

  dp[0][0] = 0;
  for (size_t i=1; i<=slen; ++i)
    dp[0][i] = i;
  for (size_t j=1; j<tlen; ++j)
    dp[j][0] = j;

  for (size_t i=0; i<slen; ++i) {
    size_t ni=i+1;
    for (size_t jj=0; jj<tlen*2; ++jj) {
      size_t j=jj%tlen, nj=(jj+1)%tlen;
      dp[nj][ni] = std::min(
          {dp[j][i]+(s[i]!=t[j]), dp[nj][i]+1, dp[j][ni]+1}
      );
    }
  }

  return dp[0][slen];
}
