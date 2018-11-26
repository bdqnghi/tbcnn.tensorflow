/*************************************************************************
	> File Name: EditDistance.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年06月28日 星期日 10时07分27秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int minDistance(string word1, string word2)
{
    if(word1.empty()) return word2.size();
    if(word2.empty()) return word1.size();
    int size1 = word1.size();
    int size2 = word2.size();

    vector<vector<int> > distance;
    for(int i=0; i<=size1; ++i)
    {
        vector<int> temp(size2+1, 0);
        distance.push_back(temp);
    }
    for(int i=0; i<=size1; ++i) distance[i][0] = i;
    for(int j=0; j<=size2; ++j) distance[0][j] = j;

    for(int i=1; i<=size1; ++i)
    {
        for(int j=1; j<=size2; ++j)
        {
            int distance1 = distance[i-1][j]+1;
            int distance2 = distance[i][j-1]+1;
            int distance3 = distance[i-1][j-1]+(word1[i-1]==word2[j-1] ? 0 : 1);
            int minDis = min(distance1, distance2);
            minDis = min(minDis, distance3);
            distance[i][j] = minDis;
        }
    }
    return distance[size1][size2];
}

int main()
{
    string word1 = "a";
    string word2 = "b";
    cout<<minDistance(word1, word2)<<endl;

    return 0;
}

