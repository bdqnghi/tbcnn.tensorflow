//we find in string from the last to the first till we find 
//first letter not space. Every time we find a word, we should 
//reverse it in the right order. And between words, we should add
//a space.
class Solution {
public:
    void reverseWords(string &s) {
        int n = s.length();
        if(n <= 0) return;
        
        string re;
        for(int i = n-1; i >= 0; --i)
        {
            while(s[i] == ' ' && i >= 0) --i;
            if(i < 0) break;
            if(!re.empty()) re += " ";
            
            string tmp;
            while(s[i] != ' ' && i >= 0) tmp.push_back(s[i--]);
            reverse(tmp.begin(), tmp.end());
            re += tmp;
        }
        s = re;
    }
};
