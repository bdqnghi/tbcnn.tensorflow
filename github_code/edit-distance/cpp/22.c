#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
/* Iterative Levenshtein Distance calculation. 
   Calculates the number of edits needed to change string s1 into s2. 
   Edits include substitutions, insertions, and deletions.

   Algorithm from http://en.wikipedia.org/wiki/Levenshtein_distance
*/ 
int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.length();
    int n = s2.length();
    // for all i and j, d[i,j] will hold the Levenshtein distance between
    // the first i characters of s and the first j characters of t;
    // note that d has (m+1)*(n+1) values
    std::vector<std::vector<int> > d(m+1, std::vector<int>(n+1));
 
    // source prefixes can be transformed into empty string by
    // dropping all characters
    for (int i = 1; i <= m; i++) {
        d[i][0] = i;
    }

    // target prefixes can be reached from empty source prefix
    // by inserting every characters
    for (int j = 1; j <= n; j++) {
        d[0][j] = j;
    }
 
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (s1[i-1] == s2[j-1])
                d[i][j] = d[i-1][j-1];  // no operation required
            else
                d[i][j] = std::min({d[i-1][j] + 1,   // deletion
                                d[i][j-1] + 1,      // insertion
                                d[i-1][j-1] + 1});   // substitution
        }
    }

    return d[m][n];
}

/*
 * Test program for levenshtein distance.
 */
/*
int main(int argc, char **argv) {
    if (argc != 3)
        std::cout << "Two arguments required." << std::endl;

    std::string s1, s2;
    s1 = argv[1];
    s2 = argv[2];

    int distance = levenshteinDistance(s1, s2);
    std::cout << s1 << " -> " << s2 << " has L distance of: " << distance << std::endl;

    return 0;
}
*/

