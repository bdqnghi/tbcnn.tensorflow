




#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <iterator>


using namespace std;



class Solution {
public:

    int minDistance(string word1, string word2) {
        
        

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




