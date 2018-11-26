// 072-Edit Distance.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
		int m = word1.length()+1, n = word2.length()+1;
		vector<vector<int>> distance(m, vector<int>(n,0));
		for(int i = 0; i < m; i++) distance[i][0] = i;
		for(int i = 1; i < n; i++) distance[0][i] = i;
		for(int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (word1[i-1]==word2[j-1]) distance[i][j] = distance[i-1][j-1];
				else distance[i][j] = min(distance[i-1][j-1]+1, min(distance[i][j-1]+1,distance[i-1][j]+1));
			}
		}
		return distance[m-1][n-1];
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

