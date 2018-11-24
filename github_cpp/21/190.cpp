class Solution {
public:
	int minDistance(string word1, string word2) {
	    // https://oj.leetcode.com/problems/edit-distance/
	    //
	    // Given two words word1 and word2, find the minimum number of steps 
	    // required to convert word1 to word2. Each step can be either
	    // insert or delete or replace a character.
	    
	    // Solution: DP
	    // f(i, j) := minDist(word1[0..i), word2[0..j));
	    // f(i, j) = f(i-1, j-1)  if w[i] == w[j]
	    //     or, min( f(i-1,j-1) + 1, using replace
	    //              f(i,  j-1) + 1, using add
	    //              f(i-1,j  ) + 1, using delete
	    //            )
	    // edge case: f(0,k)=f(k,0)=k
	    // f(i) = save, // save := f(i-1,j-1)
	    //     or min(f(i-1), f(i), save) + 1
	    int m = word1.size();
	    int n = word2.size();
	    if (m == 0) { return n; }
	    if (n == 0) { return m; }
	    vector<int> f(n+1);
	    for (int i = 0; i <= n; i++) {
	        f[i] = i;
	    }
	    for (int row = 1; row <= m; row++) {
	        int save = f[0];
	        f[0]++;
	        for (int i = 1; i <= n; i++) {
	            int new_save = f[i];
	            if (word1[row-1] == word2[i-1]) {
	                f[i] = save;
	            }
	            else {
	                f[i] = min(min(save, f[i-1]), f[i]) + 1;
	            }
	            save = new_save;
	        }
	    }
	    return f[n];
	}
};
