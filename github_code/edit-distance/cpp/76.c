/*
 * EditDistance.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: hatemfaheem
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	int minimum(int a, int b){
		return (a<=b)?a:b;
	}
    int minDistance(string word1, string word2) {
    	int n = word1.size(), m = word2.size();
    	int ** distance = new int*[n+1];
    	for (int i=0; i<=n; i++){
    		distance[i] = new int[m+1];
    		for (int j=0; j<=m; j++)
    			if (i==0) distance[i][j]=j;
    			else if (j==0) distance[i][j]=i;
    			else distance[i][j]=0;
    	}
    	for (int i=1; i<=n; i++)
    		for (int j=1; j<=m; j++)
    			if (word1[i-1] == word2[j-1])
    				distance[i][j] = distance[i-1][j-1];
    			else
    				distance[i][j] = minimum(distance[i-1][j-1]+1,
    						minimum(distance[i][j-1]+1, distance[i-1][j]+1));
    	return distance[n][m];
    }
};


