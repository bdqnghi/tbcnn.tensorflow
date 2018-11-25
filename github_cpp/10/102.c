



#include "Levenshtein.h"

size_t
levenshtein(const std::string & str1, const std::string & str2,
        size_t w, size_t s, size_t a, size_t d) {

    auto len1 = str1.size(), len2 = str2.size();
	auto row0 = new size_t[len2 + 1], 
         row1 = new size_t[len2 + 1], 
         row2 = new size_t[len2 + 1];
	size_t i = 0, j = 0;

    for (; j <= len2; j++)
        row1[j] = j * a;
    for (; i < len1; i++) {

        row2[0] = (i + 1) * d;
        for (j = 0; j < len2; j++) {

            
            row2[j + 1] = row1[j] + s * (str1[i] != str2[j]);

            
            if (i > 0 && j > 0 && str1[i - 1] == str2[j] &&
                    str1[i] == str2[j - 1] &&
                    row2[j + 1] > row0[j - 1] + w)
                row2[j + 1] = row0[j - 1] + w;

            
            if (row2[j + 1] > row1[j + 1] + d)
                row2[j + 1] = row1[j + 1] + d;

            
            if (row2[j + 1] > row2[j] + a)
                row2[j + 1] = row2[j] + a;
        }

        
        auto dummy = row0;
        row0 = row1;
        row1 = row2;
        row2 = dummy;
    }

    i = row1[len2];
    delete [] row0;
    delete [] row1;
    delete [] row2;

    return i;
}
