//
//  P072_EditDistance.cpp
//  CppPlayground
//
//  Created by Hui Hui on 11/2/16.
//  Copyright © 2016 Hui Hui. All rights reserved.
//

#include <string>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        
        int distance[word1.length()+1][word2.length()+1];
        
        for (int i =0; i<=word1.length(); i++) {
            distance[i][0] = i;
        }
        
        for (int i=0; i<=word2.length(); i++) {
            distance[0][i] = i;
        }
        
        for (int i=1; i<=word1.length(); i++) {
            for (int j=1; j<=word2.length(); j++) {
                
                int min = distance[i-1][j] + 1;
                
                int left = distance[i][j-1] + 1;
                if (min > left) {
                    min = left;
                }
                
                int mid = distance[i-1][j-1];
                if (word1[i-1] != word2[j-1]) {
                    mid += 1;
                }
                
                if (min > mid) {
                    min = mid;
                }
                
                distance[i][j] = min;
            }
        }
        
        return distance[word1.length()][word2.length()];
    }
};
