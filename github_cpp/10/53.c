











#include "levenshtein.h"


unsigned int levenshtein_distance(const std::string& s1, const std::string& s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2+1), prevCol(len2+1);
    
    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (unsigned int j = 0; j < len2; j++)
            
            
            col[j+1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i]==s2[j] ? 0 : 1) });
        col.swap(prevCol);
    }
    return prevCol[len2];
}


string commands[] = {"login", "order", "serve", "depart", "arrive", "logout", "status", "summary", "help", "deliver"};


string guessCommand(string word){
    string closest = "";
    int closestNum = 100;
    int secondClosest = 101;
    int levDist;
    
    for(auto &test : commands){
        levDist = levenshtein_distance(test, word);
        if(levDist < closestNum){
            closest = test;
            closestNum = levDist;
        }
        else if(levDist < secondClosest)
            secondClosest = levDist;
        
    }
    
    if(secondClosest - closestNum < 2){
        cout << "Did you mean " << closest << "?" << endl;
        return "";
    }
    else if(closestNum <= 1)
        return closest;
    else{
        cout << "Did you mean " << closest << "?" << endl;
        return "";
    }
}


bool isValidCommand(string word){
    for(auto &test : commands){
        if(test == word)
            return true;
    }
    return false;
}

