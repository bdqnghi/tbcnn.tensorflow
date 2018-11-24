#include <bits/stdc++.h>

using namespace std;

int main() {
	string str, substr;
	
	str = "aabaabaaaabaabaaab";
	substr = "aabaa";
	
	str = substr + "%" + str;
	
	cout << str << endl;
	
	for(int i=0; i<str.size(); i++) {
		cout << setw(substr.size()/ 10 + 2) << str[i]; 
	}
	cout << endl;
	
	int pref[str.size() + 1];
	vector<int> indexes;
	pref[0] = 0;
	int k = 0;
	cout << setw(substr.size()/ 10 + 2) << 0;
	for(int i=1; i< str.size(); i++) {
		while(k > 0 && str[i] != str[k]) {
			k = pref[k - 1];
		}
			
		if(str[i] == str[k]) k++;
		pref[i] = k;
		cout << setw(substr.size()/ 10 + 2) << pref[i]; 
		if(pref[i] == substr.size())
			indexes.push_back(i - substr.size()*2);
	}

	cout << endl;
	
	cout << "indexes: ";
	for(int i=0; i<indexes.size(); i++)
		cout << indexes[i] << " ";
}
