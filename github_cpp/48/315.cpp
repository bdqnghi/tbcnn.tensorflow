//
//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
//
//For example,
//"A man, a plan, a canal: Panama" is a palindrome.
//"race a car" is not a palindrome.
//

#include <stdio.h>
#include <iostream>
using namespace std;

class Solution {

    public:
        bool isPalindrome(string s) {
            int i = 0;
            int j = s.length() - 1;
            char head, tail;
            while(i<j) {
                head = tolower(s[i]);
                //cout << "head:" << head << int(head) << endl;
                if (head < 48 || head > 122 || (head > 57 && head < 97)) {
                    i++;
                    continue;
                }
                tail = tolower(s[j]);
                //cout << "tail: " << tail << endl;
                if (tail < 48 || tail > 122 || (tail > 57 && tail < 97)) {
                    j--;
                    continue;
                }
                //cout << head << "---" << tail << endl;
                if (head != tail) {
                    return false;
                }
                i++;
                j--;
            }
            return true;
        }
};

int main(int argc, char* argv[]) {
    Solution s = Solution();
    cout << s.isPalindrome("A man, a plan, a canal: Panama") << endl;
    cout << s.isPalindrome("race a car") << endl;
    cout << s.isPalindrome("") << endl;
    cout << s.isPalindrome("1a2") << endl;
}
