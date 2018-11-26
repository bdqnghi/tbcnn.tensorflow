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
  // Using bottom-up Dynamic Programming approach
  // Making 2X2 matrix to store subproblem costs
  int cost[m + 1][n + 1];

  for(int i = 0; i <= m; ++i){
    for (int j = 0; j <= n; ++j)
    {
      // If the first sentence is empty,
      // the cost will be the number of words
      // in the second sentence, because we will simply
      // insert all of the words from the second sentence
      // in order to have the two sentences be equalivent
      if(i == 0){
        cost[i][j] = j; // set the cost equal to the number of words in the second sentence
      }

      // Same case, but if the second sentence is empty
      else if(j == 0){
        cost[i][j] = i; // set the cost equal to the number of words in the first sentence
      }

      // If the last words are the same, the cost does not increase
      // then continue for the rest of the sentence
      else if (str1[i - 1] == str2[j - 1]){
        cost[i][j] = cost[i - 1][j - 1];
      }

      // If last character are different, consider all
      // possibilities and find minimum
      else{
        cost[i][j] = 1 + min(cost[i][j-1],    // Insert
                             cost[i-1][j],    // Remove
                             cost[i-1][j-1]); // Replace
      }
    }
  }

  return cost[m][n];
}

#endif // EDIT_DISTANCE_CPP_