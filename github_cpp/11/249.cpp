#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
//과연 자바나 파이썬으로 만들 수 있을까....
string reverse(string::iterator & it) {
	char head = *it;

	it++;

	if (head == 'b' || head == 'w')
		return string(1, head);			//"(head)" 라는 문자열을 만듬

	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string underLeft = reverse(it);
	string underRight = reverse(it);

	return string("x") + underLeft + underRight + upperLeft + upperRight;
}

int main() {
	vector<string> S = {
		"w",
		"xbwwb",
		"xbwxwbbwb",
		"xxwwwbxwxwbbbwwxxxwwbbbwwwwbb" 
	};

	for (string s : S) {
		string::iterator it = s.begin();
		auto res = reverse(it);
		cout << res << endl;
	}
	return 0;
}