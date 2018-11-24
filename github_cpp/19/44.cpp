#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
 
 
using namespace std;
 
vector<int> p(string &s) {
    vector<int> p(s.size());
    p[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int k = p[i-1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    string str, substr;
    getline(cin, str);
    getline(cin, substr);
 
    if (substr.size() > str.size()) {
        cout << -1;
        return 0;
    }
 
    string kmp_query = substr + "$" + str;
 
    vector<int> prefs = p(kmp_query);
    for (int i = 2*substr.size(); i < kmp_query.size(); ++i) {
        if (prefs[i] == substr.size()) {
            cout << i-2*substr.size()+1;
            return 0;
        }
    }
    cout << -1;
    return 0;
}
