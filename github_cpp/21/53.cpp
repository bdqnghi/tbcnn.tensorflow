/*
 * Song Qiang <qiang.song@usc.edu> 2012
 */


/*

Edit Distance

Given two words word1 and word2, find the minimum number of steps
required to convert word1 to word2. (each operation is counted as 1
step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

 */

#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <iterator>


using namespace std;


// dynamic programming
class Solution {
public:

    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (word2.empty()) return word1.size();
        if (word1.empty()) return word2.size();

        const int MAX = numeric_limits<int>::max();
        const int n1 = word1.size();
        const int n2 = word2.size();
        
        vector<vector<int> > d(n2, vector<int>(n1, MAX));

        for (int i1 = 0; i1 < n1; ++i1)
            d[0][i1] = min((word2[0] != word1[i1]) + i1,
                           i1 > 0 ? (1 + d[0][i1 - 1]) : MAX);
        
        for (int i2 = 1; i2 < n2; ++i2)
            for (int i1 = 0; i1 < n1; ++i1)
            {
                const int md = (word1[i1] != word2[i2])
                    + (i1 == 0 ? i2 : d[i2 - 1][i1 - 1]);
                d[i2][i1] = min(md, min(i2 > 0 ? (1 + d[i2 - 1][i1]) : MAX,
                                        i1 > 0 ? (1 + d[i2][i1 - 1]) : MAX));
            }

        int best(MAX);
        for (int i1 = 0; i1 < n1; ++i1)
            best = min(best, d[n2 - 1][i1] + n1 - i1 - 1);
        for (int i2 = 0; i2 < n2; ++i2)
            best = min(best, d[i2][n1 - 1] + n2 - i2 - 1);


        // cout << " \t";
        // copy(word1.begin(), word1.end(), ostream_iterator<char>(cout, "\t"));
        // cout << endl;
        // for (int i2 = 0; i2 < n2; ++i2)
        // {
        //     cout << word2[i2] << "\t";
        //     copy(d[i2].begin(), d[i2].end(), ostream_iterator<int>(cout, "\t"));
        //     cout << endl;
        // }
        
        return best;
    }
};

                   

int
main(int argc, char *argv[])
{
    Solution r;
    cout << r.minDistance(argv[1], argv[2]) << endl;
    return 0;
}


// "pla   sma", 
// "altruism"
