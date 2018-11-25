#include <iostream>

using namespace std;

void reverse(string);

int main() {

	string sentence;
	getline(cin, sentence);

	

	int start = 1;
	int dist = 0;

	for (int i = sentence.length() - 1; i >= 0; i--) {
		dist++;
		if (sentence[i] == ' ') {
			string tmp = sentence.substr(i + 1, dist);
			dist = 0;
			reverse(tmp);
			if (start == 1) { 
				start = 0;
			} else { 
				cout << " ";
			}
		}
		else if (i == 0) { 
			string tmp = sentence.substr(i, dist);
			reverse(tmp);
		}
	}
}

void reverse(string sent) {
	for (int i = sent.length() - 1; i >= 0; i--) {
		cout << sent[i];
	}
}
