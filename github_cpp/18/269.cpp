class Solution {
public:
    void reverse(string &s, int start, int end){
        for(int i=0; i<(end-start+1)/2; i++){
            char temp = s[start+i];
            s[start+i] = s[end-i];
            s[end-i] = temp;
        }
    }
    string reverseStr(string s, int k) {
        string result = s;
        if(k <= 0) return s;
        int size = s.length();
        if(size < k){
            reverse(result, 0, size-1);
        }
        else{
            for(int i=0; i<size; i+=2*k){
                if(i+k-1 >= size){
                    reverse(result, i, size-1);
                }
                else
                    reverse(result, i, i+k-1);
            }
        }
        return result;
    }
};
