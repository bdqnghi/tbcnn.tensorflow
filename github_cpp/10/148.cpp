






#include "../headers/global.hpp"







public int minDistance(String word1, String word2) {
    
    int m = word1.length();
    int n = word2.length();
    int[][] dp = new int[m+1][n+1];
    
    for(int j=0;j<=n;j++) dp[0][j] = j;
    for(int i=1;i<=m;i++) { 
        dp[i][0] = i;
        for(int j=1;j<=n;j++)
            if(word1.charAt(i-1) != word2.charAt(j-1))
                dp[i][j] = Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1])) + 1;
            else dp[i][j] = dp[i-1][j-1];
    }
    return dp[m][n];
}









public int minDistance(String word1, String word2) {
    int m = word1.length();
    int n = word2.length();
    int[][] opt= new int[m+1][n+1];
    for(int i=0;i<=m;i++) opt[i][0] = i;
    for(int j=0;j<=n;j++) opt[0][j] = j;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            opt[i][j] = word1.charAt(i-1) == word2.charAt(j-1) ? opt[i-1][j-1] : Math.min(opt[i-1][j-1], Math.min(opt[i-1][j], opt[i][j-1])) + 1;
    return opt[m][n];
}


#define MAX 3


int minDistance(string word1, string word2) {
   int m = word1.length();
   int n = word2.length();
   
   vector<vector<int> > opt(m+1, vector<int>(n+1,0));
   
   for (int j=0;j<=n;j++) {
       opt[0][j] = j;
   }
   for (int i=1;i<=m;i++) {
       
       opt[i][0] = i;
       for (int j=1;j<=n;j++) {
           
           int min_cost = min( opt[i-1][j] + 1,opt[i][j-1] + 1);
           
           
           if (word1[i-1] == word2[j-1]) {
               opt[i][j] = min(opt[i-1][j-1],min_cost);
           } else {
               opt[i][j] = min(opt[i-1][j-1] + 1,min_cost);
           }
       }
   }
   return opt[m][n];
}













int minDistance(string word1, string word2) {
    int l1 = word1.size();
    int l2 = word2.size();
    vector<int> f(l2+1, 0);
    for (int j = 1; j <= l2; ++j)
        f[j] = j;

    for (int i = 1; i <= l1; ++i)
    {
        int prev = i;
        for (int j = 1; j <= l2; ++j)
        {
            int cur;
            if (word1[i-1] == word2[j-1]) {
                cur = f[j-1];
            } else {
                cur = min(min(f[j-1], prev), f[j]) + 1;
            }

            f[j-1] = prev;
            prev = cur;
        }
        f[l2] = prev;
    }
    return f[l2];
}

int minDistance(string word1, string word2) {
  
  int m = word1.length();
  int n = word2.length();
  int opt[MAX];
  if(m == 0 || n == 0) {
    return m + n;
  }
  opt[0] = minDistance(word1.substr(0,m-1),word2) + 1;
  opt[1] = minDistance(word1,word2.substr(0,n-1)) + 1;
  if(word1[m-1] == word2[n-1]) {
    opt[2] = minDistance(word1.substr(0,m-1),word2.substr(0,n-1));
  } else {
    opt[2] = minDistance(word1.substr(0,m-1),word2.substr(0,n-1)) + 1;
  }
  int min = opt[0];
  for(int i=1;i<MAX;i++) {
    if(min > opt[i]) {
      min = opt[i];
    }
  }
  return min;
}
int main() {
    string s = "algorithm";
    string t = "altruistic";
    int n = minDistance(s,t);
    cout << " min DIST ( " << s << "," << t << " ) = " << n << endl;
    n = edit_distance_rec(s,t);
    cout << " min DIST ( " << s << "," << t << " ) = " << n << endl;
}
