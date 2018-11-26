//Edit Distance
//Given two words word1 and word2, find the minimum number of steps required to
//convert word1 to word2. (each operation is counted as 1 step.)
//You have the following 3 operations permitted on a word:
//a) Insert a character
//b) Delete a character
//c) Replace a character
#include "../headers/global.hpp"

// s1 = a....a
// s2 = ab

//#########################################DP#########################################
//String prefix 1. Find Matching prefix 2. Find opt tranformation among
//insert(Pick 1st prefix),delete(Pick 2nd prefix),replace
public int minDistance(String word1, String word2) {
    //prefixes of 1 char
    int m = word1.length();
    int n = word2.length();
    int[][] dp = new int[m+1][n+1];
    //Assume word1--| word2---> and word1 is empty
    for(int j=0;j<=n;j++) dp[0][j] = j;
    for(int i=1;i<=m;i++) { //iterave over word1
        dp[i][0] = i;
        for(int j=1;j<=n;j++)
            if(word1.charAt(i-1) != word2.charAt(j-1))
                dp[i][j] = Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1])) + 1;
            else dp[i][j] = dp[i-1][j-1];
    }
    return dp[m][n];
}

//1.Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for
//replacement));
//2.Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i
//- 1][j] + 1 (for deletion));
//3.Insert word2[j - 1] to word1[0..i - 1] and word1[0..i - 1] + word2[j - 1] =
//word2[0..j - 1] (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).

//#########################################DP#########################################
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

//######################################## DP implementation ########################################
int minDistance(string word1, string word2) {
   int m = word1.length();
   int n = word2.length();
   //int opt[m+1][n+1];
   vector<vector<int> > opt(m+1, vector<int>(n+1,0));
   //Initialize columns
   for (int j=0;j<=n;j++) {
       opt[0][j] = j;
   }
   for (int i=1;i<=m;i++) {
       //Lazy row initialization
       opt[i][0] = i;
       for (int j=1;j<=n;j++) {
           //min_cost of insert and delete
           int min_cost = min( opt[i-1][j] + 1,opt[i][j-1] + 1);
           //As initialization start at 0th row and column use i-1,j-1 as the current string index for
           //word1 and word2
           if (word1[i-1] == word2[j-1]) {
               opt[i][j] = min(opt[i-1][j-1],min_cost);
           } else {
               opt[i][j] = min(opt[i-1][j-1] + 1,min_cost);
           }
       }
   }
   return opt[m][n];
}
//######################################## Optimized DP ########################################
//Use f[i][j] to represent the shortest edit distance between word1[0,i) and
//word2[0, j). Then compare the last character of word1[0,i) and word2[0,j),
//which are c and d respectively (c == word1[i-1], d == word2[j-1]):
//if c == d, then : f[i][j] = f[i-1][j-1]
//Otherwise we can use three operations to convert word1 to word2:
//(a) if we replaced c with d: f[i][j] = f[i-1][j-1] + 1;
//(b) if we added d after c: f[i][j] = f[i][j-1] + 1;
//(c) if we deleted c: f[i][j] = f[i-1][j] + 1;
//Note that f[i][j] only depends on f[i-1][j-1], f[i-1][j] and f[i][j-1],
//therefore we can reduce the space to O(n) by using only the (i-1)th array and
//previous updated element(f[i][j-1]).
//
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
//######################################## Recursive implementation ########################################
int minDistance(string word1, string word2) {
  //base case
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
