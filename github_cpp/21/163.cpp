#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> d(m + 1, vector<int>(n + 1));
        for(int i=0;i<=m;i++)
            d[i][0] = i;
        for(int j=0;j<=n;j++)
            d[0][j] = j;

        for(int j=1;j<=n;j++) {
            for(int i=1;i<=m;i++) {
                if(word1[i-1] == word2[j-1]) {
                    d[i][j] = d[i-1][j-1];
                }
                else {
                    d[i][j] = find_min({d[i-1][j], d[i][j-1], d[i-1][j-1]}) + 1;
                }
            }
        }
        /* for(auto &row:d) { */
        /*     copy(row.begin(), row.end(), std::ostream_iterator<int>(std::cout, " ")); */
        /*     cout << endl; */
        /* } */

        return d[m][n];
    }

    int find_min(std::initializer_list<int> ilist) {
        std::min(ilist, [](const int &n1, const int &n2) { return n1 < n2; });
    }
};

int main()
{
    Solution s;
    cout << s.minDistance("sitting", "kitten");
}
