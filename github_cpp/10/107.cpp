#ifndef EDIT_DISTANCE_CPP_
#define EDIT_DISTANCE_CPP_

#include "EditDistance.h"

int EditDistance::min(int x, int y, int z)
{
  if(x < y && x < z){
    return x;
  }
  else if(y < x && y < z){
    return y;
  }
  else if(z < y && z < x){
    return z;
  }
  
}

int EditDistance::ED(vector <string> str1, int m, vector <string> str2, int n)
{
  
  
  int cost[m + 1][n + 1];

  for(int i = 0; i <= m; ++i){
    for (int j = 0; j <= n; ++j)
    {
      
      
      
      
      
      if(i == 0){
        cost[i][j] = j; 
      }

      
      else if(j == 0){
        cost[i][j] = i; 
      }

      
      
      else if (str1[i - 1] == str2[j - 1]){
        cost[i][j] = cost[i - 1][j - 1];
      }

      
      
      else{
        cost[i][j] = 1 + min(cost[i][j-1],    
                             cost[i-1][j],    
                             cost[i-1][j-1]); 
      }
    }
  }

  return cost[m][n];
}

#endif 