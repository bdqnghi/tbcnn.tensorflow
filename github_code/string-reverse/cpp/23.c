//
// Created by ZachZhang on 2017/5/1.
//

#include <iostream>
#include <sstream>

using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {
        int cur = 0;

        ostringstream out;
        auto start = s.begin();
        while (cur <= s.size() - 1) {
            if ((cur + k) >= s.size()) {
                auto end = s.end();
                reverse(start, end);
                out << s.substr(cur, s.size() - cur);
                cur += k;
            } else {
                auto end = start + k;
                reverse(start, end);
                out << s.substr(cur, k);
                cur += k;
                start += k;
                if (cur + k >= s.size())
                    out << s.substr(cur, s.size() - cur);
                else {
                    out << s.substr(cur, k);
                    start += k;
                }
                cur += k;
            }
        }
        return out.str();
    }

    string reverseStr2(string s, int k) {
        for (int left = 0; left < s.size(); left += 2*k) {
            for (int i = left, j = min(left + k - 1, (int)s.size() - 1);
                    i < j; i++, j--)
                swap(s[i], s[j]);
        }
        return s;
    }
};

int main(void) {
    Solution s;
    cout << s.reverseStr2("abcdefg", 2) << endl;

}