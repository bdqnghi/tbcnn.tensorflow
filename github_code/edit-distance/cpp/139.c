/*******************************************************************************
 *  @File  : 072_edit_distance.cpp
 *  @Author: Zhang Zixuan
 *  @Email : zixuan.zhang.victor@gmail.com
 *  @Blog  : www.noathinker.com
 *  @Date  : Sun 03 Jan 2016 04:06:50 PM CST
 ******************************************************************************/

/*
 * Question:
 *
 * Given two words word1 and word2, find the minimum number of steps required
 * to convert word1 to word2. (each operation is counted as 1 step.)
 *
 * You have the following 3 operations permitted on a word:
 *
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 *
 */

#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int len1 = word1.length();
        int len2 = word2.length();

        int **distance = new int*[len1+1];
        for (int i = 0; i < len1+1; ++i)
            distance[i] = new int[len2+1];
        
        // initialize
        for (int i = 0; i < len1+1; ++i)
            distance[i][0] = i;
        for (int i = 0; i < len2+1; ++i)
            distance[0][i] = i;

        for (int i = 1; i < len1+1; ++i)
        {
            for (int j = 1; j < len2+1; ++j)
            {
                if (word1[i-1] == word2[j-1])
                    distance[i][j] = distance[i-1][j-1];
                else
                {
                    int _min = min(distance[i-1][j], distance[i][j-1]);
                    _min = min(_min, distance[i-1][j-1]);
                    distance[i][j] = _min + 1;
                }
            }
        }

        for (int i = 0; i < len1+1; ++i)
        {
            for (int j = 0; j < len2+1; ++j)
                cout<<distance[i][j]<<" ";
            cout<<endl;
        }
        return distance[len1][len2];
    }
};

int main()
{
    Solution s;
    int res = s.minDistance("intention", "execution");
    cout<<res<<endl;
    return 0;
}
