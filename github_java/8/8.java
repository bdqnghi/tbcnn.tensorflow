class Solution {
  public static void main(String[] args) {
    String word1 = "kkka";
    String word2 = "13kkaz";
     System.out.println(minDistance(word1,word2));
  }

    public static int minDistance(String word1,String word2)
    {
      if (word1.equals(word2))
        return 0;
      int n=word1.length(), m = word2.length();
      int [][] dp = new int [n+1][m+1];
      for (int i=0;i<=n;i++)
      {
        dp[i][0] =i;
      }
      for (int j=0;j<=m;j++)
      {
        dp[0][j] = j;
      }
      for (int i=1;i<=n;i++)
      {
        for (int j=1;j<=m;j++)
        {
          if (word1.charAt(i-1)==word2.charAt(j-1))
          {
            dp[i][j] =dp[i-1][j-1];
          }
          else {
              dp[i][j] = Math.min(dp[i-1][j-1],Math.min(dp[i-1][j],dp[i][j-1]))+1;
          }
        }
      }
      return dp[n][m];
    }
}