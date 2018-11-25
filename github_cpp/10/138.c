#include <algorithm>
#include <vector>

#include "LevenshteinDistance.h"

namespace lvstn
{
    int distance(const std::string & source, const std::string & target) {

        
        const int n = source.length();
        const int m = target.length();
        if (n == 0) {
            return m;
        }
        if (m == 0) {
            return n;
        }

        
        typedef std::vector< std::vector<int> > Tmatrix; 

        Tmatrix matrix(n+1);

        
        
        for (int i = 0; i <= n; i++) {
            matrix[i].resize(m+1);
        }

        
        for (int i = 0; i <= n; i++) {
            matrix[i][0]=i;
        }

        for (int j = 0; j <= m; j++) {
            matrix[0][j]=j;
        }

        
        for (int i = 1; i <= n; i++) {

            const char s_i = source[i-1];

            
            for (int j = 1; j <= m; j++) {

                const char t_j = target[j-1];
                

                int cost;
                if (s_i == t_j) {
                    cost = 0;
                }
                else {
                    cost = 1;
                }

                
                const int above = matrix[i-1][j];
                const int left = matrix[i][j-1];
                const int diag = matrix[i-1][j-1];
                 int cell = std::min( above + 1, std::min(left + 1, diag + cost));

                
                
                
                
                

                if (i>2 && j>2) {
                    int trans=matrix[i-2][j-2]+1;
                    if (source[i-2]!=t_j) trans++;
                    if (s_i!=target[j-2]) trans++;
                    if (cell>trans) cell=trans;
                }

                matrix[i][j]=cell;
            }
        }

        
        return matrix[n][m];
    }
}
