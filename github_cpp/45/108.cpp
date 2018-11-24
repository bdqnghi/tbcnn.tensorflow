#include <iostream>
#include <vector>

using namespace std;


vector<int> PrefixFunction(string S) {
    vector<int> p(S.size());
    int j = 0;
    for (int i = 1; i < (int)S.size(); i++) {
        while (j > 0 && S[j] != S[i])
            j = p[j-1];

        if (S[j] == S[i])
            j++;
        p[i] = j;
    }
    return p;
}

int main() {
    vector<int> theshit = PrefixFunction("ababbabbabbababbabb");
    for(int i=0; i<theshit.size(); i++)
        cout << theshit[i] << " ";
    return 0;
}