
// Original Challenge at https://www.hackerrank.com/contests/ngcjcjccg/challenges/string-reverse
// Challenge1: Reverse a string char by char 
// Challenge2: Reverse a string word by word (hint: reuse the above result)

/**
  * @brief It reverses a string char by char simply iterating from `rbegin()` to `rend()` 
  */
string reverse(const string& s)
{
    string res=""; 
    // NOTE: Using += operator to appen the `char` to a `string` appunto 
    for(auto i = s.rbegin(); i != s.rend(); ++i) res+=*i; 
    return res; 
}



/**
  * @brief It reverses a string word by word first reversing it char by char and then reversing again at word level 
  * @note Words are got via a sort of PHP explode() function, using ' ' as a delimiter and implemented with getline() 
  */
string word_reverse(const string& s)
{
    string res; 
    string word; 
    
    stringstream str1(reverse(s)); 
    // NOTE: Two possible failure conditions 
    // 1. Stream empty 
    // 2. getline() fails and in this word value has not to be used 
    while((str1) && (getline(str1, word, ' '))) 
    {
        res += reverse(word) + ' '; 
    }
    return res; 
}



