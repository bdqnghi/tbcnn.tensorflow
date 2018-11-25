







#include "StringEditDistance.hpp"




int stringEditDistance(string s, string t) {
    
    
    
    int editDistance[s.length() + 1][t.length() + 1];
    
    
    editDistance[0][0] = 0;
    
    for(int i = 1; i <= s.length(); i++) {
        editDistance[0][i] = i;
    }
    
    
    for(int i = 1; i <= t.length(); i++) {
        editDistance[i][0] = i;
    }
    
    
    for(int i = 1; i <= s.length(); i++) {
        for(int j = 1; j <= t.length(); j++) {
           
            
            if(s.at(i-1) == t.at(j-1)) {
                editDistance[i][j] = min(min(editDistance[i-1][j-1], editDistance[i][j-1]), editDistance[i-1][j]);
            }
            else {
            
            editDistance[i][j] = min(min(editDistance[i-1][j-1], editDistance[i][j-1]), editDistance[i-1][j]) + 1;
            }
        }
    }
    

    
    
    return editDistance[s.length()][t.length()];
}

void stringEditDistanceTest() {
    
    string s;
    string t;
    
    
    cin >> s;
    cin >> t;
    
    cout << stringEditDistance(s, t) << endl;
}