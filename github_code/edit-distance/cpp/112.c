//
//  072_Edit Distance.cpp
//  leetcode
//
//  Created by gexin on 15/6/11.
//  Copyright (c) 2015年 gexin. All rights reserved.
//

#include <stdio.h>
#include"common.h"
class Solution072 {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        if(len1 == 0 || len2 == 0)
            return ((len1 == 0)?len2:len1);
        distance = new int*[len1 + 1];
        for(int i = 0; i <= len1; i++){
            distance[i] = new int[len2 + 1];
            for(int j = 0; j < len2 + 1; j++)
                distance[i][j] = -1;
        }
        return recursive(word1,word2,len1,len2);
    }
    int recursive(string word1,string word2,int i,int j){
        cout<<i<<" "<<j<<endl;
        if(i == 0 || j == 0)
            return ((i == 0)?j:i);
        else if(distance[i][j] != -1)return distance[i][j];
        else if(word1[i - 1] == word2[j - 1])distance[i][j] = recursive(word1,word2,i-1,j-1);
        else
            distance[i][j] = min(min(recursive(word1,word2,i-1,j),recursive(word1,word2,i,j-1)),recursive(word1,word2,i-1,j-1)) + 1;
        return distance[i][j];
    }
private:
    int **distance;
};
int main072(){
    Solution072 so;
    cout<<so.minDistance("a", "a")<<endl;
    return 0;
}