







#include "EditDistance.h"
#include <cstring>
using namespace std;
class EditDistance{
public:
    int minDistance(string word1, string word2) {
        
        int size1 = (int)(word1.size()+1);
        int size2 = (int)(word2.size()+1);
        
        int dp[size2][size1];
        
        memset(dp, INT_MAX, sizeof(int)*size1*size2);
        
        dp[0][0]=0;
        
        for(int i = 1;i<size1;i++){
            dp[0][i] = i;
        }
        
        for(int i = 1;i<size2;i++){
            dp[i][0]=i;
        }
        
        for(int i = 1;i<size2;i++)
            for(int j = 1;j<size1;j++){
                int n = 1;
                if(word1[j-1]==word2[i-1])
                    n = 0;
                
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