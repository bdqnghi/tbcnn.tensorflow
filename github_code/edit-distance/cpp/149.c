//
//  levenshtein.cpp
//  ofxTesseractExample
//
//  Created by Haochuan Liu on 11/24/13.
//
//

#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>

unsigned int levenshtein_distance(const T &s1, const T & s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2+1), prevCol(len2+1);
    
    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (unsigned int j = 0; j < len2; j++)
            col[j+1] = min( min( 1 + col[j], 1 + prevCol[1 + j]),
                           prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
        col.swap(prevCol);
    }
    return prevCol[len2];
}

