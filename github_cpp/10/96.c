







#include "edit_distance.h"

#include <iostream>




size_t editDistance(const std::string & first, const std::string & second)
{
    size_t s1Len = first.length();
    size_t s2Len = second.length();
    
    if (s1Len == 0) {
        return s2Len;
    }
    
    if (s2Len == 0) {
        return s1Len;
    }
    
    size_t ed[s1Len+1][s2Len+1];
    
    
    size_t i = 0;
    for (; i <= s1Len; ++i) {
        
        
        ed[i][0] = i;
        
        if (i <= s2Len) {
            ed[0][i] = i;
        }
    }
    
    if (i<=s2Len) {
        for (;i<=s2Len; ++i) {
            ed[0][i] = i;
        }
    }
    
    
    
    for (size_t i = 1; i <= s1Len; i++) {
        for (size_t j = 1; j <= s2Len; j++) {
            ed[i][j] = std::min(
                                ed[i-1][j-1] + (first[i-1] == second[j-1]? 0 : 1),
                                std::min (
                                    ed[i][j-1] + 1,
                                          ed[i-1][j] + 1)
                                );
        }
    }









    return ed[s1Len][s2Len];
}

void unitTestEditDistance()
{
    {
        std::cout << "ed(\"balaji\", \"bala\") = " << editDistance("balaji", "bala") << "\n\n";
    }
    
    {
        std::cout << "ed(\"balaji\", \"baala\") = " << editDistance("baalaji", "bala") << "\n\n";
    }
    
    {
        std::cout << "ed(\"dhaaraa\", \"dhara\") = " << editDistance("dhaaraa", "dhara") << "\n\n";
    }
    
    {
        std::cout << "ed(\"dhaaraa\", \"\") = " << editDistance("dhaaraa", "") << "\n\n";
    }

    {
        std::cout << "ed(\"\", \"dhaaraa\") = " << editDistance("", "dhaaraa") << "\n\n";
    }
    
    {
        std::cout << "ed(\"balaji\", \"dhaaraa\") = " << editDistance("balaji", "dhaaraa") << "\n\n";
    }
    {
        std::cout << "ed(\"bar\", \"tap\") = " << editDistance("bar", "tap") << "\n\n";
    }

    {
        std::string word1("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef");
        std::string word2("bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg");
        std::cout << "ed("<< word1 <<", "<< word2 << ") = " << editDistance(word1, word2) << "\n\n";
    }
}
