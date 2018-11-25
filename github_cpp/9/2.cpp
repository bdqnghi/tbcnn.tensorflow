







#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    string reverseString(string s) {
        int start = 0;
        int end = s.size()-1;
        while(start < end) {
            int temp = s[start];
            s[start++] = s[end];
            s[end--] = temp;
        }
        return s;
    }
};
