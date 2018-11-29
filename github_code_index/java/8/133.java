
public int minDistance(String word1, String word2) {
        if(word1==null||word1.length()==0) return word2.length();
        if(word2==null||word2.length()==0) return word1.length();
        
        int n = word1.length();
        int m = word2.length();
        int[][] dp = new int[n+1][m+1];
        
        for(int i=0;i<=m;i++){
            dp[0][i] = i;
        }
        
        for(int i=0;i<=n;i++){
            dp[i][0] = i;
        }
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int a = dp[i-1][j-1]+(word1.charAt(i-1)==word2.charAt(j-1)?0:1);
                int b = dp[i-1][j]+1;
                int c = dp[i][j-1]+1;
                dp[i,j] =Math.min(Math.min(a,b),c);
            }
        }
        return dp[n][m];
    }

// Method 2: O(n) space
public int minDistance(String word1, String word2) {
        int l1 = word1.length();
        int l2 = word2.length();

        int[] dp = new int[l2+1];
        for (int j = 1; j <= l2; j++)
            dp[j] = j;

        for (int i = 1; i <= l1; i++)
        {
            int prev = i;
            for (int j = 1; j <= l2; j++)
            {
                int cur;
                cur = Math.min(Math.min(dp[j-1]+((word1.charAt(i-1) == word2.charAt(j-1))?0:1), prev+1), dp[j]+1);
                dp[j-1] = prev;
                prev = cur;
            }
            dp[l2] = prev;
        }
        return dp[l2];
    }
