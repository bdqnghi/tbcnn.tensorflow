#include <string>
#include <cstring>
#include <list>
#include <iostream>
#include <vector>

#include "StringOps.h"

using namespace std;

const int K = 2;
const char* DELIM = " ,.-:;?!\"\t\n\v\f\r";   //Characters that are not words


//Provide a hardcopy of a string and all uppercases will be lowercased
string lowercaseThisString(string _word){
  for(unsigned int i=0; i<_word.length(); i++){
    if('A'<=_word[i] && _word[i]<='Z'){
      _word[i]=char(((int)_word[i])+32);
    }
  }
  return _word;
}

list<string> tokenizeString(char* query){
  list<string> result;
  char* token;
  string tokenS;

  token = strtok(query, DELIM);
  if(!token) return result;
  if((string)token != ""){
    tokenS = lowercaseThisString(token);
    result.push_back(tokenS);
    for(int i = 1; i < 100; ++i){
      token = strtok(0, DELIM);
      if(!token) break;
      if((string)token == "") continue;
      tokenS = lowercaseThisString(token);
      result.push_back(tokenS);
    }
  }
  return result;
}

//Works not so good
// Edit- / Levenshtein-distance
unsigned int editDistance(string *s1, string *s2){
  size_t len1 = s1->size(), len2 = s2->size();
  size_t dist[(len1+1) * (len2+1)];

  dist[0] = 0;
  for (size_t i=1; i<=len1;++i) dist[i*(len1+1) + 0] = i;
  for (size_t i=1; i<=len2;++i) dist[0*(len1+1) + i] = i;

  for (size_t i=1; i<=len1; ++i) {
    for (size_t j=1; j<=len2; ++j) {
      dist[i*(len1+1) + j] =
            min(
              min(dist[(i-1)*(len1+1) + j]+1 , //add
                  dist[i*(len1+1) + (j+1)]+1), //delete
              //edit
              dist[(i-1)*(len1+1) + (j-1)] + (s1[i-1] == s2[j-1] ? 0 : 1) );
    }
  }
  return dist[len1*(len1+1) + len2];
}

//Works better
unsigned int levenshtein_distance(string s1, string s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

    for (unsigned int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i + 1;
        for (unsigned int j = 0; j < len2; j++)

            col[j + 1] = min(
                             min(prevCol[1 + j] + 1, col[j] + 1),
                             prevCol[j] + (s1[i] == s2[j] ? 0 : 1));
        col.swap(prevCol);
    }
    return prevCol[len2];
}

// k-gramme berechnen
void computeKGrams(string word, list<string> *kGramList){
  //cout<<"kGrams for "<<word<<" are: ";
  for (size_t i = 0; i < word.size(); ++i){
    string kGram = word.substr(i, K);
    if (kGram.size() == K){
      kGramList->push_back(kGram);
      //cout<<kGram<<" ";
    }
  }
  kGramList->sort();
  kGramList->unique();
  
}
