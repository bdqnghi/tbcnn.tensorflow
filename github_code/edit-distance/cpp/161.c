//
//  EditDistance.cpp
//  CPP
//
//  Created by zhaoze on 5/20/14.
//  Copyright (c) 2014 zhaoze. All rights reserved.
//

#include "EditDistance.h"
#include <cstring>
using namespace std;
class EditDistance{
public:
    int minDistance(string word1, string word2) {
        // word1.size() the returned value type is long.
        int size1 = (int)(word1.size()+1);
        int size2 = (int)(word2.size()+1);
        // cout<<size1<<" "<<size2;
        int dp[size2][size1];
        //set the dp matrix
        memset(dp, INT_MAX, sizeof(int)*size1*size2);
        // for(int i =size2)
        dp[0][0]=0;
        //init the first row
        for(int i = 1;i<size1;i++){
            dp[0][i] = i;
        }
        //init the first column
        for(int i = 1;i<size2;i++){
            dp[i][0]=i;
        }
        //start dp
        for(int i = 1;i<size2;i++)
            for(int j = 1;j<size1;j++){
                int n = 1;
                if(word1[j-1]==word2[i-1])
                    n = 0;
                //cout<<word1[j-1]<<" "<<word2[i-1]<<endl;
                int min = Mins(dp[i][j-1]+1, dp[i-1][j]+1, dp[i-1][j-1]+n);
                dp[i][j]=min;
                
            }
        return dp[size2-1][size1-1];
    }
    int Mins(int a, int b, int c){
        int min = 0;
        if(a>b){
            if(b>c)
                min = c;
            else
                min = b;
        }else{
            if(a>c){
                min = c;
            }
            else
                min = a;
        }
        return min;
    }
};