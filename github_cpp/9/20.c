





string reverse(const string& s)
{
    string res=""; 
    
    for(auto i = s.rbegin(); i != s.rend(); ++i) res+=*i; 
    return res; 
}




string word_reverse(const string& s)
{
    string res; 
    string word; 
    
    stringstream str1(reverse(s)); 
    
    
    
    while((str1) && (getline(str1, word, ' '))) 
    {
        res += reverse(word) + ' '; 
    }
    return res; 
}



