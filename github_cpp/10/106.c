







#include "EditDistance.h"

using namespace std;

void EditDistance::run()
{
    cout<<"Run EditDistance"<<endl;
    
    test1();
}

void EditDistance::test1()
{
    string word1 = "intention";
    string word2 = "execution";
    
    int result = minDistance(word1, word2);
    int expected = 5;
    
    assert(result == expected);
}


int EditDistance::minDistance(std::string word1, std::string word2)
{
    
    int m = word1.size();
    int n = word2.size();
    
    
    vector<int> col(n + 1, 0);
    vector<vector<int> > distance(m + 1, col);
    
    for (int i = 0; i <= m; ++i) {
        distance[i][0] = i;
    }
    
    for (int i = 0; i <= n; ++i) {
        distance[0][i] = i;
    }
    
    
    
    
    
    
    
    
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            
            distance[i][j] = distance[i-1][j-1];
            if (word1[i-1] != word2[j-1]) {
                distance[i][j] += 1;
            }
            
            if (distance[i][j] > distance[i-1][j] + 1) {
                distance[i][j] = distance[i-1][j] + 1;
            }
            
            if (distance[i][j] > distance[i][j-1] + 1) {
                distance[i][j] = distance[i][j-1] + 1;
            }
            
        }
    }
    
    
    
    return distance[m][n];
}