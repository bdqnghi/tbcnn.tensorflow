#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <stack>
#include <functional>
#include <unordered_map>
#include <set>
#include <list>
#include <unordered_set>


using namespace std;

class Solution {
public:
	void reverse_until_here(string &s, int i, int j) {
		while(i <= j){
			char tmp = s[j];
			s[j] = s[i];
			s[i] = tmp;
			i++;
			j--;
		}
	}
    void reverseWords(string &s) {
    	int i = 0;
    	while(i < s.size() - 1) {
    		if(s[i] == ' ')
    			i++;
    		else break;
    	}
    	s.erase(0, i);
    	i = s.size() - 1;
    	while(i >= 0) {
    		if(s[i] == ' ')
    			i--;
    		else break;
    	}
    	s.erase(i + 1, s.size() - i);
    	reverse(s.begin(), s.end());
    	cout << "'" << s << "'" << endl;

    }
};

int main()
{
    //vector<vector<char> > v{{'X','O','X','O','X','O'},{'O','X','O','X','O','X'},{'X','O','X','O','X','O'},{'O','X','O','X','O','X'}};
    //string s("   the sky is blue   ");
    string s("   the sky is blue");
    Solution obj;
	cout << "'" << s << "'" << endl;
    obj.reverseWords(s);
    cout << "'" << s << "'" << endl;
}