class Solution {
public:
	int minDistance(string word1, string word2) {
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
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
