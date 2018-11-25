#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
 
int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.length();
    int n = s2.length();
    
    
    
    std::vector<std::vector<int> > d(m+1, std::vector<int>(n+1));
 
    
    
    for (int i = 1; i <= m; i++) {
        d[i][0] = i;
    }

    
    
    for (int j = 1; j <= n; j++) {
        d[0][j] = j;
    }
 
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (s1[i-1] == s2[j-1])
                d[i][j] = d[i-1][j-1];  
            else
                d[i][j] = std::min({d[i-1][j] + 1,   
                                d[i][j-1] + 1,      
                                d[i-1][j-1] + 1});   
        }
    }

    return d[m][n];
}




