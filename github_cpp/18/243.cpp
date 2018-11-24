#include <bits/stdc++.h>
using namespace std;

void reverse(string& s, int begin, int end) {
    while (begin <= end) {
        char c = s[begin];
        s[begin] = s[end];
        s[end] = c;
        begin++;
        end--;
    }
}

void reversewords(string& s) {
    int begin = 0;
    int end = 0;
    int l = s.length();
    while (end < l) {
        end++;
        if (end == l) {
            reverse(s, begin, end-1);
        }
        else if (s[end] == ' ') {
            reverse(s, begin, end-1);
            begin = end+1;
        }
    }
    reverse(s, 0, l-1);
}

int main() {
    string s = "My name is Anand";
    reversewords(s);
    cout << s << endl;
}